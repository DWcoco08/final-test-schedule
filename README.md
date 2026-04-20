# 🎓 Exam Scheduling System (Xếp Lịch Thi)

## 📌 Giới thiệu

Dự án này giải quyết bài toán **xếp lịch thi** sao cho không có sinh viên nào phải thi 2 môn cùng lúc.

Bài toán được mô hình hóa thành **bài toán tô màu đồ thị (Graph Coloring Problem)**:

* Mỗi môn học → 1 đỉnh
* Nếu 2 môn có sinh viên học chung → có cạnh (xung đột)
* Mỗi màu → 1 ca thi

🎯 Mục tiêu:
Tối thiểu số ca thi (số màu) sao cho không có xung đột.

---

## ⚙️ Các thuật toán sử dụng

### 1. 🔍 Backtracking

* Duyệt toàn bộ khả năng
* Tìm nghiệm tối ưu (ít ca nhất)
* Độ phức tạp cao → chậm với dữ liệu lớn

---

### 2. 🧠 Dynamic Programming (Independent Set)

* Tìm tập môn **không xung đột lớn nhất**
* Gán từng nhóm vào từng ca thi
* Nhanh hơn Backtracking

---

### 3. ⚡ Greedy (Tham lam)

* Sắp xếp môn theo số xung đột (bậc)
* Gán vào ca sớm nhất có thể
* Nhanh nhất nhưng có thể không tối ưu

---

## 📥 Cấu trúc Input

```
t                      // số test case
ns nm                  // số sinh viên, số môn

Với mỗi sinh viên:
k                      // số môn học
m1 m2 ... mk           // danh sách môn
```

---

## 📤 Output

* Số ca thi
* Danh sách môn trong từng ca
* Thời gian chạy của từng thuật toán

---

## 📊 Ví dụ

### Input

```
1
3 4
2 1 2
2 2 3
2 3 4
```

### Output

```
--- Backtracking ---
So ca: 2
Ca 1: 1 3
Ca 2: 2 4
Time: 1200 us

--- Dynamic Programming ---
So ca: 2
Time: 300 us

--- Greedy ---
So ca: 3
Time: 50 us
```

---

## ⏱️ Đo thời gian

Sử dụng thư viện:

```cpp
#include <chrono>
```

Đo bằng:

```cpp
auto start = high_resolution_clock::now();
auto end = high_resolution_clock::now();
```

Đơn vị:

* microseconds (µs)
* milliseconds (ms)

---

## 📈 So sánh thuật toán

| Thuật toán          | Độ chính xác | Tốc độ        |
| ------------------- | ------------ | ------------- |
| Backtracking        | ⭐⭐⭐⭐⭐        | ❌ Chậm        |
| Dynamic Programming | ⭐⭐⭐⭐         | ⚠️ Trung bình |
| Greedy              | ⭐⭐           | ⚡ Rất nhanh   |

---

## 🧩 Ý tưởng chính

1. Xây dựng **ma trận xung đột**
2. Áp dụng thuật toán tô màu đồ thị
3. So sánh kết quả và thời gian

---

## 🚀 Hướng phát triển

* Áp dụng **AI / Machine Learning** để dự đoán lịch tốt hơn
* Tối ưu bằng **Genetic Algorithm**
* Giao diện GUI (Tkinter / Web)
* Xuất file kết quả (.txt, .csv)

---

## 👨‍💻 Công nghệ sử dụng

* C++
* STL (vector, algorithm)
* chrono (đo thời gian)

---

## 📌 Ghi chú

* Input môn học bắt đầu từ **1**
* Chuyển về index **0** khi xử lý
* Dữ liệu lớn → nên tránh Backtracking

---

✨ Đây là một bài toán kinh điển trong:

* Lập lịch (Scheduling)
* Tối ưu tổ hợp (Combinatorial Optimization)
* Lý thuyết đồ thị (Graph Theory)

---
