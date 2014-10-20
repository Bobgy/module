//计算n(n<MAXN)个圆形面积的并，并给出其质心坐标(cx, cy)
//坐标和半径绝对值超过10000时需要修改避免爆int
//用add_circle(x, y, r)添加圆
//多case时用clear()清空
template<class T> T sqr(T x){return x*x;}
typedef double flt;
const flt EPS=1e-9;
const int MAXN=2001;
const flt PI=acos(-1.0);
struct CIRU{
    int x[MAXN],y[MAXN],r[MAXN],n;
    void clear(){n=0;}
    void add_circle(int xx,int yy,int rr){
        x[n]=xx,y[n]=yy,r[n++]=rr;
    }
    int sqdis(int i, int j){
        return sqr(x[i]-x[j])+sqr(y[i]-y[j]);
    }
    flt fix(flt x){
        if(x<-PI)x+=2*PI;
        if(x>PI)x-=2*PI;
        return x;
    }
    pair<flt,int> v[MAXN*4+9];
    flt cx, cy;
    flt calc_area(){
        flt area=0;
        cx=cy=0;
        for(int i=0;i<n;++i){
            bool ok=1;
            int tot=2;
            v[0]=mp(-PI,0);
            v[1]=mp(PI,0);
            for(int j=0;j<n;++j)if(j!=i){
                if(x[j]==x[i]&&y[j]==y[i]&&r[j]==r[i]&&j<i){ok=0;break;}
                int dis=sqdis(i,j);
                if(r[i]<r[j]&&dis<=sqr(r[i]-r[j])){ok=0;break;}
                if(dis>=sqr(r[i]+r[j])||dis<=sqr(r[i]-r[j]))continue;
                flt delta = (sqr(r[i])-sqr(r[j])+dis)*0.5;
                delta = acos(delta / (sqrt(flt(dis))*r[i]));
                flt dir = atan2(flt(y[j]-y[i]),flt(x[j]-x[i]));
                flt bg=dir-delta, ed=dir+delta;
                bg=fix(bg),ed=fix(ed);
                v[tot++]=make_pair(bg,1);
                v[tot++]=make_pair(ed,-1);
                if(bg>ed+EPS){
                    v[tot++]=mp(PI,-1);
                    v[tot++]=mp(-PI,1);
                }
            }
            if(!ok)continue;
            if(tot==2){
                flt s=2*PI*sqr(r[i]);
                area+=s; //与其他圆不相交
                cx+=s*x[i];
                cy+=s*y[i];
            } else {
                sort(v,v+tot);
                int cnt=0;
                REP(j,tot-1){
                    cnt+=v[j].second;
                    flt a1=v[j].first,a2=v[j+1].first;
                    if(cnt==0 && a2-a1>EPS){
                        flt x1=x[i]+r[i]*cos(a1), y1=y[i]+r[i]*sin(a1);
                        flt x2=x[i]+r[i]*cos(a2), y2=y[i]+r[i]*sin(a2);
                        flt s_poly = x1*y2-x2*y1; //被包围的多边形面积
                        //只算面积时可以只用下一行注释内的替换后面的所有
                        //area += r[i] * (y[i]*(cos(a1)-cos(a2)) + x[i]*(sin(a2)-sin(a1)));
                        flt s_fan  = (a2-a1)*sqr(r[i]); //扇形面积
                        flt s_tri  = -sin(a2-a1)*sqr(r[i]); //扇形内的三角形面积，注意是负的
                        area+=s_poly+s_fan+s_tri;
                        flt sx=4.0/3.0*sin((a2-a1)/2)*r[i]*r[i]*r[i]/s_fan; //以下是求质心的
                        cx += (x1+x2)*s_poly/3;
                        cy += (y1+y2)*s_poly/3;
                        cx += (x[i]+sx*cos((a1+a2)/2))*s_fan;
                        cy += (y[i]+sx*sin((a1+a2)/2))*s_fan;
                        cx += (x1+x2+x[i])*s_tri/3;
                        cy += (y1+y2+y[i])*s_tri/3;
                    }
                }
            }
        }
        if(fabs(area)>EPS){
            cx/=area;
            cy/=area;
        }
        return area*0.5;
    }
} cu;