# Embedded-Automotive
## Bài 2 GPIO
![GPIO](https://raw.githubusercontent.com/diephauthan/Embedded-Automotive/main/GPIO.jpg)

- Để sử dụng ngoại vi, luôn cấp clock cho ngoại vi. Mỗi ngoại vi trên STM32 được điều khiển bằng một bộ điều khiển riêng (ví dụ: GPIO, UART, SPI, I2C, etc.), và mỗi bộ điều khiển đều có một bit điều khiển clock riêng trong thanh ghi tương ứng.
- Sau khi bạn đã bật tín hiệu clock cho ngoại vi, bước tiếp theo là cấu hình các chức năng và các thiết lập khác cho ngoại vi đó, tuỳ thuộc vào mục đích sử dụng của bạn. Cấu hình này thường bao gồm việc chọn chế độ hoạt động, cấu hình các chân GPIO, chọn tốc độ truyền dữ liệu, và các thiết lập khác liên quan đến nhu cầu cụ thể của ứng dụng.

Ví dụ, nếu bạn đang cấu hình một chân GPIO để làm chân đầu ra, bạn sẽ cần xác định các thông số như chế độ đầu ra (output mode), điện trở kéo lên hoặc kéo xuống (pull-up/pull-down), tốc độ đầu ra (output speed), và các thông số khác tùy thuộc vào yêu cầu của ứng dụng.
