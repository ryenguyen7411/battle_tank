1. Giải nén file bin.rar, đặt tất cả các file có trong file nén vào thư mục bin có đường dẫn "../Game/bin"

2. Mở solution bằng Visual Studio
	+ Bấm chuột phải vào project "Game",chọn Properties.
	+ Configuration Properties -> Debugging -> Working Directory, sửa thành $(ProjectDir)../data
	
3. Bấm Run để chạy chương trình.