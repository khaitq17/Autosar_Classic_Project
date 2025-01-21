/***************************************************************************
 * @file    Rte_TorqueControl.c
 * @brief   Định nghĩa các hàm giao diện để điều khiển mô-men xoắn
 * @details File này triển khai các hàm trong hệ thống cho phép điều khiển 
 *          mô-men xoắn. Nó bao gồm các chức năng khởi tạo, đọc và ghi dữ liệu
 *          cho các module phần mềm như bàn đạp ga, tốc độ, tải trọng, mô-tơ.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Rte_TorqueControl.h"

/**************************************************************************
 * @brief 	Khởi tạo cảm biến bàn đạp ga
 * @details	Hàm này được gọi để khởi tạo cảm biến bàn đạp ga, thông qua việc 
 *          gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpThrottleSensor_Init() {
    // Cấu hình cho cảm biến bàn đạp ga
    ThrottleSensor_ConfigType throttleSensorConfig = {
        .ThrottleSensor_Channel = 0  // Kênh ADC cho cảm biến bàn đạp ga
    };
    return IoHwAb_ThrottleSensor_Init(&throttleSensorConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến bàn đạp ga
}

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tốc độ
 * @details	Hàm này được gọi để khởi tạo cảm biến tốc độ, thông qua việc gọi
 *          API từ I/O Hardware Abstraction (IoHwAb).
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpSpeedSensor_Init() {
    // Cấu hình cho cảm biến tốc độ
    SpeedSensor_ConfigType speedSensorConfig = {
        .SpeedSensor_Channel = 1,        // Kênh ADC cho cảm biến tốc độ
        .SpeedSensor_MaxValue = 200      // Tốc độ tối đa giả lập (200 km/h)
    };
    return IoHwAb_SpeedSensor_Init(&speedSensorConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến tốc độ
}

/**************************************************************************
 * @brief 	Khởi tạo cảm biến tải trọng
 * @details	Hàm này được gọi để khởi tạo cảm biến tải trọng, thông qua việc 
 *          gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpLoadSensor_Init() {
    // Cấu hình cho cảm biến tải trọng
    LoadSensor_ConfigType loadSensorConfig = {
        .LoadSensor_Channel = 2,         // Kênh ADC cho cảm biến tải trọng
        .LoadSensor_MaxValue = 1000      // Tải trọng tối đa giả lập (1000 kg)
    };
    return IoHwAb_LoadSensor_Init(&loadSensorConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến tải trọng
}

/**************************************************************************
 * @brief 	Khởi tạo cảm biến mô-men xoắn
 * @details	Hàm này được gọi để khởi tạo cảm biến mô-men xoắn, thông qua việc 
 *          gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpTorqueSensor_Init() {
    // Cấu hình cho cảm biến mô-men xoắn
    TorqueSensor_ConfigType torqueSensorConfig = {
        .TorqueSensor_Channel = 3,       // Kênh ADC cho cảm biến mô-men xoắn
        .TorqueSensor_MaxValue = 500     // Mô-men xoắn tối đa giả lập (500 Nm)
    };
    return IoHwAb_TorqueSensor_Init(&torqueSensorConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến mô-men xoắn
}

/**************************************************************************
 * @brief 	Khởi tạo bộ điều khiển mô-men xoắn
 * @details	Hàm này được gọi để khởi tạo bộ điều khiển mô-men xoắn, thông 
 *          qua việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_PpMotorDriver_Init() {
    // Cấu hình cho bộ điều khiển mô-men xoắn
    MotorDriver_ConfigType motorDriverConfig = {
        .Motor_Channel = 1,              // Kênh điều khiển mô-tơ
        .Motor_MaxTorque = 300           // Mô-men xoắn tối đa giả lập (300 Nm)
    };
    return IoHwAb_MotorDriver_Init(&motorDriverConfig);  // Gọi API từ IoHwAb để khởi tạo bộ điều khiển mô-men xoắn
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến bàn đạp ga
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến bàn đạp ga, thông qua
 *          việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   ThrottlePosition    Con trỏ lưu giá trị bàn đạp ga đọc được       
 * @return 	Std_ReturnType      Trả về E_OK nếu đọc giá trị thành công,
 *                                     E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpThrottleSensor_ThrottlePosition(float32* ThrottlePosition) {
    if (ThrottlePosition == NULL_PTR) {
        return E_NOT_OK;  // Trả về lỗi nếu con trỏ NULL
    }
    return IoHwAb_ThrottleSensor_Read(ThrottlePosition);  // Gọi API từ IoHwAb để đọc giá trị từ cảm biến
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tốc độ
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến tốc độ, thông qua
 *          việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   Speed           Con trỏ lưu giá trị tốc độ đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpSpeedSensor_Speed(float32* Speed) {
    if (Speed == NULL_PTR) {
        return E_NOT_OK;
    }
    return IoHwAb_SpeedSensor_Read(Speed);  // Gọi API từ IoHwAb để đọc giá trị từ cảm biến tốc độ
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến tải trọng
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến tải trọng, thông qua
 *          việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   LoadWeight      Con trỏ lưu giá trị tải trọng đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpLoadSensor_LoadWeight(float32* LoadWeight) {
    if (LoadWeight == NULL_PTR) {
        return E_NOT_OK;
    }
    return IoHwAb_LoadSensor_Read(LoadWeight);  // Gọi API từ IoHwAb để đọc giá trị từ cảm biến tải trọng
}

/**************************************************************************
 * @brief 	Đọc mô-men xoắn thực tế từ cảm biến mô-men xoắn
 * @details	Hàm này được gọi để đọc mô-men xoắn thực tế từ cảm biến mô-men 
 *          xoắn, thông qua việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   ActualTorque    Con trỏ lưu giá trị mô-men xoắn đọc được       
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpTorqueSensor_ActualTorque(float32* ActualTorque) {
    if (ActualTorque == NULL_PTR) {
        return E_NOT_OK;
    }
    return IoHwAb_TorqueSensor_Read(ActualTorque);  // Gọi API từ IoHwAb để đọc mô-men xoắn thực tế
}

/**************************************************************************
 * @brief 	Ghi dữ liệu mô-men xoắn yêu cầu tới bộ điều khiển động cơ
 * @details	Hàm này được gọi để ghi dữ liệu mô-men xoắn yêu cầu tới bộ điều khiển
 *          động cơ, thông qua việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   TorqueValue     Giá trị mô-men xoắn yêu cầu muốn ghi (Nm)       
 * @return 	Std_ReturnType  Trả về E_OK nếu ghi giá trị thành công,
 *                                 E_NOT_OK nếu ghi giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Write_PpMotorDriver_SetTorque(float32 TorqueValue) {
    return IoHwAb_MotorDriver_SetTorque(TorqueValue);  // Gọi API từ IoHwAb để ghi mô-men xoắn yêu cầu tới động cơ
}