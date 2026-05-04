#include "../CPU1/include_editable/initial_header.h"
#include "../CPU1/include_editable/intercore_cpu1.h"

#define CM_HANDSHAKE_POLL_DELAY_US 1000U
#define CM_HANDSHAKE_TIMEOUT_POLLS 5000U
#define CPU2_HANDSHAKE_POLL_DELAY_US 1000U
#define CPU2_HANDSHAKE_TIMEOUT_POLLS 5000U

#define CPU1_TO_CM_BOOT_READY_TOKEN 0xC001CAFEUL
#define CM_TO_CPU1_ACK_READY_TOKEN 0xACCECA11UL
#define CPU1_TO_CPU2_BOOT_READY_TOKEN 0xC002CAFEUL
#define CPU2_TO_CPU1_ACK_READY_TOKEN 0xACCE2C11UL

volatile uint32_t g_cm_handshake_status = 0U;
volatile uint32_t g_cm_handshake_poll_count = 0U;
volatile uint32_t g_cpu2_handshake_status = 0U;
volatile uint32_t g_cpu2_handshake_poll_count = 0U;

#pragma DATA_SECTION(g_cpu1_to_cm_mailbox, "MSGRAM_CPU_TO_CM")
volatile uint32_t g_cpu1_to_cm_mailbox;

#pragma DATA_SECTION(g_cm_to_cpu1_mailbox, "MSGRAM_CM_TO_CPU")
volatile uint32_t g_cm_to_cpu1_mailbox;

#pragma DATA_SECTION(g_cpu1_to_cpu2_mailbox, "MSGRAM_CPU1_TO_CPU2")
volatile uint32_t g_cpu1_to_cpu2_mailbox;

#pragma DATA_SECTION(g_cpu2_to_cpu1_mailbox, "MSGRAM_CPU2_TO_CPU1")
volatile uint32_t g_cpu2_to_cpu1_mailbox;

static void intercore_cpu1_boot_cm(void)
{
#ifdef _FLASH
    Device_bootCM(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
#else
    Device_bootCM(BOOTMODE_BOOT_TO_S0RAM);
#endif
}

static void intercore_cpu1_boot_cpu2(void)
{
#ifdef _FLASH
    Device_bootCPU2(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
#else
    Device_bootCPU2(BOOTMODE_BOOT_TO_M0RAM);
#endif
}

void intercore_cpu1_run_cm_handshake(void)
{
    uint32_t poll_count;

    g_cm_handshake_status = CM_HANDSHAKE_STATUS_IDLE;
    g_cm_handshake_poll_count = 0U;
    g_cpu1_to_cm_mailbox = 0U;
    g_cm_to_cpu1_mailbox = 0U;

    intercore_cpu1_boot_cm();
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

void intercore_cpu1_run_cpu2_handshake(void)
{
    uint32_t poll_count;

    g_cpu2_handshake_status = CPU2_HANDSHAKE_STATUS_IDLE;
    g_cpu2_handshake_poll_count = 0U;
    g_cpu1_to_cpu2_mailbox = 0U;
    g_cpu2_to_cpu1_mailbox = 0U;

    intercore_cpu1_boot_cpu2();
    g_cpu2_handshake_status = CPU2_HANDSHAKE_STATUS_BOOTED;

    g_cpu1_to_cpu2_mailbox = CPU1_TO_CPU2_BOOT_READY_TOKEN;
    g_cpu2_handshake_status = CPU2_HANDSHAKE_STATUS_WAITING_ACK;

    for (poll_count = 0U; poll_count < CPU2_HANDSHAKE_TIMEOUT_POLLS; ++poll_count)
    {
        if (g_cpu2_to_cpu1_mailbox == CPU2_TO_CPU1_ACK_READY_TOKEN)
        {
            g_cpu2_handshake_poll_count = poll_count;
            g_cpu2_handshake_status = CPU2_HANDSHAKE_STATUS_OK;
            return;
        }

        DEVICE_DELAY_US(CPU2_HANDSHAKE_POLL_DELAY_US);
    }

    g_cpu2_handshake_poll_count = CPU2_HANDSHAKE_TIMEOUT_POLLS;
    g_cpu2_handshake_status = CPU2_HANDSHAKE_STATUS_TIMEOUT;
}
