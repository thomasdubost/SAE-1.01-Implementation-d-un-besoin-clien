#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_ARGUMENTS_COUNT 3
#define MAX_ARGUMENTS_LENGTH 256
#define MAX_NAME_TAILLE 50
#define INSCRIPTION_ARGS_COUNT 2
#define MAX_ETUDIANTS 100
#define NB_SEMESTRES 6
#define NB_BILANS 3
#define NB_UE 6
#define MAX_COMMAND_LENGTH 256
#define NOTE_MAX 20
#define APPRECIATION_LENGTH 5
#define NB_SEMESTRE_PAR_BILAN 2
#define STATUT_LENGTH 15
#define MAX_NOTE_INF_10 3
#define NB_ANNEE 3

typedef enum
{

    AJOURNE,
    EN_COURS,
    STATUT_DEMISSION,
    DIPLOME,
    DEFAILLANT,
} Status;

typedef enum
{
    UNKNOWN = -1,
    EXIT = 0,
    INSCRIRE_ETUDIANT,
    CURSUS,
    NOTE,
    NOTE_INPUT,
    DEMISSION,
    DEFAILLANCE,
    JURY,
    ETUDIANTS,
    BILAN,
} Command_type;

typedef struct
{
    Command_type command_type;
    char list_arguments[MAX_ARGUMENTS_COUNT][MAX_ARGUMENTS_LENGTH];
    int arguments_cmp;
} texte_separer;

typedef struct
{
    float note;
    char appreciation[APPRECIATION_LENGTH]; // exemple: "ADM", "AJ", "ADC", "ADS"
} Note;

typedef struct
{
    Note notes[NB_UE];
} UE;

typedef struct
{
    char nom[MAX_NAME_TAILLE];
    char prenom[MAX_NAME_TAILLE];
    int id_etudiant;
    UE semestres[NB_SEMESTRES];
    int semestre_en_cours;
    UE bilan[NB_BILANS];
    Status status;
} Etudiant;

void separertxt(char *command, texte_separer *texte_separer);
void choixCommande(char *command, int *etudiant_count, Etudiant *etudiant_list);
void inscrireEtudiant(const texte_separer separertxt, int *nb_students, Etudiant *student_list);
void texteSeparerNote(texte_separer *texte_separer);
void cursus(const texte_separer separer_txt, int nb_etudiant, Etudiant *etudiant_list);
void affichage_semestre(Etudiant etudiant);
void affichage_bilan(Etudiant etudiant, int bilan_a_afficher);
void note(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant);
void demission(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant);
void defaillance(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant);
void jury(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant);
void calculer_bilan(Etudiant *etudiant, int num_bilan);
void etudiants(const texte_separer separertxt, Etudiant *etudiant_list, int nb_etudiant);
void bilan_etu(const texte_separer separertxt, Etudiant *etudiant_list, int nb_etudiant);
void init_ue(UE semestres[]);

// Il recupere la commande et stock les etudiants et la command.
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
// choisie la command a appeler avec la commande separer en entrée
void choixCommande(char *command, int *etudiant_count, Etudiant *etudiant_list)
{
    // remplace le \n a la fin de la commande par un \0
    command[strcspn(command, "\n")] = 0;
    command[strcspn(command, "\r")] = 0;

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
        etudiants(separer_txt, etudiant_list, *etudiant_count);
        break;
    case BILAN:
        bilan_etu(separer_txt, etudiant_list, *etudiant_count);
        break;
    default:

        printf("Commande inconnue. Veuillez réessayer.\n");
        break;
    }
}
// separe la command du fgets en une command et des arguments a envoyer aux fonctions
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
    else if (strcmp(token, "BILAN") == 0)
    {
        texte_separer->command_type = BILAN;
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
    etudiant.id_etudiant = ++(*nb_etudiant);
    etudiant.status = EN_COURS; // par défaut
    list_etudiant[*nb_etudiant - 1] = etudiant;

    printf("Inscription enregistree (%d)\n", etudiant.id_etudiant);
}

void init_ue(UE semestres[])
{
    for (int i = 0; i < NB_SEMESTRES; ++i)
    {
        for (int j = 0; j < NB_UE; ++j)
        {
            semestres[i].notes[j].note = -1;
        }
    }
}
// affiche le cursus d'un etudiant
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
        puts("en cours");
        break;
    case AJOURNE:
        puts("ajourne");
        break;
    case STATUT_DEMISSION:
        puts("demission");
        break;
    case DIPLOME:
        puts("diplome");
        break;
    case DEFAILLANT:
        puts("defaillance");
        break;
    }
}
// affiche un cursus des notes en fonction du nombre de semestres avec un bilan tt les 2 semestres
void affichage_semestre(Etudiant etudiant)
{
    int nb_semestres = etudiant.semestre_en_cours;

    for (int s = 0; s < nb_semestres; s++)
    {
        if (s % 2 == 0 && s != 0)
        {
            affichage_bilan(etudiant, s / 2);
            printf("\n");
        }

        printf("S%d - ", s + 1);

        for (int m = 0; m < NB_UE; m++)
        {
            float note = etudiant.semestres[s].notes[m].note;
            char *app = etudiant.semestres[s].notes[m].appreciation;
            if (note != -1)
                printf("%.1f (%s)", floorf(note * 10.f) / 10.f, app);
            else
                printf("* (*)");
            printf(" - ");
        }
        if (s + 1 != nb_semestres)
        {
            printf("\n");
        }
    }

    if (etudiant.status == AJOURNE)
    {
        printf("\n");
        affichage_bilan(etudiant, etudiant.semestre_en_cours / 2);
    }

    if (nb_semestres == NB_SEMESTRES)
    {
        printf("\n");
        affichage_bilan(etudiant, NB_BILANS);
    }
}
// affiche un bilan eet arrondie la moyen a 10.f
void affichage_bilan(Etudiant etudiant, int bilan_a_afficher)
{

    printf("B%d - ", bilan_a_afficher);
    for (int m = 0; m < NB_UE; m++)
    {
        float note = etudiant.bilan[bilan_a_afficher - 1].notes[m].note;
        char *app = etudiant.bilan[bilan_a_afficher - 1].notes[m].appreciation;
        if (note >= 0)
            printf("%.1f (%s)", floorf(note * 10.f) / 10.f, app);
        else
            printf("* (*)");
        printf(" - ");
    }
}
// enregistrer une note dans une ue, dans un semestre, a un id
void note(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant)
{
    int id = atoi(separer_txt.list_arguments[0]);

    if (id > nb_etudiant || id < 1)
    {
        puts("Identifiant incorrect");
        return;
    }
    if (etudiant_list[id - 1].status != EN_COURS)
    {
        puts("Etudiant hors formation");
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
        puts("Note incorrecte");
        return;
    }

    Etudiant *etudiant = &etudiant_list[id - 1];
    int semestre_index = etudiant->semestre_en_cours - 1;
    etudiant->semestres[semestre_index].notes[UE_index].note = note;
    char *appreciation = etudiant->semestres[semestre_index].notes[UE_index].appreciation;

    // Déterminer l'appréciation en fonction de la note
    if (note >= 10)
        strcpy(appreciation, "ADM");
    else if (note < 10)
        strcpy(appreciation, "AJ");
    else
        strcpy(appreciation, "ADS");
    printf("Note enregistree\n");
}
// jury fait passer un etudiant a l'année suivante ou non, un etudiant doit avoir tt ses notes
void jury(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant)
{
    int semestre = atoi(separer_txt.list_arguments[0]);
    if (semestre < 1 || semestre > NB_SEMESTRES)
    {
        puts("Semestre incorrect");
        return;
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

            if (etudiant->semestres[semestre - 1].notes[j].note == -1)
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
        if (etudiant->status == DEFAILLANT)
        {
            continue;
        }
        if (etudiant->status == STATUT_DEMISSION)
        {
            continue;
        }
        if (semestre != etudiant->semestre_en_cours)
        {
            continue;
        }

        if (etudiant->semestre_en_cours % 2 == 1)
        {
            etudiant->semestre_en_cours++;
            nb_etudiant_affectes++;
            continue;
        }

        int semestre_index = etudiant->semestre_en_cours - 1;

        // verification des notes pour le semestre actuel
        for (int num_ue = 0; num_ue < NB_UE; ++num_ue)
        {
            float note = etudiant->semestres[semestre_index].notes[num_ue].note;
            float note_semestre_precedent = etudiant->semestres[semestre_index - 1].notes[num_ue].note;
            float moyenne_note = (note + note_semestre_precedent) / 2;

            if (note < 10 && note_semestre_precedent < 10)
            {
                continue;
            }

            if (note >= 10 || moyenne_note < 10)
            {

                continue;
            }

            strcpy(etudiant->semestres[semestre_index].notes[num_ue].appreciation, "ADC");
        }
        // verification des notes pour le semestre d'avant
        for (int num_ue = 0; num_ue < NB_UE; ++num_ue)
        {
            float note = etudiant->semestres[semestre_index - 1].notes[num_ue].note;
            float note_semestre_suivant = etudiant->semestres[semestre_index].notes[num_ue].note;
            float moyenne_note = (note + note_semestre_suivant) / 2;

            if (note < 10 && note_semestre_suivant < 10)
            {
                continue;
            }
            if (note >= 10 || moyenne_note < 10)
            {
                continue;
            }

            strcpy(etudiant->semestres[semestre_index - 1].notes[num_ue].appreciation, "ADC");
        }

        int num_bilan = etudiant->semestre_en_cours / NB_SEMESTRE_PAR_BILAN;
        calculer_bilan(etudiant, num_bilan);
        int compteur_inf_10 = 0;
        int deja_affectee = 0;

        for (int i = 0; i < NB_UE; i++)
        {
            float note = etudiant->bilan[num_bilan - 1].notes[i].note;

            if (note < 8)
            {
                etudiant->status = AJOURNE;
                nb_etudiant_affectes++;
                deja_affectee++;
                break;
            }

            if (note >= 8 && note < 10)
            {
                compteur_inf_10++;
            }
        }

        if (etudiant->semestre_en_cours == NB_SEMESTRES && etudiant->status == EN_COURS)
        {
            etudiant->status = DIPLOME;
            if (deja_affectee > 0)
            {
                nb_etudiant_affectes++;
            }

            continue;
        }

        if (etudiant->status == EN_COURS)
        {
            etudiant->semestre_en_cours++;

            nb_etudiant_affectes++;
        }

        if (compteur_inf_10 >= MAX_NOTE_INF_10 && etudiant->status != AJOURNE)
        {
            etudiant->status = AJOURNE;
            if (deja_affectee > 0)
            {
                nb_etudiant_affectes++;
            }
            continue;
        }
    }

    printf("Semestre termine pour %d etudiant(s)\n", nb_etudiant_affectes);
}
// calcul un bilan
void calculer_bilan(Etudiant *etudiant, int num_bilan)
{
    int numero_semestre_index = num_bilan * NB_SEMESTRE_PAR_BILAN - 1;
    for (int i = 0; i < NB_UE; ++i)
    {
        float note_semestre_1 = etudiant->semestres[numero_semestre_index - 1].notes[i].note;
        float note_semestre_2 = etudiant->semestres[numero_semestre_index].notes[i].note;
        float moyenne = (note_semestre_1 + note_semestre_2) / 2;
        etudiant->bilan[num_bilan - 1].notes[i].note = moyenne;
        char *appreciation_bilan = etudiant->bilan[num_bilan - 1].notes[i].appreciation;
        // Déterminer l'appréciation en fonction de la note
        if (moyenne >= 10)
            strcpy(appreciation_bilan, "ADM");
        else if (moyenne >= 8 && moyenne < 10)
            strcpy(appreciation_bilan, "AJ");
        else if (moyenne < 8)
            strcpy(appreciation_bilan, "AJB");
    }
}
// change se status d'unetudiant a demission
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
// change le status d'un etudiant a defaillant
void defaillance(const texte_separer separer_txt, Etudiant *etudiant_list, int nb_etudiant)
{
    int id = atoi(separer_txt.list_arguments[0]);
    if (id <= 0 || id > nb_etudiant)
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
// affiche tt les etudiants avec leur identifiant, leur prenom et nom, semestre en cours et leur status
void etudiants(const texte_separer separertxt, Etudiant *etudiant_list, int nb_etudiant)
{
    for (int i = 0; i < nb_etudiant; ++i)
    {
        Etudiant etudiant = etudiant_list[i];
        char statusEtudiant[STATUT_LENGTH];
        switch (etudiant.status)
        {
        case AJOURNE:
            strcpy(statusEtudiant, "ajourne");
            break;
        case EN_COURS:
            strcpy(statusEtudiant, "en cours");
            break;
        case STATUT_DEMISSION:
            strcpy(statusEtudiant, "demission");
            break;
        case DEFAILLANT:
            strcpy(statusEtudiant, "defaillance");
            break;
        case DIPLOME:
            strcpy(statusEtudiant, "diplome");
            break;
        }
        printf("%d - %s %s - S%d - %s\n", i + 1, etudiant.prenom, etudiant.nom, etudiant.semestre_en_cours, statusEtudiant);
    }
}
// fait le bilan des status des etudiants en fonction de l'année donnée en paramètre
void bilan_etu(const texte_separer separertxt, Etudiant *etudiant_list, int nb_etudiant)
{
    int annee = atoi(separertxt.list_arguments[0]);
    if (annee > NB_ANNEE)
    {
        puts("Annee incorrecte");
        return;
    }

    int demission = 0, defaillance = 0, encours = 0, ajourne = 0, passe = 0;

    for (int i = 0; i < nb_etudiant; i++)
    {
        Etudiant *etudiant = &etudiant_list[i];
        int index_semestre = NB_SEMESTRE_PAR_BILAN * annee;
        if (etudiant->semestre_en_cours < index_semestre)
        {
            switch (etudiant->status)
            {
            case AJOURNE:
                ++ajourne;
                break;
            case EN_COURS:
                ++encours;
                break;
            case STATUT_DEMISSION:
                ++demission;
                break;
            case DEFAILLANT:
                ++defaillance;
                break;
            }
        }
        if (etudiant->semestre_en_cours > index_semestre && (etudiant->semestre_en_cours < index_semestre + 2 || index_semestre >= NB_SEMESTRES))
        {
            if (etudiant->status == EN_COURS)
                ++passe;
        }
    }
    if (demission == 0 && defaillance == 0 && encours == 0 && ajourne == 0 && passe == 0)
    {
        puts("Annee incorrecte");
        return;
    }
    printf("%d demission(s)\n", demission);
    printf("%d defaillance(s)\n", defaillance);
    printf("%d en cours\n", encours);
    printf("%d ajourne(s)\n", ajourne);
    printf("%d passe(s)\n", passe);
}
