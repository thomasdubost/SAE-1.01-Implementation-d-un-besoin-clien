#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996 6031)


enum {
    ANNEE_MAX = 3,
    MAX_CHAR = 30,
    NB_COMMANDES = 7,
    NOTES_MAX = 6,
    SEMESTRES = 6,
    NB_ETUDIANTS = 100,
    NOTES_SUR = 20
};

typedef struct {
    char nom[MAX_CHAR];
    char prenom[MAX_CHAR];
    int annee;
} Etudiant;

void inscrireEtudiant();
void cursus();
void note();
void demissionDefaillance();
void jury();
void etudiants();


int main() {
    char input[100];

    while (1) {
		scanf("%s", input);

        if (strcmp(input, "EXIT") == 0) break;

        else if (strcmp(input, "INSCRIRE") == 0) {


            inscrireEtudiant();
        }
        
        else if (strcmp(input, "CURSUS") == 0) {
            cursus();
        }
        
        else if (strcmp(input, "NOTE") == 0) {
            note();
        }
        
        else if (strcmp(input, "ETUDIANTS") == 0) {
            etudiants();
        } 

        else {
            printf("Commande inconnue: %s\n", input);
		}
    }

    return 0;
}

Etudiant etudiantsTab[NB_ETUDIANTS];
int nbEtudiants = 0;

void inscrireEtudiant() {
    char prenom[MAX_CHAR], nom[MAX_CHAR];
    scanf("%s %s", prenom, nom);

    if (strlen(prenom) > MAX_CHAR || strlen(nom) > MAX_CHAR || strchr(prenom, ' ') || strchr(nom, ' ')) {
        printf("Nom incorrect\n");
        return;
    }

    for (int i = 0; i < nbEtudiants; i++) {
        if (strcmp(etudiantsTab[i].prenom, prenom) == 0 && strcmp(etudiantsTab[i].nom, nom) == 0) {
            printf("Nom incorrect\n");
            return;
        }
    }

    Etudiant nouv;
    strncpy(nouv.prenom, prenom, MAX_CHAR);
    strncpy(nouv.nom, nom, MAX_CHAR);
    nouv.annee = 1;!
    etudiantsTab[nbEtudiants] = nouv;
    nbEtudiants++;

    printf("Inscription enregistree %d\n", nbEtudiants);
}
void cursus() { printf("Commande CURSUS reçue.\n"); }
void note() { printf("Commande NOTE reçue.\n"); }
void etudiants() { printf("Commande ETUDIANTS reçue.\n"); }

