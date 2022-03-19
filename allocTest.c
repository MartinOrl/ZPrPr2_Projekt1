#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void allocate_mem(int*** arr, int n, int m)
{
  *arr = (char**)malloc(n*sizeof(char*));
  for(int i=0; i<n; i++){
    (*arr)[i] = (char*)malloc(m*sizeof(char));
  }

} 


void deallocate_mem(int*** arr, int n){
    for (int i = 0; i < n; i++)
        free((*arr)[i]);
    free(*arr); 
}

int main(){

    int width = 5;
    int height = 5;
    char **arr;
    allocate_mem(&arr, width, height);
    printf("Arrays allocated!");

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            arr[i][j] = 'a';
        }
    }

    printf("%s\n", arr[0]);
    printf("%s\n", arr[0]);
    printf("%s\n", arr[0]);
    printf("%s\n", arr[0]);
    deallocate_mem(&arr, width);
    return 0;
}