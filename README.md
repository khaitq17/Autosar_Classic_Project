# Autosar Classic Project

## 1. Giới thiệu
Mô phỏng 1 dự án với các hệ thống đơn giản trên ô tô điện, triển khai các tính năng theo tiêu chuẩn Autosar Classic và cập nhật, hiển thị thông tin liên tục lên màn hình console. Trong dự án này sẽ triển khai các hệ thống chính gồm hệ thống điều khiển mô-men xoắn (Torque Control System), hệ thống điều khiển phanh tái sinh (Regenerative Braking Control System), hệ thống kiểm soát lực kéo (Traction Control System) dựa trên việc khởi tạo các ngoại vi của vi điều khiển và sinh số ngẫu nhiên để mô phỏng việc đọc dữ liệu từ các cảm biến.

![image](https://github.com/user-attachments/assets/15bbaa75-fb44-49fb-9f32-fd137e88145e)

## 2. Các tầng chính trong cấu trúc Autosar Classic
### 2.1. Application Layer
- **Application Layer** (Lớp ứng dụng) là một thành phần quan trọng trong kiến ​​trúc phần mềm tổng thể của các hệ thống ô tô, bao gồm nhiều thành phần phần mềm (**Software Component - SWC**) thực hiện tập hợp các tác vụ để hoàn thành chức năng của xe.
- Mỗi SWC chứa nhiều chương trình, logic ứng dụng của hệ thống và không tương tác trực tiếp với phần cứng mà thông qua RTE.

### 2.2. Runtime Enviroment 
- **Runtime Enviroment** (RTE) đóng vai trò quan trọng trong việc kết nối **Software Components (SWC)** và **Basic Software (BSW)** thông qua một kiến trúc trừu tượng.
- Khi SWC cần truy cập phần cứng, chúng không tương tác trực tiếp mà thông qua RTE. RTE sẽ xử lý việc ánh xạ này tới các thành phần BSW, bao gồm các lớp như **Microcontroller Abstraction Layer (MCAL)** và **ECU Abstraction Layer**.

### 2.3. Basic software (BSW)
**Basic Software** (BSW) đóng vai trò nền tảng để hỗ trợ phần mềm ứng dụng (SWC) hoạt động trên phần cứng. BSW cung cấp các dịch vụ cơ bản như quản lý phần cứng, giao tiếp, chẩn đoán, và các dịch vụ hệ thống.

BSW được chia thành 3 thành phần chính:
- **Service Layer** (Lớp dịch vụ): Đây là lớp cao nhất trong BSW, cung cấp các dịch vụ hệ thống và tiện ích cho các phần mềm ứng dụng (SWC) và các lớp khác của BSW. Các dịch vụ này bao gồm quản lý thời gian thực, chẩn đoán, quản lý lỗi, quản lý bộ nhớ.
- **ECU Abstraction Layer** (Lớp trừu tượng hóa ECU): Lớp này cung cấp một giao diện trừu tượng cho tất cả các thiết bị ngoại vi và phần cứng cụ thể của ECU. Nó ẩn đi sự khác biệt về phần cứng của các thiết bị ngoại vi khác nhau và cung cấp một giao diện tiêu chuẩn cho các lớp bên trên (Service Layer và SWC). Lớp này gồm các thành phần: 
    - **Communication Manager** (ComM): Quản lý giao tiếp trên các giao thức truyền thông
    - **I/O Hardware Abstraction** (IoHwAb): Cung cấp các API để truy cập và điều khiển phần cứng đầu vào/đầu ra
    - **Memory Interface** (MemIf): Quản lý truy cập và lưu trữ dữ liệu trên bộ nhớ
Vì dự án này chỉ mô phỏng đơn giản nên sẽ làm việc với lớp I/O Hardware Abstraction, không làm việc với Communication Manager và Memory Interface.

- **Microcontroller Abstraction Layer - MCAL** (Lớp trừu tượng hóa vi điều khiển): Đây là lớp thấp nhất trong BSW, cung cấp giao diện trừu tượng để tương tác trực tiếp với các thành phần phần cứng của vi điều khiển, chẳng hạn như bộ xử lý trung tâm (CPU), các thiết bị ngoại vi tích hợp (như ADC, PWM, ...), và các bộ định thời (Timer).

- Ngoài ra còn có một lớp nữa là **Complex Device Driver** (CDD): Đây là lớp chứa những tính răng riêng biệt của từng hãng xe, trong dự án này sẽ không đề cập đến.

## 3. Cấu trúc dự án

![image](https://github.com/user-attachments/assets/1d5fc576-7ecd-4130-8e81-3f09f8072910)

Trong đó:
- SWC: Là tầng ứng dụng gồm 3 SWC điều khiển hệ thống: Hệ thống điều khiển mô-men xoắn, hệ thống điều khiển phanh tái sinh và hệ thống kiểm soát lực kéo. Nó sẽ khởi tạo các thành phần cần thiết để khởi tạo nên 1 hệ thống hoàn chỉnh và sẽ liên tục cập nhật, điều chỉnh các thông số để đảm bảo điều kiện vận hành.
- RTE: Là tầng trung gian giữa SWC và BSW, tại đây nó sẽ khởi tạo các thông số ban đầu cho các cảm biến (như đầu vào/đầu ra, kênh sử dụng cảm biến, giá trị lớn nhất có thể,...) và đọc các thông số dựa trên cảm biến.
- BSW: Là tầng trực tiếp tương tác với phần cứng.
    - Services: Cung cấp các dịch vụ hệ thống, tiện ích cho các phần mềm ứng dụng (SWC) và các lớp khác của BSW bao gồm hệ điều hành, chẩn đoán, quản lý lỗi và quản lý bộ nhớ.
    - IoHwAb: Cung cấp các API để truy cập và điều khiển phần cứng, sẽ chứa các cảm biến, module sử dụng cho các tầng bên trên như cảm biến tốc độ, cảm biến mô-men xoắn, cảm biến bàn đạp ga, ...
    - MCAL: Cung cấp giao diện trừu tượng để tương tác trực tiếp với các thành phần phần cứng của vi điều khiển như Dio, Adc, Pwm, Can

## 4. Các hệ thống chính
### 4.1. Hệ thống điều khiển mô-men xoắn (Torque Control System)
#### 4.1.1. Giới thiệu hệ thống
Hệ thống điều khiển mô-men xoắn nhằm điều chỉnh và quản lý lượng mô-men xoắn mà động cơ cần cung cấp để đảm bảo xe có thể vận hành một cách an toàn và hiệu quả. Mô-men xoắn quyết định khả năng tăng tốc, giảm tốc và duy trì tốc độ của xe. Quá trình điều khiển này phụ thuộc vào các yếu tố đầu vào như bàn đạp ga và điều kiện vận hành (như tốc độ, tải trọng, điều kiện đường xá).

![image](https://github.com/user-attachments/assets/0c868f71-a2cb-499d-a902-9b3fc2001bec)

#### 4.1.2. Nguyên lý hoạt động
- Hệ thống nhận đầu vào từ các cảm biến, bao gồm tốc độ xe, bàn đạp ga, tải trọng, mô-men xoắn. 
- Các cảm biến gửi tín hiệu đến ECU, ECU sẽ tính toán, so sánh với mô-men yêu cầu từ đọng cơ điện và xác định mức mô-men xoắn sao cho phù hợp với tình huống lái xe (tăng tốc, giữ tốc độ ổn định, hay giảm tốc).

#### 4.1.3. Lợi ích của chức năng điều khiển mô-men xoắn
- Tiết kiệm năng lượng: Bằng cách điều chỉnh mô-men xoắn chính xác, ECU giúp tối ưu hóa lượng năng lượng sử dụng, từ đó cải thiện hiệu suất năng lượng của xe điện.
- Cải thiện trải nghiệm lái: Hệ thống phản ứng nhanh với các thao tác của người lái, cung cấp khả năng kiểm soát chính xác và tăng cường cảm giác lái xe mượt mà và ổn định.
- An toàn hơn: Điều khiển mô-men xoắn giúp ngăn ngừa tình trạng trượt bánh và duy trì sự ổn định của xe, đặc biệt là trong các điều kiện đường trơn trượt hoặc khi tải trọng nặng.

### 4.2. Hệ thống điều khiển phanh tái sinh (Regenerative Braking Control System)
#### 4.2.1. Giới thiệu hệ thống
Hệ thống điều khiển phanh tái sinh cho phép thu hồi và tái tạo lại năng lượng từ quá trình phanh hoặc khi người lái nhả bàn đạp ga. Thay vì lãng phí động năng khi phanh như ở các xe động cơ đốt trong truyền thống, xe điện sử dụng động cơ như một máy phát điện để chuyển đổi động năng thành năng lượng điện, sau đó tái nạp vào pin. Điều này giúp cải thiện hiệu suất tổng thể của xe và tăng quãng đường di chuyển. Quá trình điều khiển này phụ thuộc vào các yếu tố đầu vào như bàn đạp phanh, trạng thái pin và điều kiện vận hành (như tốc độ, tải trọng, điều kiện đường xá).

![image](https://github.com/user-attachments/assets/1a0ca62f-c341-49c5-b795-58efc11124ab)

#### 4.2.2. Nguyên lý hoạt động
- Hệ thống phanh tái sinh hoạt động bằng cách chuyển hóa một phần động năng của xe thành điện năng khi giảm tốc. Điều này được thực hiện bằng cách điều khiển động cơ điện của xe để hoạt động như một máy phát điện, từ đó tạo ra năng lượng điện.
- Mỗi khi người lái xe nhả chân khỏi chân ga hoặc khi phanh, hệ thống sẽ kích hoạt quá trình tái sinh này để chuyển hóa năng lượng thừa từ phanh thành điện năng và lưu trữ trong bộ pin.
- Mức độ tái sinh có thể thay đổi tùy thuộc vào tình huống và thiết lập của hệ thống, giúp tối ưu hóa quá trình thu hồi năng lượng.

#### 4.2.3. Lợi ích của chức năng điều khiển phanh tái sinh
- Tăng quãng đường di chuyển: Phanh tái sinh giúp thu hồi và tái sử dụng năng lượng từ quá trình phanh, từ đó tăng quãng đường di chuyển của xe giữa các lần sạc pin. Điều này đặc biệt hữu ích trong các môi trường đô thị, nơi xe thường xuyên phanh và dừng lại.
- Cải thiện hiệu suất năng lượng: Bằng cách tận dụng năng lượng lãng phí trong quá trình phanh, phanh tái sinh giúp cải thiện hiệu suất tổng thể của xe điện, giảm tiêu hao năng lượng và kéo dài tuổi thọ pin.
- Giảm hao mòn phanh cơ khí: Bởi vì phanh tái sinh thay thế một phần lực phanh cơ khí, hệ thống phanh cơ khí (như phanh đĩa) ít bị hao mòn hơn, từ đó giảm chi phí bảo trì và tăng độ bền của hệ thống phanh

### 4.3. Hệ thống kiểm soát lực kéo (Traction Control System)
#### 4.3.1. Giới thiệu hệ thống
Hệ thống kiểm soát lực kéo (TCS) giúp xe duy trì độ bám đường, đặc biệt trong điều kiện lái xe trơn trượt. TCS làm việc bằng cách giám sát liên tục cảm biến tốc độ và độ trượt bánh xe, từ đó điều chỉnh mô-men xoắn của động cơ hoặc áp dụng phanh để ngăn ngừa mất kiểm soát, giúp xe luôn hoạt động ổn định và an toàn. Quá trình điều khiển này phụ thuộc vào các yếu tố đầu vào như bàn đạp ga, bàn đạp phanh, tốc độ, vận tốc góc bánh xe.

![image](https://github.com/user-attachments/assets/8ad1a469-77bc-48df-9e9b-6eaf5bdf73eb)

#### 4.3.2. Nguyên lý hoạt động
- Hệ thống sử dụng các cảm biến để theo dõi tốc độ quay của các bánh xe. Khi hệ thống phát hiện một hoặc nhiều bánh xe bị trượt (chạy nhanh hơn hoặc chậm hơn so với tốc độ của các bánh còn lại), nó sẽ can thiệp để giảm mô-men xoắn của động cơ hoặc áp dụng phanh vào bánh xe bị trượt.
- Hệ thống có thể làm việc phối hợp với hệ thống phanh để điều chỉnh lực kéo và ngăn ngừa hiện tượng mất kiểm soát khi lái xe trên các bề mặt trơn trượt (như đường ướt, tuyết, bùn, ...).

#### 4.3.3. Lợi ích của chức năng kiểm soát lực kéo
- Tăng cường an toàn: TCS giúp ngăn ngừa tình trạng trượt bánh và mất kiểm soát, đặc biệt trong điều kiện đường trơn trượt hoặc khi tăng tốc đột ngột. Điều này giúp tăng cường an toàn cho cả người lái và hành khách, giảm nguy cơ tai nạn.
- Cải thiện khả năng điều khiển xe: Bằng cách điều chỉnh lực kéo một cách hiệu quả, TCS giúp xe vận hành ổn định hơn, đặc biệt khi gặp điều kiện đường khó khăn hoặc thời tiết xấu. Người lái có thể kiểm soát xe tốt hơn, ngay cả khi xe gặp phải các bề mặt kém ma sát.
- Giảm hao mòn lốp: Bánh xe không bị trượt quá mức nhờ sự can thiệp của TCS, từ đó giúp giảm hao mòn lốp. Điều này kéo dài tuổi thọ của lốp xe và giảm chi phí bảo dưỡng.
- Ổn định và thoải mái khi lái: Hệ thống TCS mang lại sự ổn định và thoải mái khi lái xe, giúp xe vận hành mượt mà hơn ngay cả trên bề mặt trơn trượt.
