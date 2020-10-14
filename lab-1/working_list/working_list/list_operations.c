#include "working_list.h"

void GetInfo(tnode* person, char* surname, char* name, char* scndname) { // Copies read data into node
    strcpy(person->surname, surname);
    strcpy(person->name, name);
    strcpy(person->scndname, scndname);
}


tnode* ConvertInputToNode(char* tmp) { //Converts request from <"surname" "name" "secondname"> to node
    if (tmp == NULL) {                 //actually useless as tmp's content from fgets that fails if tmp is 0
        printf("empty buffer; ");      //works only for inputs <"..." "..." "..."> w/ spaces in between words 
        return NULL;
    }     
    int space_counter, ln;
    int i, j, k;                                         
    space_counter = ln = i = j = k = 0;                             
    char surname[MAX_LE], name[MAX_LE], scndname[MAX_LE];
    char q;
    while ((q = tmp[ln]) != '\0') {     //function reads input twice , must be a way to make it O(n), dk how
        if (tmp[ln] == ' ') {           //first time for inspecting if input's format correct
            space_counter++;            //second time for function's very intended purpose
        }
        ln++;
    }
    if (space_counter != 2) {       // for any version of correct type of input there're 2 spaces
        printf("improper format of input");
        return NULL;
    }
    while ((q = tmp[i]) != ' ') {
        if (i >= MAX_LE) {
            printf("overflow; ");
            return NULL;
        }

        surname[i] = q;
        i++;
    }
    surname[i] = '\0';
    i++;                        // skips space between words
    while ((q = tmp[i]) != ' ') {       // i++; used instead of tmp[i++] for readability 
        if (k >= MAX_LE) {
            printf("overflow ;");
            return NULL;
        }
        name[k] = q;                    
        i++;                                
        k++;
    }
    name[k] = '\0';
    i++;
    while ((q = tmp[i]) != '\0') {  
        if (j >= MAX_LE) {                
            printf("overflow  ;");             
            return NULL;
        }
        scndname[j] = q;
        i++;
        j++;
    }

    if (scndname[j-1] == '\n' && j>0) {
        scndname[j - 1] = '\0';         //puts /0 instead of /n for Compare() to work properly 
    }                                   //needed for reading from file
    else {
        scndname[j] = '\0';                 //this branch goes if string has no \n
    }
    
    tnode* result = (tnode*)malloc(sizeof(tnode));

    if (result == NULL) {
        printf("not enough memory ");
        return NULL;
    }

    GetInfo(result, surname, name, scndname);

    return result;
}

tnode* GetPtrLast(tnode* top) { // gives pointer to last element of list
    if (top == NULL) {             // needed for correct data reading from file
        return NULL;
    }
    while (top->next != NULL) {
        top = top->next;
    }
    return top;
}

int Compare(tnode* person_l, tnode* info) { // returns NO_MATCH(= 1) if person_l shouldn't be printed
    int lenth;                              // returs MATCH(= 0) if person_l should be printed
    if (person_l == NULL) {
        printf("no such element found in list");
        return EMPTY_ELEMENT;
    }
    if (info == NULL) {
        printf("empty input entered");
        return EMPTY_ELEMENT;
    }
    if (info->surname != "") {          //compares surname if one has been entered 
        lenth = strlen(info->surname);
        for (int i = 0; i < lenth; i++) {
            if (person_l->surname[i] != info->surname[i]) {
                return NO_MATCH;
            }
        }
    }

    if (info->name != "") {             //same for name and second name
        lenth = strlen(info->name);
        for (int i = 0; i < lenth; i++) {
            if (person_l->name[i] != info->name[i]) {
                return NO_MATCH;
            }
        }
    }

    if (info->scndname != "") {
        lenth = strlen(info->scndname);
        for (int i = 0; i < lenth; i++) {
            if (person_l->scndname[i] != info->scndname[i]) {
                return NO_MATCH;
            }
        }
    }

    return MATCH;
}


int AddToList(tnode** top, tnode* person) {  // adds element to end of list 
    if (person == NULL) {
        printf("tried to add empty element;");
        return EMPTY_ELEMENT;
    }
    //if ((*top) == NULL) {   // if list's empty and person is first
        person->next = (*top);
        (*top) = person;
        
        /*
    }
    else {
        tnode* last = GetPtrLast((*top));
        person->next = NULL;
        last->next = person;
    }*/
}

int PrintFilteredList(tnode** top, tnode* input) { // applies entered filters "info" to list and prints it
    int match_counter = 0;
    tnode* tmp = (*top);
    while (tmp != NULL) {                    // does nothing if initial list is empty, as intended
        if (Compare(tmp, input) == MATCH) {
            printf("%s\n", tmp->surname);
            match_counter++;
        }
        tmp = tmp->next;
    }
    return match_counter;
}

void PrintInitialList(tnode** top) { // prints the list read from the file
    tnode* tmp = (*top);            // prints only surnames
    if ((*top) == NULL) {
        printf("empty list");
        return;
    }
    while (tmp != NULL) {
        printf("%s\n", tmp->surname);
        tmp = tmp->next;
    }
    printf("list successfully printed\n");
}


void FreeList(tnode** top) {        // kills the list after the programm is done
    tnode* tmp = (*top);
    if (tmp == NULL) return;
    while ((*top) != NULL) {
        tmp = (*top);
        (*top) = (*top)->next;
        free(tmp);
    }
    free(*top);
}

