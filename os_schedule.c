#include "os_schedule.h"

//任务句柄
taskHandle_t taskHandles[MAX_TASKS];

/*!
 *
 *说明：任务创建函数
 *参数：
 *返回值：
 */
void taskCreate(taskHandle_t *taskHandle, void (*taskEnter)(void), OS_U16 taskCycle)
{
	  if (taskHandle == 0) {
        // 错误处理：任务句柄为空指针
        return;
    }
    taskHandle->taskCycle = taskCycle;
    taskHandle->taskEnter = taskEnter;
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
    OS_U8 i = 0;
    for (i = 0; i < MAX_TASKS; i++) {
        if (taskHandles[i].status == TASK_RUNNING) {
            taskHandles[i].status = TASK_IDLE;
            taskHandles[i].taskEnter();
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
    OS_U8 i = 0;
    for (i = 0; i < MAX_TASKS; i++) {
        taskHandles[i].timer++;
        if (taskHandles[i].timer >= taskHandles[i].taskCycle) {
            taskHandles[i].timer = 0;
            taskHandles[i].status = TASK_RUNNING;
        }
    }
}
