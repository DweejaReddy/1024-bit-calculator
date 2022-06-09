#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 310       //[1024*0.301] = 308 ......Since 1024 bits contain at max 309 digits, 310 is taken as a round figure

//      /* declarations of all functions
void reverse(char s[]);
void ignore_zeros(char a[]);
int compare(char str1[], char str2[]);
void addition(char a[], char b[], int status);
void difference(char str1[], char str2[]);
void product(char str1[], char str2[]);
//                                      */

void reverse(char str[])      // reverses the string
{
    int n = strlen(str);
    for(int i = 0; i < n/2; ++i)
    {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

 // used to ignore all the unneccessary zeroes in the start of a number, if any
void ignore_zeros(char s[])    
{
    int n = strspn(s, "0");
    char s1[310];
    int j = 0;
    for(int i = n; s[i] != '\0'; ++i)
    {
        s1[j++] = s[i];
    }
    s1[j] = '\0';
    strcpy(s, s1);
}


int compare(char str1[], char str2[])
{
    // Calculate lengths of both string
    int n1 = strlen(str1), n2 = strlen(str2);
    if(n1 < n2)
        return 1;
    if(n2 < n1)
        return 0;
    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return 1;
        else if (str1[i] > str2[i])
            return 0;

    return 0;
}


void addition(char s1[], char s2[], int status)
{
    int first_char1 = 0, first_char2 = 0;         //declared for iterations. 
    if(s1[0] == '-' && s2[0] == '-')
    {
        first_char1 = 1;
        first_char2 = 1;                          // changed to 1 only if both numbers are negative so that iteration is done till that number before 1
    }
    else if(s1[0] == '-')
    {
        s1[0] = '0';                           // minus removed for simpler addition
        ignore_zeros (s1);
        return difference(s2, s1);
    }
    else if(s2[0] == '-')
    {
        s2[0] = '0';                           // minus removed for simpler addition
        ignore_zeros (s2);
        return difference(s1, s2);
    }
    int m = strlen(s1);
    int n = strlen(s2);
    char final[SIZE];
    int i = 0;
    int carry = 0;
    while(m > first_char1 && n > first_char2)
    {
        int x = s1[m - 1] - '0';
        int y = s2[n - 1] - '0';
        int val = x + y + carry;                     // initially carry is 0
        carry = val / 10;                            // if sum > 10 carry is taken as val/10
        val = val % 10;
        char c = val + '0';
        final[i] = c;
        i++;
        m--;
        n--;
        if(i > 310)
        {
            printf("Size not supported!! Enter lesser digit numbers\n");
            return ;
        }
    }
    while(m > first_char1)                          // same procedure like the above one
    {
        int x = s1[m - 1] - '0';
        int val = x + carry;
        carry = val / 10;
        val = val % 10;
        char c = val + '0';
        final[i] = c;
        i++;
        m--;
        if(i > 310)
        {
            printf("Size not supported!! Enter lesser digit numbers\n");
            return ;
        }
    }
    while(n > first_char2)                  // same procedure like the above one
    {
        int x = s2[n - 1] - '0';
        int val = x + carry;
        carry = val / 10;
        val = val % 10;
        char c = val + '0';
        final[i] = c;
        i++;
        n--;
        if(i > 310)
        {
            printf("Size not supported!! Enter lesser digit numbers\n");
            return ;
        }
    }
    if(carry > 0)
    {
        final[i] = carry + '0';                   // if final carry is > 0
        i++;
        if(i > 310)
        {
            printf("Size not supported!! Enter lesser digit numbers\n");
            return ;
        }
    }
    final[i] = '\0';
    reverse(final);
    ignore_zeros (final);
    if(strlen(final) == 0)
    {
        printf("0\n");
        return;
    }
    printf("Answer is: \n");
    if((first_char1 == 1 && first_char2 == 1) || (status == 1))
        printf("-");
    printf("%s\n", final);
}


void difference(char str1[], char str2[])
{
    int flag = 0;
    if(str1[0] == '-' && str2[0] != '-')
    {
        str1[0] = '0';
        ignore_zeros (str1);
        addition(str1, str2, 1);
    }
    else if(str1[0] != '-' && str2[0] == '-')
    {
        str2[0] = '0';
        ignore_zeros (str2);
        addition(str1, str2, 0);
    }
    else
    {
        if(str1[0] == '-' && str2[0] == '-')
        {
            str1[0] = '0';
            str2[0] = '0';
            ignore_zeros (str1);
            ignore_zeros (str2);
            difference(str2, str1);
        }
        else
        {
            if (compare(str1, str2))
            {
                char temp[SIZE];
                strcpy(temp, str1);
                strcpy(str1, str2);
                strcpy(str2, temp);
                flag = 1;
            }
            char str[SIZE] = "";
            int n1 = strlen(str1), n2 = strlen(str2);
            reverse(str1);
            reverse(str2);
            int carry = 0;
            int k = 0;
            // Run loop till small string length
            // and subtract digit of str1 to str2
            for (int i = 0; i < n2; i++)
            {
                int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);
                if (sub < 0)
                {
                    sub = sub + 10;
                    carry = 1;
                }
                else
                    carry = 0;
                    str[k++] = sub + '0';
                    if(k > 310)
                    {
                        printf("Size not supported!! Enter lesser digit numbers\n");
                        return ;
                    }
            }

            // subtracting remaining digits of bigger number
            for (int i = n2; i < n1; i++)
            {
                int sub = ((str1[i] - '0') - carry);

                
                if (sub < 0)
                {
                    sub = sub + 10;
                    carry = 1;
                }
                else
                carry = 0;
                str[k++] = sub + '0';
                if(k > 310)
                {
                    printf("Size not supported!! Enter lesser digit numbers\n");
                    return ;
                }
            }
            str[k] = '\0';
            // reverse resultant string
            reverse(str);
            ignore_zeros (str);
            printf("Answer is: \n");
            if(flag == 1)
                printf("-");
            printf("%s\n", str);
        }
    }
}


void product(char str1[], char str2[])
{
	int i,j;
    int sign_status = 1;        // Used to set the sign of the answer based on two inputs
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if(len1 + len2 > 310)
    {
        printf("Size not supported!! Enter lesser digit numbers\n");
        return;
    }
    if((len1 == 1 && str1[0] == '0') || (len2 == 1 && str2[0] == '0'))
    {
        printf("0\n");
        return;
    }
    else
    {
        if(str1[0] == '-' && str2[0] == '-')
        {
            str1[0] = '0';
            str2[0] = '0';
            sign_status = 1;       // sign_status is 1 if answer is positive else 0
        }
        else if(str1[0] == '-')
        {
            str1[0] = '0';
            sign_status = 0;
        }
        else if(str2[0] == '-')
        {
            str2[0] = '0';
            sign_status = 0;
        }
        ignore_zeros (str1);
        ignore_zeros (str2);       //removing the zeros and taking new length
        len1 = strlen(str1);
        len2 = strlen(str2);
        int final[SIZE] = {0};
        for(i = len1 - 1; i >= 0; i--)
        {
            for(j = len2 - 1; j >= 0; j--)
            {
                final[i+j+1]+=(str1[i]-'0')*(str2[j]-'0');       // product aof i and j indices will appear at i+j or i+j+1 indices
                final[i+j]+=final[i+j+1]/10;
                final[i+j+1]%=10;
            }
        }
        int i = 0;
        while(i < len1 + len2 && final[i] == 0)
            i++;
        char s[SIZE];
        int j = 0;
        while(i < len1 + len2)
        {
            s[j++] = final[i++] + '0';
        }
        s[j] = '\0';
        ignore_zeros (s);
        if(strlen(s)  == 0)
        {
            printf("0\n");
            return;
        }
        printf("Answer is: \n");
        if(sign_status == 0)
            printf("-");
        printf("%s\n", s);
        return;
    }
    return;
}

int main()
{
    while(1)
    {
         printf("/----------------------------------------------------------------------------------/\n");
        printf("Enter the operations you want to perform\n1). For Addition\n2). For Subtraction\n3). For multiplication\n4).Exit\n");
        int n;
        scanf("%d", &n);
        if(n < 1 || n > 3)
            return 0;
        printf("--------------------------------------------------------------------------------\n");
        char str1[SIZE], str2[SIZE];
        printf("Enter 1st number\n");
        scanf("%s", str1);
        printf("Enter 2nd number\n");
        scanf("%s", str2);
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        if(len1 > 310 || len2 > 310)
        {
            printf("Size not supported!! Enter lesser digit numbers\n");
        }
        else
        {
            if(n == 1)
                addition(str1, str2, 0);
            else if(n == 2)
                difference(str1, str2);
            else if(n == 3)
                product(str1, str2);
            else
                return 0;
        }
    }
    return 0;
}