#include "Dem.h"

/**************************************************************************
 * @brief Mảng để lưu trữ các sự kiện chẩn đoán
 **************************************************************************/
Dem_EventType diagnostic_events[MAX_DIAGNOSTIC_EVENTS];

/**************************************************************************
 * @brief Số lượng sự kiện chẩn đoán hiện tại
 **************************************************************************/
uint8 event_count = 0;

/**************************************************************************
 * @brief   Khởi tạo hệ thống DEM
 * @details Hàm này được gọi một lần duy nhất khi khởi động hệ thống.
 * @param   None
 * @return 	None  
 **************************************************************************/
void Dem_Init() {
    printf("Diagnostic Event Manager (DEM) Initialized.\n");
    for (uint8 i = 0; i < MAX_DIAGNOSTIC_EVENTS; i++) {
        diagnostic_events[i].event_id = -1;
        diagnostic_events[i].is_active = 0;
        strcpy(diagnostic_events[i].event_description, "");
    }
    event_count = 0;
}

/**************************************************************************
 * @brief   Kích hoạt một sự kiện chẩn đoán
 * @details Hàm này được gọi khi một sự kiện chẩn đoán xảy ra.
 * @param   event_id        Mã sự kiện chẩn đoán
 * @param   description     Mô tả sự kiện chẩn đoán
 * @return 	None  
 **************************************************************************/
void Dem_ReportErrorStatus(uint16 event_id, const char* description) {
    if (event_count >= MAX_DIAGNOSTIC_EVENTS) {
        printf("Cannot report more events. Maximum diagnostic events reached.\n");
        return;
    }

    // Kiểm tra xem sự kiện đã tồn tại chưa
    for (uint8 i = 0; i < event_count; i++) {
        if (diagnostic_events[i].event_id == event_id) {
            diagnostic_events[i].is_active = 1;
            printf("Event ID %d already exists. Updating its status to active.\n", event_id);
            return;
        }
    }

    // Thêm sự kiện mới
    diagnostic_events[event_count].event_id = event_id;
    diagnostic_events[event_count].is_active = 1;
    strncpy(diagnostic_events[event_count].event_description, description, sizeof(diagnostic_events[event_count].event_description) - 1);
    event_count++;

    printf("New diagnostic event reported: ID = %d, Description = %s\n", event_id, description);
}

/**************************************************************************
 * @brief   Xóa bỏ một sự kiện chẩn đoán
 * @details Hàm này được gọi để xóa một sự kiện chẩn đoán, tức là lỗi đã được 
 *          giải quyết.
 * @param   event_id    Mã sự kiện chẩn đoán
 * @return 	None  
 **************************************************************************/
void Dem_ClearErrorStatus(uint16 event_id) {
    for (uint8 i = 0; i < event_count; i++) {
        if (diagnostic_events[i].event_id == event_id) {
            diagnostic_events[i].is_active = 0;
            printf("Event ID %d cleared (no longer active).\n", event_id);
            return;
        }
    }
    printf("Event ID %d not found.\n", event_id);
}

/**************************************************************************
 * @brief   Kiểm tra trạng thái của một sự kiện chẩn đoán
 * @details Hàm này được gọi để kiểm tra xem một sự kiện chẩn đoán có đang
 *          active hay không.
 * @param   event_id    Mã sự kiện chẩn đoán
 * @return 	int         Trả về trạng thái của sự kiện: 1 - active, 
 *                                                     0 - inactive, 
 *                                                     -1 - không tồn tại  
 **************************************************************************/
int Dem_CheckErrorStatus(uint16 event_id) {
    for (uint8 i = 0; i < event_count; i++) {
        if (diagnostic_events[i].event_id == event_id) {
            if (diagnostic_events[i].is_active) {
                printf("Event ID %d is active.\n", event_id);
                return 1;
            } else {
                printf("Event ID %d is inactive.\n", event_id);
                return 0;
            }
        }
    }
    printf("Event ID %d not found.\n", event_id);
    return -1;  // Sự kiện không tồn tại
}

/**************************************************************************
 * @brief   In ra danh sách sự kiện chẩn đoán
 * @details Hàm này in ra toàn bộ danh sách các sự kiện chẩn đoán.
 * @param   None
 * @return 	None 
 **************************************************************************/
void Dem_PrintEventList() {
    printf("Diagnostic Events List:\n");
    for (uint8 i = 0; i < event_count; i++) {
        printf("ID: %d, Description: %s, Status: %s\n",
               diagnostic_events[i].event_id,
               diagnostic_events[i].event_description,
               diagnostic_events[i].is_active ? "Active" : "Inactive");
    }
}