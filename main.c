//
//  main.c
//  Binomialkoeffizienten
//
//  Created by Faris Elfellah on 12.10.20.
//

#include <stdio.h>
#include <stdlib.h>

void binomialkoeffizient(int n);

int main(void) {
    int Eingabe = 0;

    printf("Bitte geben Sie eine natürliche Zahl >= 0 ein!\n");
    scanf("%i", &Eingabe);
    if(Eingabe < 0 ) {
        printf("Die Eingabe muss eine natürliche Zahl >= 0 sein!\n");
        return -1;
    }
   binomialkoeffizient(Eingabe);
    return 0;
}


void binomialkoeffizient(int n) {
    int ergebnis[n];
    int z;

    for(int i = 0; i <= n; i++) {
        z = 1;
        z = (ergebnis[i-1]* (n-i+1)) / i;
        ergebnis[i] = z;
        printf("k = %i Binomialkoeffizient=%i\n", i, z);
    }
}


