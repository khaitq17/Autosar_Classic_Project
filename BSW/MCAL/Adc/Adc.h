/***************************************************************************
 * @file    Adc.h
 * @brief   Khai báo giao diện điều khiển ADC (Analog to Digital Convert)
 * @details File này cung cấp giao diện để điều khiển và sử dụng bộ chuyển
 *          đổi tín hiệu tương tự của (ADC) của vi điều khiển. Nó chứa các 
 *          kiểu dữ liệu định nghĩa, cấu trúc cấu hình và các hàm liên quan 
 *          đến ADC.
 * @version 1.0
 * @date    2024-12-15
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <stdlib.h>  // Thư viện hỗ trợ tạo giá trị ngẫu nhiên
#include <time.h>    // Thư viện hỗ trợ thời gian (sử dụng cho random)
#include <unistd.h>  // Thư viện hỗ trợ hàm sleep (sử dụng cho delay)
#include "Std_Types.h"

/**************************************************************************
 * @typedef Adc_InstanceType
 * @brief 	Định nghĩa kiểu dữ liệu cho một bộ ADC (ADC1, ADC2, ...)
 * @details Kiểu dữ liệu này được sử dụng cho tất cả các bộ ADC.
 **************************************************************************/
typedef uint8	Adc_InstanceType;
#define ADC_INSTANCE_1	    (Adc_InstanceType)0		/* ADC1 */
#define ADC_INSTANCE_2	    (Adc_InstanceType)1		/* ADC2 */
// Các bộ ADC khác (nếu có)

/**************************************************************************
 * @typedef Adc_ChannelType
 * @brief 	Định nghĩa kiểu dữ liệu cho kênh ADC
 * @details Kiểu dữ liệu này được sử dụng cho tất cả các kênh ADC.
 **************************************************************************/
typedef uint8	Adc_ChannelType;
#define ADC1_CHANNEL_0      (Adc_ChannelType)0      /* Kênh 0 ADC1 */
#define ADC1_CHANNEL_1      (Adc_ChannelType)1      /* Kênh 1 ADC1 */
#define ADC1_CHANNEL_2      (Adc_ChannelType)2      /* Kênh 2 ADC1 */
#define ADC1_CHANNEL_3      (Adc_ChannelType)3      /* Kênh 3 ADC1 */
#define ADC1_CHANNEL_4      (Adc_ChannelType)4      /* Kênh 4 ADC1 */
#define ADC1_CHANNEL_5      (Adc_ChannelType)5      /* Kênh 5 ADC1 */
#define ADC1_CHANNEL_6      (Adc_ChannelType)6      /* Kênh 6 ADC1 */
#define ADC1_CHANNEL_7      (Adc_ChannelType)7      /* Kênh 7 ADC1 */
#define ADC1_CHANNEL_8      (Adc_ChannelType)8      /* Kênh 8 ADC1 */
#define ADC1_CHANNEL_9      (Adc_ChannelType)9      /* Kênh 9 ADC1 */
#define ADC1_CHANNEL_10     (Adc_ChannelType)10     /* Kênh 10 ADC1 */
#define ADC1_CHANNEL_11     (Adc_ChannelType)11     /* Kênh 11 ADC1 */
#define ADC1_CHANNEL_12     (Adc_ChannelType)12     /* Kênh 12 ADC1 */
#define ADC1_CHANNEL_13     (Adc_ChannelType)13     /* Kênh 13 ADC1 */
#define ADC1_CHANNEL_14     (Adc_ChannelType)14     /* Kênh 14 ADC1 */
#define ADC1_CHANNEL_15     (Adc_ChannelType)15     /* Kênh 15 ADC1 */

#define ADC2_CHANNEL_0      (Adc_ChannelType)16     /* Kênh 0 ADC2 */
#define ADC2_CHANNEL_1      (Adc_ChannelType)17     /* Kênh 1 ADC2 */
#define ADC2_CHANNEL_2      (Adc_ChannelType)18     /* Kênh 2 ADC2 */
#define ADC2_CHANNEL_3      (Adc_ChannelType)19     /* Kênh 3 ADC2 */
#define ADC2_CHANNEL_4      (Adc_ChannelType)20     /* Kênh 4 ADC2 */
#define ADC2_CHANNEL_5      (Adc_ChannelType)21     /* Kênh 5 ADC2 */
#define ADC2_CHANNEL_6      (Adc_ChannelType)22     /* Kênh 6 ADC2 */
#define ADC2_CHANNEL_7      (Adc_ChannelType)23     /* Kênh 7 ADC2 */
#define ADC2_CHANNEL_8      (Adc_ChannelType)24     /* Kênh 8 ADC2 */
#define ADC2_CHANNEL_9      (Adc_ChannelType)25     /* Kênh 9 ADC2 */
#define ADC2_CHANNEL_10     (Adc_ChannelType)26     /* Kênh 10 ADC2 */
#define ADC2_CHANNEL_11     (Adc_ChannelType)27     /* Kênh 11 ADC2 */
#define ADC2_CHANNEL_12     (Adc_ChannelType)28     /* Kênh 12 ADC2 */
#define ADC2_CHANNEL_13     (Adc_ChannelType)29     /* Kênh 13 ADC2 */
#define ADC2_CHANNEL_14     (Adc_ChannelType)30     /* Kênh 14 ADC2 */
#define ADC2_CHANNEL_15     (Adc_ChannelType)31     /* Kênh 15 ADC2 */
// Tương tự với các kênh ADC khác (nếu có)

/**************************************************************************
 * @typedef Adc_GroupType
 * @brief 	Định nghĩa kiểu dữ liệu cho một nhóm kênh ADC
 * @details Kiểu dữ liệu này được sử dụng cho một nhóm kênh trong 1 bộ ADC.
 **************************************************************************/
typedef uint8	Adc_GroupType;

/**************************************************************************
 * @typedef Adc_ValueGroupType
 * @brief 	Định nghĩa kiểu dữ liệu cho giá trị chuyển đổi của một nhóm kênh
 * @details Kiểu dữ liệu này được sử dụng để biểu diễn giá trị chuyển đổi 
 *          của một nhóm kênh ADC. 
 **************************************************************************/
typedef int	Adc_ValueGroupType;

/**************************************************************************
 * @enum    Adc_ConversionModeType
 * @brief 	Định nghĩa kiểu dữ liệu cho chế độ chuyển đổi ADC
 * @details Kiểu dữ liệu này được sử dụng để biểu diễn chế độ chuyển đổi
 *          cho ADC (1 kênh hoặc nhiều kênh).
 **************************************************************************/
typedef enum {
	ADC_CONV_MODE_SINGLE = 0,   /* Thực hiện chuyển đổi ADC trong 1 kênh */
	ADC_CONV_MODE_SCAN = 1		/* Thực hiện chuyển đổi ADC trong nhiều kênh */
} Adc_ConversionModeType;

/**************************************************************************
 * @typedef Adc_SamplingTimeType
 * @brief 	Định nghĩa kiểu dữ liệu cho thời gian lấy mẫu ADC
 * @details Kiểu dữ liệu này được sử dụng để biểu diễn thời gian lấy mẫu cho ADC.
 **************************************************************************/
typedef uint8	Adc_SamplingTimeType;
#define	ADC_SAMPLETIME_1CYCLE5		(Adc_SamplingTimeType)0		/* Thời gian lấy mẫu 1,5 chu kỳ */
#define	ADC_SAMPLETIME_7CYCLE5		(Adc_SamplingTimeType)1		/* Thời gian lấy mẫu 7,5 chu kỳ */
#define	ADC_SAMPLETIME_13CYCLE5		(Adc_SamplingTimeType)2		/* Thời gian lấy mẫu 13,5 chu kỳ */
#define	ADC_SAMPLETIME_28CYCLE5		(Adc_SamplingTimeType)3		/* Thời gian lấy mẫu 28,5 chu kỳ */
#define	ADC_SAMPLETIME_41CYCLE5		(Adc_SamplingTimeType)4		/* Thời gian lấy mẫu 41,5 chu kỳ */
#define	ADC_SAMPLETIME_55CYCLE5		(Adc_SamplingTimeType)5		/* Thời gian lấy mẫu 55,5 chu kỳ */
#define	ADC_SAMPLETIME_71CYCLE5		(Adc_SamplingTimeType)6		/* Thời gian lấy mẫu 71,5 chu kỳ */
#define	ADC_SAMPLETIME_239CYCLE5	(Adc_SamplingTimeType)7		/* Thời gian lấy mẫu 239,5 chu kỳ */

/**************************************************************************
 * @typedef Adc_ResolutionType
 * @brief 	Định nghĩa kiểu dữ liệu cho độ phân giải ADC
 * @details Kiểu dữ liệu này được sử dụng để biểu diễn độ phân giải của ADC.
 **************************************************************************/
typedef uint8	Adc_ResolutionType;
#define ADC_RESOLUTION_8BIT		(Adc_ResolutionType)8		/* Độ phân giải 8 bit */
#define ADC_RESOLUTION_10BIT	(Adc_ResolutionType)10		/* Độ phân giải 10 bit */
#define ADC_RESOLUTION_12BIT	(Adc_ResolutionType)12		/* Độ phân giải 12 bit */
// Các độ phân giải khác (nếu có)

/**************************************************************************
 * @struct  Adc_ConfigType
 * @brief 	Định nghĩa cấu trúc cấu hình cho ADC
 * @details	Kiểu dữ liệu này chứa các thông số cần thiết để cấu hình cho ADC.
 **************************************************************************/
typedef struct {
    Adc_ChannelType Channel;                /* Kênh ADC */
    Adc_SamplingTimeType SamplingTime;      /* Tần số lấy mẫu */
    Adc_ResolutionType Resolution;          /* Độ phân giải ADC */
    Adc_ConversionModeType ConversionMode;  /* Chế độ chuyển đổi ADC */
} Adc_ConfigType;

/**************************************************************************
 * @brief 	Khởi tạo ADC 
 * @param   ConfigPtr    Con trỏ trỏ đến cấu hình ADC
 * @return 	None
 **************************************************************************/
void Adc_Init(const Adc_ConfigType* ConfigPtr);

/**************************************************************************
 * @brief 	Đọc giá trị kênh ADC 
 * @param   Channel         Kênh ADC cần đọc
 * @param   adcValue        Con trỏ trỏ đến giá trị ADC đọc được
 * @return 	Std_ReturnType  Trả về E_OK nếu đọc giá trị thành công,
 *                                 E_NOT_OK nếu đọc giá trị không thành công
 **************************************************************************/
Std_ReturnType Adc_ReadChannel(Adc_ChannelType Channel, uint16* adcValue);

/**************************************************************************
 * @brief   Tạo độ trễ (delay)
 * @param   milliseconds    Thời gian độ trễ cần tạo (tính theo mili giây)
 * @return 	None  
 **************************************************************************/
void Adc_Delay(uint32 milliseconds);

#endif /* ADC_H */ 