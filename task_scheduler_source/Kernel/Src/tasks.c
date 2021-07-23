#include "led.h"
#include "systick.h"
#include "uart_drivers.h"
#include "spi_drivers.h"

void idle_task(void)
{
	while(1);
}


void task1_handler(void)
{
	while(1)
	{
		uint8_t spi_rx_data[] = "sp\n\r";
		SPI1_Transmit(spi_rx_data);

		uint8_t num[] = "taskOne\n\r";
		uputs(num);

		uint8_t receive_buffer[12];
 		SPI1_Receive(receive_buffer, 12);
		task_delay(10);
//		uputs(receive_buffer);
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
		uint8_t num[] = "taskTwo\n\r";
		uputs(num);
		led_on(LED_ORANGE);
		task_delay(6000);
		led_off(LED_ORANGE);
		task_delay(6000);
	}

}

void task3_handler(void)
{
	while(1)
	{
		uint8_t num[] = "taskThree\n\r";
		uputs(num);
		led_on(LED_BLUE);
		task_delay(45000);
		led_off(LED_BLUE);
		task_delay(45000);
	}

}

void task4_handler(void)
{
	while(1)
	{
		uint8_t num[] = "taskFour\n\r";
		uputs(num);
		led_on(LED_RED);
		task_delay(32500);
		led_off(LED_RED);
		task_delay(32500);
	}
}

