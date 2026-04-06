#include "../CPU1/include_editable/pwm.h"

class PwmSmoke
{
public:
    explicit PwmSmoke(uint16_t seed) : value_(seed)
    {
    }

    void step(void)
    {
        value_ = static_cast<uint16_t>(value_ + 1U);
    }

    uint16_t value(void) const
    {
        return value_;
    }

private:
    uint16_t value_;
};

extern "C" uint16_t pwm_test_run(uint16_t seed)
{
    PwmSmoke pwm(seed);

    pwm.step();

    return pwm.value();
}
