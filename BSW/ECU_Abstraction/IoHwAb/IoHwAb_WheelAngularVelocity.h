/***************************************************************************
 * @file    IoHwAb_WheelAngularVelocity.h
 * @brief   Khai báo các hàm giao diện cảm biến vận tốc góc bánh xe
 * @details File này cung cấp giao diện để tương tác với phần cứng cảm biến     
 *          vận tốc góc bánh xe. Nó chứa cấu trúc cấu hình và các hàm để khởi   
 *          tạo và đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2025-01-11
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef IOHWAB_WHEELANGULARVELOCITY_H
#define IOHWAB_WHEELANGULARVELOCITY_H

#include "Std_Types.h"

/**************************************************************************
 * @brief Định nghĩa số bánh xe
 **************************************************************************/
#define WHEEL_NUMBERS   4   // 4 bánh xe

/**************************************************************************
 * @struct  WheelAngularVel_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho cảm biến vận tốc góc góc bánh xe
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho
 *          cảm biến vận tốc góc góc bánh xe (Wheel Speed Sensor).
 **************************************************************************/
typedef struct {
    uint8 WheelAngularVel_Channel;   /* Kênh ADC để đọc giá trị từ cảm biến vận tốc góc bánh xe */
    uint16 WheelAngularVel_MaxValue; /* Giá trị vận tốc góc tối đa mà cảm biến có thể đọc (rad/s) */ 
} WheelAngularVel_ConfigType; 

/**************************************************************************
 * @brief 	Khởi tạo cảm biến vận tốc góc góc bánh xe
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến vận tốc góc
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_WheelAngularVel_Init(const WheelAngularVel_ConfigType ConfigPtr[WHEEL_NUMBERS]);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến vận tốc góc
 * @param   AngularVelocity Mảng lưu giá trị các vận tốc góc đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_WheelAngularVel_Read(float32 AngularVelocity[WHEEL_NUMBERS]);

#endif /* IOHWAB_WHEELANGULARVELOCITY_H */