#include <bits/stdc++.h>
#define ONLINE_JUDGE
using namespace std;
const int MAXN = 112345;

class SegTree{
private:
    int L, R, N;
    struct Node{
        //code
    } v[MAXN*4];
    inline void down(int x, int l, int m, int r){
        Node &lch=v[x*2], &rch=v[x*2+1];
        //code
    }
    inline void up(int x, int l, int m, int r){
        Node &lch=v[x*2], &rch=v[x*2+1];
        //code
    }
    void _print(int x, int l, int r){
        int m=(l+r)/2;
        if(l<r){
            _print(x*2, l, m);
            _print(x*2+1, m+1, r);
        }
        //code
        //printf("range=[%d, %d], s=%d\n", l, r, v[x].s);
    }
    void _build(int x, int l, int r){
        if(l==r){
            //code
            return;
        }
        int m=(l+r)/2;
        _build(x*2, l, m);
        _build(x*2+1, m+1, r);
        Node &lch=v[x*2], &rch=v[x*2+1];
        //code
    }
    void _update(int x, int l, int r){
        if(l>R || r<L)return;
        if(L<=l && r<=R){
            //code
            return;
        }
        int m=(l+r)/2;
        down(x, l, m, r);
        _update(x*2, l, m);
        _update(x*2+1, m+1, r);
        up(x, l, m, r);
    }
    int _query(int x, int l, int r){
        if(l>R || r<L)return 0;
        if(L<=l && r<=R){
            //code
        }
        int m=(l+r)/2;
        down(x, l, m, r);
        //code
        //TData res=_query(x*2, l, m)+_query(x*2+1, m+1, r);
        up(x, l, m, r);
        return res;
    }
public:
    void build(int n){
        N=n;
        _build(1, 1, N);
    }
    TData query(int l, int r){
        L=l; R=r;
        return _query(1, 1, N);
    }
    void update(int l, int r){
        L=l; R=r;
        _update(1, 1, N);
    }
    void print(){
#ifndef ONLINE_JUDGE
        _print(1, 1, N);
#endif
    }
} seg;

int main(){
    seg.build(n);
    seg.update(l, r);
    TData res=seg.query(l, r);
    seg.print();
}
