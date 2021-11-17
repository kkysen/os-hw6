#include "sched.h"

#define todo_message(message)                                                  \
	pr_err("TODO%s%s at %s:%d:%s\n", message[0] == 0 ? "" : ": ", message, \
	       __FILE__, __LINE__, __func__)

#define todo() todo_message("")

/**
 * See `include/linux/sched/rt.h:65`.
 * 100 milliseconds.
 * Should this be in a header file like `rt.h`.
 */
#define FREEZER_TIMESLICE (100 * HZ / 1000)

static void enqueue_task_freezer(struct rq *rq, struct task_struct *p,
				 int flags)
{
	todo();
}

static void dequeue_task_freezer(struct rq *rq, struct task_struct *p,
				 int flags)
{
	todo();
}

static void yield_task_freezer(struct rq *rq)
{
	todo();
}

static bool yield_to_task_freezer(struct rq *rq, struct task_struct *p)
{
	todo();
	return false;
}

static void check_preempt_curr_freezer(struct rq *rq, struct task_struct *p,
				       int flags)
{
	todo();
}

static struct task_struct *pick_next_task_freezer(struct rq *rq)
{
	todo();
	return NULL;
}

static void put_prev_task_freezer(struct rq *rq, struct task_struct *p)
{
	todo();
}

static void set_next_task_freezer(struct rq *rq, struct task_struct *p,
				  bool first)
{
	todo();
}

#ifdef CONFIG_SMP

static int balance_freezer(struct rq *rq, struct task_struct *prev,
			   struct rq_flags *rf)
{
	todo();
	return 0;
}

static int select_task_rq_freezer(struct task_struct *p, int task_cpu,
				  int sd_flag, int flags)
{
	todo();
	return 0;
}

static void migrate_task_rq_freezer(struct task_struct *p, int new_cpu)
{
	todo();
}

static void task_woken_freezer(struct rq *this_rq, struct task_struct *task)
{
	todo();
}

static void set_cpus_allowed_freezer(struct task_struct *p,
				     const struct cpumask *newmask)
{
	todo();
}

static void rq_online_freezer(struct rq *rq)
{
	todo();
}

static void rq_offline_freezer(struct rq *rq)
{
	todo();
}

#endif

static void task_tick_freezer(struct rq *rq, struct task_struct *p, int queued)
{
	todo();
}

static void task_fork_freezer(struct task_struct *p)
{
	todo();
}

static void task_dead_freezer(struct task_struct *p)
{
	todo();
}

static void switched_from_freezer(struct rq *this_rq, struct task_struct *task)
{
	todo();
}

static void switched_to_freezer(struct rq *this_rq, struct task_struct *task)
{
	todo();
}

static void prio_changed_freezer(struct rq *this_rq, struct task_struct *task,
				 int oldprio)
{
	todo();
}

static unsigned int get_rr_interval_freezer(struct rq *rq,
					    struct task_struct *task)
{
	todo();
	return 0;
}

static void update_curr_freezer(struct rq *rq)
{
	todo();
}

#ifdef CONFIG_FAIR_GROUP_SCHED

static void *task_change_group_freezer(struct task_struct *p, int type)
{
	todo();
}

#endif

const struct sched_class freezer_sched_class __section(
	"__freezer_sched_class") = {
	.enqueue_task = enqueue_task_freezer, /* idle didn't use this */
	.dequeue_task = dequeue_task_freezer,
	.yield_task = yield_task_freezer, /* idle didn't use this */
	.yield_to_task = yield_to_task_freezer, /* deadline didn't use this */

	.check_preempt_curr = check_preempt_curr_freezer,

	.pick_next_task = pick_next_task_freezer,
	.put_prev_task = put_prev_task_freezer,
	.set_next_task = set_next_task_freezer,

#ifdef CONFIG_SMP
	.balance = balance_freezer,
	.select_task_rq = select_task_rq_freezer,
	.migrate_task_rq = migrate_task_rq_freezer, /* idle didn't use this */
	.set_cpus_allowed = set_cpus_allowed_freezer,
	.task_woken = task_woken_freezer, /* idle didn't use this */
	.rq_online = rq_online_freezer, /* idle didn't use this */
	.rq_offline = rq_offline_freezer, /* idle didn't use this */
#endif

	.task_tick = task_tick_freezer,
	.task_fork = task_fork_freezer, /* idle didn't use this */
	.task_dead = task_dead_freezer, /* deadline didn't use this */

	.switched_from = switched_from_freezer, /* idle didn't use this */
	.switched_to = switched_to_freezer,
	.prio_changed = prio_changed_freezer,

	.get_rr_interval =
		get_rr_interval_freezer, /* deadline didn't use this */

	.update_curr = update_curr_freezer,

#ifdef CONFIG_FAIR_GROUP_SCHED
	.task_change_group =
		task_change_group_freezer, /* deadline didn't use this */
#endif
};
