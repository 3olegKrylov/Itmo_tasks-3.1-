#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

vector<vector<int>> graph;
vector<vector<int>> Gtrans;
vector<int> order;

set<pair<int,int>> res;
int col = 0;

void dfs1 (int v,  vector<bool> &used, int p = -1 ) {
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        int to;
        to = graph[v][i];

        if (!used[to]) {
            dfs1(to, used, v);
        }
    }
    order.push_back(v);
}

    void dfs2(int feel, int v, vector<int> &Color, int p = -1) {

        Color[v] = feel;
        for (int i = 0; i < Gtrans[v].size(); i++) {
            int to = Gtrans[v][i];

            if (Color[to] == -1) {
                dfs2(feel, to, Color, v);
            }

        }
    }


int main() {
    int n;
    long int rib;
    int a, b;

    cin >> n >> rib;


    graph.resize(n+1);
    Gtrans.resize(n+1);

    vector<bool> used(n+1);
    vector<bool> used2(n+1);
    vector<int> t_in(n+1);
    vector<int> num(n+1);
    vector<int> Color(n+1);

    for(int i = 0; i< n+1; i++)
    {
        Color[i] = -1;
    }

    vector<int> t_up(n+1);

    for (int i = 0; i < rib; i++){
        cin >> a >> b;
            graph[a].push_back(b);
            Gtrans[b].push_back(a);

    }

    for(int i = 1; i<=n;i++) {
        if(!used[i]) {
            dfs1(i, used, -1);
        }
    }
    /*cout<<order.size()<<endl;
    for(int i =0; i<order.size();i++){
        cout<<order[i]<<" ";
    }*/

    for(int i = 1, feel = 0; i<=n;i++) {
        int l = n - i;
       int v = order[l];
       if(Color[v] == -1)
           dfs2(feel++, v, Color, -1);
    }

    for(int i  = 1 ; i<graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++){
            int to = graph[i][j];
            if(Color[i] != Color[to])
                res.insert(make_pair(Color[i], Color[to]));
        }
    }
    cout<<res.size();
}