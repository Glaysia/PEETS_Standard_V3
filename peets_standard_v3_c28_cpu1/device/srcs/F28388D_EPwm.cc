#include "include/f28388d_project.h"

namespace peets {
namespace epwm {

struct EpwmGpio
{
    enum Module
    {
        kNone   = 0U,
        kEpwm1  = (1U << 0),
        kEpwm2  = (1U << 1),
        kEpwm3  = (1U << 2),
        kEpwm4  = (1U << 3),
        kEpwm5  = (1U << 4),
        kEpwm6  = (1U << 5),
        kEpwm7  = (1U << 6),
        kEpwm8  = (1U << 7),
        kEpwm9  = (1U << 8),
        kEpwm10 = (1U << 9),
        kEpwm11 = (1U << 10),
        kEpwm12 = (1U << 11),
        kEpwm13 = (1U << 12),
        kEpwm14 = (1U << 13),
        kEpwm15 = (1U << 14),
        kEpwm16 = (1U << 15)
    };

    static inline void init(Uint32 mask)
    {
        if (mask == 0U)
        {
            return;
        }

        EALLOW;

        if (mask & kEpwm1) { init_epwm1(); }
        if (mask & kEpwm2) { init_epwm2(); }
        if (mask & kEpwm3) { init_epwm3(); }
        if (mask & kEpwm4) { init_epwm4(); }
        if (mask & kEpwm5) { init_epwm5(); }
        if (mask & kEpwm6) { init_epwm6(); }
        if (mask & kEpwm7) { init_epwm7(); }
        if (mask & kEpwm8) { init_epwm8(); }
        if (mask & kEpwm9) { init_epwm9(); }
        if (mask & kEpwm10) { init_epwm10(); }
        if (mask & kEpwm11) { init_epwm11(); }
        if (mask & kEpwm12) { init_epwm12(); }
        if (mask & kEpwm13) { init_epwm13(); }
        if (mask & kEpwm14) { init_epwm14(); }
        if (mask & kEpwm15) { init_epwm15(); }
        if (mask & kEpwm16) { init_epwm16(); }

        EDIS;
    }

private:
    static inline void init_epwm1(void)
    {
        // GPIO0/1 -> EPWM1A/B
        GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;
        GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
    }

    static inline void init_epwm2(void)
    {
        // GPIO2/3 -> EPWM2A/B
        GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;
        GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;
        GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
    }

    static inline void init_epwm3(void)
    {
        // GPIO4/5 -> EPWM3A/B
        GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;
        GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;
        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;
    }

    static inline void init_epwm4(void)
    {
        // GPIO6/7 -> EPWM4A/B
        GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;
        GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;
    }

    static inline void init_epwm5(void)
    {
        // GPIO8/9 -> EPWM5A/B
        GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;
        GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;
    }

    static inline void init_epwm6(void)
    {
        // GPIO10/11 -> EPWM6A/B
        GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;
        GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;
    }

    static inline void init_epwm7(void)
    {
        // GPIO12/13 -> EPWM7A/B
        GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;
        GpioCtrlRegs.GPAPUD.bit.GPIO13 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;
    }

    static inline void init_epwm8(void)
    {
        // GPIO14/15 -> EPWM8A/B
        GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1;
        GpioCtrlRegs.GPAPUD.bit.GPIO15 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;
    }

    static inline void init_epwm9(void)
    {
        // GPIO161/162 -> EPWM9A/B
        GpioCtrlRegs.GPFPUD.bit.GPIO161 = 1;
        GpioCtrlRegs.GPFPUD.bit.GPIO162 = 1;
        GpioCtrlRegs.GPFMUX1.bit.GPIO161 = 1;
        GpioCtrlRegs.GPFMUX1.bit.GPIO162 = 1;
    }

    static inline void init_epwm10(void)
    {
        // GPIO163/164 -> EPWM10A/B
        GpioCtrlRegs.GPFPUD.bit.GPIO163 = 1;
        GpioCtrlRegs.GPFPUD.bit.GPIO164 = 1;
        GpioCtrlRegs.GPFMUX1.bit.GPIO163 = 1;
        GpioCtrlRegs.GPFMUX1.bit.GPIO164 = 1;
    }

    static inline void init_epwm11(void)
    {
        // GPIO165/166 -> EPWM11A/B
        GpioCtrlRegs.GPFPUD.bit.GPIO165 = 1;
        GpioCtrlRegs.GPFPUD.bit.GPIO166 = 1;
        GpioCtrlRegs.GPFMUX1.bit.GPIO165 = 1;
        GpioCtrlRegs.GPFMUX1.bit.GPIO166 = 1;
    }

    static inline void init_epwm12(void)
    {
        // GPIO167/168 -> EPWM12A/B
        GpioCtrlRegs.GPFPUD.bit.GPIO167 = 1;
        GpioCtrlRegs.GPFPUD.bit.GPIO168 = 1;
        GpioCtrlRegs.GPFMUX1.bit.GPIO167 = 1;
        GpioCtrlRegs.GPFMUX1.bit.GPIO168 = 1;
    }

    static inline void init_epwm13(void)
    {
        // TODO: Add EPWM13 pin mux when routed.
    }

    static inline void init_epwm14(void)
    {
        // TODO: Add EPWM14 pin mux when routed.
    }

    static inline void init_epwm15(void)
    {
        // TODO: Add EPWM15 pin mux when routed.
    }

    static inline void init_epwm16(void)
    {
        // TODO: Add EPWM16 pin mux when routed.
    }
};

} // namespace epwm
} // namespace peets

#ifndef PEETS_EPWM_GPIO_ENABLE_MASK
#define PEETS_EPWM_GPIO_ENABLE_MASK \
    (peets::epwm::EpwmGpio::kEpwm1 | \
     peets::epwm::EpwmGpio::kEpwm2 | \
     peets::epwm::EpwmGpio::kEpwm3)
#endif

extern "C" void InitEPwmGpio(void)
{
    peets::epwm::EpwmGpio::init(
        static_cast<Uint32>(PEETS_EPWM_GPIO_ENABLE_MASK));
}

extern "C" void InitEPwm1Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm1);
}

extern "C" void InitEPwm2Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm2);
}

extern "C" void InitEPwm3Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm3);
}

extern "C" void InitEPwm4Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm4);
}

extern "C" void InitEPwm5Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm5);
}

extern "C" void InitEPwm6Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm6);
}

extern "C" void InitEPwm7Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm7);
}

extern "C" void InitEPwm8Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm8);
}

extern "C" void InitEPwm9Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm9);
}

extern "C" void InitEPwm10Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm10);
}

extern "C" void InitEPwm11Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm11);
}

extern "C" void InitEPwm12Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm12);
}

extern "C" void InitEPwm13Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm13);
}

extern "C" void InitEPwm14Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm14);
}

extern "C" void InitEPwm15Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm15);
}

extern "C" void InitEPwm16Gpio(void)
{
    peets::epwm::EpwmGpio::init(peets::epwm::EpwmGpio::kEpwm16);
}
