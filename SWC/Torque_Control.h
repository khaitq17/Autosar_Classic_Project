/***************************************************************************
 * @file    Torque_Control.h
 * @brief   Khai báo các hàm giao diện để điều khiển mô-men xoắn (Torque Control) 
 *          thông qua tầng RTE (Runtime Environment)
 * @details File này cung cấp giao diện các hàm liên quan trong hệ thống 
 *          cho phép điều khiển mô-men xoắn.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef TORQUE_CONTROL_H
#define TORQUE_CONTROL_H

#include "Std_Types.h"

/**************************************************************************
 * @brief Định nghĩa giá trị mô-men xoắn tối đa và tối thiểu
 **************************************************************************/
#define MAX_TORQUE 100.0f   /* Giá trị mô-men xoắn tối đa */
#define MIN_TORQUE 0.0f     /* Giá trị mô-men xoắn tối thiểu */

/**************************************************************************
 * @brief 	Khởi tạo hệ thống điều khiển mô-men xoắn 
 * @param   None
 * @return 	None
 **************************************************************************/
void TorqueControl_Init(void); 

/**************************************************************************
 * @brief 	Cập nhật hệ thống điều khiển mô-men xoắn
 * @param   None
 * @return 	None
 **************************************************************************/
void TorqueControl_Update(void); 

#endif /* TORQUE_CONTROL_H */ 