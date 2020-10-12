#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS

extern "C" {
#include "../lab1/empH.h"
}

int CheckOpening(FILE* DataIn)
{
	if (DataIn == NULL) {
		printf("Error opening file!\n");
		return(ERROR_OPENING_FILE);
	}
	else
		printf("File opened\n");
	return 0;
}

int CheckMonth(struct employee* emp) {
	if (emp->date.month > DECEMBER || emp->date.month < JANUARY)
		return(WRONG_MONTH_NUMBER);
	return 0;
}

int CheckDay(struct employee* emp) {
	if (emp->date.month == FEBRUARY && emp->date.year % CHECK_BISSEXTILE == 0 && emp->date.day > MAX_FEB_DAYS4) {
		printf("Wrong day number!\n");
		return(WRONG_DAY_NUMBER);
	}
	else if (emp->date.month == FEBRUARY && emp->date.year % CHECK_BISSEXTILE != 0 && emp->date.day > MAX_FEB_DAYS) {
		printf("Wrong day number!\n");
		return(WRONG_DAY_NUMBER);
	}
	else if (emp->date.month == (JANUARY | MARCH | JULY | AUGUST | OCTOBER | DECEMBER) && emp->date.day > MAX_DAY_COUNT1) {
		printf("Wrong day number!\n");
		return(WRONG_DAY_NUMBER);
	}
	else if (emp->date.month == (APRIL | JUNE | SEPTEMBER | NOVEMBER) && emp->date.day > MAX_DAY_COUNT0) {
		printf("Wrong day number!\n");
		return(WRONG_DAY_NUMBER);
	}
	return 0;
}

int CheckHours(struct employee* emp, int hours) {
	if (hours > emp->hours) {
		printf("There's no one employee who has more than %d hours", hours);
		return(WRONG_HOURS_NUMBER);
	}
	return 0;
}

int CheckList(struct employee* emp) {
	if (emp == NULL) {
		printf("===============================\n");
		printf("List has been destroyed\n");
		printf("===============================\n");
		return 0;
	}
	printf("List has already been destroyed\n");
	return(ERROR_DESTRUCTING_LIST);
}

const char* MonthName(int month)
{
	const char* months[] = {
	"Illegal month",
	"January", "February", "March",
	"April", "May", "June",
	"July", "August", "September",
	"October", "November", "December" };
	return (month < JANUARY || month > DECEMBER) ? months[0] : months[month];
}

size_t CalcLines(const char* FileName) {
	FILE* DataIn = fopen(FileName, "r");
	size_t lines = 0;
	while (!feof(DataIn))
	{
		if (fgetc(DataIn) == '\n')
			lines++;
	}
	lines++;
	if (ferror(DataIn))
		printf("err\n");
	return lines;
}

struct employee* empConstructor(FILE* DataIn) {
	struct employee* emp = (employee*)malloc(sizeof(struct employee));
	fscanf(DataIn, "%u%u%u%s%s%u", &emp->date.day, &emp->date.month,
		&emp->date.year, emp->name.first, emp->name.second, &emp->hours);
	CheckMonth(emp);
	CheckDay(emp);
	return emp;
}

struct employee* empListConstructor(const char* FileName) {
	FILE* DataIn = fopen(FileName, "r");
	CheckOpening(DataIn);
	struct employee* emp = empConstructor(DataIn);
	struct employee* empList = emp;
	(empList)->next = NULL;
	while (!feof(DataIn)) {
		emp = emp->next;
		emp = empConstructor(DataIn);
		struct employee* node = emp;
		if (node->hours > empList->hours || (node->hours == empList->hours && (strcmp(empList->name.first, node->name.first) > 0)))
		{
			REPLACE_EMP(empList);
		}
		else {
			struct employee* current = empList;
			while (current->next != NULL && !(node->hours > current->next->hours)) {
				if (current->next->hours == node->hours && (strcmp(current->name.first, node->name.first) > 0)) {
					REPLACE_EMP(current->next);
					goto endcycle;
				}
				else current = current->next;
			}
			REPLACE_EMP(current->next);
		endcycle:;
		}
	}
	return empList;
}

int PrintList(struct employee* emp) {
	size_t id = 0;
	for (id = 1; emp != NULL; emp = emp->next, ++id)
		PRINT_EMP(emp);
	if (id < CalcLines(FILE_NAME))
		return(ERROR_INSERTING_EMP);
	return 0;
}

void PrintSearchList(struct employee* emp) {
	int hours;
	printf("===============================\n");
	printf("Please, enter number of hours: ");
	scanf("%d", &hours);
	printf("===============================\n");
	CheckHours(emp, hours);
	for (int id = 1; emp != NULL; emp = emp->next, ++id) {
		if (emp->hours >= hours)
			PRINT_EMP(emp);
	}
}

struct employee* empListDestructor(struct employee* emp) {
	while (emp != NULL) {
		struct employee* tmp = emp;
		emp = emp->next;
		free(tmp);
	}
	return emp;
}
TEST(CheckTestSeries, TestCheckOpenNull) {
	FILE* DataIn = NULL;
	ASSERT_EQ(CheckOpening(DataIn), ERROR_OPENING_FILE);
}

TEST(CheckTestSeries, TestCheckMonth) {
	struct employee* empTest = (employee*)malloc(sizeof(struct employee));
	empTest->date.month = 0;
	EXPECT_EQ(CheckMonth(empTest), WRONG_MONTH_NUMBER);
	empTest->date.month = FEBRUARY;
	EXPECT_NE(CheckMonth(empTest), WRONG_MONTH_NUMBER);
	free(empTest);
}

TEST(CheckTestSeries, TestCheckDay) {
    struct employee* empTest = (employee*)malloc(sizeof(struct employee));
	empTest->date.month = DECEMBER;
	empTest->date.day = MAX_DAY_COUNT1;
	EXPECT_EQ(CheckDay(empTest), 0);
	empTest->date.year = 1999;
	empTest->date.month = FEBRUARY;
	empTest->date.day = MAX_FEB_DAYS;
	EXPECT_EQ(CheckDay(empTest), 0);
	empTest->date.year = 1999;
	empTest->date.month = FEBRUARY;
	empTest->date.day = MAX_FEB_DAYS4;
	EXPECT_NE(CheckDay(empTest), 0);
	empTest->date.month = NOVEMBER;
	empTest->date.day = MAX_DAY_COUNT1;
	EXPECT_NE(CheckDay(empTest), WRONG_DAY_NUMBER);
	free(empTest);
}

TEST(CheckTestSeries, TestCheckHours) {
	struct employee* empTest = (employee*)malloc(sizeof(struct employee));
	int hours = 1000;
	empTest->hours = 999;
	EXPECT_EQ(CheckHours(empTest, hours), WRONG_HOURS_NUMBER);
	empTest->hours = 1000;
	EXPECT_NE(CheckHours(empTest, hours), WRONG_HOURS_NUMBER);
	free(empTest);
}

TEST(CheckTestSeries, TestCheckList) {
	struct employee* empTest = NULL;
	EXPECT_EQ(CheckList(empTest), 0);
}

TEST(DifTestSeries, TestMonthName) {
	EXPECT_STRCASENE(MonthName(0), "January");
	EXPECT_STRCASEEQ(MonthName(1), "January");
	EXPECT_STRCASEEQ(MonthName(2), "February");
	EXPECT_STRCASEEQ(MonthName(3), "March");
	EXPECT_STRCASEEQ(MonthName(4), "April");
	EXPECT_STRCASEEQ(MonthName(5), "May");
	EXPECT_STRCASEEQ(MonthName(6), "June");
	EXPECT_STRCASEEQ(MonthName(7), "July");
	EXPECT_STRCASEEQ(MonthName(8), "August");
	EXPECT_STRCASEEQ(MonthName(9), "September");
	EXPECT_STRCASEEQ(MonthName(10), "October");
	EXPECT_STRCASEEQ(MonthName(11), "November");
	EXPECT_STRCASEEQ(MonthName(12), "December");
	EXPECT_STRCASENE(MonthName(13), "December");
}

TEST(empTestSeries, TestConstructor) {
	FILE* DataIn = fopen("empList.txt", "r");
	struct employee* empTest = empConstructor(DataIn);
	EXPECT_EQ(empTest->date.day, 18);
	EXPECT_EQ(empTest->date.day, 6);
	EXPECT_EQ(empTest->date.day, 1942);
	EXPECT_STRCASEEQ(empTest->name.first, "Paul");
	EXPECT_STRCASEEQ(empTest->name.second, "McCartney");
	EXPECT_EQ(empTest->hours, 1000);
	fclose(DataIn);
}