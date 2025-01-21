/***************************************************************************
 * @file    IoHwAb_TorqueSensor.h
 * @brief   Khai báo các hàm giao diện cảm biến mô-men xoắn
 * @details File này cung cấp giao diện để tương tác với phần cứng cảm biến     
 *          mô-men xoắn. Nó chứa cấu trúc cấu hình và các hàm để khởi tạo và 
 *          đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef IOHWAB_TORQUESENSOR_H
#define IOHWAB_TORQUESENSOR_H

#include "Std_Types.h"

/**************************************************************************
 * @struct  TorqueSensor_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho cảm biến mô-men xoắn
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho 
 *          cảm biến mô-men xoắn.
 **************************************************************************/
typedef struct {
    uint8 TorqueSensor_Channel;   /* Kênh ADC để đọc giá trị từ cảm biến mô-men xoắn */ 
    uint16 TorqueSensor_MaxValue; /* Giá trị mô-men xoắn tối đa (Nm) */
} TorqueSensor_ConfigType;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến mô-men xoắn
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến mô-men xoắn
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_TorqueSensor_Init(const TorqueSensor_ConfigType* ConfigPtr);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến mô-men xoắn
 * @param   TorqueValue     Con trỏ trỏ đến giá trị mô-men xoắn đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_TorqueSensor_Read(float32* TorqueValue);

#endif /* IOHWAB_TORQUESENSOR_H */
