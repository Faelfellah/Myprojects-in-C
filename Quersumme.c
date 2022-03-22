//
//  main.c
//  quersumme
//
//  Created by Faris Elfellah on 08.10.20.
//

#include <stdio.h>
#include <stdlib.h>


int Quersumme(long x);

int main() {
    long x,y,z;
    int sx,sy,sz;
    int swap;
    printf("Geben Sie die Zahlen  ein:\n");
    printf(" x : \n");
    scanf("%ld",&x);
    printf(" y : \n");
    scanf("%ld",&y);
    printf(" z : \n");
    scanf("%ld",&z);
    if ((x<0 && y<0 && z<0)){
        printf("Falsche Eingabe!!! Bitte versuchen Sie nochmal\n");
        printf("Geben Sie die Zahlen  ein:\n");
        printf(" x : \n");
        scanf("%ld",&x);
        printf(" y : \n");
        scanf("%ld",&y);
        printf(" z : \n");
        scanf("%ld",&z);
    }
    else {
    printf(" x : %ld\n",x);
    printf(" y : %ld\n",y);
    printf(" z : %ld\n",z);
    }
    sx = Quersumme(x);
    sy = Quersumme(y);
    sz = Quersumme(z);
    // Sortierverfahren
    if(sz > sx){  //sx wird definitiv die grösste Zahl
        swap = sx ;
        sx = sz;
        sz = swap;
    }
    if(sy > sx){
        swap=sx;
        sx = sy;
        sy= swap;
        
    }
    if(sz > sy){
        swap = sz;
        sz = sy;
        sy = swap;
    }
    printf("%d,%d,%d\n",sx,sy,sz);
    return 0;
}

int Quersumme(long zahl){
    int s = 0;
    
    while (zahl !=0 ){
        s = s + (zahl % 10);
        zahl = zahl / 10;
    }
    return s;
    
}
