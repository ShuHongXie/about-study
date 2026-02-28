const origin = [1, 3, 5, 11, 13, 16, 20, 21, 33, 45, 66];
let min = 0,
  max = origin.length,
  mid;
let key = 21
while (min <= max) {
  mid = (min + max) / 2;
  if(origin[min] < key) {
    min += 1
  }
}
