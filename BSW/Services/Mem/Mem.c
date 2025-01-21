#include "Mem.h"

/**************************************************************************
 * @brief Định nghĩa số lượng vùng bộ nhớ cấp phát tối đa
 **************************************************************************/
#define MAX_ALLOCATIONS 100

/**************************************************************************
 * @brief Mảng giả lập để theo dõi các vùng bộ nhớ đã cấp phát
 **************************************************************************/
void* allocated_blocks[MAX_ALLOCATIONS];

/**************************************************************************
 * @brief Số lượng vùng bộ nhớ đã cấp phát
 **************************************************************************/
uint8 allocation_count = 0;

/**************************************************************************
 * @brief   Khởi tạo hệ thống quản lý bộ nhớ
 * @details Hàm này sẽ khởi tạo hệ thống quản lý bộ nhớ bằng cách thiết lập
 *          mảng giả lập để theo dõi các vùng bộ nhớ đã cấp phát và số lượng 
 *          vùng bộ nhớ đã cấp phát.
 * @param   None
 * @return 	None  
 **************************************************************************/
void Mem_Init() {
    printf("Memory Management System Initialized.\n");
    for (uint8 i = 0; i < MAX_ALLOCATIONS; i++) {
        allocated_blocks[i] = NULL_PTR;
    }
    allocation_count = 0;
}

/**************************************************************************
 * @brief   Cấp phát một vùng bộ nhớ
 * @details Hàm này sẽ cấp phát một vùng bộ nhớ có kích thước size và theo dõi
 *          vùng bộ nhớ đã cấp phát bằng cách lưu trữ con trỏ của vùng bộ nhớ
 *          vào mảng giả lập.
 * @param   size    Kích thước vùng bộ nhớ cần cấp phát
 * @return 	None  
 **************************************************************************/
void* Mem_Alloc(size_t size) {
    if (allocation_count >= MAX_ALLOCATIONS) {
        printf("Memory allocation failed: Maximum allocation count reached.\n");
        return NULL_PTR;
    }

    void* ptr = malloc(size);
    if (ptr == NULL_PTR) {
        printf("Memory allocation failed: Not enough memory.\n");
        return NULL_PTR;
    }

    allocated_blocks[allocation_count++] = ptr;
    printf("Memory allocated: %zu bytes at address %p\n", size, ptr);
    return ptr;
}

/**************************************************************************
 * @brief   Giải phóng một vùng bộ nhớ
 * @details Hàm này sẽ giải phóng vùng bộ nhớ được trỏ bởi con trỏ ptr và
 *          loại bỏ con trỏ này khỏi mảng giả lập.
 * @param   ptr     Con trỏ trỏ đến vùng bộ nhớ cần giải phóng
 * @return 	None  
 **************************************************************************/
void Mem_Free(void* ptr) {
    if (ptr == NULL_PTR) {
        printf("Memory free failed: Null pointer provided.\n");
        return;
    }

    for (uint8 i = 0; i < allocation_count; i++) {
        if (allocated_blocks[i] == ptr) {
            printf("Memory freed at address %p\n", ptr);
            free(ptr);
            allocated_blocks[i] = NULL_PTR;
            return;
        }
    }

    printf("Memory free failed: Invalid pointer %p\n", ptr);
}

/**************************************************************************
 * @brief   Kiểm tra vùng bộ nhớ có hợp lệ hay không
 * @details Hàm này sẽ kiểm tra xem con trỏ ptr trỏ đến vùng bộ nhớ nào đó
 *          có hợp lệ hay không bằng cách kiểm tra xem con trỏ này có tồn tại
 *          trong mảng giả lập không.
 * @param   ptr     Con trỏ trỏ đến vùng bộ nhớ cần kiểm tra
 * @return 	int     Trả về 1 nếu vùng nhớ hợp lệ,
 *                         0 nếu vùng nhớ không hợp lệ  
 **************************************************************************/
int Mem_Check(void* ptr) {
    for (uint8 i = 0; i < allocation_count; i++) {
        if (allocated_blocks[i] == ptr) {
            printf("Memory check: Valid pointer %p\n", ptr);
            return 1;  // Vùng nhớ hợp lệ
        }
    }
    printf("Memory check: Invalid pointer %p\n", ptr);
    return 0;  // Vùng nhớ không hợp lệ
}