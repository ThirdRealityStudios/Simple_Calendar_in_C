typedef struct meeting_struct meeting;

extern void test();
extern void test_yearToDays();
extern void test_monthToDays();
extern void test_isLeapYear();
extern void test_datestamp();
extern void test_timestamp();
extern unsigned long long yearToDays(unsigned long long year);
extern unsigned long long monthToDays(unsigned long long month);
extern unsigned long long isLeapYear(unsigned long long year);
extern unsigned long long datestamp(unsigned long long year, unsigned long long month, unsigned long long day);
extern unsigned long long timestamp(unsigned long long datestamp, unsigned long long hour, unsigned long long minute, unsigned long long second);