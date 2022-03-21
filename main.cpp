#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdio>

using namespace std;

const bool COUNT_ALL_TIME = false;

const int MAX_N = 10000;

vector <int> vec[MAX_N], answer;
bool edge_is_used_arr[MAX_N][MAX_N], used[MAX_N];
int n, m = 0;

bool edge_is_used(int v1, int v2){
    return edge_is_used_arr[min(v1, v2)][max(v1, v2)];
}

void set_edge_used(int v1, int v2, bool val){
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

void solve(const string& input_filename){

    fill(used, used + MAX_N, false);
    for (int i = 0; i < MAX_N; i++){
        fill(edge_is_used_arr[i], edge_is_used_arr[i] + MAX_N, false);
        vec[i].clear();
    }

    int start_time = clock();

    ifstream fin;
    fin.open(input_filename);
    freopen("C:\\Users\\vmn3w\\CLionProjects\\eiler\\output.txt", "w", stdout);

    fin >> n;

    if (n == 1){
        cout << "Cycle";
        return ;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){
            int q;
            fin >> q;
            if (q) {
                vec[i].push_back(j);
                m += 1;
            }
        }

    m /= 2;

    if (!COUNT_ALL_TIME)
        start_time = clock();

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
                return ;
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
    cerr << (double)(end_time - start_time) / CLOCKS_PER_SEC;

    fin.close();
}

int main() {

    for (int i = 10; i <= 940; i += 10) {
        cerr << i << ")\t";
        for (int j = 1; j <= 5; j++) {

            solve("C:\\Users\\vmn3w\\CLionProjects\\eiler\\tests\\" + to_string(i) + "-" + to_string(j) + "-0.txt");
            cerr << " ";
            solve("C:\\Users\\vmn3w\\CLionProjects\\eiler\\tests\\" + to_string(i) + "-" + to_string(j) + "-1.txt");
            cerr << "\t";
        }
        cerr << endl;
    }
    solve("C:\\Users\\vmn3w\\CLionProjects\\eiler\\tests\\940-4-1.txt");

    return 0;
}
