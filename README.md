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
  
**SPI**
Là chuẩn giao tiếp nối tiếp đòng bộ. Có thể hoạt động ở chế độ song công (truyền - nhận cùng lúc). Sử dụng 4 dây giao tiếp (SCK, MOSI, MISO, CS)

SCK (Serial Clock): Thiết bị Master tạo xung tín hiệu SCK và cung cấp cho Slave. Xung này có chức năng giữ nhịp cho giao tiếp SPI. Mỗi nhịp trên chân SCK báo 1 bit dữ liệu đến hoặc đi → Quá trình ít bị lỗi và tốc độ truyền cao.

MISO (Master Input Slave Output): Tín hiệu tạo bởi thiết bị Slave và nhận bởi thiết bị Master. Đường MISO phải được kết nối giữa thiết bị Master và Slave.

MOSI (Master Output Slave Input): Tín hiệu tạo bởi thiết bị Master và nhận bởi thiết bị Slave. Đường MOSI phải được kết nối giữa thiết bị Master và Slave.

SS (Slave Select): Chọn thiết bị Slave cụ thể để giao tiếp. Để chọn Slave giao tiếp thiết bị Master chủ động kéo đường SS tương ứng xuống mức 0 (Low). Chân này đôi khi còn được gọi là CS (Chip Select). Chân SS của vi điều khiển (Master) có thể được người dùng tạo bằng cách cấu hình 1 chân GPIO bất kỳ chế độ Output.

SPI cho phép 1 MCU chủ giao tiếp với nhiều thiết bị tớ thông qua tín hiệu chọn thiết bị SS. Các thiết bị tớ chỉ có thể có 1 chân CS để nhận tín hiệu chọn này, tuy nhiên thiết bị chủ có thể có nhiều hơn 1 chân SS để chọn từng thiết bị muốn giao tiếp.
</details>

## Bài 5: SPI SW & SPI HW
<details>

</details>

## Bài 6: I2C SW & I2C HW
<details>

</details>

## Bài 7: UART SW & UART HW
<details>

</details>

## Bài 8: EXTI, NGẮT TIMER, NGẮT TRUYỀN THÔNG
<details>

</details>

## Bài 9: ADC
<details>

**Analog to Digital Converter (ADC)** là một thiết bị hoặc mạch điện tử chuyển đổi tín hiệu analog thành tín hiệu digital. ADC cho phép các thiết bị kỹ thuật số làm việc với các tín hiệu từ thế giới thực như âm thanh, ánh sáng, nhiệt độ, và áp suất.

**Các khái niệm cơ bản**

**1. Tín hiệu Analog và Digital**
- Tín hiệu Analog: Là tín hiệu có giá trị thay đổi liên tục theo thời gian, ví dụ như điện áp, dòng điện, âm thanh.
- Tín hiệu Digital: Là tín hiệu chỉ có các giá trị rời rạc, thường là 0 và 1 trong hệ nhị phân.
**2. Quá trình chuyển đổi**
ADC thực hiện chuyển đổi qua ba bước chính:

**Lấy mẫu (Sampling):** Tín hiệu analog được lấy mẫu tại các khoảng thời gian giống nhau.
Giữ và chuyển đổi (Hold and Convert): Mỗi mẫu được giữ lại và chuyển đổi thành giá trị digital tương ứng.
Lượng tử hóa (Quantization): Giá trị analog được làm tròn đến giá trị digital gần nhất.
Các loại ADC
Có nhiều loại ADC khác nhau, mỗi loại có ưu và nhược điểm riêng:

1. Flash ADC
Nguyên lý: Sử dụng một mạng lưới các so sánh điện áp để chuyển đổi tín hiệu trong một bước duy nhất.
Ưu điểm: Tốc độ chuyển đổi rất nhanh.
Nhược điểm: Yêu cầu nhiều linh kiện hơn và tiêu thụ nhiều năng lượng.
2. Successive Approximation Register (SAR) ADC
Nguyên lý: Sử dụng một mạch so sánh để từng bước tìm ra giá trị digital tương ứng.
Ưu điểm: Tốc độ chuyển đổi vừa phải, độ chính xác cao.
Nhược điểm: Phức tạp hơn và có thể chậm hơn Flash ADC.
3. Sigma-Delta ADC
Nguyên lý: Sử dụng phương pháp lấy mẫu quá mức và lọc để đạt được độ chính xác cao.
Ưu điểm: Độ chính xác rất cao và tiêu thụ năng lượng thấp.
Nhược điểm: Tốc độ chuyển đổi chậm hơn so với các loại khác.
**Các thông số quan trọng của ADC**

**1. Độ phân giải (Resolution)**

**Định nghĩa:** là số bit dùng để mã hóa ADC.

**Ý nghĩa:** Độ phân giải càng cao, tín hiệu digital càng chính xác. Ví dụ, một ADC 8-bit có thể biểu diễn 256 mức tín hiệu khác nhau, trong khi một ADC 16-bit có thể biểu diễn 65536 mức.

**2. Tốc độ lấy mẫu (Sampling Rate)**
**Định nghĩa:** Là số lần ADC lấy mẫu tín hiệu analog mỗi giây, đo bằng Hertz (Hz).

**Ý nghĩa:** Tốc độ lấy mẫu càng cao, khả năng theo dõi tín hiệu nhanh và phức tạp càng tốt.

**3. Độ chính xác (Accuracy)**

**Định nghĩa:** Là mức độ chính xác của giá trị digital so với giá trị analog thực tế.

**Ý nghĩa:** Độ chính xác cao đảm bảo rằng tín hiệu digital gần đúng với tín hiệu analog gốc.

4. Dải động (Dynamic Range)
Định nghĩa: Là tỷ số giữa tín hiệu lớn nhất có thể đo và tín hiệu nhỏ nhất có thể đo.
Ý nghĩa: Dải động rộng giúp ADC có thể xử lý các tín hiệu với biên độ khác nhau mà không bị bão hòa.
</details>
