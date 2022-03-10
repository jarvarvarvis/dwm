#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/sysinfo.h>

void tryreadcmd(const char *cmd, char *buffer, const int buffersize)
{
	FILE *cmdfp;
	if ((cmdfp = popen(cmd, "r")) == NULL)
	{
		fprintf(stderr, "Error opening pipe!\n");
		exit(-1);
	}
	assert(fgets(buffer, buffersize, cmdfp) != NULL);
	buffer[strlen(buffer) - 1] = 0;
	pclose(cmdfp);
}

#ifdef MODULE_BATTERY
char *batcmd()
{
	// Get battery percentage
	#define PERCENTAGE_BUFSIZE 16
	char percentage[PERCENTAGE_BUFSIZE];
	const char *pcmd = "upower -i $(upower -e | grep 'BAT') | awk '/percentage/ { print $2 }'";
	tryreadcmd(pcmd, percentage, PERCENTAGE_BUFSIZE);

	// Get battery state
	#define STATE_BUFSIZE 16
	char state[STATE_BUFSIZE];
	const char *scmd = "upower -i $(upower -e | grep 'BAT') | awk '/state/ { print $2 }'";
	tryreadcmd(scmd, state, STATE_BUFSIZE);

	char *s = (char *) malloc(sizeof(char) * (PERCENTAGE_BUFSIZE + STATE_BUFSIZE + 4));
	sprintf(s, "%s (%s)", percentage, state);

	return s;
}
#endif

#ifdef MODULE_DATE
char *datecmd() 
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	char *s = (char *) malloc(sizeof(char) * 64);
	strftime(s, sizeof(char) * 64, "%c", tm);
	return s;
}
#endif

/* Definitions of blocks */
static const Block blocks[] =
{
#ifdef MODULE_BATTERY
        { "Battery: ",  &batcmd  },
#endif
#ifdef MODULE_DATE
	{ "Date: ",     &datecmd },
#endif
};

/* The update interval in seconds */
static int interval = 5;

/* Block separator */
static char *separator = " | ";
