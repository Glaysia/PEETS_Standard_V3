#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint16_t pwm_test_run(uint16_t seed);
void pwm_smoke_init(void);
void pwm_smoke_force_safe_off(void);
void pwm_smoke_release_outputs(void);

#ifdef __cplusplus
}
#endif

#endif
