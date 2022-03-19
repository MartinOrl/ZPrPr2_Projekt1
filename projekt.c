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
    printf("\n");
    printf("  k - ukoncenie\n\n");
    printf("  l - pomocne menu\n");
    printf("\n***********************\n");
}

void v( int *point_file_read, int *point_arrays_allocated,char **nazvyPrispevkov[], char **menaAutorov[] , char **typyPrezentovania[],char **casyPrezentovania[], char **datumy[], FILE **fr ){
    // Checks if file was open for reading
    if(*point_file_read){
        printf("Subor uz bol otvoreny!\n");
        // Checks if arrays have been allocated
        if(*point_arrays_allocated){
            // Prints individual records loaded from arrays
            for(int i = 0; i < *point_arrays_allocated; i++){
                printf("Nazov prispevku: %.150s\n", (*nazvyPrispevkov)[i]);
                printf("Mena autorov: %.100s\n", (*menaAutorov)[i]);
                printf("Typ prezentovania: %s\n", (*typyPrezentovania)[i]);
                printf("Cas prezentovania: %c%c:%c%c\n", (*casyPrezentovania)[i][0], (*casyPrezentovania)[i][1], (*casyPrezentovania)[i][2],(*casyPrezentovania)[i][3]);
                printf("Datum: %s\n", (*datumy)[i]);
                printf("\n");
            }
            return;
        } else{
            // Sets file cursor to the beggining of file
            fseek(*fr, 0, SEEK_SET);
            *point_file_read = 1;
            char row[256];
            char *segment;
            int counter = 0;
            // Loops through the file and prints values to their respective category
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
                    printf("%s", segment);
                    segment = strtok(NULL, "#");
                }
                free(segment);
        
                counter++;
            }
           
        }
        return;

    } 
    // Runs in case file wasn't opened yet
    if((*fr = fopen("OrganizacnePodujatia.txt", "r")) == NULL){
        printf("Neotvoreny subor\n");
        return;
    }
    *point_file_read = 1;
    char row[256];
    char *segment;
    int counter = 0;
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
            printf("%s", segment);
            segment = strtok(NULL, "#");
        }
        free(segment);

        counter++;
    }
    
    return;

}

void n( int *point_file_read, int *point_arrays_allocated,char ***nazvyPrispevkov, char ***menaAutorov, char ***typyPrezentovania, char ***casyPrezentovania, char ***datumy,FILE **fr ){
    if(! *point_file_read){
        printf("Neotvoreny subor");
        return;
    }
    // Checks if arrays have been allocated before and deallocs them, also checks if file was opened. If yes, it gets closed
    if(*point_arrays_allocated){
        for(int j = 0; j < *point_arrays_allocated; j++){
            free((*nazvyPrispevkov)[j]);
            free((*menaAutorov)[j]);
            free((*typyPrezentovania)[j]);
            free((*casyPrezentovania)[j]);
            free((*datumy)[j]);
        }
        free(*nazvyPrispevkov);
        free(*menaAutorov);
        free(*typyPrezentovania);
        free(*casyPrezentovania);
        free(*datumy);
        *point_arrays_allocated = 0;
        if(fclose(*fr)){
            printf("AAAA\n");

        }
        if((*fr = fopen("OrganizacnePodujatia.txt", "r")) == NULL){
            printf("Neotvoreny subor\n");
            return;
        }
    }
    int rowCount = 0;
    char c;
    // Loops through the file and counts rows in file
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
    // Computes number of data blocks in file
    int groupCount = rowCount / 6;
    int i = 0;

    // Allocating 2D arrays
    *nazvyPrispevkov = (char**) malloc(groupCount * sizeof(char*) );
    *menaAutorov = (char **) malloc(groupCount * sizeof(char *));
    *typyPrezentovania = (char **) malloc(groupCount * sizeof(char *));
    *casyPrezentovania = (char **) malloc(groupCount * sizeof(char *));
    *datumy = (char **) malloc(groupCount * sizeof(char *));
    for(i = 0; i < groupCount; i++){
        (* nazvyPrispevkov)[i] = (char *) malloc(256 *sizeof(char));
        (* menaAutorov)[i] = (char *) malloc(256 *sizeof(char));
        (* typyPrezentovania)[i] = (char *) malloc(256 *sizeof(char));
        (* casyPrezentovania)[i] = (char *) malloc(256 *sizeof(char));
        (* datumy)[i] = (char *) malloc(256 *sizeof(char));
    }

    fseek(*fr, 0, SEEK_SET);
    char row[256];
    i = 0;
    // Loops through the file and saves data to the respective 2d array
    while(feof(*fr) == 0){
        rowCount++;
        fgets(row, 256, *fr);
        // Searches for newline character in string, and removes it in the next line
        char *rem_newline = strrchr(row, '\n');
        if(rem_newline){
            *rem_newline = '\0';
        }
        if(rowCount % 6 == 1){
            strcpy((*nazvyPrispevkov)[i], row);
        }
        else if(rowCount % 6 == 2){
            strcpy((*menaAutorov)[i], row);
        }
        else if(rowCount % 6 == 3){
            strcpy((*typyPrezentovania)[i], row);
        }
        else if(rowCount % 6 == 4){
            strcpy((*casyPrezentovania)[i], row);
        }
        else if(rowCount % 6 == 5){
            strcpy((*datumy)[i], row);
        }
        else{
            i++;
        }
    }
    printf("Nacitane data\n");
    // Sets allocated arrays count to the number of blocks of data
    *point_arrays_allocated = groupCount;
    return;
}

void p(int *point_file_read, int *point_arrays_allocated,char ***nazvyPrispevkov, char ***menaAutorov, char ***typyPrezentovania, char ***casyPrezentovania, char ***datumy, int *pointer_special_alloc){
    
    char nazov[128];
    char meno[64];
    char typ[64];
    char cas[64];
    char datum[64];
    
    scanf("%[^\n]", &nazov);
    while(getchar() != '\n');
    scanf("%[^\n]", &meno);
    while(getchar() != '\n');
    scanf("%[^\n]", &typ);
    while(getchar() != '\n');
    scanf("%[^\n]", &cas);
    while(getchar() != '\n');
    scanf("%[^\n]", &datum);
    while(getchar() != '\n');
    
    // Starts checking inputs for correct specifications and allocated arrays existence
    if(! *point_arrays_allocated && ! *pointer_special_alloc){
        printf("Polia nie su vytvorene\n");
        return;
    }

    if(strcmp(typ,"UP") && strcmp(typ,"UD") && strcmp(typ,"PP") && strcmp(typ,"PD")){
        printf("Neplatny typ! Ukoncujem\n");
        return;
    }
    if((int) atoi(cas) == 0 || (int) atoi(datum) == 0){
        printf("Neplatny cas alebo datum! Ukoncujem funkciu!\n");
        return;
    }
    if((int) atoi(cas) > 2400 || (int) atoi(cas) < 0){
        printf("Neplatna hodnota casu! Ukoncujem funkciu!");
        return;
    }
    if((int) strlen(datum) != 8){
        printf("Neplatna hodnota datumu! Ukoncujem funkciu!");
        return;
    }

    // Reallocs 2d arrays to store new data records
    *nazvyPrispevkov = (char **) realloc(*nazvyPrispevkov,*point_arrays_allocated * sizeof(char *) + sizeof(char *));
    *menaAutorov = (char **) realloc(*menaAutorov,*point_arrays_allocated * sizeof(char *) + sizeof(char *));
    *typyPrezentovania = (char **) realloc(*typyPrezentovania,*point_arrays_allocated * sizeof(char *) + sizeof(char *));
    *casyPrezentovania = (char **) realloc(*casyPrezentovania,*point_arrays_allocated * sizeof(char *) + sizeof(char *));
    *datumy = (char **) realloc(*datumy,*point_arrays_allocated * sizeof(char *) + sizeof(char *));

    // Allocates the memory for subarrays
    (*nazvyPrispevkov)[*point_arrays_allocated] = (char *) malloc(256 * sizeof(char));
    (*menaAutorov)[*point_arrays_allocated] = (char *) malloc(256 * sizeof(char));
    (*typyPrezentovania)[*point_arrays_allocated] = (char *) malloc(256 * sizeof(char));
    (*casyPrezentovania)[*point_arrays_allocated] = (char *) malloc(256 * sizeof(char));
    (*datumy)[*point_arrays_allocated] = (char *) malloc(256 * sizeof(char));

    // Pastes new data to reallocated arrays
    strcpy((*nazvyPrispevkov)[*point_arrays_allocated], nazov);
    strcpy((*menaAutorov)[*point_arrays_allocated], meno);
    strcpy((*typyPrezentovania)[*point_arrays_allocated], typ);
    strcpy((*casyPrezentovania)[*point_arrays_allocated], cas);
    strcpy((*datumy)[*point_arrays_allocated], datum);

    *point_arrays_allocated += 1;

    printf("Zaznam sa podarilo pridat");

    return;    
}

void o(int *point_file_read, int *point_arrays_allocated,char ***nazvyPrispevkov, char ***menaAutorov, char ***typyPrezentovania, char ***casyPrezentovania, char ***datumy, FILE **fr){

    int datum = 0;
    int helper = 0;
    int posHelper = 0;
    int pos_switch_helper = 0;
    int pos_switch_temp = 0;
    int match_found = 0;
 
    if(scanf("%d", &datum) < 1){
        printf("Neplatny vstup! Ukoncujem funkciu!\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');
    if(*point_arrays_allocated){
        int *upIndexes, *udIndexes, *ppIndexes, *pdIndexes;
        int upPos = 0, udPos = 0, ppPos = 0, pdPos = 0;

        // Allocates memory for arrays containing indexes for each presentation type category based on number of allocated arrays
        upIndexes = (int *) malloc(*point_arrays_allocated * sizeof(int));
        udIndexes = (int *) malloc(*point_arrays_allocated * sizeof(int));
        ppIndexes = (int *) malloc(*point_arrays_allocated * sizeof(int));
        pdIndexes = (int *) malloc(*point_arrays_allocated * sizeof(int));
        
        // Loops through the allocated arrays with records, finds a match and stores index of it in respective array
        for(int i = 0; i < *point_arrays_allocated; i++){
            helper = (int)atoi((*datumy)[i]);
            if(helper == datum){
                match_found = 1;
                if(!strcmp((*typyPrezentovania)[i], "UP")){
                    upIndexes[upPos] = i;
                    upPos++;
                }
                else if(!strcmp((*typyPrezentovania)[i], "UD")){
                    udIndexes[udPos] = i;
                    udPos++;
                }
                else if(!strcmp((*typyPrezentovania)[i], "PP")){
                    ppIndexes[ppPos] = i;
                    ppPos++;
                }
                else if(!strcmp((*typyPrezentovania)[i], "PD")){
                    pdIndexes[pdPos] = i;
                    pdPos++;
                }
            }
        }
        if(!match_found){
            printf("Pre dany vstup neexistuju zaznamy!\n");
            return;
        }

        // Next 4 for loops bubble sort each index arrays based on values of presentation times of their respective category
        for(int i = 0; i < upPos-1; i++){
            for(int j = 0; j < upPos - 1 - i; j++){
                helper = (int) atoi((*casyPrezentovania)[upIndexes[j]]);
                pos_switch_helper = (int) atoi((*casyPrezentovania)[upIndexes[j+1]]);
                if(helper > pos_switch_helper){
                    pos_switch_temp = upIndexes[j];
                    upIndexes[j] = upIndexes[j+1];
                    upIndexes[j+1] = pos_switch_temp;
                }
            }
        }

        for(int i = 0; i < udPos-1; i++){
            for(int j = 0; j < udPos - 1 - i; j++){
                helper = (int) atoi((*casyPrezentovania)[udIndexes[j]]);
                pos_switch_helper = (int) atoi((*casyPrezentovania)[udIndexes[j+1]]);
                if(helper > pos_switch_helper){
                    pos_switch_temp = udIndexes[j];
                    udIndexes[j] = udIndexes[j+1];
                    udIndexes[j+1] = pos_switch_temp;
                }
            }
        }

        for(int i = 0; i < ppPos-1; i++){
            for(int j = 0; j < ppPos - 1 - i; j++){
                helper = (int) atoi((*casyPrezentovania)[ppIndexes[j]]);
                pos_switch_helper = (int) atoi((*casyPrezentovania)[ppIndexes[j+1]]);
                if(helper > pos_switch_helper){
                    pos_switch_temp = ppIndexes[j];
                    ppIndexes[j] = ppIndexes[j+1];
                    ppIndexes[j+1] = pos_switch_temp;
                }
            }
        }

        for(int i = 0; i < pdPos-1; i++){
            for(int j = 0; j < pdPos - 1 - i; j++){
                helper = (int) atoi((*casyPrezentovania)[pdIndexes[j]]);
                pos_switch_helper = (int) atoi((*casyPrezentovania)[pdIndexes[j+1]]);
                if(helper > pos_switch_helper){
                    pos_switch_temp = pdIndexes[j];
                    pdIndexes[j] = pdIndexes[j+1];
                    pdIndexes[j+1] = pos_switch_temp;
                }
            }
        }
        // Prints output
        for(int i = 0; i < udPos; i++){
            printf("%s %s %s %s\n",(*casyPrezentovania)[udIndexes[i]], (*typyPrezentovania)[udIndexes[i]], (*menaAutorov)[udIndexes[i]], (*nazvyPrispevkov)[upIndexes[i]]);
        }
        for(int i = 0; i < upPos; i++){
            printf("%s %s %s %s\n",(*casyPrezentovania)[upIndexes[i]], (*typyPrezentovania)[upIndexes[i]], (*menaAutorov)[upIndexes[i]], (*nazvyPrispevkov)[upIndexes[i]]);
        }
        for(int i = 0; i < ppPos; i++){
            printf("%s %s %s %s\n",(*casyPrezentovania)[ppIndexes[i]], (*typyPrezentovania)[ppIndexes[i]], (*menaAutorov)[ppIndexes[i]], (*nazvyPrispevkov)[ppIndexes[i]]);
        }
        for(int i = 0; i < pdPos; i++){
            printf("%s %s %s %s\n",(*casyPrezentovania)[pdIndexes[i]], (*typyPrezentovania)[pdIndexes[i]], (*menaAutorov)[pdIndexes[i]], (*nazvyPrispevkov)[pdIndexes[i]]);
        }
        // Freeing mallocated index arrays
        free(upIndexes);
        free(udIndexes);
        free(pdIndexes);
        free(ppIndexes);
        return;
    }

    if(*point_file_read){
        char **nazvy;
        char **mena;
        char **typy;
        char **casy;
        char **datumy_v;
        rewind(*fr);
        char c = ' ';
        int rowCount = 0;
        while(1){
            c = fgetc(*fr);
            if(c == EOF){
                rowCount++;
                break;
            }
            if(c == '\n'){
                rowCount++;
            } 
        }
        int tempCount = rowCount / 6;
        nazvy = (char**) malloc(tempCount * sizeof(char *));
        mena = (char**) malloc(tempCount * sizeof(char *));
        typy = (char**) malloc(tempCount * sizeof(char *));
        casy = (char**) malloc(tempCount * sizeof(char *));
        datumy_v = (char**) malloc(tempCount * sizeof(char *));
        for(int i = 0; i < tempCount; i++){
            nazvy[i] = (char *) malloc(256 *sizeof(char));
            mena[i] = (char *) malloc(256 *sizeof(char));
            typy[i] = (char *) malloc(256 *sizeof(char));
            casy[i] = (char *) malloc(256 *sizeof(char));
            datumy_v[i] = (char *) malloc(256 *sizeof(char));
        }
        rewind(*fr);
        char row[256];
        int i = 0;
        rowCount = 0;
        while(feof(*fr) == 0){
            rowCount++;
            fgets(row, 256, *fr);
            char *rem_newline = strrchr(row, '\n');
            if(rem_newline){
                *rem_newline = '\0';
            }
            if(rowCount % 6 == 1){
                strcpy(nazvy[i], row);
            }
            else if(rowCount % 6 == 2){
                strcpy(mena[i], row);
            }
            else if(rowCount % 6 == 3){
                strcpy(typy[i], row);
            }
            else if(rowCount % 6 == 4){
                strcpy(casy[i], row);
            }
            else if(rowCount % 6 == 5){
                strcpy(datumy_v[i], row);
            }
            else{
                i++;
            }
        }

        int *upIndexes, *udIndexes, *ppIndexes, *pdIndexes;
        int upPos = 0, udPos = 0, ppPos = 0, pdPos = 0;

        upIndexes = (int *) malloc(tempCount * sizeof(int));
        udIndexes = (int *) malloc(tempCount * sizeof(int));
        ppIndexes = (int *) malloc(tempCount * sizeof(int));
        pdIndexes = (int *) malloc(tempCount * sizeof(int));

        for(int i = 0; i < tempCount; i++){
            helper = (int)atoi(datumy_v[i]);
            if(helper == datum){
                match_found = 1;
                if(!strcmp(typy[i], "UP")){
                    upIndexes[upPos] = i;
                    upPos++;
                }
                else if(!strcmp(typy[i], "UD")){
                    udIndexes[udPos] = i;
                    udPos++;
                }
                else if(!strcmp(typy[i], "PP")){
                    ppIndexes[ppPos] = i;
                    ppPos++;
                }
                else if(!strcmp(typy[i], "PD")){
                    pdIndexes[pdPos] = i;
                    pdPos++;
                }
            }
        }
        if(!match_found){
            printf("Pre dany vstup neexistuju zaznamy!\n");
            return;
        }

        for(int i = 0; i < upPos-1; i++){
            for(int j = 0; j < upPos - 1 - i; j++){
                helper = (int) atoi(casy[upIndexes[j]]);
                pos_switch_helper = (int) atoi(casy[upIndexes[j+1]]);
                if(helper > pos_switch_helper){
                    pos_switch_temp = upIndexes[j];
                    upIndexes[j] = upIndexes[j+1];
                    upIndexes[j+1] = pos_switch_temp;
                }
            }
        }

        for(int i = 0; i < udPos-1; i++){
            for(int j = 0; j < udPos - 1 - i; j++){
                helper = (int) atoi(casy[udIndexes[j]]);
                pos_switch_helper = (int) atoi(casy[udIndexes[j+1]]);
                if(helper > pos_switch_helper){
                    pos_switch_temp = udIndexes[j];
                    udIndexes[j] = udIndexes[j+1];
                    udIndexes[j+1] = pos_switch_temp;
                }
            }
        }

        for(int i = 0; i < ppPos-1; i++){
            for(int j = 0; j < ppPos - 1 - i; j++){
                helper = (int) atoi(casy[ppIndexes[j]]);
                pos_switch_helper = (int) atoi(casy[ppIndexes[j+1]]);
                if(helper > pos_switch_helper){
                    pos_switch_temp = ppIndexes[j];
                    ppIndexes[j] = ppIndexes[j+1];
                    ppIndexes[j+1] = pos_switch_temp;
                }
            }
        }

        for(int i = 0; i < pdPos-1; i++){
            for(int j = 0; j < pdPos - 1 - i; j++){
                helper = (int) atoi(casy[pdIndexes[j]]);
                pos_switch_helper = (int) atoi(casy[pdIndexes[j+1]]);
                if(helper > pos_switch_helper){
                    pos_switch_temp = pdIndexes[j];
                    pdIndexes[j] = pdIndexes[j+1];
                    pdIndexes[j+1] = pos_switch_temp;
                }
            }
        }

        for(int i = 0; i < udPos; i++){
            printf("%s %s %s %s\n",casy[udIndexes[i]], typy[udIndexes[i]], mena[udIndexes[i]], nazvy[upIndexes[i]]);
        }
        for(int i = 0; i < upPos; i++){
            printf("%s %s %s %s\n",casy[upIndexes[i]], typy[upIndexes[i]], mena[upIndexes[i]], nazvy[upIndexes[i]]);
        }
        for(int i = 0; i < ppPos; i++){
            printf("%s %s %s %s\n",casy[ppIndexes[i]], typy[ppIndexes[i]], mena[ppIndexes[i]], nazvy[ppIndexes[i]]);
        }
        for(int i = 0; i < pdPos; i++){
            printf("%s %s %s %s\n",casy[pdIndexes[i]], typy[pdIndexes[i]], mena[pdIndexes[i]], nazvy[pdIndexes[i]]);
        }


        

        free(upIndexes);
        free(udIndexes);
        free(pdIndexes);
        free(ppIndexes);

        for(int i = 0; i < tempCount; i++){
            free(nazvy[i]);
            free(mena[i]);
            free(typy[i]);
            free(casy[i]);
            free(datumy_v[i]);
        }
        free(nazvy);
        free(mena);
        free(typy);
        free(casy);
        free(datumy_v);

        return;
    }
    printf("Subor nebol otvoreny\n");
    return;
}

void h(int *point_file_read, int *point_arrays_allocated,char ***nazvyPrispevkov, char ***menaAutorov, char ***typyPrezentovania, char ***casyPrezentovania, char ***datumy){
    if(*point_arrays_allocated == 0){
        printf("Polia nie su vytvorene\n");
        return;
    } else{
        int up[] = {0,0,0,0,0,0};
        int ud[] = {0,0,0,0,0,0};
        int pp[] = {0,0,0,0,0,0};
        int pd[] = {0,0,0,0,0,0};
        int help_index = 0;
        int help_val = 0;
        int h = 8;
        printf("   hodina      UP   UD   PP   PD\n");
        for(int i = 0; i < *point_arrays_allocated; i++){
            help_val = (int)atoi((*casyPrezentovania)[i]);
            // Calculates index based on time, if index < 0 or index > 5, skips a loop iteration, as the time they represent isn't supposed to be in the intervals as specified in the project documentation
            help_index = (help_val - 800) / 200;
            if(help_index < 0 || help_index > 5){
                continue;
            }
            // Starts comparing presentation type value at index i with predefined categories and incrementing value stored at respective category array at calculated index
            if(strcmp((*typyPrezentovania)[i], "UP") == 0){
                up[help_index]++;
            }
            if(strcmp((*typyPrezentovania)[i], "UD") == 0){
                ud[help_index]++;
            }
            if(strcmp((*typyPrezentovania)[i], "PP") == 0){
                pp[help_index]++;
            }
            if(strcmp((*typyPrezentovania)[i], "PD") == 0){
                pd[help_index]++;
            }
        }
        // Prints histogram output
        for(int i = 0; i < 6; i++){
            printf("%.2d:00-%.2d:59:    %d    %d    %d    %d\n", h + i*2, h+1 + i*2, up[i], ud[i], pp[i], pd[i]);
        }
    }
    return;
}

void s(int *point_file_read, int *point_arrays_allocated,char ***nazvyPrispevkov, char ***menaAutorov, char ***typyPrezentovania, char ***casyPrezentovania, char ***datumy){
    if(!*point_arrays_allocated){
        printf("Polia nie su vytvorene!\n");
        return;
    }
    int datum = 0;
    char typ[3];
    int helper = 0;
    int found = 0;
    scanf("%d", &datum);
    scanf("%s", &typ);
    // Loops through allocated arrays to look for match at date and type of presentation, if match found, it prints it to the console
    for(int i = 0; i < *point_arrays_allocated; i++){
        helper = (int) atoi((*datumy)[i]);
        if(helper == datum && !strcmp((*typyPrezentovania)[i], typ)){
            printf("%s %s  %s\n", (*casyPrezentovania)[i], (*menaAutorov)[i], (*nazvyPrispevkov)[i]);
            found++;
        }
    }
    if(!found){
        printf("Pre dany vstup neexistuju zaznamy\n");
        while(getchar() != '\n');
    }
    return;

}

void z(int *point_file_read, int *point_arrays_allocated,char ***nazvyPrispevkov, char ***menaAutorov, char ***typyPrezentovania, char ***casyPrezentovania, char ***datumy, int *pointer_special_alloc){
    if(! *point_arrays_allocated){
        printf("Polia nie su vytvorene!");
        return;
    }
    char nazov_target[256];
    scanf("%[^\n]", &nazov_target);
    int erased_count = 0;
    int *indexes;
    // Allocates memory for index array of records that need to be erased
    indexes = (int *) malloc(*point_arrays_allocated * sizeof(int));

    // Loops through the array to look for a match at name of presentation, if match found, saves index to indexes array
    for(int i = 0; i < *point_arrays_allocated; i++){
        if(strcmp(nazov_target, (*nazvyPrispevkov)[i]) == 0){
            indexes[erased_count] = i;
            erased_count++;
        }
    }
    if(erased_count){
        int lowest = indexes[0];
        int highest = indexes[erased_count - 1] + 1;
        if(highest == *point_arrays_allocated){
            highest = indexes[erased_count -1];
        }
        // Moves records up, skipping the records destined for erase
        for(int i = highest; i < *point_arrays_allocated; i++){
            strcpy((*nazvyPrispevkov)[lowest], (*nazvyPrispevkov)[i]);
            strcpy((*menaAutorov)[lowest], (*menaAutorov)[i]);
            strcpy((*typyPrezentovania)[lowest], (*typyPrezentovania)[i]);
            strcpy((*casyPrezentovania)[lowest], (*casyPrezentovania)[i]);
            strcpy((*datumy)[lowest], (*datumy)[i]);
            lowest++;
        }
        // Frees memory of unused arrays
        for(int i = lowest; i < *point_arrays_allocated; i++){
            free((*nazvyPrispevkov)[i]);
            free((*menaAutorov)[i]);
            free((*typyPrezentovania)[i]);
            free((*casyPrezentovania)[i]);
            free((*datumy)[i]);
        }
        
        // Decrements arrays allocated count by number of erased records
        *point_arrays_allocated -= erased_count;
        // Reallocs memory of 2D arrays, so that there isn't unused memory
        *nazvyPrispevkov = (char **) realloc(*nazvyPrispevkov, *point_arrays_allocated * sizeof(char *));
        *menaAutorov = (char **) realloc(*menaAutorov, *point_arrays_allocated * sizeof(char *));
        *typyPrezentovania = (char **) realloc(*typyPrezentovania, *point_arrays_allocated * sizeof(char *));
        *casyPrezentovania = (char **) realloc(*casyPrezentovania, *point_arrays_allocated * sizeof(char *));
        *datumy = (char **) realloc(*datumy, *point_arrays_allocated * sizeof(char *));

        // In case of all records erased, this is being used by function p to be able to store new data in the arrays
        if(*point_arrays_allocated == 0){
            *pointer_special_alloc = 1;
        } 
        
    }
    printf("Vymazalo sa: %d zaznamov!\n", erased_count);
    // Frees memory for indexes array
    free(indexes);

    return;

}

int main(){

    //! VARIABLES
    // opt - stores a value entered at menu
    // file_read - either 0 or 1, represents if the file has been opened or not
    // arrays_allocated - represents count of arrays that have been allocated for data records
    // special_alloc - this is used in special case, when all records have been erased from arrays with function z, but it's needed to store new records in p function
    char opt = ' ';
    int file_read = 0;
    int arrays_allocated = 0;
    int special_alloc = 0;

    //! POINTERS
    // *point_file_read - points to file_read, is used for modifying it's value and working with it inside functions where needed
    // *point_arrays_allocated - points to arrays_allocated , is used for modifying it's value and working with it inside functions where needed
    // *pointer_special_alloc - points to special_alloc, used in special cases of all records errased by z function, but space is needed for storing new data in p function
    // *fr - points to a file, that was opened, or in case file wasn't opened, points to NULL
    int *point_file_read = &file_read;
    int *point_arrays_allocated = &arrays_allocated;
    int *pointer_special_alloc = &special_alloc;
    FILE *fr = NULL;

    //! POLIA
    // Represent pointers to the 2D arrays allocated with function n and reallocated in other functions
    char **nazvyPrispevkov;
    char **menaAutorov;
    char **typyPrezentovania;
    char **casyPrezentovania;
    char **datumy;

    //? Menu
    printf(">: ");
    while(scanf("%c", &opt) < 1){
        printf("Neplatny vstup!\n");
        while(getchar() != '\n');
    }

    while(1){

        switch (opt){
            case 'v':
                v(point_file_read, point_arrays_allocated, &nazvyPrispevkov, &menaAutorov, &typyPrezentovania, &casyPrezentovania, &datumy,&fr);
                break;
            case 'o':
                o(point_file_read, point_arrays_allocated, &nazvyPrispevkov, &menaAutorov, &typyPrezentovania, &casyPrezentovania, &datumy, &fr);
                break;
            case 'n':
                n(point_file_read, point_arrays_allocated, &nazvyPrispevkov, &menaAutorov, &typyPrezentovania, &casyPrezentovania, &datumy, &fr);
                break;
            case 's':
                s(point_file_read, point_arrays_allocated, &nazvyPrispevkov, &menaAutorov, &typyPrezentovania, &casyPrezentovania, &datumy);
                break;
            case 'h':
                h(point_file_read, point_arrays_allocated, &nazvyPrispevkov, &menaAutorov, &typyPrezentovania, &casyPrezentovania, &datumy);
                break;
            case 'z':
                z(point_file_read, point_arrays_allocated, &nazvyPrispevkov, &menaAutorov, &typyPrezentovania, &casyPrezentovania, &datumy, pointer_special_alloc);
                break;
            case 'p':
                p(point_file_read, point_arrays_allocated, &nazvyPrispevkov, &menaAutorov, &typyPrezentovania, &casyPrezentovania, &datumy, pointer_special_alloc);
                break;
            case 'k':
                if(arrays_allocated){
                    // If any arrays have been allocated for records storage, it frees memory allocated by them
                    for(int i = 0; i < arrays_allocated; i++){
                        free(nazvyPrispevkov[i]);
                        free(menaAutorov[i]);
                        free(typyPrezentovania[i]);
                        free(casyPrezentovania[i]);
                        free(datumy[i]);
                    }
                    free(nazvyPrispevkov);
                    free(menaAutorov);
                    free(typyPrezentovania);
                    free(casyPrezentovania);
                    free(datumy);
                    arrays_allocated = 0;
                }
                if(fr){
                    // If file has been opened, tries to close it, and resets pointer value to NULL
                    if(fclose(fr) == EOF){
                        printf("Nepodarilo sa zatvorit");
                    }
                    fr = NULL;
                }
                printf("See you later, alligator!");
                return;

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
        if(fr){
            fseek(fr, 0, SEEK_SET);
        }
        while(getchar() != '\n');
    }
    return 0;
}