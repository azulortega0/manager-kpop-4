#include <stdio.h>
#include <string.h>

typedef struct {
    char nombre[50];
    int vigencia;
} Cancion;

typedef struct {
    char nombre[50];
    int energia;
    int popularidad_total;
    int activa;
    Cancion *cancion;
} Idol;

typedef struct {
    char nombre_grupo[50];
    Idol *miembros[10];
    int num_miembros;
    Idol *lider;
    int energia_max;
} Grupo;

// HU-21: Dar un concierto
void dar_concierto(Grupo *g) {
    if (g == NULL) return;

    for (int i = 0; i < g->num_miembros; i++) {
        if (g->miembros[i] != NULL && g->miembros[i]->activa) {
            g->miembros[i]->popularidad_total += 10;
            
            g->miembros[i]->energia -= 15;
            if (g->miembros[i]->energia < 0) {
                g->miembros[i]->energia = 0;
            }

            if (g->miembros[i]->cancion != NULL) {
                if (g->miembros[i]->cancion->vigencia > 0) {
                    g->miembros[i]->cancion->vigencia--;
                    if (g->miembros[i]->cancion->vigencia == 0) {
                        printf("La cancion %s ya no esta vigente.\n", g->miembros[i]->cancion->nombre);
                    }
                }
            }
        }
    }
}

// HU-23: Mostrar la canción de la líder sin fallar
void mostrar_cancion_lider(const Grupo *g) {
    if (g == NULL) {
        printf("No hay grupo.\n");
        return;
    }
    if (g->lider == NULL) {
        printf("El grupo no tiene lider.\n");
        return;
    }
    if (g->lider->cancion == NULL) {
        printf("La lider %s no tiene cancion.\n", g->lider->nombre);
        return;
    }

    printf("Cancion de la lider (%s): %s\n", g->lider->nombre, g->lider->cancion->nombre);
}

// HU-24: Preparar la presentación del grupo
void preparar_presentacion(Grupo *g) {
    if (g == NULL) return;

    dar_concierto(g);

    printf("--- Resumen ---\n");
    printf("Grupo: %s\n", g->nombre_grupo);
    
    int activas = 0;
    for (int i = 0; i < g->num_miembros; i++) {
        if (g->miembros[i] != NULL && g->miembros[i]->activa) {
            activas++;
        }
    }
    printf("Integrantes activas: %d\n", activas);
    mostrar_cancion_lider(g);
}