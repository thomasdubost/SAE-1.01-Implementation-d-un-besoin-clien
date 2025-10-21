#define MAX_ARGUMENTS_COUNT 3
typedef enum
{
    admis,
    exclus,
    demissionne,
    defaillant,
} Status;

typedef enum
{
    UNKNOWN = -1,
    EXIT = 0,
    INSCRIRE_ETUDIANT,
    CURSUS,
    NOTE,
    NOTE_INPUT,
    DEMISSION_DEFAILLANCE,
    JURY,
    ETUDIANTS,

} Command_type;

typedef struct
{
    Command_type command_type;
    char *list_arguments[MAX_ARGUMENTS_COUNT];
    int arguments_count;
} Separertxt;

typedef enum
{
    UE1 = 1,
    UE2,
    UE3,
    UE4,
    UE5,
    UE6,
} UE;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    // char padding[2];
    int nb_absence;
    int student_id;
    int group;
    Status stat;
    int annee;
} Etudiant;

void separertxt(char *command, Separertxt *Separertxt);
void choixcommande();

void exit();
void inscrireEtudiant();
void cursus();
void note();
void demissionDefaillance();
void jury();
void etudiants();
