#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace std;

int num[1000];

void get_next(int T[], int *next, int Tlen){
    int i = 0, j = -1;
    next[0] = -1;
    while(i < Tlen){
        if(j == -1 || T[i] == T[j]){
            ++i;
            ++j;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
}

int index_KMP(int S[], int T[], int pos, int next[], int Slen, int Tlen){
    int i = pos, j = 0;
    while(i < Slen && j < Tlen){
        if(j == -1 || S[i] == T[j]){
            ++i;
            ++j;
        }else{
            j = next[j];
        }
    }
    if(j >= Tlen)
        return (i-Tlen);
    else
        return (-1);
}

int main(){
    ifstream fin("input.txt");
    ofstream fcout("KMPout.txt");
    int Tlen, N, M;
    int T[5];
    if(fin.fail()){
        cout << "ERROR" << endl;
        return 0;
    }
    fin >> Tlen >> N >> M;
    for(int i = 0; i < Tlen; i++){
        fin >> T[i];
    }
    int *next = (int*)malloc(sizeof(int)*Tlen);
    get_next(T, next, Tlen);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < (M + 1); j++){
            fin >> num[j];
        }
        int pos = 0;
        pos = index_KMP(num, T, pos, next, (M + 1), Tlen);
        if(pos == -1)
        {
            fcout << "-1" << endl;
        }else{
            while(pos <= (M+1)-Tlen){
                fcout << pos << " ";
                pos = pos + Tlen;
                pos = index_KMP(num, T, pos, next, (M + 1)-pos, Tlen);
                if(pos == -1) break;
            }
            fcout << endl;
        }
    }
    fin.close();
    fcout.close();

}