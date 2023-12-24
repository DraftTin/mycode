#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include<map>

using namespace std;

typedef struct HTNode{
    int freq;
    int parent;
    int left;
    int right;
    HTNode() : left(-1), right(-1), parent(-1), freq(0) {}
} HTNode, *HuffmanTree;

typedef struct MinNode{
    int m1;
    int m2;
}MinNode;

MinNode Select(HuffmanTree& HT, int n){
    // n表示构造好的结点的数量
    MinNode mn;
    int mval;
    mval = INT_MAX;
    for(int i = 1; i <= n; ++i){
        //取没有被访问过并且频率最小的两个点
        if(HT[i].parent == -1 && HT[i].freq < mval){
            mval = HT[i].freq;
            mn.m1 = i;
        }
    }
    mval = INT_MAX;
    for(int i = 1; i <= n; ++i){
        if(HT[i].parent == -1 && i != mn.m1 && HT[i].freq < mval){
            mval = HT[i].freq;
            mn.m2 = i;
        }
    }
    return mn;
}

vector<string> HuffmanCode(HuffmanTree& HT, int *w, int n){
    // 循环进行n-1次，每次遍历[0..i]，时间复杂度为O(n^2)
    // HT表示要构造的huffmanTree, w表示出现频率, n表示w的长度
    int m = 2 * n - 1; //表示总共需要的结点数量
    HT = new HTNode[2 * n]; //下标为0的空间不用
    for(int i = 1; i <= n; ++i)
        HT[i].freq = w[i-1];
    for(int i = n + 1; i <= m; ++i){
        MinNode mnode = Select(HT, i - 1);
        int s1 = mnode.m1;
        int s2 = mnode.m2;
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].left = s1;
        HT[i].right = s2;
        HT[i].freq = HT[s1].freq + HT[s2].freq;
    }
    // for(int i = 1; i <= n; ++i){
    //     cout << i << "'s father: " << HT[i].parent << endl;
    // }
    // 编码
    vector<string> huffmancode(n + 1);
    for(int i = 1; i <= n; ++i){
        int tmp = i;
        while(HT[tmp].parent != -1){
            if(tmp == HT[HT[tmp].parent].right)
                huffmancode[i].push_back('1');
            else
                huffmancode[i].push_back('0');
            tmp = HT[tmp].parent;
        }
        reverse(huffmancode[i].begin(), huffmancode[i].end());
    }
    return huffmancode;
}

string inCode(map<char, string> codes, string& s){
    string code;
    for(char tmp : s){
        code += codes[tmp];
    }
    return code;
}

string deCode(HuffmanTree HT, string& code, int n){
    string s;
    int pos =  2 * n - 1;
    int flag = 0;
    for(string::iterator iter = code.begin(); iter != code.end(); ++iter){
        if(pos > n){
            pos = (*iter == '0') ? HT[pos].left : HT[pos].right;
        }
        if(pos <= n){
            s.push_back('a' + pos - 1);
            pos = 2 * n - 1;
            //--iter;
        }
    }
    return s;
}

int main(void){
    HuffmanTree HT;
    int n;
    cin >> n;
    int *w = new int[n];
    for(int i = 0; i < n; ++i){
        cout << "enter the weight: ";
        cin >> w[i];
    }
    // map<char, string> codes = {{'a', ""}, {'b', ""}, {'c', ""}, {'d', ""}, {'e', ""}, {'f', ""}};
    vector<string> huffmancode = HuffmanCode(HT, w, n);
    for(int i = 0; i < huffmancode.size(); ++i)
        cout << huffmancode[i] << endl;
    // int i = 1;
    // for(map<char, string>::iterator iter = codes.begin(); iter != codes.end(); ++iter){
    //     iter->second = huffmancode[i];
    //     ++i;
    // }
    // for(map<char, string>::iterator iter = codes.begin(); iter != codes.end(); ++iter)
    //     cout << iter->first << "'s huffmanCode: " << iter->second << endl;
    // cout << "The cost: " << HT[2 * n - 1].freq << endl;

    // string s;
    // cout << "enter the string" << endl;
    // cin >> s;
    // string code = inCode(codes, s);
    // cout << code << endl;
    // s = deCode(HT, code, 6);
    // cout << s << endl;
    return 0;
}