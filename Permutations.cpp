#include <iostream>
#include <vector>	

using namespace std;

class Solution {
public:
 	static void nextPermution(vector<int>& nums){
    	for(int i = nums.size() - 1; i > 0; --i){
    		if(nums[i] > nums[i-1]){
    			int min = i;
    			int j;
    			for(j = i + 1; j < nums.size(); ++j){
    				if(nums[min] > nums[j] && nums[j] > nums[i - 1]){
    					min = j;
    				}
    			}
    			swap(nums[min], nums[i-1]);
    			quickSort(nums, i, nums.size() - 1);
    			return ;
    		}
    	}
    	for(int i = 0, j = nums.size() - 1; i < j; ++i, --j){
    		swap(nums[i], nums[j]);
    	}
    }
    static void swap(int& a, int& b){
	    int swap;
	    swap = a;
	    a = b;
	    b = swap;
	}
	static void quickSort(vector<int>& nums, int begin, int end){
	    if(begin >= end)
	        return ;
	    int mid = nums[begin], i = begin, j = end;
	    while(i < j){
	        while(i < j && nums[j] >= mid)
	            j--;
	        nums[i] = nums[j];
	        while(i < j && nums[i] <= mid)
	            i++;
	        nums[j] = nums[i];
	    }
	    nums[i] = mid;
	    quickSort(nums, begin, i - 1);
	    quickSort(nums, i + 1, end);
	}
    static vector<vector<int>> permute(vector<int>& nums) {
        int sum = 1;
        vector<int> copy = nums;
        for(int i = 2; i <= nums.size(); ++i){
        	sum *= i;
        }
        vector<vector<int>> res;
        for(int i = 0; i < sum; ++i){
        	res.push_back(nums);
        	nextPermution(nums);
        	if(judge(copy, nums)){
        		break;
        	}
        }
  		return res;
    }
    static bool judge(vector<int>& nums, vector<int> n){
    	for(int i = 0; i < nums.size(); ++i){
    		if(nums[i] != n[i]){
    			return false;
    		}
    	}
    	return true;
    }
};

int main(){
	vector<int> nums = {1,0,1};
	vector<vector<int>> permutions;
	permutions = Solution::permute(nums);
	for(vector<int> nums : permutions){
		for(int num : nums){
			cout << num << " ";
		}
		cout << endl;
	}
	return 0;
}


