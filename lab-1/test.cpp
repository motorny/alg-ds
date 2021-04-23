#include "pch.h"
extern "C"
{
  #include "Set.h"
}


/********
 * UNIT TESTS
 ********/

static Set* PrepareDataForTest()
{
  Set* S;
  Node* tmp1;
  Node* tmp2;
  Node* tmp3;
  S = (Set*)malloc(sizeof(Set));
  tmp1 = (Node *)malloc(sizeof(Node));
  tmp2 = (Node*)malloc(sizeof(Node));
  tmp3 = (Node *)malloc(sizeof(Node));
  tmp1->data = 1;
  tmp2->data = 3;
  tmp3->data = 4;
  S->Root = tmp1;
  tmp1->next = tmp2;
  tmp2->next = tmp3;
  tmp3->next = NULL;
  return S;
}

static Set* PrepareEmptyForTest()
{
  Set* S;
  S = (Set *)malloc(sizeof(Set));
  S->Root = NULL;
  return S;
}

static void DeleteDataForTest(Set* S)
{
  free(S->Root->next->next);
  free(S->Root->next);
  free(S->Root);
  free(S);
  return;
}

static void DeleteEmptyForTest(Set* S)
{
  free(S);
  return;
}

TEST(SetAdd_AddBegin_Correct)
{
  Set* S = PrepareDataForTest();
  SetAdd(S, 0);
  ASSERT_EQ(S->Root->data, 0);
  DeleteDataForTest(S);
}

TEST(SetAdd_AddEnd_Correct)
{
  Set* S = PrepareDataForTest();
  SetAdd(S, 5);
  ASSERT_EQ(S->Root->next->next->next->data, 5);
  DeleteDataForTest(S);
}
TEST(SetAdd_AddMiddle_Correct)
{
  Set* S = PrepareDataForTest();
  SetAdd(S, 2);
  ASSERT_EQ(S->Root->next->data, 2);
  DeleteDataForTest(S);
}

TEST(SetDel_DelBegin_Correct)
{
  Set* S = PrepareDataForTest();
  SetDel(S, 1);
  ASSERT_EQ(S->Root->data, 3);
  DeleteDataForTest(S);
}
TEST(SetDel_DelEnd_Correct)
{
  Set* S = PrepareDataForTest();
  SetDel(S, 4);
  ASSERT_EQ(S->Root->next->next, (Node *)NULL);
  DeleteDataForTest(S);
}
TEST(SetDel_DelMiddle_Correct)
{
  Set* S = PrepareDataForTest();
  SetDel(S, 3);
  ASSERT_EQ(S->Root->next->data, 4);
  DeleteDataForTest(S);
}
TEST(SetDel_DelNotExist_Correct)
{
  Set* S = PrepareDataForTest();
  SetDel(S, 30);
  ASSERT_EQ(S->Root->data, 1);
  ASSERT_EQ(S->Root->next->data, 3);
  ASSERT_EQ(S->Root->next->next->data, 4);
  DeleteDataForTest(S);
}

TEST(SetUnion_EmptyAndEmpty_ReturnEmpty)
{
  Set* S1 = PrepareEmptyForTest();
  Set* S2 = PrepareEmptyForTest();

  Set* Srez = SetUnion(S1, S2);
  ASSERT_EQ(Srez->Root, (Node*)NULL);

  DeleteEmptyForTest(S1);
  DeleteEmptyForTest(S2);
  DeleteEmptyForTest(Srez);
}

TEST(SetUnion_EmptyAndNonEmpty_ReturnSecond)
{
  Set* S1 = PrepareDataForTest();
  Set* S2 = PrepareEmptyForTest();

  Set* S = SetUnion(S2, S1);
  ASSERT_EQ(S->Root->data, 1);
  ASSERT_EQ(S->Root->next->data, 3);
  ASSERT_EQ(S->Root->next->next->data, 4);

  DeleteDataForTest(S1);
  DeleteEmptyForTest(S2);
  DeleteDataForTest(S);
}

TEST(SetUnion_NonEmptyAndEmpty_ReturnFirst)
{
  Set* S1 = PrepareDataForTest();
  Set* S2 = PrepareEmptyForTest();

  Set* S = SetUnion(S1, S2);
  ASSERT_EQ(S->Root->data, 1);
  ASSERT_EQ(S->Root->next->data, 3);
  ASSERT_EQ(S->Root->next->next->data, 4);

  DeleteDataForTest(S1);
  DeleteEmptyForTest(S2);
  DeleteDataForTest(S);
}

TEST(SetUnion_NonSame_ReturnCorrect)
{
  Set* S1 = PrepareDataForTest();
  Set* S2 = PrepareDataForTest();
  S2->Root->data = 0;
  S2->Root->next->data = 2;
  S2->Root->next->next->data = 5;

  Set* S = SetUnion(S1, S2);
  ASSERT_EQ(S->Root->data, 0);
  ASSERT_EQ(S->Root->next->data, 1);
  ASSERT_EQ(S->Root->next->next->data, 2);
  ASSERT_EQ(S->Root->next->next->next->data, 3);
  ASSERT_EQ(S->Root->next->next->next->next->data, 4);
  ASSERT_EQ(S->Root->next->next->next->next->next->data, 5);

  DeleteDataForTest(S1);
  DeleteDataForTest(S2);
  free(S->Root->next->next->next->next->next);
  free(S->Root->next->next->next->next);
  free(S->Root->next->next->next);
  free(S->Root->next->next);
  free(S->Root->next);
  free(S->Root);
  free(S);
}

TEST(SetUnion_PartlySame_ReturnCorrect)
{
  Set* S1 = PrepareDataForTest();
  Set* S2 = PrepareDataForTest();
  S2->Root->data = 2;

  Set* S = SetUnion(S1, S2);
  ASSERT_EQ(S->Root->data, 1);
  ASSERT_EQ(S->Root->next->data, 2);
  ASSERT_EQ(S->Root->next->next->data, 3);
  ASSERT_EQ(S->Root->next->next->next->data, 4);

  DeleteDataForTest(S1);
  DeleteDataForTest(S2);
  free(S->Root->next->next->next);
  free(S->Root->next->next);
  free(S->Root->next);
  free(S->Root);
  free(S);
}

TEST(SetUnion_Same_ReturnSame)
{
  Set* S1 = PrepareDataForTest();
  Set* S2 = PrepareDataForTest();

  Set* S = SetUnion(S1, S2);
  ASSERT_EQ(S->Root->data, 1);
  ASSERT_EQ(S->Root->next->data, 3);
  ASSERT_EQ(S->Root->next->next->data, 4);

  DeleteDataForTest(S1);
  DeleteDataForTest(S2);
  DeleteDataForTest(S);
}

TEST(SetIntersect_EmptyAndEmpty_ReturnEmpty)
{
  Set* S1 = PrepareEmptyForTest();
  Set* S2 = PrepareEmptyForTest();

  Set* Srez = SetIntersect(S1, S2);
  ASSERT_EQ(Srez->Root, (Node*)NULL);

  DeleteEmptyForTest(S1);
  DeleteEmptyForTest(S2);
  DeleteEmptyForTest(Srez);
}

TEST(SetIntersect_EmptyAndNonEmpty_ReturnEmpty)
{
  Set* S1 = PrepareDataForTest();
  Set* S2 = PrepareEmptyForTest();

  Set* S = SetIntersect(S2, S1);
  ASSERT_EQ(S->Root, (Node*)NULL);

  DeleteDataForTest(S1);
  DeleteEmptyForTest(S2);
  DeleteEmptyForTest(S);
}
TEST(SetIntersect_NonEmptyAndEmpty_ReturnEmpty)
{
  Set* S1 = PrepareDataForTest();
  Set* S2 = PrepareEmptyForTest();

  Set* S = SetIntersect(S1, S2);
  ASSERT_EQ(S->Root, (Node*)NULL);

  DeleteDataForTest(S1);
  DeleteEmptyForTest(S2);
  DeleteEmptyForTest(S);
}
TEST(SetIntersect_NonSame_ReturnEmpty)
{
  Set* S1 = PrepareDataForTest();
  Set* S2 = PrepareDataForTest();

  S2->Root->data = 0;
  S2->Root->next->data = 2;
  S2->Root->next->next->data = 5;

  Set* S = SetIntersect(S2, S1);
  ASSERT_EQ(S->Root, (Node*)NULL);

  DeleteDataForTest(S1);
  DeleteDataForTest(S2);
  DeleteEmptyForTest(S);
}
TEST(SetIntersect_PartlySame_ReturnSamePart)
{
  Set* S1 = PrepareDataForTest();
  Set* S2 = PrepareDataForTest();

  S2->Root->next->data = 2;
  S2->Root->next->next->data = 5;

  Set* S = SetIntersect(S2, S1);
  ASSERT_EQ(S->Root->data, 1);
  ASSERT_EQ(S->Root->next, (Node*)NULL);

  DeleteDataForTest(S1);
  DeleteDataForTest(S2);
  free(S->Root);
  free(S);
}
TEST(SetIntersect_Same_ReturnSame)
{
  Set* S1 = PrepareDataForTest();
  Set* S2 = PrepareDataForTest();

  Set* S = SetIntersect(S2, S1);
  ASSERT_EQ(S->Root->data, 1);
  ASSERT_EQ(S->Root->next->data, 3);
  ASSERT_EQ(S->Root->next->next->data, 4);

  DeleteDataForTest(S1);
  DeleteDataForTest(S2);
  DeleteDataForTest(S);
}

TEST(SetFree_NULLPointer_Return)
{
  SetFree(NULL);
}