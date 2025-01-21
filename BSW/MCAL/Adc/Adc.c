/***************************************************************************
 * @file    Adc.c
 * @brief   Định nghĩa các hàm điều khiển ADC
 * @details File này triển khai các hàm để điều khiển và sử dụng bộ chuyển
 *          đổi tín hiệu tương tự của (ADC) của vi điều khiển. Nó bao gồm 
 *          các chức năng khởi tạo, đọc giá trị từ bộ ADC.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Adc.h"

/**************************************************************************
 * @brief Giả lập ADC hardware với các giá trị cấu hình
 **************************************************************************/
static Adc_ConfigType Adc_CurrentConfig;  /* Lưu trữ cấu hình hiện tại của ADC */ 

/**************************************************************************
 * @brief 	Khởi tạo ADC 
 * @details	Hàm này được gọi để khởi tạo ADC với cấu hình được truyền vào.
 * @param   ConfigPtr    Con trỏ trỏ đến cấu hình ADC
 * @return 	None
 **************************************************************************/
void Adc_Init(const Adc_ConfigType* ConfigPtr) {
    // Kiểm tra con trỏ cấu hình 
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to Adc_Init.\n");
        return;
    }

    // Lưu cấu hình ADC từ ConfigPtr vào biến toàn cục
    Adc_CurrentConfig.Channel = ConfigPtr->Channel;
    Adc_CurrentConfig.SamplingTime = ConfigPtr->SamplingTime;
    Adc_CurrentConfig.Resolution = ConfigPtr->Resolution;
    Adc_CurrentConfig.ConversionMode = ConfigPtr->ConversionMode;

    // Khởi tạo seed cho việc sinh số ngẫu nhiên để mô phỏng ADC
    srand(time(0));

    // Giả lập các thông số ngẫu nhiên của ADC
    //Adc_CurrentConfig.Channel = rand() % 32;  // Giả lập kênh ADC từ 0 đến 31
    Adc_CurrentConfig.SamplingTime = (rand() % 8) * 6 + 1;  // Giả lập thời gian lấy mẫu từ 1,5 đến 239,5 chu kỳ
    Adc_CurrentConfig.Resolution = (rand() % 3) * 2 + 8;  // Độ phân giải 8, 10 hoặc 12 bit
    Adc_CurrentConfig.ConversionMode = (rand() % 2) ? ADC_CONV_MODE_SCAN : ADC_CONV_MODE_SINGLE;  // Giả lập chế độ chuyển đổi

    // In ra thông tin cấu hình ADC
    printf("ADC Initialized with Configuration:\n");
    //printf(" - Channel: %d\n", Adc_CurrentConfig.Channel);
    printf(" - Sampling Rate: %d MHz\n", Adc_CurrentConfig.SamplingTime);
    printf(" - Resolution: %d-bit\n", Adc_CurrentConfig.Resolution);
    printf(" - Conversion Mode: %s\n", (Adc_CurrentConfig.ConversionMode == ADC_CONV_MODE_SINGLE) ? "Single" : "Scan");
}

/**************************************************************************
 * @brief 	Đọc giá trị kênh ADC 
 * @details	Hàm này đọc giá trị của 1 kênh ADC (với giá trị ngẫu nhiên).
 * @param   Channel         Kênh ADC cần đọc
 * @param   adcValue        Con trỏ trỏ đến giá trị ADC đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Adc_ReadChannel(Adc_ChannelType Channel, uint16* adcValue) {
    if (adcValue == NULL_PTR) {
        return E_NOT_OK;
    }
    
    // Giả lập giá trị ADC
    uint16 adc_value = 0;

    // Gọi hàm delay để mô phỏng thời gian đọc ADC
    Adc_Delay(500);  // Tạo độ trễ 500ms để mô phỏng

    // Giả lập giá trị ngẫu nhiên từ 0 đến 1023 (giá trị ADC 10-bit)
    adc_value = rand() % 1024;

    // In giá trị đọc được từ kênh ADC
    printf("Reading ADC Channel %d: Value = %d\n", Channel, adc_value);

    // Trả giá trị đọc được thông qua tham chiếu
    *adcValue = adc_value;

    return E_OK;  // Trả về E_OK nếu đọc thành công
}

/**************************************************************************
 * @brief   Tạo độ trễ (delay)
 * @details Hàm này dùng để tạo độ trễ mô phỏng (tính theo milliseconds).
 * @param   milliseconds    Thời gian độ trễ cần tạo (tính theo mili giây)
 * @return 	None  
 **************************************************************************/
void Adc_Delay(uint32 milliseconds) {
    usleep(milliseconds * 1000); // Hàm usleep tính theo micro giây, nhân với 1000 để thành mili giây
}