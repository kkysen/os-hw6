#ifndef _LINUX_SCHED_FREEZER_H
#define _LINUX_SCHED_FREEZER_H

#include <linux/sched.h>

#define FREEZER_TIMESLICE (100 * HZ / 1000)

extern void init_sched_freezer_entity(struct sched_freezer_entity *freezer_se);

#endif /* _LINUX_SCHED_FREEZER_H */
