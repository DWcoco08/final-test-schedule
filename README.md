# Xếp Lịch Thi Cuối Kỳ — PTTKGT

## Mục tiêu

Xếp lịch thi cho các môn học sao cho **không có sinh viên nào bị trùng ca thi**, đồng thời **tối thiểu số ca thi** cần dùng.

## 3 chiến lược thuật toán

| Thuật toán | Ưu điểm | Nhược điểm |
|---|---|---|
| **Backtracking** | Tìm được lời giải tối ưu | Chậm khi nhiều môn |
| **Greedy** | Rất nhanh | Có thể không tối ưu |
| **DP (bitmask)** | Tối ưu, nhanh hơn backtracking | Chỉ dùng được khi n nhỏ (≲ 20) |

## Cấu trúc dự án

```
├── src/
│   ├── source.cpp                    # Chương trình chính
│   ├── core/                       # Module dùng chung
│   │   ├── scheduler.h             # Struct Course + typedef Schedule
│   │   ├── input.h / input.cpp     # Đọc file + in kết quả
│   │   └── conflict.h / conflict.cpp  # Xây dựng ma trận xung đột
│   └── algorithms/                 # Các thuật toán (mỗi người 1 thuật toán)
│       ├── backtracking/
│       ├── greedy/
│       └── dp/
├── data/                           # File test
│   ├── input.txt
│   └── output.txt
├── build/
└── .gitignore
```

## Cách dùng

### Build
```bash
mkdir -p build
g++ src/main.cpp src/core/*.cpp -std=c++17 -O2 -o build/schedule
```

### Chạy
```bash
./build/schedule
```

## Định dạng file input

```
num_courses  num_students
count  s1 s2 s3 ...
count  s1 s2 ...
...
```

Ví dụ (3 môn, 5 sinh viên):
```
3 5
3 1 2 3
2 2 4
2 3 5
```

## Cách thêm thuật toán

Mỗi thuật toán chỉ cần là **1 hàm** nhận courses + conflict matrix, trả về `Schedule`:

```cpp
// Ví dụ trong algorithms/greedy/greedy.h
Schedule greedy(const vector<Course>& courses, const vector<vector<bool>>& conflict);
```

Rồi gọi trong `main.cpp`:
```cpp
Schedule result = greedy(courses, conflict);
printSchedule(result);
printStatistics(result);
```
