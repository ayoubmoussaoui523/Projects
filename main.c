#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "bib.h"




int main()
{
    //initialisation des tailles logique

    int nb_adh=0, nb_liv = 0, nb_empr=0,f=-1,l=-1;

    //Initialisation des tableaux utiliser
    Adherant *liste_adh =NULL;
    livre *liste_liv =NULL;
    Emprunt *liste_emp =NULL;
    //Initialisation des tailles physiques.
    int tP_tAdh = 0, tP_tJe = 0, tP_tEmp = 0, choix = 0;

    DIR* dir = opendir("bin");//opendir inspire d'une autre appllication attend une chaine de caractère et revoie un pointeur vers le répertoire courant sinon au cas d'une arreur elle revoit un  pointeur null
    if (!dir)
    {
        mkdir("bin");
    }

    //Lire les fichiers qui sont dans le repertoire courant, récuperer les informations.
    //Si on peut pas acceder le fichier, on le crée.
   if (access("bin/adherants.bin", F_OK) == -1) {
        SauverAdherants(liste_adh, nb_adh);
    }

    if (access("bin/emprunts.bin", F_OK) == -1) {
        SauverEmprunts(liste_emp,nb_empr);
    }

    if (access("bin/livres.bin", F_OK) == -1) {
        Sauver_livre(liste_liv,nb_liv);
    }

    liste_adh = LireAdherants(&nb_adh);
    liste_liv = Lire_livre(&nb_liv);
    liste_emp = LireEmprunts(&nb_empr);

    //Presenter le menu
    do
    {   int choix2 = 0;
        printf("______ _   _  _____ _____           _____\n");
       printf("|  ____| \ | |/ ____|_   _|   /\    / ____|\n");
       printf("| |__  |  \| | (___   | |    /  \  | (___  \n");
       printf("|  __| | . ` |\___ \  | |   / /\ \  \___ \ \n");
       printf("| |____| |\  |____) |_| |_ / ____ \ ____) |\n");
       printf("|______|_|_\_|_____/|_____/_/_ __\_\|_____/_\n");
       printf(" ____ _____ ____  _      _____ ____ _______ _    _ ______ ____  _    _ ______ \n");
       printf("|  _ \_   _|  _ \| |    |_   _/ __ \__   __| |  | |  ____/ __ \| |  | |  ____|\n");
       printf("| |_) || | | |_) | |      | || |  | | | |  | |__| | |__ | |  | | |  | | |___\n");
       printf("|  _ < | | |  _ <| |      | || |  | | | |  |  __  |  __|| |  | | |  | |  __|\n");
       printf("| |_) || |_| |_) | |____ _| || |__| | | |  | |  | | |___| |__| | |__| | |____\n");
       printf("|____/_____|____/|______|_____\____/  |_|  |_|  |_|______\___\_\\____/|______|\n");
        printf("Realise par: MOUSSAOUI Ayoub\n");
        printf("Encadrant : MOUMANE KHADIJA");
        printf("\n\n| MENU PRINCIPAL |\n\n");
        printf("1. MENU AJOUTER\n");
        printf("2. MENU AFFICHAGE\n");
        printf("3. MENU SUPPRESSION\n");
        printf("4. MENU RECHERCHER\n");
        printf("5. QUITTER\n");
        choix =INPUT_NUM();
        system("cls");
        switch (choix) {
            case 1:
                do {


printf(",--.   ,--.,------.,--.  ,--.,--. ,--.      ,---.       ,--. ,-----. ,--. ,--.,--------.,------.,------.\n");
printf("|   `.'   ||  .---'|  ,'.|  ||  | |  |     /  O  \      |  |'  .-.  '|  | |  |'--.  .--'|  .---'|  .--. '\n");
printf("|  |'.'|  ||  `--, |  |' '  ||  | |  |    |  .-.  |,--. |  ||  | |  ||  | |  |   |  |   |  `--, |  '--'.'\n");
printf("|  |   |  ||  `---.|  | `   |'  '-'  '    |  | |  ||  '-'  /'  '-'  ''  '-'  '   |  |   |  `---.|  |\  \ \n");
printf("`--'   `--'`------'`--'  `--' `-----'     `--' `--' `-----'  `-----'  `-----'    `--'   `------'`--' '--'\n");





                    printf("1. AJOUTER UN NOUVEL ADHERENT. \n");
                    printf("2. AJOUTER UN livre.\n");
                    printf("3. AJOUTER UN EMPRUNT.\n");
                    printf("4. Modifier adherance\n");
                    printf("5. RETOURNER AU MENU PRINCIPAL.\n");

                    choix2 = INPUT_NUM();
                    switch (choix2) {
                        case 1:system("cls");
                            liste_adh = ajouter(liste_adh, &nb_adh, &tP_tAdh); //Chargue le tableau 'tAdherants' avec un Adherant.
                            SauverAdherants(liste_adh, nb_adh); //Sauvegarde le tableau retourne dans le fichier correspondant.
                            break;
                        case 2:system("cls");
                            liste_liv = Ajouter_livre(liste_liv, &nb_liv, &tP_tJe);
                            Sauver_livre(liste_liv, nb_liv);
                            break;
                        case 3:system("cls");
                            if (nb_liv > 0 && nb_adh > 0) {
                                liste_emp=ajouterEmprunts(liste_adh, nb_adh, liste_liv, nb_liv, liste_emp,
                                                            &nb_empr,&tP_tEmp);printf("%d",nb_empr);
                                SauverEmprunts(liste_emp,nb_empr);Sauver_livre(liste_liv, nb_liv);SauverAdherants(liste_adh, nb_adh);
                            } else {
                                printf("Impossible d'emprunter. Aucun livre ou adherant trouve.\n");
                            }
                            break;
                        case 4: system("cls");
                        liste_adh=Modifier_adh(liste_adh,&nb_adh,&tP_tAdh);
                        SauverAdherants(liste_adh, nb_adh);
                        break;
                        case 5:system("cls");
                        break;

                        default:system("cls");
                            printf("\nFaites une choix parmi les options presentees.\n\n\n");
                            break;

                    }
                } while (choix2 !=5);break;

            case 2:
                do {
printf(",--.   ,--.,------.,--.  ,--.,--. ,--.      ,---.  ,------.,------.,--. ,-----.,--.  ,--.,------.,------.\n");
printf("|   `.'   ||  .---'|  ,'.|  ||  | |  |     /  O  \ |  .---'|  .---'|  |'  .--./|  '--'  ||  .---'|  .--. '\n");
printf("|  |'.'|  ||  `--, |  |' '  ||  | |  |    |  .-.  ||  `--, |  `--, |  ||  |    |  .--.  ||  `--, |  '--'.''\n");
printf("|  |   |  ||  `---.|  | `   |'  '-'  '    |  | |  ||  |`   |  |`   |  |'  '--'\|  |  |  ||  `---.|  |\  \ \n");
printf("`--'   `--'`------'`--'  `--' `-----'     `--' `--'`--'    `--'    `--' `-----'`--'  `--'`------'`--' '--'\n");




                    printf("1. AFFICHER LA LISTE DES ADHERENTS.\n");
                    printf("2. AFFICHER LA LISTE DES LIVRES.  \n");
                    printf("3. AFFICHER LES EMPRUNTS EN COURS. \n");
                    printf("4. RETOURNER AU MENU PRINCIPAL. \n");
                    choix2 = INPUT_NUM();
                    system("cls");
                    switch (choix2) {
                        case 1:system("cls");

                            AfficherAdherants(liste_adh, nb_adh);
                            break;
                        case 2:system("cls");


                            Afficher_livre(liste_liv, nb_liv); //On affiche les jeux.
                            break;
                        case 3:system("cls");

                            AfficherEmprunts(liste_emp, nb_empr);
                            break;

                        case 4:system("cls");

                            break;
                        default:system("cls");

                            printf("\nFaites une choix parmi les options presentees.\n\n\n");
                            break;
                    }
                } while (choix2 != 4);
                break;

            case 3:
                do {


printf(",--.   ,--.,------.,--.  ,--.,--. ,--.     ,---.  ,--. ,--.,------. ,------. ,------. ,--.,--.   ,--.,------.,------.\n");
printf("|   `.'   ||  .---'|  ,'.|  ||  | |  |    '   .-' |  | |  ||  .--. '|  .--. '|  .--. '|  ||   `.'   ||  .---'|  .--. '\n");
printf("|  |'.'|  ||  `--, |  |' '  ||  | |  |    `.  `-. |  | |  ||  '--' ||  '--' ||  '--'.'|  ||  |'.'|  ||  `--, |  '--'.'\n");
printf("|  |   |  ||  `---.|  | `   |'  '-'  '    .-'    |'  '-'  '|  | --' |  | --' |  |\  \ |  ||  |   |  ||  `---.|  |\  \  \n");
printf("`--'   `--'`------'`--'  `--' `-----'     `-----'  `-----' `--'     `--'     `--' '--'`--'`--'   `--'`------'`--' '--' \n");

                    printf("1. SUPPRIMER UN ADHERENT. \n");
                    printf("2. SUPPRIMER UN LIVRE\n");
                    printf("3. RETOURNER UN EMPRUNT.\n");
                    printf("4. RETOURNER AU MENU PRINCIPAL.\n");
                    choix2 = INPUT_NUM();system("cls");
                    switch (choix2) {
                        case 1:system("cls");

                            SupprimerAdherant(liste_adh, &nb_adh);
                            SauverAdherants(liste_adh, nb_adh);
                            break;
                        case 2:system("cls");

                            Supprimer_livre(liste_liv, &nb_liv);
                            Sauver_livre(liste_liv, nb_liv);
                            break;
                        case 3:system("cls");

                            RetournerEmprunt(liste_emp, &nb_empr, liste_adh, nb_adh, liste_liv, nb_liv);
                            SauverEmprunts(liste_emp, nb_empr);Sauver_livre(liste_liv, nb_liv);SauverAdherants(liste_adh, nb_adh);
                            break;

                        case 4:system("cls");

                            break;
                        default:system("cls");

                            printf("\nFaites une choix parmi les options presentees.\n\n\n");
                            break;
                    }
                } while (choix2 != 4);
                break;
            case 4:
                do{




printf("     __          _  __  __    __ _  __    __ _  \n");
printf(" |V||_ |\|| |   |_)|_ /  |_||_ |_)/  |_||_ |_) \n");
printf(" | ||__| ||_|  | \|__ \__| ||__| \\__| ||__| \ \n");





                    printf("1. RECHERCHE UN ADHERENT.\n");
                    printf("2. RECHERCHE UN LIVRE\n");
                    printf("3. RETOURNER AU MENU PRINCIPAL.\n");
                   choix2 = INPUT_NUM();system("cls");
                    switch (choix2) {
                        case 1:
                        f=RechercherAdherant_par_nom(liste_adh,nb_adh);
                        if(f==-1){printf("n'existe pas" );break;}else{printf("\n\n ADHERANT ID: %d\n\tnom : %s\n\tprenom : %s\n\tnombre d'emprunt %d : \n\tadresse email %s \n\tadresse personelle %s \n\n",
           liste_adh[f].num_adh,liste_adh[f].nom_adh, liste_adh[f].prenom_adh, liste_adh[f].nb_emp,liste_adh[f].email,liste_adh[f].adresse);break;}
                        case 2:system("cls");
                        l=Rechercher_livre_par_categorie(liste_liv,nb_liv);
                        if(l==-1){printf("n'existe pas" );}else{printf("ce livre existe");}

                        case 3:break;
                        default:printf("\nFaites une choix parmi les options presentees.\n\n\n");
                        break;}
                        }while (choix2 != 3);break;



            case 5:

                printf("\n\tMerci d'avoir utilise cette application! \n");
                break;
            default:

                printf("\nFaites une choix parmi les options presentees.\n\n\n");
                break;
        }
    } while (choix != 5);
    sauvegarder(liste_adh, nb_adh,liste_liv, nb_liv, liste_emp, nb_empr);
    return 0;
}
