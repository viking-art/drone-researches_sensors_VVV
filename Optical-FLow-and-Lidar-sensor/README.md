# Optical-FLow-and-Lidar-sensor
## Thông số hoạt động

- FlowX, FlowY (pixel/frame)
- D (mm)

### Lidar-distance data Chuỗi dữ liệu 14 byte:

- Dữ liệu lidar chứa trong **byte9 và byte10** (quan sát sự thay đổi từ dữ liệu thô). Sau đó đảo vị trí giữa 2 byte để được kết quả chính xác.

### Optical Flow X,Y data Chuỗi dự liệu 18 byte:

- Dữ liệu **flowX** chứa trong các **byte 12,11,9,13** theo thứ tự.
- Dữ liệu **flowY** chứa trong các **byte 15,16,13,14** theo thứ tự.

See code in: https://github.com/NguyenChiCuong-1706/Optical-FLow-and-Lidar-sensor/blob/main/Data_Processing.h

### Cách tính toán các thống số

Đọc các thông số Flow X,Y từ cảm biến (sự thay đổi pixel trong trục X và Y) và  D (độ cao) so với mặt đất, sau đó chuyển đổi chúng thành vận tốc theo trục X và Y (vx, vy) tính bằng km/h.

**FOV** chỉ vùng không gian mà cảm biến có thể phát hiện hoặc đo lường, là góc nhìn tối đa mà cảm biến có thể bao quát hoặc thu thập dữ liệu.
**Image width in pixels** chỉ số lượng **pixel** (điểm ảnh) dọc theo chiều rộng của một hình ảnh kỹ thuật số.

See code in: https://github.com/NguyenChiCuong-1706/Optical-FLow-and-Lidar-sensor/blob/main/Transfer_pixel_to_velocity.h
