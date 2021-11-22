/* Disable for the includes. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "sched.h"

#pragma GCC diagnostic pop

void __init init_sched_freezer_class(void)
{
	BUG();
}

void init_freezer_rq(struct freezer_rq *freezer_rq __always_unused)
{
	BUG();
}

void print_freezer_stats(struct seq_file *m __always_unused,
			 int cpu __always_unused)
{
	BUG();
}

void print_freezer_rq(struct seq_file *m __always_unused,
		      int cpu __always_unused,
		      struct freezer_rq *freezer_rq __always_unused)
{
	BUG();
}

static void enqueue_task_freezer(struct rq *rq __always_unused,
				 struct task_struct *p __always_unused,
				 int flags __always_unused)
{
	BUG();
}

static void dequeue_task_freezer(struct rq *rq __always_unused,
				 struct task_struct *p __always_unused,
				 int flags __always_unused)
{
	BUG();
}

static void yield_task_freezer(struct rq *rq __always_unused)
{
	BUG();
}

static bool yield_to_task_freezer(struct rq *rq __always_unused,
				  struct task_struct *p __always_unused)
{
	BUG();
	return false;
}

static void check_preempt_curr_freezer(struct rq *rq __always_unused,
				       struct task_struct *p __always_unused,
				       int flags __always_unused)
{
	BUG();
}

static struct task_struct *pick_next_task_freezer(struct rq *rq __always_unused)
{
	BUG();
	return NULL;
}

static void put_prev_task_freezer(struct rq *rq __always_unused,
				  struct task_struct *p __always_unused)
{
	BUG();
}

static void set_next_task_freezer(struct rq *rq __always_unused,
				  struct task_struct *p __always_unused,
				  bool first __always_unused)
{
	BUG();
}

#ifdef CONFIG_SMP

static int balance_freezer(struct rq *rq __always_unused,
			   struct task_struct *prev __always_unused,
			   struct rq_flags *rf __always_unused)
{
	BUG();
	return 0;
}

static int select_task_rq_freezer(struct task_struct *p __always_unused,
				  int task_cpu __always_unused,
				  int sd_flag __always_unused,
				  int flags __always_unused)
{
	BUG();
	return 0;
}

static void migrate_task_rq_freezer(struct task_struct *p __always_unused,
				    int new_cpu __always_unused)
{
	BUG();
}

static void task_woken_freezer(struct rq *this_rq __always_unused,
			       struct task_struct *task __always_unused)
{
	BUG();
}

static void
set_cpus_allowed_freezer(struct task_struct *p __always_unused,
			 const struct cpumask *newmask __always_unused)
{
	BUG();
}

static void rq_online_freezer(struct rq *rq __always_unused)
{
	BUG();
}

static void rq_offline_freezer(struct rq *rq __always_unused)
{
	BUG();
}

#endif

static void task_tick_freezer(struct rq *rq __always_unused,
			      struct task_struct *p __always_unused,
			      int queued __always_unused)
{
	BUG();
}

static void task_fork_freezer(struct task_struct *p __always_unused)
{
	BUG();
}

static void task_dead_freezer(struct task_struct *p __always_unused)
{
	BUG();
}

static void switched_from_freezer(struct rq *this_rq __always_unused,
				  struct task_struct *task __always_unused)
{
	BUG();
}

static void switched_to_freezer(struct rq *this_rq __always_unused,
				struct task_struct *task __always_unused)
{
	BUG();
}

static void prio_changed_freezer(struct rq *this_rq __always_unused,
				 struct task_struct *task __always_unused,
				 int oldprio __always_unused)
{
	BUG();
}

static unsigned int
get_rr_interval_freezer(struct rq *rq __always_unused,
			struct task_struct *task __always_unused)
{
	BUG();
	return 0;
}

static void update_curr_freezer(struct rq *rq __always_unused)
{
	BUG();
}

#ifdef CONFIG_FAIR_GROUP_SCHED

static void task_change_group_freezer(struct task_struct *p __always_unused,
				      int type __always_unused)
{
	BUG();
}

#endif

const struct sched_class freezer_sched_class = {
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
