 int n;
    const int MAXN=1e5+10;
    vector<vi> adj(MAXN);
    vector<bool> visited(MAXN,0);
    vi tin(MAXN),low(MAXN,1e9);
    vi artp(MAXN,0);
    int timer=0;
    void dfs(int v,int p=-1){
        visited[v]=true;
        tin[v]=low[v]=timer++;
        int children=0;
        for(auto to:adj[v]){
            if(to==p) continue;
            if(visited[to]){
                amin(low[v],tin[to]);
            }
            else{
                dfs(to,v);
                low[v]=min(low[v],low[to]);
                if(tin[v]<=low[to]&&p!=-1){
                    artp[v]=1;
                }
                ++children;
            }
        }
        if(p==-1 && children >1) artp[v]=1;

    }
    void find_cutpoints(){
        timer=0;
        visited.assign(n,false);
        tin.assign(n,-1);
        low.assign(n,-1);
        for(int i=1;i<=n;i++){
            if(!visited[i]){
                dfs(i);
            }
        }
    }
