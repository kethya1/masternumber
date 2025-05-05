#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "couleur_console.h"

#define TAILLECODE 4
#define VALEURMIN 1
#define VALEURMAX 6
#define ESSAISMAX 10

void genererCodeSecret(int codeSecret[], int tailleCode);
void Indices(int codeSecret[], int proposition[], char indications[], int tailleCode);
int niveauJeu();
int quitterJeu();
int lireProposition(int proposition[], int tailleCode);

int main(void) {
    system("cls"); // Effacer l'écran au début du jeu

    // Afficher le titre en ASCII


    

    if (quitterJeu() == 1) {
        printf("Vous avez choisi de quitter le jeu. Au revoir !\n");
        return 0;
    }

    int difficulte = niveauJeu();
    int codeSecret[difficulte];
    int essaisRestants;
    int proposition[difficulte];
    char indications[difficulte];

    genererCodeSecret(codeSecret, difficulte);



    printf("Bienvenue dans le Mastermind %c chiffres !\n",133);
    printf("Devinez le code secret %c %d chiffres, les chiffres vont de %d %c %d.\n", 133, difficulte, VALEURMIN,133, VALEURMAX);
    printf("Le 'X' indique qu'un chiffre est bien placé, le 'O' indique qu'un chiffre est correct mais mal placé.\n\n");

    for (essaisRestants = ESSAISMAX; essaisRestants > 0; --essaisRestants) {
        printf("Essais restants : %d\n", essaisRestants);

        if (!lireProposition(proposition, difficulte)) {
            printf("Entree invalide. %d chiffres sont attendus.\n",difficulte);
            ++essaisRestants; // Ne pas pénaliser pour une entrée invalide
            continue;
        }

        for (int i = 0; i < difficulte; ++i) {
            indications[i] = '_';
        }

        Indices(codeSecret, proposition, indications, difficulte);

        printf(" +===============+\n");
        printf(" | ");
        for (int i = 0; i < difficulte; ++i) {
            printf("%d ", proposition[i]);
        }

        printf("    | ");
        for (int i = 0; i < difficulte; ++i) {
            if (indications[i] == 'X') {
                couleur_texte(VERT); // Vert pour 'X'
            } else if (indications[i] == 'O') {
                couleur_texte(ROUGE); // Rouge pour 'O'
            } else {
                couleur_texte(BLANC); // Blanc pour '_'
            }
            printf("%c ", indications[i]);
        }
        couleur_texte(BLANC); // Réinitialiser la couleur par défaut
        printf("|\n");
        printf(" +===============+\n");

        int victoire = 1;
        for (int i = 0; i < difficulte; ++i) {
            if (indications[i] != 'X') {
                victoire = 0;
                break;
            }
        }

        if (victoire) {
            printf("\nGG ! Le code secret était bien : ");
            for (int i = 0; i < difficulte; ++i) {
                printf("%d ", codeSecret[i]);
            }
            printf("\n");
            return 0;
        }
    }

    printf("Nombre d'essais atteint ;-( Le code secret était : ");
    for (int i = 0; i < difficulte; ++i) {
        printf("%d ", codeSecret[i]);
    }
    printf("\n");

    return 0;
}

void genererCodeSecret(int codeSecret[], int tailleCode) {
    srand(time(NULL));
    for (int i = 0; i < tailleCode; ++i) {
        codeSecret[i] = rand() % (VALEURMAX - VALEURMIN + 1) + VALEURMIN;
    }
}

void Indices(int codeSecret[], int proposition[], char indications[], int tailleCode) {
    int marqueCode[tailleCode];
    int marqueProp[tailleCode];
    memset(marqueCode, 0, sizeof(marqueCode));
    memset(marqueProp, 0, sizeof(marqueProp));

    for (int i = 0; i < tailleCode; ++i) {
        if (proposition[i] == codeSecret[i]) {
            indications[i] = 'X';
            marqueCode[i] = 1;
            marqueProp[i] = 1;
        }
    }

    for (int i = 0; i < tailleCode; ++i) {
        if (marqueProp[i]) continue;
        for (int j = 0; j < tailleCode; ++j) {
            if (!marqueCode[j] && proposition[i] == codeSecret[j]) {
                indications[i] = 'O';
                marqueCode[j] = 1;
                break;
            }
        }
    }
}

int niveauJeu() {
    int difficulte;
    do {
        printf("Envie de plus de difficulté ? Choisissez 4, 5, ou 6 chiffres à deviner : ");
        if (scanf("%d", &difficulte) != 1) {
            while (getchar() != '\n'); // Vider le buffer
            difficulte = 0;
        } else {
            while (getchar() != '\n'); // Vider le buffer après une saisie valide
        }
    } while (difficulte < 4 || difficulte > 6);

    return difficulte;
}

int quitterJeu() {
    int choix;
    do {
        printf("Tapez 0 pour jouer au jeu, 1 pour le quitter : ");
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n'); // Vider le buffer
            choix = -1;
        }
    } while (choix < 0 || choix > 1);

    return choix;
}

int lireProposition(int proposition[], int tailleCode) {
    char buffer[100];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return 0;
    }

    if (strlen(buffer) != tailleCode + 1 || buffer[tailleCode] != '\n') {
        return 0;
    }

    for (int i = 0; i < tailleCode; ++i) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            return 0;
        }
        proposition[i] = buffer[i] - '0';
        if (proposition[i] < VALEURMIN || proposition[i] > VALEURMAX) {
            return 0;
        }
    }

    return 1;
}
