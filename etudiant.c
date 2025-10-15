#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum status
{
    admis,
    exclus,
    demissionne,
    defaillant,
} Status;
enum command_type
{
    UNKNOWN = -1,
    EXIT = 0,
    INSCRIRE_ETUDIANT,
    CURSUS,
    NOTE,
    DEMISSION_DEFAILLANCE,
    JURY,
    ETUDIANTS,

};
typedef struct command
{
    enum command_type type;
    int arg1;
    int arg2;
    int arg3;
};

typedef enum UE
{
    UE1 = 1,
    UE2,
    UE3,
    UE4,
    UE5,
    UE6,
} UE;

typedef enum semestre
{
    paire,
    impaire,

} Semestre;

typedef struct etudiant
{
    int id_etu;
    int notes[6];
    char status[10];
    char nom[20];
    char prenom[20];
    Status stat;
    Semestre sem;
    int annee;
} Etudiant;

void separertxt(char *input, struct command *cmd);
void choixcommande(char *input,struct command *cmd);

void exit();
void inscrireEtudiant();
void cursus();
void note();
void demissionDefaillance();
void jury();
void etudiants();

void separertxt(char *input, struct command *cmd)
{
    const char *token;
    token = strtok(input, " ");
    if (token == NULL)
    {
        cmd->type = UNKNOWN;
        return;
    }

    if (strcmp(token, "EXIT") == 0)
    {
        cmd->type = EXIT;
        return;
    }
    else if (strcmp(token, "INSCRIRE") == 0)
    {
        cmd->type = INSCRIRE_ETUDIANT;
    }
    else if (strcmp(token, "CURSUS") == 0)
    {
        cmd->type = CURSUS;
    }
    else if (strcmp(token, "NOTE") == 0)
    {
        cmd->type = NOTE;
    }
    else if (strcmp(token, "DEMISSION") == 0)
    {
        cmd->type = DEMISSION_DEFAILLANCE;
    }
    else if (strcmp(token, "JURY") == 0)
    {
        cmd->type = JURY;
    }
    else if (strcmp(token, "ETUDIANTS") == 0)
    {
        cmd->type = ETUDIANTS;
    }
    else
    {
        cmd->type = UNKNOWN;
        return;
    }

    int count = 0;
    const char *separator = " ";
    while ((word = strtok(NULL, token)) != NULL && count < MAX_ARGUMENTS_COUNT)
    {
        command->arguments_list[count] = word;
        count++;
    };
    parsed_command->arguments_count = count;
    }
    
}   
    void choixcommande(char *input,struct command *cmd)
    {
        switch (cmd->type)
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
        inscrireEtudiant(){

        }
    }
    
