#include "../CPU1/include_editable/initial_header.h"
#include "../CPU1/include_editable/intercore_cpu1.h"
#include "../CPU1/include_editable/pinmux.h"
#include "../CPU1/include_editable/pwm.h"

#define CPU1_HEARTBEAT_GPIO DEVICE_GPIO_PIN_LED1
#define CPU1_HEARTBEAT_GPIO_CFG DEVICE_GPIO_CFG_LED1
#define CPU1_HEARTBEAT_HALF_PERIOD_US 1000000U
#define BOARD_IO_BUFFER_OE_INACTIVE 1U
#define BOARD_IO_BUFFER_OE_ACTIVE 0U
#define BOARD_IO_BUFFER_DIR_DEFAULT 0U

static volatile uint16_t g_pwm_smoke_value = 0U;
volatile uint32_t g_board_io_enable_request = 0U;
volatile uint32_t g_board_io_outputs_enabled = 0U;
volatile uint32_t g_epwm_smoke_initialized = 0U;

static const uint32_t kBufferOeGpios[] = {
    42U, 43U, 46U, 50U, 100U
};

static const uint32_t kBufferDirGpios[] = {
    58U, 59U, 107U, 120U
};

static void cpu1_init_heartbeat(void)
{
    GPIO_setPinConfig(CPU1_HEARTBEAT_GPIO_CFG);
    GPIO_setDirectionMode(CPU1_HEARTBEAT_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(CPU1_HEARTBEAT_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_writePin(CPU1_HEARTBEAT_GPIO, 0U);
}

static void cpu1_init_board_io_safe(void)
{
    uint16_t i;

    for (i = 0U; i < (sizeof(kBufferOeGpios) / sizeof(kBufferOeGpios[0])); ++i)
    {
        GPIO_setDirectionMode(kBufferOeGpios[i], GPIO_DIR_MODE_OUT);
        GPIO_setPadConfig(kBufferOeGpios[i], GPIO_PIN_TYPE_STD);
        GPIO_writePin(kBufferOeGpios[i], BOARD_IO_BUFFER_OE_INACTIVE);
    }

    for (i = 0U; i < (sizeof(kBufferDirGpios) / sizeof(kBufferDirGpios[0])); ++i)
    {
        GPIO_setDirectionMode(kBufferDirGpios[i], GPIO_DIR_MODE_OUT);
        GPIO_setPadConfig(kBufferDirGpios[i], GPIO_PIN_TYPE_STD);
        GPIO_writePin(kBufferDirGpios[i], BOARD_IO_BUFFER_DIR_DEFAULT);
    }

    g_board_io_outputs_enabled = 0U;
}

static void cpu1_set_board_io_outputs(uint32_t enable)
{
    uint16_t i;

    if (enable == 0U)
    {
        for (i = 0U; i < (sizeof(kBufferOeGpios) / sizeof(kBufferOeGpios[0])); ++i)
        {
            GPIO_writePin(kBufferOeGpios[i], BOARD_IO_BUFFER_OE_INACTIVE);
        }

        pwm_smoke_force_safe_off();
        g_board_io_outputs_enabled = 0U;
        return;
    }

    pwm_smoke_release_outputs();

    for (i = 0U; i < (sizeof(kBufferOeGpios) / sizeof(kBufferOeGpios[0])); ++i)
    {
        GPIO_writePin(kBufferOeGpios[i], BOARD_IO_BUFFER_OE_ACTIVE);
    }

    g_board_io_outputs_enabled = 1U;
}

//
// Main
//
void main(void)
{
    Device_init();
    GPIO_setPinMuxConfig();
    g_pwm_smoke_value = pwm_test_run(1U);
    cpu1_init_board_io_safe();
    cpu1_init_heartbeat();
    pwm_smoke_init();
    pwm_smoke_force_safe_off();
    g_epwm_smoke_initialized = 1U;
    intercore_cpu1_run_cm_handshake();
    intercore_cpu1_run_cpu2_handshake();

    for (;;)
    {
        if (g_board_io_enable_request != g_board_io_outputs_enabled)
        {
            cpu1_set_board_io_outputs(g_board_io_enable_request);
        }

        GPIO_togglePin(CPU1_HEARTBEAT_GPIO);
        DEVICE_DELAY_US(CPU1_HEARTBEAT_HALF_PERIOD_US);
    }
}

//
// End of File
//
