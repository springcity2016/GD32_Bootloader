
#define __JUMPTOCODE_C_



#include "gd32f3x0.h"
#include "core_cm4.h"
#include "core_cmFunc.h"

typedef void (*IapFun)(void);
IapFun JumpToApp;

void Iap_Load_App(unsigned int AppAddr)
{
    if (((*(volatile unsigned int*)AppAddr) & 0x2FFE0000) == 0x20000000)   //检查栈顶地址是否合法.
    {
		// printf("Start Jump! \n");
        __disable_irq();
        nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x5000); //地址映射
        JumpToApp = (IapFun)(*(volatile unsigned int *)(AppAddr + 4));        //用户代码区第二个字为程序开始地址(新程序复位地址)
        __set_MSP(*(volatile unsigned int*)AppAddr);
		// printf("Start Jump! \n");
		JumpToApp();    //设置PC指针为新程序复位中断函数的地址，往下执行
    }
}

#undef __JUMPTOCODE_C_

