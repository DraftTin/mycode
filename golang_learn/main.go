package main

import (
	"fmt"
	"sort"
)

func test(nums []int) {
	nums = nums[:2]
	fmt.Println(nums)
}

func main() {
	s := "1234"
	fmt.Printf("%T %T\n", 'A', s[0])
	sort.Find()
	sort.Search()
	fmt.Println(s)
}
