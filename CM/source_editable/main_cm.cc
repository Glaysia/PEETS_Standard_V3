
//
// Included Files
//
#include "../CM/include_editable/initial_header.h"

#define CPU1_TO_CM_BOOT_READY_TOKEN 0xC001CAFEUL
#define CM_TO_CPU1_ACK_READY_TOKEN 0xACCECA11UL
#define CM_HANDSHAKE_IDLE_DELAY_US 1000U

#pragma DATA_SECTION("MSGRAM_CPU1_TO_CM")
volatile uint32_t g_cpu1_to_cm_mailbox;

#pragma DATA_SECTION("MSGRAM_CM_TO_CPU1")
volatile uint32_t g_cm_to_cpu1_mailbox;

volatile uint32_t g_cm_main_entered = 0U;
volatile uint32_t g_cm_handshake_status = 0U;

enum
{
    CM_STATUS_IDLE = 0U,
    CM_STATUS_WAITING_BOOT_READY = 1U,
    CM_STATUS_ACK_WRITTEN = 2U
};

//
// Main
//
void main(void)
{
    CM_init();
    g_cm_main_entered = 1U;
    g_cm_handshake_status = CM_STATUS_WAITING_BOOT_READY;

    while (g_cpu1_to_cm_mailbox != CPU1_TO_CM_BOOT_READY_TOKEN)
    {
        DEVICE_DELAY_US(CM_HANDSHAKE_IDLE_DELAY_US);
    }

    g_cm_to_cpu1_mailbox = CM_TO_CPU1_ACK_READY_TOKEN;
    g_cm_handshake_status = CM_STATUS_ACK_WRITTEN;

    for (;;)
    {
        DEVICE_DELAY_US(CM_HANDSHAKE_IDLE_DELAY_US);
    }
}

//
// End of File
//
