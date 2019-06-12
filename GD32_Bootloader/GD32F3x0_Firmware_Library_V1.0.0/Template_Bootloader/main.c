/*!
    \file  main.c
    \brief led spark with systick, USART print and key example
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-06-06, V1.0.0, firmware for GD32F3x0
*/

#include "gd32f3x0.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"
#include "gd32f3x0_eval.h"
#include "JumpToCode.h"

#include "ff.h"
#include "diskio.h"

static FIL mfdir;
static FATFS mfs;

int main(void)
{
    unsigned char _u08Cnt = 0;

    memset(&mfdir, 0, sizeof(FIL));
    memset(&mfs, 0, sizeof(FATFS));

    gd_eval_com_init(EVAL_COM1);
    /* configure systick */
    systick_config();
	
	disk_initialize(DEV_MMC);

    printf("\r\nCK_SYS is %d", rcu_clock_freq_get(CK_SYS));
    printf("\r\nCK_AHB is %d", rcu_clock_freq_get(CK_AHB));
    printf("\r\nCK_APB1 is %d", rcu_clock_freq_get(CK_APB1));
    printf("\r\nCK_APB2 is %d", rcu_clock_freq_get(CK_APB2));

    printf("\r\nCK_SYS is %d", SystemCoreClock);



     while (1){
        printf("    Wait %d Sec! \n", _u08Cnt++);
        // Iap_Load_App(AppAddress);
        delay_1ms(100);

    }
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM1, (uint8_t)ch);
    while(RESET == usart_flag_get(EVAL_COM1, USART_FLAG_TBE));

    return ch;
}
