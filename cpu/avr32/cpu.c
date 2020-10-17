#include "cpu.h"

int main(void)
{

	puts("Hello World!");

	printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
	printf("This board features a(n) %s MCU.\n", RIOT_MCU);
	while (1);
	while (1);
	return 0;
}

void cpu_init(void)
{

}

void pm_reboot(void)
{
	//WDT_enable();
	irq_disable();
	while (1);
}

//~ void cond_wait(cond_t *cond, mutex_t *mutex)
//~ {
	//~ //TODO:
	//~ (void) *cond;
	//~ (void) *mutex;
//~ }

void thread_yield_higher(void)
{

}

char* thread_stack_init(thread_task_func_t task_func, void *arg, void *stack_start, int stack_size)
{
	(void)task_func;
	(void)arg;
	(void)stack_start;
	(void)stack_size;
	return NULL;
}

/**
 * @brief Call context switching at thread exit
 *
 * This is called is two situations: 1) after the initial main and idle threads
 * have been created and 2) when a thread exits.
 *
 */
void cpu_switch_context_exit(void)
{
    /* enable interrupts */
    irq_enable();

    /* force a context switch to another thread */
    thread_yield_higher();
    UNREACHABLE();
}


/**
 * @brief Read the current value of the given timer device
 *
 * @param[in] dev           the timer to read the current value from
 *
 * @return                  the timers current value
 */
unsigned int timer_read(tim_t dev)
{
	(void)dev;
	return 0;
}

/**
 * @brief Set an absolute timeout value for the given channel of the given timer
 *
 * Timers that are less wide than `unsigned int` accept and truncate overflown
 * values.
 *
 * @param[in] dev           the timer device to set
 * @param[in] channel       the channel to set
 * @param[in] value         the absolute compare value when the callback will be
 *                          triggered
 *
 * @return                  0 on success
 * @return                  -1 on error
 */
int timer_set_absolute(tim_t dev, int channel, unsigned int value)
{
	(void)dev;
	(void)channel;
	(void)value;
	return 0;
}

atomic_int_least16_t atomic_load_explicit(atomic_int_least16_t * ptr, const int mo)
{
	atomic_int_least16_t tmp;

	(void)mo;
	irq_disable();
	tmp = *ptr;
	irq_enable();
	return tmp;
}

void atomic_store_explicit(atomic_int_least16_t * ptr, atomic_int_least16_t val, const int mo)
{
	(void) mo;
	irq_disable();
	*ptr = val;
	irq_enable();
}
