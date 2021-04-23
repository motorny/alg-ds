#include "pch.h"

extern "C"
{
  #include "Lab_C.h"
}

TEST(TestDFSPrint, String_Empty_DontCrush) {
  char Buf[] = "";
  PrintDFS(Buf);
}

TEST(TestDFSPrint, String_Chars_DontCrush) {
  char Buf[] = "Some very meaningful sentence\n";
  PrintDFS(Buf);
}

TEST(TestDFSPrint, String_IncorrectSize_DontCrush) {
  char Buf[] = "-20\n";
  PrintDFS(Buf);
}
TEST(TestDFSPrint, String_NotAllData_DontCrush) {
  char Buf[] = "5\n"
    "0 2\n"
    "1\n"
    "2 4";
  PrintDFS(Buf);
}

TEST(TestDFSPrint, String_TooBigElement_DontCrush) {
  char Buf[] = "3\n"
    "0 2\n"
    "100 1\n"
    "2 4";
  PrintDFS(Buf);
}

TEST(TestDFSPrint, String_CorrectWithLast) {
  char Buf[] = "5\n"
    "0 2\n"
    "1\n"
    "2 4\n"
    "3 4\n"
    "4\n";
  PrintDFS(Buf);
}

TEST(TestDFSPrint, String_CorrectWithoutLast) {
  char Buf[] = "5\n"
    "0 2\n"
    "1\n"
    "2 4\n"
    "3 4\n"
    "4";
  PrintDFS(Buf);
}
