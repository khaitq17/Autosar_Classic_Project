#ifndef DEM_H
#define DEM_H

#include <stdio.h>
#include <string.h>
#include "Std_Types.h"

/**************************************************************************
 * @brief Định nghĩa số lượng sự kiện chẩn đoán tối đa có thể theo dõi
 **************************************************************************/
#define MAX_DIAGNOSTIC_EVENTS 10

/**************************************************************************
 * @struct  Dem_EventType
 * @brief   Cấu trúc mô phỏng sự kiện chẩn đoán
 * @details Kiểu dữ liệu này được sử dụng để biểu diễn một sự kiện chẩn đoán 
 *          bao gồm mã sự kiện, mô tả và trạng thái.
 **************************************************************************/
typedef struct {
    uint16 event_id;                /* Mã sự kiện chẩn đoán */
    char event_description[50];     /* Mô tả sự kiện */
    uint8 is_active;                /* Trạng thái sự kiện: 1 - active (có lỗi), 0 - inactive (không có lỗi) */
} Dem_EventType;

/**************************************************************************
 * @brief   Khởi tạo hệ thống DEM
 * @param   None
 * @return 	None  
 **************************************************************************/
void Dem_Init(void);

/**************************************************************************
 * @brief   Kích hoạt một sự kiện chẩn đoán
 * @param   event_id        Mã sự kiện chẩn đoán
 * @param   description     Mô tả sự kiện chẩn đoán
 * @return 	None  
 **************************************************************************/
void Dem_ReportErrorStatus(uint16 event_id, const char* description);

/**************************************************************************
 * @brief   Xóa bỏ một sự kiện chẩn đoán
 * @param   event_id    Mã sự kiện chẩn đoán
 * @return 	None  
 **************************************************************************/
void Dem_ClearErrorStatus(uint16 event_id);

/**************************************************************************
 * @brief   Kiểm tra trạng thái của một sự kiện chẩn đoán
 * @param   event_id    Mã sự kiện chẩn đoán
 * @return 	int         Trả về trạng thái của sự kiện: 1 - active, 
 *                                                     0 - inactive, 
 *                                                     -1 - không tồn tại  
 **************************************************************************/
int Dem_CheckErrorStatus(uint16 event_id);

/**************************************************************************
 * @brief   In ra danh sách sự kiện chẩn đoán
 * @param   None
 * @return 	None 
 **************************************************************************/
void Dem_PrintEventList(void);

#endif /* DEM_H */ 