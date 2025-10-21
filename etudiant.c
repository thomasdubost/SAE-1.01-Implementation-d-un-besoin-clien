#include <stdio.h>
#include <stdlib.h>
#include "etudiant.h"
#include <string.h>

int main()
{
}

void choixcommande(char *command, Separertxt *Separertxt)
{
    // remplace le \n a la fin de la commande par un \0
    command_line[strcspn(command_line, "\n")] = 0;
    // récupérer la commande séparée
    ParsedCommand parsed_command = {0};
    parse_command(command_line, &parsed_command);

    switch (Separertxt->command_type)
    {
    case EXIT:
        exit();
        break;
    case INSCRIRE_ETUDIANT:
        inscrireEtudiant();
        break;
    case CURSUS:
        cursus();
        break;
    case NOTE:
        note();
        break;
    case DEMISSION_DEFAILLANCE:
        demissionDefaillance();
        break;
    case JURY:
        jury();
        break;
    case ETUDIANTS:
        etudiants();
        break;
    default:
        printf("Commande inconnue. Veuillez réessayer.\n");
        break;
    }
}

void separertxt(char *command, Separertxt *Separertxt)
{
    const char *token;
    token = strtok(command, " ");
    if (token == NULL)
    {
        Separertxt->command_type = UNKNOWN;
        return;
    }

    if (strcmp(token, "EXIT") == 0)
    {
        Separertxt->command_type = EXIT;
        return;
    }
    else if (strcmp(token, "INSCRIRE") == 0)
    {
        Separertxt->command_type = INSCRIRE_ETUDIANT;
    }
    else if (strcmp(token, "CURSUS") == 0)
    {
        Separertxt->command_type = CURSUS;
    }
    else if (strcmp(token, "NOTE") == 0)
    {
        // pour la commande justificatif car le dernier argument est une suite de plusieurs notes
        separertxt_justificatif(Separertxt);
        return;
    }
    else if (strcmp(token, "DEMISSION") == 0)
    {
        Separertxt->command_type = DEMISSION_DEFAILLANCE;
    }
    else if (strcmp(token, "JURY") == 0)
    {
        Separertxt->command_type = JURY;
    }
    else if (strcmp(token, "ETUDIANTS") == 0)
    {
        Separertxt->command_type = ETUDIANTS;
    }
    else
    {
        Separertxt->command_type = UNKNOWN;
        return;
    }

    int cmt = 0;
    const char *separator = " ";
    while ((token = strtok(NULL, token)) != NULL && cmt < MAX_ARGUMENTS_COUNT)
    {
        Separertxt->list_arguments[cmt] = token;
        cmt++;
    };
    Separertxt->arguments_count = cmt;
}
// Sépare les arguments de la commande Justificatif
void separertxt_justificatif(Separertxt *separertxt)
{
    const char *space_separator = " ";
    const char *newline_separator = "\n";
    int nb_argument = 0;
    separertxt->command_type = NOTE_INPUT;
    separertxt->list_arguments[0] = strtok(NULL, space_separator);
    ++nb_argument;
    separertxt->list_arguments[1] = strtok(NULL, space_separator);
    ++nb_argument;
    separertxt->list_arguments[2] = strtok(NULL, newline_separator);
    ++nb_argument;
    separertxt->arguments_count = nb_argument;
}

// Gère la commande inscription :
void inscrireEtudiant(const Separertxt separertxt, int *nb_students, Etudiant *student_list)
{
    if (separertxt.arguments_count < INSCRIPTION_ARGS_COUNT)
        return;

    for (int i = 0; i < *nb_students; ++i)
    {
        if ((((strcmp(separertxt.list_arguments[0], student_list[i].name)) == 0) &&
             (atoi(separertxt.list_arguments[1]) == student_list[i].group)))
        {
            puts("Nom incorrect");
            return;
        }
    }

    Etudiant etudiant;
    strcpy(etudiant.name, separertxt.list_arguments[0]);
    etudiant.group = atoi(separertxt.list_arguments[1]);
    etudiant.id_etudiant = ++*(nb_students);
    etudiant.nb_absence = 0;
    student_list[*nb_students - 1] = etudiant;

    printf("Inscription enregistree (%d)\n", etudiant.student_id);
}
}
