# 004 EPWM Scope Smoke Requirements

## Scope

- Verify board I/O enable control before any power-stage experiment.
- Verify EPWM1 through EPWM12 A/B pins on the EV board with a scope first.
- Repeat the same checklist on the real board only after EV board behavior is understood.

## Requirements

### R1 Safe Default

WHEN CPU1 initialization completes
THE SYSTEM SHALL keep buffer outputs disabled and EPWM outputs in safe-off.

Acceptance:
- Buffer OE GPIOs are driven inactive.
- EPWM one-shot trip is forced.
- CPU1 heartbeat continues.

### R2 Debug-Controlled Enable

WHEN the debugger enable request is set
THE SYSTEM SHALL release EPWM safe-off and drive buffer OE active.

Acceptance:
- `g_board_io_enable_request = 1` leads to `g_board_io_outputs_enabled = 1`.
- EPWM pins produce scope-visible waveforms on EV board.

### R3 Debug-Controlled Safe-Off

WHEN the debugger enable request is cleared
THE SYSTEM SHALL disable buffer outputs and force EPWM safe-off.

Acceptance:
- `g_board_io_enable_request = 0` leads to `g_board_io_outputs_enabled = 0`.
- Scope-visible EPWM outputs are off or held in safe state.

### R4 No Power-Stage Transition Yet

IF buffer enable and safe-off behavior have not been verified
THEN the test SHALL NOT move to a power-stage experiment.

Acceptance:
- Verification notes record EV board result before real-board power-stage work.
