#include <stdio.h>
#include "unity.h"

#include "csv.h"

void test_csv_open_close()
{
	struct csv file;
	TEST_ASSERT_EQUAL_INT(CSV_OK, csv_open(&file, "../files/file1.csv", ',', 4));
	TEST_ASSERT_EQUAL_INT(CSV_OK, csv_close(&file));
	TEST_ASSERT_EQUAL_INT(CSV_OK, csv_open(&file, "../files/file2.csv", ',', 5));
	TEST_ASSERT_EQUAL_INT(CSV_OK, csv_close(&file));
	TEST_ASSERT_EQUAL_INT(CSV_OK, csv_open(&file, "../files/file3.csv", ',', 5));
	TEST_ASSERT_EQUAL_INT(CSV_OK, csv_close(&file));
}



int main()
{
	UNITY_BEGIN();
	RUN_TEST(test_csv_open_close);
	return UNITY_END();
}