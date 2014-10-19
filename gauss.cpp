//列主元法高斯消元，矩阵存在e数组中
//n行m+1列的矩阵，第m+1列为等式右侧的常量
//返回值-1表示无解，其他数字表示矩阵的秩
//有解时返回任意一组解
//pos[i]表示第i行第一个非零数的位置
//复杂度O(min(n,m)*n*m)
typedef double flt;
const flt eps=1e-9;//有的范围大的题目可能需要更小的eps
const int MAXN=512, MAXM=512;
struct Gauss{
    flt e[MAXN][MAXM],x[MAXM];
    int pos[MAXM];
    int solve(int n, int m){
        int r=0;
        //c for column, r for row
        for(int c=0,i,j,k;c<=m&&r<n;++c){
            for(i=k=r;i<n;++i)
                if(fabs(e[i][c])>fabs(e[k][c]))k=i;
            if(k!=r)for(j=c;j<=m;++j)swap(e[k][j],e[r][j]);
            if(fabs(e[r][c])<eps)continue;
            pos[r]=c;
            for(i=r+1;i<n;++i){
                flt t=-e[i][c]/e[r][c];
                for(int j=c;j<=m;++j)e[i][j]+=t*e[r][j];
            }
            ++r; //注意,前面有continue,不能写到for里面去
        }
        if(r>0 && pos[r-1]==m)return -1;
        for(int i=0;i<m;++i)x[i]=0;
        for(int i=r-1;i>=0;--i){
            int c=pos[i];
            x[c]=e[i][m]/e[i][c];
            for(int j=0;j<i;++j)e[j][m]-=e[j][c]*x[c];
        }
        return r;
    }
};
