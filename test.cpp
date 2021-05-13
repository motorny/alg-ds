#include "pch.h"

#include "hash_table.h"

TEST(InitTable, InitTable_ReturnValidPtr) {
	hash_table_t* table = InitTable(2);

	EXPECT_NE(table, nullptr);
	EXPECT_NE(table->body, nullptr);
	EXPECT_EQ(table->size, 2);

	free(table->body);
	free(table);
}

TEST(FindElem, ElemIsInList_ReturnValidPtr) {
	const char* str = "ab\0";
	node_t* elem;
	hash_table_t* table = (hash_table_t*)malloc(sizeof(hash_table_t));
	table->body = (node_t**)malloc(3 * sizeof(node_t*));
	table->size = 3;

	for (int i = 0; i < 3; i++) {
		table->body[i] = (node_t*)malloc(sizeof(node_t));
		table->body[i]->data = (char*)malloc(2 * sizeof(char));
		table->body[i]->next = NULL;
	}
	strcpy(table->body[0]->data, "c\0");
	strcpy(table->body[1]->data, "a\0");
	strcpy(table->body[2]->data, "b\0");

	table->body[0]->next = (node_t*)malloc(sizeof(node_t));
	table->body[0]->next->data = (char*)malloc(3 * sizeof(char));
	strcpy(table->body[0]->next->data, "ab\0");
	table->body[0]->next->next = NULL;


	elem = FindElem(table, str);
	EXPECT_NE(elem, nullptr);
	EXPECT_EQ(elem, table->body[0]->next);


	free(table->body[0]->next->data);
	free(table->body[0]->next);
	for (int i = 0; i < 3; i++) {
		free(table->body[i]->data);
		free(table->body[i]);
	}
	free(table->body);
	free(table);
}

TEST(InsertElem, InsertInFreeNode_ReturnSuccess) {
	const char* str = "b\0";
	hash_table_t* table = (hash_table_t*)malloc(sizeof(hash_table_t));
	table->body = (node_t**)malloc(3 * sizeof(node_t*));
	table->size = 3;

	for (int i = 0; i < 2; i++) {
		table->body[i] = (node_t*)malloc(sizeof(node_t));
		table->body[i]->data = (char*)malloc(2 * sizeof(char));
		table->body[i]->next = NULL;
	}
	strcpy(table->body[0]->data, "c\0");
	strcpy(table->body[1]->data, "a\0");

	table->body[0]->next = (node_t*)malloc(sizeof(node_t));
	table->body[0]->next->data = (char*)malloc(3 * sizeof(char));
	strcpy(table->body[0]->next->data, "ab\0");
	table->body[0]->next->next = NULL;
	table->body[2] = NULL;


	EXPECT_EQ(InsertElem(table, str, 2), T_SUCCESS);
	EXPECT_EQ(strcmp(table->body[2]->data, str), 0);


	free(table->body[0]->next->data);
	free(table->body[0]->next);
	for (int i = 0; i < 3; i++) {
		free(table->body[i]->data);
		free(table->body[i]);
	}
	free(table->body);
	free(table);
}


TEST(InsertElem, InsertInFullNode_ReturnSuccess) {
	const char* str = "ac\0";
	hash_table_t* table = (hash_table_t*)malloc(sizeof(hash_table_t));
	table->body = (node_t**)malloc(3 * sizeof(node_t*));
	table->size = 3;

	for (int i = 0; i < 3; i++) {
		table->body[i] = (node_t*)malloc(sizeof(node_t));
		table->body[i]->data = (char*)malloc(2 * sizeof(char));
		table->body[i]->next = NULL;
	}
	strcpy(table->body[0]->data, "c\0");
	strcpy(table->body[1]->data, "a\0");
	strcpy(table->body[2]->data, "b\0");

	table->body[0]->next = (node_t*)malloc(sizeof(node_t));
	table->body[0]->next->data = (char*)malloc(3 * sizeof(char));
	strcpy(table->body[0]->next->data, "ab\0");
	table->body[0]->next->next = NULL;


	EXPECT_EQ(InsertElem(table, str, 3), T_SUCCESS);
	EXPECT_NE(table->body[1]->next, nullptr);
	EXPECT_EQ(strcmp(table->body[1]->next->data, str), 0);


	free(table->body[0]->next->data);
	free(table->body[0]->next);
	free(table->body[1]->next->data);
	free(table->body[1]->next);
	for (int i = 0; i < 3; i++) {
		free(table->body[i]->data);
		free(table->body[i]);
	}
	free(table->body);
	free(table);
}

TEST(RemoveElem, ElemIsInList_ReturnSuccess) {
	const char* str = "c\0";
	hash_table_t* table = (hash_table_t*)malloc(sizeof(hash_table_t));
	table->body = (node_t**)malloc(3 * sizeof(node_t*));
	table->size = 3;

	for (int i = 0; i < 3; i++) {
		table->body[i] = (node_t*)malloc(sizeof(node_t));
		table->body[i]->data = (char*)malloc(2 * sizeof(char));
		table->body[i]->next = NULL;
	}
	strcpy(table->body[0]->data, "c\0");
	strcpy(table->body[1]->data, "a\0");
	strcpy(table->body[1]->data, "b\0");

	table->body[0]->next = (node_t*)malloc(sizeof(node_t));
	table->body[0]->next->data = (char*)malloc(3 * sizeof(char));
	strcpy(table->body[0]->next->data, "ab\0");
	table->body[0]->next->next = NULL;


	EXPECT_EQ(RemoveElem(table, str), T_SUCCESS);
	EXPECT_EQ(table->body[0]->next, nullptr);
	EXPECT_EQ(strcmp(table->body[0]->data, "ab\0"), 0);


	for (int i = 0; i < 3; i++) {
		free(table->body[i]->data);
		free(table->body[i]);
	}
	free(table->body);
	free(table);
}
