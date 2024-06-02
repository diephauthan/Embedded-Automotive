# Embedded-Automotive
## Bài 2: GPIO
<details>
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
</details>

## Bài 3: Interrupt & Timer
<details>
Ngắt là 1 sự kiện khẩn cấp xảy ra trong hay ngoài vi điều khiển. Nó yêu MCU phải dừng chương trình chính và thực thi chương trình ngắt.

**Độ ưu tiên**
Khi một ngắt ưu tiên cao hơn xảy ra trong khi một ngắt ưu tiên thấp hơn đang được xử lý, việc xử lý ngắt ưu tiên thấp hơn sẽ bị tạm dừng và ngắt ưu tiên cao hơn sẽ được xử lý. Khi ngắt ưu tiên cao hơn hoàn tất, việc xử lý ngắt ưu tiên thấp hơn sẽ tiếp tục. Điều này được gọi là lồng ngắt (interrupt nesting).

Nếu một ngắt ưu tiên thấp hơn xảy ra trong khi bộ xử lý đang xử lý ngắt ưu tiên cao hơn, ngắt ưu tiên thấp hơn sẽ bị để lại ở trạng thái chờ cho đến khi ngắt ưu tiên cao hơn hoàn tất.

Khi một ngắt xảy ra cùng mức ưu tiên với ngắt đang được xử lý, ngắt đang được xử lý sẽ được phép hoàn thành. Sau đó, quá trình xử lý ngắt tiếp theo sẽ bắt đầu. Trong trường hợp này, lồng ngắt cũng có thể xảy ra nếu ngắt hiện tại kích hoạt lại các ngắt ở cùng mức ưu tiên với nó. Nói cách khác, một ngắt có thể cho phép nó bị ngắt bởi các ngắt khác ở cùng mức ưu tiên.

**Mức và cạnh**
- Ngắt theo mức (Level-triggered interrupt):

Ngắt theo mức xảy ra khi tín hiệu ngắt giữ ở mức logic cao hoặc thấp (ví dụ: mức cao - logic 1 hoặc mức thấp - logic 0) trong một khoảng thời gian nhất định.
Miễn là tín hiệu ngắt giữ ở mức đó, ngắt sẽ tiếp tục được yêu cầu. Điều này có nghĩa là nếu một thiết bị ngoại vi giữ tín hiệu ngắt ở mức cao, CPU sẽ liên tục nhận biết yêu cầu ngắt cho đến khi tín hiệu đó được xóa.
Ví dụ: Một cảm biến nhiệt độ có thể kích hoạt ngắt mức cao khi nhiệt độ vượt quá một ngưỡng xác định và giữ ngắt đó cho đến khi nhiệt độ giảm xuống dưới ngưỡng.
- Ngắt theo cạnh (Edge-triggered interrupt):

Ngắt theo cạnh xảy ra khi tín hiệu ngắt thay đổi trạng thái từ mức logic này sang mức logic khác, ví dụ từ mức thấp sang mức cao (cạnh lên) hoặc từ mức cao sang mức thấp (cạnh xuống).
Ngắt chỉ được kích hoạt khi có sự chuyển đổi trạng thái, không phụ thuộc vào thời gian tín hiệu giữ ở mức đó. Điều này có nghĩa là ngắt chỉ xảy ra tại thời điểm chuyển đổi.
Ví dụ: Một nút nhấn có thể kích hoạt ngắt cạnh lên khi nút được nhấn (từ mức thấp lên mức cao) và không yêu cầu ngắt cho đến khi có lần nhấn tiếp theo.

Sự khác nhau chính:

Ngắt theo mức liên tục yêu cầu CPU xử lý ngắt miễn là điều kiện mức logic được duy trì.
Ngắt theo cạnh chỉ yêu cầu xử lý ngắt tại thời điểm chuyển đổi trạng thái và không yêu cầu ngắt liên tục.

Ứng dụng:

Ngắt theo mức thường được sử dụng cho các tình huống yêu cầu giám sát liên tục.
Ngắt theo cạnh thường được sử dụng cho các sự kiện ngắn hạn, chẳng hạn như phát hiện cạnh lên hoặc cạnh xuống trong các tín hiệu số.
</details>

## Bài 4: Communication Protocols
<details>

</details>
