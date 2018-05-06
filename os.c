#include "os.h"

/* 全局变量声明 */
UINT32 cpu_rs = 0;    
UINT8 OSRdyTbl[8] = {0};    
UINT8 OSPrioCur = 0;    
UINT8 OSPrioHighRdy = 0;    
struct TaskCtrBlock TCB[OS_TASKS]; 
UINT8 OSRdyGrp[256] = {

};    


/*
* OS系统初始化
*/
void OSInit(void)
{

}

/*
* OS创建任务
* Task : 任务入口地址
* p_Stack : 任务栈栈底地址
* TaskID : 任务优先级
*/
void OSTaskCreate(void (*Task)(void), UINT32 *p_Stack, UINT8 TaskID)
{
	
	/* 出入栈顺序为 ： {R0-R12, LR, PC} */
	*p_Stack = (UINT32)Task;    //P15
	*(--p_Stack) = (UINT32)14;    //R14
	*(--p_Stack) = (UINT32)12;    //R12
	*(--p_Stack) = (UINT32)11;    //R11
	*(--p_Stack) = (UINT32)10;    //R10
	*(--p_Stack) = (UINT32)9;    //R9
	*(--p_Stack) = (UINT32)8;    //R8
	*(--p_Stack) = (UINT32)7;    //R7
	*(--p_Stack) = (UINT32)6;    //R6
	*(--p_Stack) = (UINT32)5;    //R5
	*(--p_Stack) = (UINT32)4;    //R4
	*(--p_Stack) = (UINT32)3;    //R3
	*(--p_Stack) = (UINT32)2;    //R2
	*(--p_Stack) = (UINT32)1;    //R1
	*(--p_Stack) = (UINT32)0;    //R0
	
	TCB[TaskID].OSTCBStkPtr = (UINT32)p_Stack;    //当前任务栈顶地址
	TCB[TaskID].OSTCBDly = 0;    //挂起延时为0

	OSSetPrioRdy(TaskID);    //任务激活，切换为就绪态
}

/*
* 当高优先级任务就绪，任务切换
*/
void OSTaskSwitch(void)
{
	OSEnterCritical();    //暂停全局中断
	
	OSGetHighRdy();    //查找最高优先级就绪任务 save in OSPrioHighRdy
	if( OSPrioHighRdy != OSPrioCur )
	{
		OSTaskStkCge((UINT32)&TCB[OSPrioHighRdy]);
	}

	OSExitCririacl();    //恢复中断
}

/*
* 任务延时，切换至挂起状态，等待任务块中的等待时钟为0
*/
void OSTimeDly(UINT32 ms)
{	
	if( 0 != ms)
	{
		OSEnterCritical();    //暂停全局中断
		
		TCB[OSPrioCur].OSTCBDly = ms;    //设置挂起时间
		OSDelPripRdy(OSPrioCur);    //挂起当前任务，就绪表位置清0
		OSGetHighRdy();    //查找最高优先级就绪任务 save in OSPrioHighRdy
		OSTaskStkCge((UINT32)&TCB[OSPrioHighRdy]);
		
		OSExitCririacl();    //恢复中断
	}
}



