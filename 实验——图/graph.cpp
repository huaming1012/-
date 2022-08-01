#include <stdio.h>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define MAX_VERTEX_NUM 79
#define OK 1
#define ERROR -2
#define MAXN 1000
#define INF 100000

int visited[MAX_VERTEX_NUM];
int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = {0};
typedef struct
{
    int FlightID;
    int time_m;
}InfoType;


typedef struct ArcNode {
    int adjvex;       // 该弧所指向的顶点的位置
    struct ArcNode *nextarc;    // 指向下一条弧的指针
    InfoType *info;         // 该弧相关信息的指针
} ArcNode;
typedef struct VNode { 
    //VertexType data;       // 顶点信息
    int data;
    string time;
    ArcNode *firstarc = NULL; // 指向第一条依附该顶点的弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
    AdjList vertices;   
    int vexnum, arcnum;   //顶点数、边数
    int kind;          // 图的种类标志
} ALGraph;   //邻接表存储


typedef struct{
    int vexs[MAX_VERTEX_NUM];   //顶点
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //边
    int vexnum, arcnum;   //顶点数、边数

}MGraph;    //邻接矩阵存储


//===============================problem1===============================
//创建邻接表存储的图
int creategraph(ALGraph *map1){
    map1->vexnum = 79;
    for(int i = 0; i < map1->vexnum; i++){   //直接使用机场号作为下标
        map1->vertices[i].data = i + 1;
        map1->vertices[i].firstarc = NULL;
    }
    FILE *fp;
	fp = fopen("data.csv", "r");   //打开文件
	if(fp == NULL)   //打开失败处理
		cout << "FAIL" << endl;
	else{
		char *line, *record;
		char buffer[200];
        fgets(buffer, sizeof(buffer), fp);   //变量名，不需要读
		while((line = fgets(buffer, sizeof(buffer), fp)) != NULL){   //每次读一行
			record = strtok(line, ",");   //csv逗号分隔
			int i = 0;
            int row, col;
			while(record != NULL){   //i的值表示第几列
                i = i+1;
				if(i == 5){
                    row = atoi(record);
                }else if(i == 6){
                    col = atoi(record);
                }
				record = strtok(NULL, ",");
			}
			ArcNode *p = map1->vertices[row-1].firstarc;
            
            int flag = 0;
            while(p != NULL){
                if(p->adjvex == (col-1)){
                    flag = 1;   //表示该航线已经存在
                    break;
                }
                p = p->nextarc;
            }
            if(!flag){   //不存在则新建节点并插入邻接表
                ArcNode *q;
                q = (ArcNode*)malloc(sizeof(ArcNode));
                q->adjvex = col - 1;
                q->nextarc = map1->vertices[row-1].firstarc;
                map1->vertices[row-1].firstarc = q;
            }
		}
		fclose(fp);
		fp = NULL;
        return OK;
	}
    return OK;
}

//深度优先遍历
void DFS(ALGraph* G, int v, vector<int>* reachID){
    if(v < 0 || v >= G->vexnum) return;
    else{
        visited[v] = 1;   //访问第v个顶点
        reachID->push_back(G->vertices[v].data);
        ArcNode* p = G->vertices[v].firstarc;
        while(p != NULL){
            if(visited[p->adjvex] != 1)   //对其还未访问的邻接顶点递归调用DFS
                DFS(G, p->adjvex, reachID);
            p = p->nextarc;
        }
    }
}
void DFSTraverse(ALGraph* G, int start, vector<int>* reachID){
    int v;
    cout << "深度优先遍历：" << endl;
    for(v = 0; v < G->vexnum; v++)   //初始化
        visited[v] = 0;
    //for(v = 0; v < G->vexnum; v++){
        if(!visited[start-1])   //对未被访问的顶点调用DFS
            DFS(G, start-1, reachID);
    //}
    cout << endl;
}

//广度优先遍历
void BFSTraverse(ALGraph* G, int v, vector<int>* reachID){
    cout << "广度优先遍历：" << endl;
    int t;
    for(t = 0; t < G->vexnum; ++t){  //初始化
        visited[t] = 0;
    }
    queue<int> Q;       //利用队列实现BFS
        if(!visited[v]){
            visited[v] = 1;
            reachID->push_back(G->vertices[v].data);
            Q.push(v);
            while (!Q.empty())
            {
                int u = Q.front();   //队头元素出列，尝试访问其邻接顶点
                Q.pop();
                ArcNode* p = G->vertices[u].firstarc;
                while(p != NULL){
                    if(visited[p->adjvex] != 1){
                        visited[p->adjvex] = 1;
                        reachID->push_back(G->vertices[p->adjvex].data);
                        Q.push(p->adjvex);
                    }
                    p = p->nextarc;
                }
            }
            
        }

}
//邻接表进行遍历
void Traverse(){
    int ans1 = -1;
    cout << "邻接表进行深度优先和广度优先遍历，请输入出发机场的ID" << endl;
    cin >> ans1;
    vector<int> reachID;
    ALGraph* map1 = (ALGraph*)malloc(sizeof(ALGraph));
    creategraph(map1);  //创建邻接表
    DFSTraverse(map1, ans1, &reachID);  //深度优先遍历 
    sort(reachID.begin(), reachID.end(), less<int>());
    for(vector<int>::size_type i = 0; i < reachID.size(); i++){
        cout << reachID[i] << " ";
    }
    cout << endl;
    reachID.clear();
    BFSTraverse(map1, ans1, &reachID); //广度优先遍历
    sort(reachID.begin(), reachID.end(), less<int>());
    for(vector<int>::size_type i = 0; i < reachID.size(); i++){
        cout << reachID[i] << " ";
    }
    cout << endl;
    reachID.clear();
}


//===============================problem2===============================
//读入邻接矩阵
int readgraph(MGraph *map){   //读入过程不再赘述
    FILE *fp;
	fp = fopen("data.csv", "r");
	if(fp == NULL){
        cout << "FAIL" << endl;
        return ERROR;
    }else{
		char *line, *record;
		char buffer[200];
        fgets(buffer, sizeof(buffer), fp);
		while((line = fgets(buffer, sizeof(buffer), fp)) != NULL){
			record = strtok(line, ",");
			int i = 0;
            int row, col;
			while(record != NULL){
				if((++i) == 5){
                    row = atoi(record);
                }else if(i == 6){
                    col = atoi(record);
                }
				record = strtok(NULL, ",");
			}
			map->arcs[row-1][col-1] = 1;   //存在路径的边置为1
		}
		fclose(fp);
		fp = NULL;
	}
    return OK;
}
//求邻接矩阵的n次幂
void matrixmul(int n, MGraph map){
    for(int i = 0; i < MAX_VERTEX_NUM; i++){   //初始化一个单位矩阵
        matrix[i][i] = 1;
    }
    int temp[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = {0};
    for(int t = 0; t < n; t++){   //矩阵乘法进行n次
        for (int i = 0; i < MAX_VERTEX_NUM; i++) {
            for (int j = 0; j < MAX_VERTEX_NUM; j++) {
                double sum=0;
                for (int k = 0; k < MAX_VERTEX_NUM; k++) {
                    sum += matrix[i][k] * map.arcs[k][j];    
                }
                temp[i][j] = !(!sum); 
            }
        }
        for (int i = 0; i < MAX_VERTEX_NUM; i++) {
            for (int j = 0; j < MAX_VERTEX_NUM; j++) {
                matrix[i][j] = temp[i][j];
            }
        }
    }
}

//判断在给定条件下，任意两机场的可连通性
int limits(MGraph *map){
    cout << "请输入中转次数限制" << endl;
    int timelimit;
    cin >> timelimit;
    if(timelimit != -1){    //有限制，则直接求邻接矩阵的k次幂
        matrixmul(timelimit + 1, *map);
        for (int i = 0; i < MAX_VERTEX_NUM; i++) {
            for (int j = 0; j < MAX_VERTEX_NUM; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }else{    //无限制，则对每个顶点进行1中的深度优先遍历得到所有可以到达的点，将其在邻接矩阵中的对应位置置为1
        vector<int> reachID;
        ALGraph* map1 = (ALGraph*)malloc(sizeof(ALGraph));
        creategraph(map1);
        for(int i = 1; i <= 79; i++){
            DFSTraverse(map1, i, &reachID);   //求可到达点
            for(int j = 0; j < reachID.size(); j++){
                matrix[i-1][reachID[j]] = 1;
            }
        }
        for (int i = 0; i < MAX_VERTEX_NUM; i++) {   //输出
            for (int j = 0; j < MAX_VERTEX_NUM; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    return OK;
}
void judgelink(){
    MGraph * map = (MGraph*)malloc(sizeof(MGraph));
    readgraph(map);
    limits(map);
}


//===============================problem3===============================
int dist[MAX_VERTEX_NUM];   //存储源点到每个点的最短路径

vector<string> times[MAX_VERTEX_NUM];   //存储每个顶点（机场）对应的所有出发时间

//node类，是拆后的顶点，包括机场ID和对应时刻
class node{
    public:
    int AipID;
    char* time;
    node(){
        AipID = 0;
        time = (char*)malloc(20*sizeof(char));
    }
    node(int a, const char* b){
        AipID = a;
        time = (char*)malloc(20*sizeof(char));
        strcpy(time, b);
    }
    node& operator=(const node &other){
        AipID = other.AipID;
        time = (char*)malloc(20*sizeof(char));
        strcpy(time, other.time);
        return *this;
    }
    node(const node& other){
        AipID = other.AipID;
        time = (char*)malloc(20*sizeof(char));
        strcpy(time, other.time);
    }
    //bool operator < (const node &other) const{
    //    return AipID > other.AipID;
    //}
};
//nextedge类，表示边（航线），内含下一个顶点、下一条边、还有这条边的信息
class nextedge{
public:
    node nextnode;   //到达的机场和对应时刻
    struct nextedge* next;   //同一个出发点的下一条边
    int FlightID;   //航班号
    int time_m;  //边的权值，飞行时间或者航费
    nextedge(){
        nextnode = node(0,"");
        next = NULL;
        time_m = 0;
        FlightID = 0;
    }
    nextedge(node a, nextedge* b, int c){
        nextnode = a;
        next = b;
        time_m = c;
        FlightID = 0;
    }
    nextedge(node a, nextedge* b, int c, int d){
        nextnode = a;
        next = b;
        time_m = c;
        FlightID = d;
    }
    nextedge & operator=(const nextedge &other){
        nextnode = other.nextnode;
        next = other.next;
        time_m = other.time_m;
        FlightID = other.FlightID;
    }
};
template <class T>
struct Compare   //node类的比较函数，为了使用map创建
{
    int operator()(const T& x, const T& k) const {
        if(x.AipID >= k.AipID) return 0;
        else return 1;
    }
};

map<node, nextedge*, Compare<node> > mygraph;  //邻接表存储的图
set<node, Compare<node> > solid;    //标记dijkstra算法中已经确定的顶点
map<node,nextedge, Compare<node> > path;   //存储路径
struct qbase   //优先队列的元素类型
{
    node key;
    int value;  //与出发点的距离
    bool operator < (const qbase &other) const {
        return value > other.value;
    }
};

//计算时间（字符串类型）之差
int caltime(string time_s, string time_e){
    int day1, hour1, minute1;
    int day2, hour2, minute2;
    char time1[30];
    char time2[30];
    strcpy(time1, time_s.c_str());
    strcpy(time2, time_e.c_str());
    day1 = atoi(strtok(time1, "/"));   //依次分割处出日期，时分
    day1 = atoi(strtok(NULL, "/"));
    hour1 = atoi(strtok(NULL, " "));
    hour1 = atoi(strtok(NULL, ":"));
    minute1 = atoi(strtok(NULL, "\0"));
    day2 = atoi(strtok(time2, "/"));
    day2 = atoi(strtok(NULL, "/"));
    hour2 = atoi(strtok(NULL, " "));
    hour2 = atoi(strtok(NULL, ":"));
    minute2 = atoi(strtok(NULL, "\0"));
    int ans = (minute2-minute1) + (hour2 - hour1)*60 + (day2 - day1)*60*24;   //以分钟为单位
    return ans;
}
//创建邻接表存储的图（带时序关系）
void creategraph_D(){
    FILE *fp;
	fp = fopen("data.csv", "r");
	if(fp == NULL)
		cout << "FAIL" << endl;
	else{
		char *line, *record;
		char buffer[200];
        fgets(buffer, sizeof(buffer), fp);
		while((line = fgets(buffer, sizeof(buffer), fp)) != NULL){
			record = strtok(line, ",");
			int i = 0;
            int row, col;
            string time1, time2;
			while(record != NULL){
                i = i+1;
				if(i == 5){
                    row = atoi(record);
                }else if(i == 6){
                    col = atoi(record);
                }else if(i == 7){
                    time1 = record;
                }else if(i == 8){
                    time2 = record;
                }
				record = strtok(NULL, ",");
			}
            node tmp_s(row,time1.c_str());
            times[row-1].push_back(time1);
            if(mygraph.count(tmp_s) > 0){   //区分map中是否已经存在该节点，然后分别处理插入新节点
                nextedge* q;
                q = (nextedge*)malloc(sizeof(nextedge));
                node tmp_e(col,time2.c_str());
                q->nextnode = tmp_e;
                q->time_m = caltime(time1, time2);  //时间差作为权值
                q->next = mygraph[tmp_s];
                mygraph[tmp_s] = q;
                
            }else{
                nextedge* q;
                q = (nextedge*)malloc(sizeof(nextedge));
                if(!q) cout << "ERROR" << endl;
                node tmp_e(col,time2.c_str());
                q->nextnode = tmp_e;
                
                q->time_m = caltime(time1, time2);
                q->next = NULL;
                mygraph.insert(pair<node,nextedge*>(tmp_s,q));
            }
        }
		fclose(fp);
		fp = NULL;
        for(int i = 0; i < MAX_VERTEX_NUM; i++){    //建立同一个机场不同时刻之间的边
            for(int j = 0; j < times[i].size(); j++){
                node tmp(i+1,times[i][j].c_str());
                for(int k = j+1; k < times[i].size(); k++){
                    if(strcmp(times[i][k].c_str(),times[i][j].c_str()) <= 0) continue;
                    nextedge* q;
                    q = (nextedge*)malloc(sizeof(nextedge));
                    q->nextnode = node(i+1, times[i][k].c_str());
                    q->time_m = caltime(times[i][j],times[i][k]);
                    q->next = mygraph[tmp];
                    mygraph[tmp] = q;
                }

            }
        }
        
	}
}
//dijkstra算法（优先队列优化）
int Dijkstra(int start, int end){
    priority_queue<qbase> q;   //优先队列
    qbase sstart;
    sstart.key.AipID = start;
    int min = 9999999;
    for(int i = 0; i < times[start-1].size(); i++){
        for(int j = 0; j < MAX_VERTEX_NUM; j++){  //dist存放每个顶点离源点的最短路径，初始化
            dist[j] = INF;
        }
        dist[start-1] = 0;   //出发点距离自己为0
        strcpy(sstart.key.time,times[start-1][i].c_str());
        sstart.value = 0;
        q.push(sstart);
        path[sstart.key] = nextedge(node(0,"\0"),NULL,0, 0);
        while(!q.empty()){
            qbase h = q.top();  //权值最小的元素出队
            q.pop();
            int hID = h.key.AipID - 1;
            if(solid.count(h.key)) continue;
            solid.insert(h.key);
            nextedge * p = mygraph[h.key];  //读取与该元素相邻的边，找到权值最小的邻接顶点
            while(p != NULL){
                int w = p->time_m;
                if(!solid.count(p->nextnode) && dist[p->nextnode.AipID-1] > h.value + w){//若经h得到的权值小于dist中存放的，则进行更新
                    dist[p->nextnode.AipID-1] = h.value + w;
                    qbase tmp;
                    tmp.key = p->nextnode;
                    tmp.value = dist[p->nextnode.AipID-1];
                    path[p->nextnode] = nextedge(h.key,NULL,0, p->FlightID);  //这里的路径实际上是存放临界顶点到前一个顶点的有向边
                    q.push(tmp);
                }
                p = p->next;
            }
        }
        if(dist[end-1] < min){  //找目的机场的最小权值（最短时间）
            min = dist[end-1];
        }
    }
    return min;
}
//执行该算法
void exeDijkstra(){
    creategraph_D();
    cout << "请输入出发地和目的地" << endl;
    int start, end;
    cin >> start >> end;
    int ans = Dijkstra(start,end);
    cout << ans << endl;
    
}


//===============================problem4===============================
struct qbase2   //存储的信息可以看作一条边，根据起始时间进行排序
{
    int start,end;
    int FlightID;
    string time_s, time_e;
    bool operator < (const qbase2 &other) const{
        //return time_s > other.time_s;
        return strcmp(time_s.c_str(), other.time_s.c_str());
    }
};

struct flights{   //该结构体存储一次中转时的两个航班号，用于建立优先队列，方便输出字典序
    int first;
    int second;
    bool operator < (const flights & other) const{
        if(first == other.first)    return second > other.second;
        else return first > other.first;
    }
};

//查直飞或一次中转时的所有满足要求的航线
void findflight(){
    int s, t, change_times;
    cout << "请输入出发地和目的地，以及中转次数" << endl;
    cin >> s >> t >> change_times;
    //ALGraph * map = (ALGraph*)malloc(sizeof(ALGraph));
    if(change_times == 0){  //对于直飞的情况，直接在读入信息是选择出发地目的地与要求匹配的航班进行输出
        FILE *fp;
        fp = fopen("data.csv", "r");
        if(fp == NULL)
            cout << "FAIL" << endl;
        else{
            char *line, *record;
            char buffer[200];
            fgets(buffer, sizeof(buffer), fp);
            while((line = fgets(buffer, sizeof(buffer), fp)) != NULL){
                record = strtok(line, ",");
                int i = 0;
                int row, col, FID;
                while(record != NULL){
                    i = i+1;
                    if(i == 5){
                        row = atoi(record);
                    }else if(i == 6){
                        col = atoi(record);
                    }else if(i == 1){
                        FID = atoi(record);
                    }
                    record = strtok(NULL, ",");
                }
                if(row == s && col == t){   //直飞的情况直接在输入时选择对应的出发和目的机场即可，满足字典序
                    cout << FID << endl;
                }
            }
        }
        fclose(fp);
        fp = NULL;
    }else if(change_times == 1){   //对于中转一次的情况，按照时间顺序依次搜索从出发地出发的航班1，然后再向后寻找以航班1的到达地起飞，且到达目的地的航班，则时间上一定满足要求
        priority_queue<qbase2> queue;   //时间优先队列
        priority_queue<flights> ans;   //优先队列，用于输出字典序
        FILE *fp;
        fp = fopen("data.csv", "r");
        if(fp == NULL)
            cout << "FAIL" << endl;
        else{
            char *line, *record;
            char buffer[200];
            fgets(buffer, sizeof(buffer), fp);
            while((line = fgets(buffer, sizeof(buffer), fp)) != NULL){   //循环读入数据
                record = strtok(line, ",");
                int i = 0;
                int row, col, FID;
                string time1, time2;
                while(record != NULL){
                    i = i+1;
                    if(i == 5){
                        row = atoi(record);
                    }else if(i == 6){
                        col = atoi(record);
                    }else if(i == 1){
                        FID = atoi(record);
                    }else if(i == 7){
                        time1 = record;
                    }else if(i == 8){
                        time2 = record;
                    }
                    record = strtok(NULL, ",");
                }
                qbase2 tmp;   
                tmp.start = row;
                tmp.end = col;
                tmp.FlightID = FID;
                tmp.time_s = time1;
                tmp.time_e = time2;
                queue.push(tmp);
            }
            fclose(fp);  //关闭文件
            fp = NULL;
            while(!queue.empty()){   
                qbase2 tmp = queue.top();
                queue.pop();
                if(tmp.start != s) continue;   //先找到时间最小的从出发点出发的航班
                int new_s = tmp.end;   //以该航班到达的机场作为新的起点
                int num1 = tmp.FlightID;
                string new_time_s = tmp.time_e;//以该航班到达的时间作为新的出发时间
                priority_queue<qbase2>ttmp = queue;
                while (!ttmp.empty())
                {
                    qbase2 tmp2 = ttmp.top();
                    ttmp.pop();
                    if(tmp2.time_s < new_time_s || tmp2.start != new_s || tmp2.end != t) continue;   //凡是时间比第一个航班到达时间早，出发机场目的机场不对的都排除
                    int num2 = tmp2.FlightID;
                    flights a;
                    a.first = num1;
                    a.second = num2;
                    ans.push(a);
                }
                
            }
            while (!ans.empty())   //字典序输出
            {
                flights b = ans.top();
                cout << b.first << " " << b.second << endl;
                ans.pop();
            }
            
        }
        
    }
}


//===============================problem5&6===============================
//读取数据，大致过程与creategraph_D函数相同，只是将边的权值改为航费，方便第六问的解决
void read_fromtime(string lowtime, string hightime, int Airplane_mode, int mode){   //四个参数分别是时间下限、上限、机型要求和限制条件（起飞时间、降落时间、机型）
    FILE *fp;
	fp = fopen("data.csv", "r");
	if(fp == NULL)
		cout << "FAIL" << endl;
	else{
		char *line, *record;
		char buffer[200];
        fgets(buffer, sizeof(buffer), fp);
		while((line = fgets(buffer, sizeof(buffer), fp)) != NULL){  //循环读入
			record = strtok(line, ",");
			int i = 0;
            int row, col, FID, A_fares, A_mode;
            string time1, time2;
			while(record != NULL){
                i = i+1;
				if(i == 5){
                    row = atoi(record);
                }else if(i == 6){
                    col = atoi(record);
                }else if(i == 7){
                    time1 = record;
                }else if(i == 8){
                    time2 = record;
                }else if(i == 1){
                    FID = atoi(record);
                }else if(i == 11){
                    A_fares = atoi(record);
                }else if(i == 10){
                    A_mode = atoi(record);
                }
				record = strtok(NULL, ",");
			}
            if(mode == 1 && (time1 < lowtime || time1 > hightime)) continue;  //限制起飞时间，排除时限之外的
            if(mode == 2 && (time2 < lowtime || time2 > hightime)) continue;  //限制降落时间，排除时限之外的
            if(mode == 3 && A_mode != Airplane_mode) continue;  //限制机型，排除其余的
            node tmp_s(row,time1.c_str());
            times[row-1].push_back(time1);
            if(mygraph.count(tmp_s) > 0){
                nextedge* q;
                q = (nextedge*)malloc(sizeof(nextedge));
                node tmp_e(col,time2.c_str());
                q->nextnode = tmp_e;
                q->time_m = A_fares;
                q->FlightID = FID;
                q->next = mygraph[tmp_s];
                mygraph[tmp_s] = q;
                
            }else{
                nextedge* q;
                q = (nextedge*)malloc(sizeof(nextedge));
                if(!q) cout << "ERROR" << endl;
                node tmp_e(col,time2.c_str());
                q->nextnode = tmp_e;
                q->FlightID = FID;
                q->time_m = A_fares;
                q->next = NULL;
                mygraph.insert(pair<node,nextedge*>(tmp_s,q));
            }
        }
		fclose(fp);
		fp = NULL;
        for(int i = 0; i < MAX_VERTEX_NUM; i++){
            for(int j = 0; j < times[i].size(); j++){
                node tmp(i+1,times[i][j].c_str());
                for(int k = j+1; k < times[i].size(); k++){
                    if(strcmp(times[i][k].c_str(),times[i][j].c_str()) <= 0) continue;
                    nextedge* q;
                    q = (nextedge*)malloc(sizeof(nextedge));
                    q->nextnode = node(i+1, times[i][k].c_str());
                    q->time_m = 0;  //同处一个机场的不同时刻，花费为0
                    q->FlightID = 0;
                    q->next = mygraph[tmp];
                    mygraph[tmp] = q;
                }

            }
        }
        
	}
}
//求一条中转次数k以下的满足要求的航线
void oneline_BFS(int s, int t, int k){
    vector<int> ansFID;
    node ans;
    int fflag = 0;
    for(int i = 0; i < times[s-1].size(); i++){
        node start(s,times[s-1][i].c_str());
        
        queue<node> Q;   //队列，进行广度优先搜索
        int flag = 0;
        solid.insert(start);
        Q.push(start);
        path[start] = nextedge(node(0,"\0"),NULL,0, 0);
        while (!Q.empty())
        {
            node tmp = Q.front();
            Q.pop();
            nextedge* p = mygraph[tmp];
            while(p){
                if(!solid.count(p->nextnode)){
                    solid.insert(p->nextnode);
                    Q.push(p->nextnode);
                    path[p->nextnode] = nextedge(tmp,NULL,0, p->FlightID);   //存储路径及其航班号
                    if(p->nextnode.AipID == t){   //搜索到第一条到达目的地的路，即为最短路，跳出循环
                        flag = 1;
                        ans = p->nextnode;
                        break;
                    }
                }
                p = p->next;
            }
            if(flag) break;
        }
        if(flag){   //判断最短路的中转次数是否满足要求，满足才输出路径
            int min = 0;
            node tmp = ans;
            while(tmp.AipID != 0){
                min++;
                tmp = path[tmp].nextnode;
            }
            if(min <= k + 1){
                fflag = 1;
                break;
            }
                
        }
    }
    if(fflag){   //满足要求，则输出path中存储的路径
        node tmp = ans;
        while(path[tmp].nextnode.AipID != 0){
            ansFID.push_back(path[tmp].FlightID);
            tmp = path[tmp].nextnode;
        }
        for(std::vector<int>::iterator it = ansFID.end()-1; it >= ansFID.begin(); it--){
            cout << *it << " ";
            if(it == ansFID.begin()) break;
        }
        cout << endl;
    }else{   //不满足，则输出-1
        cout << "-1" << endl;
    }
    
}


map<node, int, Compare<node> > expenses;  //到达目的机场有不同时刻，存储所有对应顶点及其花费，方便找到花费最小的一个
//Dijkstra算法求航费最少的航班
int Dijkstra_fares(int start, int end){   //大致过程与Dijkstra函数一致
    priority_queue<qbase> q;
    qbase sstart;
    sstart.key.AipID = start;
    int min = 9999999;
    for(int i = 0; i < times[start-1].size(); i++){
        for(int j = 0; j < MAX_VERTEX_NUM; j++){
            dist[j] = INF;
        }
        dist[start-1] = 0;
        strcpy(sstart.key.time,times[start-1][i].c_str());
        sstart.value = 0;
        q.push(sstart);
        path[sstart.key] = nextedge(node(0,"\0"),NULL,0, 0);
        while(!q.empty()){
            qbase h = q.top();
            q.pop();
            int hID = h.key.AipID - 1;
            if(solid.count(h.key)) continue;
            solid.insert(h.key);
            nextedge * p = mygraph[h.key];
            while(p != NULL){
                int w = p->time_m;
                if(!solid.count(p->nextnode) && dist[p->nextnode.AipID-1] > h.value + w){
                    dist[p->nextnode.AipID-1] = h.value + w;
                    qbase tmp;
                    tmp.key = p->nextnode;
                    tmp.value = dist[p->nextnode.AipID-1];
                    expenses[p->nextnode] = h.value + w;
                    path[p->nextnode] = nextedge(h.key,NULL,0, p->FlightID);  //path存储到达p->nextnode的路径
                    q.push(tmp);
                }
                p = p->next;
            }
        }
        if(dist[end-1] < min){
            min = dist[end-1];
        }
    }
    
    node ans;
    vector<int> ansFID;
    for(map<node,int>::iterator it = expenses.begin(); it != expenses.end(); it++){  //找到对应最低花费的时刻，从而通过path求其路径
        if(it->second == min){
            ans = it->first;
        }
    }
    node tmp = ans;
    while(path[tmp].nextnode.AipID != 0){   //path依次求路径
        ansFID.push_back(path[tmp].FlightID);
        tmp = path[tmp].nextnode;
    }
    if(!ansFID.empty()){
        for(std::vector<int>::iterator it = ansFID.end()-1; it >= ansFID.begin(); it--){  //输出路径
            cout << *it << " ";
            if(it == ansFID.begin()) break;
        }
        cout << endl;
        cout << min << endl;
    }else{
        cout << "-1" << endl;
    }
    return min;
}
//第五题的解决函数，响应不同的要求（起飞时间、降落时间、机型）
void request_read(){
    int ans1;
    cout << "input:" << endl;
    cout << "1 : limit departure time" << endl;
    cout << "2 : limit arrival time" << endl;
    cout << "3 : limit airplane model" << endl;
    cin >> ans1;
    int s, t, k;
    string hightime, lowtime;
    if(ans1 == 1){
        cout << "请输入出发机场，目的机场和中转次数上限" << endl;
        cin >> s >> t >> k;
        getchar();
        getline(cin,hightime);
        getline(cin,lowtime);
        read_fromtime(lowtime, hightime, 2, ans1);
        oneline_BFS(s, t, k);
    }else if(ans1 == 2){
        cout << "请输入出发机场，目的机场和中转次数上限" << endl;
        cin >> s >> t >> k;
        getline(cin,hightime);
        getline(cin,lowtime);
        read_fromtime(lowtime, hightime, 2, ans1);
        oneline_BFS(s, t, k);
    }else if(ans1 == 3){
        cout << "请输入出发机场，目的机场和中转次数上限，以及机型要求" << endl;
        cin >> s >> t >> k;
        int ID;
        cin >> ID;
        read_fromtime("", "", ID, ans1);
        oneline_BFS(s, t, k);
    }
}
//第六题的解决函数，响应不同的要求（起飞时间、降落时间、机型）
void request_fares(){
    int ans1;
    cout << "input:" << endl;
    cout << "1 : limit departure time" << endl;
    cout << "2 : limit arrival time" << endl;
    cout << "3 : limit airplane model" << endl;
    cin >> ans1;
    int s, t;
    string hightime, lowtime;
    if(ans1 == 1){
        cout << "请输入出发机场，目的机场" << endl;
        cin >> s >> t;
        getchar();
        getline(cin,hightime);
        getline(cin,lowtime);
        read_fromtime(lowtime, hightime, 2, ans1);
        Dijkstra_fares(s, t);
    }else if(ans1 == 2){
        cout << "请输入出发机场，目的机场" << endl;
        cin >> s >> t;
        getline(cin,hightime);
        getline(cin,lowtime);
        read_fromtime(lowtime, hightime, 2, ans1);
        Dijkstra_fares(s, t);
    }else if(ans1 == 3){
        cout << "请输入出发机场，目的机场和机型要求" << endl;
        cin >> s >> t;
        int ID;
        cin >> ID;
        read_fromtime("", "", ID, ans1);
        Dijkstra_fares(s, t);
    }
}

//=========================================================================
int main(){
    int choice = -1;
    cout << "input:" << endl;
    cout << "1 : DFS or BFS traverses" << endl;
    cout << "2 : judge if two airports are connected" << endl;
    cout << "3 : the minTime between two airports" << endl;
    cout << "4 : the flight(direct or transit 1) between two airports" << endl;
    cout << "5 : the flight(transit less than k times) with limits" << endl;
    cout << "6 : the flight(minFare) with limits" << endl;
    cin >> choice;
    if(choice == 1){
        Traverse();
    }else if(choice == 2){
        judgelink();
    }else if(choice == 3){
        exeDijkstra();
    }else if(choice == 4){
        findflight();
    }else if(choice == 5){
        request_read();
    }else if(choice == 6){
        request_fares();
    }

    return 0;
}