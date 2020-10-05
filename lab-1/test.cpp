extern "C"{
 #include "ListBirthDay.h"
 #include <time.h>
 #include <string.h>
}

// int AddDayToList(ListDays **q, time_t time, char *fio);
TEST(AddDayToList, NULLq_returnTrue){
    ListDays *list = NULL;

    ASSERT_EQ(AddDayToList(&list, (time_t)989193600 ,"Ширяев Виктор Андреевич"), SUCCESS);
    ASSERT_EQ(list->time, (time_t)989193600);

    DestroyList(&list);
}


TEST(AddDayToList, qOf1ElementAddToTheTop_returnTRUE){
    ListDays *list = NULL;
    AddDayToList(&list, (time_t)989193600 ,"Ширяев Виктор Андреевич");

    ASSERT_EQ(AddDayToList(&list, (time_t)83635200 ,"Леонтьев Алексей Александрович"), SUCCESS);
    ASSERT_EQ(list->time, (time_t)83635200);
    ASSERT_EQ(list->next->time, (time_t)989193600);

    DestroyList(&list);
}

TEST(AddDayToList, qOf1ElementAddToTheEnd_returnTRUE){
    ListDays *list = NULL;
    AddDayToList(&list, (time_t)989193600 ,"Ширяев Виктор Андреевич");

    ASSERT_EQ(AddDayToList(&list, (time_t)1349136000 ,"Николаева Маргарита Кирилловна"), SUCCESS);
    ASSERT_EQ(list->time, (time_t)989193600);
    ASSERT_EQ(list->next->time, (time_t)1349136000);

    DestroyList(&list);
}


TEST(AddDayToList, qOf2ElementAddToTheTop_returnTRUE){
    ListDays *list = NULL;
    AddDayToList(&list, (time_t)989193600 ,"Ширяев Виктор Андреевич");
    AddDayToList(&list, (time_t)1349136000 ,"Николаева Маргарита Кирилловна");

    ASSERT_EQ(AddDayToList(&list, (time_t)83635200 ,"Леонтьев Алексей Александрович"), SUCCESS);
    ASSERT_EQ(list->time, (time_t)83635200);
    ASSERT_EQ(list->next->time, (time_t)989193600);
    ASSERT_EQ(list->next->next->time, (time_t)1349136000);

    DestroyList(&list);  
}

TEST(AddDayToList, qOf2ElementAddToTheMiddle_returnTRUE){
    ListDays *list = NULL;
    AddDayToList(&list, (time_t)1349136000 ,"Николаева Маргарита Кирилловна");
    AddDayToList(&list, (time_t)965088000 ,"Спиридонов Лев Ярославович");

    ASSERT_EQ(AddDayToList(&list, (time_t)989193600 ,"Ширяев Виктор Андреевич"), SUCCESS);
    ASSERT_EQ(list->time, (time_t)965088000);
    ASSERT_EQ(list->next->time, (time_t)989193600);
    ASSERT_EQ(list->next->next->time, (time_t)1349136000);

    DestroyList(&list); 
}

TEST(AddDayToList, qOf2ElementAddToTheEnd_returnTRUE){
    ListDays *list = NULL;
    AddDayToList(&list, (time_t)989193600 ,"Ширяев Виктор Андреевич");
    AddDayToList(&list, (time_t)965088000 ,"Спиридонов Лев Ярославович");

    ASSERT_EQ(AddDayToList(&list, (time_t)1349136000 ,"Николаева Маргарита Кирилловна"), SUCCESS);
    ASSERT_EQ(list->time, (time_t)965088000);
    ASSERT_EQ(list->next->time, (time_t)989193600);
    ASSERT_EQ(list->next->next->time, (time_t)1349136000);

    DestroyList(&list);    
}


TEST(AddDayToList, NULLfio_returnERROR){
    ListDays *list = NULL;

    ASSERT_EQ(AddDayToList(&list, (time_t)1349136000 , NULL), ERROR);

    DestroyList(&list);
}


TEST(AddDayToList, ERRORtime_returnERROR){
    ListDays *list = NULL;

    ASSERT_EQ(AddDayToList(&list, (time_t)(-1) , "Николаева Маргарита Кирилловна"), ERROR);

    DestroyList(&list);
}

// ListDays *FindDay(time_t time, ListDays *q);
TEST(FindDay, ERRORtime_returnNULL){
    ListDays *list = NULL;
    AddDayToList(&list, (time_t)989193600 ,"Ширяев Виктор Андреевич");
    AddDayToList(&list, (time_t)965088000 ,"Спиридонов Лев Ярославович");
    
    ASSERT_EQ( FindDay((time_t)(-1), list), NULL);

    DestroyList(&list);    
}

TEST(FindDay, NULLq_returnNULL){
    ListDays *list = NULL;
    
    ASSERT_EQ( FindDay((time_t)989234680, NULL), NULL);

    DestroyList(&list); 
}

TEST(FindDay, listOf2ElementExistingDate_returnPointer){
    ListDays *list = NULL;
    AddDayToList(&list, (time_t)989193600 ,"Ширяев Виктор Андреевич");
    AddDayToList(&list, (time_t)965088000 ,"Спиридонов Лев Ярославович");

    ListFIO *lfio = FindDay((time_t)965088000, list);
    ASSERT_TRUE( lfio != NULL);

    DestroyList(&list); 
}

TEST(FindDay, listOf2ElementNonExistingDate_returnNULL){
    ListDays *list = NULL;
    AddDayToList(&list, (time_t)989193600 ,"Ширяев Виктор Андреевич");
    AddDayToList(&list, (time_t)965088000 ,"Спиридонов Лев Ярославович");
    
    ASSERT_EQ( FindDay((time_t)989234680, list), NULL);

    DestroyList(&list); 
}