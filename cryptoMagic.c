#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fp1;
FILE *fp2;
int encrypt(char *);
int decrypt(char *);

int main(int argc, char *argv[])
{
    char *E = "-E";
    char *D = "-D";
    char *argv1 = argv[1];
    if (strcmp(argv1, E) == 0)
    {
        encrypt(argv[2]);
    }
    else if (strcmp(argv1, D) == 0)
    {
        decrypt(argv[2]);
    }
    else
    {
        encrypt(argv[2]);
    }

    return 0;
}
int encrypt(char *filename)
{
    char hex[] = "00";
    printf("\n");
    fp1 = fopen(filename, "r");
    if (fp1 == NULL)
    {
        printf("Cannot find source file!!\n");
    }
    fp2 = fopen("encp.crp", "w");
    if (fp2 == NULL)
    {
        printf("Cannot find target file!!\n");
    }
    while (1)
    {
        char ch = fgetc(fp1);

        if (feof(fp1))
        {
            break;
        }
        else
        {

            int ascii = ch;
            if (ascii == 10)
            {
                char *ch;
                ch = "TT";
                fputs(ch, fp2);
            }
            else
            {
                int outChar = ascii - 16;
                if (outChar < 32)
                    outChar = (outChar - 32) + 144;
                sprintf(hex, "%X", outChar);
                fputs(hex, fp2);
            }
        }
    }
    fclose(fp1);
    fclose(fp2);
    printf("\n");
    return 0;
}

int decrypt(char *filename)
{
    int outChar;
    char hex[2];
    printf("\n");
    fp1 = fopen(filename, "r");
    if (fp1 == NULL)
    {
        printf("Source file could not be found\n");
    }
    fp2 = fopen("decp.txt", "w");
    if (fp2 == NULL)
    {
        printf("Target file could not be found\n");
    }
    while (1)
    {
        if (feof(fp1))
        {
            break;
        }
        for (int i = 0; i < 2; i++)
        {
            hex[i] = fgetc(fp1);
        }
        hex[2] = '\0';
        if (hex == "TT")
        {
            outChar = 10;
        }
        else
        {
            sscanf(hex, "%x", &outChar);
            // printf("%x %s\n",outChar,hex);
            outChar = outChar + 16;
            if (outChar > 127)
                outChar = (outChar - 144) + 32;
            // printf("Char:%c\n",ch);
        }
        char ch = outChar;
        fputc(ch, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    printf("\n");
    return 0;
}
