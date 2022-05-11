#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30

void toSmallLetter(char plaintext[], int ch)
{
    int i;
    for (i = 0; i <ch; i++) {
        if (plaintext[i] > 64 && plaintext[i] < 91)
            plaintext[i] += 32;
    }
}

int noSpace(char* plaintext, int ch)
{
    int i, count = 0;
    for (i = 0; i < ch; i++)
        if (plaintext[i] != ' ')
            plaintext[count++] = plaintext[i];
    plaintext[count] = '\0';
    return count;
}

void gettingKeyTable(char key[], int wy, char keyTable[5][5])
{
    int i, j, k, get = 0, *dicty;

    dicty = (int*)calloc(26, sizeof(int));
    for (i = 0; i < wy; i++) {
        if (key[i] != 'j')
            dicty[key[i] - 97] = 2;
    }

    dicty['j' - 97] = 1;

    i = 0;
    j = 0;

    for (k = 0; k < wy; k++) {
        if (dicty[key[k] - 97] == 2) {
            dicty[key[k] - 97] -= 1;
            keyTable[i][j] = key[k];
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }

    for (k = 0; k < 26; k++) {
        if (dicty[k] == 0) {
            keyTable[i][j] = (char)(k + 97);
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
}

void search(char keyTable[5][5], char x, char y, int arr[])
{
    int i, j;

    if (x == 'j')
        x = 'i';
    else if (y == 'j')
        y = 'i';

    for (i = 0; i < 5; i++) {

        for (j = 0; j < 5; j++) {

            if (keyTable[i][j] == x) {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyTable[i][j] == y) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

int mod5(int x) { return (x % 5); }

int prepare(char str[], int ptrs)
{
    if (ptrs % 2 != 0) {
        str[ptrs++] = 'z';
        str[ptrs] = '\0';
    }
    return ptrs;
}

void encrypt(char str[], char keyTable[5][5], int ch)
{
    int i, x[4];

    for (i = 0; i < ch; i += 2) {

        search(keyTable, str[i], str[i + 1], x);

        if (x[0] == x[2]) {
            str[i] = keyTable[x[0]][mod5(x[1] + 1)];
            str[i + 1] = keyTable[x[0]][mod5(x[3] + 1)];
        }
        else if (x[1] == x[3]) {
            str[i] = keyTable[mod5(x[0] + 1)][x[1]];
            str[i + 1] = keyTable[mod5(x[2] + 1)][x[1]];
        }
        else {
            str[i] = keyTable[x[0]][x[3]];
            str[i + 1] = keyTable[x[2]][x[1]];
        }
    }
}


void PlayfairCipherEncryption(char str[], char key[])
{
    char ch, wy, keyTable[5][5];

    wy = strlen(key);
    wy = noSpace(key, wy);
    toSmallLetter(key, wy);

    ch = strlen(str);
    toSmallLetter(str, ch);
    ch = noSpace(str, ch);

    ch = prepare(str, ch);

    gettingKeyTable(key, wy, keyTable);

    encrypt(str, keyTable, ch);
}

int main()
{
    char str[SIZE], key[SIZE];


    strcpy(key, "Hidden");
    printf("Text of the key to be dispalyed: %s\n", key);


    strcpy(str, "atomicbombs");
    printf("Plain text to be displayed: %s\n", str);


    PlayfairCipherEncryption(str, key);


    printf("Cipher text to be displayed: %s\n", str);

    return 0;
}



