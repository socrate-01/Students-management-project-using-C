#include<stdio.h>
#include <string.h>
void ajout_etudiant(e) 
{
   FILE* fichier = fopen("etudiants.smf", "a");
   e.nom = str_replace(e.nom, ' ', ':');
   e.prenom = str_replace(e.prenom, ' ', ':');
   fprintf(fichier, "%d %d %s %s %f\n", e.id, e.age, e.nom, e.prenom, e.moyenne);
   fclose(fichier);
}

int nbreEtudiant() {

   FILE* fichier;

   int i = 0;

   if ((fichier = fopen("etudiants.smf", "r")) != NULL) {

       etudiant e;

       e.nom = (char*) malloc(0);

       e.prenom = (char*) malloc(0);

       while (fscanf(fichier, "%d %d %s %s %f\n", &(e.id), &(e.age), e.nom, e.prenom, &(e.moyenne)) == 5)

           i++;

       fclose(fichier);

       free(e.nom);

       free(e.prenom);

   }

   return i;

}

etudiant lecture_etudiant(int position) {

   etudiant e;

   int i;

   FILE* fichier = fopen("etudiants.smf", "r");

   e.nom = (char*) malloc(0);

   e.prenom = (char*) malloc(0);

   for (i = 1; i <= position; i++) {

       fscanf(fichier, "%d %d %s %s %f\n", &(e.id), &(e.age), e.nom, e.prenom, &(e.moyenne));

   }

   e.nom = str_replace(e.nom, ':', ' ');

   e.prenom = str_replace(e.prenom, ':', ' ');

   fclose(fichier);

   return e;

}

void chargement_etudiant() {


   int i = 0;

   tailleEtudiant = nbreEtudiant();

   tEtudiant = (etudiant*) malloc(tailleEtudiant * sizeof (etudiant));

   for (i = 0; i < tailleEtudiant; i++)

       tEtudiant[i] = lecture_etudiant(i + 1);

}

void enregistrement_etudiant() {

   int i;

   remove("etudiants.smf");

   for (i = 0; i < tailleEtudiant; i++)

       ajout_etudiant(tEtudiant[i]);

}

void tAjoutEtudiant(etudiant e) {

   if (tailleEtudiant == 0)

       e.id = 1;

   else

       e.id = tEtudiant[tailleEtudiant - 1].id + 1;

   e.moyenne = -1;

   tEtudiant = (etudiant*) realloc(tEtudiant, (tailleEtudiant + 1) * sizeof (etudiant));

   tailleEtudiant++;

   tEtudiant[tailleEtudiant - 1] = e;

}

void suppression_etudiant(int id) {

   int i, j = 0;

   etudiant* tab = (etudiant*) malloc((tailleEtudiant - 1) * sizeof (etudiant));

   for (i = 0; i < tailleEtudiant; i++) {

       if (tEtudiant[i].id != id) {

           tab[j] = tEtudiant[i];

           j++;

       }

   }

   if (j != tailleEtudiant) {

       tailleEtudiant--;

       tEtudiant = tab;

   }

   free(tab);

/*

   i = 0;

   while (i < tailleNote) {

       if (tNote[i].id_etudiant == id) {

           suppression_note(tNote[i].id);

       } else

           i++;

   }

*/

}

void listeEtudiant() {

   etudiant e;

   int i;


   for (i = 0; i < tailleEtudiant; i++) {

       e = tEtudiant[i];

       printf("%d %d %s %s\n", e.id, e.age, e.nom, e.prenom);

   }

}

etudiant* recherche_etudiant(char* nom, char* prenom) {

   int i, j = 0;

   char*nom1 = malloc(0), *prenom1 = malloc(0);

   etudiant* tab = (etudiant*) malloc(sizeof (etudiant));

   for (i = 0; i < tailleEtudiant; i++) {

       prenom1 = tEtudiant[i].prenom;

       nom1 = tEtudiant[i].nom;

       if (strcmp(prenom1, prenom) == 0 || strcmp(nom1, nom) == 0) {

           tab[j] = tEtudiant[i];

           j++;

           tab = realloc(tab, sizeof (etudiant) + 1);

       }

       i++;

   }

   return tab;

}

etudiant recupererEtudiant(int id) {

   int i;

   etudiant e;

   e.id = -1;

   for (i = 0; i < tailleEtudiant; i++) {

       if (tEtudiant[i].id == id)

           return tEtudiant[i];

   }

   return e;

}

void modification_etudiant(etudiant e) {

   int i;

   for (i = 0; i < tailleEtudiant; i++) {

       if (tEtudiant[i].id == e.id) {

           tEtudiant[i] = e;

           break;

       }

   }

}

void classement() {

   int i, j;

   etudiant e;

   for (i = 0; i < tailleEtudiant - 1; i++)

       for (j = i + 1; j < tailleEtudiant; j++) {

           if (tEtudiant[i].moyenne < tEtudiant[j].moyenne) {

              e = tEtudiant[i];


               tEtudiant[i] = tEtudiant[j];

               tEtudiant[j] = e;

           }

       }

}

void trier() {

   int i, j;

   etudiant e;

   for (i = 0; i < tailleEtudiant - 1; i++)

       for (j = i + 1; j < tailleEtudiant; j++) {

           if (tEtudiant[i].id > tEtudiant[j].id) {

               e = tEtudiant[i];

               tEtudiant[i] = tEtudiant[j];

               tEtudiant[j] = e;

           }

       }

}

int rang(int id) {

   int i;

   classement();

   for (i = 0; i < tailleEtudiant; i++)

       if (tEtudiant[i].id == id)

           return i + 1;

}

float moyenneSurMatiere(etudiant e, int m) {

   int nbreNote = 0, i;

   float somPoint = 0;

   for (i = 0; i < tailleNote; i++)

       if ((tNote[i].id_etudiant == e.id) && (tNote[i].id_matiere == m)) {

           nbreNote++;

           somPoint += tNote[i].note;

       }

   if (nbreNote == 0)

       return -1;

   else

       return somPoint / nbreNote;

}