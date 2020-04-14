struct Matrix{
    int sz;
    vector<vector<int>> mat;

    Matrix(int _sz) : sz(_sz) {
        mat.resize(sz);
        for (int i = 0; i < sz; i++) {
            mat[i].resize(sz);
        }
    }

    Matrix(vector<vector<int>>& _mat) : mat(_mat) {
        sz = mat.size();
    }

    inline Matrix operator * (const Matrix &a) {
        Matrix temp(sz);
        for(int i = 0; i < sz; i++) {
            for(int j = 0; j < sz; j++) {
                for(int k = 0; k < sz; k++) {
	                temp.mat[i][j] += (mat[i][k] * a.mat[k][j]) % MOD;
	                if(temp.mat[i][j] >= MOD)
	                    temp.mat[i][j] -= MOD;   
	            }
	        }
	    }
        return temp;
    }

    inline Matrix operator + (const Matrix &a) {
        Matrix temp(sz);
        for(int i = 0; i < sz; i++) {
            for(int j = 0; j < sz; j++) {
                temp.mat[i][j] = mat[i][j] + a.mat[i][j] ;
                if(temp.mat[i][j] >= MOD)
                    temp.mat[i][j] -= MOD;
            }
        }
        return temp;
    }

    inline Matrix operator - (const Matrix &a) {
        Matrix temp(sz);
        for(int i = 0; i < sz; i++) {
            for(int j = 0; j < sz; j++) {
                temp.mat[i][j] = mat[i][j] - a.mat[i][j] ;
                if(temp.mat[i][j] < 0)
                    temp.mat[i][j] += MOD;
            }
        }
        return temp;
    }

    inline void operator = (const Matrix &b) {
        for(int i = 0; i < sz; i++) {
            for(int j = 0; j < sz; j++) {
                mat[i][j] = b.mat[i][j];
            }
        }
    }

    inline void print() {
        for(int i = 0; i < sz; i++) {
            for(int j = 0; j < sz; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
};

Matrix pow(Matrix a, int k) {
    int sz = a.sz;
    Matrix ans(sz);
    for(int i = 0; i < sz; i++)
        ans.mat[i][i] = 1;
    while(k) {
        if(k & 1)
            ans = ans * a;
        a = a * a;
        k >>= 1;
    }
    return ans;
}
