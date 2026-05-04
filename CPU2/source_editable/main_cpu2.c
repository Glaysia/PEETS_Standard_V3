
//
// Included Files
//
#include "../CPU2/include_editable/initial_header.h"
#include "../CPU2/include_editable/intercore_cpu2.h"

#define CPU2_TICK_DELAY_US 100000U

//
// Main
//
void main(void)
{
    Device_init();
    intercore_cpu2_init();

    for (;;)
    {
        intercore_cpu2_service();
        DEVICE_DELAY_US(CPU2_TICK_DELAY_US);
    }
}

//
// End of File
//
