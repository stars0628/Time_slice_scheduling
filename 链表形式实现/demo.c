#include "main.h"
#include "os_schedule.h"

// 创建任务结构体
struct Task_Handle TASK_01;
struct Task_Handle TASK_02;
struct Task_Handle TASK_03;

void Task01Handle(void)
{
    /*do sth*/
}

void Task02Handle(void)
{
    /*do sth*/
}

void Task03Handle(void)
{
    /*do sth*/
}
/**
 * @brief   Main program
 */
int main(void)
{
    SysTick_Config(48000000 / 1000);                    // 配置1ms滴答定时器
    taskCreate(&TASK_01, "task01", Task01Handle, 200);  // 创建任务1，任务结构体，任务名，任务处理函数，周期
    taskCreate(&TASK_02, "task02", Task02Handle, 500);
    taskCreate(&TASK_03, "task03", Task03Handle, 1000);
    taskStart(&TASK_01);  // 启动任务
    taskStart(&TASK_02);  // 启动任务
    taskStart(&TASK_03);  // 启动任务
    while (1) {
        taskProcess();  // 任务调度
    }
}
