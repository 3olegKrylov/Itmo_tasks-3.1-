//Oleg Krylov 9.10.19
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
int T = 0;
long int Count = 0;
vector<int> answer;

vector<int> t_in;
vector<int> t_up;


void dfs (int v, vector<vector<int>> &graph, vector<bool> &used, int p = -1 ) {
    used[v] = true;
    bool isTrue = false;
    t_in[v]= t_up[v]=T++;
    int children = 0;
    for (int i=0; i < graph[v].size(); ++i) {
        int to;

        to = graph[v][i];
       // cout<<"to = "<<to<<endl;
        if(to == p)
            continue;
        if(used[to])
          //  cout<<"used "<<endl;
            t_up[v] = min(t_up[v], t_in[to]);
           // cout<<" v="<<v<<"   ___ t_up[v]="<<t_up[v]<<endl;
        if(!used[to]){
            //cout<<"!used "<<endl;
            dfs(to, graph, used, v);
            t_up[v] = min(t_up[v], t_up[to]);
            //cout<<"!used v="<<v<<"   ___ t_up[v]="<<t_up[v]<<endl;

            if (t_up[to] >= t_in[v] && p != -1){
               isTrue = true;
            }
            children++;

        }

    }

    if (p == -1 && children > 1 ) {
        isTrue = true;
    }
    if(isTrue){
        answer.push_back(v + 1);
        Count++;
    }
}


int main() {
    int n;
    long int rib;
    int a, b;

    cin >> n >> rib;
    vector<vector<int>> Vector3D;
    Vector3D.resize(n+1);

    t_in.resize(n+1);
    t_up.resize(n+1);
    vector<bool> used(n);

    for (int i = 0; i < rib; i++){
        cin >> a >> b;
        Vector3D[a-1].push_back(b-1);
        Vector3D[b-1].push_back(a-1);
    }




   for(int i = 0; i<n;i++) {
        if(!used[i]) {
            dfs(i, Vector3D, used, -1);
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