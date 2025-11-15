# Minishell — Shell UNIX minimal en C (École 42)

**Minishell** est un shell UNIX minimal codé en C dans le cadre du cursus de l'École 42.  
L’objectif est de reproduire les fonctionnalités essentielles d’un shell réel :  
exécution de commandes, pipes, redirections, parsing avancé, gestion des signaux et des variables d’environnement.

Ce projet demande une compréhension fine du fonctionnement interne d’UNIX :  
processus, fork/exec, file descriptors, signaux, gestion mémoire, parsing et architecture modulaire.

---

## 🎯 Objectifs & compétences développées

### 🔵 Programmation système en C
- Manipulation avancée des **processus** (`fork`, `execve`, `waitpid`)
- Gestion stricte des **descripteurs de fichiers** (dup2, pipe)
- Utilisation des **signaux UNIX** (SIGINT, SIGQUIT…)
- Implémentation de **pipes multiples** et redirections complexes

### 🔵 Parsing & architecture logicielle
- Lexer + parser pour découper l’entrée utilisateur  
- Gestion des quotes, expansions, substitutions  
- Construction d’une structure de commandes  
- Architecture modulaire et sécurisée

### 🔵 Shell Features
Ton minishell implémente :

- ✔ **Exécution de commandes externes**  
- ✔ **Pipes multiples** (`cmd1 | cmd2 | cmd3`)  
- ✔ **Redirections**  
  - `>`  
  - `>>`  
  - `<`  
- ✔ **Heredoc** (`<<`)  
- ✔ **Variables d’environnement** (`$HOME`, `$PATH`, etc.)  
- ✔ **Signaux gérés**  
  - Ctrl-C (SIGINT)  
  - Ctrl-D  
  - Ctrl-\ (SIGQUIT)  
- ✔ **Builtins principaux**  
  - `echo`  
  - `cd`  
  - `pwd`  
  - `export`  
  - `unset`  
  - `env`  
  - `exit`

### 🔵 Gestion mémoire & robustesse
- Nettoyage précis de toutes les allocations  
- Absence de leaks (vérifié via valgrind)  
- Sécurité contre les doubles free & invalid reads  

---

## 🧱 Fonctionnement général

Le shell suit un pipeline classique :

1. Lecture de l’entrée utilisateur (readline)
2. **Tokenisation** (lexer)
3. **Parsing** (construction des commandes)
4. Setup des pipes/redirections
5. **fork()** → exécution des commandes
6. Gestion des signaux & statut de sortie
7. Nettoyage mémoire
8. Retour à l’invite de commande

---

## 🚀 Lancer le projet

### 1. Cloner le dépôt
```bash
git clone https://github.com/SamihOuague/minishell
cd minishell
