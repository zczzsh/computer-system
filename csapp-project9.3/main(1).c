#include "mymalloc.h"

int main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("usage: %s <infilename> <outfilename>\n", argv[0]);
		exit(0);
	}
	//FILE *fin = fopen(argc[2], "rb");
	//FILE *fout = fopen(argv[3], "wb");
	//打开文件
	FILE *fin = fopen(argv[1], "rb");
	FILE *fout = fopen(argv[2], "wb");
	
	//获取文件大小
	fseek(fin, 0, SEEK_END);
	long size = ftell(fin);
	rewind(fin);
	
	//申请内存
	char *buffer = (char *)malloc(sizeof(char) * size);
	if(buffer == NULL) {
		puts("error: Memory error.");
		exit(0);
	}
	
	//读取文件到buffer
	size_t res = fread(buffer, 1, size, fin);
	if(res != size) {
		puts("error: Reading error.");
		exit(0);
	}
	
	//将buffer写入到文件中
	fwrite(buffer, sizeof(char), size, fout);
	
	//释放内存
	free(buffer);
	
	//关闭文件
	fclose(fin);
	fclose(fout);
	return 0;
}
