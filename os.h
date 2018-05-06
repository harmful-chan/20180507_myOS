/* 编码   ：GB2312               */
/* 创作者 ：harmful              */
/* 时间   ：2018年5月6日01:11:46 */
/*
文件说明 ：工程全局变量声明
*/

#define _OS_H_
#define _OS_H_

#include "type.h"    //typedef

#define OS_TASKS 64    //最大任务书
#define TASK_STACK_SIZE_CUR 512     //通用私有栈空间(Byte)

/* 任务状态切换 */
#define OSSetPrioRdy(prio) { OSRdyTbl[OSRdyGrp[prio]] |=  (0x01<<OSRdyGrp[prio]); }    //置1表示就绪
#define OSDelPrioRdy(prio) { OSRdyTbl[OSRdyGrp[prio]] &= ~(0x01<<OSRdyGrp[prio]); }    //置1表示就绪

/* 临街资源访问 */
#define OSEnterCritical() cpu_sr = OSOffIrt()
#define OSExitCrirical() OSONIrt(cpu_sr)

/* 全局变量 */
extern UINT32 cpu_rs;    //保存CPSR的值
extern UINT8 OSRdyTbl[8];    //任务就绪表
extern UINT8 OSRdyGrp[256];    //优先级轮询表
extern struct TaskCtrBlock TCB[OS_TASKS];    //任务控制块
extern UINT8 OSPrioCur;    //当前任务号
extern UINT8 OSPrioHighRdy;    //最高级任务号

/* OS级API */
extern void OSGetHighRdy(void);    //查表获取当前就绪态最高级任务号， save in OSPrioHighRdy 
extern void OSTackStkCge(UINT32 *p_Stack);    //任务栈转换 
extern UINT32 OSOffIrt(void);    //清零中断位
extern void OSOnIrt(UINT32 cpu_sr);    //恢复中断位


/* 任务级API */
extern void OSInit(void);
extern void OSTaskCreate(void (*Task)(void), UINT32 *p_Stack, UINT8 TaskID);    //创建任务
extern void OSTimeDly(UINT32 ms);    //任务延时（ms）
extern void OSTaskSwitch(void);    //选择最高优先级任务执行

#endif

