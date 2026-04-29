#include "../CPU1/include_editable/initial_header.h"
#include "../CPU1/include_editable/pwm.h"

#define CPU1_HEARTBEAT_GPIO DEVICE_GPIO_PIN_LED1
#define CPU1_HEARTBEAT_GPIO_CFG DEVICE_GPIO_CFG_LED1
#define CPU1_HEARTBEAT_HALF_PERIOD_US 1000000U
#define CM_HANDSHAKE_POLL_DELAY_US 1000U
#define CM_HANDSHAKE_TIMEOUT_POLLS 5000U
#define CPU1_TO_CM_BOOT_READY_TOKEN 0xC001CAFEUL
#define CM_TO_CPU1_ACK_READY_TOKEN 0xACCECA11UL

static volatile uint16_t g_pwm_smoke_value = 0U;
volatile uint32_t g_cm_handshake_status = 0U;
volatile uint32_t g_cm_handshake_poll_count = 0U;

#pragma DATA_SECTION(g_cpu1_to_cm_mailbox, "MSGRAM_CPU_TO_CM")
volatile uint32_t g_cpu1_to_cm_mailbox;

#pragma DATA_SECTION(g_cm_to_cpu1_mailbox, "MSGRAM_CM_TO_CPU")
volatile uint32_t g_cm_to_cpu1_mailbox;

enum
{
    CM_HANDSHAKE_STATUS_IDLE = 0U,
    CM_HANDSHAKE_STATUS_BOOTED = 1U,
    CM_HANDSHAKE_STATUS_WAITING_ACK = 2U,
    CM_HANDSHAKE_STATUS_OK = 3U,
    CM_HANDSHAKE_STATUS_TIMEOUT = 4U
};

static void cpu1_init_heartbeat(void)
{
    GPIO_setPinConfig(CPU1_HEARTBEAT_GPIO_CFG);
    GPIO_setDirectionMode(CPU1_HEARTBEAT_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(CPU1_HEARTBEAT_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_writePin(CPU1_HEARTBEAT_GPIO, 0U);
}

static void cpu1_boot_cm(void)
{
#ifdef _FLASH
    Device_bootCM(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
#else
    Device_bootCM(BOOTMODE_BOOT_TO_S0RAM);
#endif
}

static void cpu1_run_cm_handshake(void)
{
    uint32_t poll_count;

    g_cm_handshake_status = CM_HANDSHAKE_STATUS_IDLE;
    g_cm_handshake_poll_count = 0U;
    g_cpu1_to_cm_mailbox = 0U;
    g_cm_to_cpu1_mailbox = 0U;

    cpu1_boot_cm();
    g_cm_handshake_status = CM_HANDSHAKE_STATUS_BOOTED;

    g_cpu1_to_cm_mailbox = CPU1_TO_CM_BOOT_READY_TOKEN;
    g_cm_handshake_status = CM_HANDSHAKE_STATUS_WAITING_ACK;

    for (poll_count = 0U; poll_count < CM_HANDSHAKE_TIMEOUT_POLLS; ++poll_count)
    {
        if (g_cm_to_cpu1_mailbox == CM_TO_CPU1_ACK_READY_TOKEN)
        {
            g_cm_handshake_poll_count = poll_count;
            g_cm_handshake_status = CM_HANDSHAKE_STATUS_OK;
            return;
        }

        DEVICE_DELAY_US(CM_HANDSHAKE_POLL_DELAY_US);
    }

    g_cm_handshake_poll_count = CM_HANDSHAKE_TIMEOUT_POLLS;
    g_cm_handshake_status = CM_HANDSHAKE_STATUS_TIMEOUT;
}

//
// Main
//
void main(void)
{
    Device_init();
    g_pwm_smoke_value = pwm_test_run(1U);
    cpu1_init_heartbeat();
    cpu1_run_cm_handshake();

    for (;;)
    {
        GPIO_togglePin(CPU1_HEARTBEAT_GPIO);
        DEVICE_DELAY_US(CPU1_HEARTBEAT_HALF_PERIOD_US);
    }
}

//
// End of File
//
