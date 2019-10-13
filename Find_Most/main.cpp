//Oleg Krylov 9.10.19
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int T = 0;
long int Count = 0;
struct FINDreb{
    int x;
    int y;
};
vector<FINDreb> answer;
vector<int> kek;

void dfs (int v, vector <int> *graph, vector<bool> &used,vector<int> &t_in, vector<int> &t_up, int p = -1) {
    used[v] = true;
    t_in[v]= t_up[v]=T++;
    for (int i=0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        if(to == p)
            continue;
        if(used[to])
            t_up[v] = min(t_up[v], t_in[to]);
        else {
            dfs(to, graph, used, t_in, t_up, v);
            t_up[v] = min(t_up[v], t_up[to]);
                if (t_up[to] > t_in[v]){
                    answer.push_back({to + 1, v + 1});
                    /*int what=0;
                    /*
                     * for(int i=0; i<graph[to].size();i++){
                        if(graph[to][i] == v) {
                            what++;
                        }
                    }
                    if(what == 1) {
                        answer.push_back({to + 1, v + 1});
                        Count++;
                    }*/
                    //cout<<to+1<<" and "<<v+1<<endl;
                }

        }
    }

}



int main() {
    int n;
    long int rib;
    int a, b;

    cin >> n >> rib;

    vector<int> graph[n+1];
    vector<bool> used(n);
    vector<int> t_in(n);
    vector<int> t_up(n);
    FINDreb Rib[rib+2];


    for (int i = 0; i < rib; i++){ //
        cin >> a >> b;
        graph[a-1].push_back(b-1);
        graph[b-1].push_back(a-1);
        Rib[i+1].x = a;
        Rib[i+1].y = b;
    }

    for (int i=0; i<n; ++i)
        used[i] = false;
    for(int i = 0; i<n;i++) {
        if(!used[i]) {
            dfs(i, graph, used, t_up, t_in, -1);
        }
    }

    cout<<Count<<endl;

    for(int i = 0; i < answer.size();i++){

            for (int j = 1; j <= rib; j++) {

                if ((answer[i].x == Rib[j].x) && (answer[i].y == Rib[j].y) ||
                    (answer[i].x == Rib[j].y) && (answer[i].y == Rib[j].x))
                    kek.push_back(j);
            }
    }
    std::sort(kek.begin(), kek.end(), std::greater<int>());
    reverse(kek.begin(), kek.end());
    for (int k = 0; k < kek.size() ; ++k) {
        cout<<kek[k]<<" ";

    }


}

