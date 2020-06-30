struct node {
    int cnt;
    node *child[26];
    node(){
        cnt = 0;
        for(int i = 0; i < 26; i++)
            child[i] = NULL;
    }
};

struct node *root;

void insert(string s) {
    node *cur = root;
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'A';
        if (cur->child[c] == NULL) {
            cur->child[c] = new node;
        }
        cur = cur->child[c];
        cur->cnt++;
    }
}

int n, k;

int dfs(node *root, int h) {
    int ans = root->cnt / k;
    for (int i = 0; i < 26; i++) {
        if (root->child[i])
            ans += dfs(root->child[i], h + 1);
    }
    return ans;
}
