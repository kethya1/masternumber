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
void jouer(int difficulte);
void quitterJeu();
int lireProposition(int proposition[], int tailleCode);

int main(void) {
    system("cls"); // Effacer l'écran au début du jeu
    unsigned int choix = 0;
    int difficulte = 4; // Valeur par défaut de la difficulté

    do {
        printf("+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
        printf("|                     MASTERNUMBER                          |\n");
        printf("|+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+|\n");  
        printf("|                                                           |\n");  
        printf("|   1. Jouer                                                |\n");
        printf("|   2. Changer la difficult%c (actuelle : %d chiffres)        |\n", 130, difficulte);
        printf("|   3. Quitter                                              |\n");
        printf("|                                                           |\n");
        printf("+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
        printf("Votre choix : ");

        do {
           
            if (scanf("%u", &choix) != 1) { // Vérifie si la saisie est invalide
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n'); // Vide le tampon d'entrée
            choix = 0; // Réinitialise le choix pour éviter un comportement inattendu
            }
        } while (choix == 0);

        switch (choix) {
            case 1:
                jouer(difficulte); // Passe la difficulté actuelle à la fonction jouer
                break;

            case 2:
                difficulte = niveauJeu(); // Met à jour la difficulté
                break;

            case 3:
                quitterJeu();
                break;

            default:
                printf("Mauvais choix. Veuillez réessayer.\n");
                break;
        }
    } while (choix != 3);

    return 0;
}

void jouer(int difficulte) {
    int codeSecret[difficulte];
    int essaisRestants;
    int proposition[difficulte];
    char indications[difficulte];
    int i; // Déclaration de la variable i à l'extérieur des boucles

    genererCodeSecret(codeSecret, difficulte);

    system("cls");
    printf("Devinez le code secret %c %d chiffres, les chiffres vont de %d %c %d.\n", 133, difficulte, VALEURMIN, 133, VALEURMAX);
    printf("Le 'X' indique qu'un chiffre est bien pla%c, le 'O' indique qu'un chiffre est correct mais mal plac%c.\n\n", 130, 130);

    for (essaisRestants = ESSAISMAX; essaisRestants > 0; --essaisRestants) {
        printf("Essais restants : %d\n", essaisRestants);

        if (!lireProposition(proposition, difficulte)) {
            printf("Rappel: %d chiffres sont attendus.\n", difficulte);
            ++essaisRestants; // Ne pas pénaliser pour une entrée invalide
            continue;
        }

        for (i = 0; i < difficulte; ++i) { // Initialisation de i dans la boucle
            indications[i] = '_';
        }

        Indices(codeSecret, proposition, indications, difficulte);

        printf(" +===============+\n");
        printf(" | ");
        for (i = 0; i < difficulte; ++i) { // Réutilisation de i
            printf("%d ", proposition[i]);
        }

        printf("    | ");
        for (i = 0; i < difficulte; ++i) { // Réutilisation de i
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
        for (i = 0; i < difficulte; ++i) { // Réutilisation de i
            if (indications[i] != 'X') {
                victoire = 0;
                break;
            }
        }

        if (victoire) {
            printf("\nGG ! Le code secret était bien : ");
            for (i = 0; i < difficulte; ++i) { // Réutilisation de i
                printf("%d ", codeSecret[i]);
            }
            printf("\n");
            return;
        }
    }

    printf("Nombre d'essais atteint ;-( Le code secret était : ");
    for (i = 0; i < difficulte; ++i) { // Réutilisation de i
        printf("%d ", codeSecret[i]);
    }
    printf("\n");
}

void quitterJeu() {
    printf("Vous avez choisi de quitter le jeu. Au revoir !\n");
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
    int i;

    // Initialisation des tabs à 0 
    for (i = 0; i < tailleCode; ++i) {
        marqueCode[i] = 0;
        marqueProp[i] = 0;
    }

    // Vérification des chiffres bien placés
    for (i = 0; i < tailleCode; ++i) {
        if (proposition[i] == codeSecret[i]) {
            indications[i] = 'X';
            marqueCode[i] = 1;
            marqueProp[i] = 1;
        }
    }

    // Vérification des chiffres corrects mais mal placés
    for (i = 0; i < tailleCode; ++i) {
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

