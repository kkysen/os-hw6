#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/hash.h>
#include <linux/wait.h>
#include <linux/sched/signal.h>
#include <linux/time.h>

#define MODULE_NAME "quickTimer"

int quicktimer_init(void)
{
    u64 jiffies_num;
    clock_t new_jiffies;
    jiffies_num = get_jiffies_64();
    new_jiffies = jiffies_64_to_clock_t(jiffies_num);

	pr_info("%d", USER_HZ);
    pr_info("%lu", jiffies);
    pr_info("%lu", jiffies_num);
    pr_info("new hz %d", HZ);
    pr_info("jiffies? %lu", new_jiffies);
    pr_info("Initial jiffies %lu", INITIAL_JIFFIES);

	return 0;
}

void quicktimer_exit(void)
{
	printk(KERN_INFO "Removing Module\n");

}

module_init( quicktimer_init );
module_exit( quicktimer_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("quick timer for hz");
MODULE_AUTHOR("fireferrises");
