#include "lab3.h"
QUEUE T;
void Pop(QUEUE* q, int iEl)
{
    LIST* tmp;
    tmp = (LIST*)malloc(sizeof(LIST));
  //  tmp = new LIST;
    tmp->Next = NULL;
    tmp->A = iEl;
    if (q->Tail != NULL)
        q->Tail->Next = tmp;
    else
        q->Top = tmp;
    q->Tail = tmp;
}
int Push(QUEUE* q)
{
    int iEl;
    if (q->Top == NULL) 
        return 0;
    LIST* tmp;
    tmp = q->Top;
    iEl = tmp->A;
    q->Top = tmp->Next;
  //  delete tmp;
    if (q->Top == NULL) 
        q->Tail = NULL;
    return iEl;
}
/*
int Push(QUEUE* S, TOK NewDate) {
    LIST* NewElement;
    (NewElement = (LIST*)malloc(sizeof(LIST)));
    if (NewElement == NULL)
        return 0;

    NewElement->T = NewDate;
    S->Tail->Next = NewElement;
    S->Tail = NewElement;
    NewElement->Next = NULL;
  //  NewElement->Next = S->Top;
 //   S->Top = NewElement;
    return 1;
}
int Pop(QUEUE* S, TOK* OldData) {
    LIST* OldElement;

    if (S->Top == NULL)
        return 0;


    OldElement = S->Top;
    S->Top = S->Top->Next;

    if (OldElement != NULL)
        *OldData = OldElement->T;

    free(OldElement);

    return 1;
}
int ClearList(LIST** L) {

    if (*L == NULL)
        return 0;
    while (*L != NULL)
    {
        LIST* ptr = 0;
        ptr = *L;
        *L = (*L)->Next;
        free(ptr);
    }
    return 1;
}
void ClearStack(QUEUE* S) {
    ClearList(&S->Top);
}
*/
int IsDigit(char ch) {
    switch (ch) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return 1;
        break;
    default:
        return 0;
        break;
    }
}
int Digit(char ch, int b) {
    int a;
    switch (ch) {
    case '0':
        a = 0;
        break;
    case '1':
        a = 1;
        break;
    case '2':
        a = 2;
        break;
    case '3':
        a = 3;
        break;
    case '4':
        a = 4;
        break;
    case '5':
        a = 5;
        break;
    case '6':
        a = 6;
        break;
    case '7':
        a = 7;
        break;
    case '8':
        a = 8;
        break;
    case '9':
        a = 9;
        break;
    default:
        a = 0;
        break;
    }
        if (b == 0)
            return a;
        return b * 10 + a;

}
char* ReadLine(FILE* file) {
    char* line = NULL;
    char ch;
    int t = 1, i = 0, len = 1;
    line = (char*)malloc(len);
    if (line == NULL) {
        //    printf("ERROR: memory\n"); 
    }
    while (t) {
        ch = (char)fgetc(file);

        if (ch == '\n' || ch == EOF) {
            line = (char*)realloc(line, (i + 1) * sizeof(char));
            if (i == 0 && ch == EOF)
                line[i++] = EOF;
            else
                line[i++] = '\0';
            t = 0;
        }

        line = (char*)realloc(line, (i + 1) * sizeof(char));
        line[i++] = ch;
    }
    if (t == 0)
        if (line[i] == EOF)
            line[0] = EOF;
        else
            line[i] = '\0';

    return line;
}

int Comp(int* M, int* R, int* C, int k, int n, int x) {
    int  l1, a, *A, i = 0;
    A = (int*)malloc(sizeof(int) * k);
    for (a = 0; a < k; a++) {
        for (l1 = 0; l1 < n; l1++)
            if (R[l1] == C[a]) {
                break;
            }
        A[a] = l1;
    }
 //  for (l2 = 0; l2 < n; l2++)
 //       if (R[l2] == C[1])
  //          break;
    if (n == A[0] && n == A[1]) {
        R[x++] = C[0];
        R[x++] = C[1];
        *(M + (x - 2) * n + x - 1) = 1;
        *(M + n * (x - 1) + x - 2) = 1;
    }
    else if (n == A[0] || n == A[1]) {
        if (n == A[0]) {
            R[x++] = C[0];
            *(M + (x - 1) * n + A[1]) = 1;
            *(M + (A[1]) * n + (x - 1)) = 1;
        }
        if (n == A[1]) {
            R[x++] = C[1];
            *(M + (x - 1) * n + A[0]) = 1;
            *(M + (A[0]) * n + (x - 1)) = 1;
        }
    }
    else {
        *(M + A[1] * n + A[0]) = 1;
        *(M + (A[0]) * n + A[1]) = 1;
    }
    return x;
}

int Comp1(int* Res, int* R, int* C, int k, int n, int x, QUEUE *Q) {
    int  l1, a, * A, i = 0, j;
//  TOK *B;
    int B;
    A = (int*)malloc(sizeof(int) * k);
//    B = (TOK*)malloc(sizeof(TOK));
    for (a = 0; a < k; a++) {
        for (l1 = 0; l1 < n; l1++)
            if (Res[l1] == R[C[a]]) {
                break;
            }
        A[a] = l1;
    }
    for (i = 0; i < k; i++)
        if (A[i] == n) {
            Res[x++] = R[C[i]];
            //
            
            for (j = 0; j < n; j++)
                if (Res[x-1] == R[j]) {
                    B = j;
                    Pop(Q, B);
                    j = n;
 //                   B->A = j;
 //                   Pop(Q, B);
                }
               
            //
        }
    /*
    for (i = k; i >= 0; i++) {
        for (j = 0; j < n; j++)
            if (Res[x - k] == R[j]) {
                Pop(Q, j);
            }
    }
    */
    return x;
}


int main(void) {
    FILE* file = NULL;
    char* line = " ";
    int* M, * R, * Res, * C, i = 0, len, a = 0, b, k = 0, n = 0, s = 0, l1, l2, x = 0, j, t = 0, num = 0, h;
    int N;
//    TOK *N;
    file = stdin;
//    N = (TOK*)malloc(sizeof(TOK));
    M = (int*)malloc(sizeof(int) * 3);
    R = (int*)malloc(sizeof(int) * 3);
    C = (int*)malloc(sizeof(int) * 3);
    Res = (int*)malloc(sizeof(int) * 3);
    
    if (file) {
        while (!feof(file)) {
            line = ReadLine(file);
            if (k == 0) {
                for (len = 0; line[len] != 0; len++);

                for (i = 0; i <= len; i++) {
                    if (IsDigit(line[i])) {
                        while (line[i] != ' ') {
                            n = Digit(line[i], n);
                            i++;
                            if (i == len)
                                break;
                        }
                        i--;
                    }
                }

                M = (int*)malloc(sizeof(int) * n * n);
                R = (int*)malloc(sizeof(int) * n);
                C = (int*)malloc(sizeof(int) * n);
                Res = (int*)malloc(sizeof(int) * n);
                for (i = 0; i < n; i++) 
                    for (j = 0; j < n; j++)
                         *(M + i * n + j) = 0;
                k++;
            }
            else {
                for (len = 0; line[len] != 0; len++);
                for (i = 0; i < len; i++) {
                    if (IsDigit(line[i])) {
                        while (line[i] != ' ') {
                            a = Digit(line[i], a);
                            i++;
                            if (i == len)
                                break;
                        }
                        b = a;
                        C[s] = b;
                        s++;
                        i--;
                        a = 0;
                    }

                }
                //           }
               
                x = Comp(M, R, C, 2, n, x);
                s = 0;
            }//
                //    место сканиования строк
              }             
                 s = 0;
                 Res[t++] = R[0];
                 for (i = 0; i < n; i++) {//не i а число из очереди
                     for (j = 0; j < n; j++)
                         if (*(M + num * n + j) == 1)
                             C[s++] = j;
                     for (l1 = 0; l1 < s; l1++) {
                         if(s >= 2)
                             for (l2 = 0; l2 + 1 < s; l2++) {
                                 if (R[C[l2]] > R[C[l2 + 1]]) {
                                     b = C[l2];
                                     C[l2] = C[l2 + 1];
                                     C[l2 + 1] = b;
                                 }
                             }
                 }
                     for (h = 0; h < s; h++)
                         printf("%i ", R[C[h]]);
                     printf("\n");
                     //Очередь
                     t = Comp1(Res, R, C, s, x, t, &T);
                     N = Push(&T);
                     num = N;
                     s = 0;
                     free(C);
                     C = (int*)malloc(sizeof(int) * n);
 //                    Push(&T, *N);
 //                    num = N->A;
 //                    printf("\n");
                 }
                 for (i = 0; i < t; i++)
                     printf("%i ", Res[i]);
                 printf("\n");
                 for (i = 0; i < n; i++) {
                     for (j = 0; j < n; j++)
                         printf("%i ", *(M + i * n + j));
                     printf("\n");
                 }
    }
    return 0;
}
