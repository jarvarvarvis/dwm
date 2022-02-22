// Modify this file to change what commands output to your statusbar, and recompile using the make command.

// Got this from here: https://www.baeldung.com/linux/get-cpu-usage 
#define cpucmd  "top -bn2 | grep '%Cpu' | tail -1 | grep -P '(....|...) id,' | awk '{print 100 - $8 \"%\"}'"
#define memcmd  "free --si -h | awk '/Mem/ { print $3 \" / \" $2 }'"
#define datecmd "date '+%a %d.%m.%y %T'"

static const Block blocks[] = {
	/*Icon*/    /*Command*/  /*Update Interval*/  /*Update Signal*/
	{"CPU: ",   cpucmd,      10,                  0  },
	{"Mem: ",   memcmd,      10,                  0  },
	{"Date: ",  datecmd,     5,                   0  },
};

// Sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
