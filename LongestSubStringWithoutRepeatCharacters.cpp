#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    static int lengthOfLongestSubstring(string s) {
       	int i = 0, j = 0;
       	int maxlen = 0;
       	map<char, int> characters;
       	while(j < s.size()){
       		if(characters.find(s[j]) != characters.end()){
       			characters.erase(s[i]);
       			++i;
       		}
       		else{
       			characters[s[j]] = 1;
       			++j;
       			maxlen = j - i > maxlen ? j - i : maxlen;
       		}
       	}
       	return maxlen;
    }
};

int main(){
	string s;
	cin >> s;
	cout << Solution::lengthOfLongestSubstring(s) << endl;
	return 0;
}