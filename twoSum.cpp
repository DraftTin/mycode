#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	static bool cmp(pair<int, int>& num1, pair<int, int>& num2){return num1.second < num2.second;}
    static vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        vector<pair<int, int>> nn(nums.size());
        for(int i = 0; i < nums.size(); ++i){
        	nn[i] = {i, nums[i]};
        }
        sort(nn.begin(), nn.end(), cmp);
        for(int i = 0; i < nn.size(); ++i){
            int tar = target - nn[i].second;
            int start = i;
            int end = nn.size() - 1;
            int mid;
            while(start <= end){
                // cout << start << " " << end << " " << i << endl;
                mid = (end - start) / 2 + start;
                //cout << mid << endl;
                if(nn[i].first != nn[mid].first && nn[mid].second == tar){
                    res.push_back(nn[i].first);
                    res.push_back(nn[mid].first);
                    return res;
                }
                if(nn[mid].second <= tar){
                    start = mid + 1;
                }
                else{
                    end = mid - 1;
                }
            }
        }
        return res;
    }
};

int main(){
	vector<int> nums = {3,2,4};
	int target = 6;
	vector<int> res = Solution::twoSum(nums, target);
	for(int tmp : res)
		cout << tmp << " ";
}