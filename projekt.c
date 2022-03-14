#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void v( int *file_read, int *arrays_allocated, FILE **fr){
    if(*file_read){
        printf("Subor uz bol otvoreny!\n");
        if(*arrays_allocated){
            printf("Polia už boli alokované!");
        } else{
            printf("Citam zo suboru!\n\n");
            fseek(*fr, 0, SEEK_SET);

            *file_read = 1;

            char row[256];
            char *segment;

            int counter = 0;
            int length = 0;

            while(feof(*fr) == 0){
                fgets(row, 256,*fr);

                if(counter == 6){
                    counter = 0;
                    printf("\n");
                }

                switch(counter){
                    case 0:
                        printf("Nazov prispevku: ");
                        break;
                    case 1:
                        printf("Mena autorov: ");
                        break;
                    case 2:
                        printf("Typ prezentovania: ");
                        break;
                    case 3:
                        printf("Cas prezentovania: ");
                        break;
                    case 4:
                        printf("Datum: ");
                        break;
                    default:
                        break;
                }
                segment = strtok(row, "#");
                while(segment != NULL){
                    length = strlen(segment);
                    printf("%s", segment);
                    segment = strtok(NULL, "#");
                }

                counter++;
            }
        }

    } else{
        if((*fr = fopen("OrganizacnePodujatia.txt", "r")) == NULL){
            printf("Neotvoreny subor\n");
            return;
        }
        *file_read = 1;
    }
    return;

}

void n( int *point_file_read, int *point_arrays_allocated,char *nazvyPrispevkov, char *menaAutorov, char *typyPrezentovania, int *casyPrezentovania, int *datumy, FILE **fr ){
    if(! *point_file_read){
        printf("Neotvoreny subor");
        return;
    }
    if(*point_arrays_allocated){
        free(nazvyPrispevkov);
        free(menaAutorov);
        free(typyPrezentovania);
        free(casyPrezentovania);
        free(datumy);
    }
    int rowCount = 0;
    char c;
    fseek(*fr, 0, SEEK_SET);
    while(2){
        c = fgetc(*fr);
        if(c == EOF){
            rowCount++;
            break;
        }
        if(c == '\n'){
            rowCount++;
        }
    }

    fseek(*fr, 0, SEEK_SET);

    printf("%d ", rowCount);



    return;
}

void k( int *point_file_read, int *point_arrays_allocated,char *nazvyPrispevkov, char *menaAutorov, char *typyPrezentovania, int *casyPrezentovania, int *datumy, FILE **fr ){
    if(*point_file_read){
        if(fclose(fr) == NULL){
            printf("Súbor sa nezatvoril");
        }
    }
    if(*point_arrays_allocated){
        free(nazvyPrispevkov);
        free(menaAutorov);
        free(typyPrezentovania);
        free(casyPrezentovania);
        free(datumy);
    }
    return;
}



int main(){

    //! VARIABLES
    char opt;
    int file_read = 0;
    int arrays_allocated = 0;


    //! POINTERS
    int *point_file_read = &file_read;
    int *point_arrays_allocated = &arrays_allocated;
    FILE *fr;

    //! POLIA
    char *nazvyPrispevkov;
    char *menaAutorov;
    char *typyPrezentovania;
    int *casyPrezentovania;
    int *datumy;






    //? Menu
    printf(">: ");
    while(scanf("%c", &opt) < 1){
        printf("Neplatny vstup!\n");
        while(getchar() != '\n');
    }

    while(opt != 'x'){

        switch (opt){
            case 'v':
                v(point_file_read, point_arrays_allocated, &fr);
                break;
            case 'o':
                printf("Funkcia O\n");
                break;
            case 'n':
                n(point_file_read, point_arrays_allocated, nazvyPrispevkov, menaAutorov, typyPrezentovania, casyPrezentovania, datumy, &fr);
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
                k(point_file_read, point_arrays_allocated, nazvyPrispevkov, menaAutorov, typyPrezentovania, casyPrezentovania, datumy, &fr);
                break;
            case 'l':
                help();
                break;

            default:
                printf("Neplatny vstup!");
                break;
        }


        printf("\n>: ");
        while(scanf(" %c", &opt) < 1){
            printf("Neplatny vstup!");
            while(getchar() != '\n');
        }
        while(getchar() != '\n');
    }
    printf("See you later, alligator!");


    return 0;
}