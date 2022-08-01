#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace std;

#define MAX_VERTEX_NUM 80
#define N 100
#define M 1000
int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = {0};

int main(){
    srand(time(NULL));
    ifstream fin("data2.txt");
    if(fin.fail()){
        cout << "ERROR" << endl;
        return 0;
    }
    while (!fin.eof())
    {
        int dep, arv;
        fin >> dep >> arv;
        matrix[dep][arv] = 1;
    }
    fin.close();
    int start = 50;
    ofstream fcout("input.txt");
    int T[5] = {50, 25, 62, 36, 49};
    fcout << "5" << " " << N << " " << M << endl;
    for(int i = 0; i < 4; i++){
        fcout << T[i] << " "; 
    }

    fcout << T[4] << endl;
    for(int i = 0; i < N; i++){
        int count = 0;
        start = 50;
        fcout << start;
        for(count; count < M; count++){
            int tmp[MAX_VERTEX_NUM];
            int k = 0; 
            for(int j = 0; j < MAX_VERTEX_NUM; j++){
                if(matrix[start][j]){
                    tmp[k++] = j;
                }
            }
            int next = tmp[rand()%k];
            fcout << " " << next;
            start = next;
        }
        fcout << endl; 
    }
    fcout.close();

    return 0;
}