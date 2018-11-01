// Jakub Zadrożny 290920 KLO
#include<cstdio>

int main () {
    int a, b;
    scanf("%d%d", &a, &b);
    int start = a / 2018 * 2018;
    while(start < a) start += 2018;
    while(start <= b) {
        printf("%d ", start);
        start += 2018;
    }
    puts("");
}