#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lexicographic_sort(const char* a, const char* b) {
    return strcmp(a, b);
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return strcmp(a, b)*(-1);
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    int arrA[256] = {0};
    int arrB[256] = {0};
    int countA = 0;
    int countB = 0;
    int length = strlen(a);

    for (int i = 0; i < length; i++) {
        int j = a[i];
        if (arrA[j] == 0) {
            countA++;
            arrA[j]++;
        }
    }
    length = strlen(b);
    for (int i= 0; i < length; i++) {
        int j = b[i];
        if (arrB[j] == 0) {
            countB++;
            arrB[j]++;
        }
    }

    if (countA > countB) {
        return 1;
    }
    if (countA < countB) {
        return -1;
    }
    return strcmp(a, b);
}

int sort_by_length(const char* a, const char* b) {
    if (strlen(a) > strlen(b)) {
        return 1;
    }
    if (strlen(a) < strlen(b)) {
        return -1;
    }
    return strcmp(a, b);
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
    // for(int i = 0; i < len; i++)
    //     printf("%d%s\n",i, arr[i]);
    // printf("\n");
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            *(arr + j) = realloc(*(arr + j), 50 * sizeof(char));
            *(arr + j+1) = realloc(*(arr + j+1), 50 * sizeof(char));
            if (cmp_func(arr[j], arr[j+1]) > 0) {
                int length = strlen(arr[j]);
                char realTemp[length+1];
                length = strlen(arr[j+1]);
                char j1[length+1];
                strcpy(realTemp, arr[j]);
                strcpy(j1, arr[j+1]);
                strcpy(arr[j], arr[j+1]);
                strcpy(arr[j+1], realTemp);
                // printf("temp:%s ,j1:%s\n", realTemp, j1);
            }
        }
    }
}


int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}