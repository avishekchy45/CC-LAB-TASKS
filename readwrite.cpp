/*
Reading a .c File and Writing the Contents in a .txt File
*/

#include <bits/stdc++.h>
using namespace std;
int main()
{
    char txt;
    FILE *source = freopen("input.c", "r", stdin);
    FILE *destination = freopen("output.txt", "wt", stdout);
    if (source == NULL)
    {
        cout << "File Not Found.";
        return 0;
    }
    while ((txt = fgetc(source)) != EOF)
    {
        cout << txt;
    }
    cout << endl;
    fclose(source);
    fclose(destination);
    return 0;
}
