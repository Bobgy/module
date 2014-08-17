#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <assert.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE=10;
typedef vector<double> vd;
typedef vector<int> vi;
typedef vector<vd> vvd;
vvd a;
vd b;
const int MAXN=50000;
const int MAXM=5000;
const int MAXK=3;
const double eps=1e-10;


vvd transpose(const vvd &M)
{
    vvd a(M);
    for(int i=0;i<a.size();i++)
        for(int j=i+1;j<a.size();j++)
            swap(a[i][j],a[j][i]);
    return a;
}

void print(const vvd &a)
{  
    cout<<"----------"<<endl;
    for(int i=0;i<a.size();i++)
        for(int j=0;j<a[i].size();j++)
            printf("%.2lf%c",a[i][j],j==a[i].size()-1?'\n':' ');
}

void print(const vd &a)
{ 
    for(int i=0;i<a.size();i++)
        printf("%.2lf%c",a[i],i==a.size()-1?'\n':' ');
}

vvd reduce(const vvd &M)  //good
{
    vvd a(M);
    assert(a.size());
    int n=a.size(),m=a[0].size();
    for(int i=1;i<n;i++)assert(a[i].size()==m);
	double tmp; int t;
	int j=-1,i=0;
	for (; i<n; i++){
	    do{
            j++;
            if(j>=m)break;
            t=i;
            for (int k=i+1; k<n; k++)
                if (fabs(a[k][j])>fabs(a[t][j])) t=k;
        } while(fabs(a[t][j])<eps);
        if(j>=m)break;
		for (int k=j; k<m; k++) swap(a[i][k], a[t][k]);
		for (int k=j+1; k<m; k++) a[i][k]/=a[i][j];
		a[i][j]=1;
        for(int k=0;k<n;k++)
        {
            if(k==i)continue;
            for(int l=j+1;l<m;l++)
                a[k][l]-=a[k][j]*a[i][l];
            a[k][j]=0;
        }
	}
	a.resize(i);
	return a;
}

int gauss(const vvd &a, const vd &b, vd &res) //not recommended
{
    assert(a.size()==b.size());
    res.clear();
	vvd d(reduce(a));
	if(d.size()<a.size()){ //multiple or none
        int last=0;
        vvd t;
        int result=0;
        for(int i=0;i<a.size();i++)
        {
            t.push_back(a[i]);
            //print(t);
            vvd tmp(reduce(t));
            //print(tmp);
            int rr=tmp.size();
            if(rr==last)result+=(1<<i);
            last=rr;
        }
        return result;
    }
    vvd c(a);
    for(int i=0;i<a.size();i++)c[i].push_back(b[i]);
	vvd r(reduce(c));
	assert(r.size()==a.size());
    for(int i=0;i<r.size();i++)res.push_back(r[i].back());
	return 0;
}

int n, m;

main()
{
    srand(time(NULL));
    int n=8;
    b=vd(n,1);
    a=vvd(n,vd(n,1));
    for(int i=0;i<n;i++){
        b[i]=rand()%10;
        for(int j=0;j<n;j++)
            a[i][j]=rand()%10;
    }
    print(a);
    vvd t1(reduce(a));
    print(t1);
    cout<<t1.size()<<endl;
    vvd c(transpose(a));
    print(c);
    vvd d(reduce(c));
    print(d);
    vd res;
    int flag=gauss(a,b,res);
    cout<<flag<<endl;
    if(flag){
        int k=0;
        while(flag)
        {
            if(flag%2)cout<<k<<' ';
            k++;
            flag/=2;
        }
        cout<<endl;
    } else print(res);
}

