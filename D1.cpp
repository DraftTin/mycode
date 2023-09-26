#include <iostream>
#include <cstring>


void get_next(int next[], char s[], int s_begin, int s_end){
	int len = s_end - s_begin + 1;
	int i = 0;
	int j = -1;
	next[0] = -1;
	while(i != len){
		if(j == -1 || s[i + s_begin] == s[j + s_begin]){
			++i;
			++j;
			if(s[i + s_begin] == s[j + s_begin]){
				next[i] = next[j];
			}
			else{
				next[i] = j;
			}
		}
		else{
			j = next[j];
		}
	}
}


int KMP(char s1[], int len1, int s2_begin, int s2_end, int next[]){
	get_next(next, s1, s2_begin, s2_end);
	int len2 = s2_end - s2_begin + 1;
	int i = 0;
	int j = 0;
	while(i < len1 && j < len2){
		if(j == -1 || s1[i] == s1[j + s2_begin]){
			++i;
			++j;
		}
		else{
			j = next[j];
		}
	}
	if(j == len2) return i - j;
	else return -1;
}

int solution(char s[], int len){
	int next[100009];
	int len_b = 0;
	int len_p1 = 0;
	int len_p2 = 0;
	int mid;
	int l = 1;
	int r = len - 1;
	while(l <= r){
		// 查看[mid, len)区间的字符串是否是好后缀
		mid = (l + r) / 2;
		int tmp_len = len - mid;
		int pos = KMP(s, len, mid, len - 1, next); // 对字串进行匹配
		if(pos != mid){
			len_b = tmp_len;
			r = mid - 1;
			if(pos == 0){
				len_p2 = len_p1;
				len_p1 = tmp_len;
			}
		}
		else{
			if(len_b > 0) break; //若已经得到好后缀则退出
			l = mid + 1;
		}
	}
	if(len_p2 == 0) {
		// 若没有得到好中缀，则从好后缀的下一个位置开始寻找
		for(int i = len - len_b + 1; i < len; ++i){
			int tmp_len = len - i;
			int pos = KMP(s, len, i, len - 1, next); // 对字串进行匹配
			if(pos == 0){
				if(len_p1 == 0){
					len_p1 = tmp_len;
				}
				else{
					len_p2 = tmp_len;
					break;
				}
			}
		}
	}
	int len_m = len - 2 * len_p2 > 0 ? len - 2 * len_p2 : 0;
	std::cout << len_b << " " << len_m << std::endl;
	return len_b + len_m;
}

int main(){
	char s[100009];
	scanf("%s", s);
	int len = strlen(s);
	int sum = solution(s, len);
	printf("%d", sum);
	return 0;
}