/*
Removing Comments from a .c File and Create a New .c File
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long int
int main()
{
    char txt[65535];
    FILE *source = freopen("input.c", "r", stdin);
    FILE *destination = freopen("output.c", "w", stdout);
    if (source == NULL)
    {
        cout << "File Not Found.";
        return 0;
    }
    ll n = 0;
    while ((txt[n] = fgetc(source)) != EOF)
    {
        n++;
    }
    // for (ll i = 0; i < n; i++)
    //     cout << txt[i];
    string out;
    bool sin_line_cmt = false, multi_line_cmt = false;
    for (ll i = 0; i < n; i++)
    {
        if (sin_line_cmt == true && txt[i] == '\n')
            sin_line_cmt = false, i += 4;
        else if (multi_line_cmt == true && txt[i] == '*' && txt[i + 1] == '/')
            multi_line_cmt = false, i++;
        else if (sin_line_cmt || multi_line_cmt)
            continue;
        else if (txt[i] == '/' && txt[i + 1] == '/')
            sin_line_cmt = true, i++;
        else if (txt[i] == '/' && txt[i + 1] == '*')
            multi_line_cmt = true, i++;
        else
            out += txt[i];
    }
    cout << out;
    fclose(source);
    fclose(destination);
    return 0;
}
