#ifndef __OS_SCHEDULE_H__
#define __OS_SCHEDULE_H__

typedef unsigned char OS_U8;
typedef unsigned short OS_U16;

// 定义最大的任务数量
#define MAX_TASKS 2

// 枚举任务
typedef enum {
    TASK_01,
    TASK_02
} TaskID;

// 任务状态枚举
typedef enum {
    TASK_IDLE,
    TASK_RUNNING
} TaskStatus;

// Task_Handle结构体类型
typedef struct Task_Handle {
    OS_U16 taskCycle;         // 任务周期
    OS_U16 timer;             // 任务计时
    TaskStatus status;        // 任务执行标志
    void (*taskEnter)(void);  // 任务函数
} taskHandle_t;

extern taskHandle_t taskHandles[MAX_TASKS];

void taskCreate(taskHandle_t *taskHandle, void (*taskEnter)(void), unsigned short taskCycle);
void taskProcess(void);
void timeCounter(void);

#endif
