#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;
vector<tuple<int, int, int>> t;

void build(const vector<int>& a, int v, int tl, int tr) {
    if (tl == tr) {
        if (a[tl] == 1) { // Si es '('
            get<0>(t[v]) = 0; 
            get<1>(t[v]) = 1; 
            get<2>(t[v]) = 0; 
        } else if (a[tl] == -1) { // Si es')'
            get<0>(t[v]) = 0; 
            get<1>(t[v]) = 0; 
            get<2>(t[v]) = 1; 
        }
    } else {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        get<0>(t[v]) = get<0>(t[v * 2]) + get<0>(t[v * 2 + 1]);
        int matches = min(get<1>(t[v * 2]), get<2>(t[v * 2 + 1]));
        get<0>(t[v]) += matches;
        get<1>(t[v]) = get<1>(t[v * 2])+ get<1>(t[v * 2 + 1]) - matches;
        get<2>(t[v]) = get<2>(t[v * 2]) + get<2>(t[v * 2 + 1]) - matches;
    }
}

tuple<int, int, int> query(int v, int tl, int tr, int l, int r) {
    if (l > r) return make_tuple(0, 0, 0);
    if (l == tl && r == tr) return t[v];

    int tm = (tl + tr) / 2;

    tuple<int, int, int> left_res = query(v * 2, tl, tm, l, min(r, tm));
    tuple<int, int, int> right_res = query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    tuple<int, int, int> answer;

    get<0>(answer) = get<0>(left_res) + get<0>(right_res);
    int matches = min(get<1>(left_res), get<2>(right_res));
    get<0>(answer) += matches;

    get<1>(answer) = get<1>(left_res) + get<1>(right_res) - matches;
    get<2>(answer) = get<2>(left_res) + get<2>(right_res) - matches;
    
    return answer;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string A;
    cin >> A;
    int n = A.size();

    if (n == 0) {
        int queries_count;
        cin >> queries_count;
        for (int i = 0; i < queries_count; ++i) {
            int l_q, r_q;
            cin >> l_q >> r_q;
            cout << 0 << endl;
        }
        return 0;
    }

    vector<int> brackets(n);
    for (int i = 0; i < n; i++) {
        if (A[i] == '(')
            brackets[i] = 1;
        else if (A[i] == ')')
            brackets[i] = -1;
    }

    t.resize(4 * n);
    build(brackets, 1, 0, n - 1);

    int queries_count;
    cin >> queries_count;
    int l_q, r_q;
    for (int i = 0; i < queries_count; i++) {
        cin >> l_q >> r_q;
        tuple<int, int, int> result_tuple = query(1, 0, n - 1, l_q - 1, r_q - 1);
        cout << 2 * get<0>(result_tuple) << endl;
    }
    return 0;
}
