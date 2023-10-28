package main

import (
	"fmt"
)

func test(nums []int) {
	nums = nums[:2]
	fmt.Println(nums)
}

func main() {
	fmt.Println(max(1, 2))
}
