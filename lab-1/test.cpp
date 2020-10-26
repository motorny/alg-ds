#include "pch.h"
#include "gtest/gtest.h"
#include "../XORList/XorList.c"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(addTest, add_to_emptyList_returnTRUE) {
	List list;
	init(&list);
	
	ASSERT_TRUE(addElem(&list, "one"));
	ASSERT_EQ(strcmp(list.first->data, "one"), 0);
	ASSERT_EQ((int)list.first->xor_addr, 0);
	ASSERT_EQ((int)list.last->xor_addr, 0);

	clearList(&list);
}

TEST(addTest, add_to_with1ElemList_returnTRUE) {
	List list;
	init(&list);
	Elem *p1, *p2;

	addElem(&list, "one");
	p1 = list.first;
	addElem(&list, "two");
	p2 = XOR(p1->xor_addr, 0);

	ASSERT_EQ(strcmp(p2->data, "two"), 0);
	ASSERT_EQ(list.first->xor_addr, p1->xor_addr);
	ASSERT_EQ(list.last->xor_addr, p2->xor_addr);

	clearList(&list);
}

TEST(addTest, add_to_moreElemList_returnTRUE) {
	List list;
	init(&list);

	addElem(&list, "one");
	addElem(&list, "two");
	addElem(&list, "three");
	addElem(&list, "for");

	ASSERT_TRUE(addElem(&list, "five"));
	ASSERT_EQ(strcmp(list.last->data, "five"), 0);

	clearList(&list);
}

TEST(FindElemByKey, find_in_emptyList) {
	List list;
	init(&list);

	ASSERT_FALSE(FindElemByKey(&list, "one"));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	clearList(&list);
}

List CreateList_1elem(void) {
	List list;
	init(&list);

	// Сохраняем строку в ОП
	int len = strlen("one");  // определяем длину строки
	char* p = (char*)malloc(len + 1); // выделяем память под строку
	// Создаем элемент списка
	Elem* new_elem = (Elem*)malloc(sizeof(Elem));

	strcpy(p, "one"); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль

	new_elem->data = p; // значение элемента (адрес строки)

	// Встраиваем элемент в конец списка
	new_elem->xor_addr = XOR(0, 0);
	list.first = new_elem;
	
	list.last = new_elem;
	return list;
}

TEST(FindElemByKey, find_in_1ElemList) {
	List list = CreateList_1elem();
	//init(&list);
	//ADD();

	//addElem(&list, "one");
	ASSERT_TRUE(FindElemByKey(&list, "one"));
	ASSERT_EQ(FindElemByKey(&list, "one"), list.first);
	ASSERT_EQ(FindElemByKey(&list, "one"), list.last);

	clearList(&list);
}

TEST(FindElemByKey, find_in_1ElemList_noExistElem) {
	List list = CreateList_1elem();
	//init(&list);

	//addElem(&list, "one");
	ASSERT_TRUE(FindElemByKey(&list, "one"));
	ASSERT_EQ(FindElemByKey(&list, "one"), list.first);
	ASSERT_EQ(FindElemByKey(&list, "one"), list.last);

	ASSERT_FALSE(FindElemByKey(&list, "two"));

	clearList(&list);
}

List CreateList_moreElem(void) {
	List list;
	init(&list);

	//1 elem
	// Сохраняем строку в ОП
	int len = strlen("one");  // определяем длину строки
	char* p = (char*)malloc(len + 1); // выделяем память под строку
	// Создаем элемент списка
	Elem* elem1 = (Elem*)malloc(sizeof(Elem));
	strcpy(p, "one"); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль
	elem1->data = p; // значение элемента (адрес строки)
	// Встраиваем элемент в конец списка
	elem1->xor_addr = XOR(0, 0);
	list.first = elem1;
	list.last = elem1;

	//2 elem
	len = strlen("two");
	p = (char*)malloc(len + 1);
	Elem* elem2 = (Elem*)malloc(sizeof(Elem));
	strcpy(p, "two"); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль
	elem2->data = p; // значение элемента (адрес строки)
	// уже есть больше одного элемента
	elem2->xor_addr = XOR(list.last, 0);
	elem1 = XOR(list.last->xor_addr, 0); // адрес предпоследнего элемента
	// обновление xor-адреса последнего элемента списка
	list.last->xor_addr = XOR(elem1, elem2);
	list.last = elem2;

	//3 elem
	len = strlen("three");
	p = (char*)malloc(len + 1);
	Elem* elem3 = (Elem*)malloc(sizeof(Elem));
	strcpy(p, "three"); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль
	elem3->data = p; // значение элемента (адрес строки)
	// уже есть больше одного элемента
	elem3->xor_addr = XOR(list.last, 0);
	elem2 = XOR(list.last->xor_addr, 0); // адрес предпоследнего элемента
	// обновление xor-адреса последнего элемента списка
	list.last->xor_addr = XOR(elem2, elem3);
	list.last = elem3;

	//4 elem
	len = strlen("four");
	p = (char*)malloc(len + 1);
	Elem* elem4 = (Elem*)malloc(sizeof(Elem));
	strcpy(p, "four"); // копирование строки
	p[len] = '\0'; // добавим терминальный ноль
	elem4->data = p; // значение элемента (адрес строки)
	// уже есть больше одного элемента
	elem4->xor_addr = XOR(list.last, 0);
	elem3 = XOR(list.last->xor_addr, 0); // адрес предпоследнего элемента
	// обновление xor-адреса последнего элемента списка
	list.last->xor_addr = XOR(elem3, elem4);
	list.last = elem4;

	return list;

}
TEST(FindElemByKey, find_in_moreElemList) {
	List list = CreateList_moreElem();
	//init(&list);

	//addElem(&list, "one");
	//addElem(&list, "two");
	//addElem(&list, "three");
	//addElem(&list, "four");

	ASSERT_TRUE(FindElemByKey(&list, "one"));
	ASSERT_TRUE(FindElemByKey(&list, "two"));
	ASSERT_TRUE(FindElemByKey(&list, "three"));
	ASSERT_TRUE(FindElemByKey(&list, "four"));
	ASSERT_EQ(FindElemByKey(&list, "one"), list.first);
	ASSERT_EQ(FindElemByKey(&list, "four"), list.last);
	//ASSERT_EQ(FindElemByKey(&list, "three"), list.last);


	clearList(&list);
}

TEST(FindElemByKey, find_in_moreElemList_noExistElem) {
	List list = CreateList_moreElem();
	//init(&list);

	//addElem(&list, "one");
	//addElem(&list, "two");
	//addElem(&list, "three");
	//addElem(&list, "for");

	ASSERT_TRUE(FindElemByKey(&list, "one"));
	ASSERT_TRUE(FindElemByKey(&list, "two"));
	ASSERT_TRUE(FindElemByKey(&list, "three"));
	ASSERT_TRUE(FindElemByKey(&list, "four"));
	ASSERT_EQ(FindElemByKey(&list, "one"), list.first);
	ASSERT_EQ(FindElemByKey(&list, "four"), list.last);

	ASSERT_FALSE(FindElemByKey(&list, "six"));
	ASSERT_FALSE(FindElemByKey(&list, "seven"));

	clearList(&list);
}

TEST(DeleteElemByKey, delete_in_emptyList) {
	List list;
	init(&list);

	ASSERT_FALSE(DeleteElemByKey(&list, "one"));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	clearList(&list);
}

TEST(DeleteElemByKey, delete_in_1ElemList) {
	List list;
	init(&list);

	addElem(&list, "one");
	ASSERT_TRUE(FindElemByKey(&list, "one"));
	ASSERT_EQ((int)list.first->xor_addr, 0);
	ASSERT_EQ((int)list.last->xor_addr, 0);

	ASSERT_TRUE(DeleteElemByKey(&list, "one"));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	clearList(&list);
}

TEST(DeleteElemByKey, delete_in_1ElemList_noExist) {
	List list;
	init(&list);

	addElem(&list, "one");
	ASSERT_TRUE(FindElemByKey(&list, "one"));
	ASSERT_EQ((int)list.first->xor_addr, 0);
	ASSERT_EQ((int)list.last->xor_addr, 0);

	ASSERT_FALSE(DeleteElemByKey(&list, "three"));
	
	clearList(&list);
}

TEST(DeleteElemByKey, delete_in_moreElemList) {
	List list;
	init(&list);

	addElem(&list, "one");
	addElem(&list, "two");
	addElem(&list, "three");
	addElem(&list, "for");

	ASSERT_TRUE(FindElemByKey(&list, "one"));
	ASSERT_TRUE(DeleteElemByKey(&list, "one"));
	ASSERT_FALSE(FindElemByKey(&list, "one"));

	ASSERT_TRUE(FindElemByKey(&list, "three"));
	ASSERT_TRUE(DeleteElemByKey(&list, "three"));
	ASSERT_EQ((int)FindElemByKey(&list, "three"), NULL);

	ASSERT_TRUE(FindElemByKey(&list, "two"));
	ASSERT_TRUE(DeleteElemByKey(&list, "two"));
	ASSERT_EQ((int)FindElemByKey(&list, "two"), NULL);
	
	clearList(&list);
}

TEST(DeleteElemByKey, delete_in_moreElemList_noExist) {
	List list;
	init(&list);

	addElem(&list, "one");
	addElem(&list, "two");
	addElem(&list, "three");
	addElem(&list, "for");

	ASSERT_TRUE(FindElemByKey(&list, "three"));
	ASSERT_TRUE(DeleteElemByKey(&list, "three"));
	ASSERT_EQ((int)FindElemByKey(&list, "three"), NULL);

	ASSERT_FALSE(FindElemByKey(&list, "hello"));
	ASSERT_FALSE(DeleteElemByKey(&list, "hello"));
	ASSERT_EQ((int)FindElemByKey(&list, "hello"), NULL);

	clearList(&list);
}

TEST(DeleteElemByAddress, delete_in_emptyList) {
	List list;
	init(&list);

	ASSERT_FALSE(DeleteElemByAddress(&list, 0));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	clearList(&list);
}

TEST(DeleteElemByAddress, delete_in_1ElemList) {
	List list;
	init(&list);

	addElem(&list, "one");
	Elem* p = FindElemByKey(&list, "one");
	ASSERT_TRUE(DeleteElemByAddress(&list, p));
	ASSERT_EQ((int)list.first, NULL);
	ASSERT_EQ((int)list.last, NULL);

	ASSERT_FALSE(FindElemByKey(&list, "one"));

	clearList(&list);
}

TEST(DeleteElemByAddress, delete_in_1ElemList_noExist) {
	List list;
	init(&list);
	Elem* p;

	addElem(&list, "one");
	ASSERT_TRUE(FindElemByKey(&list, "one"));
	p = FindElemByKey(&list, "two");
	ASSERT_EQ((int)list.first->xor_addr, 0);
	ASSERT_EQ((int)list.last->xor_addr, 0);

	ASSERT_FALSE(DeleteElemByAddress(&list, p));

	clearList(&list);
}

TEST(DeleteElemByAddress, delete_in_moreElemList) {
	List list;
	init(&list);

	addElem(&list, "one");
	addElem(&list, "two");
	addElem(&list, "three");
	addElem(&list, "for");

	ASSERT_TRUE(FindElemByKey(&list, "one"));
	Elem* p1 = FindElemByKey(&list, "one");
	ASSERT_TRUE(DeleteElemByAddress(&list, p1));
	ASSERT_FALSE(FindElemByKey(&list, "one"));

	ASSERT_TRUE(FindElemByKey(&list, "three"));
	p1 = FindElemByKey(&list, "three");
	ASSERT_TRUE(DeleteElemByAddress(&list, p1));
	ASSERT_FALSE(FindElemByKey(&list, "three"));

	ASSERT_TRUE(FindElemByKey(&list, "two"));
	p1 = FindElemByKey(&list, "two");
	ASSERT_TRUE(DeleteElemByAddress(&list, p1));
	ASSERT_FALSE(FindElemByKey(&list, "two"));

	clearList(&list);
}

TEST(DeleteElemByAddress, delete_in_moreElemList_noExist) {
	List list;
	init(&list);

	addElem(&list, "one");
	addElem(&list, "two");
	addElem(&list, "three");
	addElem(&list, "for");

	ASSERT_TRUE(FindElemByKey(&list, "three"));
	ASSERT_TRUE(DeleteElemByKey(&list, "three"));
	ASSERT_FALSE(FindElemByKey(&list, "three"));

	ASSERT_FALSE(FindElemByKey(&list, "hello"));
	Elem* p1 = FindElemByKey(&list, "hello");
	ASSERT_FALSE(DeleteElemByAddress(&list, p1));
	
	clearList(&list);
}

TEST(Next, Next_in_emptyList) {
	List list;
	init(&list);

	ASSERT_FALSE(Next(&list, (Elem*)1));

	clearList(&list);
}

TEST(Next, Next_in_1ElemList) {
	List list;
	init(&list);

	addElem(&list, "one");
	ASSERT_FALSE(Next(&list, FindElemByKey(&list, "one")));

	clearList(&list);
}

TEST(Next, Next_lastElem_in_moreElemeList) {
	List list;
	init(&list);

	addElem(&list, "one");
	addElem(&list, "two");
	addElem(&list, "three");
	ASSERT_FALSE(Next(&list, FindElemByKey(&list, "three")));
	
	clearList(&list);
}

TEST(Next, Next_in_moreElemeList) {
	List list;
	init(&list);

	addElem(&list, "one");
	addElem(&list, "two");
	addElem(&list, "three");

	ASSERT_TRUE(Next(&list, FindElemByKey(&list, "one")));
	ASSERT_TRUE(Next(&list, FindElemByKey(&list, "two")));

	clearList(&list);
}