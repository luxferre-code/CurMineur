/*
 * Created by LuxFerre on 2023/05/17 
*/

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define NB_LIGNES 10
#define NB_COLONNES 10
#define PROBA_MINES 15

typedef struct game {
    char *map;
    int *visibility;
    int *flags;
    int nb_lignes;
    int nb_colonnes;
    int nb_mines;
} game;

game* init_game();
void genere_map(game* g);
void affiche_map(game* g);
int nb_voisin(game* g, int x, int y);
int active_case(game* g, int x, int y);

int main(void) {

    return 0;
}

game* init_game() {
    game* g = malloc(sizeof(game));
    g->nb_lignes = NB_LIGNES;
    g->nb_colonnes = NB_COLONNES;
    g->nb_mines = 0; // Not initialized on start
    g->map = malloc(sizeof(char) * g->nb_lignes * g->nb_colonnes);
    g->visibility = malloc(sizeof(int) * g->nb_lignes * g->nb_colonnes);
    g->flags = malloc(sizeof(int) * g->nb_lignes * g->nb_colonnes);
    return g;
}

void genere_map(game* g) {
    for(int x = 0; x < g->nb_lignes; x++) {
        for(int y = 0; y < g->nb_colonnes; y++) {
            
            if(rand() % 100 < PROBA_MINES) {
                g->map[x * g->nb_colonnes + y] = 'X';
                g->nb_mines += 1;
            } else {
                g->map[x * g->nb_colonnes + y] = ' ';
            }
            g->visibility[x * g->nb_colonnes + y] = 0;
        }
    }
}

void affiche_map(game* g) {
    for(int x = 0; x < g->nb_lignes; x++) {
        for(int y = 0; y < g->nb_colonnes; y++) {
            if(g->visibility[x * g->nb_colonnes + y] == 0) {
                printf("?");
            } else {
                printf("%c", g->map[x * g->nb_colonnes + y]);
            }
        }
        printf("\n");
    }
}

int nb_voisin(game* g, int x, int y) {
    int nb = 0;
    for(int i = x - 1; i <= x + 1; i++) {
        for(int j = y - 1; j <= y + 1; j++) {
            if(i >= 0 && i < g->nb_lignes && j >= 0 && j < g->nb_colonnes) {
                if(g->map[i * g->nb_colonnes + j] == 'X') {
                    nb += 1;
                }
            }
        }
    }
    return nb;
}

int active_case(game* g, int x, int y) {
    // Return 1 if the case is a mine, 0 otherwise
    if(g->map[x * g->nb_colonnes + y] == 'X') {
        return 1;
    } else {
        g->visibility[x * g->nb_colonnes + y] = 1;
        if(nb_voisin(g, x, y) == 0) {
            for(int i = x - 1; i <= x + 1; i++) {
                for(int j = y - 1; j <= y + 1; j++) {
                    if(i >= 0 && i < g->nb_lignes && j >= 0 && j < g->nb_colonnes) {
                        if(g->visibility[i * g->nb_colonnes + j] == 0) {
                            active_case(g, i, j);
                        }
                    }
                }
            }
        }
        return 0;
    }
}