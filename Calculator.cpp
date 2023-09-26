#include <bits/stdc++.h>

#define LENGTH 50

using namespace std;

char pre[][7]={         
	/*运算符之间的优先级制作成一张表格*/
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=','0'},
        {'>','>','>','>','0','>','>'},
        {'<','<','<','<','<','0','='}};

bool judge_integer(char ch){
	if(ch <= '9' && ch >= '0')
		return true;
	return false;
}

char judge_prority(char lhs, char rhs){
	// > > < < < > >
	// > > > > < > >
	// < < < < < = 0
	// > > > > 0 > >
	// < < < < < < =
	int i;
	switch(lhs){
		case '+': i = 0; break;
		case '-': i = 1; break;
		case '*': i = 2; break;
		case '/': i = 3; break;
		case '(': i = 4; break;
		case ')': i = 5; break;	
		case '#': i = 6; break;
	}
	int j;
	switch(rhs){
		case '+': j = 0; break;
		case '-': j = 1; break;
		case '*': j = 2; break;
		case '/': j = 3; break;	
		case '(': j = 4; break;
		case ')': j = 5; break;	
		case '#': j = 6; break;
		default: 
			return '?';
	}
	return pre[i][j];
}

double Operate(double lhs, char c, double rhs){
	if(c == '+')
		return lhs + rhs;
	if(c == '-')
		return lhs - rhs;
	if(c == '*')
		return lhs * rhs;
	if(c == '/')
		return lhs / rhs;
	return 0;
}

double Calculator(string& expression){
	char ch;
	stack<double> Opnd;		// 操作数栈
	stack<char> Optr;			// 操作符栈
	Optr.push('#');				// '#'作为判定表达式结束的符号
	istringstream exp(expression);
	exp >> ch;
	while(true){
		double num = 0;
		if(judge_integer(ch)){
			while(judge_integer(ch)){
				num = num * 10 + ch - '0';
				exp >> ch;
			}
			Opnd.push(num);
		}
		char c = Optr.top();
		double n1, n2;
		char cc;
		switch(judge_prority(c, ch)){
			case '>': 
				n2 = Opnd.top();	//栈顶元素是式子中右边的数字
				Opnd.pop();
				n1 = Opnd.top();
				Opnd.pop();
				cc = Optr.top();
				Optr.pop();
				Opnd.push(Operate(n1, cc, n2));
				break;
			case '<':
				Optr.push(ch);
				exp >> ch;
				break;
			case '=':
				Optr.pop();
				exp >> ch;
				break;
			case '0':
				cout << "wrong expression!";
				return -1;
			default: break;
		}
		if(ch == '#' && c == '#')
			break;
	}
	double res = Opnd.top();
	return res;
}

bool judge_expBrackets(string& expression){
	stack<char> sta;
	char ch;
	istringstream exp(expression);
	while(exp >> ch){
		if(ch == '(' || ch == '{' || ch == '[')
			sta.push(ch);
		else{
			switch(ch){
				case ')':
					if(sta.top() != '(')
						return false;
					sta.pop();
					break;
				case '}':
					if(sta.top() != '{')
						return false;
					sta.pop();
					break;
				case ']':
					if(sta.top() != '[')
						return false;
					sta.pop();
					break;
				default:
					break;
			}
		}
	}
	if(!sta.empty())
		return false;
	return true;
}

int main(){
	string exp;
	cout << "enter the expression:";
	getline(cin, exp);
	exp.push_back('#');
	if(judge_expBrackets(exp)){
		double res = Calculator(exp);
		cout << "The res is " << res << endl;
	}
	else
		cout << "format error" << endl;
 	return 0;
}