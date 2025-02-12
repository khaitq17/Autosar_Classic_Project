#include "Dcm.h"
#include "Dem.h"  // Sử dụng Dem để xử lý chẩn đoán lỗi

/**************************************************************************
 * @brief   Khởi tạo hệ thống DCM
 * @details Hàm này được gọi một lần duy nhất khi khởi động hệ thống.
 * @param   None
 * @return 	None  
 **************************************************************************/
void Dcm_Init() {
    printf("Diagnostic Communication Manager (DCM) Initialized.\n");
}

/**************************************************************************
 * @brief   Xử lý yêu cầu chẩn đoán từ thiết bị kiểm tra
 * @details Hàm này được gọi mỗi khi nhận được một yêu cầu chẩn đoán từ 
 *          thiết bị kiểm tra.
 * @param   request     Con trỏ đến cấu trúc mô phỏng gói tin chẩn đoán
 * @return 	None  
 **************************************************************************/
void Dcm_ProcessRequest(Dcm_MessageType* request) {
    printf("Received diagnostic request. Service ID: 0x%x\n", request->service_id);
    
    switch (request->service_id) {
        case DIAGNOSTIC_SESSION_CONTROL:
            printf("Processing Diagnostic Session Control...\n");
            Dcm_SendResponse(request->service_id, "Session Control Acknowledged");
            break;

        case ECU_RESET:
            printf("Processing ECU Reset...\n");
            Dcm_SendResponse(request->service_id, "ECU Reset Acknowledged");
            // Giả lập reset ECU
            break;

        case READ_DTC:
            printf("Processing Read DTC...\n");
            Dcm_SendResponse(request->service_id, "Read DTC Acknowledged");
            // Giả lập đọc mã DTC từ hệ thống DEM
            Dem_PrintEventList();
            break;

        case CLEAR_DTC:
            printf("Processing Clear DTC...\n");
            Dcm_SendResponse(request->service_id, "Clear DTC Acknowledged");
            // Giả lập xóa các mã DTC từ hệ thống DEM
            for (uint8 i = 0; i < MAX_DIAGNOSTIC_EVENTS; i++) {
                Dem_ClearErrorStatus(i);
            }
            break;

        default:
            printf("Unknown diagnostic service ID: 0x%x\n", request->service_id);
            Dcm_SendResponse(request->service_id, "Unknown Service ID");
            break;
    }
}

/**************************************************************************
 * @brief   Gửi phản hồi chẩn đoán đến thiết bị kiểm tra
 * @details Hàm này được gọi mỗi khi cần gửi phản hồi chẩn đoán đến thiết bị
 *          kiểm tra.
 * @param   service_id  Mã dịch vụ chẩn đoán
 * @param   response    Chuỗi phản hồi
 * @return 	None  
 **************************************************************************/
void Dcm_SendResponse(uint16 service_id, const char* response) {
    printf("Sending response to Service ID: 0x%x - %s\n", service_id, response);
}