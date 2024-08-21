// FOV: chỉ vùng không gian mà cảm biến có thể phát hiện hoặc đo lường, là góc nhìn tối đa mà cảm biến có thể bao quát hoặc thu thập dữ liệu.
// Image width in pixels: chỉ số lượng pixel (điểm ảnh) dọc theo chiều rộng của một hình ảnh kỹ thuật số.

#define fov_degrees  42          
#define image_width_pixels  800   
#define dt  0.075

void OpticalFlow_Vel_transfer(int dx, int dy, float alt, float *vfx, float *vfy) 
{   
  alt/=1000;    // meters
  float fov_radians = (fov_degrees) * PI / 180;                     // Convert FOV to radians
	float fov_width_meters = 2 * alt * dt * tan(fov_radians / 2);     // Calculate FOV width in meters
  float scale_factor = fov_width_meters / image_width_pixels;       // Calculate scale factor

  float vx = dx * scale_factor*3.6;      
  float vy = dy * scale_factor*3.6;     
  *vfx=vx; *vfy=vy; 
}
