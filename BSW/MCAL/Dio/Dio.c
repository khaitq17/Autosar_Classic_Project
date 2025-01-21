/***************************************************************************
 * @file    Dio.c
 * @brief   Định nghĩa các hàm điều khiển DIO
 * @details File này triển khai các hàm để điều khiển và sử dụng DIO của 
 *          vi điều khiển. Nó bao gồm các chức năng khởi tạo, đọc và ghi 
 *          tín hiệu trên chân DIO.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Dio.h"

/**************************************************************************
 * @brief   Khởi tạo DIO
 * @details Hàm này được gọi để khởi tạo DIO.
 * @param   None
 * @return 	None  
 **************************************************************************/
void Dio_Init() {
    // Khởi tạo seed cho random số ngẫu nhiên
    srand(time(0));
    printf("DIO Initialized.\n");
}

/**************************************************************************
 * @brief   Đọc giá trị từ chân DIO 
 * @details Hàm này đọc giá trị từ chân DIO (trả về giá trị ngẫu nhiên).
 * @param   ChannelId       ID của kênh DIO cần đọc
 * @return 	Dio_LevelType   Trả về STD_HIGH nếu giá trị đọc được là 1 
 *                                 STD_LOW nếu giá trị đọc được là 0
 **************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId) {
    Dio_LevelType dio_value;

    // Gọi hàm delay để mô phỏng thời gian đọc DIO
    Dio_Delay(200);  // Tạo độ trễ 200ms để mô phỏng

    // Giả lập trạng thái ngẫu nhiên của DIO (0 hoặc 1)
    dio_value = (rand() % 2) ? STD_HIGH : STD_LOW;

    // In trạng thái đọc được từ kênh DIO
    printf("Reading DIO Channel %d: Value = %d\n", ChannelId, dio_value);

    return dio_value;
}

/**************************************************************************
 * @brief   Ghi giá trị cho chân DIO
 * @details Hàm này ghi trạng thái cho chân DIO (STD_HIGH hoặc STD_LOW).
 * @param   ChannelId   ID của kênh DIO cần ghi
 * @param   Level       Trạng thái cần ghi cho chân DIO
 * @return 	None  
 **************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level) {
    // Gọi hàm delay để mô phỏng thời gian ghi DIO
    Dio_Delay(100);  // Tạo độ trễ 100ms để mô phỏng

    // In trạng thái được ghi vào kênh DIO
    printf("Writing DIO Channel %d: Value = %d\n", ChannelId, Level);
}

/**************************************************************************
 * @brief   Tạo độ trễ (delay)
 * @details Hàm này dùng để tạo độ trễ mô phỏng (tính theo milliseconds).
 * @param   milliseconds    Thời gian độ trễ cần tạo (tính theo mili giây)
 * @return 	None  
 **************************************************************************/
void Dio_Delay(uint32 milliseconds) {
    usleep(milliseconds * 1000); // Hàm usleep tính theo micro giây, nhân với 1000 để thành mili giây
}