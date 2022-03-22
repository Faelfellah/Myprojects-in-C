/*
 ============================================================================
 Name        : login2.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 ============================================================================
 Name        : Login.c
 Author      : Imad Najeh/ Youssef Elbaji
 Version     : 1
 Copyright   : Your copyright notice
 Description : Das Programm enthält 3 Funktion, mit der ersten Funktion kann man sich registrieren,
 mit der zweiten Funktion kann man sich einloggen, mit der letzten Funktion kan man das Passwort ändern
 die maximale Anzahl der Benuzern ist 120.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "console.h"

void passEinlesen(char pass[]) {
    int j = 0;

    char  caracter;

    do {
        caracter = getch(); // zeichenweise Einlesen vom Strings
        printf("*"); // Versteckung der Zeichnen
        // Enter und Backspace werden vom dem Vektor ausgeschloseen
        if ((caracter != 32) && (caracter != 10)) {
            pass[j] = caracter;
            j++;
        }

    } while (caracter != 10);        //Einlesen hört mit ENTER auf

    pass[j] = '\0';        //ende vom Array bestimmen
    printf("\n");
}

int main()
{
    //Deklaration der Variablen
    char Speicherung[120][2][14]; int counterspeicher=0;
    char benutzername[9];       // eine Variable für die Benutzername
    char passwort[14];          // eine Variable für das Passwort
    char passwort2[14];         // eine Variable für die Widerholung des Passworts
    int grosse ;                // eine Variable für die Grosse eines Arrays
    int i=0,j=0 ; int counter=0, counter0=0 , counter1=0 , counter2=0;      /// Zaehler
    int wahl=0;                 // eine Variable für die Do/while Schleiffe
    char neupasswort[14];         // eine Variable für die Speicherung des neues Passwort
    char altpasswort[14];         // eine Variable für den Vergleich des Passworts
    char neupasswort2[14];         // eine Variable für die Bestätigung des neues Passworts
    int anmeldungcounter=0;      // Zaehler
    int altpasswortcounter=0;           // zaehler für die Anzahl der falsche Passwoerte
    int anmeldversuch=0;                // zaehler für die Anzahl der falsche Anmeldungen
    printf("\n\n\t------Menu------\n\n");
    do{
        printf("1-Regristrierung\t2-Anmeldung\t3-Exit\n");
        scanf("%d",&wahl);
        switch (wahl)
           {
        case 1 :printf("Regristrierung\n");
                          {
        do{
        printf("Benutzername eingeben:\t ");
        scanf("%s",benutzername);        //Eingabe des Benutzername
        getchar();
        grosse=strlen(benutzername);
        if(benutzername[0]<65 || benutzername[0]>90)         //Für den ersten Großbuchstabe
        {
            printf("Das esrte Buchstabe muss gross sein\n");      // Fehlermeldung anzeigen
        }else if (grosse<6)      //Falls die Größe kleiner als 6 Zeichen
        {
            printf("Der Benutzename muss mindesten 6 Zeichen enthalten\n");      // Fehlermeldung anzeigen
        }else if(grosse>9)       //Falls die Größe grosser als 9 Zeichen
        {
            printf("Der Benutzername darf maximal 9 Zeichen enthalten\n");      // Fehlermeldung anzeigen
        }
        for(i=1;i<grosse;i++)
        {
            if((benutzername[i]<97 || benutzername[i]>122) && (benutzername[i]<48 || benutzername[i]>57))/*
            Hier wird on ab dem zweiten Zeichen nur kleine Buchstaben bzw. Ziffern enthalten kontrolliert*/
            {
                printf("Benutzername muss ab dem zweiten Zeichen nur aus Kleinbuchstaben oder dezimalen Ziffern bestehen\n");
                i =grosse;    //Schleife abbechen falls bedingung erfüllt ist
                counter=1;
            }else counter=0;
        }
        }while((benutzername[0] < 65 || benutzername[0]>90) || (grosse<6 || grosse>9) || counter==1);//Solange die ganzen Bedingungen erfüllt

        do{

        printf("Passwort eingeben:\t ");
        //getchar();
        passEinlesen(passwort);
        //scanf("%s",passwort);//Eingabe des Passworts
        grosse=strlen(passwort);
        int i;
        /*for(i=0;i<=grosse;i++)
            {
                printf("*");
            }*/
        //printf("\n");
        if(grosse<8)
        {
            printf("Das Passwort muss mindestens 8 Zeichen enthalten\n");     // Fehlermeldung anzeigen

        }else if(grosse>14)
        {
            printf("Das Passwort darf maximal 14 Zeichen enthalten\n");          // Fehlermeldung anzeigen
        }
        for (i=0;i<grosse;i++)
        {
            if((passwort[i]>=48) && (passwort[i]<=57))
            {
                counter0=0;break;
            }
            else if(((passwort[i]<48) || (passwort[i]>57)) && (i==grosse-1))
            {
                printf("Das Passwort muss mindestens eine Ziffer enthalten\n");          // Fehlermeldung anzeigen
                counter0=1;
            }

        }
        for(i=0;i<grosse;i++)
        {
            if((passwort[i]>=65) && (passwort[i]<=90))
            {
                counter1=0;
                break;
            }
           else if(((passwort[i]<65)||(passwort[i]>90))&& (i==grosse-1))
            {
                printf("Passwort muss mindestens einen Grossbuchstabe enthalten\n");        // Fehlermeldung anzeigen
                counter1=1;
            }
        }
        for(i=0;i<grosse;i++)
        {
            if((passwort[i]>=97) && (passwort[i]<=122))
            {
                counter2=0;
                break;
            }
           else if(((passwort[i]<97)||(passwort[i]>122)) && (i==grosse-1))
            {
                printf("Passwort muss mindestens einen kleinen Buchstabe enthalten\n");        // Fehlermeldung anzeigen
                counter2=1;
            }
        }
        }while((grosse<8 || grosse>12) || counter0==1 || counter1==1 || counter2==1);

        printf("Passwort bestaetigen: ");

        do
        {
         scanf("%s",passwort2);
        for(i=0 ; i<=grosse ; i++)
        {
            printf("*");
        }
        printf("\n");
        if(strcmp(passwort,passwort2)==0)
        {
           printf("\nSie haben sich erfolgreich registriert\n\n");
           counter=0;
        }else
        {
           printf("Passworte stimmen nicht ueberein! Geben Sie das Passwort nochmal ein:");        // Fehlermeldung anzeigen
           counter=1;
        }
        }while(counter==1);

        strcpy(Speicherung[counterspeicher][0],benutzername);//Speicherung des Benutzername
        strcpy(Speicherung[counterspeicher][1],passwort);//Speicherung des Passworts
        counterspeicher++;
                          };//zur Ragistrierung
                          break;
       case 2 :   printf("Anmeldung\n");
          {
        do{
        printf("Geben sie Ihren Benutzername ein: ");
        scanf("%s",benutzername);//Eingabe des Benutzername
        printf("Geben Sie Ihr Passwort ein: ");
        scanf("%s",passwort);//Eingabe des Passworts
        for (i=0 ; i<=passwort[i] ; i++)
            {
                printf("*");
            }
        printf("\n");
        for (i=0;i<counterspeicher;i++)
            {
                if(strcmp(Speicherung[i][0],benutzername)==0 && strcmp(Speicherung[i][1],passwort)==0)/*Wenn die eingegebenen Daten mit den regestrierten Daten uebereinstimmen */

                       {
                             printf("Die anmeldung ist erfolgreich\n\n");
                             anmeldungcounter=1;
                             break;//Erfolgreiche Anmeldung
                       }
                else if(strcmp(Speicherung[i][0],benutzername)!=0)/* Wenn der eingegebene Benutzername mit dem regestrierten Benutzername nicht uebereinstimmt */
                       {
                             printf("\t!!!Fehlerhaft!!!\n\t<!!Falcher Benutzername!!>\n\n");    // Fehlermeldung anzeigen
                             anmeldversuch++;
                       }
                else if( strcmp(Speicherung[i][1],passwort)!=0)
                       {
                             printf("\t!!!Fehler!!!\n\t<!!Falches Passwort!!>\n\n");/* Wenn das eingegebene Passwort mit dem regestrierten Passwort nicht uebereinstimmt */
                             anmeldversuch++;
                       }

            }
         if(anmeldversuch==3)/* Nach drei Anmeldeversuche wird der Benutzer 2min gesperrt*/
            {

               clock_t akt_zeit;//arithmetischer Datentyp für die CPU-Zeit
               clock_t end_zeit;//arithmetischer Datentyp für die CPU-Zeit
               int zahl=120;
               printf("Sie haben das Passwort 3 mal falsch eingegebne sie werden 2min gesperrt\n ");
               printf("Warten Sie bitte!\n");
               while(zahl!=0)
               {
                   // Ende_Zeit berechnen
                   end_zeit=clock()+CLOCKS_PER_SEC;
                   do {
                         // Aktuelle_Zeit auslesen
                         akt_zeit=clock();
                      }
                   while(akt_zeit<end_zeit);
              // eine Sekunde ist um
              zahl--;
              }
            }
          }
        while(anmeldungcounter!=1);

        do{/* Wenn der Benutzer sich erfolgreich
            angemeldet hat, kann er das Passwort ändern oder abbrechen */
            printf("1-Das Passwort aendern\n2-Exit\n");
            scanf("%d",&wahl);
            switch(wahl)
            {
        case 1:{
        printf("Die Passwortaenderung\n");//Zur Passwort änderung
        do
            {
            printf("Geben Sie das alte Passwort ein:");
            do
            {
                scanf("%s",altpasswort);//Eingabe des alten Passwort
                if (strcmp(altpasswort,passwort)!=0)
                {
                    printf("Das alte Passwort ist falsch , versuchen Sie nochmal!");
                    altpasswortcounter++;
                }
                  //Wenn das alte Passwsort mit dem eingegebenen Passwort nicht überein stimmt
                else if (strcmp(altpasswort,passwort)==0)
                    break;
                 //wenn das alte Passwort mit dem eingegebenen Passwort übereinstimmt
            }while(altpasswortcounter<3);
            printf("Geben Sie das neue Passwort ein: ");
             //getchar();
            scanf("%s",neupasswort);//Eingabe des neuen Passworts
            grosse=strlen(neupasswort);
            printf("%s\n",neupasswort);

            if(grosse<8)//wenn die Grösse des Benutzername kleiner als 8 Zeichen
            {
                printf("Das Passwort muss mindestens 8 Zeichen lang sein\n");       // Fehlermeldung anzeigen

            }else if(grosse>14)//Wenn die Grösse des Benutzername grosser als 14 Zeichen
            {
                printf("Das Passwort darf maximal 14 Zeichen lang sein\n");            // Fehlermeldung anzeigen
            }
            for (i=0;i<grosse;i++)
            {
                if((neupasswort[i]>=48) && (neupasswort[i]<=57))//Für Ziffern
                    {
                          counter0=0;
                          break;
                    }
                else if(((neupasswort[i]<48) || (neupasswort[i]>57)) && (i==grosse-1))//wenn die Ziffern nicht enthalten
                    {
                          printf("Das Passwort muss mindestens eine Ziffer enthalten\n");       // Fehlermeldung anzeigen
                          counter0=1;
                    }

            }
            for(i=0;i<grosse;i++)
            {
                if((neupasswort[i]>=65) && (neupasswort[i]<=90))//Für Großbuchstaben
                    {
                          counter1=0;
                          break;
                    }
                else if(((neupasswort[i]<65)||(neupasswort[i]>90))&& (i==grosse-1))//Wenn kein Großbuchstabe enthalten
                    {
                          printf("Passwort muss mindestens ein Grossbuchstaben enthalten\n");    // Fehlermeldung anzeigen
                          counter1=1;//Großbuchstabe
                    }
            }
            for(i=0;i<grosse;i++)
            {
                if((neupasswort[i]>=97) && (neupasswort[i]<=122))//für kleine Buchstaben
                     {
                          counter2=0;
                          break;
                    }
                else if(((neupasswort[i]<97)||(neupasswort[i]>122)) && (i==grosse-1))//wenn keinen Kleinen Buchstabe enthalten
                    {
                          printf("Passwort muss mindestens ein klein Buchstabe enthalten\n");   // Fehlermeldung anzeigen
                          counter2=1;
                    }
            }
            }while((grosse<8 || grosse>12) || counter0==1 || counter1==1 || counter2==1);    //soalnge der string kleiner ist als 8 oder größer als 12 wird die abfrage wiederholt
                //Passwort bestätigung
        printf("Neues Passwort bestaetigen: ");
        do
        {
           scanf("%s",neupasswort2);//Eingabe des neuen Passworts
           if(strcmp(neupasswort,neupasswort2)==0)//die beiden Passworte vergleichedn
              {
                    printf("\nKorrektes Passwort. Das neue Passwort wurde erfolgreich gaendert\n\n");
                  for(i=0;i<counterspeicher;i++)
                  {
                       if(strcmp(Speicherung[i][0],benutzername)==0)
                        {
                            strcpy(Speicherung[i][1],neupasswort);
                        }//Speicherung des neuen Passworts
                  }
                  counter=0;
            }else
                        //Falls das alte Passwort falsch eingegeben wird
            {
                  printf("Falsches Passwort! Geben Sie das Passwort nochmal ein:");     // Fehlermeldung anzeigen
                  counter=1;
            }
        }while(counter==1);
            }
                case 2 :  {
                for (i=0;i<counterspeicher;i++)
                 {
                       printf("%d - Benutzername: %s\tPasswort: %s \n",i+1,Speicherung[i][0],Speicherung[i][1]);
                 }
                };
                          getchar();
                          exit(0);
                default:    {
                               printf("Druecken Sie nur 1 oder 2 \n");
                               j=1;
                            }

            }
            }while(wahl==1||wahl==2||j==1);
                          };//zur Anmeldung
                          break;
               case 3 :   {
               for (i=0;i<counterspeicher;i++)
                {
                     printf("%d - Benutzername: %s\tPasswort: %s \n",i+1,Speicherung[i][0],Speicherung[i][1]);
                }
               };
                          getchar();
                          exit(0);//Zum Abbrechen
               default:   printf("Druecken Sie nur 1, 2 oder 3\n"); j=1;
           }
     }while(wahl==1||wahl==2||wahl==3||j==1);
     return 0;
}
