#include <cstdio>
#include <algorithm>
#include <vector>
#include <math.h>
#include <queue>
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
        data distanceTo(Point p){   //当前点与点p之间的距离
            return (data)(x-p.x)*(data)(x-p.x)+(data)(y-p.y)*(data)(y-p.y);
        }
};

Point P[MAX];   //存放所有的Point
KDNode T[MAX];  //存放所有的KdTree结点
int np;

struct KD_pri_info
{
    KDNode node;  //当前结点
    data disToPoint;   //当前节点到查找点的距离
    data disToCell;  //查找点到当前点确定的Bin的距离
    KD_pri_info(KDNode a, data b, data c): node(a), disToPoint(b), disToCell(c) {}  //初始化
    friend bool operator < (const KD_pri_info& a, const KD_pri_info& b){  //为了优先队列中的比较
        return a.disToCell > b.disToCell;
    }
};


data nearNeighbor_BBF(KDNode root, Point q){
    if(root.location == NIL) return 0;
    KDNode p = root;
    data bestDist = 1e30;   //初始化最近邻距离
    priority_queue<KD_pri_info> queue; //优先级队列，查询点q到队列中现有Bin的距离越小优先级越大
    int t = 0;   //记录访问的Bin的个数
    if(!root.dim){  //按照维度区分当前是x还是y，然后插入队列
        queue.push(KD_pri_info(p, q.distanceTo(P[root.location]), 
            (data)(q.x-P[root.location].x)*(data)(q.x-P[root.location].x)));
    }else{
        queue.push(KD_pri_info(p, q.distanceTo(P[root.location]), 
            (data)(q.y-P[root.location].y)*(data)(q.y-P[root.location].y)));
    }
    while(!queue.empty()){
        t++;
        KD_pri_info tmp = queue.top();
        queue.pop();
        int dimemsion = tmp.node.dim;
        data cmp_dis;
        if(!dimemsion){
            cmp_dis = (data)(q.x-P[tmp.node.location].x)*(data)(q.x-P[tmp.node.location].x);
        }else{
            cmp_dis = (data)(q.y-P[tmp.node.location].y)*(data)(q.y-P[tmp.node.location].y);
        }
        //如果最近邻距离小于查找点到当前点确定的Bin的距离则不访问该分支
        if(bestDist < cmp_dis){
            continue;
        }
        //记录当前点到查找点的距离并尝试更新
        data tmp_dis = q.distanceTo(P[tmp.node.location]);
        bestDist = min(tmp_dis, bestDist);
        
        KDNode qq = tmp.node;
        //遍历以当前点为根的子树，直到叶子节点
        while(qq.r != NIL || qq.l != NIL){
            t++;
            int newdim = qq.dim;
            if(!newdim){  //在x维度上
                if(q.x <= P[qq.location].x){  //如果查找点在当前点的左部
                    if(qq.l != NIL){ //进入左子树前先判断是否为空
                        if(qq.r != NIL){   //将右结点添加到队列前先判断其是否为空
                            data point_dis = q.distanceTo(P[T[qq.r].location]);
                            data cell_dis;
                            if(!T[qq.r].dim)
                                cell_dis = (data)(q.x-P[T[qq.r].location].x)*(data)(q.x-P[T[qq.r].location].x);
                            else
                                cell_dis = (data)(q.y-P[T[qq.r].location].y)*(data)(q.y-P[T[qq.r].location].y);
                            queue.push(KD_pri_info(T[qq.r], point_dis, cell_dis));
                        }
                        qq = T[qq.l];
                    }else{
                        break;
                    }
                }else{   //如果查找点在当前点的右部，同理
                    if(qq.r != NIL){
                        if(qq.l != NIL){
                            data point_dis = q.distanceTo(P[T[qq.l].location]);
                            data cell_dis;
                            if(!T[qq.l].dim)
                                cell_dis = (data)(q.x-P[T[qq.l].location].x)*(data)(q.x-P[T[qq.l].location].x);
                            else
                                cell_dis = (data)(q.y-P[T[qq.l].location].y)*(data)(q.y-P[T[qq.l].location].y);
                            queue.push(KD_pri_info(T[qq.l], point_dis, cell_dis));
                        
                        }
                        qq = T[qq.r];
                    }else{
                        break;
                    }
                }
            }else{  //在y维度，与x同理
                if(q.y <= P[qq.location].y){
                    if(qq.l != NIL){
                        if(qq.r != NIL){
                            data point_dis = q.distanceTo(P[T[qq.r].location]);
                            data cell_dis;
                            if(!T[qq.r].dim)
                                cell_dis = (data)(q.x-P[T[qq.r].location].x)*(data)(q.x-P[T[qq.r].location].x);
                            else
                                cell_dis = (data)(q.y-P[T[qq.r].location].y)*(data)(q.y-P[T[qq.r].location].y);
                            queue.push(KD_pri_info(T[qq.r], point_dis, cell_dis));
                        }
                        qq = T[qq.l];
                    }else{
                        break;
                    }
                }else{
                    if(qq.r != NIL){
                        if(qq.l != NIL){
                            data point_dis = q.distanceTo(P[T[qq.l].location]);
                            data cell_dis;
                            if(!T[qq.l].dim)
                                cell_dis = (data)(q.x-P[T[qq.l].location].x)*(data)(q.x-P[T[qq.l].location].x);
                            else
                                cell_dis = (data)(q.y-P[T[qq.l].location].y)*(data)(q.y-P[T[qq.l].location].y);
                            queue.push(KD_pri_info(T[qq.l], point_dis, cell_dis));
                        
                        }
                        qq = T[qq.r];
                    }else{
                        break;
                    }
                }
            }
            //尝试更新最近邻距离
            bestDist = min(q.distanceTo(P[qq.location]), bestDist);
        }
        //如果更新次数超过E_max则跳出循环，即返回现有的最近邻距离
        if(t > E_max){
            break;
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
        data bestDist;
        scanf("%d %d", &tmpx, &tmpy);
        Point target = Point(tmpx, tmpy);
        bestDist = nearNeighbor_BBF(T[root], target);
        printf("%lld\n", (long long)bestDist);
    }
	return 0;
}