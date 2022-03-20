#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdio>

using namespace std;

const int MAX_N = 10000;

vector <int> vec[MAX_N], answer;
bool edge_is_used_arr[MAX_N][MAX_N], used[MAX_N];
int n, m = 0;

bool edge_is_used(int v1, int v2){
    return edge_is_used_arr[min(v1, v2)][max(v1, v2)];
}

bool set_edge_used(int v1, int v2, bool val){
    edge_is_used_arr[min(v1, v2)][max(v1, v2)] = val;
}

void dfs(int v, int target){
    if (used[v] || target != -1 && used[target])
        return;

    used[v] = true;
    for (int to : vec[v])
        if (!edge_is_used(v, to))
            dfs(to, target);
}

bool bridge(int v1, int v2){
    set_edge_used(v1, v2, true);
    fill(used, used + n + 1, false);
    dfs(v1, v2);
    set_edge_used(v1, v2, false);
    return !used[v2];
}

bool rec(int v);

bool rec_to(int v, int to){
    set_edge_used(v, to, true);
    m--;
    answer.push_back(to);
    return rec(to);
}

bool rec(int v){
    if (m == 0)
        return true;

    int most_v = -1;

    for (int to : vec[v]) {
        if (!edge_is_used(v, to)) {
            if (!bridge(v, to)) {
                return rec_to(v, to);
            } else
                most_v = to;
        }
    }
    if (most_v == -1)
        return false;

    return rec_to(v, most_v);
}

int main() {
    int start_time = clock();

    freopen("C:\\Users\\vmn3w\\CLionProjects\\eiler\\input.txt", "r", stdin); // redirects standard input
    freopen("C:\\Users\\vmn3w\\CLionProjects\\eiler\\output.txt", "w", stdout);

    cin >> n;

    if (n == 1){
        cout << "Cycle";
        return 0;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){
            int q;
            cin >> q;
            if (q) {
                vec[i].push_back(j);
                m += 1;
            }
        }

//    for (int i = 1; i <= n; i++) {
//        for (int j: vec[i])
//            cout << j << " ";
//        cout << endl;
//    }

    m /= 2;

    vector <int> odd;
    for (int i = 1; i <= n; i++)
        if (vec[i].size() % 2 == 1)
            odd.push_back(i);

    if (odd.empty()){
        int start_v = 1;

        for (int v = 1; v <= n; v++)
            if (!vec[v].empty()){
                dfs(v, -1);
                start_v = v;
                break;
            }

        for (int v = 1; v <= n; v++)
            if (!used[v] && !vec[v].empty()){
                cout << "No"; // У графа 2 или более компоненты связности
                return 0;
            }

        answer.push_back(start_v);
        if (rec(start_v)){
            cout << "Cycle\n";
            for (int i = 0; i < answer.size() - 1; i++)
                cout << answer[i] << " ";
        }
        else
            cout << "No";
    }
    else if (odd.size() == 2){
        answer.push_back(odd[0]);
        if (rec(odd[0])){
            cout << "Chain\n";
            for (int i : answer)
                cout << i << " ";
        }
        else
            cout << "No";
    }
    else
        cout << "No";

    int end_time = clock();
    cerr << end_time - start_time << endl;
    cerr << "Time: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << " seconds";

    return 0;
}
