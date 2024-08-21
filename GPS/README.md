# GPS-module
### 1. Các Thông Số Hoạt Động
Mô-đun GPS BE-880 Beitian có các thông số hoạt động chính như sau:
- **Tốc độ truyền dữ liệu (Baudrate):** 115200 bps.
- **Tần số lấy mẫu (Frequency):** 5Hz.
- **Giao thức giao tiếp:** UART.
- **Điện áp hoạt động:** Mô-đun hoạt động ở mức điện áp 3.3V hoặc 5V.
- **Mã giao thức:** NMEA.

### 2. Cách Tính Toán Các Thông Số

#### Thực hiện theo từng bước sau:

**Kiểm tra tín hiệu:**

Kiểm tra tín hiệu đã nhận được hoặc không nhận được theo 1 trong 2 cách sau:
1. Kiểm tra đèn báo PPS trên module. Nếu đèn nháy đỏ mỗi 3 giây thì GPS đã bắt được tín hiệu từ vệ tinh.
2. Kiểm tra định dạng mã NMEA. Nếu mã NMEA GPGGA, GPRMC, GPGLL hiển thị giá trị latitude, longitude thì GPS đã bắt được tín hiệu từ vệ tinh.

##### Có thể xem định dạng các mã NMEA trong datasheet sau: https://content.u-blox.com/sites/default/files/u-blox-M10-SPG-5.10_InterfaceDescription_UBX-21035062.pdf 

**Chuyển đổi từ ddmm.mmmmm hoặc dddmm.mmmmm sang độ:**
1. Tách phần độ (dd hoặc ddd) từ chuỗi dữ liệu.
2. Chia phần phút (mm.mmmmm) cho 60 để chuyển đổi thành độ.
3. Cộng kết quả từ bước 2 với phần độ đã tách ở bước 1 để có tọa độ cuối cùng.
Ví dụ, tọa độ vĩ độ 1234.56789 sẽ được chuyển đổi thành:
Vĩ độ = 12 + 34.56789/60 = 12.5761315 (độ)

Chuyển đổi sang độ định dạng dd.mm:
https://github.com/viking-art/GPS-module/blob/main/Convert_latitude.h

**Note: Longitude cũng tương tự như code trong link trên**

**Tính toán khoảng cách giữa các tọa độ từ GPS:** 
1. Tìm hệ số chuyển đổi độ của latitude, longitude sang mét. (Mỗi 10 mét thay đổi 0.000027 độ). (**Tìm hệ số chuyển đổi bằng cách xét số độ thay đổi tương ứng với bao nhiêu mét thay đổi**)
2. Lưu giá trị latitude, longitude có được từ lần đầu tiên GPS fix tọa độ.
3. Lấy giá trị latitude, longitude lúc sau trừ giá trị lưu lần đầu tiên để có độ chênh lệch so với lúc đầu.
4. Lấy độ chênh lệch nhân với hệ số 74074.07407 để có được số cm thay đổi khi di chuyển.

Công thức:
Khoảng cách = 74074.07407 * (chênh lệch độ).

Chuyển đổi sang mét:
https://github.com/viking-art/GPS-module/blob/main/Convert%20to%20meters.h

### 3. Các Phương Pháp Calibration
Để đảm bảo mô-đun GPS hoạt động chính xác, các phương pháp hiệu chuẩn (calibration) sau đây đã được áp dụng:
- **Hiệu chuẩn tần số cập nhật:** Điều chỉnh tần số lấy mẫu của mô-đun lên 5Hz bằng U-center thông qua mạch chuyển đổi USB TTL.
- **Kiểm tra tín hiệu vệ tinh:** Đặt mô-đun ở môi trường thoáng, không bị che khuất bởi các vật cản để nhận tín hiệu vệ tinh tốt nhất.
- **Kiểm tra và hiệu chỉnh độ chính xác:** So sánh tọa độ lấy được từ mô-đun GPS với app Strava để  hiệu chỉnh sai số.
