#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int x;
    int y;
} Dragon;

int compareDragons(const void *a, const void *b) {
    Dragon *da = (Dragon *)a;
    Dragon *db = (Dragon *)b;
    return da->x - db->x;
}

int main() {
    int s, n;
    scanf("%d %d", &s, &n);
    Dragon dragons[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &dragons[i].x, &dragons[i].y);
    }

    qsort(dragons, n, sizeof(Dragon), compareDragons);

    long long current = s;
    for (int i = 0; i < n; i++) {
        if (current <= dragons[i].x) {
            printf("NO\n");
            return 0;
        }
        current += dragons[i].y;
    }

    printf("YES\n");
    return 0;
}