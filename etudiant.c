#include <stdio.h>
#include <stdlib.h>
#include "etudiant.h"
#include <string.h>

int main()
{
    int etudiant_count = 0;
    Etudiant etudiant_list[MAX_ETUDIANTS];
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
        note(separer_txt, etudiant_list, *etudiant_count);
        break;
    case DEMISSION:
        demission(separer_txt, etudiant_list, *etudiant_count);
        break;
    case DEFAILLANCE:
        defaillance(separer_txt, etudiant_list, *etudiant_count);
        break;
    case JURY:
        jury(separer_txt, etudiant_list, *etudiant_count);
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
        texte_separer->command_type = DEMISSION;
    }
    else if (strcmp(token, "DEFAILLANCE") == 0)
    {
        texte_separer->command_type = DEFAILLANCE;
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
    init_ue(etudiant.semestres);
    etudiant.semestre_en_cours = 1;
    etudiant.bilan_en_cours = 1;
    etudiant.id_etudiant = ++(*nb_etudiant);
    etudiant.status = EN_COURS; // par défaut
    etudiant.annee = 1;
    list_etudiant[*nb_etudiant - 1] = etudiant;

    printf("Inscription enregistree (%d)\n", etudiant.id_etudiant);
}

void init_ue(UE semestres[])
{
    for (int i = 0; i < NB_SEMESTRES; ++i)
    {
        for (int j = 0; j < NB_UE; ++j)
        {
            semestres[i].UE[j].note = -1;
        }
    }
}

void cursus(const texte_separer separer_txt, int nb_etudiant, Etudiant *etudiant_list)
{
    if (separer_txt.arguments_cmp != 1)
    {
        return;
    }

    int id = atoi(separer_txt.list_arguments[0]);

    if (id > nb_etudiant || id < 1)
    {
        puts("Identifiant incorrect");
        return;
    }

    Etudiant *etudiant = &etudiant_list[id - 1];

    printf("%d %s %s\n", etudiant->id_etudiant, etudiant->prenom, etudiant->nom);

    affichage_semestre(*etudiant, etudiant->semestre_en_cours);
    // Statut final
    switch (etudiant->status)
    {
    case EN_COURS:
        printf("en cours\n");
        break;
    case AJOURNE:
        printf("ajourne\n");
        break;
    case STATUT_DEMISSION:
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
void affichage_semestre(Etudiant etudiant, int nb_semestres)
{

    for (int s = 0; s < nb_semestres; s++)
    {
        printf("S%d - ", s + 1);

        for (int m = 0; m < NB_UE; m++)
        {
            float note = etudiant.semestres[s].UE[m].note;
            char *app = etudiant.semestres[s].UE[m].appreciation;
            if (note != -1)
                printf("%.1f (%s)", note, app);
            else
                printf("* (*)");
            printf(" - ");
        }
        if (s + 1 != nb_semestres)
            printf("\n");
    }
}
void afficher_bilan(Etudiant etudiant, int)
{
    for (int b = 0; b < NB_BILANS; b++)
    {
        printf("B%d - ", b + 1);
        for (int m = 0; m < NB_UE; m++)
        {
            float note = etudiant.bilan[b].UE[m].note;
            char *app = etudiant.bilan[b].UE[m].appreciation;
            if (note >= 0)
                printf("%.1f (%s)", note, app);
            else
                printf("* (*)");
            printf(" - ");
        }
    }
}
void note(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant)
{
    int id = atoi(separer_txt.list_arguments[0]);

    if (id > nb_etudiant || id < 1)
    {
        puts("Identifiant incorrect");
        return;
    }

    int UE_index = atoi(separer_txt.list_arguments[1]) - 1;

    if (UE_index < 0 || UE_index > NB_UE)
    {
        return;
    }

    float note = atof(separer_txt.list_arguments[2]);

    if (note < 0 || note > NOTE_MAX)
    {
        return;
    }

    Etudiant *etudiant = &etudiant_list[id - 1];

    etudiant->semestres[0].UE[UE_index].note = note;

    // Déterminer l'appréciation en fonction de la note
    if (note >= 10)
        strcpy(etudiant->semestres[0].UE[UE_index].appreciation, "ADM");
    else if (note <= 10 && note >= 8)
        strcpy(etudiant->semestres[0].UE[UE_index].appreciation, "AJ");
    else if (note < 8)
        strcpy(etudiant->semestres[0].UE[UE_index].appreciation, "AJB");
    else if (note < 8 && (etudiant->semestres[0].UE[UE_index].note + etudiant->semestres[1].UE[UE_index].note) / 2)

        strcpy(etudiant->semestres[0].UE[UE_index].appreciation, "ADC");
    else
        strcpy(etudiant->semestres[0].UE[UE_index].appreciation, "ADS");

    printf("Note enregistree \n");
    return;
}

void jury(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant)
{
    int semestre = atoi(separer_txt.list_arguments[0]);
    if (semestre < 1 || semestre > NB_SEMESTRES)
    {
        puts("Semestre incorrect");
    }

    for (int i = 0; i < nb_etudiant; ++i)
    {
        Etudiant *etudiant = &etudiant_list[i];
        if (semestre != etudiant->semestre_en_cours || etudiant->status != EN_COURS)
        {
            continue;
        }
        for (int j = 0; j < NB_UE; ++j)
        {
            if (etudiant->semestres[semestre].UE[j].note == -1)
            {
                puts("Des notes sont manquantes");
                return;
            }
        }
    }
    int nb_etudiant_affectes = 0;
    for (int i = 0; i < nb_etudiant; ++i)
    {
        Etudiant *etudiant = &etudiant_list[i];
        if (semestre - 1 != etudiant->semestre_en_cours || etudiant->status != EN_COURS)
        {
            continue;
        }
        etudiant->semestre_en_cours++;
        nb_etudiant_affectes++;
    }
    printf("Semestre termine pour %d etudiant(s)\n", nb_etudiant_affectes);
}
void demission(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant)
{
    int id = atoi(separer_txt.list_arguments[0]);
    if (id <= 0 || id >= nb_etudiant)
    {
        puts("Identifiant incorrect");
        return;
    }

    Etudiant *etudiant = &etudiant_list[id - 1];

    if (etudiant->status != EN_COURS)
    {
        puts("Etudiant hors formation");
        return;
    }
    etudiant->status = STATUT_DEMISSION;
    puts("Demission enregistree");
}
void defaillance(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant)
{
    int id = atoi(separer_txt.list_arguments[0]);
    if (id <= 0 || id >= nb_etudiant)
    {
        puts("Identifiant incorrect");
        return;
    }

    Etudiant *etudiant = &etudiant_list[id - 1];

    if (etudiant->status != EN_COURS)
    {
        puts("Etudiant hors formation");
        return;
    }
    etudiant->status = DEFAILLANT;
    puts("Defaillance enregistree");
}
