//
//  main.c
//  Zeichenkette überprüfen
//
//  Created by Faris Elfellah on 08.10.20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGHT 100

void Writestring(char* z1,char* z2);

int main() {
    
    char* z1;
    char* z2;
    char* hilfstring;
    size_t length1,length2;
    z1=(char*) malloc(LENGHT * sizeof(char));
    z2=(char*) malloc(LENGHT * sizeof(char));
    Writestring(z1, z2);
    if((!strchr(z1,'A')||!strchr(z1,'C')||!strchr(z1,'D'))&&(!strchr(z2,'A')||!strchr(z2,'C')||!strchr(z2,'D'))){
        printf(" Falsche Eingabe!!! Bitte nochmal veruchen:\n ");
        Writestring(z1, z2);
    }
    length1= strlen(z1); // laenge ermitteln
    length2= strlen(z2); // laenge ermitteln
    printf("Laenge z1 : %zu , Laenge z2 : %zu \n",length1,length2);
    if (length1 > length2){
        printf("z1 ist laenger als z2\n");
        hilfstring = strstr(z2,z1);
        if(hilfstring){
            printf("z2 ist in z1 enthalten");
        }
    }
    else{
        printf("z2 ist laenger als z1\n");
    }
    
    
    return 0;
}

void Writestring(char* z1, char* z2){
    
    printf("Geben Sie zwei Strings ein:\n");
    printf("z1:");
    scanf("%s",z1);
    printf("z2:");
    scanf("%s",z2);
    printf("eingegebene Strings:\n");
    printf("z1:%s\n",z1);
    printf("z2:%s\n",z2);
}
