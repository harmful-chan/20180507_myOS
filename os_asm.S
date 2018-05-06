;/* 编码   ：GB2312               */
;/* 创作者 ：harmful              */
;/* 时间   ：2018年5月6日23:35:49 */
;/*
;文件说明 ：与寄存器相关代码，实时性要求高，所以用汇编实现
;*/

AREA OS_ASM, CODE, READONLY

IMPORT OSPrioCur
IMPORT OSPrioHighRdy

;并清0总中断标志位
OSOffIrt
	mrs r0, CPSR    ;r0 = CPSR;     //(状态寄存器只能mrs msr 操作)
	orr r1, r0, #NOINT    ;r0对应总中断标志位清0，在给r1
	msr CPSR_c, r1    ;CPSR = (r1&0x000000ff);
	mov pc, lr    ;return    

;恢复总中断标志位
OSOnIrt
	msr CPSR_c, r0
	mov pc, lr    ;return

;切换任务栈
OSTaskStkCge
	stmfs sp!, {lr}    ;push 程序返回地址
	stmfd sp!, {r0-r12, lr}    ;push 全部通用寄存器
	mrs r4, cpsr
	stmfd sp!, r4    ;push CPSR
	ldr r4, r0    ;r0为传入参数
	ldr r5, [r4]
	str 

	
	

END

