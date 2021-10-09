#include "fibo_opencpu.h"

#include "watchdog.h"

#define WAKE_TIMEOUT  (10)
#define SLEEP_TIMEOUT (300)  //5分钟

void startWatchdog(WatchDog_Env env)
{
    if(env == WD_WAKE)
    {
        fibo_watchdog_enable(WAKE_TIMEOUT);
    }
    else if(env == WD_SLEEP)
    {
        fibo_watchdog_enable(SLEEP_TIMEOUT);
    }
}

void stopWatchdog(void)
{
    fibo_watchdog_disable();
}

void feedWatchdog(void)
{
    fibo_watchdog_feed();
}

