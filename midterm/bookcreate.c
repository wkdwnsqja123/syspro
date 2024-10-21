#include <stdio.h>
#include "book.h"
#include <stdlib.h>
int main(int argc, char* argv[])
{
	struct book rec;
	FILE *fp;
	if (argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}
	fp = fopen(argv[1], "wb");
	printf("%-s %-7s %-8s %-4s %-s %-5s\n", "Id", "Bookname", "Author", "Year", "NumOfBorrow", "Borrow");
	while (scanf("%d %s %s %d %d %d", &rec.id, rec.bookname, rec.author, &rec.year, &rec.numofborrow, &rec.borrow)==3)
		fwrite(&rec, sizeof(rec), 1, fp);
	fclose(fp);
	exit(0);
}

