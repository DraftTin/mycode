# golang learning note

## Basic Syntax

### comment
use '//' or '/* comment */' to comment

### Data Type
int, float32, bool, array, string, slice, map, pointer, struct, interface, func, interface{}

*note: interface{} represents any type*

### Function
func funcName(name1 type1, name2 type2) returnType {
    ....
}

## Details

### struct
``` go
type Person struct {
    name string
    age int
    job string
    salary int
}
```

### Interface
```go
type Shape interface {
    Area() float64
    Perimeter() float64
}

type Rectangle struct {
    width  float64
    height float64
}

func (r Rectangle) Area() float64 {
    return r.width * r.height
}

func (r Rectangle) Perimeter() float64 {
    return 2 * (r.width + r.height)
}
```

### About Interface{}
interface{} is a type that can represents any type because it doesn't require structs to implement any method.

```go
func describe(value interface{}) {
    fmt.Printf("Type: %T, Value: %v\n", value, value)
}

describe(42)
describe("Hello")
describe([]int{1, 2, 3})
```

## Others
1. 'var a int', or 'a := 2' to initialize variable
2. if-else: 'else' must be placed next to the curly brackets.
3. "[]int" represents **slice**, whose length is variable. "[...]int" or "[3]int" reprents **array**.
4. Golang only has **for** used for Loop Statement: "for i := 0; i < n; i++", "for condition", or for i := **range** arr

