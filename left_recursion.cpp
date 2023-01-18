/*
Finding & Removing Left Recursion from Given Grammar
*/

#include <bits/stdc++.h>
using namespace std;
int main()
{
    FILE *source = freopen("input.txt", "r", stdin);
    FILE *destination = freopen("output.txt", "w", stdout);
    char left[500], right[500];
    cout << "Enter Productions of the Grammar: ";
    scanf("%1s->%s", left, right);
    cout << left << "->" << right << endl;
    int i = 0, len_prod = strlen(right), j = 0, k = 0;
    char temp[500], production[500][500], new_prod[500][500];
    bool recursion = false;
    // cout<<len_prod;
    while (sscanf(right + i, "%[^|]s", temp) == 1 && i <= len_prod)
    {
        if (temp[0] != left[0])
        {
            sprintf(production[k++], "%s->%s%s'\0", left, temp, left);
        }
        else
        {
            recursion = true;
            sprintf(new_prod[j++], "%s'->%s%s'\0", left, temp + 1, left);
        }
        i += strlen(temp) + 1;
    }
    if (recursion == true)
    {
        sprintf(new_prod[j++], "%s'->(e)", left);
        cout << "Grammar after removing left recursion:" << endl;
        for (i = 0; i < k; i++)
            cout << production[i] << endl;
        for (i = 0; i < j; i++)
            cout << new_prod[i] << endl;
    }
    else
        cout << "Given grammar has no productions containing left recursion." << endl;
    fclose(source);
    fclose(destination);
    return 0;
}
