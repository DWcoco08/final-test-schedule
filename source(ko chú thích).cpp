#include <bits/stdc++.h>
using namespace std;

int ns, nm;
vector<vector<int>> a, c;

void rd() {
    cin >> ns >> nm;
    a.resize(ns);
    for (int i = 0; i < ns; i++) {
        int k; cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; j++) 
            cin >> a[i][j];
    }
}

void bd() {
    c.assign(nm, vector<int>(nm, 0));
    for (auto& s : a) {
        for (int i = 0; i < s.size(); i++) {
            for (int j = i+1; j < s.size(); j++) {
                int x = s[i]-1;
                int y = s[j]-1;
                c[x][y] = c[y][x] = 1;
            }
        }
    }
}

bool ok(int u, int col, vector<int>& s) {
    for (int i = 0; i < nm; i++)
        if (c[u][i] && s[i] == col)
            return false;
    return true;
}

int best;
vector<int> ans;

void bt(int u, vector<int>& s, int used) {
    if (u == nm) {
        if (used < best) {
            best = used;
            ans = s;
        }
        return;
    }

    for (int col = 1; col <= best; col++) {
        if (ok(u, col, s)) {
            s[u] = col;
            bt(u+1, s, max(used, col));
            s[u] = 0;
        }
    }
}

vector<int> solveBT() {
    vector<int> s(nm, 0);
    best = nm;
    bt(0, s, 0);
    return ans;
}

vector<bool> memo;

void findIndSet(int u, vector<bool> &curr, vector<bool> &assigned) {
    if (u == nm) {
        int currSize = count(curr.begin(), curr.end(), true);
        int memoSize = count(memo.begin(), memo.end(), true);
        if (currSize > memoSize)
            memo = curr;
        return;
    }

    if (assigned[u]) {
        findIndSet(u + 1, curr, assigned);
        return;
    }

    bool canAdd = true;
    for (int i = 0; i < nm; i++)
        if (curr[i] && c[u][i]) {
            canAdd = false;
            break;
        }

    if (canAdd) {
        curr[u] = true;
        findIndSet(u + 1, curr, assigned);
        curr[u] = false;
    }

    findIndSet(u + 1, curr, assigned);
}

vector<int> solveDP() {
    vector<int> result(nm, 0);
    vector<bool> assigned(nm, false);
    int color = 1;

    while (true) {
        memo.assign(nm, false);
        vector<bool> curr(nm, false);
        findIndSet(0, curr, assigned);

        if (count(memo.begin(), memo.end(), true) == 0)
            break;

        for (int i = 0; i < nm; i++)
            if (memo[i]) {
                result[i] = color;
                assigned[i] = true;
            }

        color++;
    }
    return result;
}

vector<int> solveGreedy() {
    vector<int> result(nm, 0), degree(nm, 0);

    for (int i = 0; i < nm; i++)
        for (int j = 0; j < nm; j++)
            if (c[i][j]) degree[i]++;

    vector<pair<int,int>> sorted;
    for (int i = 0; i < nm; i++)
        sorted.push_back({degree[i], i});

    sort(sorted.rbegin(), sorted.rend());

    for (auto &p : sorted) {
        int u = p.second;
        int col = 1;
        while (!ok(u, col, result)) col++;
        result[u] = col;
    }

    return result;
}

void pl(vector<int> &s) {
    int mx = *max_element(s.begin(), s.end());
    cout << "So ca: " << mx << "\n";

    for (int i = 1; i <= mx; i++) {
        cout << "Ca " << i << ": ";
        for (int j = 0; j < nm; j++)
            if (s[j] == i)
                cout << j+1 << " ";
        cout << "\n";
    }
}

int main() {
    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        cout << "==== TEST " << tc << " ====\n";

        a.clear(); c.clear();
        ans.clear();

        rd();
        bd();

        cout << "\nBacktracking\n";
        pl(solveBT());

        cout << "\nDynamic Programming\n";
        pl(solveDP());

        cout << "\nGreedy\n";
        pl(solveGreedy());
    }
}
