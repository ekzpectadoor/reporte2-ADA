#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} Dragon;

int compareDragons(const void *a, const void *b) {
    Dragon *da = (Dragon *)a;
    Dragon *db = (Dragon *)b;
    return da->x - db->x;
}

void generate_dragons(Dragon *dragons, int n) {
    for (int i = 0; i < n; i++) {
        dragons[i].x = rand() % 10000 + 1;   // Fuerza entre 1-10000
        dragons[i].y = rand() % 100001;      // Bonus entre 0-100000
    }
}

int main() {
    srand(time(NULL));  // Semilla para números aleatorios

    // Configuración de pruebas
    int step = 10000;         // Tamaño de paso entre pruebas
    int max_n = 100000;       // Máximo número de dragones
    int s = 1000000000;       // Fuerza inicial (suficientemente grande)

    // Archivo para resultados
    FILE *fp = fopen("dragons_performance.csv", "w");
    fprintf(fp, "n,time_ms,iterations\n");

    printf("Generando datos de rendimiento...\n");
    printf("n\ttiempo(ms)\titeraciones\n");

    for (int n = step; n <= max_n; n += step) {
        Dragon *dragons = (Dragon *)malloc(n * sizeof(Dragon));
        generate_dragons(dragons, n);

        clock_t start = clock();
        
        // Paso 1: Ordenar dragones
        qsort(dragons, n, sizeof(Dragon), compareDragons);
        
        // Paso 2: Simular batallas
        long long current = s;
        int iterations = 0;
        for (int i = 0; i < n; i++) {
            iterations++;
            current += dragons[i].y;
        }
        
        clock_t end = clock();
        double time_ms = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        
        // Guardar resultados
        fprintf(fp, "%d,%.2f,%d\n", n, time_ms, iterations);
        printf("%d\t%.2f\t%d\n", n, time_ms, iterations);
        
        free(dragons);
    }

    fclose(fp);
    printf("\nDatos guardados en dragons_performance.csv\n");
    printf("1. n vs time_ms: Complejidad O(n log n)\n");
    printf("2. n vs iterations: Complejidad O(n)\n");

    return 0;
}