#ifndef __OS_SCHEDULE_H__
#define __OS_SCHEDULE_H__

// 任务状态枚举
typedef enum {
    TASK_IDLE,
    TASK_RUNNING
} TaskStatus;

// Task_Handle结构体类型
typedef struct Task_Handle {
    char *taskName;            // 任务名称
    void (*taskEnter)(void);   // 任务函数
    unsigned int taskCycle;    // 任务周期
    unsigned int timer;        // 任务计时
    TaskStatus status;         // 任务执行标志
    struct Task_Handle *next;  // 下一节点
} Task_Handle;

void taskCreate(struct Task_Handle *taskHandle, char *taskName, void (*taskEnter)(void), unsigned int taskCycle);
void taskStart(struct Task_Handle *taskHandle);
void taskStop(struct Task_Handle *taskHandle);
void taskProcess(void);
void timeCounter(void);
void timeCycleChange(struct Task_Handle *taskHandle, unsigned int cycle);
#endif
