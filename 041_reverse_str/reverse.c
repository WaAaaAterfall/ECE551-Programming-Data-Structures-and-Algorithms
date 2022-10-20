#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap_char(char * a, char * b) {
  char temp = *a;
  *a = *b;
  *b = temp;
}

void reverse(char * str) {
  //WRITE ME!
  size_t n = 0;
  if (str == NULL || *str == '\0') {
    n = 0;
  }
  else {
    while (str[n] != '\0') {
      n++;
    }
  }
  if (n == 0) {
    return;
  }
  else {
    size_t left = 0, right = n - 1;
    while (left < right) {
      swap_char(&str[left], &str[right]);
      left++;
      right--;
    }
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
