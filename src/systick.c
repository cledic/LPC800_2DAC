#include "systick.h"                        /* LPC8xx definitions */

#define SYSTICK_DELAY		(SystemCoreClock/100)

volatile uint32_t TimeTick = 0;

/* SysTick interrupt happens every 10 ms */
void SysTick_Handler(void)
{
  TimeTick++;
}

void SysTick_Init( void)
{

  /* Called for system library in core_cmx.h(x=0 or 3). */
  SysTick_Config( SYSTICK_DELAY );

}

uint32_t getTimerTick( void)
{
	return TimeTick;
}

uint32_t getTimerTickDiff( uint32_t t)
{
	return (TimeTick - t);
}

#if 0
void delaySysTick(uint32_t tick)
{
  uint32_t timetick;

  /* Clear SysTick Counter */
  SysTick->VAL = 0;
  /* Enable the SysTick Counter */
  SysTick->CTRL |= (0x1<<0);

  timetick = TimeTick;
  while ((TimeTick - timetick) < tick);

  /* Disable SysTick Counter */
  SysTick->CTRL &= ~(0x1<<0);
  /* Clear SysTick Counter */
  SysTick->VAL = 0;
  return;
}
#endif
