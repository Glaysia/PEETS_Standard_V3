# 004 EPWM Scope Smoke Design

## Current Baseline

- CPU1 owns system initialization and pinmux.
- `CPU1/include_editable/pinmux.h` maps GPIO0 through GPIO23 to EPWM1 through EPWM12 A/B.
- Buffer OE GPIOs are GPIO42, GPIO43, GPIO46, GPIO50, and GPIO100.
- Buffer OE is treated as active-low.
- Buffer DIR GPIOs are GPIO58, GPIO59, GPIO107, and GPIO120.

## Design

- CPU1 calls the generated `GPIO_setPinMuxConfig()` after `Device_init()`.
- CPU1 immediately applies board I/O safe defaults:
  - OE pins high, meaning buffer disabled.
  - DIR pins low, meaning default direction.
- `pwm_smoke_init()` configures EPWM1 through EPWM12 with driverlib while TBCLKSYNC is disabled.
- Each EPWM module starts with one-shot trip forced.
- Debugger variable `g_board_io_enable_request` controls enable and safe-off:
  - `0`: buffer disabled and EPWM trip forced.
  - `1`: EPWM trip cleared and buffer OE driven active.

## Initial Smoke Profile

- EPWM clock prescaler: divide by 1.
- Counter mode: up-down.
- Period: 50000 ticks.
- Compare A: 25 percent of period.
- Compare B: 50 percent of period.
- Deadband: 100 ticks on RED and FED.

This profile is only for no-power scope observation. ADC trigger, CMPSS, TZ fault chain, and runtime control ownership are separate follow-up work.
