#include <iostream>
#include <vector>
#include <algorithm>
#include <map>


using namespace std;

int Color = 0;
int T = 0;
long int Count = -1;
vector<vector<int>> Briges;
vector<pair<int, int>> answer;
int col = 0;
void dfs1 (int v, vector<vector<int>> &graph, vector<bool> &used,vector<int> &t_in, vector<int> &t_up, int p = -1 ) {
    used[v] = true;
    t_in[v]= t_up[v]=T++;
    for (int i=0; i < graph[v].size(); ++i) {
        int to;

        to = graph[v][i];

        if(to == p)
            continue;
        if(used[to])
            t_up[v] = min(t_up[v], t_in[to]);
        if (!used[to]) {
            dfs1(to, graph, used, t_in, t_up, v);
            t_up[v] = min(t_up[v], t_up[to]);

        }

        if (t_up[to] > t_in[v]){
            bool hm = false;
            int co = 0;
            for(int i = 0; i<graph[v].size(); i++){

                if(graph[v][i] == to)
                    co++;
                if(co > 1)
                    hm = true;
            }
            if(!hm){
            Briges[to].push_back(v);
            Briges[v].push_back(to);
            Count++;
            }
        }
    }

}

void dfs2 (int r, int v, vector<int> &num, vector<vector<int>> &graph, vector<bool> &used, int p = -1) {
    int x = r;
    if(col<x)
        col = x;
    num[v] = r;
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        int to;

        to = graph[v][i];

        if (to == p)
            continue;
        if (!used[to]) {
            bool hm = false;
            for(int i = 0; i < Briges[v].size(); i++) {
                if(Briges[v][i] == to) {
                    hm = true;
                }
            }
            if(hm == true){
                Color++;
                dfs2(Color, to,num, graph, used, v);
            }
            else
                dfs2(x, to,num, graph, used, v);
        }
    }
}

    int main() {
    int n;
    long int rib;
    int a, b;

    cin >> n >> rib;
    vector<vector<int>> Vector3D;

    Vector3D.resize(n+1);
    Briges.resize(n+1);

    vector<bool> used(n);
    vector<int> t_in(n);
    vector<int> num(n);

    vector<int> t_up(n);

    for (int i = 0; i < rib; i++){
        cin >> a >> b;

        Vector3D[a-1].push_back(b-1);
        Vector3D[b-1].push_back(a-1);
    }


    for(int i = 0; i<n;i++) {
        if(!used[i]) {
            Color++;
            Count++;
            dfs1(i, Vector3D, used, t_up, t_in, -1);
           // cout<<(Count+1)<<endl;
            vector<bool> used2(n);
            dfs2(Color, i, num, Vector3D, used2, -1);
            Color = col;
        }
    }

    cout<<Count+1<<endl;
    for(int i = 0; i<n; i++)
        cout<<num[i]<<" ";
    
}