#include "sched.h"
#include "freezer.h"
  /*
   * freezer scheduling policy implementation;
   * put the code in kernel/sched/freezer.c
   */
  struct sched_class freezer_sched_class;