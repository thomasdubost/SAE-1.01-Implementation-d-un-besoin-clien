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
    if (etudiant->semestre_en_cours > 1)
    {
        int a = 0;
    }
    printf("%d %s %s\n", etudiant->id_etudiant, etudiant->prenom, etudiant->nom);

    affichage_semestre(*etudiant);
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
void affichage_semestre(Etudiant etudiant)
{
    int nb_semestres = etudiant.semestre_en_cours;

    for (int s = 0; s < nb_semestres; s++)
    {
        if (s % 2 == 0 && s != 0)
        {
            affichage_bilan(etudiant, s / 2);
        }
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
        {
            printf("\n");
        }
    }
}
void affichage_bilan(Etudiant etudiant, int bilan_a_afficher)
{

    printf("B%d - ", bilan_a_afficher);
    for (int m = 0; m < NB_UE; m++)
    {
        float note = etudiant.bilan[bilan_a_afficher].UE[m].note;
        char *app = etudiant.bilan[bilan_a_afficher].UE[m].appreciation;
        if (note >= 0)
            printf("%.1f (%s)", note, app);
        else
            printf("* (*)");
        printf(" - ");
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
    int semestre_index = etudiant->semestre_en_cours - 1;
    etudiant->semestres[semestre_index].UE[UE_index].note = note;
    UE *semestre_actuel = &etudiant->semestres[semestre_index];
    char *appreciation = semestre_actuel->UE[UE_index].appreciation;

    // Déterminer l'appréciation en fonction de la note
    if (note >= 10)
        strcpy(appreciation, "ADM");
    else if (note <= 10 && note >= 8)
        strcpy(appreciation, "AJ");
    else if (note < 8)
        strcpy(appreciation, "AJB");
    else
        strcpy(appreciation, "ADS");
    printf("Note enregistree \n");
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

            if (etudiant->semestres[semestre - 1].UE[j].note == -1)
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

        if (semestre != etudiant->semestre_en_cours || etudiant->status != EN_COURS)
        {
            continue;
        }

        if (etudiant->semestre_en_cours % 2 == 1)
        {
            etudiant->semestre_en_cours++;
            nb_etudiant_affectes++;
            continue;
        }

        int semestre_index = etudiant->semestre_en_cours;

        // verification des notes pour le semestre d'actuel
        for (int num_ue = 0; num_ue < NB_UE; ++num_ue)
        {
            float note = etudiant->semestres[semestre_index].UE[num_ue].note;
            if (note < 10)
            {
                float note_semestre_precedent = etudiant->semestres[semestre_index - 1].UE[num_ue].note;
                float moyenne_note = (note + note_semestre_precedent) / 2;

                if (moyenne_note >= 10)
                {
                    strcpy(etudiant->semestres[semestre_index].UE[num_ue].appreciation, "ADC");
                }
            }
        }
        // verification des notes pour le semestre d'avant
        for (int num_ue = 0; num_ue < NB_UE; ++num_ue)
        {
            float note = etudiant->semestres[semestre_index - 1].UE[num_ue].note;
            if (note < 10)
            {
                float note_semestre_suivant = etudiant->semestres[semestre_index].UE[num_ue].note;
                float moyenne_note = (note + note_semestre_suivant) / 2;

                if (moyenne_note >= 10)
                {
                    strcpy(etudiant->semestres[semestre_index - 1].UE[num_ue].appreciation, "ADC");
                }
            }
        }
        etudiant->semestre_en_cours++;
        nb_etudiant_affectes++;
    }

    if (nb_etudiant_affectes != 0)
    {
        printf("Semestre termine pour %d etudiant(s)\n", nb_etudiant_affectes);
    }
}
void demission(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant)
{
    int id = atoi(separer_txt.list_arguments[0]);
    if (id < 1 || id > nb_etudiant)
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
