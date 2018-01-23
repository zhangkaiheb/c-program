#include <stdio.h>
#include <stdlib.h>

#include "aes.h"
#include "key.h"


int main()
{
	int i;
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	char *buf = NULL;
	char *buf_t = NULL;
    int enlen, file_size;

	fp1 = fopen("x","r");
	fp2 = fopen("y","w");

	if (!fp1 || !fp2) {
		return -1;
	}

	fseek(fp1, 0, SEEK_END);
	if ((file_size = ftell(fp1)) == 0) {
		printf("LINE %d\n", __LINE__);
		goto out;
	}
	fseek(fp1 , 0 , SEEK_SET);

	enlen = ((file_size + ECB_KEYLEN - 1)/ECB_KEYLEN) * ECB_KEYLEN;
	buf = calloc(enlen, 1);
	buf_t = calloc(enlen, 1);
	if (!buf || !buf_t) {
		printf("LINE %d\n", __LINE__);
		goto out;
	}

   	if (fread(buf, file_size, 1, fp1) != 1) {
		printf("LINE %d\n", __LINE__);
		goto out;
	}

    for (i = 0; i < enlen/ECB_KEYLEN; i++) {
        AES128_ECB_encrypt((unsigned char *)buf + (i*ECB_KEYLEN), gEcbKey, buf_t + (i*ECB_KEYLEN));
    }

	if (fwrite(buf_t, enlen, 1, fp2) != 1) {
		printf("LINE %d\n", __LINE__);
		goto out;
	}
	printf("LINE %d\n", __LINE__);

out:
	printf("LINE %d out\n", __LINE__);
	fclose(fp1);
	fclose(fp2);

	return 0;
}

