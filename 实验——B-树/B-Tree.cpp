#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

#define OK 1
#define ERROR -1
#define m 50
#define MAX 5

typedef int KeyType;
typedef int Status;

struct Record{
    KeyType key;
    char info[MAX];
};
typedef struct BTNode
{
    int keynum;  //节点关键字个数
    struct BTNode *parent;   //指向双亲结点
    KeyType key[m+5];  //关键字向量
    struct BTNode *ptr[m+5];  //子树指针向量
    Record *recptr[m+5];
    BTNode(): keynum(0), parent(NULL) {
		for(int i = 0; i <= m + 4; ++i) {
			key[i] = 0;
			ptr[i] = NULL;
            recptr[i] = NULL;
		}
	}
}BTNode, *BTree;
typedef struct
{
    BTNode * pt;  //指向找到的节点
    int i;  //指示关键字序号1...m
    int tag;  //表示查找是否成功：1成功，0失败
}Result;

//初始化
//int InitBTree(BTree &BT){
    
//}
//销毁
void DestroyBTree(BTree &BT){
    if(BT){  //非空
        for(int i = 0; i < BT->keynum; i++){
            DestroyBTree(BT->ptr[i]);
        }
        free(BT);
        BT = NULL;
    }
}

//===============查找==================
//在节点中查找关键字K
int Search(BTree T,KeyType K){
    //在p->key[1...keynum]中查找i，使得p->key[i] <= K < p->key[i+1]
    int i = 0, j;
    for(j = 1; j <= T->keynum; j++){
        if(T->key[j] <= K)
            i = j;
    }
    return i;
}
//在B-树上查找关键字K
Result SearchBTree(BTree T,KeyType K)
{// 在m阶B树T上查找关键字K，返回结果(pt,i,tag)。若查找成功，则特征值
// tag=1，指针pt所指结点中第i个关键字等于K；否则特征值tag=0，等于K的
// 关键字应插入在指针Pt所指结点中第i和第i+1个关键字之间。
    BTree p = T, q = NULL; //初始化，p指向待查结点，q指向p的双亲
    int found = false;
    int i = 0;
    Result r;
    while (p && !found)
    {
        i = Search(p, K);
        if(i > 0 && p->key[i] == K)
            found = true;
        else{
            q = p;
            p = p->ptr[i];
        }
    }
    r.i = i;
    if(found){
        r.pt = p;
        r.tag = 1;
    }else{
        r.pt = q;
        r.tag = 0;
    }
    return r;
}

//================插入==================
//给节点中插入关键字
void Insert(BTree &T, int i, Record *r, BTree ap){
    int j;
    for(j = T->keynum; j > i; j--){
        T->key[j+1] = T->key[j];
        T->ptr[j+1] = T->ptr[j];
        T->recptr[j+1] = T->recptr[j];
    }
    T->key[i+1] = r->key;
    T->ptr[i+1] = ap;
    T->recptr[i+1] = r;
    T->keynum++;
}
//生成新根节点
void NewRoot(BTree &T,Record *r,BTree ap){
    // 生成含信息(T,r,ap)的新的根结点*T，原T和ap为子树指针
    BTree p;
    p = (BTree)malloc(sizeof(BTNode));
    p->ptr[0] = T;
    T = p;
    if(T->ptr[0])
        T->ptr[0]->parent = T;
    T->parent = NULL;
    T->keynum = 1;
    T->key[1] = r->key;
    T->recptr[1] = r;
    T->ptr[1] = ap;
    if(T->ptr[1])
        T->ptr[1]->parent = T;
}
//结点分裂
void split(BTree &q,BTree &ap){
    // 将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap
    int i, s = (m + 1) / 2;
    ap = (BTree)malloc(sizeof(BTNode));
    ap->ptr[0] = q->ptr[s];
    if(ap->ptr[0])
        ap->ptr[0]->parent = ap;
    for(i = s + 1; i <= m; i++){   //将s之后的关键字和子树移动到新节点中
        ap->key[i-s] = q->key[i];
        q->key[i] = 0;
        ap->ptr[i-s] = q->ptr[i];
        q->ptr[i] = NULL;
        ap->recptr[i-s] = q->recptr[i];
        if(ap->ptr[i-s])
            ap->ptr[i-s]->parent = ap;
    }
    ap->keynum = m - s;
    ap->parent = q->parent;
    q->keynum = s - 1;
}
//在B-树上插入结点
Status InsertBTree(BTree &T,Record *r,BTree q,int i){
    BTree ap = NULL;
    int finished = false;
    int s;
    Record *rx;
    rx = r;
    while (q && !finished)
    {
        Insert(q, i, rx, ap);
        if(q->keynum < m)
            finished = true;
        else{  //分裂节点
            s = (m + 1) / 2;
            rx = q->recptr[s];
            split(q, ap);
            q = q->parent;
            if(q)
                i = Search(q, rx->key);
        }
    }
    if(!finished)
        NewRoot(T, rx, ap);
    return OK;
}

Status UseInsert(BTree &T, KeyType key){
    Result tmp = SearchBTree(T, key);
    Record* a = (Record *)malloc(sizeof(Record));
    a->key = key;
    if(tmp.tag == 1){
        //cout << "already exist" << endl;
        //本应是注释掉的这行代码，但是题目要求能重复
        InsertBTree(T, a, tmp.pt, tmp.i);
    }else{
        InsertBTree(T, a, tmp.pt, tmp.i);
    }
    return OK;
}

//==============删除====================
//把左兄弟结点中最大的关键码移到父结点中，并将父结点中大于其值的关键码移到被删除关键码所在的结点中
void MoveFromLeft(BTree &parent, int id, BTree &T, BTree &Lbro){
    //父节点移到当前节点
    for(int i = T->keynum; i >= 0; --i){   //所有元素后移一位，空出一个位置
        T->key[i + 1] = T->key[i];
        T->ptr[i + 1] = T->ptr[i];
    }
    T->key[1] = parent->key[id];
    T->ptr[0] = Lbro->ptr[Lbro->keynum];
    if(T->ptr[0])
        T->ptr[0]->parent = T;
    Lbro->ptr[Lbro->keynum] = NULL;
    T->keynum++;
    //左兄弟节点移到父节点
    parent->key[id] = Lbro->key[Lbro->keynum];
    Lbro->key[Lbro->keynum] = 0;
    Lbro->keynum--;
}
//把右兄弟结点中最小的关键码移到父结点中，并将父结点中小于其值的关键码移到被删除关键码所在的结点中
void MoveFromRight(BTree &parent, int id, BTree &T, BTree &Rbro){
    //父节点移到当前节点
    T->key[T->keynum + 1] = parent->key[id + 1];
    T->ptr[T->keynum + 1] = Rbro->ptr[0];
    if(T->ptr[T->keynum + 1])
        T->ptr[T->keynum + 1]->parent = T;
    Rbro->ptr[0] = NULL;
    T->keynum++;
    //右兄弟节点移到父节点
    parent->key[id + 1] = Rbro->key[1];
    Rbro->key[id] = 0;
    //处理右兄弟结点
    for(int i = 0; i <= Rbro->keynum; i++){
        Rbro->key[i] = Rbro->key[i + 1];
        Rbro->ptr[i] = Rbro->ptr[i + 1];
    }
    Rbro->key[0] = 0;
    Rbro->keynum--;
}
//把左兄弟节点（当前节点）和当前节点（右兄弟结点）、父节点中的一个关键字合并到左兄弟节点（当前节点）
void Combine(BTree &parent, int id, BTree &Lbro, BTree &T){
    //当前结点（右兄弟结点）移到左兄弟结点（当前结点）
    for(int i = 0; i <= T->keynum; i++){
        Lbro->key[Lbro->keynum + 1 + i] = T->key[i];
        Lbro->ptr[Lbro->keynum + 1 + i] = T->ptr[i];
        if(Lbro->ptr[Lbro->keynum + 1 + i]){
            Lbro->ptr[Lbro->keynum + 1 + i]->parent = Lbro;
        }
    }
    Lbro->key[Lbro->keynum + 1] = parent->key[id];
    Lbro->keynum += T->keynum + 1;

    free(T);
    for(int i = id; i <= parent->keynum; i++){
        parent->key[i] = parent->key[i + 1];
        parent->ptr[i] = parent->ptr[i + 1];
    }
    parent->keynum--;
}
//删除结点并进行调整
void DeleteBTNode(BTree &T, BTNode *dnode, int id){
    if(id < 0 || id > dnode->keynum) 
        return;
    while(true){
        if(dnode->ptr[id - 1] && dnode->ptr[id]){  //不是底层节点
            if(dnode->ptr[id - 1]->keynum > dnode->ptr[id]->keynum){  //用左子树最大节点替换
                BTree front = dnode->ptr[id - 1];
                dnode->key[id] = front->key[front->keynum];
                dnode = front;
                id = front->keynum;
            }else{  //用右子树最小节点替换
                BTree next = dnode->ptr[id];
                dnode->key[id] = next->key[1];
                dnode = next;
                id = 1;
            }
        }else if(!dnode->ptr[id - 1] && !dnode->ptr[id]){  //是底层结点
            for(int i = id; i <= dnode->keynum; i++){
                dnode->key[i] = dnode->key[i+1];
            }
            dnode->keynum--;

            int leastnum = ceil(m/2) - 1;
            BTree parent = dnode->parent;
            while (parent && dnode->keynum < leastnum){  //删除后不满足要求，需要调整
                int id = 0;
                for(int i = 0; i < parent->keynum; i++){
                    if(parent->ptr[i] == dnode){
                        id = i;
                        break;
                    }
                }

                BTree Lbro = NULL, Rbro = NULL;
                if(id - 1 >= 0)
                    Lbro = parent->ptr[id - 1];
                if(id + 1 <= parent->keynum)
                    Rbro = parent->ptr[id + 1];
                
                if(Lbro && Lbro->keynum > leastnum){   //从左兄弟借结点
                    MoveFromLeft(parent, id, dnode, Lbro);
                    break;
                }else if(Rbro && Rbro->keynum > leastnum){  //从右兄弟借结点
                    MoveFromRight(parent, id, dnode, Rbro);
                    break;
                }else{   //需要合并左（右）兄弟
                    if(Lbro)
                        Combine(parent, id, Lbro, dnode);
                    else
                        Combine(parent, id + 1, dnode, Rbro);
                    dnode = parent;
                    parent = dnode->parent;
                }
            }
            
            if(dnode->keynum == 0){  //根节点为空
                T = dnode->ptr[0];
                free(dnode);
            }
             
            break;
        }
    }
}

Status UseDelete(BTree &T, KeyType key){
    Result tmp = SearchBTree(T, key);
    if(tmp.tag == 1){
        DeleteBTNode(T, tmp.pt, tmp.i);
        return OK;
    }else{
        return ERROR;
    }
}

//=======================================

int myrank = 0;
void Traverse(BTree T, KeyType key){  //查询x数的排名
    if(T){
        if(T->ptr[0]){
            Traverse(T->ptr[0], key);
        }
        for(int i = 1; i <= T->keynum; i++){
            if(T->key[i] < key){
                myrank++;
            }else{
                break;
            }
            
            if(T->ptr[i]){
                Traverse(T->ptr[i], key);
            }
        }
    }
}

void findrankx(BTree T){  //查询排名为x的数
    if(myrank <= 0) return;
    if(T){
        if(T->ptr[0]){
            findrankx(T->ptr[0]);
        }
        for(int i = 1; i <= T->keynum; i++){
            myrank--;
            if(myrank == 0){
                cout << T->key[i] << endl;
                return;
            }
            if(T->ptr[i]){
                findrankx(T->ptr[i]);
            }
        }
    }
}

void findprior(BTree T, KeyType key){
    Result tmp = SearchBTree(T, key);
    if(tmp.tag){
        myrank = 0;
        Traverse(T, key);
        findrankx(T);
    }else{
        myrank = 0;
        Traverse(T, tmp.pt->key[tmp.i]);
        myrank++;
        findrankx(T);
    }
}

void findnext(BTree T, KeyType key){
    Result tmp = SearchBTree(T, key);
    if(tmp.tag){
        myrank = 0;
        Traverse(T, key);
        myrank += 2;
        findrankx(T);
    }else{
        myrank = 0;
        Traverse(T, tmp.pt->key[tmp.i + 1]);
        myrank++;
        findrankx(T);
    }
}

int main(){
    int n;
    cin >> n;
    BTree T = (BTNode *)malloc(sizeof(BTNode));
    while(n){
        int opt, x;
        cin >> opt >> x;
        switch (opt)
        {
        case 1:
            UseInsert(T, x);
            break;
        case 2:
            UseDelete(T, x);
            break;
        case 3:
            myrank = 0;
            Traverse(T, x);
            cout << myrank + 1 << endl;
            break;
        case 4:
            myrank = x;
            findrankx(T);
            break;
        case 5:
            findprior(T, x);
            break;
        case 6:
            findnext(T, x);
            break;
        default:
            cout << "ERROR" << endl;
            break;
        }
        n--;
    }
    return 0;
}