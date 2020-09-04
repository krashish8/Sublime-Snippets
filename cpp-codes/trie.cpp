int cc = 0;

struct node {
    int cnt;
    int child[26];
    node(){
        cnt = 0;
        for(int i = 0; i < 26; i++)
            child[i] = 0;
    }
}t[N];

void insert(string s) {
    int id = 1;
    for(int i = 0; i < (int)s.length(); i++){
        int c = s[i]-'A';
        if(t[id].child[c] == 0){
            t[id].child[c] = ++cc;
        }
        id = t[id].child[c];
        t[id].cnt++;
    }
}

int n, k;

int dfs(int id, int h) {
    int ans = t[id].cnt / k;
    t[id].cnt = 0;
    for (int i = 0; i < 26; i++) {
        if (t[id].child[i] != 0){
            ans += dfs(t[id].child[i], h + 1);
            t[id].child[i] = 0;
        }
    }
    return ans;
}
