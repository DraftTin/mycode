#include <iostream>
#include <vector> 

using namespace std;

int search(vector<int>& arr, int val){
    // 无序查找, 减少比较的次数, 在尾部添加一个和val相等的元素, 只有走到尾部或者查找成功才会进行 i < size 的比较
    int i = 0;
    int size = arr.size();
    arr.push_back(val);
    while(i < size){
        if(arr[i] != val){
            ++i;
            continue;
        }
        else{
            break;
        }
    }
    arr.pop_back();
    return i == size ? -1 : i;
}

int binarySearch(vector<int>& arr, int val){
    // 有序查找的二分查找, O(logn)
    int l = 0, r = arr.size() - 1;
    int mid;
    while(l <= r){
        mid = (l + r) / 2;
        cout << mid << endl;
        // mid取端点中值的底
        if(arr[mid] > val){
            r = mid - 1;
        }
        else if(arr[mid] < val){
            l = mid + 1;
        }
        else{
            break;
        }
    }
    //返回-1 表示未找到
    return arr[mid] == val ? mid : -1;
}

int threePointSearch(vector<int>& arr, int val){
    int begin = 0;
    int last = arr.size() - 1;
    int point1;
    int point2;
    while(begin <= last){
        point1 = begin + (last - begin) / 3;
        point2 = begin + 2 * (last - begin) / 3;
        if(val < arr[point1]){
            last = point1 - 1;
        }
        else if(val > arr[point2]){
            begin = point2 + 1;
        }
        else if(val > arr[point1] && val < arr[point2]){
            begin = point1 + 1;
            last = point2 - 1;
        }
        else{
            break;
        }
    }
    if(arr[point1] == val) return point1;
    else return arr[point2] == val ? point2 : -1;
}

int strictBinarySearch(vector<int>& arr, int val){
    // 一致对半查找, 每次严格对半划分
    int m = arr.size() >> 1, i = (arr.size() + 1) >> 1;
    while(m != 0){
        if(arr[i] < val){
            i += (m + 1) >> 1;
            m >>= 1;
        }
        else if(arr[i] > val){
            i -= (m + 1) >> 1;
            m >>= 1;
        }
        else{
            return i;
        }
    }
    return -1;
}

int strictBinarySearchPlus(vector<int>& arr, int val){
    vector<int> delta;
    int j = 1;
    int tmp = 1;
    int m = (arr.size() + 1) >> 1;  
    while(m != 0){
        delta.push_back(m);
        ++j;
        tmp <<= 1;
        m = (arr.size() + tmp) >> j;
    }
    cout << endl;
    int i = delta[0];
    j = 0;
    while(delta[j] != 0){
        if(arr[i] < val){
            i += delta[j];
            ++j;
        }
        else if(arr[i] > val){
            i -= delta[j];
            ++j;
        }
        else{
            return i;
        }
    }
    return -1;
}

int fibonacciSearch(vector<int>& arr, int val){
    // 
    vector<int> fi_num = {0, 1};
    int num1 = 1;
    int num2 = 0;
    while(num1 - 1 < arr.size()){
        int tmp = num1;
        num1 = num2 + num1;
        num2 = tmp;
        fi_num.push_back(num1);
    }
    int low = 0;
    int high = arr.size() - 1;
    int length = arr.size();
    int k = 0;
    while(fi_num[k] - 1 < length){
        ++k;
    }
    int t = arr[arr.size() - 1];
    vector<int> arr_copy = arr;
    while(arr_copy.size() < fi_num[k] - 1){
        arr_copy.push_back(t);
    }
    // 长度为fi_num[k] - 1, 生成的(k-1)阶Fibonacci树
    while (low <= high)  {  
        int mid = low + fi_num[k - 1] - 1;   // 根节点为 f_(k-1), 在数组中表示为 fi_num[k - 1] - 1

        if (arr_copy[mid] == val)  {  
            if (mid <= length - 1)  {  
                return mid;  
            }  
            else  {  
                // 说明查找得到的数据元素是补全值  
                return length - 1;  
            }  
        }  
  
        if (arr_copy[mid] > val)  {  
            high = mid - 1;  
            k = k - 1;  
        }  
  
        if (arr_copy[mid] < val)  {  
            low = mid + 1;  
            k = k - 2;  
        }  
    }  
    return -1;
}

int main(){
    vector<int> arr = {1,2,3};

    cout << binarySearch(arr, 4);
    return 0;
}