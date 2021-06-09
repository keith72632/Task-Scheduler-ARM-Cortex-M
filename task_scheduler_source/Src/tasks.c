#include "led.h"
#include "systick.h"

void idle_task(void)
{
	while(1);
}


void task1_handler(void)
{
	while(1)
	{
		led_on(LED_GREEN);
		task_delay(1000);
		led_off(LED_GREEN);
		task_delay(1000);
	}

}

void task2_handler(void)
{
	while(1)
	{
		led_on(LED_ORANGE);
		task_delay(500);
		led_off(LED_ORANGE);
		task_delay(500);
	}

}

void task3_handler(void)
{
	while(1)
	{
		led_on(LED_BLUE);
		task_delay(250);
		led_off(LED_BLUE);
		task_delay(250);
	}

}

void task4_handler(void)
{
	while(1)
	{
		led_on(LED_RED);
		task_delay(125);
		led_off(LED_RED);
		task_delay(125);
	}
}

