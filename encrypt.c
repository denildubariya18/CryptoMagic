#include <stdio.h>
#include <stdlib.h>
FILE *fp1;
FILE *fp2;
int encrypt(void);
int decrypt(void);

int main()
{
    printf("Enter 'E' for encryption or 'D' for decryption:\n");
    char ch;
    scanf("%c", &ch);
    if (ch == 'D' || ch == 'd')
    {
        decrypt();
    }
    else
    {
        encrypt();
    }

    return 0;
}
int encrypt()
{

    // This the code for the encryption
    char hex[50];
    printf("\n");
    fp1 = fopen("encp.txt", "r"); // opening the file to be encrypted
    if (fp1 == NULL)
    {
        printf("Cannot find source file!!\n");
    }
    fp2 = fopen("encp.crp", "w"); // Opening the file where the encrypted file will be stored
    if (fp2 == NULL)
    {
        printf("Cannot find target file!!\n");
    }
    while (1)
    {
        char ch = fgetc(fp1); // Storing each value character by character in ch

        if (feof(fp1)) // When the file pointer reaches at the end of the file it will break the loop
        {
            break;
        }
        else
        {

            int ascii = ch;  // converting the character into its ascii value
            if (ascii == 10) // For the new line we will print "CR" in the encrypted file
            {
                char *ch;
                ch = "CR";
                fputs(ch, fp2);
            }
            else
            {
                int outChar = ascii - 16;
                if (outChar < 32)
                    outChar = (outChar - 32) + 144;
                sprintf(hex, "%X", outChar); // Converting the number into hexadecimal value
                fputs(hex, fp2);
            }
        }
    }
    fclose(fp1);
    fclose(fp2); // Closing the files
    printf("\n");
    return 0;
}

int decrypt()
{
    // This is the code for the decryption.
    int outChar;
    char hex[2]; // Since we need to read two characters at the same time.
    printf("\n");
    fp1 = fopen("decp.crp", "r"); // opening the encrypted file
    if (fp1 == NULL)
    {
        printf("Source file could not be found\n");
    }
    fp2 = fopen("decp.txt", "w"); // opening the file where decrypted text will be stored
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
        for (int i = 0; i < 2; i++) // Storing the two characters into hex string
        {
            hex[i] = fgetc(fp1);
        }
        hex[2] = '\0';
        if (hex == "CR") // For the new line
        {
            outChar = 10;
        }
        else
        {
            sscanf(hex, "%x", &outChar); // Converting the hexadecimal value into the decimal value, i.e. its ascii value
            outChar = outChar + 16;
            if (outChar > 127)
                outChar = (outChar - 144) + 32;
        }
        char ch = outChar; // Converting the ascii value into character
        fputc(ch, fp2);
    }
    fclose(fp1);
    fclose(fp2); // Closing the files
    printf("\n");
    return 0;
}