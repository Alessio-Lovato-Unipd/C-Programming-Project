#include <stdio.h>
#include <stdlib.h>
#include "csv.h"
int main()
{
	struct csv file;
	int out = 0;
	char *error;
	char *nomefile = "../../../test/test_csv/files/file1.csv";
	char **fields;
	out = csv_open(&file, nomefile, ',', 4);
	while(csv_read_record(&file, &fields) == CSV_OK){
		printf("%s\n", fields[0]);
		printf("%s\n", fields[1]);
		printf("%s\n", fields[2]);
		printf("%s\n", fields[3]);
	}
	csv_error_string(out, &error);
	printf("%s\n", error);
	csv_close(&file);
	
	/*nomefile = "../../../test/test_csv/files/file2.csv";
	out = csv_open(&file, nomefile, ',', 5);
	csv_error_string(out, &error);
	printf("%s\n", error);
	csv_close(&file);
	
	nomefile = "../../../test/test_csv/files/file3.csv";
	out = csv_open(&file, nomefile, ',', 5);
	csv_error_string(out, &error);
	printf("%s\n", error);
	csv_close(&file);*/
	return 0;
}