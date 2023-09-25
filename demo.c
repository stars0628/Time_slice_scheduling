#include "main.h"

void Task01Handle(void)
{
    /*do sth*/
}

void Task02Handle(void)
{
    /*do sth*/
}

/**
 * @brief   Main program
 */
int main(void)
{
    SysTick_Config(48000000 / 1000);  // 配置1ms滴答定时器
    taskCreate(&taskHandles[TASK_01], Task01Handle, 1000);  // 创建任务1，任务处理函数，周期
    taskCreate(&taskHandles[TASK_02], Task02Handle, 500);   // 创建任务2，任务处理函数，周期
    while (1) {
        taskProcess();  // 任务调度
    }
}
