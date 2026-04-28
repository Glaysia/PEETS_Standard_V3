
//
// Included Files
//
#include "../CPU2/include_editable/initial_header.h"

#define CPU1_TO_CPU2_BOOT_READY_TOKEN 0xC002CAFEUL
#define CPU2_TO_CPU1_ACK_READY_TOKEN 0xACCE2C11UL
#define CPU2_TICK_DELAY_US 100000U
#define CPU1_TO_CPU2_MAILBOX_ADDR 0x0003A088UL
#define CPU2_TO_CPU1_MAILBOX_ADDR 0x0003B088UL
#define CPU1_TO_CPU2_MAILBOX (*(volatile uint32_t *)CPU1_TO_CPU2_MAILBOX_ADDR)
#define CPU2_TO_CPU1_MAILBOX (*(volatile uint32_t *)CPU2_TO_CPU1_MAILBOX_ADDR)

volatile uint32_t g_cpu2_main_entered = 0U;
volatile uint32_t g_cpu2_tick_count = 0U;
volatile uint32_t g_cpu2_handshake_status = 0U;

enum
{
    CPU2_LOCAL_HANDSHAKE_STATUS_WAITING_TOKEN = 1U,
    CPU2_LOCAL_HANDSHAKE_STATUS_ACK_SENT = 2U
};

//
// Main
//
void main(void)
{
    Device_init();

    g_cpu2_main_entered = 1U;
    g_cpu2_handshake_status = CPU2_LOCAL_HANDSHAKE_STATUS_WAITING_TOKEN;

    for (;;)
    {
        if (CPU1_TO_CPU2_MAILBOX == CPU1_TO_CPU2_BOOT_READY_TOKEN)
        {
            CPU2_TO_CPU1_MAILBOX = CPU2_TO_CPU1_ACK_READY_TOKEN;
            g_cpu2_handshake_status = CPU2_LOCAL_HANDSHAKE_STATUS_ACK_SENT;
        }

        ++g_cpu2_tick_count;
        DEVICE_DELAY_US(CPU2_TICK_DELAY_US);
    }
}

//
// End of File
//
