#include <stdio.h>
#include <string.h>



int main() {
  char s[] = "ABCCDA";
  int k; char c;
  for (k = 1; (c = s[k]) != '\0'; k++) {
    printf("%c", c);
    switch (c){
      case 'A': 
        putchar('%'); 
        continue;
      case 'B':
        ++k; 
        break;
      default:
        putchar('*');
      case 'C':
        putchar('#'); 
        continue;
    }
    putchar('@');
  }
  return 0;
}