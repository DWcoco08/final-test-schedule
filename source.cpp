#include <bits/stdc++.h>
using namespace std;

int ns, nm;                     // ns: số sinh viên, nm: số môn
vector<vector<int>> a, c;      // a: danh sách SV, c: ma trận xung đột

// ================= ĐỌC DỮ LIỆU =================
void rd(const string& f) {
    ifstream in(f);
    in >> ns >> nm;
    a.resize(ns);
    for (int i = 0; i < ns; i++) {
        int k; in >> k;        // số môn SV i học
        a[i].resize(k);
        for (int j = 0; j < k; j++) 
            in >> a[i][j];     // danh sách môn
    }
}

// ================= BUILD CONFLICT =================
void bd() {
    c.assign(nm, vector<int>(nm, 0)); // khởi tạo ma trận 0

    for (auto& s : a) {               // duyệt từng sinh viên
        for (int i = 0; i < s.size(); i++) {
            for (int j = i+1; j < s.size(); j++) {
                int x = s[i]-1;       // chuyển về index 0
                int y = s[j]-1;
                c[x][y] = c[y][x] = 1; // 2 môn xung đột
            }
        }
    }
}

// ================= KIỂM TRA HỢP LỆ =================
bool ok(int u, int col, vector<int>& s) {
    for (int i = 0; i < nm; i++)
        if (c[u][i] && s[i] == col)   // nếu xung đột và cùng ca
            return false;
    return true;
}

// ================= BACKTRACKING =================
int best;
vector<int> ans;

void bt(int u, vector<int>& s, int used) {
    if (u == nm) {                   // đã gán hết môn
        if (used < best) {
            best = used;
            ans = s;                 // lưu lời giải tốt nhất
        }
        return;
    }

    for (int col = 1; col <= best; col++) {
        if (ok(u, col, s)) {
            s[u] = col;
            bt(u+1, s, max(used, col)); // cập nhật số ca đã dùng
            s[u] = 0;                   // quay lui
        }
    }
}

vector<int> solveBT() {
    vector<int> s(nm, 0);
    best = nm;                        // tối đa nm ca
    bt(0, s, 0);
    return ans;
}

// ================= IN LỊCH =================
void pl(vector<int>& s) {
    for (int i = 0; i < nm; i++)
        cout << "M" << i+1 << " -> C" << s[i] << "\n";
}
