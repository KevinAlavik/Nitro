#include <stdio.h>

int main() {
    char text[] = "ö";
    
    for (int i = 0; text[i] != '\0'; ++i) {
        printf("Integer value of %c is %d\n", text[i], (int)text[i]);
    }

    return 0;
}
