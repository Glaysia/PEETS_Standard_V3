#include "../CM/include_editable/initial_header.h"
#include "../CM/include_editable/comm_cm.h"

#define CPU1_TO_CM_BOOT_READY_TOKEN 0xC001CAFEUL
#define CM_TO_CPU1_ACK_READY_TOKEN 0xACCECA11UL
#define CM_HANDSHAKE_IDLE_DELAY_US 1000U
#define CPU1_CM_IPC_DRIVERLIB_BUFFER_WORDS 68U
#define CM_UART_TX_BAUDRATE 115200U
#define CM_UART_TX_IDLE_DELAY_US 100000U

#pragma DATA_SECTION("MSGRAM_CPU1_TO_CM")
volatile uint32_t g_cpu1_to_cm_ipc_buffer_pad[CPU1_CM_IPC_DRIVERLIB_BUFFER_WORDS];

#pragma DATA_SECTION("MSGRAM_CPU1_TO_CM")
volatile uint32_t g_cpu1_to_cm_mailbox;

#pragma DATA_SECTION("MSGRAM_CM_TO_CPU1")
volatile uint32_t g_cm_to_cpu1_ipc_buffer_pad[CPU1_CM_IPC_DRIVERLIB_BUFFER_WORDS];

#pragma DATA_SECTION("MSGRAM_CM_TO_CPU1")
volatile uint32_t g_cm_to_cpu1_mailbox;

volatile uint32_t g_cm_main_entered = 0U;
volatile uint32_t g_cm_handshake_status = 0U;
volatile uint32_t g_cm_uart_tx_count = 0U;

static void comm_cm_uart_write_string(const char *text)
{
    while (*text != '\0')
    {
        UART_writeChar(UART0_BASE, (uint8_t)*text);
        ++text;
    }
}

void comm_cm_init_status(void)
{
    g_cm_main_entered = 1U;
    g_cm_handshake_status = CM_STATUS_WAITING_BOOT_READY;
}

void comm_cm_wait_for_cpu1_boot_ready_and_ack(void)
{
    while (g_cpu1_to_cm_mailbox != CPU1_TO_CM_BOOT_READY_TOKEN)
    {
        DEVICE_DELAY_US(CM_HANDSHAKE_IDLE_DELAY_US);
    }

    g_cm_to_cpu1_mailbox = CM_TO_CPU1_ACK_READY_TOKEN;
    g_cm_handshake_status = CM_STATUS_ACK_WRITTEN;
}

void comm_cm_uart_tx_init(void)
{
    UART_setConfig(UART0_BASE,
                   UART_CLK_FREQ,
                   CM_UART_TX_BAUDRATE,
                   UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                       UART_CONFIG_PAR_NONE);
    HWREG(UART0_BASE + UART_O_CTL) &= ~UART_CTL_RXE;
}

void comm_cm_uart_tx_service(void)
{
    comm_cm_uart_write_string("CM UART TX\r\n");
    ++g_cm_uart_tx_count;
    DEVICE_DELAY_US(CM_UART_TX_IDLE_DELAY_US);
}
