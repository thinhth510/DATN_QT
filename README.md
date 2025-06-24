# MockProject - Media Player with UART Control

## Architecture Refactor

### Vấn đề ban đầu
1. **UART Architecture:**
   - Có `UARTController` được tạo ra nhưng không được sử dụng
   - Mỗi view (AudioView, VideoView, PlaylistView) đều tạo ra instance riêng của `UARTReceiver`
   - Điều này có thể gây xung đột khi nhiều view cùng lắng nghe trên cùng một UART port

2. **MediaController Inconsistency:**
   - AudioView và VideoView sử dụng `MediaController`
   - PlaylistView sử dụng `QMediaPlayer` trực tiếp
   - Thiếu tính nhất quán trong architecture
   - PlaylistView không có previous/next functionality trong MediaController

3. **Playlist Auto-play Issue:**
   - Khi chuyển bài bằng next/previous, bài mới ở trạng thái pause
   - Không giống behavior ban đầu khi sử dụng QMediaPlayer trực tiếp

### Giải pháp đã thực hiện

#### 1. Refactor UARTController thành Singleton Pattern
- `UARTController` giờ đây sử dụng Singleton pattern để đảm bảo chỉ có một instance duy nhất
- Quản lý một `UARTReceiver` duy nhất cho toàn bộ ứng dụng
- Phân phối các lệnh UART đến các view phù hợp

#### 2. Cập nhật các View để sử dụng UARTController
- **AudioView**: Thay thế `UARTReceiver` bằng `UARTController`
- **VideoView**: Thay thế `UARTReceiver` bằng `UARTController`  
- **PlaylistView**: Thay thế `UARTReceiver` bằng `UARTController`

#### 3. Extend MediaController với Playlist Functionality
- Thêm playlist support vào `MediaController`
- Thêm methods: `previous()`, `next()`, `setPlaylist()`, `setCurrentIndex()`
- Thêm signals: `currentIndexChanged()`, `playlistEnded()`
- Tự động chuyển bài khi một bài kết thúc

#### 4. Refactor PlaylistView để sử dụng MediaController
- Thay thế `QMediaPlayer` và `QAudioOutput` trực tiếp bằng `MediaController`
- Sử dụng các methods của MediaController cho tất cả media operations
- Đảm bảo tính nhất quán với AudioView và VideoView

#### 5. Fix Auto-play Behavior trong Playlist
- Thêm `m_shouldPlayOnLoad` flag để track trạng thái playing khi chuyển bài
- Khi gọi `next()` hoặc `previous()`, lưu trạng thái playing hiện tại
- Tự động phát bài mới nếu đang ở trạng thái playing
- Đảm bảo behavior giống như ban đầu

#### 6. Auto-play khi bài kết thúc
- Thêm method `autoNext()` để xử lý tự động chuyển bài khi một bài kết thúc
- Khi bài hiện tại kết thúc, tự động chuyển sang bài tiếp theo và phát
- Force `m_shouldPlayOnLoad = true` để đảm bảo bài tiếp theo luôn được phát
- Hỗ trợ loop playlist (quay về bài đầu khi đến bài cuối)

#### 7. Double-click auto-play trong playlist
- Thêm method `setShouldPlayOnLoad()` để control auto-play behavior
- Khi double-click vào bài trong playlist, tự động phát bài đó
- Tái sử dụng logic có sẵn thay vì tạo method mới
- Đảm bảo user experience mượt mà

#### 8. Loop playlist khi kết thúc
- Khi playlist đến bài cuối và kết thúc, tự động quay về bài đầu và phát
- Sử dụng `autoNext()` để xử lý cả next track và loop
- Tạo trải nghiệm phát nhạc liên tục không gián đoạn

#### 9. Cơ chế hoạt động mới
```
UARTReceiver → UARTController (Singleton) → Views (AudioView, VideoView, PlaylistView)
                                                      ↓
                                              MediaController (Unified)
```

- `UARTReceiver` nhận dữ liệu từ UART port
- `UARTController` nhận tín hiệu từ `UARTReceiver` và phân phối đến các view đã đăng ký
- Tất cả views đều sử dụng `MediaController` cho media operations
- `MediaController` hỗ trợ cả single file và playlist modes với auto-play behavior đúng

#### 10. Lợi ích
- **Tránh xung đột**: Chỉ có một UART connection duy nhất
- **Quản lý tập trung**: Tất cả UART logic được tập trung trong `UARTController`
- **Tính nhất quán**: Tất cả views đều sử dụng `MediaController`
- **Dễ bảo trì**: Thay đổi logic chỉ cần sửa trong controllers
- **Hiệu quả**: Không tạo nhiều instance không cần thiết
- **Mở rộng**: Dễ dàng thêm tính năng mới vào MediaController
- **User Experience**: Auto-play behavior đúng như mong đợi

### Cách sử dụng
1. Các view tự động đăng ký với `UARTController` khi được tạo
2. `UARTController` tự động khởi động UART listening khi view đầu tiên được tạo
3. Các view tự động hủy đăng ký khi bị hủy
4. Tất cả các lệnh UART sẽ được phân phối đến tất cả view đang hoạt động
5. PlaylistView sử dụng MediaController cho tất cả media operations
6. Khi chuyển bài bằng next/previous, bài mới sẽ tự động phát nếu đang ở trạng thái playing
7. Khi một bài kết thúc, playlist tự động chuyển sang bài tiếp theo và phát mà không cần user can thiệp
8. Khi double-click vào bài trong playlist, tự động phát bài đó
9. Khi playlist đến bài cuối và kết thúc, tự động quay về bài đầu và phát tiếp

### Files đã thay đổi
- `controller/uartcontroller.h` - Thêm Singleton pattern và quản lý view
- `controller/uartcontroller.cpp` - Implementation mới
- `controller/mediacontroller.h` - Thêm playlist functionality, auto-play flag và setShouldPlayOnLoad method
- `controller/mediacontroller.cpp` - Implementation playlist methods, fix auto-play behavior, auto-play khi bài kết thúc, double-click auto-play và loop playlist
- `view/audioview.h` - Thay thế UARTReceiver bằng UARTController
- `view/audioview.cpp` - Cập nhật để sử dụng UARTController
- `view/videoview.h` - Thay thế UARTReceiver bằng UARTController
- `view/videoview.cpp` - Cập nhật để sử dụng UARTController
- `view/playlistview.h` - Thay thế UARTReceiver bằng UARTController, thêm MediaController
- `view/playlistview.cpp` - Refactor để sử dụng MediaController thay vì QMediaPlayer trực tiếp, thêm double-click auto-play

Multimedia App design by QT