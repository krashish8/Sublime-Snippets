const int BLOCK_SIZE = sqrt(N);
int sum[BLOCK_SIZE];

    for (int i = 0; i < n; i++)
        sum[i/BLOCK_SIZE] += a[i];

    int ll = l / BLOCK_SIZE, rr = r / BLOCK_SIZE;
    int s = 0;
    if (ll == rr) {
        for (int i = l; i <= r; i++)
            s += a[i];
    }
    else {
        for (int i = l; i < (ll+1)*BLOCK_SIZE; i++)
            s += a[i];
        for (int i = ll + 1; i < rr; i++)
            s += sum[i];
        for (int i = rr*BLOCK_SIZE; i <= r; i++)
            s += a[i];
    }
