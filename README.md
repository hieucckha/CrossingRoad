# Crossing Road

## Logic game

- Chia thành nhiều module:

  - Các enemy như Bird, Dinosaur, Car, Truck được kế thừa từ base class Enemy
  - Chia thành mỗi hàng độc lập với nhau, có hàm chứa những hàng đó lại, ban đâu thì `OneRow` -> `EmemyRow` (vector chứa các `OneRow`)
  - Sử dụng double buffer, trong class `Scene` được tạo từ class `Pixel` chứa thông tin nội dùng, foreground, background
  - Class Game sẽ chứa tất cả những thứ trên, có 3 thằng chính:
    - Player: Điều kiển về player
    - EnemyRow: Điều kiển về Enemy trên mỗi row
    - Scene: Vẽ những thứ trên lên console
  - Hàm va chạm sẽ được check bởi `Player`, khi mà player di chuyển hoặc khi mà trên hàng mà player đang đứng các xe di chuyển

## TODO

- [x] Thêm chiều ngược lại của các hình
- [x] Đưa các hình vẽ vào code
- [x] Border cho khung game
- [x] Viết lại cách render hình, cho tất cả qua buffer rồi vẽ buffer
- [x] Thêm thông số hàng, vị trí hàng khi người chơi đang đứng -> Khi mà check va chạm chỉ cần check trong cái hàng đó thôi
- [x] Thêm row, thêm entity chạy qua lại
- [x] Viết cách gen của mỗi level
  - [x] Speed ->
  - [x] Số lượng enemy của mỗi hàng (hay tổng số enemy trên map rồi chia đều cho các row or random)
- [x] Viết cách gen entity của mỗi hàng
  - [x] Gen Random|Linear -> Random thì ngầu nhiên trên màn hình và linear thì sẽ xuất hiện từ trong border đi ra
- [x] Thêm thôgn tin level, hướng dẫn di chuyển
- [x] Traffic Light
- [x] Viết lại hàm check va chạm
- [x] Pause/Resume Game
- [x] Thêm setting vào trong menu
- [ ] Hiệu ứng va chạm
- [ ] Chỉnh lại speed và thời gian chờ phù hợp khi bật qua `Mode Release`
- [ ] Chỉnh lại chữ trong trong menu chính cho đẹp hơn
