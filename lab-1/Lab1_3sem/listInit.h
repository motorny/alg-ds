#pragma once
#define isize 20
#define STRSAME 0
#define STR1B 1
#define STR2B -1

typedef struct myList{
  struct myList* next;
  char surname[isize];
  char name[isize];
  char patron[isize];
}myList;

typedef struct {
	char surname[20];
	char name[20];
	char patron[20];
}SNP;

enum SAME_E {
	SAME,
	NSAME
};

enum SNP_E {
	BETW,
	SURNAME,
	NAME,
	PATRON
};

myList* InitList(char* surname, char* name, char* patron);
void DeleteList(myList* start);
myList* AddMan(myList* next, myList* pMan, char* surname, char* name, char* patron);
void EnterSNP(myList* man, char* surname, char* name, char* patron);
myList* Add2List(myList** start, SNP snp);
enum SAME_E FindPosForMan(myList** start, SNP snp, myList** pMan, myList** nMan, enum SNP_E snp_pos);
