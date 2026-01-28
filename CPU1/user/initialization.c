#include "user/inc/peets.h"
#include "driverlib.h"
#include "device.h"

void only_c_init(){
    Device_init();
    Device_initGPIO();
    Device_bootCM(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
    GPIO_setPinMuxConfig();
}



