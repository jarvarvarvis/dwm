#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

typedef struct {
	int updatedelay;
} dwmsb_info;

void parse_args(dwmsb_info *info, int argc, char **argv) {
	opterr = 0;
	int c;

	while ((c = getopt (argc, argv, "hd:")) != -1) {
		switch (c) {
		case 'd':
			info->updatedelay = atoi(optarg);
			break;
		case 'h':
			printf("Call: dmwsb [Options]\n");
			printf("Options:\n");
			printf("  -h         Shows this help message\n");
			printf("  -d         The update delay (in seconds)\n");
			printf("\n");
			exit(1);
			break;
		case '?':
			if (optopt == 'd')
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			else
				fprintf(stderr, "Unknown option '%c'.\n", optopt);
			exit(1);
			break;
		default:
			exit(1);
			break;
		}
	}

	// Minimum delay is 1
	if (info->updatedelay == 0) {
		info->updatedelay = 1;
	}
}

int main(int argc, char **argv) {
	dwmsb_info info;
	parse_args(&info, argc, argv);

	while (1) {
		char command[50];
		memset(command, 50, 0);

		// Get current time
		time_t current_time = time(NULL);
		char *time_str = ctime(&current_time);
		int time_str_len = strlen(time_str);
		
		// Overwrite whitespace by copying to new buffer
		char fmt_time_str[time_str_len - 1];
		strncpy(fmt_time_str, time_str, time_str_len - 1);
		fmt_time_str[time_str_len - 1] = '\0';

		// Format command
		sprintf(command, "xsetroot -name \"%s\"", fmt_time_str);
		printf("%s\n", command);

		// Send command
		system(command);

		// Wait for the specified amount of seconds
		sleep(info.updatedelay);
	}
}
