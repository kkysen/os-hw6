# hw6

## Authors
Khyber Sen, ks3343
Aliza Rabinovitz, ajr2252
Isabelle Arevalo, ia2422

## Instructions

This file should contain:

- Your name & UNI (or those of all group members for group assignments)
- Homework assignment number
- Description for each part

The description should indicate whether your solution for the part is working
or not. You may also want to include anything else you would like to
communicate to the grader, such as extra functionality you implemented or how
you tried to fix your non-working code.

## Part Descriptions

### Part 1
Part 1 is completed with the answers filled out.

### Part 2
Part 2 is completed with explanations that our kernel is working.

### Part 3
Part 3 is completed with the answers filled out.

### Part 4
Part 4 is completed with the results of our experiment and the original kernel builds.

### Part 5
Answered the questions about jiffies and HZ.

### Part 6
Completed part 6. We added the functions in kernel/sched/freezer.c and included the data
structures in multiple files, including adding some header files and editing sched.h.

### Part 7
We implemented the functions in `freezer.c`. Some of these functions do
not do anything because freezer is a round-robin and we are not reassigning cpus. Our
script works to change our processes to the freezer scheduler.

To set a process's scheduling policy to `SCHED_FREEZER`,
we ran this program as the process to set to freezer:
```shell
❯ bash -c 'while true; do date; sleep 1; done'
Sun 21 Nov 2021 04:02:08 PM EST
Sun 21 Nov 2021 04:02:09 PM EST
Sun 21 Nov 2021 04:02:10 PM EST
...
```
Then we ran this to set it to freezer:
```shell
❯ ps aux | rg bash
khyber       787  0.0  0.1  10332  7292 pts/0    Ss   15:57   0:00 -bash
khyber       911  0.5  0.1  10704  7672 pts/1    Ss   16:00   0:00 -bash
khyber      1397  0.2  0.0   6896  3540 pts/1    S+   16:02   0:00 bash -c while true; do date; sleep 1; done
khyber      1426  0.0  0.1   8536  5760 pts/0    S+   16:02   0:00 rg bash

❯ ./user/test/set-freezer/set-freezer 1397
policy set to freezer for process 1397

❯ ps -e --forest -o sched,policy,psr,pcpu,c,pid,user,cmd
SCH POL PSR %CPU  C     PID USER     CMD
...
  7 #7    0  0.3  0    1397 khyber    |           \_ bash -c while true; do date; sleep 1;
  7 #7    0  0.9  0    1818 khyber    |               \_ bash -c while true; do date; sleep 1;
...
```

After setting the scheduler to freezer,
the sleep and date loop kept going, but much slower.
Setting CPU bound processes to use freezer, like `yes > /dev/null`, also worked.

### Part 8
We changed the `init_task.c`, `kthread.c`, and `core.c` files to reflect that
`SCHED_FREEZER` is now the default scheduler instead of `SCHED_NORMAL`.
To test both parts 7 and 8 we ran ps commands to see the schedulers of programs
that were regular programs as well as that forked into multiple processes.
We also had print statements to check the functions that were running to
verify the round robin functionality. We were not able to complete any
further/more intricate testing.
