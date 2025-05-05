#ifndef COULEUR_CONSOLE_H
#define COULEUR_CONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Couleur pour le texte*/
#define NOIR 30
#define ROUGE 31
#define VERT 32
#define JAUNE 33
#define BLEU 34
#define MAGENTA 35
#define CYAN 36
#define BLANC 37
#define GRIS 90


/*MACRO FONCTIONS*/
#define effacer_ecran() printf("\033[H\033[2J")
#define couleur_reset()	printf("\033[%dm",RESET)
#define couleur_texte(coul) printf("\033[%dm",coul)
#define couleur_fond(coul)	printf("\033[%dm",coul+10)



#endif
