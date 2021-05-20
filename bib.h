#ifndef BIB_H_INCLUDED
#define BIB_H_INCLUDED

#ifndef FCT_H_INCLUDED
#define FCT_H_INCLUDED
#define MAX_NUMADHERANT  100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
     int num_adh;
     char nom_adh[15];
     char prenom_adh[15];
     char email[25];
     char adresse[25];
     int nb_emp;
 }Adherant;

 typedef struct{
     int num_liv;
     char titre_liv[15];
     char categorie[20];
     char aut_nom[15];
     char aut_prenom[15];
     int nb_empr;
 }livre;

typedef struct{
     char titre[15];
     int num_liv;
     int num_adh;
}Emprunt;
char *CreerIdentifiant(int length);
int INPUT_NUM(void);
Adherant *ajouter(Adherant liste_adh[], int *nb_adh, int *taillePhysique);
livre *Ajouter_livre(livre liste_liv[], int *nb_liv, int *taillePhysique);
Adherant *Modifier_adh(Adherant liste_adh[], int *nb_adh, int *taillePhysique);

Emprunt *ajouterEmprunts(Adherant liste_adh[], int nb_adh, livre liste_liv[], int nb_liv, Emprunt liste_emp[], int *nb_empr, int *taillePhysique);
Adherant *LireAdherants(int *nb_adh);
livre *Lire_livre(int *nb_liv);
Emprunt *LireEmprunts(int *nb_empr);
void AfficherAdherants(Adherant liste_adh[], int nb_adh);
void Afficher_livre(livre liste_liv[], int nb_liv);
void AfficherEmprunts(Emprunt liste_emp[], int nb_emp);
int RechercherAdherant(Adherant liste_adh[], int nb_adh, int num_adh) ;
int RechercherAdherant_par_nom(Adherant liste_adh[], int nb_adh);
int RechercherEmprunt(Emprunt liste_emp[], int nb_empr, int num_adh, char titre_liv[]);
int Rechercher_livre(livre liste_liv[], int nb_liv, char titre[25]);
int Rechercher_livre_par_categorie(livre liste_liv[], int nb_liv);
void SupprimerAdherant(Adherant liste_adh[], int *nb_adh);
void Supprimer_livre(livre liste_liv[], int *nb_liv);
void Supprimer_livre(livre liste_liv[], int *nb_liv);
void RetournerEmprunt(Emprunt liste_emp[], int *nb_empr, Adherant liste_adh[], int nb_adh, livre liste_liv[], int nb_liv);

void SauverAdherants(Adherant liste_adh[], int nb_adh);
void Sauver_livre(livre liste_liv[], int nb_liv);
void SauverEmprunts(Emprunt liste_emp[], int nb_empr);
void sauvegarder(Adherant liste_adh[],int nb_adh,livre liste_liv[],int nb_liv,Emprunt liste_emp[],int nb_empr);



#endif // FCT_H_INCLUDED


#endif // BIB_H_INCLUDED
