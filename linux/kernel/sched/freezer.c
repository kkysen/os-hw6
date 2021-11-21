/* Disable for the includes. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "sched.h"

#pragma GCC diagnostic pop

#define todo_message(message)                                                  \
	pr_err("TODO%s%s at %s:%d:%s\n", message[0] == 0 ? "" : ": ", message, \
	       __FILE__, __LINE__, __func__)

#define todo() todo_message("")

void __init init_sched_freezer_class(void)
{
	/* nothing to do */
}

void init_freezer_rq(struct freezer_rq *fr_rq)
{
	fr_rq->nr_running = 0;
	INIT_LIST_HEAD(&fr_rq->sched_entities);
	spin_lock_init(&fr_rq->lock);
	fr_rq->runtime = 0;
}

void init_sched_freezer_entity(struct sched_freezer_entity *fr_se)
{
	INIT_LIST_HEAD(&fr_se->run_list);
	fr_se->remaining_runtime = FREEZER_TIMESLICE;
}

void print_freezer_rq(struct seq_file *m, int cpu, struct freezer_rq *fr_rq)
{
	seq_printf(m, "freezer_rq[%d]:\n  .number processes: %zu\n", cpu,
		   fr_rq->nr_running);
}

void print_freezer_stats(struct seq_file *m, int cpu)
{
	print_freezer_rq(m, cpu, &cpu_rq(cpu)->freezer);
}

static void enqueue_task_freezer(struct rq *rq, struct task_struct *p,
				 int flags __always_unused)
{
	/* run_list should always be initialized */
	list_add_tail(&p->freezer.run_list, &rq->freezer.sched_entities);
	rq->freezer.nr_running++;
}

static void dequeue_task_freezer(struct rq *rq, struct task_struct *p,
				 int flags __always_unused)
{
	/* leave in initialized state */
	list_del_init(&p->freezer.run_list);
	rq->freezer.nr_running--;
}

static void yield_task_freezer(struct rq *rq)
{
	list_rotate_left(&rq->freezer.sched_entities);
}

static bool yield_to_task_freezer(struct rq *rq, struct task_struct *p)
{
	yield_task_freezer(rq);
	list_add(&p->freezer.run_list, &rq->freezer.sched_entities);
	rq->freezer.nr_running++;
	return true;
}

static void check_preempt_curr_freezer(struct rq *rq __always_unused,
				       struct task_struct *p __always_unused,
				       int flags __always_unused)
{
	/* don't preempt, no internal priorities w/i freezer */
}

static bool sched_freezer_runnable(struct rq *rq)
{
	return rq->freezer.nr_running > 0;
}

static struct task_struct *freezer_task_of(struct sched_freezer_entity *fr_se)
{
	return container_of(fr_se, struct task_struct, freezer);
}

// static struct task_struct *freezer_rq_curr_task(struct rq *rq) {

// }

static struct sched_freezer_entity *
pick_next_freezer_entity(struct freezer_rq *fr_rq)
{
	return list_first_entry(&fr_rq->sched_entities,
				struct sched_freezer_entity, run_list);
}

static void set_next_task_freezer(struct rq *rq, struct task_struct *p,
				  bool first __always_unused)
{
	p->se.exec_start = rq_clock_task(rq);
}

static struct task_struct *pick_next_task_freezer(struct rq *rq)
{
	struct freezer_rq *fr_rq;
	struct sched_freezer_entity *fr_se;
	struct task_struct *p;

	if (!sched_freezer_runnable(rq))
		return NULL;
	fr_rq = &rq->freezer;
	fr_se = pick_next_freezer_entity(fr_rq);
	p = freezer_task_of(fr_se);
	set_next_task_freezer(rq, p, true);
	return p;
}

static void put_prev_task_freezer(struct rq *rq, struct task_struct *prev)
{
	list_move_tail(&prev->freezer.run_list, &rq->freezer.sched_entities);
}

static void update_curr_freezer(struct rq *rq)
{
	struct freezer_rq *fr_rq;
	struct task_struct *curr;
	struct sched_entity *se;
	u64 now;
	u64 delta_exec;

	fr_rq = &rq->freezer;
	curr = rq->curr;
	se = &curr->se;

	if (curr->sched_class != &freezer_sched_class)
		return;
	now = rq_clock_task(rq);
	delta_exec = now - se->exec_start;
	if (unlikely(delta_exec <= 0))
		return;
	schedstat_set(se->statistics.exec_max,
		      max(se->statistics.exec_max, delta_exec));
	se->sum_exec_runtime += delta_exec;
	se->exec_start = now;
	fr_rq->runtime += delta_exec;
	if (fr_rq->runtime > FREEZER_TIMESLICE)
		resched_curr(rq);
}

#ifdef CONFIG_SMP

static int balance_freezer(struct rq *rq __always_unused,
			   struct task_struct *prev __always_unused,
			   struct rq_flags *rf __always_unused)
{
	/* not reassigning */
	return 0;
}

static int select_task_rq_freezer(struct task_struct *p,
				  int old_cpu __always_unused,
				  int sd_flag __always_unused,
				  int flags __always_unused)
{
	int cpu;
	int cpu_with_min_tasks;
	size_t min_tasks;

	cpu_with_min_tasks = task_cpu(p);
	min_tasks = (size_t)-1; /* max */
	for_each_possible_cpu(cpu) {
		struct rq *rq;
		size_t nr_tasks;

		rq = cpu_rq(cpu);
		nr_tasks = rq->freezer.nr_running;
		if (nr_tasks < min_tasks) {
			min_tasks = nr_tasks;
			cpu_with_min_tasks = cpu;
		}
	}
	return cpu_with_min_tasks;
}

static void migrate_task_rq_freezer(struct task_struct *p __always_unused,
				    int new_cpu __always_unused)
{
	/* to do balancing, freezer will not do this */
}

static void task_woken_freezer(struct rq *this_rq __always_unused,
			       struct task_struct *task __always_unused)
{
	/* not dealing with priority in round robin */
}

static void set_cpus_allowed_freezer(struct task_struct *p,
				     const struct cpumask *newmask)
{
	set_cpus_allowed_common(p, newmask);
}

static void rq_online_freezer(struct rq *rq __always_unused)
{
	/* nothing to do */
}

static void rq_offline_freezer(struct rq *rq __always_unused)
{
	/* nothing to do */
}

#endif

static void task_tick_freezer(struct rq *rq, struct task_struct *p,
			      int queued __always_unused)
{
	/**
	 * Called from the timer interrupt handler.
	 * `p` is the currently running task and
	 * `rq` is the runqueue that it's on.
	 * It is called whenever a timer interrupt happens,
	 * and its job is to perform bookeeping and set the run `resched_curr`
	 * if the currently-running process needs to be preempted.
	 */
	struct sched_freezer_entity *fr_se;

	fr_se = &p->freezer;
	update_curr_freezer(rq);
	if (p->policy != SCHED_FREEZER)
		return;
	if (--fr_se->remaining_runtime > 0)
		return;
	/* need to reschedule and reset its runtime for the next time now */
	fr_se->remaining_runtime = FREEZER_TIMESLICE;
	list_rotate_left(&rq->freezer.sched_entities);
	resched_curr(rq);
}

static void task_fork_freezer(struct task_struct *p __always_unused)
{
	/* nothing to do */
}

static void task_dead_freezer(struct task_struct *p __always_unused)
{
	/* nothing to do */
}

static void switched_from_freezer(struct rq *rq __always_unused,
				  struct task_struct *task __always_unused)
{
	/* nothing to do */
}

static void switched_to_freezer(struct rq *rq, struct task_struct *task)
{
	if (!task_on_rq_queued(task))
		return;
	if (task_current(rq, task))
		resched_curr(rq);
	else
		check_preempt_curr_freezer(rq, task, 0);
}

static void prio_changed_freezer(struct rq *this_rq __always_unused,
				 struct task_struct *task __always_unused,
				 int oldprio __always_unused)
{
	/* freezer doesn't have priorities */
}

static unsigned int get_rr_interval_freezer(struct rq *rq __always_unused,
					    struct task_struct *task)
{
	if (task->policy == SCHED_FREEZER)
		return FREEZER_TIMESLICE;
	return 0;
}

#ifdef CONFIG_FAIR_GROUP_SCHED

static void task_change_group_freezer(struct task_struct *p __always_unused,
				      int type __always_unused)
{
	/* we don't have groups */
}

#endif

/**
 * Not directly used but used through the section name,
 * which is why there's a `__always_unused`.
 */
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
