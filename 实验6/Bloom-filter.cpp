#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <vector>
using namespace std;


//共有10000000个整数，需要一千万位来表示，其中每个int可以放32位
class Bitmap{
public:
    vector<int> nums;  //数组
    Bitmap(){}
    Bitmap(int size){
        nums.resize((size >> 5) + 1);   //计算共需多少个int
        //1个int有32bit，除以32等价于右移5位
    }
    void set(int n){  //将第n位设置为1
        int index = n >> 5;  //数组下标
        int bitpos = n % 32;  //具体在int中的哪一位
        nums[index] |= 1 << (31 - n);
    }
    bool find(int n){  //查找第n位是否为1
        int index = n >> 5;
        int bitpos = n % 32;
        return (nums[index] >> (31 - n)) & 1;
    }
};

//下面是4个字符串的哈希函数
size_t BKDRHash(const char *str)
{
	size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = hash * 131 + ch;
	}
	return hash;
}


size_t SDBMHash(const char *str)
{
	size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = 65599 * hash + ch; 
	}
	return hash;
}


size_t RSHash(const char * str)
{
	size_t hash = 0;
	size_t magic = 63689;
	while (size_t ch = (size_t)*str++)
	{
		hash = hash * magic + ch;
		magic *= 378551;
	}
	return hash;
}


size_t APHash(const char *str)
{
	size_t hash = 0;
	size_t ch;
	for (long i = 0; ch = (size_t)*str++; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
		}
	}
	return hash;
}




class Bloomfilter{
public:
    Bitmap bitmap;
    size_t mysize;
    
    Bloomfilter(int size){
        mysize = size;
        bitmap.nums.resize((size >> 5) + 1);
    }

    void set(string key){  //4种哈希函数得到的位置设为1
        bitmap.set(BKDRHash(key.c_str()) % mysize);
        bitmap.set(SDBMHash(key.c_str()) % mysize);
        bitmap.set(RSHash(key.c_str()) % mysize);
        bitmap.set(APHash(key.c_str()) % mysize);
    }

    bool is_contain(string key){  //查找，只有4种哈希查找结果都为是才认为包含
        if(!bitmap.find(BKDRHash(key.c_str()) % mysize))
            return false;
        if(!bitmap.find(SDBMHash(key.c_str()) % mysize))
            return false;
        if(!bitmap.find(RSHash(key.c_str()) % mysize))
            return false;
        if(!bitmap.find(APHash(key.c_str()) % mysize))
            return false;
        
        return true;
    }

};

int main(){
    Bloomfilter myfilter = Bloomfilter(10000000);
    ifstream fs;
    fs.open("bloomfilter_data.txt");
    if(!fs.is_open()){
        cout << "error" << endl;
        exit(0);
    }
    string str;
    while(getline(fs, str)){
        myfilter.set(str);
    }

    int times;
    cout << "please input the number of nums you want to query" << endl;
    cin >> times;
    while(times--){
        string num;
        cin >> num;
        cout << (myfilter.is_contain(num)? "yes":"no") << endl;
    }
    cout << "Is 1923950 in the set?" << (myfilter.is_contain("1923950")?"yes":"no") << endl;
    cout << "Is 7521074 in the set?" << (myfilter.is_contain("7521074")?"yes":"no") << endl;
    cout << "Is 9715134 in the set?" << (myfilter.is_contain("9715134")?"yes":"no") << endl;
    cout << "Is 13490 in the set?" << (myfilter.is_contain("13490")?"yes":"no") << endl;
    cout << "Is 425 in the set?" << (myfilter.is_contain("425")?"yes":"no") << endl;
    cout << "Is 327814 in the set?" << (myfilter.is_contain("327814")?"yes":"no") << endl;

    return 0;
}