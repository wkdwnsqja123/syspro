#include <stdio.h>
#include "book.h"

int main(int argc, char* argv[]) {
	struct book rec;
	FILE *fp;
	if (argc != 2) {
		fprintf(stderr, "How to use: %s FileName\n", argv[0]);
		return 1;
	}
	fp = fopen(argv[1], "r");
	printf("%-s %-7s %-8s %-4s %-s %-5s\n", "Id", "Bookname", "Author", "Year", "NumOfBorrow", "Borrow");
	while (fscanf(fp,"%d %s %s %d %d %d", &rec.id, rec.bookname, rec.author, &rec.year, &rec.numofborrow, &rec.borrow)==6)
			printf("%10d %6s %6s %6d %6d %6d\n", rec.id, rec.bookname, rec.author, rec.year, rec.numofborrow, rec.borrow);
	fclose(fp);
	return 0;
}
			
