#include "led.h"
#include "systick.h"
#include "uart_drivers.h"

void idle_task(void)
{
	while(1);
}


void task1_handler(void)
{
	while(1)
	{
		uint8_t num[] = "taskOne\n";
		uputs(num);
		led_on(LED_GREEN);
		task_delay(20000);
		led_off(LED_GREEN);
		task_delay(20000);
	}

}

void task2_handler(void)
{
	while(1)
	{
		uint8_t num[] = "taskOne\n";
		uputs(num);
		task_delay(6000);
		led_off(LED_ORANGE);
		task_delay(6000);
	}

}

void task3_handler(void)
{
	while(1)
	{
		uint8_t num[] = "taskOne\n";
		uputs(num);
		task_delay(45000);
		led_off(LED_BLUE);
		task_delay(45000);
	}

}

void task4_handler(void)
{
	while(1)
	{
		uint8_t num[] = "taskOne\n";
		uputs(num);
		task_delay(32500);
		led_off(LED_RED);
		task_delay(32500);
	}
}

