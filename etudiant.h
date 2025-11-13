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
