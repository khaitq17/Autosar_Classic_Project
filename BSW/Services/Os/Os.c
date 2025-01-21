#include "Os.h"

/**************************************************************************
 * @brief Định nghĩa số lượng luồng tối đa
 **************************************************************************/
#define MAX_TASKS 9

/**************************************************************************
 * @brief Mảng giả lập để lưu trữ luồng
 **************************************************************************/
pthread_t task_threads[MAX_TASKS];

/**************************************************************************
 * @brief Số lượng luồng hiện tại
 **************************************************************************/
uint8 task_count = 0;

/**************************************************************************
 * @brief   Khởi tạo hệ điều hành (OS)
 * @details Hàm này được gọi để khởi tạo hệ điều hành.
 * @param   None
 * @return 	None  
 **************************************************************************/
void Os_Init() {
    printf("OS Initialized.\n");
    task_count = 0;
}

/**************************************************************************
 * @brief   Tạo và khởi động một luồng (thread)
 * @details Hàm này được gọi để tạo và khởi động một luồng mới.
 * @param   task_func   Con trỏ hàm của luồng cần tạo
 * @param   task_name   Tên của luồng
 * @return 	None  
 **************************************************************************/
void Os_CreateTask(void* (*task_func)(void*), const char* task_name) {
    if (task_count >= MAX_TASKS) {
        printf("Cannot create more tasks. Maximum task count reached.\n");
        return;
    }
    
    printf("Creating task: %s\n", task_name);
    pthread_create(&task_threads[task_count], NULL_PTR, task_func, NULL_PTR);
    task_count++;
}

/**************************************************************************
 * @brief   Tạo độ trễ (delay)
 * @details Hàm này dùng để tạo độ trễ mô phỏng (tính theo milliseconds).
 * @param   milliseconds    Thời gian độ trễ cần tạo (tính theo mili giây)
 * @return 	None  
 **************************************************************************/
void Os_Delay(uint32 milliseconds) {
    usleep(milliseconds * 1000); // Sử dụng usleep cho delay tính theo mili giây
}

/**************************************************************************
 * @brief   Kết thúc hệ điều hành
 * @details Hàm này được gọi để kết thúc hệ điều hành và chờ các luồng kết thúc.
 * @param   None
 * @return 	None  
 **************************************************************************/
void Os_Shutdown() {
    printf("Shutting down OS and waiting for tasks to finish...\n");
    for (uint8 i = 0; i < task_count; i++) {
        pthread_join(task_threads[i], NULL_PTR); // Chờ các luồng kết thúc
    }
    printf("All tasks have completed. OS Shutdown.\n");
}