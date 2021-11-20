#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>
#include "syscall.h"

#ifndef SCHED_FREEZER
#define SCHED_FREEZER 7
#endif

/*
 * Have not tested for with freezer since freezer implementation is not complete
 * but works for other sched policies when run with sudo(can we fix that?)
 */

int main(int argc, char **argv)
{
	if (argc != 2) {
		perror("Incorrect usage: ./set-freezer <pid>\n");
		return -1;
	}

	pid_t p = atoi(argv[1]);
	struct sched_param sp = { .sched_priority = 0 };

	if ((sched_setscheduler(p, SCHED_FREEZER, &sp)) < 0) {
		perror("Error in sched_setscheduler\n");
		return -1;
	}
	printf("Policy set to freezer for process %d\n", p);
	return 0;
}