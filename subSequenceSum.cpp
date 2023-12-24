#include <iostream>
#include <vector>

using namespace std;

struct Segment{
	int begin;
	int last;
	int sum;
};

Segment solution(vector<int>& arr, int begin, int last){
    if(begin >= last) return {begin, last, arr[begin]};
    int mid = (begin + last) / 2;
    Segment segment1 = solution(arr, begin, mid);
    Segment segment2 = solution(arr, mid + 1, last);
    int l = mid;
    int lsum = INT_MIN;
    int r = mid + 1;
    int rsum = INT_MIN;
    int val = 0;
    for(int i = mid; i >= begin; --i){
        val += arr[i];
        if(val > lsum){
            lsum = val;
            l = i;
        }
    }
    val = 0;
    for(int i = mid + 1; i <= last; ++i){
        val += arr[i];
        if(val > rsum){
            rsum = val;
            r = i;
        }
    }
    int lrsum = lsum + rsum;
    if(lrsum == max(lrsum, max(segment1.sum, segment2.sum))){
        return {l, r, lrsum};
    }
    return segment1.sum > segment2.sum ? segment1 : segment2;
}

int main(){
    int n = 13;
    vector<int> arr(n);
    for(int i = 0; i < arr.size(); ++i){
        cin >> arr[i];
    }
    Segment segment = solution(arr, 0, arr.size() - 1);
    for(int i = segment.begin; i <= segment.last; ++i){
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "sum: " << segment.sum << endl;
    return 0; 
}