void o(int *point_file_read, int *point_arrays_allocated,char ***nazvyPrispevkov, char ***menaAutorov, char ***typyPrezentovania, char ***casyPrezentovania, char ***datumy, FILE **fr){

    int datum = 0;
    int helper = 0;
    int posHelper = 0;
    int pos_switch_helper = 0;
    int pos_switch_temp = 0;
    scanf("%d", &datum);
    while(getchar() != '\n');
    if(*point_arrays_allocated){

        printf("%d\n", datum);
        int *upIndexes, *udIndexes, *ppIndexes, *pdIndexes;
        int upPos = 0, udPos = 0, ppPos = 0, pdPos = 0;

        upIndexes = (int *) malloc(*point_arrays_allocated * sizeof(int));
        udIndexes = (int *) malloc(*point_arrays_allocated * sizeof(int));
        ppIndexes = (int *) malloc(*point_arrays_allocated * sizeof(int));
        pdIndexes = (int *) malloc(*point_arrays_allocated * sizeof(int));

        for(int i = 0; i < *point_arrays_allocated; i++){
            helper = (int)atoi((*datumy)[i]);
            if(helper == datum){
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
        
        





        free(nazvy);
        free(mena);
        free(typy);
        free(casy);
        free(datumy_v);


    }
    return;
}