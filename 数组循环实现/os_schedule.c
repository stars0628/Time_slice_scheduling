#include "os_schedule.h"

// 任务句柄
taskHandle_t taskHandles[MAX_TASKS];

/*!
 *
 *说明：任务创建函数
 *参数： *taskHandle：任务结构体数组
        *taskName：任务名字
        (*taskEnter)(void)任务处理函数
        taskCycle任务周期
 *返回值：
 */
void taskCreate(taskHandle_t *taskHandle, char *taskName, void (*taskEnter)(void), unsigned int taskCycle)
{
    if (taskHandle == (void *)0) {
        // 错误处理：任务句柄为空指针
        return;
    }
    taskHandle->taskName = taskName;
    taskHandle->taskEnter = taskEnter;
    taskHandle->taskCycle = taskCycle;
    taskHandle->status = TASK_IDLE;
    taskHandle->timer = 0;
}

/*!
 *
 *说明：判断是否满足允许条件，在主循环中调用
 *参数：
 *返回值：
 */
void taskProcess(void)
{
    unsigned char i = 0;
    for (i = 0; i < MAX_TASKS; i++) {
        if (taskHandles[i].status == TASK_RUNNING) {
            taskHandles[i].taskEnter();
            taskHandles[i].status = TASK_IDLE;
        }
    }
}

/*!
 *
 *说明：计时器，该函数在定时器中断中调用
 *参数：
 *返回值：
 */
void timeCounter(void)
{
    unsigned char i = 0;
    for (i = 0; i < MAX_TASKS; i++) {
        taskHandles[i].timer++;
        if (taskHandles[i].timer >= taskHandles[i].taskCycle) {
            taskHandles[i].timer = 0;
            taskHandles[i].status = TASK_RUNNING;
        }
    }
}

/*!
 *
 *说明：修改任务周期
 *参数：*taskHandle：任务结构体数组，cycle:周期
 *返回值：
 */
void timeCycleChange(taskHandle_t *taskHandle, unsigned int cycle)
{
    taskHandle->taskCycle = cycle;
}