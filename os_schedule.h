#ifndef __OS_SCHEDULE_H__
#define __OS_SCHEDULE_H__

// 枚举任务
typedef enum {
    // 枚举的顺序就是优先级先后
    TASK_01,
    TASK_02,
    // 可根据实际需求添加更多任务
    // TASK_03,
    // TASK_04,
    // ...

    MAX_TASKS  // 任务数量
} TaskID;

// 任务状态枚举
typedef enum {
    TASK_IDLE,
    TASK_RUNNING
} TaskStatus;

// Task_Handle结构体类型
typedef struct Task_Handle {
    char *taskName;           // 任务名称
    void (*taskEnter)(void);  // 任务函数
    unsigned int taskCycle;   // 任务周期
    unsigned int timer;       // 任务计时
    TaskStatus status;        // 任务执行标志
} taskHandle_t;

extern taskHandle_t taskHandles[MAX_TASKS];
void taskCreate(taskHandle_t *taskHandle, char *taskName, void (*taskEnter)(void), unsigned int taskCycle);
void taskProcess(void);
void timeCounter(void);
#endif
