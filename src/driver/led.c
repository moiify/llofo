#include "fibo_opencpu.h"
#include "hardware.h"
#include "user_timer.h"
#include "led.h"

void LED_on(LED_TYPE ledType)
{
    switch (ledType)
    {
        case LED_WORK:
        {
            timer_stop(TIMER_WORK_BLINK);
            fibo_gpio_set(PIN_LED_DRIVER, GPIO_LEVEL_LOW);
        }
        break;
        case LED_GNSS:
        {
            timer_stop(TIMER_GNSS_BLINK);
            fibo_gpio_set(PIN_LED_GPS_DRIVER, GPIO_LEVEL_LOW);
        }
        break;
        default:
            break;
    }

}

void LED_off(LED_TYPE ledType)
{
    switch (ledType)
    {
        case LED_WORK:
        {
            timer_stop(TIMER_WORK_BLINK);
            fibo_gpio_set(PIN_LED_DRIVER, GPIO_LEVEL_HIGH);
        }
        break;
        case LED_GNSS:
        {
            timer_stop(TIMER_GNSS_BLINK);
            fibo_gpio_set(PIN_LED_GPS_DRIVER, GPIO_LEVEL_HIGH);
        }
        break;
        default:
            break;
    }

}

static int LED_ToggleWORK(void)
{
    static GpioLevel_enum state = GPIO_LEVEL_LOW;

    if(state == GPIO_LEVEL_HIGH)
    {
        state = GPIO_LEVEL_LOW;
    }
    else
    {
        state = GPIO_LEVEL_HIGH;
    }
    fibo_gpio_set(PIN_LED_DRIVER, state);
	return 0;
}
static int LED_ToggleGNSS(void)
{
    static GpioLevel_enum state = GPIO_LEVEL_LOW;

    if(state == GPIO_LEVEL_HIGH)
    {
        state = GPIO_LEVEL_LOW;
    }
    else
    {
        state = GPIO_LEVEL_HIGH;
    }
    fibo_gpio_set(PIN_LED_GPS_DRIVER, state);
	return 0;
}

void LED_startFastBlink(LED_TYPE ledType)
{
    switch (ledType)
    {
        case LED_WORK:
        {
            if(!timer_isTimerStart(TIMER_WORK_BLINK))
            {
                timer_startRepeat(TIMER_WORK_BLINK, TIMER_MS, 200,LED_ToggleWORK);
            }
        }
        break;
        case LED_GNSS:
        {
            if(!timer_isTimerStart(TIMER_GNSS_BLINK))
            {
                timer_startRepeat(TIMER_GNSS_BLINK, TIMER_MS, 180,LED_ToggleGNSS);
            }
        }
        break;
        default :
            break;
    }
}

void LED_startSlowBlink(LED_TYPE ledType)
{
    //eat_gpt_start(2 * ONE_SECOND_GPT_TIME, EAT_TRUE, LED_Blink);
}
