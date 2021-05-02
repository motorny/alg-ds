#include "pch.h"
#include "hash_table.h"

hash_table* init_simple_table() {
	int size = 5;
	int str_len = 7;
	hash_table* table = (hash_table*)malloc(sizeof(hash_table));
	table->table = (node**)malloc(size * sizeof(node*));
	table->size = size;

	for (int i = 0; i < size; i++) {
		table->table[i] = (node*)malloc(sizeof(node));
		table->table[i]->str = (char*)malloc(str_len *sizeof(char));
	
	}
	
	strcpy(table->table[0]->str,"a");
	strcpy(table->table[1]->str, "b");
	
	strcpy(table->table[2]->str, "c");
	strcpy(table->table[3]->str, "d");
	strcpy(table->table[4]->str, "e");

	table->table[0]->next = (node*)malloc(sizeof(node));
	table->table[0]->next->str = (char*)malloc(str_len * sizeof(char));
	strcpy(table->table[0]->next->str, "ab");
	
	table->table[0]->next->next = (node*)malloc(sizeof(node));
	table->table[0]->next->next->str = (char*)malloc(str_len * sizeof(char));
	strcpy(table->table[0]->next->next->str, "abc");



	return table;
}



TEST(TestInsertNode, InsertOneNode) {
	hash_table* t = init_table(1, 2);
	node* a = init_node("a", 2);
	insert_node(t, a);
	int str_cmp_res = strcmp(t->table[0]->str, "a");
	EXPECT_EQ(str_cmp_res, 0);
	
}


TEST(TestInsertNode, InserTwoNodesOneField) {
	hash_table* t = init_table(1, 2);
	node* a = init_node("a", 2);
	node* b = init_node("b", 2);

	insert_node(t, a);
	insert_node(t, b);
	EXPECT_TRUE(t->table[0]->next != NULL);
	int str_cmp_res = strcmp(t->table[0]->next->str, "b");
	EXPECT_EQ(str_cmp_res, 0);
}


TEST(TestFindNode, OneNodeFieldReturnTrue) {
	hash_table* t = init_table(1, 2);
	node* a = init_node("a", 2);

	insert_node(t, a);
	EXPECT_TRUE(find_node(t,"a") != NULL);
	free_table(t);

}


TEST(TestFindNode, OneNodeFieldNoValReturnFalse) {
	hash_table* t = init_table(1, 2);
	node* a = init_node("a", 2);

	insert_node(t, a);
	EXPECT_TRUE(find_node(t, "b") == NULL);
	free_table(t);

}


TEST(TestFindNode, TwoNodeFieldReturnTrue) {
	hash_table* t = init_table(1, 2);
	node* a = init_node("a", 2);
	node* b = init_node("b", 2);

	insert_node(t, a);
	insert_node(t, b);
	EXPECT_TRUE(find_node(t, "b") != NULL);
	free_table(t);

}

TEST(TestRemoveNode, RemoveExistingNodeReturnTrue) {
	hash_table* t = init_table(2,2);
	insert_node(t, init_node("a", 2));

	EXPECT_TRUE(remove(t, "a"));
	free_table(t);

}

TEST(TestRemoveNode, RemoveNonExistingNodeReturnFalse) {
	hash_table* t = init_table(2, 2);
	insert_node(t, init_node("a", 2));

	EXPECT_FALSE(remove(t, "doesnt_exist"));
	free_table(t);
}



TEST(TestRemoveNode, RemoveFirstFromThreeNodeFieldReturnTrue) {
	hash_table* t = init_table(1, 2);
	insert_node(t, init_node("a", 2));
	insert_node(t, init_node("ab", 3));
	insert_node(t, init_node("abc", 4));

	EXPECT_TRUE(remove(t, "a"));
	EXPECT_TRUE(t->table[0]);
	EXPECT_TRUE(t->table[0]->next);

	EXPECT_EQ(strcmp(t->table[0]->str, "ab"), 0);
	EXPECT_EQ(strcmp(t->table[0]->next->str, "abc"), 0);

	free_table(t);
}

TEST(TestRemoveNode, RemoveMiddleFromThreeNodeFieldReturnTrue) {
	hash_table* t = init_table(1, 2);
	insert_node(t, init_node("a", 2));
	insert_node(t, init_node("ab", 3));
	insert_node(t, init_node("abc", 4));

	EXPECT_TRUE(remove(t, "ab"));
	EXPECT_TRUE(t->table[0]);
	EXPECT_TRUE(t->table[0]->next);

	EXPECT_EQ(strcmp(t->table[0]->str, "a"), 0);
	EXPECT_EQ(strcmp(t->table[0]->next->str, "abc"), 0);

	free_table(t);
}

