#include <iostream>
#include <stdlib.h>
#include <time.h>
#define N 10  //待输入的数据集大小
using namespace std;

int compare_num = 0; //记录总比较次数

void swap(int *a, int *b){  //交换两个数
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//ChoosePivot子程序的四种实现
int ChoosePivot1(int *a, int l, int r){//第一种实现，总使用第一个元素作为基准元素
    return l;
}
int ChoosePivot2(int *a, int l, int r){//第二种实现，总使用最后一个元素作为基准元素
    return r;
}
int ChoosePivot3(int *a, int l, int r){//第三种实现，使用随机元素作为基准元素（按照要求运行十次，取平均值）
    int sum = 0;
    srand((unsigned)time(NULL));  //随机种子
    for(int i = 0; i < 10; i++){
        sum += rand()%(r-l) + l;
    }
    int pos = sum / 10;
    return pos;
}
int ChoosePivot4(int *a, int l, int r){//第四种实现，使用“三取中”方法选取基准元素
    int mid = (r + l)/2;
    if(a[l] >= a[mid]){
        if(a[mid] >= a[r]){
            compare_num += 2;  //比较两次即出结果
            return mid;
        }else{
            compare_num += 3;  //比较三次才有结果
            return a[l] >= a[r]?r:l;
        }
    }else{
        if(a[l] >= a[r]){
            compare_num += 2;  //比较两次即出结果
            return l;
        }else{
            compare_num += 3;  //比较三次才有结果
            return a[mid] >= a[r]?r:mid;
        }
    }
}

int Partition(int *a, int l, int r){  //以基准元素为标准，对整个数组排序（不占用额外空间）
    int p = a[l];
    int i = l + 1;
    for(int j = l + 1; j <= r; j++){
        if(a[j] <= p){
            swap(a[j], a[i]);
            i++;
        }
    }
    swap(a[l], a[i - 1]);
    return i - 1;
}

void QuickSort(int *a, int l, int r){
    if(l >= r) 
        return;
    compare_num += r - l;  //比较次数一共是长度减1
    int p = ChoosePivot4(a, l, r);  //改变这里可以选择不同的pivot的选择方式
    swap(a[l], a[p]);
    int pos = Partition(a, l, r);
    QuickSort(a, l, pos - 1);
    QuickSort(a, pos + 1, r);
}

int main(){
    int num[N];
    for(int i = 0; i < N; i++){
        cin >> num[i];
    }
    QuickSort(num, 0, N - 1);
    for(int i = 0; i < N; i++){
        cout << num[i] << " ";
    }
    cout << endl;
    cout << "The total number of comparisions is " << compare_num << endl;
}