/* Disable for the includes. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "sched.h"

#pragma GCC diagnostic pop

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

void __init init_sched_freezer_class(void)
{
	todo();
}

void init_freezer_rq(struct freezer_rq *fr_rq)
{
	fr_rq->nr_running = 0;
	INIT_LIST_HEAD(&fr_rq->sched_entities);
	spin_lock_init(&fr_rq->lock);
	fr_rq->runtime = 0;
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

static void enqueue_task_freezer(struct rq *rq,
				 struct task_struct *p,
				 int flags __always_unused)
{
	/* run_list should always be initialized */
	list_add_tail(&p->freezer.run_list, &rq->freezer.sched_entities);
	rq->freezer.nr_running++;
}

static void dequeue_task_freezer(struct rq *rq,
				 struct task_struct *p,
				 int flags __always_unused)
{
	list_del_init(&p->freezer.run_list);
	rq->freezer.nr_running--;
}

static void yield_task_freezer(struct rq *rq)
{
	/* move to end, aka move to next in a circular list */
	list_rotate_left(&rq->freezer.sched_entities);
}

static bool yield_to_task_freezer(struct rq *rq,
				  struct task_struct *p)
{
	todo();
	yield_task_freezer(rq);
	return true;
}

static void check_preempt_curr_freezer(struct rq *rq __always_unused,
				       struct task_struct *p __always_unused,
				       int flags __always_unused)
{
	if(p->sched_class == rq->curr->sched_class)
		rq->curr->sched_class->check_preempt_curr_freezer(rq, p, flags);
	else if(p->sched_class > rq->curr->sched_class)
		resched_curr(rq);
	
}

static bool sched_rt_runnable(struct rq *rq)
{
	return rq->freezer.nr_running > 0;
}

static struct task_struct *freezer_task_of(struct sched_freezer_entity *fr_se)
{
	return container_of(fr_se, struct task_struct, freezer);
}

static struct task_struct *freezer_rq_curr_task(struct rq *rq) {
	struct freezer_rq *fr_rq;
	struct freezer_sched_entity *fr_se;

	if (!sched_rt_runnable(rq))
		return NULL;
	fr_rq = &rq->freezer;
	fr_se = list_first_entry(&fr_rq->sched_entities, typeof(*fr_se), run_list);
	return freezer_task_of(fr_se);
}

static struct task_struct *pick_next_task_freezer(struct rq *rq)
{
	return freezer_rq_curr_task(rq);
}

static void put_prev_task_freezer(struct rq *rq __always_unused,
				  struct task_struct *prev __always_unused)
{
	struct sched_freezer_entity *se = &prev->se;
	struct freezer_rq *freezer_rq;

	for(; se; se=se->parent){
		freezer_rq = container_of(freezer_rq, struct rq, freezer);
		put_prev_entity_freezer(freezer_rq, se);
	}
}

static void put_prev_entity_freezer(struct freezer_rq *freezer_rq,
					struct sched_freezer_entity *prev){

	u64 wait_start, prev_wait_start;

	if(prev->on_rq){
		update_curr_freezer(freezer_rq);
	}
	if(prev->on_rq){
		if(sched_stat_enabled()){
			wait_start = rq_clock(container_of(freezer_rq, struct rq, freezer));
			prev_wait_start = schedstat_val(prev->statistics.wait_start);
			__schedstat_set(se->statistics.wait_start, wait_start);
		}
		list_add_tail(&prev->freezer.run_list, &rq->freezer.sched_entities);
		rq->freezer.nr_running++;
	}
	freezer_rq->curr = NULL;
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
	/* not reassigning */
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
	todo();
}

static void task_woken_freezer(struct rq *this_rq __always_unused,
			       struct task_struct *task __always_unused)
{
	todo();
}

static void
set_cpus_allowed_freezer(struct task_struct *p,
			 const struct cpumask *newmask)
{
	set_cpus_allowed_common(p, newmask);
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
	/* nothing to do */
}

static void task_dead_freezer(struct task_struct *p __always_unused)
{
	/* nothing to do */
}

static void switched_from_freezer(struct rq *this_rq __always_unused,
				  struct task_struct *task __always_unused)
{
	/* nothing to do */
}

static void switched_to_freezer(struct rq *this_rq __always_unused,
				struct task_struct *task __always_unused)
{
	if(task_on_rq_queued(task)){
		if(task_current(rq, task){
			resched_curr(rq);
		else{
			check_preempt_curr_freezer(rq, task, 0);
		}
	}
}

static void prio_changed_freezer(struct rq *this_rq __always_unused,
				 struct task_struct *task __always_unused,
				 int oldprio __always_unused)
{
	return; /* Round Robin */
}

static unsigned int
get_rr_interval_freezer(struct rq *rq __always_unused,
			struct task_struct *task __always_unused)
{
	if(task->policy == SCHED_FREEZER){
		return FREEZER_TIMESLICE;
	}
	return 0;
}

static void update_curr_freezer(struct rq *rq)
{
	struct freezer_rq *fr_rq = &rq->freezer;
	struct sched_freezer_entity *curr = freezer_rq_curr_task(rq);
	struct task_struct *curr_task = freezer_task_of(curr);

	if (curr->sched_class != &freezer_sched_class)
		return;
	u64 now = rq_clock_task(rq);
	u64 delta_exec;
	delta_exec = now - curr->se.exec_start;
	if (unlikely(delta_exec <= 0)) {
		return;
	}
	schedstat_set(curr->se.statistics.exec_max, max(curr->se.statistics.exec_max, delta_exec));
	curr->se.sum_exec_runtime += delta_exec;
	curr->se.exec_start = now;
	fr_rq->time += delta_exec;
	if (fr_rq->time > FREEZER_TIMESLICE) {
		resched_curr(curr);
	}
}

#ifdef CONFIG_FAIR_GROUP_SCHED

static void task_change_group_freezer(struct task_struct *p __always_unused,
				      int type __always_unused)
{
	/* we don't have groups */
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
