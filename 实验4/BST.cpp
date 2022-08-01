#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct TreeNode{
    int val;
    int size;
    TreeNode *lchild;
    TreeNode *rchild;
}TreeNode, *BiTree;

int InsertNode(BiTree* BSTTree, int e){  //插入节点
    if(*BSTTree == NULL){//此树为空，则创建根节点
        TreeNode* tmpnode = (TreeNode*)malloc(sizeof(TreeNode));
        tmpnode->val = e;
        tmpnode->size = 1;
        tmpnode->lchild = NULL;
        tmpnode->rchild = NULL;
        *BSTTree = tmpnode;
        return 1;//插入成功
    }
    if((*BSTTree)->val == e){  //关键值相同，插入失败
        return 0;
    }else if((*BSTTree)->val > e){  //插入值小于根节点的值，插入左子树
        (*BSTTree)->size++;
        return InsertNode(&(*BSTTree)->lchild, e);
    }else if((*BSTTree)->val < e){  //否则，插入右子树
        (*BSTTree)->size++;
        return InsertNode(&(*BSTTree)->rchild, e);
    }
}

int AuxBST_Select(BiTree BSTTree, int k){  //查找第k小的数
    if(BSTTree->size < k)  //总结点数小于k，查找失败
        return -1;
    int num = 0;
    if(BSTTree->lchild){ 
        num = BSTTree->lchild->size;  //num是该树中小于当前节点值的结点数
    }
    if(num == k - 1)  //找到了
        return BSTTree->val;
    else if(num < k - 1){  //需要在右子树中继续查找
        return AuxBST_Select(BSTTree->rchild, k - num - 1);
    }else if(num > k - 1){ //需要在左子树中继续查找
        return AuxBST_Select(BSTTree->lchild, k);
    }
}



void CreateTree(BiTree* BSTTree, int n){  //创建BST,其中n为节点总数
    int tmp;
    for(int i = 0; i < n; i++){
        cin >> tmp;
        InsertNode(BSTTree, tmp);
    }

}

TreeNode* SearchNode(BiTree BSTTree, int e, int* esize){  
//查找值为e的结点，esize返回除当前节点的左子树以外，小于当前节点值的结点总数
    if(BSTTree == NULL)
        return NULL;
    if(BSTTree->val == e){
        (*esize) += 1;
        return BSTTree;
    }else if(BSTTree->val > e){
        return SearchNode(BSTTree->lchild, e, esize);
    }else if(BSTTree->val < e){
        (*esize) += BSTTree->lchild->size+1;
        return SearchNode(BSTTree->rchild, e, esize);
    } 
    
}

int AuxBST_Find(BiTree Tree, int z, int k){ //找比z大的第k个数
    int zsize = 0;
    TreeNode* tmp = SearchNode(Tree, z, &zsize);
    if(tmp == NULL){//查找错误，没有为z的值
        return -1;
    }else{
        if(tmp->lchild)
            return AuxBST_Select(Tree, zsize + tmp->lchild->size + k); //zsize加左子树结点数，就是所有值小于z所在结点值的结点总数
        else
            return AuxBST_Select(Tree, zsize + k);
    }
}

TreeNode* DeleteNode(BiTree* BSTTree, int e){  //删除节点
    if(*BSTTree == NULL)
        return NULL;
    else if((*BSTTree)->val > e){  //找左节点
        (*BSTTree)->size--;
        (*BSTTree)->lchild = DeleteNode(&(*BSTTree)->lchild, e);
    }else if((*BSTTree)->val < e){  //找右节点
        (*BSTTree)->size--;
        (*BSTTree)->rchild = DeleteNode(&(*BSTTree)->rchild, e);
    }else{  //找到了，分情况处理
        if((*BSTTree)->lchild == NULL){  //没有左节点
            TreeNode* rnode = (*BSTTree)->rchild;
            free(*BSTTree);
            return rnode;
        }else if((*BSTTree)->rchild == NULL){  //没有右节点
            TreeNode* lnode = (*BSTTree)->lchild;
            free(*BSTTree);
            return lnode;
        }else if((*BSTTree)->lchild->rchild == NULL){  //左节点没有右节点
            TreeNode* lnode = (*BSTTree)->lchild;
            lnode->rchild = (*BSTTree)->rchild;
            free(*BSTTree);
            return lnode;
        }else{  //找左子树的最大值来替换当前节点
            TreeNode* p = (*BSTTree)->lchild;
            for(p; p->rchild->rchild != NULL; p = p->rchild);
            TreeNode* lnode = p->lchild;
            p->rchild = lnode->rchild;
            lnode->lchild = (*BSTTree)->lchild;
            lnode->rchild = (*BSTTree)->rchild;
            free(p);
            return lnode;
        }
    }
    return *BSTTree;
}

void ShowTree(BiTree BSTTree){  //中序遍历
    if(BSTTree){
        ShowTree(BSTTree->lchild);
        printf("%d:%d ", BSTTree->val, BSTTree->size);
        ShowTree(BSTTree->rchild);
    }
    
}

int main(){
    int n;
    printf("Please input the number of the nodes\n");
    cin >> n;
    BiTree Tree;
    printf("Please input the nums in order\n");
    CreateTree(&Tree, n);
    ShowTree(Tree);
    printf("\n");
    printf("Size of the left child of root: %d\n", Tree->lchild->size);
    printf("Size of the right child of root: %d\n", Tree->rchild->size);

    printf("Now you input k to get the kth num in BST\n");
    int k;
    cin >> k;
    printf("The %dth num is:%d\n", k, AuxBST_Select(Tree, k));

    printf("Now you input z&k to get the kth num greater than z in BST\n");
    int z;
    cin >> z >> k;
    printf("The %dth num greater than %d is:%d\n", k, z, AuxBST_Find(Tree, z, k));
    return 0;
}