#include <iostream>
#include <vector>

using namespace std;

/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

 

Example 1:

Input: nums = [3,2,3]
Output: [3]
Example 2:

Input: nums = [1]
Output: [1]
Example 3:

Input: nums = [1,2]
Output: [1,2]
 

Constraints:

1 <= nums.length <= 5 * 104
-109 <= nums[i] <= 109
*/

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int count1 = 0, count2 = 0;
        int candidate1 = -1, candidate2 = -2;
        for(int i = 0; i < nums.size(); ++i) {
            if(nums[i] == candidate1) {
                ++count1;
            }
            else if(nums[i] == candidate2) {
                candidate2 = nums[i];
                ++count2;
            }
            else if(count1 == 0) {
                candidate1 = nums[i];
                count1 = 1;
            }
            else if(count2 == 0) {
                candidate2 = nums[i];
                count2 = 1;
            }
            else {
                --count1;
                --count2;
            }
        }
        count1 = 0;
        count2 = 0;
        for(auto n : nums) {
            if(n == candidate1) ++count1;
            if(n == candidate2) ++count2;
        }
        vector<int> res;
        if(count1 > nums.size() / 3) res.push_back(candidate1);
        if(count2 > nums.size() / 3) res.push_back(candidate2);
        return res;
    }
};