#include <iostream>
#include <vector>

using namespace std;

#define MAX 99999

vector<int> solution(vector<int>& PP, vector<int>& WW, int M){
    // 动态规划——01背包问题
    int n = PP.size() - 1;
    vector<int> F(PP.size() + 1);   // 用于记录S^i在P和W中的位置，记录S^0到S^{n - 1}
    vector<int> P(MAX); // 存储序偶对(P^i, W^i)
    vector<int> W(MAX); 
    P[1] = 0;
    W[1] = 0;
    int next = 2;
    int l = 1;
    int h = 1;
    F[0] = 1;
    F[1] = 2;
    for(int i = 1; i <= n - 1; ++i){
        int r = -1;
        int w = WW[i];
        int p = PP[i];
        for(int j = l; j <= h; ++j){
            if(W[j] + w > M) break;
            r = j;
        }
        int k = l;
        for(int j = l; j <= r; ++j){
            int pp = P[j] + p;
            int ww = W[j] + w;
            while(k <= h && W[k] < ww){
                P[next] = P[k];
                W[next] = W[k];
                ++next;
                ++k;
            }
            if(k <= h && W[k] == w){
                pp = max(P[k], pp);
                ++k;
            }
            if(pp > P[next - 1]){
                P[next] = pp;
                W[next] = ww;
                ++next;
            }
            while(k <= h && P[k] <= P[next - 1]) ++k;
        }
        while(k <= h){
            P[next] = P[k];
            W[next] = W[k];
            ++next;
            ++k;
        }
        l = h + 1;
        h = next - 1;
        F[i + 1] = next;
    }
    int p1 = P[F[n - 1]];
    int w1 = W[F[n - 1]];
    int p = PP[n];
    int w = WW[n];
    int maxP = INT_MIN; // 记录S^{n - 1}序偶对中(P[i] + p, W[i] + w)的最大值(W[i] + w <= M)
    int maxW = INT_MIN;
    for(int i = F[n - 1]; i < F[n]; ++i){
        if(P[i] + p > maxP && W[i] + w <= M){
            maxW = W[i] + w;
            maxP = P[i] + p;
        }
    }
    vector<int> X(n + 1, 0);
    int resP = 0;
    int resW = 0;
    if(maxP > p1){
        resP = maxP;
        resW = maxW;
    }
    else{
        resP = p1;
        resW = w1;
    }
    for(int i = n - 1; i >= 0; --i){
        int tmpP = resP - PP[i + 1];
        int tmpW = resW - WW[i + 1];
        for(int j = F[i]; j < F[i + 1]; ++j){
            if(P[j] == tmpP && W[j] == tmpW){
                X[i + 1] = 1;
                resP = tmpP;
                resW = tmpW;
                break;
            }
        }
    }
    return X;
}

int main(){
    int n;
    cin >> n;
    vector<int> PP(n + 1);
    vector<int> WW(n + 1);
    for(int i = 1; i <= n; ++i){
        cin >> PP[i] >> WW[i];
    }
    int M;
    cin >> M;
    vector<int> X = solution(PP, WW, M);
    for(int i = 1; i <= n; ++i){
        cout << X[i] << " ";
    }
    cout << endl;
    return 0;
}