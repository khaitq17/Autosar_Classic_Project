#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>
#include "Std_Types.h"

/**************************************************************************
 * @brief   Khởi tạo hệ thống quản lý bộ nhớ
 * @param   None
 * @return 	None  
 **************************************************************************/
void Mem_Init(void);

/**************************************************************************
 * @brief   Cấp phát một vùng bộ nhớ
 * @param   size    Kích thước vùng bộ nhớ cần cấp phát
 * @return 	None  
 **************************************************************************/
void* Mem_Alloc(size_t size);

/**************************************************************************
 * @brief   Giải phóng một vùng bộ nhớ
 * @param   ptr     Con trỏ trỏ đến vùng bộ nhớ cần giải phóng
 * @return 	None  
 **************************************************************************/
void Mem_Free(void* ptr);

/**************************************************************************
 * @brief   Kiểm tra vùng bộ nhớ có hợp lệ hay không
 * @details Hàm này sẽ kiểm tra xem con trỏ ptr trỏ đến vùng bộ nhớ nào đó
 *          có hợp lệ hay không bằng cách kiểm tra xem con trỏ này có tồn tại
 *          trong mảng giả lập không.
 * @param   ptr     Con trỏ trỏ đến vùng bộ nhớ cần kiểm tra
 * @return 	int     Trả về 1 nếu vùng nhớ hợp lệ,
 *                         0 nếu vùng nhớ không hợp lệ   
 **************************************************************************/
int Mem_Check(void* ptr);

#endif /* MEM_H */ 