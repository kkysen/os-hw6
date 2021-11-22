#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>
#include <limits.h>

#ifndef SCHED_FREEZER
#define SCHED_FREEZER 7
#endif

/**
 * Have not tested for with freezer since freezer implementation is not complete
 * but works for other sched policies when run with sudo (can we fix that?)
 */
int main(const int argc, const char *const *const argv)
{
	if (argc != 2) {
		fprintf(stderr, "incorrect usage: %s <pid>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char *endptr;
	const long pid_long = strtol(argv[1], &endptr, 0);

	if (endptr[0] != 0
		|| pid_long == LONG_MIN
		|| pid_long == LONG_MAX
		|| pid_long < 0) {
		fprintf(stderr, "invalid pid: %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	const pid_t pid = (pid_t) pid_long;
	const struct sched_param sp = {
		.sched_priority = 0,
	};

	if ((sched_setscheduler(pid, SCHED_FREEZER, &sp)) == -1) {
		perror("error in sched_setscheduler");
		return EXIT_FAILURE;
	}
	printf("policy set to freezer for process %d\n", pid);
	return EXIT_SUCCESS;
}
