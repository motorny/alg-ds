//#ifndef __POLYNOMIAL_H__
//#define __POLYNOMIAL_H__
//
//#include <stdlib.h>
//#include <stdbool.h>
//
//typedef struct poly_t poly;
//poly  *polyCreate(size_t degree);
//void   polyDestroy(poly *p);
//void   polySetDegree(poly *p, size_t i, int a);
//int    polyGetCoeff(poly *p, size_t i);
//double polyEvaluale(poly *p, double x);
//poly   *polyAdd(poly *p1, poly *p2);
//poly   *polySub(poly *p1, poly *p2);
//poly   *polyMul(poly *p1, poly *p2);
//poly   *polyMulInt(poly *p, int c);
//poly*  polyFrom(int n,...);
//poly*  polyParse(const char *str);
//void polyFormat(poly *poly,char * str);
//poly*  polyRead(const char *str);
//void   polyWrite(const char *filename, poly *poly);
//char*  polyElement(poly* poly,int i);
//#endif

#ifndef __LinkedListsSort_H__
#define __LinkedListsSort_H__
typedef struct LIST LIST_T;

//Not public functions
//void Split(LIST_T* head, LIST_T** first, LIST_T** second);
//LIST_T * Merge(LIST_T *A, LIST_T *B);

void Sort(LIST_T **head);

#endif 
