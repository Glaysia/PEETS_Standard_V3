#ifndef CM_INCLUDE_EDITABLE_COMM_CM_H_
#define CM_INCLUDE_EDITABLE_COMM_CM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    CM_STATUS_IDLE = 0U,
    CM_STATUS_WAITING_BOOT_READY = 1U,
    CM_STATUS_ACK_WRITTEN = 2U
};

extern volatile uint32_t g_cm_main_entered;
extern volatile uint32_t g_cm_handshake_status;
extern volatile uint32_t g_cm_uart_tx_count;
extern volatile uint32_t g_cpu1_to_cm_mailbox;
extern volatile uint32_t g_cm_to_cpu1_mailbox;

void comm_cm_init_status(void);
void comm_cm_wait_for_cpu1_boot_ready_and_ack(void);
void comm_cm_uart_tx_init(void);
void comm_cm_uart_tx_service(void);

#ifdef __cplusplus
}
#endif

#endif
