#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <netinet/in.h>

void printUsage()
{
	printf("syntax : add-nbo <file1> <file2>\n");
	printf("sample : add-nbo a.bin b.bin\n");
	return;
}

void error(int errno) 
{
	printf("error %d\n", errno);
	switch(errno)
	{
		case 1 :
			printf("syntax : add-nbo <file1> <file2>\n");
			printf("sample : add-nbo a.bin b.bin\n");
			exit(-1);
			break;
		case 2 :
			printf("There's no matching file(s).\n");
			exit(-1);
			break;
		case 3 :
			printf("The file size must be greater than 4 bytes.\n");
			exit(-1);
			break;
		default :
			printf("Unknown error.\n");
			exit(-1);
	}
}

int main(int argc, char*argv[])
{
	if (argc < 3)
		error(1);
	
	FILE* file1 = fopen(argv[1], "rb");
	FILE* file2 = fopen(argv[2], "rb");
	if(!file1 || !file2)
		error(2);
	
	uint32_t num1 = 0, num2 = 0;
	fread(&num1, sizeof(uint32_t), 1, file1);
	fread(&num2, sizeof(uint32_t), 1, file2);
	uint64_t tell_file1 = ftell(file1);
	uint64_t tell_file2 = ftell(file2);
	if(tell_file1 < 4 || tell_file2 < 4)
		error(3);

	num1 = ntohl(num1);
	num2 = ntohl(num2);
	uint32_t sum = num1 + num2;	
	printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, sum, sum);

	return 0;
}
