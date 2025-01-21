/***************************************************************************
 * @file    IoHwAb_MotorDriver.h
 * @brief   Khai báo các hàm giao diện cho mô-tơ
 * @details File này cung cấp giao diện để tương tác với phần cứng mô-tơ.    
 *          Nó chứa cấu trúc cấu hình và các hàm để khởi tạo và đọc dữ liệu 
 *          cảm biến.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef IOHWAB_MOTORDRIVER_H
#define IOHWAB_MOTORDRIVER_H

#include "Std_Types.h"

/**************************************************************************
 * @struct  MotorDriver_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho mô-tơ
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho 
 *          mô-tơ điện.
 **************************************************************************/
typedef struct {
    uint8 Motor_Channel;      /* Kênh PWM điều khiển mô-tơ */
    uint16 Motor_MaxTorque;   /* Mô-men xoắn tối đa (Nm) */
} MotorDriver_ConfigType;

/**************************************************************************
 * @brief 	Khởi tạo mô-tơ
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình mô-tơ
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_MotorDriver_Init(const MotorDriver_ConfigType* ConfigPtr);

/**************************************************************************
 * @brief 	Điều chỉnh mô-men xoắn của mô-tơ
 * @param   TorqueValue     Giá trị mô-men xoắn muốn điều chỉnh (Nm)
 * @return 	Std_ReturnType  Trả về E_OK nếu điều chỉnh thành công,
 *                                 E_NOT_OK nếu điều chỉnh không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_MotorDriver_SetTorque(float32 TorqueValue);

#endif /* IOHWAB_MOTORDRIVER_H */