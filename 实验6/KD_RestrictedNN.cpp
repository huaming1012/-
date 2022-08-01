#include <cstdio>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

#define MAX 1000000
#define NIL -1
#define E_max 500

typedef long long data;

class KDNode{   //KDTree的结点
	public:
		int location; //表示该节点对应的Point在列表中的位置
        int size;  //表示以该节点为根的子树的节点数
        int dim; //表示该结点的维度信息
		int p, l, r;  //指示父节点、左右子节点在KDNode列表中的位置
		KDNode() {}
}; 

class Point{
	public:
		int x, y;
		Point() {}
		Point(int x, int y): x(x), y(y) {}
        data distanceTo(Point p){  //当前点与点p之间的距离
            return (data)(x-p.x)*(data)(x-p.x)+(data)(y-p.y)*(data)(y-p.y);
        }
};


Point P[MAX];   //存放所有的Point
KDNode T[MAX];  //存放所有的KdTree结点
int np;

class Rectangle{  //描述每个结点的范围
public:
    Point low;  //左下点
    Point high;  //右上点
    Rectangle(Point low1, Point high1): low(low1), high(high1){}
    bool contains(Point q){  //该范围是否包含点q
        if(q.x >= low.x && q.x <= high.x && q.y >= low.y && q.y <= high.y)
            return true;
        else return false;
    }
    bool contains(Rectangle c){   //该范围是否包含区域c
        if(c.low.x >= low.x && c.low.y >= low.y && c.high.x <= high.x && c.high.y <= high.y){
            return true;
        }else return false;
    }
    bool isDIsjointFrom(Rectangle c){   //该范围与区域c是否没有交集
        if(c.low.x > high.x || c.low.y > high.y || c.high.x < low.x || c.high.y < low.y){
            return true;
        }else return false;
    }
    Rectangle leftPart(int dim, Point s){   //在维度dim上，用s将该区域分割，返回左半部分
        if(!dim){
            Point newhigh = Point(s.x, high.y);
            return Rectangle(low, newhigh);
        }else{
            Point newhigh = Point(high.x, s.y);
            return Rectangle(low, newhigh);
        }
    }
    Rectangle rightPart(int dim, Point s){  //在维度dim上，用s将该区域分割，返回右半部分
        if(!dim){
            Point newlow = Point(s.x, low.y);
            return Rectangle(newlow, high);
        }else{
            Point newlow = Point(low.x, s.y);
            return Rectangle(newlow, high);
        }
    }
    data distanceTo(Point q){   //点q与该区域的距离，分多钟情况计算
        if(q.x >= low.x && q.x <= high.x && q.y >= low.y && q.y <= high.y)
            return 0;
        if(q.x >= low.x && q.x <= high.x){
            if(q.y > high.y) return (data)(q.y-high.y)*(data)(q.y-high.y);
            else return (data)(low.y-q.y)*(data)(low.y-q.y);
        }
        if(q.y >= low.y && q.y <= high.y){
            if(q.x > high.x) return (data)(q.x-high.x)*(data)(q.x-high.x);
            else return (data)(low.x-q.x)*(data)(low.x-q.x);
        }
        if(q.x < low.x && q.y > high.y){
            Point lh = Point(low.x, high.y);
            return q.distanceTo(lh);
        }
        if(q.x < low.x && q.y < low.y){
            return q.distanceTo(low);
        }
        if(q.x > high.x && q.y > high.y){
            return q.distanceTo(high);
        }
        if(q.x > high.x && q.y < low.y){
            Point rl = Point(high.x, low.y);
            return q.distanceTo(rl);
        }

    }
};

int t = 0;  //记录已访问的叶节点数量
data nearNeighbor(Point q, KDNode p, Rectangle cell, data bestDist){
    if(p.l == NIL && p.r == NIL) t++;   //访问的如果是叶节点则计数加一
    if(t <= E_max){   //只有在访问叶节点个数小于E_max时才继续搜索
        if(p.location != NIL){
            data tmp = q.distanceTo(P[p.location]);
            bestDist = min(tmp, bestDist);  //更新最小距离

            int dimension = p.dim;
            Rectangle leftCell = cell.leftPart(dimension, P[p.location]);
            Rectangle rightCell = cell.rightPart(dimension, P[p.location]);
            if(!dimension){   //在x维度时 
                if(q.x < P[p.location].x){//如果q离left部分更近
                    if(p.l != NIL)bestDist = nearNeighbor(q, T[p.l], leftCell, bestDist);
                    if(rightCell.distanceTo(q) < bestDist){  //先更新最近的部分，再以此判断是否需要遍历另一部分
                        if(p.r != NIL)bestDist = nearNeighbor(q, T[p.r], rightCell, bestDist);
                    }
                }else{  //否则离right部分更近，同理
                    if(p.r != NIL)bestDist = nearNeighbor(q, T[p.r], rightCell, bestDist);
                    if(leftCell.distanceTo(q) < bestDist){
                        if(p.l != NIL)bestDist = nearNeighbor(q, T[p.l], leftCell, bestDist);
                    }
                }
            }else{  //在y维度时，同理
                if(q.y < P[p.location].y){
                    if(p.l != NIL)bestDist = nearNeighbor(q, T[p.l], leftCell, bestDist);
                    if(rightCell.distanceTo(q) < bestDist){
                        if(p.r != NIL)bestDist = nearNeighbor(q, T[p.r], rightCell, bestDist);
                    }
                }else{
                    if(p.r != NIL)bestDist = nearNeighbor(q, T[p.r], rightCell, bestDist);
                    if(leftCell.distanceTo(q) < bestDist){
                        if(p.l != NIL)bestDist = nearNeighbor(q, T[p.l], leftCell, bestDist);
                    }
                }
            }

        }
    }

    return bestDist;
}


bool lessX(const Point &p1, const Point &p2) { return p1.x < p2.x; }
bool lessY(const Point &p1, const Point &p2) { return p1.y < p2.y; }

int makeKDTree(int l, int r, int depth){   //建树
	if(!(l < r) ) return NIL;
	int mid = (l + r) / 2;
	int t = np++; //指示KDNode队列中的下标位置
	if(depth % 2 == 0){ //不同的维度按照不同规则排序
		sort(P + l, P + r, lessX);
        T[t].dim = 0;
	} else {
		sort(P + l, P + r, lessY);
        T[t].dim = 1;
	}
	T[t].location = mid; //下标t的结点对应的Point的位置在P队列中是mid
    T[t].size = r-l; //子树的节点个数
	T[t].l = makeKDTree(l, mid, depth + 1);  //递归建立左子树
    T[T[t].l].p = t;
	T[t].r = makeKDTree(mid + 1, r, depth + 1); //递归建立右子树
    T[T[t].r].p = t;
	
	return t;
}


int main(){
	int px, py;
    int tmpxmin, tmpxmax, tmpymin, tmpymax;
    int pnum;
	scanf("%d", &pnum);
	for(int i = 0; i < pnum; i++){
		scanf("%d %d", &px, &py);
		P[i] = Point(px, py);
		T[i].l = T[i].r = T[i].p = NIL;
        if(px < tmpxmin) tmpxmin = px;
        if(px > tmpxmax) tmpxmax = px;
        if(py < tmpymin) tmpymin = py;
        if(py > tmpymax) tmpymax = py;
	}
	
	np = 0;
	
	int root = makeKDTree(0, pnum, 0);
	
	int q;
	scanf("%d", &q);
    int tmpx, tmpy;
	for(int i = 0; i < q; i++){
        data bestDist = 1e30;
        scanf("%d %d", &tmpx, &tmpy);
        Rectangle C = Rectangle(Point(tmpxmin,tmpymin), Point(tmpxmax, tmpymax));
        Point target = Point(tmpx, tmpy);
        t = 0;
        bestDist = nearNeighbor(target, T[root], C, bestDist);
        printf("%lld\n", (long long)bestDist);
    }
	return 0;
}