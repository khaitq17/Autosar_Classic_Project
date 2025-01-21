/***************************************************************************
 * @file    Regen_Brake_Control.h
 * @brief   Khai báo các hàm giao diện để điều khiển phanh tái sinh (Regenerative
 *          Braking Control) thông qua tầng RTE (Runtime Environment)
 * @details File này cung cấp giao diện các hàm liên quan trong hệ thống 
 *          cho phép điều khiển phanh tái sinh.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef REGEN_BRAKE_CONTROL_H
#define REGEN_BRAKE_CONTROL_H

#include "Std_Types.h"

/**************************************************************************
 * @brief Định nghĩa các thông số cho hệ thống phanh tái sinh
 **************************************************************************/
#define CHARGING_EFFICIENCY 0.85f       /* Hiệu suất sạc pin (85%) */
#define KINETIC_CONVERSION_EFF 0.8f     /* Hiệu suất chuyển đổi động năng (80%) */
#define BATTERY_CAPACITY 50000.0f       /* Dung lượng pin (Wh) */
#define TIME_REGEN 5.0f                 /* Thời gian tái sinh (giây) */

#define BRAKE_INPUT_THRESHOLD 10.0f     /* Ngưỡng mức độ nhấn phanh để kích hoạt phanh tái sinh */
#define SPEED_THRESHOLD 10.0f           /* Ngưỡng tốc độ phanh tái sinh (dưới ngưỡng không hoạt động) */
#define BRAKE_COEFFICIENT 0.5f          /* Hệ số phanh tái sinh */ 
#define MAX_BATTERY_TEMP 50.0f          /* Nhiệt độ tối da khi sạc pin (50 độ C) */

#define INCLINATION_THRESHOLD 15.0f     /* Ngưỡng góc nghiêng khi điều chỉnh lực phanh tái sinh */

/**************************************************************************
 * @brief 	Khởi tạo hệ thống điều khiển phanh tái sinh 
 * @details	Hàm này được gọi để khởi tạo hệ thống điều khiển phanh tái sinh
 *          thông qua việc gọi các API từ RTE. 
 * @param   None
 * @return 	None
 **************************************************************************/
void RegenBrakeControl_Init(void);   

/**************************************************************************
 * @brief 	Cập nhật hệ thống điều khiển phanh tái sinh  
 * @details	Hàm này được gọi để cập nhật hệ thống điều khiển phanh tái sinh,
 *          thông qua việc gọi các API từ RTE. 
 * @param   None
 * @return 	None
 **************************************************************************/
void RegenBrakeControl_Update(void); 

#endif /* REGEN_BRAKE_CONTROL_H */