void dfs(int n) {
    in[n] = timer++;
    for (auto i : g[n]) {
        if (in[i] == -1) 
            dfs(i); // Tree edge
        else {
            if (out[i] == -1)
                cycle = 1; // back edge
            else if (in[i] > in[n])
                ;// Forward edge
            else
                ; // Cross edge
        }
    }
    out[n] = timer++;
}
