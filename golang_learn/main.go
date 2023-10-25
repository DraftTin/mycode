package main

import (
	"fmt"
)

func test(nums []int) {
	nums = nums[:2]
	fmt.Println(nums)
}

func main() {
	a := []int{6, 5, 4}
	test(a)
	fmt.Println(a)
}
