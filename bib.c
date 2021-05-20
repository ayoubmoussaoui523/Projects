#define MAX_NUMADHERANT  100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>



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

typedef struct{//cette strucrure emprunt suplémentaire permet de faciliter la
    //gestion des emprunt au lieu d'inclure les adherants
    // emprunteurs d'un livre dans la structure livre
     char titre[25];
     int num_liv;
     int num_adh;
}Emprunt;
/*pour des raisons d'organisation les fonctions similaire ne possèdent pas toutes des commentaires
ces dernièrs ce trouve selement dans le premier exemple*/

char *generation_num_aleatoire(int length) {//grace a la fonction rand() cette fonction génére un nombre aléatoire parmi6 62
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *ID;
    size_t stringLen = 62;
    ID = malloc(sizeof(char)*(length +1));
    if (!ID) {
        return (char*)0;}
unsigned int NB = 0;
int i;
for (i = 0;i < length;i++) {
        NB = rand() % stringLen;
        ID[i] = string[NB];}
ID[length] = '\0';return ID;
}

int INPUT_NUM(void){
    int x; char term;
    int nb = scanf("%d%c", &x, &term);
    while(nb != 2 || term != '\n'){
        printf("\nSaisie incorrecte. Ressayez:\n");
        getchar();
        nb = scanf("%d%c", &x, &term);
    }
    return x;
}

Adherant *ajouter(Adherant liste_adh[],int *nb_adh,int *taillePhysique) {
    if(*nb_adh == 0) {/*Cette partie vérifie si au debut la taille réelle du tableau est
            la meme que sa taille logique(taillePhysique>=taille logique)pour éviter toute perte d'information*/
        *taillePhysique += 3;
        liste_adh = (Adherant *) malloc(*taillePhysique * sizeof(Adherant));
        if (liste_adh == NULL) {
            printf("Probleme d'allocation de memoire (malloc tAdherants)");
            exit(1);/*quitter le programme si l'allocation est incorrecte*/
        }
    }
    Adherant a, *nv_liste_adh;//cette partie est identique a la précédente ici on réalloc
    int i = *nb_adh;//Si à ce moment là la taille logique est égale à la taille physique //on augmente la capacité de stockage du tableau.
    for (*nb_adh=i; *nb_adh < (i+1); *nb_adh+=1) {
        if (*nb_adh == *taillePhysique) {
            *taillePhysique += 3;
            nv_liste_adh = (Adherant *) realloc(liste_adh, *taillePhysique * sizeof(Adherant));
            if (nv_liste_adh == NULL) {
                printf("Probleme d'allocation de memoire. (realloc tAdherants)");
                exit(1);
            }
            liste_adh =nv_liste_adh;
        }
         a.num_adh =((int)generation_num_aleatoire(4))%MAX_NUMADHERANT;//on affecte à chaque adherant un numero et on vérifie s'il est unique
   int index = RechercherAdherant(liste_adh,*nb_adh,a.num_adh);//la fonction recherche return -1 si l'element n'existe pas et sa position si il a trouver
    while (index != -1) {
        a.num_adh = ((int)generation_num_aleatoire(4))%MAX_NUMADHERANT;//on répete la meme chose tant que le num génere existe déja
        index = RechercherAdherant(liste_adh, *nb_adh, a.num_adh);
    }
    printf("Num. Adherant: %d\n", a.num_adh);//on affiche à l'adherant son numero
    printf("Entrez son nom (14 caracteres maximum): \n");
    fgets(a.nom_adh, 15, stdin);//j'ai utiliser gets et stdin car lorsque on frappe <enter> le caractère'\n' est aussi placer dans stdin(stdin est connecter au clavier
    a.nom_adh[strlen(a.nom_adh)-1]= '\0';//'\0' est utiliser ici car les fonction de manipulation des chaine de caractère nécessitent que votre chaine se termine par un caractère nul
    printf("Entrez son prenom (14 caracteres maximum): \n");
    fgets(a.prenom_adh, 15, stdin);
    a.prenom_adh[strlen(a.prenom_adh)-1]= '\0';
    printf("Entrez son email (14 caracteres maximum): \n");
    fgets(a.email, 25, stdin);
    a.email[strlen(a.email)-1]= '\0';
    printf("Entrez son adresse personelle (14 caracteres maximum): \n");
    fgets(a.adresse, 25, stdin);
    a.adresse[strlen(a.adresse)-1]= '\0';
    a.nb_emp = 0;
    liste_adh[*nb_adh] = a;
    } printf("\n-- Adherant ajouter avec succes! --\n");
    return liste_adh;
}
Adherant *Modifier_adh(Adherant liste_adh[], int *nb_adh, int *taillePhysique){
if(*nb_adh <= 0){
        printf("Aucun adherant n'a ete trouve. Impossible de modifier. \n");
        return;
    }
    int i, num_adh;
    printf("\n|Modification d'une adherance|\n");
    printf("Saisissez le numero de l'adherant a modifier: \n");
    num_adh = INPUT_NUM();
    int pos_adh = RechercherAdherant(liste_adh, *nb_adh,num_adh);

    while (pos_adh == -1) {
        printf("\nNumero d'adherant inconnu. choisir parmi cette liste :\n");
        AfficherAdherants(liste_adh, *nb_adh);
        printf("\n");
        num_adh = INPUT_NUM();
        pos_adh = RechercherAdherant(liste_adh, *nb_adh,num_adh);
    }liste_adh[pos_adh].num_adh=num_adh;

    printf("Num. Adherant: %d\n",liste_adh[pos_adh].num_adh);
    printf("Entrez son nouveau nom (14 caracteres maximum): \n");
    fgets(liste_adh[pos_adh].nom_adh, 15, stdin);//j'ai utiliser gets et stdin car lorsque on frappe <enter> le caractère'\n' est aussi placer dans stdin(stdin est connecter au clavier
    liste_adh[pos_adh].nom_adh[strlen(liste_adh[pos_adh].nom_adh)-1]= '\0';//'\0' est utiliser ici car les fonction de manipulation des chaine de caractère nécessitent que votre chaine se termine par un caractère nul
    printf("Entrez son nouveau prenom (14 caracteres maximum): \n");
    fgets(liste_adh[pos_adh].prenom_adh, 15, stdin);// stdin
    liste_adh[pos_adh].prenom_adh[strlen(liste_adh[pos_adh].prenom_adh)-1]= '\0';
    printf("Entrez son nouveau email (14 caracteres maximum): \n");
    fgets(liste_adh[pos_adh].email,25, stdin);
    liste_adh[pos_adh].email[strlen(liste_adh[pos_adh].email)-1]= '\0';
    printf("Entrez son nouvelle adresse personelle (14 caracteres maximum): \n");
    fgets(liste_adh[pos_adh].adresse, 25, stdin);
    liste_adh[pos_adh].adresse[strlen(liste_adh[pos_adh].adresse)-1]= '\0';

     printf("\n-- Adherance modifier avec succes! --\n");
    return liste_adh;
}

livre *Ajouter_livre(livre liste_liv[], int *nb_liv, int *taillePhysique) {
    if(*nb_liv == 0) {
        *taillePhysique += 3;
        liste_liv = (livre*) malloc(*taillePhysique *sizeof(livre));
        if (liste_liv == NULL) {
            printf("Probleme d'allocation de memoire (malloc tAdherants)");
            exit(1);
        }
    }
    livre lv, *nv_liste_liv;
    int i= *nb_liv,nbCateg;
    for (*nb_liv; *nb_liv < (i+1);*nb_liv += 1) {
        if (*nb_liv ==*taillePhysique) { //Si à ce moment là la taille logique est égale à la taille physique //on augmente la capacité de stockage du tableau.
            *taillePhysique += 3; //on augmente la capacité de stockage du tableau de 3.
            nv_liste_liv = (livre*)realloc(liste_liv,*taillePhysique * sizeof(livre));
            if (nv_liste_liv==NULL) {
                printf("Probleme d'allocation de memoire. (realloc tAdherants)");
                exit(1);
            }
            liste_liv=nv_liste_liv;
        }


       lv.num_liv =((int)generation_num_aleatoire(4))%MAX_NUMADHERANT;
    int pos_adh= RechercherAdherant(liste_liv,*nb_liv, lv.num_liv);
    while (pos_adh != -1) {
        lv.num_liv =((int)generation_num_aleatoire(4))%MAX_NUMADHERANT;
        pos_adh= RechercherAdherant(liste_liv,*nb_liv,lv.num_liv);
    }
    printf("Num. Livre: %d\n",lv.num_liv);
    printf("Entrez son titre (14 caracteres maximum): \n");
    fgets(lv.titre_liv,15,stdin);
    lv.titre_liv[strlen(lv.titre_liv)-1]='\0';
    printf("Entrez le nom  de l'auteur(14 caracteres maximum): \n");
    fgets(lv.aut_nom,15,stdin);
    lv.aut_nom[strlen(lv.aut_nom)-1]='\0';
    printf("Entrez le prenom  de l'auteur(14 caracteres maximum): \n");
    fgets(lv.aut_prenom,15,stdin);
    lv.aut_prenom[strlen(lv.aut_prenom)-1]='\0';
    printf("Quelle est la categorie du livre ?(Entrez le numero correspondant)"
                   "\n\t 1: literatue\n\t 2: religion"
                   "\n\t 3: science\n\t 4: loisir\n");
    scanf("%d",&nbCateg);

    while (!(nbCateg ==1 || nbCateg ==2 || nbCateg ==3 || nbCateg ==4)) {
        printf("Saisie incorrecte. (possibilites : 1, 2, 3 ou 4)\n");//l'adherant doit choisir un num et le programme affecte la categorie selon le nombre
        printf("Quelle est la categorie du livre ?(Entrez le numero correspondant)"
                        "\n\t 1: litùratue\n\t 2: religion"
                   "\n\t 3: science\n\t 4: loisir\n");
        scanf("%d",&nbCateg);
    }
    switch (nbCateg) {
        case 1:
            strcpy(lv.categorie,"literatue");
            break;
        case 2:
            strcpy(lv.categorie,"religion");
            break;
        case 3:
            strcpy(lv.categorie,"science");
            break;
        case 4:
            strcpy(lv.categorie,"loisir");
            break;
        default:
            break;}
    lv.nb_empr = 0;
    printf("\n-- livre ajouter avec succes --\n");
    liste_liv[*nb_liv] = lv;
    }
    return liste_liv;
}



Emprunt *ajouterEmprunts(Adherant liste_adh[], int nb_adh, livre liste_liv[], int nb_liv, Emprunt liste_emp[], int *nb_empr, int *taillePhysique, int nbAjouts){
    if(*nb_empr == 0) {
        *taillePhysique += 3;
        liste_emp = (Emprunt *) malloc(*taillePhysique * sizeof(Emprunt));
        if (liste_emp == NULL) {
            printf("Probleme d'allocation de memoire ");
            exit(1);
        }
    }
    Emprunt emprunt, *nv_liste_emp;
    int i= *nb_empr;
    for (; *nb_empr< (i+1); *nb_empr+=1) {
        if (*nb_empr == *taillePhysique) { //Si à ce moment là la taille logique est égale à la taille physique //on augmente la capacité de stockage du tableau.
            *taillePhysique += 3; //on augmente la capacité de stockage du tableau de 3.
            nv_liste_emp = (Emprunt *) realloc(liste_emp, *taillePhysique * sizeof(Emprunt));
            if (nv_liste_emp == NULL) {
                printf("Probleme d'allocation de memoire. ");
                exit(1);
            }
            liste_emp = nv_liste_emp;
        }
    printf("Saisissez le numero de l'Adherant qui veut emprunter : \n");
    emprunt.num_adh = INPUT_NUM();
    int posAdherant = RechercherAdherant(liste_adh, nb_adh, emprunt.num_adh);
    while (posAdherant == -1) {
        printf("Numero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(liste_adh, nb_adh);
        printf("\n");
        emprunt.num_adh = INPUT_NUM();
        posAdherant = RechercherAdherant(liste_adh, nb_adh, emprunt.num_adh);
    }

    if (liste_adh[posAdherant].nb_emp >= 3){
        system("cls");
        printf("\nL'adherant %s emprunte deja 3 livres. Il doit en retourner un avant de pouvoir re-emprunter.\n", liste_adh[posAdherant].nom_adh);
        liste_emp[*nb_empr] = emprunt;
        return liste_emp;
    }

    printf("Saisissez le titre du livre a  emprunte : \n");
    getchar();
    fgets(emprunt.titre, 25, stdin);
    emprunt.titre[strlen(emprunt.titre) - 1] = '\0';
    int pos_liv = Rechercher_livre(liste_liv, nb_liv, emprunt.titre);
    while (pos_liv == -1) {
        printf("\nCe livre n'existe pas. Voici la liste des livres existants :\n");

        Afficher_livre(liste_liv, nb_liv);
        printf("\n");
        printf("Saisissez le titre du livre a emprunter : \n");
        fgets(emprunt.titre, 25, stdin);
        emprunt.titre[strlen(emprunt.titre) - 1] = '\0';
        pos_liv = Rechercher_livre(liste_liv, nb_liv, emprunt.titre);
    }

        liste_liv[pos_liv].nb_empr++;
        liste_adh[posAdherant].nb_emp++;

            liste_emp[*nb_empr] = emprunt;

    } printf("\n-- Emprunt ajoute avec succes! --\n");
    return liste_emp;
}


Adherant *LireAdherants(int *nb_adh) {
    Adherant *liste_adh;
    FILE *fb;
    fb = fopen("bin/adherants.bin", "rb");//j'ai utiliser des fichiers binaires car il sont plus facile à manipuler que les fichiers textes
    if (fb==NULL) {
        printf("Probleme d'ouverture de fichier.\n");
        *nb_adh= -1;
        return NULL;
    }
    fread(nb_adh,sizeof(int),1,fb);
    liste_adh=(Adherant *)malloc(*nb_adh *sizeof(Adherant));
    if (liste_adh==NULL) {
        printf("Probleme d'allocation de memoire (lecture tAdherants)");
        exit(1);
    }
    fread(liste_adh,sizeof(Adherant),(size_t)*nb_adh,fb);
    fclose(fb);
    return liste_adh;
}

livre *Lire_livre(int *nb_liv) {
    livre *liste_liv;
    FILE *fb;
    fb=fopen("bin/livres.bin", "rb");
    if (fb==NULL) {
        printf("Probleme d'ouverture de fichier.\n");
        *nb_liv= -1;
        return NULL;
    }
    fread(nb_liv,sizeof(int),1,fb);
    liste_liv=(livre *)malloc(*nb_liv *sizeof(livre));
    if (liste_liv==NULL) {
        printf("Probleme d'allocation de memoire (lecture tJeux)");
        exit(1);
    }
    fread(liste_liv,sizeof(livre),(size_t)*nb_liv,fb);
    fclose(fb);
    return liste_liv;
}



Emprunt *LireEmprunts(int *nb_empr){
    FILE *fb;
    fb=fopen("bin/emprunts.bin", "rb");
    if (fb==NULL){
        printf("Probleme d'ouverture de ficiher. \n");
        *nb_empr= -1;
        return NULL;
    }
    fread(nb_empr,sizeof(int),1,fb);
    Emprunt *liste_emp;
    liste_emp=(Emprunt*)malloc(*nb_empr * sizeof(Emprunt));
    if (liste_emp==NULL){
        printf("Probleme d'allocation de memoire (lecture tEmprunts)");
        exit(1);
    }

    fread(liste_emp,sizeof(Emprunt),(size_t)*nb_empr,fb);
    return liste_emp;
}



void AfficherAdherants(Adherant liste_adh[],int nb_adh) {//cette fonction affiche toute la liste des adherants(livre-emprunt) qui existent
    int i;
    for (i = 0;i <nb_adh;i++) {
             printf("\n\n ADHERANT ID: %d\n\tnom : %s\n\tprenom : %s\n\tnombre d'emprunt %d : \n\tadresse email %s \n\tadresse personelle %s \n\n",
           liste_adh[i].num_adh,liste_adh[i].nom_adh, liste_adh[i].prenom_adh, liste_adh[i].nb_emp,liste_adh[i].email,liste_adh[i].adresse);
    }
    if(nb_adh==0){
        printf("\nAucun adherant n'a ete trouve.\n");
        return;}
}


void Afficher_livre(livre liste_liv[],int nb_liv) {
    int i;
    for (i=0; i<nb_liv;i++) {
        printf("\n\nNom : %s (%s) - Emprunts en cours: %d numero : %d nom de l'auteur:%s prenom de l'auteur:%s", liste_liv[i].titre_liv, liste_liv[i].categorie, liste_liv[i].nb_empr,liste_liv[i].num_liv,liste_liv[i].aut_nom,liste_liv[i].aut_prenom);
    }
    if(nb_liv==0){
        printf("\nAucun livre n'a ete trouve.\n");
        return;}
}


void AfficherEmprunts(Emprunt liste_emp[],int nb_empr){
    int i;
    for(i=0;i<nb_empr;i++){
        printf("\n\n titre du livre: %s \nNum de l'emprunteur: %d\n",liste_emp[i].titre,liste_emp[i].num_adh);
    }
    if(nb_empr==0){
        printf("\nAucun emprunt n'a ete trouve.\n");
        return;}
}


int RechercherAdherant(Adherant liste_adh[],int nb_adh,int num_adh) {
    int i;
    for (i=0;i<nb_adh;i++) {
        if (liste_adh[i].num_adh == num_adh)
            break;}if(i==nb_adh){return -1;}
    else {return i;}
}

int RechercherAdherant_par_nom(Adherant liste_adh[],int nb_adh) {
    char nom[15];
    printf("enter le nom\n");
    gets(nom);
    int i;
    for (i = 0;i<nb_adh;i++) {
        if (strcmp(liste_adh[i].nom_adh,nom)==0)
           {
              return i;
           }
    }return -1;

}


int RechercherEmprunt(Emprunt liste_emp[], int nb_empl, int num_adh, char titre_liv[]){
    if (strcmp(liste_emp[nb_empl].titre, titre_liv) == 0 && liste_emp[nb_empl].num_adh == num_adh) {
        return nb_empl;
    }
    if (nb_empl== -1){
        return -1;
    }

 return RechercherEmprunt(liste_emp, nb_empl - 1, num_adh, titre_liv);
}


int Rechercher_livre(livre liste_liv[],int nb_liv,char titre[25]) {

    if (strcmp(liste_liv[nb_liv].titre_liv, titre)== 0) {
       return nb_liv;
    }
    if (nb_liv== -1){
        return -1;
    }

    return Rechercher_livre(liste_liv,nb_liv-1,titre);
}


int Rechercher_livre_par_categorie(livre liste_liv[],int nb_liv) {
    int i;
     char titr[15];
     char cat[15];
    printf("enter le titre\n");
    gets(titr);
    printf("enter la categorie \n");
    gets(cat);
    for(i=0;i<nb_liv;i++){
    if (strcmp(liste_liv[i].titre_liv,titr) == 0 && strcmp(liste_liv[i].categorie,cat)==0) {
        return nb_liv;
    }}
    return -1;
}




void SupprimerAdherant(Adherant liste_adh[],int *nb_adh) {
    if(*nb_adh <= 0){//avant de commencer si il n'existe aucun adherant alors il n'existe aucun adherant à supprimer
        printf("Aucun adherant n'a ete trouve. Impossible de supprimer. \n");
        return;
    }
    int i,num_adh;//sinon on commence le processus de suppression
    printf("\n|SUPPRESSION D'UN ADHERANT|\n");
    printf("Saisissez le numero de l'adherant a supprimer: \n");
    num_adh = INPUT_NUM();
    int pos_adh = RechercherAdherant(liste_adh,*nb_adh,num_adh);

    while (pos_adh == -1) {
        printf("\nNumero d'adherant inconnu. Faites un choix parmi la liste suivante :\n");
        AfficherAdherants(liste_adh,*nb_adh);
        printf("\n");
        num_adh = INPUT_NUM();
        pos_adh = RechercherAdherant(liste_adh,*nb_adh,num_adh);
    }printf("%d",liste_adh[pos_adh].nb_emp);
    if(liste_adh[pos_adh].nb_emp > 0){
        printf("\nImpossible de supprimmer un adherant avec des emprunts en cours. Veuillez retourner premierement ses emprunts.\n");
        return;
    }

    for (i=pos_adh;i< *nb_adh-1;i++) {
        liste_adh[i]=liste_adh[i+1];
    }
    *nb_adh =*nb_adh-1;
    printf("\nLa suppression a ete realisee avec succes.\n");
}



void Supprimer_livre(livre liste_liv[], int *nb_liv){
    if(*nb_liv <= 0){
        printf("Aucun livre n'a ete trouve. Impossible de supprimer. \n");
        return;
    }
    int i;
    char nom[20];
    printf("Saisissez le nom du livre a supprimer : \n");
    fgets(nom, 25, stdin);
    nom[strlen(nom) - 1]='\0';
    int pos_liv = Rechercher_livre(liste_liv,*nb_liv,nom);
    while (pos_liv== -1) {
        printf("\nCe livre n'existe pas. Voici la liste des livres existants :\n");

        Afficher_livre(liste_liv,*nb_liv);
        printf("\n");
        printf("Saisissez le nom du livre a supprimer : \n");
        fgets(nom,25,stdin);
        nom[strlen(nom) - 1] ='\0';
        pos_liv = Rechercher_livre(liste_liv, *nb_liv, nom);
    }

    for (i=pos_liv;i < *nb_liv - 1;i++){
        liste_liv[i]=liste_liv[i+1];
    }
    *nb_liv = *nb_liv -1;
    printf("-- La suppression a ete realisee avec succes --\n");
    return;
}





void RetournerEmprunt(Emprunt liste_emp[],int *nb_empr,Adherant liste_adh[],int nb_adh,livre liste_liv[],int nb_liv) {
    if(*nb_empr <= 0 || nb_adh <= 0){
        printf("Aucun emprunt ou adherant n'a ete trouve. Impossible de supprimer. \n");
        return;
    }
    Emprunt emprunt;
    int i;
    printf("\n| RETOURNER UN EMPRUNT |\n");
    printf("Saisissez le numero de l'Adherant qui veux retourner un emprunt: \n");
    emprunt.num_adh=INPUT_NUM();
    int pos_adh=RechercherAdherant(liste_adh,nb_adh,emprunt.num_adh);
    while (pos_adh== -1) {
        printf("Numero d'adherant inconnu. Vos choix sont parmis la liste suivante :\n");
        AfficherAdherants(liste_adh,nb_adh);
        printf("\n");
        emprunt.num_adh=INPUT_NUM();
        pos_adh=RechercherAdherant(liste_adh, nb_adh, emprunt.num_adh);
    }
    if (liste_adh[pos_adh].nb_emp ==0) {
        printf("Cet adherant n'a aucun emprunt en cours\n");
        return;
    }

    printf("Voici les livres que cet adherant a emprunte(s) :\n");

    for (i=0;i<*nb_empr;i++) {
        if (liste_emp[i].num_adh==emprunt.num_adh) {
            printf("\n %s",liste_emp[i].titre);
        }
    }

    printf("\n\nSaissisez le nom du livre : \n");
    fgets(emprunt.titre,25,stdin);
    emprunt.titre[strlen(emprunt.titre) - 1] ='\0';

    int pos_emp=RechercherEmprunt(liste_emp,*nb_empr, emprunt.num_adh,emprunt.titre);

    if (pos_emp== -1) {
        printf("\nL'emprunt saisi ne figure pas parmi les emprunts actuels. \n");
        return;
    }


    int pos_liv=Rechercher_livre(liste_liv,nb_liv,emprunt.titre);
    liste_liv[pos_liv].nb_empr--;
    liste_adh[pos_adh].nb_emp--;
    for (i = pos_emp; i < *nb_empr - 1; i++) {
        liste_emp[i] = liste_emp[i + 1];
    }
    *nb_empr = *nb_empr - 1;
    printf("\n-- Emprunt rendu avec succes --- \n");
}







void SauverAdherants(Adherant liste_adh[], int nb_adh) {

    FILE *fb;
    fb=fopen("bin/adherants.bin", "wb");
    if(fb==NULL){
        printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
        exit(1);
    }
    fwrite(&nb_adh,sizeof(int),1,fb);
    fwrite(liste_adh,sizeof(Adherant),(size_t) nb_adh,fb);
    fclose(fb);
}

void Sauver_livre(livre liste_liv[],int nb_liv) {
    FILE *fb;
    fb=fopen("bin/livres.bin", "wb");
    if (fb==NULL) {
        printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
        exit(1);
    }
    fwrite(&nb_liv,sizeof(int),1,fb);
    fwrite(liste_liv,sizeof(livre),(size_t) nb_liv,fb);
    fclose(fb);
}

void SauverEmprunts(Emprunt liste_emp[], int nb_empr) {

    FILE *fb;
    fb=fopen("bin/emprunts.bin", "wb");
    if (fb==NULL) {
        printf("Probleme de droits d'ecriture dans le repertoire courant.\n");
        exit(1);
    }
    fwrite(&nb_empr,sizeof(int),1,fb);
    fwrite(liste_emp,sizeof(Emprunt),(size_t) nb_empr,fb);
    fclose(fb);
}
void sauvegarder(Adherant liste_adh[],int nb_adh,livre liste_liv[],int nb_liv,Emprunt liste_emp[],int nb_empr){
 SauverEmprunts(liste_emp,nb_empr);
 Sauver_livre(liste_liv,nb_liv);
 SauverAdherants(liste_adh,nb_adh);
}


