# 时间片调度

#### 介绍
单片机裸机简易时间片调度


#### 软件架构
软件架构说明
1.  有关os_schedule的源文件和头文件各一个
2.  demo.c文件一个


#### 使用说明

1.  添加.c文件和.h文件
2.  定义任务结构体，如struct Task_Handle TASK_01;
3.  在1ms的定时器中断中调用timeCounter()函数
4.  参考demo.c创建和启动任务
5.  在主函数的while中循环调用taskProcess()函数

