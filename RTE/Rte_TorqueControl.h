/***************************************************************************
 * @file    Rte_TorqueControl.h
 * @brief   Khai báo các hàm giao diện để điều khiển mô-men xoắn (Torque Control) 
 *          thông qua tầng I/O Hardware Abstraction
 * @details File này cung cấp giao diện các hàm liên quan trong hệ thống 
 *          cho phép điều khiển mô-men xoắn và trao đổi dữ liệu giữa các tầng.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef RTE_TORQUECONTROL_H
#define RTE_TORQUECONTROL_H

#include "IoHwAb_ThrottleSensor.h"  // API IoHwAb để đọc cảm biến bàn đạp ga
#include "IoHwAb_SpeedSensor.h"     // API IoHwAb để đọc cảm biến tốc độ
#include "IoHwAb_LoadSensor.h"      // API IoHwAb để đọc cảm biến tải trọng
#include "IoHwAb_TorqueSensor.h"    // API IoHwAb để đọc mô-men xoắn thực tế
#include "IoHwAb_MotorDriver.h"     // API IoHwAb để điều khiển mô-men xoắn động cơ
#include "Std_Types.h"  

/**************************************************************************
 * @brief 	Khởi tạo cảm biến bàn đạp ga
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpThrottleSensor_Init(void);

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tốc độ
 * @details	Hàm này được gọi để khởi tạo cảm biến tốc độ, thông qua việc gọi
 *          API từ I/O Hardware Abstraction (IoHwAb).
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpSpeedSensor_Init(void);

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tải trọng
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpLoadSensor_Init(void);

/**************************************************************************
 * @brief 	Khởi tạo cảm biến mô-men xoắn
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpTorqueSensor_Init(void);

/**************************************************************************
 * @brief 	Khởi tạo bộ điều khiển mô-men xoắn
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_PpMotorDriver_Init(void);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến bàn đạp ga
 * @param   ThrottlePosition    Con trỏ lưu giá trị bàn đạp ga đọc được       
 * @return 	Std_ReturnType      Trả về E_OK nếu đọc giá trị thành công,
 *                                     E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpThrottleSensor_ThrottlePosition(float32* ThrottlePosition);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tốc độ
 * @param   Speed           Con trỏ lưu giá trị tốc độ đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpSpeedSensor_Speed(float32* Speed);

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tải trọng
 * @param   LoadWeight      Con trỏ lưu giá trị tải trọng đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpLoadSensor_LoadWeight(float32* LoadWeight);

/**************************************************************************
 * @brief 	Đọc mô-men xoắn thực tế từ cảm biến mô-men xoắn
 * @param   ActualTorque    Con trỏ lưu giá trị mô-men xoắn đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpTorqueSensor_ActualTorque(float32* ActualTorque);

/**************************************************************************
 * @brief 	Ghi dữ liệu mô-men xoắn yêu cầu tới bộ điều khiển động cơ
 * @param   TorqueValue     Giá trị mô-men xoắn yêu cầu muốn ghi (Nm)       
 * @return 	Std_ReturnType  Trả về E_OK nếu ghi giá trị thành công,
 *                                 E_NOT_OK nếu ghi giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Write_PpMotorDriver_SetTorque(float32 TorqueValue);

#endif /* RTE_TORQUECONTROL_H */ 