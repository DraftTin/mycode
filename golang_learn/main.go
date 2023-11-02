package main

import (
	"fmt"
)

func test(nums []int) {
	nums = nums[:2]
	fmt.Println(nums)
}

func main() {
	s := "1234"
	fmt.Printf("%T %T\n", 'A', s[0])
	fmt.Println(s)
}
