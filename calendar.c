#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

const unsigned long long NANOSEC =  1ULL,
					MICRSOSEC = 1ULL * 1000ULL,
					MILLISEC = 1ULL * 1000ULL * 1000ULL,
					SEC = 	   1ULL * 1000ULL * 1000ULL * 1000ULL;

const unsigned long long MINUTE =   1ULL * 1000ULL * 1000ULL * 1000ULL * 60ULL,
					HOUR =     1ULL * 1000ULL * 1000ULL * 1000ULL * 60ULL * 60ULL,
					DAY = 	   1ULL * 1000ULL * 1000ULL * 1000ULL * 60ULL * 60ULL * 24ULL;

// Tells you if the specified year is a leap year (= 1, otherwise 0).
unsigned long long isLeapYear(unsigned long long year)
{
	return (year % 4) == 0;
}

// calculates the amount of days for a specific month in a specific year.
unsigned long long monthToDays(int isLeapYear, unsigned long long month)
{
	return month % 2ULL == 1ULL ? (month <= 7ULL ? 31ULL : 30ULL) : (month <= 7ULL ? (month == 2ULL ? (isLeapYear ? 29ULL : 28ULL) : 30ULL) : 31ULL);
}

// Tells you the amount of days for a specific year, including leap years.
unsigned long long yearToDays(unsigned long long year)
{
	unsigned long long daySum = 0;
	
	for(int month = 1; month <= 12; month++)
	{
		daySum += monthToDays((year % 4) == 0, month);
	}
	
	return daySum;
}

// Calculates the amount of days elapsed since the 1st Jan of year 1.
unsigned long long datestamp(unsigned long long year, unsigned long long month, unsigned long long day)
{
	unsigned long long daySum = 0ULL;

	for(unsigned long long yearSum = 1ULL; yearSum <= (year - 1); yearSum++)
	{
		if(isLeapYear(yearSum))
		{
			daySum += 366ULL;
		}
		else
		{
			daySum += 365ULL;
		}
	}
	
	for(unsigned long long monthSum = 1ULL; monthSum <= (month - 1); monthSum++)
	{
		daySum += monthToDays(isLeapYear(year), monthSum);
	}
	
	daySum += (day - 1);
	
	return daySum;
}

// Returns the time elapsed in nanoseconds (!) since the 1st Jan of year 1 and since the time 00:00:00 hh:mm:ss.
unsigned long long timestamp(unsigned long long datestamp, unsigned long long hour, unsigned long long minute, unsigned long long second)
{
	return datestamp * DAY + hour * HOUR + minute * MINUTE + second * SEC;
}

void test_isLeapYear()
{
	puts("test_isLeapYear()");
	assert(isLeapYear(2023ULL) == 0);
	puts("OK");
	assert(isLeapYear(2021ULL) == 0);
	puts("OK");
	assert(isLeapYear(2024ULL) == 1);
	puts("OK");
	assert(isLeapYear(2020ULL) == 1);
	puts("OK");
	assert(isLeapYear(2008ULL) == 1);
	puts("OK");
	assert(isLeapYear(2006ULL) == 0);
	puts("OK");
	assert(isLeapYear(1998ULL) == 0);
	puts("OK");
	assert(isLeapYear(1ULL) == 0);
	puts("OK");
	assert(isLeapYear(4ULL) == 1);
	puts("OK");
}

void test_monthToDays()
{
	puts("test_monthToDays()");
	assert(monthToDays(0, 1ULL) == 31ULL);
	puts("OK");
	assert(monthToDays(0, 2ULL) == 28ULL);
	puts("OK");
	assert(monthToDays(0, 3L) == 31ULL);
	puts("OK");
	assert(monthToDays(0, 4ULL) == 30ULL);
	puts("OK");
	assert(monthToDays(0, 5ULL) == 31ULL);
	puts("OK");
	assert(monthToDays(0, 6ULL) == 30ULL);
	puts("OK");
	assert(monthToDays(0, 7ULL) == 31ULL);
	puts("OK");
	assert(monthToDays(0, 8L) == 31ULL);
	puts("OK");
	assert(monthToDays(0, 9ULL) == 30ULL);
	puts("OK");
	assert(monthToDays(0, 10ULL) == 31ULL);
	puts("OK");
	assert(monthToDays(0, 11L) == 30ULL);
	puts("OK");
	assert(monthToDays(0, 12ULL) == 31ULL);
	puts("OK");
	puts("test_monthToDays() (leap years turned on)");
	assert(monthToDays(1, 1ULL) == 31ULL);
	puts("OK");
	assert(monthToDays(1, 2ULL) == 29ULL);
	puts("OK");
	assert(monthToDays(1, 3L) == 31ULL);
	puts("OK");
	assert(monthToDays(1, 4ULL) == 30ULL);
	puts("OK");
	assert(monthToDays(1, 5ULL) == 31ULL);
	puts("OK");
	assert(monthToDays(1, 6ULL) == 30ULL);
	puts("OK");
	assert(monthToDays(1, 7ULL) == 31ULL);
	puts("OK");
	assert(monthToDays(1, 8L) == 31ULL);
	puts("OK");
	assert(monthToDays(1, 9ULL) == 30ULL);
	puts("OK");
	assert(monthToDays(1, 10ULL) == 31ULL);
	puts("OK");
	assert(monthToDays(1, 11L) == 30ULL);
	puts("OK");
	assert(monthToDays(1, 12ULL) == 31ULL);
	puts("OK");
}

void test_yearToDays()
{	
	puts("test_yearToDays()");
	assert(yearToDays(2020ULL) == 366ULL);
	puts("OK");
	assert(yearToDays(2023ULL) == 365ULL);	
	puts("OK");
	assert(yearToDays(2012ULL) == 366ULL);	
	puts("OK");
	assert(yearToDays(2008ULL) == 366ULL);	
	puts("OK");
	assert(yearToDays(2006ULL) == 365ULL);	
	puts("OK");
	assert(yearToDays(1ULL) == 365ULL);
	puts("OK");
	assert(yearToDays(4ULL) == 366ULL);
	puts("OK");
}

void test_datestamp()
{
	puts("test_datestamp()");
	assert(datestamp(1ULL, 1ULL, 1ULL) == 0ULL); // 1st Jan of year 1
	puts("OK");
	assert(datestamp(1ULL, 1ULL, 2ULL) == 1ULL); // 2nd Jan of year 1
	puts("OK");
	assert(datestamp(1ULL, 1ULL, 3ULL) == 2ULL); // 3rd Jan of year 1
	puts("OK");
	assert(datestamp(1ULL, 12ULL, 31ULL) == 364ULL); // 31st Dec of year 1
	puts("OK");
	assert(datestamp(2ULL, 1ULL, 1ULL) == 365ULL); // 1st Jan of year 2
	puts("OK");
	assert(datestamp(3ULL, 1ULL, 1ULL) == 2*365ULL); // 1st Jan of year 3
	puts("OK");
	assert(datestamp(4ULL, 1ULL, 1ULL) == 3*365ULL); // 1st Jan of year 4
	puts("OK");
	assert(datestamp(5ULL, 1ULL, 1ULL) == (3*365ULL + 366)); // 1st Jan of year 5
	puts("OK");
}

void test_timestamp()
{
	unsigned long long datestampReceived = 0ULL;
	
	datestampReceived = datestamp(1ULL, 1ULL, 1ULL); // 1st Jan of year 1.
	
	puts("test_timestamp()");
	assert(timestamp(datestampReceived, 0ULL, 0ULL, 0ULL) == 0ULL); // Will give you the time 00:00:00 hh:mm:ss for the 1st Jan of year 1.
	puts("OK");
	assert(timestamp(datestampReceived, 0ULL, 0ULL, 1ULL) == SEC); // Will give you the time 00:00:01 hh:mm:ss for the 1st Jan of year 1.
	puts("OK");
	assert(timestamp(datestampReceived, 0ULL, 0ULL, 2ULL) == SEC * 2ULL); // Will give you the time 00:00:02 hh:mm:ss for the 1st Jan of year 1.
	puts("OK");
	assert(timestamp(datestampReceived, 0ULL, 0ULL, 59ULL) == SEC * 59ULL); // Will give you the time 00:00:59 hh:mm:ss for the 1st Jan of year 1.
	puts("OK");
	assert(timestamp(datestampReceived, 0ULL, 1ULL, 32ULL) == SEC * 32ULL + MINUTE); // Will give you the time 00:01:32 hh:mm:ss for the 1st Jan of year 1.
	puts("OK");
	assert(timestamp(datestampReceived, 23ULL, 59ULL, 59ULL) == SEC * 59ULL + MINUTE * 59ULL + HOUR * 23ULL); // Will give you the time 23:59:59 hh:mm:ss for the 1st Jan of year 1.
	puts("OK");
	
	datestampReceived = datestamp(2ULL, 1ULL, 1ULL); // 1st Jan of year 2.
	
	assert(timestamp(datestampReceived, 0ULL, 0L, 0ULL) == 365ULL * DAY); // Will give you the time 00:00:00 hh:mm:ss for the 1st Jan of year 2.
	puts("OK");
	assert(timestamp(datestampReceived, 23ULL, 59L, 59ULL) == 365ULL * DAY + 23ULL * HOUR + 59ULL * MINUTE + 59ULL * SEC); // Will give you the time 23:59:59 hh:mm:ss for the 1st Jan of year 2.
	puts("OK");
	
	datestampReceived = datestamp(2ULL, 3ULL, 3ULL); // 3rd Mar of year 2.
	
	assert(timestamp(datestampReceived, 0ULL, 0L, 0ULL) == 365ULL * DAY + 31ULL * DAY + 28ULL * DAY + 2ULL * DAY); // Will give you the time 00:00:00 hh:mm:ss for the 3rd Mar of year 2.
	puts("OK");
	assert(timestamp(datestampReceived, 23ULL, 59L, 59ULL) == 365ULL * DAY + 31ULL * DAY + 28ULL * DAY + 2ULL * DAY + 23ULL * HOUR + 59ULL * MINUTE + 59ULL * SEC); // Will give you the time 23:59:59 hh:mm:ss for the 3rd Mar of year 2.
	puts("OK");

	// Choose a different year and so on..
	datestampReceived = datestamp(4ULL, 11ULL, 5ULL); // 5th Nov of year 4.
	
	assert(timestamp(datestampReceived, 23ULL, 59ULL, 59ULL) == (3ULL * 365ULL * DAY + (366ULL - 31ULL - 30ULL) * DAY + 4ULL * DAY + SEC * 59ULL + MINUTE * 59ULL + HOUR * 23ULL)); // Will give you the time 23:59:59 hh:mm:ss for the 5th Nov of year 4.
	puts("OK");
}

void test()
{
	test_isLeapYear();
	test_monthToDays();
	test_yearToDays();
	test_datestamp();
	test_timestamp();
}