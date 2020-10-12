#include "pch.h"

extern "C" {
#include "../lab1/empH.h"
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

