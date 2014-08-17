#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char t[1000010], w[10100];
int nxt[10100];
void calc_nxt(char *s, int n){
    nxt[0] = -1;
    for(int i = 1; i < n; i++){
        int j = i - 1;
        nxt[i] = -1;
        do{
            j = nxt[j];
            if (s[i] == s[j+1]) nxt[i] = j + 1, j = -1;
        } while(~j);
    }
}
int main()
{
    int TT;
    scanf("%d", &TT);
    getchar();
    while(TT--){
        int cnt = 0;
        gets(w); gets(t);
        int W = strlen(w), T = strlen(t);
        calc_nxt(w, W);
        for(int i = 0, j = 0; i < T; i++){
            while(t[i] != w[j] && j >= 1)j = nxt[j-1] + 1;
            if(t[i] == w[j]) j++;
            if(j >= W) cnt++, j = nxt[j-1] + 1;
        }
        printf("%d\n", cnt);
    }
}   
