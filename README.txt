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
TODO

### Part 7

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

### Part 8
TODO
