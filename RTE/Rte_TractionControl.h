/***************************************************************************
 * @file    Rte_TractionControl.h
 * @brief   Khai báo các hàm giao diện để điều khiển lực kéo (Traction Control) 
 *          thông qua tầng I/O Hardware Abstraction
 * @details File này cung cấp giao diện các hàm liên quan trong hệ thống 
 *          cho phép điều khiển lực kéo và trao đổi dữ liệu giữa các tầng.
 * @version 1.0
 * @date    2025-01-11
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef RTE_TRACTIONCONTROL_H
#define RTE_TRACTIONCONTROL_H

#include "Std_Types.h"
#include "IoHwAb_WheelAngularVelocity.h"    // API IoHwAb để đọc cảm biến vận tốc góc
#include "IoHwAb_BrakeSensor.h"             // API IoHwAb để đọc cảm biến bàn đạp phanh
#include "IoHwAb_SpeedSensor.h"             // API IoHwAb để đọc cảm biến tốc độ
#include "IoHwAb_ThrottleSensor.h"          // API IoHwAb để đọc cảm biến bàn đạp ga

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tốc độ
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
extern Std_ReturnType Rte_Call_RpSpeedSensor_Init(void);

/**************************************************************************
 * @brief 	Khởi tạo cảm biến bàn đạp ga
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
extern Std_ReturnType Rte_Call_RpThrottleSensor_Init(void);

/**************************************************************************
 * @brief 	Khởi tạo cảm biến bàn đạp phanh
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
extern Std_ReturnType Rte_Call_RpBrakeSensor_Init(void);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tốc độ
 * @param   Speed           Con trỏ lưu giá trị tốc độ đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
extern Std_ReturnType Rte_Read_RpSpeedSensor_Speed(float32* Speed);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến bàn đạp ga
 * @param   ThrottlePosition    Con trỏ lưu giá trị bàn đạp ga đọc được       
 * @return 	Std_ReturnType      Trả về E_OK nếu đọc giá trị thành công,
 *                                     E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
extern Std_ReturnType Rte_Read_RpThrottleSensor_ThrottlePosition(float32* ThrottlePosition);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến bàn đạp phanh
 * @param   BrakePosition   Con trỏ lưu giá trị bàn đạp phanh đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
extern Std_ReturnType Rte_Read_RpBrakeSensor_BrakePosition(float32* BrakePosition);

/**************************************************************************
 * @brief 	Khởi tạo cảm biến vận tốc góc
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpWheelAngularVelSensor_Init(void);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến vận tốc góc
 * @param   AngularVel      Mảng lưu giá trị các cảm biến vận tốc góc       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpWheelAngularVelSensor_AngularVel(float32 AngularVel[WHEEL_NUMBERS]);

#endif /* RTE_TRACTIONCONTROL_H */