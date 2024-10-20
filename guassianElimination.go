package main

import (
	"fmt"
)

// 将方程转换为mod 2矩阵
func convertEquations() ([][]int, []int) {
	// 输入的矩阵（20行12列），+ 表示 0，- 表示 1
	equations := [][]int{
		{1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0},
		{1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
		{0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1},
		{0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
		{1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1},
		{0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0},
		{1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0},
		{1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1},
		{0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0},
		{1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1},
		{0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0},
		{0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
		{0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
		{1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0},
		{1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0},
		{1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0},
	}

	// 右侧的结果向量
	results := []int{
		0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1,
	}

	return equations, results
}

// 高斯消元模2实现
func gaussianEliminationMod2(matrix [][]int, results []int) []int {
	rows := len(matrix)
	cols := len(matrix[0])

	// 消元过程
	for i := 0; i < rows; i++ {
		// 寻找第 i 列中可以作为主元的行
		if matrix[i][i] == 0 {
			for k := i + 1; k < rows; k++ {
				if matrix[k][i] == 1 {
					// 交换行
					matrix[i], matrix[k] = matrix[k], matrix[i]
					results[i], results[k] = results[k], results[i]
					break
				}
			}
		}

		// 消去第 i 行以下的所有行
		for k := i + 1; k < rows; k++ {
			if matrix[k][i] == 1 {
				// 将第 k 行和第 i 行做模2加法
				for j := i; j < cols; j++ {
					matrix[k][j] ^= matrix[i][j] // 1 XOR 1 = 0, 1 XOR 0 = 1, 0 XOR 0 = 0
				}
				results[k] ^= results[i]
			}
		}
	}

	// 回代求解
	solution := make([]int, cols)
	for i := rows - 1; i >= 0; i-- {
		solution[i] = results[i]
		for j := i + 1; j < cols; j++ {
			solution[i] ^= matrix[i][j] * solution[j]
		}
	}

	return solution
}

func main() {
	// 转换输入的方程为矩阵
	equations, results := convertEquations()

	// 通过高斯消元求解
	solution := gaussianEliminationMod2(equations, results)

	// 输出非零解的列索引（升序排列）
	fmt.Print("Solution columns: ")
	for i, val := range solution {
		if val == 1 {
			fmt.Printf("%d ", i+1)
		}
	}
	fmt.Println()
}
