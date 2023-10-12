package main

import "fmt"

type Stack []int

func (s *Stack) Push(value int) {
	*s = append(*s, value)
}

func (s *Stack) Pop() (int, bool) {
	if s.Empty() {
		return 0, false
	}
	index := len(*s) - 1
	value := (*s)[index]
	*s = (*s)[:index]
	return value, true
}

func (s *Stack) Empty() bool {
	return len(*s) == 0
}

func main() {
	stack := Stack{}
	stack.Push(1)
	stack.Push(2)
	stack.Push(3)

	for !stack.Empty() {
		value, _ := stack.Pop()
		fmt.Println(value)
	}
}
