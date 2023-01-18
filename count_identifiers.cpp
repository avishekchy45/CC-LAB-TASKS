/*
Finding and Counting Occurrences of Valid Identifiers from a .c File
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
    // for (ll i = 0; i < n; i++)
    //     cout << txt[i];
    string out;
    bool sin_line_cmt = false, multi_line_cmt = false;
    for (ll i = 0; i < n; i++)
    {
        if (sin_line_cmt == true && s[i] == '\n')
            sin_line_cmt = false, i+=4;
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
int split_word(FILE *source2)
{
    char temp;
    bool end = false, q = false;
    while ((temp = fgetc(source2)) != EOF)
    {
        // cout << temp << endl;
        // A = 65, Z = 90, a = 97, z = 122
        if (temp == ' ' || temp == ',' || temp == '\n' || temp == ';' || temp == '(' || temp == ')' || temp == '{' || temp == '}' || temp == '[' || temp == ']')
        {
            // cout << "Hi" << endl;
            if (!q)
                end = true;
            else
                txt[i][j++] = temp;
        }
        else if (temp == '"')
        {
            if (!q)
            {
                q = true, j = 0, txt[++i][j++] = temp;
            }
            else
                q = false, txt[i][j++] = temp;
        }
        else
        {
            if (end && !q)
                i++, j = 0, end = false;
            txt[i][j++] = temp;
        }
    }
    // cout << i << " " << j << endl;
    // printf("%d", '.');
    return i;
}

int main()
{
    remove_comment();
    FILE *source2 = freopen("output.c", "r", stdin);
    FILE *destination2 = freopen("output.txt", "w", stdout);
    split_word(source2);
    struct keywords
    {
        char word[10];
        ll occur;
    };
    struct keywords key[] = {"auto", 0, "break", 0, "case", 0, "char", 0, "const", 0, "continue", 0, "default", 0, "do", 0, "double", 0, "else", 0, "enum", 0, "extern", 0, "float", 0, "for", 0, "goto", 0, "if", 0, "int", 0, "long", 0, "register", 0, "return", 0, "short", 0, "signed", 0, "sizeof", 0, "static", 0, "struct", 0, "switch", 0, "typedef", 0, "union", 0, "unsigned", 0, "void", 0, "volatile", 0, "while", 0};

    struct keywords blt_in_func[] = {"scanf", 0, "main", 0, "fscanf", 0, "freopen", 0, "get", 0, "printf", 0, "strcmp", 0, "abort", 0, "asctime", 0, "calloc", 0};

    struct keywords operators[] = {"+", 0, "-", 0, "*", 0, "/", 0, "=", 0, "+=", 0, "-=", 0, "==", 0, "<", 0, ">", 0, "<=", 0, ">=", 0, "%", 0};

    ll total_key = 0, total_func = 0, total_op = 0, total_hd = 0, total_id = 0;
    bool found = false;
    map<string, int> idMap;
    for (ll k = 0; k <= i; k++)
    {
        // cout << txt[k] << endl;
        found = false;
        j = *(&key + 1) - key;
        for (ll l = 0; l < j; l++)
        {
            if (!strcmp(txt[k], key[l].word))
            {
                // cout << "Hi" << endl;
                key[l].occur++, total_key++;
                cout << key[l].word << "\t\t\t\t"
                     << "Keyword" << endl;
                found = true;
                break;
            }
        }
        if (found)
            continue;
        j = *(&blt_in_func + 1) - blt_in_func;
        for (ll l = 0; l < j; l++)
        {
            if (!strcmp(txt[k], blt_in_func[l].word))
            {
                blt_in_func[l].occur++, total_func++;
                cout << blt_in_func[l].word << "\t\t\t"
                     << "Built in Function" << endl;
                found = true;
                break;
            }
        }
        if (found)
            continue;
        j = *(&operators + 1) - operators;
        for (ll l = 0; l < j; l++)
        {
            if (!strcmp(txt[k], operators[l].word))
            {
                operators[l].occur++, total_op++;
                cout << operators[l].word << "\t\t\t\t"
                     << "Operator" << endl;
                found = true;
                break;
            }
        }
        if (found)
            continue;
        if (strstr(txt[k], ".h"))
        {
            total_hd++;
            cout << txt[k] << "\t\t"
                 << "Header" << endl;
            found = true;
        }
        if (found)
            continue;
        bool found_id = true;
        if (isalpha(txt[k][0]))
        {
            // cout << txt[k] << endl;
            ll l = 1;
            while (txt[k][l] != '\0')
            {
                if (!isdigit(txt[k][l]) && !isalpha(txt[k][l]) && txt[k][l] != '_')
                {
                    found_id = false;
                    break;
                }
                l++;
            }
            if (found_id)
            {
                total_id++;
                cout << txt[k] << "\t\t\t\t"
                     << "Identifier" << endl;
                found = true;
                int count = 1;
                pair<map<string, int>::iterator, bool> retrunValue;
                // insert element
                retrunValue = idMap.insert(pair<string, int>(txt[k], count));
                // check if map contains value
                if (retrunValue.second == false)
                {
                    // element already exists
                    ++retrunValue.first->second;
                }
            }
        }
        // cout << key[l].word << endl;
    }
    cout << "\nTotal Identifiers:  " << total_id << endl;
    cout << "No. of Occurrences: " << endl;
    map<string, int>::iterator i;
    for (i = idMap.begin(); i != idMap.end(); ++i)
    {
        cout << i->first << "\t\t\t\t\t" << i->second << endl;
    }
    fclose(source2);
    fclose(destination2);
    return 0;
}
