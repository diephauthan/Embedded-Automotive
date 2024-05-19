# Embedded-Automotive
## Bài 2: GPIO
![GPIO](https://raw.githubusercontent.com/diephauthan/Embedded-Automotive/main/GPIO.jpg)

- Để sử dụng ngoại vi, luôn cấp clock cho ngoại vi. Mỗi ngoại vi trên STM32 được điều khiển bằng một bộ điều khiển riêng (ví dụ: GPIO, UART, SPI, I2C, etc.), và mỗi bộ điều khiển đều có một bit điều khiển clock riêng trong thanh ghi tương ứng.
- Sau khi bạn đã bật tín hiệu clock cho ngoại vi, bước tiếp theo là cấu hình các chức năng và các thiết lập khác cho ngoại vi đó, tuỳ thuộc vào mục đích sử dụng của bạn. Cấu hình này thường bao gồm việc chọn chế độ hoạt động, cấu hình các chân GPIO, chọn tốc độ truyền dữ liệu, và các thiết lập khác liên quan đến nhu cầu cụ thể của ứng dụng.

Ví dụ, nếu bạn đang cấu hình một chân GPIO để làm chân đầu ra, bạn sẽ cần xác định các thông số như chế độ đầu ra (output mode), điện trở kéo lên hoặc kéo xuống (pull-up/pull-down), tốc độ đầu ra (output speed), và các thông số khác tùy thuộc vào yêu cầu của ứng dụng.

GPIO_InitTypeDef là một cấu trúc dữ liệu được sử dụng trong thư viện STM32 Standard Peripheral Firmware Library (ví dụ như trong file stm32f4xx_gpio.h) để cấu hình các chân GPIO trên vi điều khiển STM32. Cấu trúc này chứa các thông số cần thiết để cấu hình một chân GPIO, bao gồm:

GPIO_Pin: Định danh chân GPIO cần cấu hình. Đây thường là một hoặc kết hợp của các giá trị GPIO_Pin_x (trong đó x là số của chân GPIO) được định nghĩa trong thư viện STM32.

GPIO_Mode: Chế độ hoạt động của chân GPIO, ví dụ như đầu vào (input), đầu ra (output), hoặc chức năng đặc biệt (alternate function).

GPIO_Speed: Tốc độ của chân GPIO, thường được thiết lập thành một trong các giá trị GPIO_Speed_xMHz (trong đó x là tốc độ truyền dẫn tối đa của chân GPIO).

GPIO_OType: Loại đầu ra của chân GPIO, có thể là push-pull hoặc open-drain.

GPIO_PuPd: Trạng thái điện trở kéo lên hoặc kéo xuống của chân GPIO khi không có tín hiệu đầu vào, có thể là GPIO_PuPd_NOPULL, GPIO_PuPd_UP, hoặc GPIO_PuPd_DOWN.

Khi bạn muốn cấu hình một chân GPIO, bạn sẽ khai báo một biến kiểu GPIO_InitTypeDef và cung cấp các thông số cần thiết cho nó, sau đó chuyển nó cho hàm GPIO_Init để thực hiện việc cấu hình chân GPIO tương ứng.

## Bài 3: Interrupt & Timer
Ngắt là 1 sự kiện khẩn cấp xảy ra trong hay ngoài vi điều khiển. Nó yêu MCU phải dừng chương trình chính và thực thi chương trình ngắt.

