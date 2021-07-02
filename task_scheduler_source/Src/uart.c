/*
 * uart.c
 *
 *  Created on: Jun 30, 2021
 *      Author: keith
 */

#include <stdint.h>

uint32_t *pAhb1 = (uint32_t *)0x40023830;
uint32_t *pApb  = (uint32_t *)0x40023840;
uint32_t *pAMode = (uint32_t *)0x40020000;
uint32_t *AltFunc = (uint32_t *)0x40020020;
uint32_t *pUsart_Sr = (uint32_t *)0x40004400;
uint32_t *pUsart_Dr = (uint32_t *)0x40004404;
uint32_t *pUsart_Brr = (uint32_t *)0x40004408;
uint32_t *pUsart_Cr1 = (uint32_t *)0x4000440C;


void usart_init()
{
    *pAhb1 |= (1 << 0);
    *pApb  |= (1 << 17);
    *pAMode |= (2 << 4) | (2 << 6);
    *AltFunc |= (7 << 8) | (7 << 12);

    /* baudrate calculation: 16,000,000/(16 * 9600) = 104.1667
     * Mantissa = 68
     * Decimal = 0.1667 * 16 = 3
     * Brr value = 0x683
     */
    *pUsart_Brr = 0x0683;
    *pUsart_Cr1 |= (1 << 3) | (1 << 13);
}

void usart_write(uint8_t c)
{
    while(!(*pUsart_Sr & 0x0080)){};
    *pUsart_Dr = c;
}

void uputs(char s[])
{
    for(int i = 0; s[i] != '\0'; i++)
    {
        usart_write(s[i]);
    }
    while(!(*pUsart_Sr & 0x0040)){};
}
