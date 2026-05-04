# 004 EPWM Scope Smoke Tasks

## Code Tasks

- [x] Task 1: Apply generated CPU1 pinmux.
  - Checkpoint: `GPIO_setPinMuxConfig()` is called from CPU1 init.
  - Success condition: GPIO0 through GPIO23 are configured as EPWM pins.

- [x] Task 2: Add buffer OE/DIR safe defaults.
  - Checkpoint: OE GPIOs default inactive and DIR GPIOs default low.
  - Success condition: `g_board_io_outputs_enabled == 0` after boot.

- [x] Task 3: Add EPWM1 through EPWM12 scope smoke profile.
  - Checkpoint: driverlib EPWM init builds for CPU1.
  - Success condition: CPU1 build produces `CPU1.out`.

- [x] Task 4: Add debugger-controlled enable and safe-off.
  - Checkpoint: `g_board_io_enable_request` controls EPWM trip and OE pins.
  - Success condition: request `1` enables outputs, request `0` disables outputs.

## Bench Tasks

- [ ] Task 5: EV board buffer enable check.
  - Checkpoint: measure OE GPIO level before and after request change.
  - Success condition: OE inactive at boot, active only after request `1`.

- [ ] Task 6: EV board EPWM scope check.
  - Checkpoint: scope EPWM1 through EPWM12 A/B.
  - Success condition: expected frequency, duty, and deadband are visible without power-stage load.

- [ ] Task 7: Real-board repeat.
  - Checkpoint: use the same EV board checklist.
  - Success condition: real-board I/O behavior matches EV board before power-stage work.
