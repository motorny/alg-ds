#include "DFS.h"

/// <summary>
/// ������ � �������� ����� �� ������
/// </summary>
/// <param name="f">��������� �� �������� �����</param>
/// <returns> � ������ ������ NULL, ����� ������</returns>
char *ReadPotok(FILE *f) {
    char *str;

    if(f == NULL)
        return NULL;

    str = (char *)malloc(sizeof(char) * MAX_STR);
    if ( str == NULL )
        return NULL;

    str = fgets(str, MAX_STR, f);

    if ( ferror(f) || !feof(f) ) {
        free(str);
        return NULL;
    }

    return str;
}

/// <summary>
/// ������������ ������ � ������� ����������
/// </summary>
/// <param name="str">������ ����������</param>
/// <param name="mat">��������� �� ������� ����������</param>
/// <returns>� ������ ������ 1, ����� 0</returns>
int ConvertsList2Matrix(char *str, graph *mat) {
    int size, i, j, k;
    if ( str == NULL || mat == NULL )
        return ERROR;
    // ������� ���������� �����
    for ( i = 0, size = 0; str[i] != EOF; i++ ) {
        if ( str[i] == '\n' )
            size++;
    }
    
    if ( size <= 0 )
        return ERROR;

    // ������� ������� �������
    mat->matrix = (int **)malloc(sizeof(int *) * size);
    if ( mat->matrix == NULL )
        return ERROR;

    for ( i = 0; i < size; i++ ) {
        mat->matrix[i] = (int *)malloc(sizeof(int *) * size);
        if ( mat->matrix[i] == NULL ) 
            break;
        for ( j = 0; j < size; j++ )
            mat->matrix[i][j] = 0;
    }

    if ( i < size ) {
        while ( i >= 0 ) {
            free(mat->matrix[i]);
            i--;
        }
        free(mat->matrix);
        return ERROR;
    }

    mat->size = size;

    k = 0;
    i = -1;
    while ( str[k] != '\0' ) {

        if ( isspace(str[k]) ) {
            if ( str[k] == '\n' ) i = -1;
            k++;
            continue;
        }

        if ( '1' <= str[k] && str[k] <= '9' && atoi(str + k) <= size) {

            if ( i == -1 ) {
                i = atoi(str + k) - 1;
            }
            else {
                j = atoi(str + k) - 1;
                mat->matrix[i][j]++;
            }

            while ( '0' <= str[k] && str[k] <= '9' ) {
                k++;
            }
            continue;

        }
        else {
            DestroyMatrix(mat);
            return ERROR;
        }
    }

    return SUCCESS;
}

/// <summary>
/// ������� � ������� ���������� ������� ����������
/// </summary>
/// <param name="mat">��������� �� ������� ����������</param>
void DestroyMatrix(graph *mat) {
    int i;
    if ( mat != NULL && mat->matrix != NULL ) {
        for ( i = 0; i < mat->size; i++ )
            free(mat->matrix[i]);
        free(mat->matrix);
    }
}

/// <summary>
/// ����� ������ ����������
/// </summary>
/// <param name="mat">��������� �� ������� ����������</param>
void PrintAdjacentList(graph *mat) {
    int i, j;
    if ( mat != NULL ) {
        for ( i = 0; i < mat->size; i++ ) {
            printf("%i", i);
            for ( j = 0; j < mat->size; j++ )
                if ( mat->matrix[i][j] )
                    printf("->%i", j);
            printf("\n");
        }
    }
}

/// <summary>
/// ����� ������� ����������
/// </summary>
/// <param name="mat">��������� �� ������� ����������</param>
void PrintGraphMatrix(graph *mat) {
    int i, j;
    if ( mat != NULL ) {
        for ( i = 0; i < mat->size; i++ ) {
            for ( j = 0; j < mat->size; j++ )
                printf("%i", mat->matrix[j][i]);
            printf("\n");
        }
    }
}