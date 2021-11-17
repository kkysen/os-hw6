/* SCHED_FREEZER must be defined to be 7 */
  #define  SCHED_FREEZER  7

  /*
   * define FREEZER_TIMESLICE so that every task receives
   * a time slice of 100 milliseconds
   */
  #define  FREEZER_TIMESLICE  <the-right-timeslice-value>

  /* freezer run queue and entity */
  struct freezer_rq;
  struct sched_freezer_entity;