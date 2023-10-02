#include <iostream>
#include <string>

using namespace std;

int main() {
    std::string str;
int n = 10;

str.reserve(n);  // 预留空间

for (int i = 0; i < n; ++i) {
    str.push_back('!');  // 直接使用下标操作符修改每个位置的字符为 '!'
}

std::cout << str << std::endl;  // 输出：!!!!!!!!!!
return 0;
}
