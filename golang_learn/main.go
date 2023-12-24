package main

import (
	"fmt"
	"strings"
)

func main() {
	var b strings.Builder

	b.WriteString("Player list:\n")
	for i := 1; i < 5; i++ {
		b.WriteString(fmt.Sprintf("Player %d\n", i))
	}

	fmt.Print(b.String())
	fmt.Println(len(b.String()))
}

// Output:
// Player list:
// Player 1
// Player 2
// Player 3
// Player 4
