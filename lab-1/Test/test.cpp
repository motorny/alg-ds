#include "pch.h"

extern "C" {
  #include"list.h"
}
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

static void CreateFirstListForTests(List_t* bucket[]) {

  List_t* list1, * list2, * list3, * list4;

  list1 = (List_t*)malloc(sizeof(List_t));
  list1->data = (char*)malloc(21 * sizeof(char*));
  list2 = (List_t*)malloc(sizeof(List_t));
  list2->data = (char*)malloc(21 * sizeof(char*));
  list3 = (List_t*)malloc(sizeof(List_t));
  list3->data = (char*)malloc(21 * sizeof(char*));
  list4 = (List_t*)malloc(sizeof(List_t));
  list4->data = (char*)malloc(21 * sizeof(char*));

  if (list1 && list2 && list3 && list4) {
    strcpy(list1->data, "Name");
    strcpy(list2->data, "Dima");
    strcpy(list3->data, "Sasha");
    strcpy(list4->data, "Nikolay");
    list1->next = list2;
    list2->next = list3;
    list3->next = list4;
    list4->next = NULL;
  }

  List_t* list5, * list6, * list7, * list8;
  list5 = (List_t*)malloc(sizeof(List_t));
  if(list5 && list5->data)
    list5->data = (char*)malloc(21 * sizeof(char*));
  list6 = (List_t*)malloc(sizeof(List_t));
  if (list6 && list6->data)
    list6->data = (char*)malloc(21 * sizeof(char*));
  list7 = (List_t*)malloc(sizeof(List_t));
  if (list7 && list7->data)
    list7->data = (char*)malloc(21 * sizeof(char*));
  list8 = (List_t*)malloc(sizeof(List_t));
  if (list8 && list8->data)
    list8->data = (char*)malloc(21 * sizeof(char*));

  if (list5 && list6 && list7 && list8 && list5->data && list6->data && list7->data && list8->data) {
    strcpy(list5->data, "Code");
    strcpy(list6->data, "1");
    strcpy(list7->data, "2");
    strcpy(list8->data, "2");
    list5->next = list6;
    list6->next = list7;
    list7->next = list8;
    list8->next = NULL;
  }

  bucket[0] = list1;
  bucket[1] = list5;
}

static void CreateSecondListForTests(List_t* bucket[]) {

  List_t* list1, * list2, * list3;
  list1 = (List_t*)malloc(sizeof(List_t));
  if(list1->data)
    list1->data = (char*)malloc(21 * sizeof(char*));
  list2 = (List_t*)malloc(sizeof(List_t));
  if (list2->data)
    list2->data = (char*)malloc(21 * sizeof(char*));
  list3 = (List_t*)malloc(sizeof(List_t));
  if (list3 && list3->data)
    list3->data = (char*)malloc(21 * sizeof(char*));

  if (list1 && list2 && list3 && list1->data && list2->data && list3->data) {
    strcpy(list1->data, "Section");
    strcpy(list2->data , "Football");
    strcpy(list3->data , "Box");
    list1->next = list2;
    list2->next = list3;
    list3->next = NULL;
  }
  List_t* list4, * list5, * list6;
  list4 = (List_t*)malloc(sizeof(List_t));
  if (list4 && list4->data)
    list4->data = (char*)malloc(21 * sizeof(char*));
  list5 = (List_t*)malloc(sizeof(List_t));
  if (list5 && list5->data)
    list5->data = (char*)malloc(21 * sizeof(char*));
  list6 = (List_t*)malloc(sizeof(List_t));
  if (list6 && list6->data)
    list6->data = (char*)malloc(21 * sizeof(char*));

  if (list4 && list5 && list6 && list4->data && list5->data && list6->data) {
    strcpy(list4->data, "Code");
    strcpy(list5->data, "1");
    strcpy(list6->data, "2");
    list4->next = list5;
    list5->next = list6;
    list6->next = NULL;
  }

  bucket[0] = list1;
  bucket[1] = list4;
}

static void FreeTestData(List_t* buckets[], int n) {
  while (buckets[0] != NULL)
    for (int i = 0; i < n; i++) {
      List_t* cur = buckets[i];
      buckets[i] = cur->next;
      free(cur->data);
      free(cur);
    }
  return;
}

TEST(CreateBucketMerge, CorrectData_ReturnTrue) {//check if Add2List can initializ empty list
  List_t* buckets1[2] = {NULL}, * buckets2[2] = {NULL};
  List_t* bucketsMerge[4] = {NULL};

  CreateFirstListForTests(buckets1);
  CreateSecondListForTests(buckets2);
  CreateBucketMerge(buckets1, buckets2, bucketsMerge, 2);
  ASSERT_STREQ(bucketsMerge[0]->data,"Name");
  ASSERT_STREQ(bucketsMerge[0]->next->data, "Dima");
  ASSERT_STREQ(bucketsMerge[0]->next->next->data, "Sasha");
  ASSERT_STREQ(bucketsMerge[0]->next->next->next->data, "Nikolay");

  ASSERT_STREQ(bucketsMerge[1]->data, "Code");
  ASSERT_STREQ(bucketsMerge[1]->next->data, "1");
  ASSERT_STREQ(bucketsMerge[1]->next->next->data, "2");
  ASSERT_STREQ(bucketsMerge[1]->next->next->next->data, "2");

  ASSERT_STREQ(bucketsMerge[2]->data, "Section");
  ASSERT_STREQ(bucketsMerge[2]->next->data, "Football");
  ASSERT_STREQ(bucketsMerge[2]->next->next->data, "Box");
  ASSERT_STREQ(bucketsMerge[2]->next->next->next->data, "Box");

 FreeTestData(bucketsMerge, 3);
}

#define INVALID_COLUMNS_ERROR_CODE -1
#define CORRECT_COLUMNS_CODE 1

TEST(CreateBucketMerge, normalColumns_ValidVal) {
  List_t* buckets1[2] = {NULL}, * buckets2[2] = {NULL};
  List_t* bucketsMerge[4] = {NULL};

  CreateFirstListForTests(buckets1);
  CreateSecondListForTests(buckets2);
  ASSERT_EQ(CreateBucketMerge(buckets1, buckets2, bucketsMerge, 2), CORRECT_COLUMNS_CODE);

  FreeTestData(bucketsMerge, 3);
}

TEST(CreateBucketMerge, badlColumns_ValidVal) {
  List_t* buckets1[2] = { NULL }, * buckets2[2] = { NULL };
  List_t* bucketsMerge[4] = { NULL };


  CreateFirstListForTests(buckets1);
  CreateSecondListForTests(buckets2);
  strcpy(buckets2[1]->data, "id");

  ASSERT_EQ(CreateBucketMerge(buckets1, buckets2, bucketsMerge, 2), INVALID_COLUMNS_ERROR_CODE);

  FreeTestData(buckets1, 2);
  FreeTestData(buckets2, 2);
}

TEST(CreateBucketMerge, emptyList_ValidVal) {
  List_t* buckets1[2] = {NULL}, * buckets2[2] = {NULL};
  List_t* bucketsMerge[4] = {NULL};

  CreateFirstListForTests(buckets1);
  ASSERT_EQ(CreateBucketMerge(buckets1, buckets2, bucketsMerge, 2), INVALID_COLUMNS_ERROR_CODE);

  FreeTestData(buckets1, 2);
}

TEST(Add2List, emptyList_ReturnTrue) {
  List* node = NULL;
  node = Add2List(node, "check");
  ASSERT_STREQ(node->data, "check");
  free(node);
}

TEST(Add2List, notEmptyList_ReturnTrue) {
  List* node = (List_t*)malloc(sizeof(List_t));
  node->next = NULL;
  node = Add2List(node, "check");
  ASSERT_STREQ(node->next->data, "check");
  free(node->next);
  free(node);
}

