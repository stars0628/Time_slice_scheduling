#include "os_schedule.h"

// 任务结构体头指针
struct Task_Handle *ListHead = (void *)0;

/*!
 *
 *说明：任务创建函数
 *参数： *taskHandle：任务结构体
        *taskName：任务名字
        (*taskEnter)(void)任务处理函数
        taskCycle任务周期
 *返回值：
 */
void taskCreate(struct Task_Handle *taskHandle, char *taskName, void (*taskEnter)(void), unsigned int taskCycle)
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
 *说明：开始任务
 *参数： *taskHandle：任务结构体
 *返回值：
 */
#if 1
// 尾插链表
void taskStart(struct Task_Handle *taskHandle)
{
    struct Task_Handle *target = ListHead;
    while (target) {
        if (target == taskHandle) {
            return;
        }
        target = target->next;
    }
    taskHandle->next = ListHead;
    ListHead = taskHandle;
}
#else
// 头插链表
void taskStart(struct Task_Handle *taskHandle)
{
    struct Task_Handle *target = ListHead;
    if (target == (void *)0) {
        ListHead = taskHandle;
    } else {
        while (target->next) {
            target = target->next;
        }
        target->next = taskHandle;
    }
    taskHandle->next = (void *)0;
}
#endif

/*!
 *
 *说明：结束任务
 *参数： *taskHandle：任务结构体
 *返回值：
 */
void taskStop(struct Task_Handle *taskHandle)
{
    struct Task_Handle **curr;
    for (curr = &ListHead; *curr;) {
        struct Task_Handle *entry = *curr;
        if (entry == taskHandle) {
            *curr = entry->next;
            return;
        } else {
            curr = &entry->next;
        }
    }
    taskHandle->timer = 0;
    taskHandle->status = TASK_IDLE;
}

/*!
 *
 *说明：判断是否满足允许条件，在主循环中调用
 *参数：
 *返回值：
 */
void taskProcess(void)
{
    struct Task_Handle *target;
    for (target = ListHead; target; target = target->next) {
        if (target->status == TASK_RUNNING) {
            target->taskEnter();
            target->status = TASK_IDLE;
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
    struct Task_Handle *target;
    for (target = ListHead; target; target = target->next) {
        if (target->timer++ >= target->taskCycle) {
            target->timer = 0;
            target->status = TASK_RUNNING;
        }
    }
}

/*!
 *
 *说明：修改任务周期
 *参数：*taskHandle：任务结构体，cycle:周期
 *返回值：
 */
void timeCycleChange(struct Task_Handle *taskHandle, unsigned int cycle)
{
    taskHandle->taskCycle = cycle;
}
