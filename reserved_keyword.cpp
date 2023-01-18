/*
Finding and Counting Reserved Keywords from a .c File
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long int
int remove_comment()
{
    char s[65535];
    FILE *source = freopen("input.c", "r", stdin);
    FILE *destination = freopen("output.c", "w", stdout);
    if (source == NULL)
    {
        cout << "File Not Found.";
        return 0;
    }
    ll n = 0;
    while ((s[n] = fgetc(source)) != EOF)
    {
        n++;
    }
    string out;
    bool sin_line_cmt = false, multi_line_cmt = false;
    for (ll i = 0; i < n; i++)
    {
        if (sin_line_cmt == true && s[i] == '\n')
            sin_line_cmt = false, i += 4;
        else if (multi_line_cmt == true && s[i] == '*' && s[i + 1] == '/')
            multi_line_cmt = false, i++;
        else if (sin_line_cmt || multi_line_cmt)
            continue;
        else if (s[i] == '/' && s[i + 1] == '/')
            sin_line_cmt = true, i++;
        else if (s[i] == '/' && s[i + 1] == '*')
            multi_line_cmt = true, i++;
        else
            out += s[i];
    }
    cout << out;
    fclose(source);
    fclose(destination);
    return n;
}
char txt[1500][1300];
ll i = 0, j = 0;
int split_word()
{
    FILE *source2 = freopen("output.c", "r", stdin);
    FILE *destination2 = freopen("output.txt", "w", stdout);
    char temp;
    bool end = false;
    while ((temp = fgetc(source2)) != EOF)
    {
        // cout << temp << endl;
        // A = 65, Z = 90, a = 97, z = 122
        if ((temp < 'A' || temp > 'z') || (temp > 'Z' && temp < 'a'))
        {
            // cout << "Hi" << endl;
            end = true;
        }
        else
        {
            if (end)
                i++, j = 0, end = false;
            txt[i][j++] = temp;
        }
    }
    // cout << i << " " << j << endl;
    // printf("%d", '.');
    // fclose(source2);
    // fclose(destination2);
    return i;
}
int main()
{
    remove_comment();
    split_word();
    struct keywords
    {
        char word[10];
        ll occur;
    };
    struct keywords key[] = {"auto", 0, "break", 0, "case", 0, "char", 0, "const", 0, "continue", 0, "default", 0, "do", 0, "double", 0, "else", 0, "enum", 0, "extern", 0, "float", 0, "for", 0, "goto", 0, "if", 0, "int", 0, "long", 0, "register", 0, "return", 0, "short", 0, "signed", 0, "sizeof", 0, "static", 0, "struct", 0, "switch", 0, "typedef", 0, "union", 0, "unsigned", 0, "void", 0, "volatile", 0, "while", 0};
    ll total = 0;
    j = *(&key + 1) - key;
    for (ll k = 0; k <= i; k++)
    {
        for (ll l = 0; l < j; l++)
        {
            if (!strcmp(txt[k], key[l].word))
            {
                // cout << "Hi" << endl;
                key[l].occur++, total++;
                break;
            }
            // cout << txt[k] << endl;
            // cout << key[l].word << endl;
        }
        // cout << txt[k] << endl;
    }
    for (i = 0; i < j; i++)
    {
        if (key[i].occur != 0)
            cout << key[i].word << "\t" << key[i].occur << endl;
        // printf("  %s\t  %d\n", key[i].word, key[i].occur);
    }
    cout << "Total Keywords: " << total << endl;
    return 0;
}
