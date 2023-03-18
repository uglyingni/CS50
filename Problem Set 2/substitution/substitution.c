#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool check_argv(string argv);
int main(int argc, string argv[])
{
    if (argc != 2 || check_argv(argv[1]) == false) //確實輸入argv[1]且沒有輸入錯誤(argv[0]是./substitution)
    {
        return 1;
    }
    else
    {
        string plain = get_string("plaintext:  ");
        printf("ciphertext: ");
        for (int j = 0; j < strlen(plain); j++)
        {
            if (isupper(plain[j]))
            {
                printf("%c", toupper(argv[1][plain[j] - 65]));
            }
            else if (islower(plain[j]))
            {
                printf("%c", tolower(argv[1][plain[j] - 97]));
            }
            else
            {
                printf("%c", plain[j]);
            }
        }
        printf("\n");
        return 0;
    }
}

bool check_argv(string argv)
{
    int check = 0;
    for (int i = 0; i < strlen(argv); i++)
    {
        check += toupper(argv[i]) - 65; //都變成大寫就可以不用寫if-else區分大小寫
        for (int j = 1; j < strlen(argv) - i; j++) //確認multiple duplicate char(可能有字元數=26且加總=325情形)
        {
            if (toupper(argv[i]) == toupper(argv[i + j])) //每個字元跟後面字元比較
            {
                return false;
            }
        }
    }
    if (check != 325 || strlen(argv) != 26) //如果不是英文字母(0+1+...+26)就不會是325
    {
        return false;
    }
    return true;
}