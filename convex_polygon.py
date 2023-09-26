from itertools import combinations
from multiprocessing import pool
from pprint import pprint

INT_MAX = 9999999
def solve(polygon):
    if len(polygon) <= 2:
        # 无效图形
        return None 
    combinations = {}
    # 1. 初始化
    n = len(polygon)
    dp = [[INT_MAX for i in range(len(polygon))] for j in range(len(polygon))]
    for i in range(len(polygon)):
        dp[i][i] = 0
        if i < len(polygon) - 2:
            dp[i][i + 2] = polygon[i][i + 1] + polygon[i + 1][i + 2] + polygon[i][i + 2]
    # 2. 动态规划
    solve_dp(polygon, dp, 0, n - 1, combinations)
    # 3. 返回结果
    return dp, combinations

def solve_dp(polygon, dp, i, j, combinations):
    # 1. 递归边界
    if j == i + 1 or j == i:
        combinations[i, j] = set()
        return 0
    if j == i + 2:
        combinations[i, j] = {(i + 1, i + 2, j + 1)}
        return dp[i][j]
    if dp[i][j] != INT_MAX:
        return dp[i][j]
    # 2. 递归计算
    for k in range(i + 1, j):
        cost = solve_dp(polygon, dp, i, k, combinations) + solve_dp(polygon, dp, k, j, combinations) + polygon[i][j] + polygon[i][k] + polygon[k][j]
        if cost < dp[i][j]:
            dp[i][j] = cost
            combinations[i, j] = combinations[i, k] | combinations[k, j] | {(i + 1, j + 1, k + 1)}
    return dp[i][j]

def main():
    # 凸多边形动态规划
    # 1. 读取数据
    polygon = [[0 for i in range(8)] for j in range(8)]
    # for i in range(8):
    #     for j in range(i + 1, 8):
    #         polygon[i][j] = int(input("请输入第%d行第%d列的数据：" % (i + 1, j + 1)))
    polygon = [[0, 14, 25, 27, 10, 11, 24, 16],
               [0, 0, 18, 15, 27, 28, 16, 14],
               [0, 0, 0, 19, 14, 19, 16, 10],
               [0, 0, 0, 0, 22, 23, 15, 14],
               [0, 0, 0, 0, 0, 14, 13, 20],
               [0, 0, 0, 0, 0, 0, 15, 18],
               [0, 0, 0, 0, 0, 0, 0, 27],
               [0, 0, 0, 0, 0, 0, 0, 0]]
    # 2. 计算最优解
    dp, combinations = solve(polygon)
    # 3. 输出结果
    if dp != None:
        pprint(dp)
        print('best result: ', dp[0][len(polygon) - 1])
        print('combinations: ', combinations[0, len(polygon) - 1])
    else:
        print('invalid polygon')

if __name__ == '__main__':
    main()
