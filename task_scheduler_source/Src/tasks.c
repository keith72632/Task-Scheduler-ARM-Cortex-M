#include "led.h"
#include "systick.h"
#include "uart.h"

void idle_task(void)
{
	while(1);
}


void task1_handler(void)
{
	while(1)
	{
		uputs("Task One\n");
		led_on(LED_GREEN);
		task_delay(2000);
		led_off(LED_GREEN);
		task_delay(2000);
	}

}

void task2_handler(void)
{
	while(1)
	{
		uputs("Task Two\n");
		led_on(LED_ORANGE);
		task_delay(600);
		led_off(LED_ORANGE);
		task_delay(600);
	}

}

void task3_handler(void)
{
	while(1)
	{
		uputs("Task Three\n");
		led_on(LED_BLUE);
		task_delay(450);
		led_off(LED_BLUE);
		task_delay(450);
	}

}

void task4_handler(void)
{
	while(1)
	{
		uputs("Task Four\n");
		led_on(LED_RED);
		task_delay(325);
		led_off(LED_RED);
		task_delay(325);
	}
}

