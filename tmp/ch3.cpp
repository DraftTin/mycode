#include <cstring>
#include <iostream>

using namespace std;

void test_1() {
	int* a = new int[10];
 
	//sizeof
	cout << "sizeof of a: " << sizeof(*a) << endl;
 
	//a地址
	cout <<"address of a: " << a << endl;
 
	//++
	cout << "++: " << ++a << endl;
 
	//--
	cout << "--:" << --a << endl;
 
	// +
	cout << "+: " << a + 1 << endl;

	// -
	cout << "-: " << a - 1 << endl;
 
	// &
	cout << "&: " << &a << endl;

	// *
	cout << "*: " << *a << endl;

	a[0] = 1;
	cout << "*: " << *a << endl;

	// cout << a * 2 << endl;
	// cout << a / 2 << endl;
	// void *b = new int[10];
	// b++;
	// b--;
}

void iniNrun() {
	//override
	static bool initialized = false;
	if(!initialized)	{cout << "initializing" << endl; initialized = true;} //此处不用写具体实现什么}
	else {cout << "ok" << endl;} //此处不用写具体实现什么}
}
 
int main()
{
	iniNrun();
	iniNrun();
	iniNrun();
	int a = 5;
	int * i = &a;
	*i += 5;
	cout << a << endl;
	int k = 1;
	int j = -100;
	switch (k) {
		case 1:
		case 2:
			j = 2 * k - 1;
			break;
		case 3:
		case 5:
			j = 3 * k + 1;
			break;
		case 4:
			j = 4 * k - 1;
			break;
		case 6:
		case 7:
		case 8:
			j = k - 2;
			break;
		default:
			break;
	}
	cout << j << endl;

	return 0;
}

/*
(base) ningyuheng@ningyuhengdeMacBook-Pro tmp % g++ test.cpp
(base) ningyuheng@ningyuhengdeMacBook-Pro tmp % ./a.out     
sizeof of a: 4
address of a: 0x120606a00
++: 0x120606a04
--:0x120606a00
+: 0x120606a04
-: 0x1206069fc
&: 0x16d8f2f80
*: 0
*: 1
*/