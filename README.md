# Crossing Road

## Cài đặt

- Clone về thôi có file `.sln` rồi bật là tự lên thôi
- Môi trường thì dùng `Visual Studio 2019`
- Muốn sướng hơn thì dùng `Visual Assist X` để đời bớt khổ hơn (cài vào thì chạy nặng hơn tí)(Có thể nói t để lấy bản crack)

## Vài điều lưu ý

- `Project Game` là chính, `Project Testing` và `Project TestingGame` để test code và mấy design pattern (chắc khi nào bỏ 2 thằng đó để khỏi bị conflict) 
- Mới phần sườn, còn rất nhiều thứ cần làm trong `TODO`
- Chú ý ghi chú cẩn thận vì là project team, không phải cá nhân, tiện hiểu code (Chắc khi nào sẽ thảo luận về phần `Coding Convention` và phần git sau)
- Nhớ commit ghi rõ làm cái gì là được để git log đọc cho dễ :D

- Chắc khi nào học thêm cái `branch` với `pull request` lại nữa
- À mà đừng commit nhiều lắm, chắc phải học thêm cái `rebase`

- Have Fun Coding :3 

## Về thuật toán

- Chúng ta có 2 thread là `main` và `SubThread`(Chắc phải đổi tên lại)
 - Thread main để bắt Input Key và 
 - Thread SubThread để vẽ game là chính

- Class chính là Game
 - Game sẽ gồm 2 `Vector Animal và Vehicle` chứa thông tin về vị trí của tụi nó
 - Một thằng `player` để điều khiển
 - Hai cái `PrevBuffer` và `Buffer` để có thể vẽ lên console (Kỹ thuật là double buffering) tránh trường hợp bọn nó vẽ lại nhiều quá dẫn đến bị sọc chớp chớp?
 - Một biến `level` để lưu level thôi

- Class phụ là Player và mấy cái xe + động vật

- File `Win32Helper` chứa hàm về Win32 liên quan đến `Console` và mấy thứ như `Màu, GotoXY` và `ClearConsoleScreen`(đừng dùng system("cls") vì nó rất chậm) 

## TODO:

- [X] Dead & Finish level
- [X] Hiện sprite
- [ ] Gen level (Same lane but more Car and Animal and faster?)(Either that or the thing can teleport)
- [ ] Menu
- [X] Pause
- [ ] Save file/Load file
- [X] Tạm dừng các xe
- [ ] Xử lý hiệu ứng
- [ ] Giao diện trò chơi
- [ ] Thêm nhạc
