编码格式 ： GB2312

创作者 ： harmful

时间 ： 2018年5月5日23:55:50

项目目的 ： 深入了解RTOS原理，初步建立一个简易单片机OS

实现方法 ：
	->用定时器提供调度时钟节拍，初始设定为1ms
	->定时器中断用于刷新各任务<延时节拍>
	->任务有且仅有三个状态：就绪态，运行态，挂起态。
		就绪态：当前任务可被调用，根据任务优先级确定任务执行持续（若高优先级任务一直处于就绪态，低优先级任务永远不会被执行），
		运行态：正在运行的任务，享有CPU资源。
		挂起态：该任务从任务就绪表中被剔除，CPU不会主动调用该任务。
	->创建一个全局变量区用于保存各任务的<延时节拍><私有栈区栈顶指针>
	->私有栈界定：
		任务切换时寄存器保存格式
		+----+
		|CPSR|    当前任务的状态寄存器，普通任务调度始终工作在用户模式
		+----+
		| R0 |    通用寄存器
		+----+
		| ~  |
		+----+
		| R12|
		+----+
		| LR |    R14 任务返回地址
		+----+
		| PC |    R15 下一条执行指令的地址
		+----+

文件架构 ：
	os.S os.c os.h
		->全局变量定义，声明
		->任务控制API定义
	it.c it.h 
		->中断函数初始化（定时器中断，外部中断）
		->中断服务定义
	type.h
		->typedef 类型定义，结构体类型定义
	task.c task.h
		->任务实现源码，任务声明
	
	




	
		



log :
	2018年5月6日00:28:27 
		刚开始有点小紧张哈哈。。
	2018年5月7日00:40:44
		完善了基本架构，字都还没打完，心脏有点痛，要早点睡才行
	
