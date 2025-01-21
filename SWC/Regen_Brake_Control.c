/***************************************************************************
 * @file    Regen_Brake_Control.c
 * @brief   Định nghĩa các hàm giao diện để điều khiển phanh tái sinh thông 
 *          qua tầng RTE
 * @details File này triển khai các hàm trong hệ thống cho phép điều khiển 
 *          phanh tái sinh. Nó bao gồm các chức năng khởi tạo và cập nhật 
 *          hệ thống điều khiển phanh tái sinh với các module phần mềm liên quan.
 * @version 1.0
 * @date    2025-01-05
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Rte_RegenBrakeControl.h"   // Bao gồm interface của RTE cho Regen Brake Control
#include "Regen_Brake_Control.h"
#include <stdio.h>

float32 brake_input = 0.0f;             // Trạng thái bàn đạp phanh
extern float32 current_speed;           // Tốc độ xe hiện tại (km/h)
extern float32 load_weight;             // Tải trọng của xe (kg)
float32 inclination_angle = 0.0f;       // Góc nghiêng của xe (độ)
uint16 battery_soc = 0;                 // Trạng thái pin (SOC) (%)
float32 battery_temp = 0.0f;            // Nhiệt độ pin
boolean regenbrake_active = FALSE;      // Trạng thái phanh tái sinh

/**************************************************************************
 * @brief 	Khởi tạo hệ thống điều khiển phanh tái sinh 
 * @details	Hàm này được gọi để khởi tạo hệ thống điều khiển phanh tái sinh
 *          thông qua việc gọi các API từ RTE. 
 * @param   None
 * @return 	None
 **************************************************************************/
void RegenBrakeControl_Init() {
    Std_ReturnType status;

    printf("Initializing Regenerative Braking Control system...\n");

    // Khởi tạo cảm biến bàn đạp phanh
    status = Rte_Call_RpBrakeSensor_Init();
    if (status == E_OK) {
        printf("Brake sensor has been initialized successfully.\n");
    } else {
        printf("Error initializing brake sensor.\n");
        brake_input = -1.0f;
        return;
    }

    // // Khởi tạo cảm biến tốc độ (nếu chưa khởi tạo)
    // status = Rte_Call_RpSpeedSensor_Init();
    // if (status == E_OK) {
    //     printf("Speed sensor has been initialized successfully.\n");
    // } else {
    //     printf("Error initializing speed sensor.\n");
    //     return;
    // }

    // // Khởi tạo cảm biến tải trọng (nếu chưa khởi tạo)
    // status = Rte_Call_RpLoadSensor_Init();
    // if (status == E_OK) {
    //     printf("Load sensor has been initialized successfully.\n");
    // } else {
    //     printf("Error initializing load sensor.\n");
    //     return;
    // }

    // Khởi tạo cảm biến trạng thái pin 
    status = Rte_Call_Rp_BatterySOC_Init();
    if (status == E_OK) {
        printf("Battery SOC has been initialized successfully.\n");
    } else {
        printf("Error initializing battery SOC.\n");
        return;
    }

    // Khởi tạo cảm biến góc nghiêng
    status = Rte_Call_Rp_InclinationSensor_Init();
    if (status == E_OK) {
        printf("Inclination sensor has been initialized successfully.\n");
    } else {
        printf("Error initializing inclination sensor.\n");
        return;
    }

    printf("The Regenerative Braking Control system is ready.\n");
}

/**************************************************************************
 * @brief 	Cập nhật hệ thống điều khiển phanh tái sinh  
 * @details	Hàm này được gọi để cập nhật hệ thống điều khiển phanh tái sinh,
 *          thông qua việc gọi các API từ RTE. 
 * @param   None
 * @return 	None
 **************************************************************************/
void RegenBrakeControl_Update() {
    // Đọc dữ liệu từ cảm biến tốc độ
    // if (Rte_Read_RpSpeedSensor_Speed(&current_speed) == E_OK) {
    //     printf("Current vehicle speed: %.2f km/h\n", current_speed);
    // } else {
    //     printf("Error reading speed sensor!\n");
    // }
    if (current_speed != -1.0f) {
        printf("Current vehicle speed: %.2f km/h\n", current_speed);
    } else {
        printf("Error reading speed sensor!\n");
    }

    // Đọc dữ liệu từ cảm biến bàn đạp phanh
    if (Rte_Read_RpBrakeSensor_BrakePosition(&brake_input) == E_OK) {
        printf("Brake pedal value: %.2f%%\n", brake_input * 100);
    } else {
        printf("Error reading throttle sensor!\n");
        brake_input = -1.0f;
    }

    // Tính lực phanh tái sinh
    float32 regenbrake_force = (current_speed - SPEED_THRESHOLD) * BRAKE_COEFFICIENT * (brake_input / 100);

    // Tính công suất tái sinh
    float32 regen_power = regenbrake_force * current_speed * KINETIC_CONVERSION_EFF;

    // Tính năng lượng tái sinh trong thời gian phanh
    float32 regen_energy = regen_power * (TIME_REGEN / 3600.0f) * CHARGING_EFFICIENCY;

    // Kiểm tra điều kiện kích hoạt phanh tái sinh
    if (current_speed < SPEED_THRESHOLD) {
        // Tốc độ quá thấp, không kích hoạt phanh tái sinh
        printf("No regenerative braking because the speed is too low.\n");
    } else if (brake_input < BRAKE_INPUT_THRESHOLD) {
        // Chưa nhấn phanh hoặc nhấn quá nhẹ, không kích hoạt phanh tái sinh
        printf("No regenerative braking becausethe brake is not pressed or pressing it insufficiently.\n");
    } else {
        // Kích hoạt phanh tái sinh
        regenbrake_active = TRUE;
        printf("Regenerative brake force activated: %.2f N\n", regenbrake_force);
        printf("Regenerative power from regenerative brake force: %.2f W\n", regen_power);
        printf("Regenerative energy in %.0f seconds: %.2f Wh\n", TIME_REGEN, regen_energy);

        // Chuyển đổi năng lượng tái sinh thành % pin nạp vào
        float32 delta_SOC = (regen_energy / BATTERY_CAPACITY) * 100;
        
        // Đọc dữ liệu từ cảm biến đo trạng thái và nhiệt độ pin
        if (Rte_Read_RpBatterySOC_BatterySOC(&battery_soc, &battery_temp) == E_OK) {
            if (battery_temp < MAX_BATTERY_TEMP) {
                printf("Battery temperature is stable, and regenerative braking is available. Proceeding with recharging...\n");
                printf("Percentage of battery recharged: %.3f%%\n", delta_SOC);
                printf("Recharging process completed!\n");
            } else {
                printf("Battery temperature is too high! Recharging paused.\n");
            }
        }
    }
    
    // Đọc dữ liệu từ cảm biến góc nghiêng
    if (Rte_Read_RpInclinationSensor_Inclination(&inclination_angle) == E_OK) {
        printf("Current vehicle inclination angle: %.2f\u00b0\n", inclination_angle); 
    } else {
        printf("Error reading inclination sensor!\n");
    }

    // Đọc dữ liệu từ cảm biến tải trọng
    // if (Rte_Read_RpLoadSensor_LoadWeight(&load_weight) == E_OK) {
    //     printf("Current vehicle load: %.2f kg\n", load_weight);
    // } else {
    //     printf("Error reading load sensor!\n");
    // }
    if (load_weight != -1.0f) {
        printf("Current vehicle load: %.2f kg\n", load_weight);
    } else {
        printf("Error reading load sensor!\n");
    }

    // Điều chỉnh lực phanh tái sinh theo góc nghiêng
    float32 adjusted_brakeforce = regenbrake_force * (1.0f+ (inclination_angle / 100)); 

    // Điều chỉnh lực phanh tái sinh theo điều kiện địa hình
    printf("Adjusting regenerative braking force...\n");

    // Xe đang lên dốc
    if (inclination_angle > INCLINATION_THRESHOLD) {    
        adjusted_brakeforce *= 1.2f; // Tăng 20% lực phanh tái sinh khi lên dốc
        printf("The vehicle is going uphill...\n");

        // Điều chỉnh theo tải trọng
        if (load_weight > 400.0f) {
            adjusted_brakeforce *= 1.1f; // Tăng thêm lực phanh cho xe nặng
            printf("Heavy load. Increased regenerative braking force: %.2f N\n", adjusted_brakeforce);
        } else {
            printf("Light load. Adjusted regenerative braking force appropriately: %.2f N\n", adjusted_brakeforce);
        }
    } 
    // Xe đang xuống dốc
    else if (inclination_angle < - INCLINATION_THRESHOLD) {   
        adjusted_brakeforce *= 0.8f; // Giảm 20% lực phanh tái sinh khi xuống dốc
        printf("The vehicle í going downhill...\n");

        // Điều chỉnh theo tải trọng
        if (load_weight > 400.0f) {
            adjusted_brakeforce *= 1.05f; // Xe nặng vẫn cần giữ lực phanh
            printf("Heavy load. Slightly reduced braking force but maintained: %.2f N\n", adjusted_brakeforce);
        } else {
            printf("Light load. Reduced regenerative braking force slightly: %.2f N\n", adjusted_brakeforce);
        }        
    }
    // Xe đang đi trên đường bằng
    else {
        printf("The vehicle is moving on a flat surface...\n");

        // Điều chỉnh theo tải trọng
        if (load_weight > 400.0f) {
            adjusted_brakeforce *= 1.05f; // Xe nặng tăng thêm lực phanh
            printf("Heavy load. Increased regenerative braking force: %.2f N\n", adjusted_brakeforce);
        } else {
            printf("Light load. Normal regenerative braking force: %.2f N\n", adjusted_brakeforce);
        }
    }

    // Hoàn tất quá trình cập nhật
    printf("Regenerative braking control system update completed!\n");
}