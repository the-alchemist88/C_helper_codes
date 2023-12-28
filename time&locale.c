#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <locale.h>

#define BUFF_SIZE 100

int main()
{
	// time_t (terms: epoch, calender time, time point, duration, broken-down time)
	time_t t;

	time(&t);

	printf("time elapsed since epoch in seconds: %lld\n\n", time(&t));

	struct tm* stm = localtime(&t); // there are two functions to convert time_t into struct tm --> localtime and gmtime

	char str[BUFF_SIZE];
	size_t len = strftime(str, BUFF_SIZE, "%d %B %A %Y\n", stm); // search for strftime for more formatting options

	printf("strftime string: %s", str);
	printf("string length  : %zu", len);

	puts("\n");

	stm = gmtime(&t); // set stm by t as GMT

	const char* p = asctime(stm); // asctime and ctime both set the same global pointer

	printf("UTC time  : %s", p);

	p = ctime(&t); // sets time as local time

	printf("local time: %s", p);

	t = 0;
	stm = gmtime(&t);
	p = asctime(stm);
	printf("epoch     : %s", p);

	puts("\n");

	/****************************************************************************************************************************/

	// locale(there are specific locals for various categories, LC_ALL includes them all)
	double dval = 123.5498;
	printf("C locale format for floating point number = %03f\n", dval);

	const char* ret = setlocale(LC_ALL, "turkish");

	if (!ret)
		puts("locale couldn't be set\n");
	else
		puts("locale is successfully set\n");

	t = time(NULL);
	stm = localtime(&t);
	strftime(str, BUFF_SIZE, "%d %B %A %Y\n", stm);

	printf("Turkish locale format for floating point number = %03f\n", dval);
	puts(str);
}

