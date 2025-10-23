#include <stdio.h>
#include <stdlib.h>
#include "etudiant.h"
#include <string.h>

int main()
{
    int etudiant_count = 0;
    Etudiant etudiant_list[MAX_ETUDIANTS] = {0};
    char command[MAX_COMMAND_LENGTH];
    while (1)
    {

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            continue;
        }
        choixCommande(command, &etudiant_count, etudiant_list);
    }
}

void choixCommande(char *command, int *etudiant_count, Etudiant *etudiant_list)
{
    // remplace le \n a la fin de la commande par un \0
    command[strcspn(command, "\n")] = 0;
    // récupérer la commande séparée
    texte_separer separer_txt = {0};
    separertxt(command, &separer_txt);

    switch (separer_txt.command_type)
    {
    case EXIT:
        exit(0);
        break;
    case INSCRIRE_ETUDIANT:
        inscrireEtudiant(separer_txt, etudiant_count, etudiant_list);
        break;
    case CURSUS:
        cursus(separer_txt, *etudiant_count, etudiant_list);
        break;
    case NOTE:
        // note();
        break;
    case DEMISSION_DEFAILLANCE:
        // demissionDefaillance();
        break;
    case JURY:
        // jury();
        break;
    case ETUDIANTS:
        // etudiants();
        break;
    default:
        printf("Commande inconnue. Veuillez réessayer.\n");
        break;
    }
}

void separertxt(char *command, texte_separer *texte_separer)
{
    const char *token;
    token = strtok(command, " ");
    if (token == NULL)
    {
        texte_separer->command_type = UNKNOWN;
        return;
    }

    if (strcmp(token, "EXIT") == 0)
    {
        texte_separer->command_type = EXIT;
        return;
    }
    else if (strcmp(token, "INSCRIRE") == 0)
    {
        texte_separer->command_type = INSCRIRE_ETUDIANT;
    }
    else if (strcmp(token, "CURSUS") == 0)
    {
        texte_separer->command_type = CURSUS;
    }
    else if (strcmp(token, "NOTE") == 0)
    {
        texte_separer->command_type = NOTE;
    }
    else if (strcmp(token, "DEMISSION") == 0)
    {
        texte_separer->command_type = DEMISSION_DEFAILLANCE;
    }
    else if (strcmp(token, "JURY") == 0)
    {
        texte_separer->command_type = JURY;
    }
    else if (strcmp(token, "ETUDIANTS") == 0)
    {
        texte_separer->command_type = ETUDIANTS;
    }
    else
    {
        texte_separer->command_type = UNKNOWN;
        return;
    }

    int cmt = 0;
    while ((token = strtok(NULL, " ")) != NULL && cmt < MAX_ARGUMENTS_COUNT)
    {
        strcpy(texte_separer->list_arguments[cmt], token);
        cmt++;
    };
    texte_separer->arguments_cmp = cmt;
}

// Inscrire un étudiant
void inscrireEtudiant(const texte_separer separertxt, int *nb_etudiant, Etudiant *list_etudiant)
{
    if (separertxt.arguments_cmp < INSCRIPTION_ARGS_COUNT)
        return;

    for (int i = 0; i < *nb_etudiant; ++i)
    {
        if (strcmp(separertxt.list_arguments[0], list_etudiant[i].prenom) == 0 &&
            strcmp(separertxt.list_arguments[1], list_etudiant[i].nom) == 0)
        {
            puts("Nom incorrect");
            return;
        }
    }

    Etudiant etudiant = {-1};
    strcpy(etudiant.prenom, separertxt.list_arguments[0]);
    strcpy(etudiant.nom, separertxt.list_arguments[1]);
    etudiant.id_etudiant = ++(*nb_etudiant);
    etudiant.status = EN_COURS; // par défaut
    etudiant.annee = 1;
    list_etudiant[*nb_etudiant - 1] = etudiant;

    printf("Inscription enregistree (%d)\n", etudiant.id_etudiant);
}

void cursus(const texte_separer separer_txt, int nb_etudiant, Etudiant *etudiant_list)
{
    if (separer_txt.arguments_cmp < 1)
    {
        printf("Erreur : ID étudiant manquant.\n");
        return;
    }

    int id = atoi(separer_txt.list_arguments[0]);
    Etudiant *etudiant = NULL;

    // Recherche de l’étudiant
    for (int i = 0; i < nb_etudiant; i++)
    {
        if (etudiant_list[i].id_etudiant == id)
        {
            etudiant = &etudiant_list[i];
            break;
        }
    }

    if (etudiant == NULL)
    {
        printf("Aucun étudiant trouvé avec l’ID %d.\n", id);
        return;
    }

    // Affichage en-tête
    printf("%s %s\n", etudiant->prenom, etudiant->nom);

    // Affichage des semestres
    for (int s = 0; s < NB_SEMESTRES; s++)
    {
        printf("S%d - ", s + 1);
        for (int m = 0; m < NB_MATIERES; m++)
        {
            float note = etudiant->semestres[s].matieres[m].note;
            char *app = etudiant->semestres[s].matieres[m].appreciation;
            if (note >= 0)
                printf("%.1f (%s)", note, app);
            else
                printf("* (*)");
            if (m < NB_MATIERES - 1)
                printf(" - ");
        }
        printf(" -\n");
    }

    // Affichage des différents blocs
    for (int b = 0; b < NB_BLOCS; b++)
    {
        printf("B%d - ", b + 1);
        for (int m = 0; m < NB_MATIERES; m++)
        {
            float note = etudiant->blocs[b].matieres[m].note;
            char *app = etudiant->blocs[b].matieres[m].appreciation;
            if (note >= 0)
                printf("%.1f (%s)", note, app);
            else
                printf("* (*)");
            if (m < NB_MATIERES - 1)
                printf(" - ");
        }
        printf(" -\n");
    }

    // Statut final
    switch (etudiant->status)
    {
    case EN_COURS:
        printf("en cours\n");
        break;
    case AJOURNE:
        printf("ajourne\n");
        break;
    case DEMISSION:
        printf("demission\n");
        break;
    case DIPLOME:
        printf("diplome\n");
        break;
    default:
        printf("statut inconnu\n");
        break;
    }
}
