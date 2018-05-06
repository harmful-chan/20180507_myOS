/* 编码   ：GB2312               */
/* 创作者 ：harmful              */
/* 时间   ：2018年5月6日01:11:46 */
/*
文件说明 ：工程全局变量声明
*/

#define _OS_H_
#define _OS_H_

#include "type.h"    //typedef

/* 常量宏定义 */
#define OS_TASKS 32    //最大任务书
#define TASK_STACK_SIZE_CUR 512     //通用私有栈空间(Byte)

/* 函数宏定义 */
/* 任务状态切换 */
#define OSSetPrioRdy(prio) OSRdyTbl |= (0x01<<prio);    //置1表示就绪
#define OSDelPrioRdy(prio) OSRdyTbl &= ~(0x01<<prio);    //置1表示就绪
/* 临街资源访问 */
extern UINT32 cpu_sr;
#define OSEnterCritical() cpu_sr = OSStoreSR()
#define OSExitCrirical() OSRestoreSR(cpu_sr)


extern UINT32 OSRdyTbl;    //任务就绪表，32个任务
extern struct TaskCtrBlock TCB[OS_TASKS+1];    //任务控制块



#endif

