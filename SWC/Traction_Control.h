/***************************************************************************
 * @file    Traction_Control.h
 * @brief   Khai báo các hàm giao diện để điều khiển lực kéo (Traction Control) 
 *          thông qua tầng RTE (Runtime Environment)
 * @details File này cung cấp giao diện các hàm liên quan trong hệ thống 
 *          cho phép điều khiển lực kéo.
 * @version 1.0
 * @date    2025-01-11
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef TRACTION_CONTROL_H
#define TRACTION_CONTROL_H

#include "Std_Types.h"

/**************************************************************************
 * @brief Định nghĩa các thông số cho hệ thống điều khiển lực kéo
 **************************************************************************/
#define WHEEL_RADIUS 0.35f               /* Bán kính bánh xe (m) */               
#define SLIP_THRESHOLD 0.2f             /* Ngưỡng trượt (20% trượt) */ 
#define BRAKE_THRESHOLD 0.5f            /* Ngưỡng trượt cao (50% trượt - bắt đầu can thiệp phanh) */

/**************************************************************************
 * @brief 	Khởi tạo hệ thống điều khiển lực kéo
 * @param   None
 * @return 	None
 **************************************************************************/
void TractionControl_Init(void); 

/**************************************************************************
 * @brief 	Cập nhật hệ thống điều khiển lực kéo
 * @param   None
 * @return 	None
 **************************************************************************/
void TractionControl_Update(void); 

#endif /* TRACTION_CONTROL_H */
