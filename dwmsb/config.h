#include <time.h>
#include <sys/sysinfo.h>

char *datecmd() 
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char *s = malloc(sizeof(char) * 64);
	strftime(s, sizeof(char) * 64, "%c", tm);
	return s;
}

char *memcmd()
{
	// Get sysinfo
	struct sysinfo info;
	sysinfo(&info);

	// Create string
	unsigned long totalram = info.totalram;
	unsigned long freeram  = info.freeram;
	unsigned long usedram  = totalram - freeram;

	char *s = malloc(sizeof(char) * 64);
	sprintf(s, "%ld / %ld", usedram, totalram);
	return s;
}

/* Definitions of blocks */
static const Block blocks[] =
{
	{ "Date: ", &datecmd },
	{ "Mem: ",  &memcmd  }
};

/* The update interval in seconds */
static int interval = 5;

/* Block separator */
static char *separator = " | ";
