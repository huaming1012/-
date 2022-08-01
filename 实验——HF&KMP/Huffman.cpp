/*#include <iostream>
#include <stdio.h>
#include <queue>
#include <stdlib.h>
using namespace std;

#define IDSIZE 143

struct Node{
    int data;
    int weight;
    Node* lchild;
    Node* rchild;
    string HFcode;
    Node(int a = 0, int b = 0, Node* c = NULL, Node* d = NULL):
        data(a), weight(b), lchild(c), rchild(d), HFcode("") {}
}*tree;

struct cmp1{
    bool operator() (Node *a, Node *b){
        return a->weight > b->weight;
    }
};

struct cmp2{
    bool operator() (Node *a, Node *b){
        return a->data > b->data;
    }
};

int num[IDSIZE] = {0};
priority_queue<Node*, vector<Node*>, cmp2> sort_p_que;

void HuffmanCoding(Node * root){
    
    if(root->lchild){
        root->lchild->HFcode = root->HFcode + "0";
        HuffmanCoding(root->lchild);
    }
    if(!(root->lchild) && !(root->rchild)){
        sort_p_que.push(root);
    }
    if(root->rchild){
        root->rchild->HFcode = root->HFcode + "1";
        HuffmanCoding(root->rchild);
    }
}

int main(){
    FILE *fp = NULL;
    int val;
    int w_length = 0;
    priority_queue<Node*, vector<Node*>, cmp1> p_que;
    if((fp = fopen("data.txt", "r+")) != NULL){
        while(1){
            if(fscanf(fp, "%d", &val) == EOF)
                break;
            num[val]++;
                /*
            map<int,int>::iterator iter = Nodes.find(val);
            if(iter != Nodes.end()){
                iter->second++;
            }else{
                Nodes.insert(pair<int,int>(val,1));
            }
        }
        fclose(fp);
        for(int i = 1; i < IDSIZE; i++){
            Node * t = new Node;
            t->data = i;
            t->weight = num[i];
            p_que.push(t);
        }
        
        while(p_que.size() != 1){
            Node *a, *b;   //取权值最小的两个节点
            a = p_que.top();
            p_que.pop();
            b = p_que.top();
            p_que.pop();
            Node *tmp = new Node;   //ab连成新节点
            tmp->weight = a->weight + b->weight;
            tmp->lchild = a;
            tmp->rchild = b;
            p_que.push(tmp);
            w_length += a->weight + b->weight;
        }

        HuffmanCoding(p_que.top());
        while(!sort_p_que.empty()){
            cout << sort_p_que.top()->data << " " << sort_p_que.top()->weight << " " << sort_p_que.top()->HFcode << endl;
            sort_p_que.pop();
        }
        cout << w_length << endl;
        
        
    }else{
        cout << "ERROR" << endl;
    }
}*/

#include <iostream>
#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <fstream>
using namespace std;

#define IDSIZE 143

struct Node{
    int data;
    int weight;
    Node* lchild;
    Node* rchild;
    string HFcode;
    Node(int a = 0, int b = 0, Node* c = NULL, Node* d = NULL):
        data(a), weight(b), lchild(c), rchild(d), HFcode("") {}
}*tree;

struct cmp1{
    bool operator() (Node *a, Node *b){
        if(a->weight == b->weight)
            return a->data > b->data;
        return a->weight > b->weight;
    }
};

struct cmp2{
    bool operator() (Node *a, Node *b){
        return a->data > b->data;
    }
};

int num[IDSIZE] = {0};
priority_queue<Node*, vector<Node*>, cmp2> sort_p_que;

void HuffmanCoding(Node * root){
    
    if(root->lchild){
        root->lchild->HFcode = root->HFcode + "0";
        HuffmanCoding(root->lchild);
    }
    if(!(root->lchild) && !(root->rchild)){
        sort_p_que.push(root);
    }
    if(root->rchild){
        root->rchild->HFcode = root->HFcode + "1";
        HuffmanCoding(root->rchild);
    }
}

int main(){
    FILE *fp = NULL;
    int val;
    int w_length = 0;
    int n = IDSIZE;
    priority_queue<Node*, vector<Node*>, cmp1> p_que;
    if((fp = fopen("data.txt", "r+")) != NULL){
        while(1){
            if(fscanf(fp, "%d", &val) == EOF)
                break;
            num[val]++;
                
        }
        fclose(fp);
        fp = NULL;
        for(int i = 1; i < IDSIZE; i++){
            Node * t = new Node;
            t->data = i;
            t->weight = num[i];
            p_que.push(t);
        }
        
        while(p_que.size() != 1){
            Node *a, *b;   //取权值最小的两个节点
            a = p_que.top();
            p_que.pop();
            b = p_que.top();
            p_que.pop();
            Node *tmp = new Node;   //ab连成新节点
            tmp->data = n++;
            tmp->weight = a->weight + b->weight;
            tmp->lchild = a;
            tmp->rchild = b;
            p_que.push(tmp);
            w_length += a->weight + b->weight;
        }

        HuffmanCoding(p_que.top());
        ofstream fcout("Huffmanout.txt");
        while(!sort_p_que.empty()){
            fcout << sort_p_que.top()->data << " " << sort_p_que.top()->weight << " " << sort_p_que.top()->HFcode << endl;
            sort_p_que.pop();
        }
        fcout << w_length << endl;
        fcout.close();
        cout << w_length << endl;
        
        
    }else{
        cout << "ERROR" << endl;
    }
}