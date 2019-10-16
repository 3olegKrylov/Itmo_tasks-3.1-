//Oleg Krylov 9.10.19
 #include <iostream>
#include <vector>
#include <algorithm>
#include <map>


using namespace std;

vector<int> t_in;
vector<int> t_up;
std::map <pair<int,int>,int> t;//номера рёбер
int T = 0;
int maxColor = 0;
vector<int> answer;//тут хроним мосты
int col = 1;
vector<int> ResRib;

void dfs(int v, vector<vector<int>> &graph, vector<bool> &used, int p = -1 ) {
    used[v] = true;
    bool isTrue = false;
    t_in[v]= t_up[v]=T++;
    int children = 0;
    for (int i=0; i < graph[v].size(); ++i) {
        int to;

        to = graph[v][i];
        if(to == p)
            continue;
        if(used[to])

            t_up[v] = min(t_up[v], t_in[to]);

        if(!used[to]){

            dfs(to, graph, used, v);
            t_up[v] = min(t_up[v], t_up[to]);

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
        answer.push_back(v);
    }
}

void dfs2(int color, int v, vector<vector<int>> &graph, vector<bool> &used, int p = -1){
    used[v] = true;
    int loose = false;

    if(p==-1 && graph[v].size()==0)
        maxColor--;

    for(int i = 0; i<graph[v].size(); i++){
        int to = graph[v][i];

             if(v == to){
            int val = t[make_pair(to, v)];
            ResRib[val] = color;
            continue;
        }

        if(to == p)
            continue;
        if(!used[to]){
            if(t_up[to]>=t_in[v] &&(p != -1 || loose)) {
                int newColore = ++maxColor;
                int val = t[make_pair(to, v)];
                ResRib[val] = newColore;

                dfs2(newColore, to, graph, used, v);
            }
            else{
                loose = true;
                int val = t[make_pair(to, v)];
                ResRib[val] = color;
                dfs2(color, to, graph, used, v);
            }
        }
        else{
            if(t_in[to] < t_in[v]){
                int val = t[make_pair(to, v)];
                ResRib[val] = color;
            }
        }
    }


}

    int main() {
    int n;
    int rib;
    int a, b;

    cin >> n >> rib;

    vector<vector<int>> Vector3D(n);
    vector<vector<int>> RibKrat(rib);

    Vector3D.resize(n+1);
    t_in.resize(n+1);
    t_up.resize(n+1);
    ResRib.resize(rib+1);
    for(int i =0 ; i<rib+1; i++)
        ResRib[i] = -1;
    vector<bool> used(n);
    vector<int> num(n);
        int Krat = 0;
    for (int i = 0; i < rib; i++){
        cin >> a >> b;

        for(int j = 0; j<Vector3D[a-1].size();j++){
            if(Vector3D[a-1][j]==(b-1)){
                Krat++;
                int val = t[make_pair(a-1, b-1)];
                RibKrat[val].push_back(i);
            }
        }
        if(Krat == 0) {
            Vector3D[a - 1].push_back(b - 1);
            Vector3D[b - 1].push_back(a - 1);
            t[make_pair(a - 1, b - 1)] = i;
            t[make_pair(b - 1, a - 1)] = i;
        }
        Krat =0;
    }

    for(int i = 0; i<n;i++) {
            if(!used[i]) {
                dfs(i, Vector3D, used,-1);
            }
        }

        vector<bool> used2(n);

    for(int i = 0; i<n;i++) {
        if(!used2[i]) {
           maxColor++;
            dfs2( maxColor, i,Vector3D, used2, -1);
        }
    }

        for (int k = 0; k < RibKrat.size(); ++k) {
            for (int i = 0; i < RibKrat[k].size(); ++i) {
               /* cout<<"k="<<k<<" "<<"i="<<i<<endl;
                cout<<RibKrat[k][i]<<endl;
                cout<<ResRib[k]<<endl;
                cout<<ResRib[RibKrat[k][i]]<<endl;*/
                if(ResRib[RibKrat[k][i]]==-1) {
                    //cout<<"hear"<<endl;
                    ResRib[RibKrat[k][i]] = ResRib[k];
                }
                if(ResRib[k]==-1) {
                    //cout<<"ishere";
                    ResRib[k] = ResRib[RibKrat[k][i]];
                }

            }
        }

    cout<<maxColor<<endl;

    for(int i = 0; i<rib; i++)
        cout<<ResRib[i]<<" ";

}

