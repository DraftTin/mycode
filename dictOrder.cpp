#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(char &a, char &b)
{
	char tmp = a;
	a = b;
	b = tmp;
}

void quicksort(string &items, int begin, int end)
{
	if(begin >= end)
		return ;
	int mid = items[begin];
	int i = begin, j = end;
	while(i < j)
	{
		while(i < j && items[j] >= mid)
			--j;
		items[i] = items[j];
		while(i < j && items[i] <= mid)
			++i;
		items[j] = items[i];
	}
	items[i] = mid;
	quicksort(items, begin, i - 1);
	quicksort(items, i + 1, end);
}

void nextPermutation(string &items)
{
	for(int i = items.size() - 2; i >= 0; --i)
	{
		if(items[i] < items[i + 1])
		{
			int min = i + 1;
			for(int j = i + 1; j < items.size(); ++j)
			{
				if(items[j] < items[min] && items[j] > items[i])
					min = j;
			}
			swap(items[i], items[min]);
			quicksort(items, i + 1, items.size() - 1);
			
			return ;
		}
	}
	for(int i = 0, j = items.size(); i < j; ++i, --j)
		swap(items[i], items[j]);
}

int main(void)
{
	string items;
	vector<string> res;
	cout << "please input the items" << endl;
	cin >> items;
	int sum = 1;
	int n = items.size();
	while(n)
	{
		sum *= n;
		--n;
	}
	for(int i = 0; i < sum; ++i)
	{
		res.push_back(items);
		nextPermutation(items);
	}
	for(int i = 0; i < res.size(); ++i)
		cout << res[i] << endl;
	vector<string> evenReplacement;
	cout << endl;
	for(int i = 0; i < res.size(); ++i)
	{
		string nn = res[i];
		vector<int> roots(nn.size(), -1);
		int count = nn.size();
		for(int j = 0; j < nn.size(); ++j)
		{
			if(roots[j] == -1)
			{
				roots[j] = j;	//j的根是自己
				--count; //一个轮换count - 1
			}
			else
				continue;
			char tmp = nn[j]; //tmp - '0'表示数字映射的数字, tmp赋值为j + 1映射的值
			while(j + 1 != tmp - '0')
			{
				roots[tmp - '0' - 1] = j;
				tmp = nn[tmp - '0' - 1];
			}
		}
		if(count % 2 == 0)
			evenReplacement.push_back(nn);
	}
	for(int i = 0; i < evenReplacement.size(); ++i)
		cout << evenReplacement[i] << endl;
	cout << evenReplacement.size() << endl;
	system("pause");
	return 0;
}
