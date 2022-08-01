#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAX_NUM 100000 //最大区间数


struct Interval {  //区间，包括开始时间、结束时间和权重
    int beginTime;
    int endTime;
    int weight;
};

//对区间排序时用结束时间排序
bool operator<(const Interval& r1, const Interval& r2) {
    return r1.endTime < r2.endTime;
}

class DP {
public: 
    Interval reqs[MAX_NUM + 1];
    int IntervalNum;
    int p[MAX_NUM + 1]; //p数组，表示最近并且相容的活动
    int M[MAX_NUM + 1]; //M数组，表示最大权重和
    //int pred[MAX_NUM + 1];
    void setIntervalNum(const int& IntervalNum) { //设置总区间数
        this->IntervalNum = IntervalNum;
    }
    void init() {  //读入数据，初始化
        for (int i = 1; i <= IntervalNum; ++i) {
            cin >> reqs[i].beginTime >> reqs[i].endTime >> reqs[i].weight;
        }
    }
    int binarySearch(int n, int key){ //二分查找最近并且相容的活动
        int low = 1;
        int high = n - 1;
        int mid;
        while(low < high){
            mid = (low + high + 1)/2;
            Interval midVal = reqs[mid];
            if(midVal.endTime <= key)
                low = mid;
            else if(midVal.endTime > key)
                high = mid - 1;
            else
                return mid;
        }
        if(reqs[low].endTime > key) return 0;
        if(reqs[low].endTime <= key) return low;
        else return high;
    }

    void prepare() {
        sort(reqs + 1, reqs + IntervalNum + 1); //根据结束时间对所有区间排序
        memset(p, 0, sizeof(p)); 
        memset(M, 0, sizeof(M)); //初始化数组M
        for (int i = 1; i <= IntervalNum; i++) { //初始化数组p
            p[i] = binarySearch(i, reqs[i].beginTime);
        }
    }
    // 动态规划算法
    int solveWIS() {

        M[0] = 0;
        for(int i = 1; i <= IntervalNum; i++){
            if(reqs[i].weight + M[p[i]] >= M[i - 1]){
                M[i] = reqs[i].weight + M[p[i]];
            }else{
                M[i] = M[i - 1];
            }
        }
        return M[IntervalNum];
    }
  
};

int main() {
    int num;
    cin >> num;
    DP dp;
    
    dp.setIntervalNum(num);
    dp.init();
    dp.prepare();
    int maxweight = dp.solveWIS();
    cout << maxweight << endl;
    return 0;
}
