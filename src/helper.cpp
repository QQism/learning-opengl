#include "helper.h"

char *readcontent(const char *filename)
{
    char *fcontent = NULL;

    FILE *fp = fopen(filename, "rb");
    if(fp) {
        fseek(fp, 0L, SEEK_END);
        long fsize = ftell(fp);
        rewind(fp);
        printf("File Size %ld\n", fsize);

        fcontent = (char*) malloc(sizeof(char) * fsize);
        fread(fcontent, 1, fsize, fp);

        // NULL terminator, important to avoid garbage characters randomly
        fcontent[fsize] = 0x0;

        fclose(fp);
    }
    return fcontent;
}
