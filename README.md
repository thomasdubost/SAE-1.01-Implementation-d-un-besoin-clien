# SAE S1.01 - Implémentation d’un besoin client
## Projet : Gestion de la scolarité des étudiants en BUT Informatique
  
---  

## 🎯 Objectif
Développer en **C** un interpréteur de commandes permettant de gérer la scolarité d’étudiants de BUT Informatique.
  
---  

## 🧩 Étapes du projet

### 1. Compréhension des règles de gestion
- Chaque année = 2 semestres → 6 UE par semestre.
- Notes sur 20, validées si ≥ 10.
- Moyenne des 2 semestres d’une année = **RCUE**.
- RCUE ≥ 10 valide automatiquement les UE concernées.
- Passage :
    - S1 → S2 : automatique.
    - S2 → S3 : si ≥ 4 RCUE ≥ 10 et aucune note < 8.
    - Passage en 3e année : toutes les UE de 1re année validées.
    - Diplôme : toutes les UE validées sur 3 ans.
- Statuts possibles : `en cours`, `démission`, `défaillance`, `ajourné`, `diplômé`.

---  

### 2. Commandes à implémenter

| Commande | Description | Exemple |  
|-----------|--------------|----------|  
| **EXIT** | Quitte le programme | `EXIT` |  
| **INSCRIRE prénom nom** | Ajoute un étudiant et affiche son ID | `INSCRIRE Marcel Pagnol` |  
| **CURSUS id** | Affiche le parcours et les notes de l’étudiant | `CURSUS 1` |  
| **NOTE id ue note** | Enregistre une note (UE 1 à 6, 0 ≤ note ≤ 20) | `NOTE 1 3 12.5` |  
| **DEMISSION id** | Marque un étudiant comme démissionnaire | `DEMISSION 1` |  
| **DEFAILLANCE id** | Marque un étudiant comme défaillant | `DEFAILLANCE 1` |  
| **JURY n°semestre** | Lance le jury de fin de semestre | `JURY 2` |  
| **ETUDIANTS** | Liste les étudiants connus | `ETUDIANTS` |  
| **BILAN n°année** | Affiche le bilan de l’année | `BILAN 1` |  
  
---  

### 3. Progression par sprints

| Sprint | Commandes à coder |  
|---------|------------------|  
| **SP1** | EXIT, INSCRIRE, NOTE, CURSUS, ETUDIANTS |  
| **SP2** | SP1 + DEMISSION, DEFAILLANCE, JURY (semestre impair) |  
| **SP3** | SP2 + JURY (semestre pair) |  
| **SP4** | SP3 + BILAN |  

Chaque sprint doit être validé à l’aide d’un **jeu de tests** (`in.txt` / `out.txt`).
  
---  

### 4. Détails techniques
- Max 100 étudiants.
- Noms ≤ 30 caractères.
- Notes de type **float** (0 à 20).
- Affichage avec **1 décimale tronquée** :
  ```c  
  printf("%.1f", floorf(note * 10) / 10);```
- Éviter de stocker des valeurs calculables (RCUE, moyennes).

---  

### 5. Rapport à rendre
Archive `.zip` contenant :
- Le **rapport PDF** et le **fichier C** du sprint validé.

#### Le rapport doit contenir :
1. Page de garde (noms, groupe, objet du rapport).
2. Présentation du projet (1 page max).
3. Méthode de vérification du programme.
4. Bilan (difficultés, réussites, améliorations).
5. Annexes :
    - Code source commenté.
    - Exemple d’exécution du sprint validé.

---  

### 6. Dates importantes
- **Recette (test final)** : semaine du **20 octobre 2025**
- **Remise finale sur Moodle** : **vendredi 24 octobre 2025**

---  
