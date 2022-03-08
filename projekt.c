#include <stdio.h>
#include <stdlib.h>


void help(){
    system("clear");
    printf("***********************\n");
    printf("    ZPrPr2 Projekt 1\n\n");
    printf(" Funkcie\n");
    printf("  v - ???\n");
    printf("  o - vypis prispevkov s rovnakym datumom\n");
    printf("  n - zisti pocet zaznamov v subore, vytvori polia pre polozky\n");
    printf("  s - vypis prezentovani podla datumu\n");
    printf("  h - histogram typov prezentovania\n");
    printf("  z - vymazanie zaznamu podla nazvu\n");
    printf("  p - pridanie zaznamu\n");
    printf("  k - cistenie pamate\n\n");
    printf("  l - pomocne menu\n");
    printf("  x - ukoncenie\n");
    printf("\n***********************\n");
}

int main(){

    //? Menu
    char opt;
    printf(">: ");
    while(scanf("%c", &opt) < 1){
        printf("Neplatny vstup!\n");
        while(getchar() != '\n');
    }

    while(opt != 'x'){

        switch (opt){
            case 'v':
                printf("Funkcia V\n");
                break;
            case 'o':
                printf("Funkcia O\n");
                break;
            case 'n':
                printf("Funkcia N\n");
                break;
            case 's':
                printf("Funkcia S\n");
                break;
            case 'h':
                printf("Funkcia H\n");
                break;
            case 'z':
                printf("Funkcia Z\n");
                break;
            case 'p':
                printf("Funkcia P\n");
                break;
            case 'k':
                printf("Funkcia K\n");
                break;
            case 'l':
                help();
                break;

            default:
                printf("Neplatny vstup!");
                break;
        }


        printf("\n>: ");
        while(scanf("%c", &opt) < 1){
            printf("Neplatny vstup!");
            while(getchar() != '\n');
        }
        while(getchar() != '\n');
    }



    return 0;
}