#include "utc_time.h"

#define	YearLength(yr)	(IsLeapYear(yr) ? 366 : 365)

/*********************************************************************
 * CONSTANTS
 */

// (MAXCALCTICKS * 5) + (max remainder) must be <= (uint16 max),
// so: (13105 * 5) + 7 <= 65535
#define MAXCALCTICKS  ((uint16)(13105))

#define	BEGYEAR	        1970     // UTC started at 00:00:00 January 1, 2000

#define	DAY             86400UL  // 24 hours * 60 minutes * 60 seconds

/*********************************************************************
 * EXTERNAL VARIABLES
 */

static uint8_t monthLength( uint8_t lpyr, uint8_t mon )
{
    uint8_t days = 30;

    if ( mon == 1 ) // feb
    {
        days = ( 28 + lpyr );
    }
    else
    {
        if ( mon == 0 || mon == 2 || mon == 4 || mon == 6  || mon == 7 || mon == 9 || mon == 11)
        {
        days = 31;
        }
    }

    return ( days );
}

void convert_utc_time( struct utc_time_t *tm, utc_time sec_time )
{
    // calculate the time less than a day - hours, minutes, seconds
    {
        uint32_t day = sec_time % DAY;
        tm->seconds = day % 60UL;
        tm->minutes = (day % 3600UL) / 60UL;
        tm->hour = day / 3600UL;
    }
    // Fill in the calendar - day, month, year
    {
        uint16_t numDays = sec_time / DAY;
        
        tm->year = BEGYEAR;
        while ( numDays >= YearLength( tm->year ) )
        {
        numDays -= YearLength( tm->year );
        tm->year++;
        }
    
        tm->month = 0;
        while ( numDays >= monthLength( IsLeapYear( tm->year ), tm->month ) )
        {
        numDays -= monthLength( IsLeapYear( tm->year ), tm->month );
        tm->month++;
        }
    
        tm->day = numDays;
    }
}

utc_time convert_utc_secs( struct utc_time_t *tm )
{
    uint32_t seconds;
    
    /* Seconds for the partial day */
    seconds = (((tm->hour * 60UL) + tm->minutes) * 60UL) + tm->seconds;
    
    /* Account for previous complete days */
    {
        /* Start with complete days in current month */
        uint16_t days = tm->day;
    
        /* Next, complete months in current year */
        {
        int8_t month = tm->month;
        while ( --month >= 0 )
        {
            days += monthLength( IsLeapYear( tm->year ), month );
        }
        }
    
        /* Next, complete years before current year */
        {
        uint16_t year = tm->year;
        while ( --year >= BEGYEAR )
        {
            days += YearLength( year );
        }
        }
    
        /* Add total seconds before partial day */
        seconds += (days * DAY);
    }
    
    return ( seconds );
}

