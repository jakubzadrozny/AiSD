#include <cstdio>
#include <cstdlib>

int main (int argc, char **argv) {
    srand(*argv[1]);
    int l = 2000;
    int k = rand() % 99 + 1;
    printf("%d %d\n", k, l);
    for (int i = 0; i < l; i++) {
        printf("%d ", rand() % 999 + 1);
    }
    puts("");
}
