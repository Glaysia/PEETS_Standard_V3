# 004 EPWM Scope Smoke Verification

Status: `PENDING`

## Environment

- Board:
- Board revision:
- Power state:
- CCS version:
- Build configuration: CPU1 RAM
- Scope:

## Procedure

1. Load `CPU1/CPU1_RAM/CPU1.out`.
2. Run CPU1 and confirm heartbeat continues.
3. Confirm Watch values:
   - `g_epwm_smoke_initialized == 1`
   - `g_board_io_outputs_enabled == 0`
   - `g_board_io_enable_request == 0`
4. Probe buffer OE GPIOs or downstream OE test points.
5. Set `g_board_io_enable_request = 1` in Watch.
6. Confirm `g_board_io_outputs_enabled == 1`.
7. Scope EPWM1 through EPWM12 A/B pins on EV board.
8. Set `g_board_io_enable_request = 0`.
9. Confirm OE inactive and EPWM safe-off.
10. Repeat on the real board only after EV board notes are complete.

## Expected Values

- EPWM period setting: 50000 ticks in up-down mode.
- EPWM A compare: 25 percent of period.
- EPWM B compare: 50 percent of period.
- Deadband setting: 100 ticks RED/FED.
- Buffer OE default: inactive.

## Results

- Date:
- Board:
- EV board OE result:
- EV board EPWM scope result:
- Real-board OE result:
- Real-board EPWM scope result:
- Notes:

## Stop Conditions

- Unexpected current draw.
- Any power-stage node becomes active during no-power smoke.
- OE active at boot before debugger request.
- EPWM safe-off does not respond to request `0`.
