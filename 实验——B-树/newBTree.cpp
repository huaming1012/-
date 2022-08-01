#include <bits/stdc++.h>
using namespace std;

#define m 70
#define mid 35
class BTree
{
  public:
    typedef std::pair<int, int> value_type;

  private:
    struct BTNode
    {
        value_type values[m - 1];
        BTNode *ptr[m] = {NULL};
        BTNode *p = NULL;
        int keyNum = 0, size = 0;   //size表示结点及其所有子孙的关键字总数
        bool Leafflag = true;
        const int &key(int i) const { 
            return values[i].first; 
        }
        int &count(int i) {   //返回关键字出现次数
            return values[i].second; 
        }
        BTNode(BTNode *p = NULL) : p(p) {}
    };
    BTNode *root = NULL;
    static bool pairComp(const value_type &lhs, const int &rhs) { 
        return lhs.first < rhs; 
    }
    template <typename T>
    static void mymove(T *ptr, int length, int shift) { 
        memmove(ptr + shift, ptr, length * sizeof(T)); 
    }
    //求结点x及其所有子孙的关键字个数
    static int calSize(BTNode *x)
    {
        if (!x)
            return 0;
        int nsz = 0;
        for (int i = 0; i < x->keyNum; ++i)
            nsz += getSize(x->ptr[i]) + x->count(i);
        nsz += getSize(x->ptr[x->keyNum]);
        return nsz;
    }
    static int getSize(BTNode *x)
    {
        if (!x)
            return 0;
        return x->size;
    }
    //把index子树分裂成两个
    void split(BTNode *x, int index)
    {
        BTNode *z = new BTNode(x);
        BTNode *y = x->ptr[index];
        z->Leafflag = y->Leafflag;
        memmove(z->values, y->values + mid, (mid - 1) * sizeof(value_type));
        if (!y->Leafflag)
        {
            memmove(z->ptr, y->ptr + mid, mid * sizeof(BTNode *));
            for (int i = 0; i < mid; ++i)
                z->ptr[i]->p = z;
        }
        z->keyNum = y->keyNum = mid - 1;
        mymove(x->ptr + index + 1, x->keyNum - index, 1); //注意ptr本身keyNum多一个
        x->ptr[index + 1] = z;
        mymove(x->values + index, x->keyNum - index, 1);
        new (x->values + index) value_type(y->values[mid - 1]);

        y->size = calSize(y), z->size = calSize(z);
        ++x->keyNum;
    }
    //x结点插入关键字
    void insertEmpty(BTNode *x, const int &key)
    {
        while (true)
        {
            int i = lower_bound(x->values, x->values + x->keyNum, key, pairComp) - x->values;
            if (i != x->keyNum && !(key < x->values[i].first)) //已存在，计数加一
            {
                ++x->count(i);
                while (x)
                    ++x->size, x = x->p;
                return;
            }
            if (x->Leafflag)
            {
                mymove(x->values + i, x->keyNum - i, 1);
                x->values[i] = pair<int,int>(key, 1);
                ++x->keyNum;
                while (x)
                    ++x->size, x = x->p;
                return;
            }
            if (x->ptr[i]->keyNum == 2 * mid - 1)
            {
                split(x, i);
                if (x->key(i) < key)
                    ++i;
                else if (!(key < x->key(i)))
                {
                    ++x->count(i);
                    while (x)
                        ++x->size, x = x->p;
                    return;
                }
            }
            x = x->ptr[i];
        }
    }
    //合并结点
    void Combine(BTNode *x, int i) //将x的i孩子与i+1孩子合并，用x的i键作为分隔，这两个孩子都只有mid-1个孩子，合并后有2*mid-1个
    {
        BTNode *y = x->ptr[i], *z = x->ptr[i + 1];
        y->keyNum = 2 * mid - 1;
        y->values[mid - 1] = std::move(x->values[i]);
        memmove(y->values + mid, z->values, (mid - 1) * sizeof(value_type));
        if (!y->Leafflag)
        {
            memmove(y->ptr + mid, z->ptr, mid * sizeof(BTNode *));
            for (int j = mid; j <= 2 * mid - 1; ++j)
                y->ptr[j]->p = y;
        }
        mymove(x->values + i + 1, x->keyNum - i - 1, -1);
        mymove(x->ptr + i + 2, x->keyNum - i - 1, -1);

        --x->keyNum;
        y->size = calSize(y);
    }
    //删除x结点中的关键字key
    void Delete(BTNode *x, const int &key)
    {
        int i = lower_bound(x->values, x->values + x->keyNum, key, pairComp) - x->values;
        if (i != x->keyNum && !(key < x->values[i].first)) //找到了key
        {
            if (x->count(i) > 1)  //出现不止一次，次数计数减一即可
            {
                --x->count(i);
                while (x)  //所有祖先节点
                    --x->size, x = x->p;
                return;
            }
            if (x->Leafflag) //x是叶节点，直接删除
            {
                mymove(x->values + i + 1, --x->keyNum - i, -1); //需要移动的内存是x->keyNum-i-1
                while (x)
                    --x->size, x = x->p;
            }
            else
            {
                if (x->ptr[i]->keyNum >= mid)  //从前驱取关键字
                {
                    BTNode *y = x->ptr[i];
                    while (!y->Leafflag)
                        y = y->ptr[y->keyNum]; //找前驱
                    x->values[i] = y->values[y->keyNum - 1];
                    if (x->count(i) != 1) 
                    {
                        y->count(y->keyNum - 1) = 1;
                        while (y != x)
                            y->size -= x->count(i) - 1, y = y->p;
                    }

                    Delete(x->ptr[i], x->key(i));
                }
                else if (x->ptr[i + 1]->keyNum >= mid) //从后继取关键字
                {
                    BTNode *y = x->ptr[i + 1];
                    while (!y->Leafflag)
                        y = y->ptr[0]; //找后继
                    x->values[i] = y->values[0];
                    if (x->count(i) != 1)
                    {
                        y->count(0) = 1;
                        while (y != x)
                            y->size -= x->count(i) - 1, y = y->p;
                    }

                    Delete(x->ptr[i + 1], x->key(i));
                }
                else //合并兄弟节点、双亲结点一个关键字
                {
                    Combine(x, i);
                    if (root->keyNum == 0) 
                        root = x->ptr[i], root->p = NULL
			;
                    Delete(x->ptr[i], key);
                }
            }
        }
        else if (!x->Leafflag) //没有找到，继续找子树层
        {
            if (x->ptr[i]->keyNum == mid - 1)
            {
                BTNode *y = x->ptr[i];
                if (i >= 1 && x->ptr[i - 1]->keyNum >= mid) //左兄弟，取走它的最大孩子
                {
                    BTNode *z = x->ptr[i - 1];
                    mymove(y->values, y->keyNum, 1);
                    new (y->values) value_type(std::move(x->values[i - 1]));
                    new (x->values + i - 1) value_type(std::move(z->values[z->keyNum - 1]));
                    if (!y->Leafflag)
                    {
                        mymove(y->ptr, y->keyNum + 1, 1);
                        y->ptr[0] = z->ptr[z->keyNum], y->ptr[0]->p = y;
                    }

                    --z->keyNum, ++y->keyNum;
                    y->size = calSize(y), z->size = calSize(z);
                    Delete(y, key);
                }
                else if (i < x->keyNum && x->ptr[i + 1]->keyNum >= mid) //右兄弟,取走它的最小孩子
                {
                    BTNode *z = x->ptr[i + 1];
                    new (y->values + y->keyNum) value_type(std::move(x->values[i]));
                    new (x->values + i) value_type(std::move(z->values[0]));
                    if (!y->Leafflag) //y和z深度一样，Leafflag情况相同
                    {
                        y->ptr[y->keyNum + 1] = z->ptr[0], y->ptr[y->keyNum + 1]->p = y;
                        mymove(z->ptr + 1, z->keyNum, -1);
                    }
                    mymove(z->values + 1, z->keyNum - 1, -1);

                    --z->keyNum, ++y->keyNum;
                    y->size = calSize(y), z->size = calSize(z);
                    Delete(y, key);
                }
                else //与兄弟节点合并
                {
                    if (i != 0)
                        --i; //区分合并的是左还是右
                    y = x->ptr[i];
                    Combine(x, i);
                    if (root->keyNum == 0)
                        root = y, root->p = NULL
			;
                    Delete(y, key);
                }
            }
            else
                Delete(x->ptr[i], key);
        }
    }

  public:
    BTree() : root(new BTNode) {}
    //插入结点
    void insert(const int &key)
    {
        if (root->keyNum == m - 1)
        {
            BTNode *x = new BTNode;
            x->Leafflag = false, x->ptr[0] = root, x->size = root->size;
            root->p = x, root = x;
            split(x, 0);
        }
        insertEmpty(root, key);
    }
    //删除结点
    void Delete(const int &key) { 
        Delete(root, key);
    }

    //=======================================
    //找后继
    int findnext(const int &key)
    {
        BTNode *x = root;
        int ret;
        while (x)
        {
            int i = lower_bound(x->values, x->values + x->keyNum, key, pairComp) - x->values;
            if (x->values[i].first == key)
                ++i;
            if (i != x->keyNum)
                ret = x->values[i].first;
            x = x->ptr[i];
        }
        return ret;
    }
    //找前驱
    int findprior(const int &key)
    {
        BTNode *x = root;
        int ret;
        while (x)
        {
            int i = lower_bound(x->values, x->values + x->keyNum, key, pairComp) - x->values;
            if (i)
                ret = x->values[i - 1].first;
            x = x->ptr[i];
        }
        return ret;
    }

    //查询key数的排名
    int solverank(const int &key)
    {
        BTNode *x = root;
        int ret = 0;
        while (x)
        {
            if (x->key(x->keyNum - 1) < key)
            {
                ret += x->size - getSize(x->ptr[x->keyNum]);
                x = x->ptr[x->keyNum];
                continue;
            }
            for (int i = 0; i < x->keyNum; ++i)
            {
                if (x->key(i) < key)
                    ret += getSize(x->ptr[i]) + x->count(i);
                else if (x->key(i) == key)
                    return ret + getSize(x->ptr[i]) + 1;
                else
                {
                    x = x->ptr[i];
                    break;
                }
            }
        }
        return ret;
    }
    //查询排名为x的数
    int findrank(int k)
    {
        BTNode *x = root;
        while (true)
        {
            for (int i = 0; i <= x->keyNum; ++i)
            {
                
                const int lb = getSize(x->ptr[i]) + 1, ub = getSize(x->ptr[i]) + (i == x->keyNum ? 1 : x->count(i));
                if (k >= lb && k <= ub)
                    return x->key(i);
                if (k < lb)
                {
                    x = x->ptr[i];
                    break;
                }
                k -= ub;
            }
        }
    }
};


int main()
{
    BTree bt;
    int n, opt, x;
    cin >> n;
    while (n--)
    {
        cin >> opt >> x;
        switch (opt)
        {
        case 1:
            bt.insert(x);
            break;
        case 2:
            bt.Delete(x);
            break;
        case 3:
            cout << bt.solverank(x) << endl;
            break;
        case 4:
            cout << bt.findrank(x) << endl;
            break;
        case 5:
            cout << bt.findprior(x) << endl;
            break;
        case 6:
            cout << bt.findnext(x) << endl;
            break;
        }
    }
    return 0;
}