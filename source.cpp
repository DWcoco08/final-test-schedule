#include <bits/stdc++.h>
using namespace std;

int ns, nm;               // ns: số sinh viên, nm: số môn
vector<vector<int>> a, c; // a: danh sách SV, c: ma trận xung đột

// ===== ĐỌC INPUT =====
void rd()
{
    cin >> ns >> nm; // nhập số SV và số môn
    a.resize(ns);

    for (int i = 0; i < ns; i++)
    {
        int k;
        cin >> k; // số môn SV i học
        a[i].resize(k);
        for (int j = 0; j < k; j++)
            cin >> a[i][j]; // danh sách môn
    }
}

// ===== XÂY DỰNG MA TRẬN XUNG ĐỘT =====
void bd()
{
    c.assign(nm, vector<int>(nm, 0)); // khởi tạo 0

    for (auto &s : a) // duyệt từng SV
        for (int i = 0; i < s.size(); i++)
            for (int j = i + 1; j < s.size(); j++)
            {
                int x = s[i] - 1; // chuyển về index 0
                int y = s[j] - 1;
                c[x][y] = c[y][x] = 1; // 2 môn không thi cùng ca
            }
}

// ===== KIỂM TRA CÓ XẾP ĐƯỢC KHÔNG =====
bool ok(int u, int col, vector<int> &s)
{
    for (int i = 0; i < nm; i++)
        if (c[u][i] && s[i] == col) // nếu xung đột và cùng ca
            return false;
    return true;
}

// ===== BACKTRACKING =====
int best;
vector<int> ans;

void bt(int u, vector<int> &s, int used)
{
    if (u == nm)
    { // đã xếp hết môn
        if (used < best)
        {
            best = used; // cập nhật số ca tốt nhất
            ans = s;
        }
        return;
    }

    for (int col = 1; col <= best; col++)
    {
        if (ok(u, col, s))
        {
            s[u] = col;
            bt(u + 1, s, max(used, col)); // thử tiếp
            s[u] = 0;                     // quay lui
        }
    }
}

vector<int> solveBT()
{
    vector<int> s(nm, 0);
    best = nm; // tối đa nm ca
    bt(0, s, 0);
    return ans;
}

// ===== QUY HOẠCH ĐỘNG (TÌM INDEPENDENT SET) =====
vector<bool> memo;
int maxSize;

void findIndSet(int u, vector<bool> &curr, vector<bool> &assigned)
{
    if (u == nm)
    {                     // duyệt hết toàn bộ
        int currSize = 0; // đếm số phần tử trong curr
        for (int i = 0; i < nm; i++)
            if (curr[i])
                currSize++;

        int memoSize = 0; // đếm số phần tử trong memo
        for (int i = 0; i < nm; i++)
            if (memo[i])
                memoSize++;

        if (currSize > memoSize)
        {
            memo = curr; // cập nhật tập độc lập lớn nhất
        }
        return;
    }

    if (assigned[u])
    { // nếu đã gán rồi, skip
        findIndSet(u + 1, curr, assigned);
        return;
    }

    // Thử thêm môn u vào tập
    bool canAdd = true;
    for (int i = 0; i < nm; i++)
    {
        if (curr[i] && c[u][i])
        { // nếu xung đột
            canAdd = false;
            break;
        }
    }

    if (canAdd)
    {
        curr[u] = true; // thêm môn u
        findIndSet(u + 1, curr, assigned);
        curr[u] = false; // quay lui
    }

    findIndSet(u + 1, curr, assigned);
}

vector<int> solveDP()
{
    vector<int> result(nm, 0);
    vector<bool> assigned(nm, false);
    int color = 1;

    while (true)
    {
        memo.assign(nm, false); // xóa memo
        vector<bool> curr(nm, false);
        findIndSet(0, curr, assigned);

        bool isEmpty = true; // kiểm tra memo có rỗng không
        for (int i = 0; i < nm; i++)
            if (memo[i])
            {
                isEmpty = false;
                break;
            }

        if (isEmpty)
            break; // không còn môn chưa gán

        for (int i = 0; i < nm; i++)
        {
            if (memo[i])
            {
                result[i] = color; // gán vào ca thi hiện tại
                assigned[i] = true;
            }
        }
        color++;
    }

    return result;
}

// ===== THAM LAM (GREEDY - SẮP XẾP THEO BẬC) =====
vector<int> solveGreedy()
{
    vector<int> result(nm, 0);
    vector<int> degree(nm, 0); // số xung đột của mỗi môn

    // Tính bậc (số xung đột) của mỗi môn
    for (int i = 0; i < nm; i++)
    {
        for (int j = 0; j < nm; j++)
            if (c[i][j]) // nếu xung với j
                degree[i]++;
    }

    // Tạo danh sách sorted: sắp xếp theo bậc giảm dần
    vector<pair<int, int>> sorted; // {bậc, chỉ số môn}
    for (int i = 0; i < nm; i++)
        sorted.push_back({degree[i], i});

    sort(sorted.begin(), sorted.end());    // sort theo bậc tăng
    reverse(sorted.begin(), sorted.end()); // đảo lại thành giảm

    // Gán môn vào ca thi sớm nhất có thể
    for (auto &p : sorted)
    {
        int course = p.second; // chỉ số môn
        int col = 1;           // thử từ ca 1

        while (!ok(course, col, result)) // nếu không được gán vào ca col
            col++;

        result[course] = col; // gán vào ca đầu tiên có thể
    }

    return result;
}

// ===== IN KẾT QUẢ =====
void pl(vector<int> &s)
{
    int mx = 0;
    for (int x : s)
        mx = max(mx, x); // tìm số ca

    cout << "So ca: " << mx << "\n";

    for (int i = 1; i <= mx; i++)
    {
        cout << "Ca " << i << ": ";
        for (int j = 0; j < nm; j++)
            if (s[j] == i)
                cout << j + 1 << " ";
        cout << "\n";
    }
}
