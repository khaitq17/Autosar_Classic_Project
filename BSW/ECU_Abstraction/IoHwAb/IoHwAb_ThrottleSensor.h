/***************************************************************************
 * @file    IoHwAb_ThrottleSensor.h
 * @brief   Khai báo các hàm giao diện cảm biến bàn đạp ga
 * @details File này cung cấp giao diện để tương tác với phần cứng cảm biến     
 *          bàn đạp ga. Nó chứa cấu trúc cấu hình và các hàm để khởi tạo và 
 *          đọc dữ liệu cảm biến.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef IOHWAB_THROTTLESENSOR_H
#define IOHWAB_THROTTLESENSOR_H

#include "Std_Types.h"

/**************************************************************************
 * @struct  ThrottleSensor_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho cảm biến bàn đạp ga
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho 
 *          cảm biến bàn đạp ga.
 **************************************************************************/
typedef struct {
    uint8 ThrottleSensor_Channel;  /* Kênh ADC để đọc giá trị từ cảm biến bàn đạp ga */
} ThrottleSensor_ConfigType;

/**************************************************************************
 * @brief 	Khởi tạo cảm biến bàn đạp ga
 * @param   ConfigPtr       Con trỏ trỏ đến cấu hình cảm biến bàn đạp ga
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_ThrottleSensor_Init(const ThrottleSensor_ConfigType* ConfigPtr);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến bàn đạp ga
 * @param   ThrottlePosition    Con trỏ trỏ đến giá trị bàn đạp ga đọc được
 * @return 	Std_ReturnType      Trả về E_OK nếu đọc giá trị thành công,
 *                                     E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType IoHwAb_ThrottleSensor_Read(float32* ThrottlePosition);

#endif /* IOHWAB_THROTTLESENSOR_H */