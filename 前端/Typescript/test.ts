const COLORS = {
  red: 'red',
  blue: 'blue'
}

// 首先通过typeof操作符获取color变量的类型，然后通过keyof操作符获取该类型的所有键，
// 即字符串字面量联合类型 'red' | 'blue'

type Colors = keyof typeof COLORS 
let color: Colors;
color = 'red' // Ok
color = 'blue' // Ok

// Type '"yellow"' is not assignable to type '"red" | "blue"'.
color = 'yellow' // Error
