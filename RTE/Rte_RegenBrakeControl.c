/***************************************************************************
 * @file    Rte_RegenBrakeControl.c
 * @brief   Định nghĩa các hàm giao diện để điều khiển phanh tái sinh
 * @details File này triển khai các hàm trong hệ thống cho phép điều khiển 
 *          phanh tái sinh. Nó bao gồm các chức năng khởi tạo, đọc dữ liệu
 *          cho các module phần mềm như bàn đạp phanh, tốc độ, tải trọng, 
 *          trạng thái pin, góc nghiêng của xe.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Rte_RegenBrakeControl.h"

/**************************************************************************
 * @brief 	Khởi tạo cảm biến bàn đạp phanh
 * @details	Hàm này được gọi để khởi tạo cảm biến bàn đạp phanh, thông qua  
 *          việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_RpBrakeSensor_Init() {
    // Cấu hình cho cảm biến bàn đạp phanh
    BrakeSensor_ConfigType brakeSensorConfig = {
        .BrakeSensor_Channel = 4  // Kênh ADC cho cảm biến bàn đạp phanh
    };
    return IoHwAb_BrakeSensor_Init(&brakeSensorConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến bàn đạp phanh
}

/**************************************************************************
 * @brief 	Khởi tạo cảm biến cho sử dụng cho trạng thái pin
 * @details Hàm này được gọi để khởi tạo cảm biến cho sử dụng cho trạng thái 
 *          pin bao gồm cảm biến SOC (State of Charge) và cảm biến nhiệt độ
 *          pin, thông qua việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_Rp_BatterySOC_Init() {
    // Cấu hình cho cảm biến trạng thái pin SOC
    BatterySOC_ConfigType batterySOCConfig = {
        .BatterySOC_Channel = 5,        // Kênh ADC cho cảm biến SOC
        .BatteryTemp_Channel = 6,       // Kênh ADC cho cảm biến nhiệt độ pin
        .BatteryTemp_MaxValue = 50      // Nhiệt độ tối đa giả lập (50 độ C)
    };
    return IoHwAb_BatterySOC_Init(&batterySOCConfig);  // Gọi API từ IoHwAb để khởi tạo cảm biến trạng thái pin SOC
}

/**************************************************************************
 * @brief 	Khởi tạo cảm biến góc nghiêng
 * @details	Hàm này được gọi để khởi tạo cảm biến góc nghiêng, thông qua việc 
 *          gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   None       
 * @return 	Std_ReturnType  Trả về E_OK nếu khởi tạo thành công,
 *                                 E_NOT_OK nếu khởi tạo không thành công
 **************************************************************************/
Std_ReturnType Rte_Call_Rp_InclinationSensor_Init() {
    // Cấu hình cho cảm biến góc nghiêng
    InclinationSensor_ConfigType inclinationConfig = {
        .InclinationSensor_Channel = 7,       // Kênh ADC cho cảm biến góc nghiêng
        .InclinationSensor_MaxValue = 30      // Góc nghiêng tối đa giả lập (30 độ)
    };
    return IoHwAb_InclinationSensor_Init(&inclinationConfig);   // Gọi API từ IoHwAb để khởi tạo cảm biến góc nghiêng
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến bàn đạp phanh
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến bàn đạp phanh, thông qua
 *          việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   BrakePosition   Con trỏ lưu giá trị bàn đạp phanh đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpBrakeSensor_BrakePosition(float32* BrakePosition) {
    if (BrakePosition == NULL_PTR) {
        return E_NOT_OK;  // Trả về lỗi nếu con trỏ NULL
    }
    return IoHwAb_BrakeSensor_Read(BrakePosition);  // Gọi API từ IoHwAb để đọc giá trị từ cảm biến
}

/**************************************************************************
 * @brief 	Đọc giá trị từ các cảm biến sử dụng cho trạng thái pin SOC
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến trạng thái pin, bao 
 *          gồm cảm biến SOC (State of Charge) và cảm biến nhiệt độ pin, thông 
 *          qua việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   BatterySOC      Con trỏ lưu giá trị SOC đọc được
 * @param   BatteryTemp     Con trỏ lưu giá trị nhiệt độ pin đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpBatterySOC_BatterySOC(uint16* BatterySOC, float32* BatteryTemp) {
    if (BatterySOC == NULL_PTR || BatteryTemp == NULL_PTR) {
        return E_NOT_OK;
    }
    return IoHwAb_BatterySOC_Read(BatterySOC, BatteryTemp); // Gọi API từ IoHwAb để đọc giá trị từ các cảm biến trạng thái pin SOC
}

/**************************************************************************
 * @brief 	Đọc giá trị từ cảm biến góc nghiêng
 * @details	Hàm này được gọi để đọc giá trị từ cảm biến góc nghiêng, thông qua
 *          việc gọi API từ I/O Hardware Abstraction (IoHwAb).
 * @param   Inclination     Con trỏ lưu giá trị góc nghiêng đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Rte_Read_RpInclinationSensor_Inclination(float32* Inclination) {
    if (Inclination == NULL_PTR) {
        return E_NOT_OK;
    }
    return IoHwAb_InclinationSensor_Read(Inclination);    // Gọi API từ IoHwAb để đọc giá trị từ cảm biến góc nghiêng
}