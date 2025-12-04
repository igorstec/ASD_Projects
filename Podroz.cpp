#include <iostream>
#include <list>
#include <cmath>
#include <vector>
using namespace std;

int dfs_find_fathers(int node, int parent, int level, vector<vector<int>>& graph, vector<vector<int>>& log_fathers, vector<int> & levels) {
    log_fathers[node].push_back(parent);
    levels[node] = level;
    int j=0;
    while(log_fathers[log_fathers[node][j/2]].size() > j/2) {
        int father = log_fathers[log_fathers[node][j/2]][j/2];
        if(father != 0)
            log_fathers[node].push_back(father);
        j+=2;
    }
    for(int neighbor : graph[node]) {
        if(neighbor != parent) {
            dfs_find_fathers(neighbor, node, level+1, graph, log_fathers, levels);
        }
    }
    return 0;
}

int count_lca(int a, int b, vector<vector<int>>& log_fathers, vector<int>& levels) {
    if(a==b) return 0;
    int result = 0;
    //wyrownaj poziom a i b
    while(levels[b] > levels[a]) {
        int j = levels[b]-levels[a];
        b = log_fathers[b][(int)log2(j)];
        result+= (1 << (int)log2(j));
    }
    while(levels[a] > levels[b]) {
        int j = levels[a]-levels[b];
        a = log_fathers[a][(int)log2(j)];
        result+= (1 << (int)log2(j));
    }

     // cout << "Po wyrownaniu a: " << a << " b: " << b << endl;
     // cout << "Poziomy a: " << levels[a] << " b: " << levels[b] << endl;
     // cout << "Aktualny reasult: " << result << endl;
    // fflush(stdout);
    //a i b na tym samym poziomie
    if(a==b) {
        // cout<<"Znaleziono LCA: "<<a<<endl;
        return result;
    }


    while(log_fathers[a][0]!=log_fathers[b][0]) {
        int search_dist = (int)log_fathers[a].size()-1;
        while(log_fathers[a][search_dist] == log_fathers[b][search_dist]) {
            search_dist--;
        }
        a = log_fathers[a][search_dist];
        b = log_fathers[b][search_dist];
        // cout<<"Podnosze a do "<<a<<" i b do "<<b<<endl;
        // fflush(stdout);
        //cout<<"Znaleziono rozbieznosc na odleglosci "<<search_dist<<endl;
        result += (1 << search_dist)*2;
    }
    result += 2;
    return result;
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;


    // Graf jako lista sąsiedztwa (indeksowanie od 1)
    vector<vector<int>> graph(n + 1);
    
    // Wczytanie n-1 dróg
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector log_fathers(n+1, vector<int>());
    vector<int> levels(n+1, 0);
    // Budowanie tablicy ojców dla każdego wierzchołka gdzie i-ty to ojciec 2^i
    dfs_find_fathers(1, 0, 0, graph, log_fathers, levels);

    // Wczytanie q zapytań
    for (int i = 0; i < q; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        int result = 0;
        result+=count_lca(a, b, log_fathers, levels);
        result+=count_lca(b, c, log_fathers, levels);
        result+=count_lca(c, a, log_fathers, levels);
        result/=2;
        cout<<result<<endl;
    }
    
    return 0;
}
