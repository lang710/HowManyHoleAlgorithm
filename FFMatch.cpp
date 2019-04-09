#include <iostream>
#include <vector>
using namespace std;

void ford_fulkerson(int g_size,int **graph,int s,int t){
    //cout<<"start"<<endl;
    int **remain,**flow;
    remain=new int*[g_size];
    flow=new int*[g_size];
    int i,j;
    for(i=0;i<g_size;i++) {
        remain[i] = new int[g_size];
        flow[i] = new int[g_size];
    }

    for(i=0;i<g_size;i++)
        for(j=0;j<g_size;j++)
            remain[i][j]=graph[i][j],flow[i][j]=0;

    vector<int> path;
    int visit[g_size];
    int top;
    bool back;
    bool jump=false;
    int bottleneck;
    while(!jump){
        memset(visit,0,sizeof(visit));
        path.clear();
        path.push_back(s);
        while(true){
            top=path.back();
            visit[top]=1;
            //cout<<top<<endl;
            if(top==t)
                break;
            back=true;
            for(i=0;i<g_size;i++) {
                if (remain[top][i] > 0&&visit[i]==0) {
                    path.push_back(i);
                    back=false;
                    break;
                }
            }
            if(back) {
                path.pop_back();
                if (path.empty()) {
                    jump = true;
                    break;
                }
            }
        }

        if(!jump) {
            bottleneck = 0x7fffffff;
            for (i = 0; i < path.size() - 1; i++)
                if (remain[path[i]][path[i + 1]] < bottleneck)
                    bottleneck = remain[path[i]][path[i + 1]];
            //cout << bottleneck << endl;
            for (i = 0; i < path.size() - 1; i++)
                flow[path[i]][path[i + 1]] += bottleneck;
            for (i = 0; i < g_size; i++)
                for (j = 0; j < g_size; j++)
                    if (flow[i][j] > 0) {
                        remain[i][j] = graph[i][j] - flow[i][j];
                        remain[j][i] = flow[i][j];
                    }
        }
    }
    /*
    int max_flow=0;
    for(i=0;i<g_size;i++)
        max_flow+=flow[0][i];
    cout<<max_flow<<endl;
     */
    for(i=1;i<g_size-1;i++)
        for(j=-1;j<g_size-1;j++)
            if (flow[i][j] == 1)
                cout << i << ' ' << j << ' ' << flow[i][j] << endl;

}

int main(){
    int g_size;
    cin>>g_size;
    int **graph=new int*[g_size+2];
    int i,j;
    for(i=0;i<g_size+2;i++)
        graph[i]=new int[g_size+2];
    for(i=0;i<g_size+2;i++)
        for(j=0;j<g_size+2;j++)
            graph[i][j]=0;
    int g1_size,g2_size;
    cin>>g1_size>>g2_size;
    int *g1=new int[g1_size];
    int *g2=new int[g2_size];
    for(i=0;i<g1_size;i++)
        cin>>g1[i];
    for(i=0;i<g2_size;i++)
        cin>>g2[i];
    int left,right;
    bool jump;
    int edges;
    cin>>edges;
    for(i=0;i<edges;i++){
        cin>>left>>right;
        jump=true;
        for(j=0;j<g1_size;j++)
            if(g1[j]==left){
                graph[left][right]=1;
                jump=false;
                break;
            }
        if(jump)
            graph[right][left]=1;
    }
    for(i=0;i<g1_size;i++)
        graph[0][g1[i]]=1;
    for(i=0;i<g2_size;i++)
        graph[g2[i]][g_size+1]=1;

    ford_fulkerson(g_size+2,graph,0,g_size+1);
}

/*
12
6 6
1 3 6 8 9 11
2 4 5 7 10 12
17
1 2
1 5
2 3
2 6
3 4
3 7
4 8
5 6
5 9
6 7
6 10
7 8
7 11
8 12
9 10
10 11
11 12
 *
 */
