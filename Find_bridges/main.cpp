//Oleg Krylov 9.10.19
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
int T = 0;
long int Count = 0;
vector<int> answer;
std::map <pair<int,int>,int> t;

void dfs (int v, vector<vector<int>> &graph, vector<bool> &used,vector<int> &t_in, vector<int> &t_up, int p = -1 ) {
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
            dfs(to, graph, used, t_in, t_up, v);
            t_up[v] = min(t_up[v], t_up[to]);

        }

        if (t_up[to] > t_in[v]){
            int x;
            x = t[make_pair(v, to)];
            if(x == 0)
                x = t[make_pair(to, v)];


            answer.push_back(x);
            Count++;
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

    vector<bool> used(n);
    vector<int> t_in(n);
    vector<int> t_up(n);

    for (int i = 0; i < rib; i++){
        cin >> a >> b;

        Vector3D[a-1].push_back(b-1);
        Vector3D[b-1].push_back(a-1);
        t[make_pair(a-1, b-1)] = i + 1;
    }




    for(int i = 0; i<n;i++) {
        if(!used[i]) {
            dfs(i, Vector3D, used, t_up, t_in, -1);
        }
    }


    cout<<Count<<endl;
    std::sort(answer.begin(), answer.end(), std::greater<int>());
    reverse(answer.begin(), answer.end());
    for(int i=0;i < answer.size();i++)
    {
        cout<<answer[i]<<" ";
    }


}