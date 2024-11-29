#include "bib.h"
#include <time.h>


    int Duree_Sejour(DATE d) {
        int jours = 0;
        int j1=0;
        int j2=0;
        DATE date_actuelle;
        int Mjours[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


        time_t t = time(NULL);
        struct tm *tm_now = localtime(&t);

        date_actuelle.jour = tm_now->tm_mday;
        date_actuelle.mois = tm_now->tm_mon + 1;
        date_actuelle.annee = tm_now->tm_year + 1900;

        if (d.annee < date_actuelle.annee) {
            j1 = (date_actuelle.annee - d.annee) * 365;

            for (int i = 0; i < d.mois - 1; i++) {
                j1 -= Mjours[i];
            }

            j1 =j1 - d.jour +1;



            for (int i = 0; i < date_actuelle.mois ; i++) {
                j2 += Mjours[i];
            }

            j2= j2-(Mjours[date_actuelle.mois-1] - date_actuelle.jour);

        jours =j1+j2;


        }
        else if (d.annee == date_actuelle.annee) {

            if (d.mois < date_actuelle.mois) {
                for (int i = d.mois - 1; i < date_actuelle.mois ; i++) {
                    jours += Mjours[i];
                }
                jours =jours - date_actuelle.jour - d.jour;
            }
            else if (d.mois == date_actuelle.mois) {
                jours = date_actuelle.jour - d.jour;
            }

        }
        return jours;
    }

    void Remplissage(CENTRE *C, float cout) {
        int i, j, k;

        printf("Donner libelle du centre : \n");
        scanf("%s", C->libelle);

        printf("Donner le nombre de chambres : \n");
        scanf("%d", &C->nb_chambre);

        printf("Donner le nombre de services : \n");
        scanf("%d", &C->nb_service);

        C->budget_totale = 0.0;

        C->services = (SERVICE*)malloc(C->nb_service * sizeof(SERVICE));
        if (!C->services) exit(-1);

        for (i = 0; i < C->nb_service; i++) {
            (C->services + i)->code = i + 1;

            printf("Donner le libelle du service %d :\n ", i + 1);
            scanf("%s", (C->services + i)->libelle);

            printf("Donner le budget pour le service %d : ", i + 1);
            scanf("%f", &(C->services + i)->budget);

            C->budget_totale += (C->services + i)->budget;

            printf("Donner le nombre maximum de personnes pouvant profiter du service %d : ", i + 1);
            scanf("%d", &(C->services + i)->nb_max);

            printf("Donner le nombre de personnes dans le service %d : ", i + 1);
            scanf("%d", &(C->services + i)->nb_personnes);
            while ((C->services + i)->nb_personnes > (C->services + i)->nb_max) {
                printf("Erreur: Le nombre de personnes ne peut pas depasser le maximum (%d). Reessayez : ", (C->services + i)->nb_max);
                scanf("%d", &(C->services + i)->nb_personnes);
            }

            (C->services + i)->pourcentage_personne = ((float)(C->services + i)->nb_personnes / (C->services + i)->nb_max) * 100;

            (C->services + i)->personnes = (PERSONNE*)malloc((C->services + i)->nb_personnes * sizeof(PERSONNE));
            if (!(C->services + i)->personnes) exit(-2);

            for (j = 0; j < (C->services + i)->nb_personnes; j++) {
                ((C->services + i)->personnes + j)->code = j + 1;

                printf("Donner le nom de la personne %d dans le service %d : ", j + 1, i + 1);
                scanf("%s", ((C->services + i)->personnes + j)->nom);

                printf("Donner le prenom de la personne %d dans le service %d : ", j + 1, i + 1);
                scanf("%s", ((C->services + i)->personnes + j)->prenom);

                printf("Donner la difficulte de la personne %d dans le service %d : ", j + 1, i + 1);
                scanf("%s", ((C->services + i)->personnes + j)->difficulte);

                printf("Donner la date d'inscription (jour mois annee) de la personne %d dans le service %d : ", j + 1, i + 1);
                scanf("%d %d %d",
                      &((C->services + i)->personnes + j)->inscription.jour,
                      &((C->services + i)->personnes + j)->inscription.mois,
                      &((C->services + i)->personnes + j)->inscription.annee);

                int c=Duree_Sejour(((C->services + i)->personnes + j)->inscription);
                ((C->services + i)->personnes + j)->duree_sejour=c;

            }

            printf("Donner le nombre d'employes dans ce service : ");
            scanf("%d", &(C->services + i)->nb_employees);

            (C->services + i)->employees = (EMPLOYEE*)malloc((C->services + i)->nb_employees * sizeof(EMPLOYEE));
            if (!(C->services + i)->employees) exit(-3);

            for (k = 0; k < (C->services + i)->nb_employees; k++) {
                ((C->services + i)->employees + k)->code = k + 1;

                printf("Donner le nom de l'employe %d dans le service %d : ", k + 1, i + 1);
                scanf("%s", ((C->services + i)->employees + k)->nom);

                printf("Donner le prenom de l'employe %d dans le service %d : ", k + 1, i + 1);
                scanf("%s", ((C->services + i)->employees + k)->prenom);

                printf("Donner le nombre d'heures travailleees pour l'employe %d dans le service %d : ", k + 1, i + 1);
                scanf("%d", &((C->services + i)->employees + k)->ht);

                printf("\nSaisir la date de debut de travail (jour mois annee) pour l'employe %d dans le service %d : ", k + 1, i + 1);
                scanf("%d %d %d",
                      &((C->services + i)->employees + k)->db.jour,
                      &((C->services + i)->employees + k)->db.mois,
                      &((C->services + i)->employees + k)->db.annee);

                ((C->services + i)->employees + k)->salaire = ((C->services + i)->employees + k)->ht * cout;
            }
        }
    }

    void Affichage(CENTRE C){
        int i, j ;
        printf("Centre: %s\n", C.libelle);
        printf("Nombre de services: %d\n", C.nb_service);
        printf("Nombre de chambres: %d\n", C.nb_chambre);
        printf("Budget total: %.2f\n", C.budget_totale);

        printf("===================================\n");

        for (int i = 0; i < C.nb_service; i++) {

            printf("Service %d: %s\n", (C.services + i)->code, (C.services + i)->libelle);
            printf("Nombre d'employes: %d\n", (C.services + i)->nb_employees);
            printf("Budget: %.2f\n", (C.services + i)->budget);
            printf("Nombre de personnes: %d\n", (C.services + i)->nb_personnes);
            printf("Nombre maximum de personnes: %d\n", (C.services + i)->nb_max);
            printf("Pourcentage de personnes dans le service: %.2f%%\n", (C.services + i)->pourcentage_personne);

            printf("Employes:\n");
            for (int j = 0; j < (C.services + i)->nb_employees; j++) {

                printf("  Code: %d, Nom: %s %s, Heure de travail: %d, Salaire: %.2f, Date de debut: %d/%d/%d\n",
                    ((C.services + i)->employees + j)->code, ((C.services + i)->employees + j)->prenom, ((C.services + i)->employees + j)->nom, ((C.services + i)->employees + j)->ht, ((C.services + i)->employees + j)->salaire,
                    ((C.services + i)->employees + j)->db.jour, ((C.services + i)->employees + j)->db.mois, ((C.services + i)->employees + j)->db.annee);
            }

            printf("Personnes:\n");
            for (j = 0; j < (C.services + i)->nb_personnes; j++) {

        printf("  Code: %d, Nom: %s %s, Difficulte: %s, Date d'inscription: %d/%d/%d, Duree du sejour: %d\n",
    ((C.services + i)->personnes + j)->code,
    ((C.services + i)->personnes + j)->nom,
    ((C.services + i)->personnes + j)->prenom,
    ((C.services + i)->personnes + j)->difficulte,
    ((C.services + i)->personnes + j)->inscription.jour,
    ((C.services + i)->personnes + j)->inscription.mois,
    ((C.services + i)->personnes + j)->inscription.annee,
    ((C.services + i)->personnes + j)->duree_sejour);

            }

            printf("-----------------------------------\n");
        }
    }



    void Resultat(CENTRE C , RESULTAT **R){
    int i,k;

    R = (RESULTAT**)malloc(C.nb_service * sizeof(RESULTAT*));
    if (!R) exit(-4);

    for (i = 0; i < C.nb_service; i++) {
        *(R + i) = (RESULTAT*)malloc(sizeof(RESULTAT));
        if (!*(R + i)) exit(-5);

        int maxHt =  ((C.services + i)->employees + 0)->ht;
        int maxCode =  ((C.services + i)->employees + 0)->code;

        for (k = 1; k < (C.services + i)->nb_employees; k++) {
            if ( ((C.services + i)->employees + k)->ht > maxHt) {
                maxHt = ((C.services + i)->employees + k)->ht;
                maxCode =  ((C.services + i)->employees + k)->code;
            }
        }

        (*(R + i))->code = maxCode;
        (*(R + i))->ht = maxHt;
    }

    printf("Affichage du resultat du traitement :\n");
    for (i = 0; i < C.nb_service; i++) {
        printf("Service %d: Code employe avec max heures de travail: %d, Heures: %d\n", i + 1, (*(R + i))->code, (*(R + i))->ht);
    }}




    void EmployeeMeilleurRendementCentre(CENTRE C) {
    EMPLOYEE *max = (C.services)->employees;

    for (int i = 0; i < C.nb_service; i++) {
        for (int j = 0; j < (C.services + i)->nb_employees; j++) {
            if (((C.services + i)->employees + j)->ht > max->ht) {
                max = (C.services + i)->employees + j;
            }
        }
    }

    printf("Employe avec meilleur rendement dans le centre est %s %s\n", max->nom, max->prenom);
    }


    void EmployeeMeilleurRendementService(SERVICE *S) {
    EMPLOYEE *max = S->employees;

    for (int i = 0; i < S->nb_employees; i++) {
            if ((S->employees + i)->ht > max->ht)
                max = S->employees + i;
    }
    printf("Employe avec meilleur rendement dans le service %s est %s %s\n", S->libelle ,max->nom, max->prenom);
    }





    void ServicePlusDemandee(CENTRE C) {
    SERVICE *max = C.services;

    for (int i = 1; i < C.nb_service; i++) {
        if ((C.services + i)->nb_personnes > max->nb_personnes) {
            max = C.services + i;
        }
    }
    printf("Le service le plus demande est : %s avec le pourcentage de %.2f%%\n", max->libelle , max->pourcentage_personne);
    }


    void ServicePlusCouteux(CENTRE C)
    {
    SERVICE* max=C.services;
    for(int i=0;i<C.nb_service;i++)
    {
        if (((C.services+i)->budget)>max->budget)
           max=C.services+i ;
    }
    printf("Le service le plus couteux est %s",max->libelle);
    }

    void PersonnePlusAncienneService(SERVICE *S) {
    PERSONNE *max = S->personnes;

    for (int i = 1; i < S->nb_personnes; i++) {
        if ((S->personnes + i)->duree_sejour > max->duree_sejour) {
            max = S->personnes + i;
        }
    }

    printf("La personne avec la plus longue duree de sejour dans le service %s est %s %s avec %d jours \n", S->libelle, max->nom, max->prenom ,max->duree_sejour);
    }



    int menu(){

    int choix =0 ;

    while(choix < 1 || choix >6 ){

        printf("Menu \n");

        printf(" 1: Affichage de toute les informations \n");
        printf(" 2: Afficher l'employe avec le meilleur rendement dans  le centre \n");
        printf(" 3: Afficher l'employe avec le meilleur rendement dans  le service  \n");
        printf(" 4: Afficher le service le plus demandee  \n");
        printf(" 5: Afficher le service le plus couteux  \n");
        printf(" 6: Afficher la personne la plus ancienne dans le service \n");
        printf(" 6: Afficher la personne la plus ancienne dans le service \n");


        printf("Votre choix ?");
        scanf("%d" ,&choix);
    }
    return choix;
    }


