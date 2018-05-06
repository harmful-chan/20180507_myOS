/* 编码   ：GB2312               */
/* 创作者 ：harmful              */
/* 时间   ：2018年5月6日01:36:07 */
/*
文件说明 ：类型定义*/

#ifndef _TYPE_H_
#define _TYPE_H_

typedef unsigned char  UINT8 
typedef          char  INT8 
typedef unsigned short UINT16 
typedef          short INT16 
typedef unsigned int   UINT32 
typedef          int   INT32  

struct TaskCtrBlock
{
	UINT32 OSTCBStkPtr;    //OS Task Control Block Stack Pointer
	UINT32 OSTCBDly;    //OS Task Control Block Delay
};

#endif



