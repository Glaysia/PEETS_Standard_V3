#include "../CPU1/include_editable/initial_header.h"
#include "../CPU1/include_editable/pwm.h"

#define CPU1_HEARTBEAT_GPIO DEVICE_GPIO_PIN_LED1
#define CPU1_HEARTBEAT_GPIO_CFG DEVICE_GPIO_CFG_LED1
#define CPU1_HEARTBEAT_HALF_PERIOD_US 1000000U

static volatile uint16_t g_pwm_smoke_value = 0U;

//
// Main
//
void main(void)
{
    Device_init();
    g_pwm_smoke_value = pwm_test_run(1U);

    GPIO_setPinConfig(CPU1_HEARTBEAT_GPIO_CFG);
    GPIO_setDirectionMode(CPU1_HEARTBEAT_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(CPU1_HEARTBEAT_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_writePin(CPU1_HEARTBEAT_GPIO, 0U);

    for (;;)
    {
        GPIO_togglePin(CPU1_HEARTBEAT_GPIO);
        DEVICE_DELAY_US(CPU1_HEARTBEAT_HALF_PERIOD_US);
    }
}

//
// End of File
//
