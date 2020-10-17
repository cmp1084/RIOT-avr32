#include <stdio.h>

#include "cpu_conf.h"
#include "irq_arch.h"
#include "stdatomic.h"
#include "cond.h"
#include "thread.h"
#include "/home/marcus/avr32/code/RIOT/drivers/include/periph/timer.h"

void cpu_init(void);

void pm_reboot(void);
void thread_yield_higher(void);
char* thread_stack_init(thread_task_func_t task_func, void *arg, void *stack_start, int stack_size);
void cpu_switch_context_exit(void);

atomic_int_least16_t atomic_load_explicit(atomic_int_least16_t * ptr, const int mo);
void atomic_store_explicit(atomic_int_least16_t * ptr, atomic_int_least16_t val, const int mo);
