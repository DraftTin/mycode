#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {1, 2, 2, 3, 3, 3, 4, 5, 5};

    // 使用 std::unique 删除相邻的重复元素
    auto endIt = std::unique(nums.begin(), nums.end());

    // 输出去重后的容器内容
    for (auto it = nums.begin(); it != endIt; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for(auto i : nums) {
        std::cout << i << std::endl;
    }
    return 0;
}