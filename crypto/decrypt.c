#include <stdio.h>
#include <stdlib.h>

#include "aes.h"
#include "key.h"



int main()
{
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	char *buf;
	char *buf_t;
	int i, file_size;

	fp1 = fopen("y", "r");
	fp2 = fopen("x.d", "w");

	if (!fp1 && !fp2)
		return -1;

	fseek(fp1, 0, SEEK_END);
	if ((file_size = ftell(fp1)) == 0) {
		printf("LINE %d\n", __LINE__);
		goto out;
	}
	fseek(fp1 , 0 , SEEK_SET);

	if (file_size%ECB_KEYLEN) {
		printf("%s file size %d(0x%x) ecb not aligned", __func__, file_size, file_size);
		goto out;
	}

	buf = calloc(file_size, 1);
	buf_t = calloc(file_size, 1);
	if (!buf || !buf_t) {
		printf("LINE %d\n", __LINE__);
		goto out;
	}
   	if (fread(buf, file_size, 1, fp1) != 1) {
		printf("LINE %d\n", __LINE__);
		goto out;
	}

	for (i=0; i<(file_size/ECB_KEYLEN); i++) {
		AES128_ECB_decrypt(buf + (i*ECB_KEYLEN), gEcbKey, buf_t + (i*ECB_KEYLEN));
	}

	if (fwrite(buf_t, file_size, 1, fp2) != 1) {
		printf("LINE %d\n", __LINE__);
		goto out;
	}
	printf("LINE %d\n", __LINE__);

out:
	fclose(fp1);
	fclose(fp2);

	return 0;
}

