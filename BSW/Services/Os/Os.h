#ifndef OS_H
#define OS_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "Std_Types.h"

/**************************************************************************
 * @brief   Khởi tạo hệ điều hành (OS)
 * @param   None
 * @return 	None  
 **************************************************************************/
void Os_Init(void);

/**************************************************************************
 * @brief   Tạo và khởi động một luồng (thread)
 * @param   task_func   Con trỏ hàm của luồng cần tạo
 * @param   task_name   Tên của luồng
 * @return 	None  
 **************************************************************************/
void Os_CreateTask(void* (*task_func)(void*), const char* task_name);

/**************************************************************************
 * @brief   Tạo độ trễ (delay)
 * @param   milliseconds    Thời gian độ trễ cần tạo (tính theo mili giây)
 * @return 	None  
 **************************************************************************/
void Os_Delay(uint32 milliseconds);

/**************************************************************************
 * @brief   Kết thúc hệ điều hành
 * @param   None
 * @return 	None  
 **************************************************************************/
void Os_Shutdown(void);

#endif /* OS_H */ 