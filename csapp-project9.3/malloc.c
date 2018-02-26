//

#include <unistd.h>
#include "malloc.h"
#include <stdio.h>

// Store free memory.
typedef struct free_list {
	int size;
	struct free_list *next;
	struct free_list *before;
} *Free_list;

int found;

Free_list f = NULL;
Free_list a = NULL;

void * my_malloc(unsigned int size)
{
	char *p;

	// User does not want memory so return NULL.
	if (size == 0)
	{
		return NULL;
	}

	// First time malloc called.
	if (f == NULL)
	{
		// Allocate a bunch of memory with 12 bytes for header.
		// If size is less than 3, 10*size is not enough so allocate 40.
		if (size > 3)
		{
			p = sbrk(10 * size);
			f = (void *)p;
			f->size = 10 * size - 12;
		}
		else
		{
			p = sbrk(40);
			f = (void *)p;
			f->size = 40 - 12;
		}
		f->next = NULL;
		f->before = NULL;

		p = (void*) &(f->size);

		if (*p == -1)
		{
			return NULL;
		}

		// 8 byte header after (p + 12) which has the actual size to be used and the checksum.
		*(p + 12) = size;	// Actual size to be returned.
		*(p + 12 + 4) = 0;	// Checksum.

							// This chunk is not available any more.
		f->size = 0;

		// Set the next attributes.
		f->next = (void *)p + 20 + size;

		if (size > 3)
			f->next->size = 10 * size - (12 + 8 + size + 12);
		else
			f->next->size = 40 - (12 + 8 + size + 12);
		f->next->next = NULL;
		f->next->before = (void *)p;

		// Return the space requested from user.
		return p + 20;

	}
	// Not the first time.
	else
	{
		found = 1;

		// Get ready to traverse through free list.
		a = f;

		// While the size needed is greater than available size at current location.
		while (a->size <= (size + 20))
		{
			// If the next section exists, go there.
			if (a->next != NULL)
			{
				a = a->next;
			}
			// Else, no more space.
			else
			{
				found = 0;
				break;
			}
		}

		// If enough space is found in buffer.
		if (found)
		{
			// Get the address of a.
			p = (void*) &(a->size);

			// 12 byte headers already set by previous malloc.

			// Set the 8 byte headers.
			*(p + 12) = size;	// Actual size to be returned.
			*(p + 12 + 4) = 0;	// Checksum.

								// Set the next attributes (only if this is the last section of the list).
			if (a->next == NULL)
			{
				a->next = (void *)p + 12 + 8 + size;
				a->next->size = a->size - (8 + size + 12);
				a->next->next = NULL;
				a->next->before = (void *)a;
			}

			// This chunk is not available anymore.
			a->size = 0;

			// Return space requested by user.
			return p + 20;
		}
		// Not enough space found in buffer.
		else
		{
			// Allocate more memory.
			// If size is less than 3, 10*size is not enough so allocate 40.
			if (size > 3)
			{
				p = sbrk(10 * size);
			}
			else
			{
				p = sbrk(40);
			}

			if (*p == -1)
			{
				return NULL;
			}

			// Make sure the last chunk is now pointing to the beginning of the newly allocated memory.
			a->next = (void *)p;
			a = a->next;

			a = (void *)p;

			// 12 byte header.
			if (size > 3)
			{
				a->size = 10 * size - 12;
			}
			else
			{
				a->size = 40 - 12;
			}

			p = (void*) &(a->size);

			a->next = NULL;
			a->before = NULL;


			// 8 byte header after (p + 12) which has the actual size to be used and the checksum.
			*(p + 12) = size;	// Actual size to be returned.
			*(p + 12 + 4) = 0;	// Checksum.

								// This chunk is not available any more.
			a->size = 0;

			// Set the next attributes.
			a->next = (void *)p + 20 + size;
			if (size > 3)
			{
				a->next->size = 10 * size - (12 + 8 + size + 12);
			}
			else
			{
				a->next->size = 40 - (12 + 8 + size + 12);
			}
			a->next->next = NULL;
			a->next->before = (void *)a;

			// Return the space requested from user.
			return p + 20;
		}
	}
	return NULL;
}

void my_free(void *p)
{
	int size;
	char *a;
	a = (void *)p;

	// Cannot free a NULL pointer.
	if (p == NULL)
		return;

	// If checksum is indeed 0.
	if (*(a - 4) == 0 && (a - 8) != NULL && (a - 20) != NULL)
	{
		size = *(a - 8);
		*(a - 20) = size + 8; // Size + 8 byte headers available to use again.
	}
}

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
	char *buffer = (char *)my_malloc(sizeof(char) * size);
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
	my_free(buffer);
	
	//关闭文件
	fclose(fin);
	fclose(fout);
	return 0;
	// int a[100];
	// for(int i=0;i<100;i++)
	// {
	// 	a[i]=i;
	// }
	// int *b=(int *)my_malloc(sizeof(a));
	// printf("%d\n",sizeof(b));
    // return 0;
}

