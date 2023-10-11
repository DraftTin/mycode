package main

import (
	"errors"
	"fmt"
	"os"
)

func main() {
	err := openFile("nonexistentfile.txt")
	if err != nil {
		if errors.Is(err, os.ErrPermission) {
			fmt.Println("权限错误")
		} else if errors.Is(err, os.ErrNotExist) {
			fmt.Println("文件不存在错误")
		} else {
			fmt.Println("未知错误:", err)
		}

		// 打印完整的错误链
		fmt.Println("完整错误链:")
		fmt.Println(err)
	}
}

func openFile(path string) error {
	_, err := os.Open(path)
	if err != nil {
		return fmt.Errorf("路径错误: %w", err)
	}
	return nil
}
