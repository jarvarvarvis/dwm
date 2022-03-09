#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/sysinfo.h>

#ifdef MODULE_BATTERY
char *batcmd()
{
	#define PERCENTAGE_BUFSIZE 16
	#define STATE_BUFSIZE 16
	char percentage[PERCENTAGE_BUFSIZE];
	char state[STATE_BUFSIZE];

	/* Open the command for reading. */
	// Get battery percentage
	const char *pcmd = "upower -i $(upower -e | grep 'BAT') | awk '/percentage/ { print $2 }'";
	FILE *pcmdfp;
	if ((pcmdfp = popen(pcmd, "r")) == NULL)
	{
		fprintf(stderr, "Error opening pipe!\n");
		exit(-1);
	}
	assert(fgets(percentage, PERCENTAGE_BUFSIZE, pcmdfp) != NULL);
	percentage[strlen(percentage) - 1] = 0;
	pclose(pcmdfp);

	// Get battery state
	const char *scmd = "upower -i $(upower -e | grep 'BAT') | awk '/state/ { print $2 }'";
	FILE *scmdfp;
	if ((scmdfp = popen(scmd, "r")) == NULL)
	{
		fprintf(stderr, "Error opening pipe!\n");
		exit(-1);
	}
	assert(fgets(state, STATE_BUFSIZE, scmdfp) != NULL);
	state[strlen(state) - 1] = 0;
	pclose(scmdfp);

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
