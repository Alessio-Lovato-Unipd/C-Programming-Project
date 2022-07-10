#include <stdio.h>
#include <stdlib.h>
#include "csv.h"
int main()
{
	struct csv file;
	int out = 0;
	char *error;
	int ret;
	char *nomefile = "../../../test/test_csv/files/file1.csv";
	char **fields;
	out = csv_open(&file, nomefile, ',', 4);
	csv_error_string(out, &error);
	printf("%s\n", error);
	while((ret = csv_read_record(&file, &fields)) == CSV_OK){
		csv_error_string(ret, &error);
		printf("%s\n", error);
		printf("%s\t", fields[0]);
		printf("%s\t", fields[1]);
		printf("%s\t", fields[2]);
		printf("%s\t", fields[3]);
		printf("\n");
	}
	csv_error_string(ret, &error);
	printf("%s\n", error);
	csv_close(&file);
	
	nomefile = "../../../test/test_csv/files/file2.csv";
	out = csv_open(&file, nomefile, ',', 5);
	csv_error_string(out, &error);
	while((ret = csv_read_record(&file, &fields)) == CSV_OK){
		csv_error_string(ret, &error);
		printf("%s\n", error);
		printf("%s\t", fields[0]);
		printf("%s\t", fields[1]);
		printf("%s\t", fields[2]);
		printf("%s\t", fields[3]);
		printf("%s\t", fields[4]);
		printf("\n");
	}
	csv_error_string(ret, &error);
	printf("%s\n", error);
	csv_close(&file);
	
	nomefile = "../../../test/test_csv/files/file3.csv";
	out = csv_open(&file, nomefile, ',', 5);
	csv_error_string(out, &error);
	while((ret = csv_read_record(&file, &fields)) == CSV_OK){
		csv_error_string(ret, &error);
		printf("%s\n", error);
		printf("%s\t", fields[0]);
		printf("%s\t", fields[1]);
		printf("%s\t", fields[2]);
		printf("%s\t", fields[3]);
		printf("%s\t", fields[4]);
		printf("\n");
	}
	csv_error_string(ret, &error);
	printf("%s\n", error);
	csv_close(&file);
	return 0;
}