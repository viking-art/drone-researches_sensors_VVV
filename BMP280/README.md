# BMP280
### 1. Các Thông Số Hoạt Động
Mô-đun GPS BE-880 Beitian có các thông số hoạt động chính như sau:
- **Giao thức giao tiếp:** I2C (400000kHz).
- **Điện áp hoạt động:** Mô-đun hoạt động ở mức điện áp 3.3V hoặc 5V.

### 2. Cách Tính Toán Các Thông Số
- **Đọc dữ liệu từ 2 thanh ghi nhiệt độ và áp suất:**
<img width="606" alt="image" src="https://github.com/user-attachments/assets/c5583f6b-2570-41a7-9dee-2224fa6571d7">

Dịch các bit ở các thanh ghi xlsb, lsb, msb của 2 loại thanh ghi nhiệt độ và áp suất theo mô tả trong datasheet để có được dữ liệu áp suất và nhiệt độ thô:

<img width="606" alt="image" src="https://github.com/user-attachments/assets/dda50f40-6e57-4af4-99e4-ce737cee045f">

<img width="606" alt="image" src="https://github.com/user-attachments/assets/0e8a0418-84f0-4944-83c6-63c0718f8700">

Sử dụng công thức được cho sẵn trong datasheet để tính ra áp suất thực tế:

<img width="606" alt="image" src="https://github.com/user-attachments/assets/02c42020-f3cf-46bd-bb01-d986e816899f">

Tính ra độ cao theo công thức trên trang: https://community.bosch-sensortec.com/t5/Question-and-answers/How-to-calculate-the-altitude-from-the-pressure-sensor-data/qaq-p/5702

Công thức tính toán độ cao dựa vào áp suất: H = 44330 * [1 - (P/p0)^(1/5.255) ]

Code tính toán áp suất: https://github.com/viking-art/BMP280/blob/main/Calculating_Altitude.h

### 3. Các Phương Pháp Calibration
- Pressure sẽ được tham khảo ở nơi mình sống để hiệu chỉnh chính xác.

Code Calib BMP280: https://github.com/viking-art/BMP280/blob/main/Calibration_BMP280.h
