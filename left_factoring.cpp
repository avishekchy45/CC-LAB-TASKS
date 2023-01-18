/*
Performing Left Factoring in a Grammar
*/

#include <bits/stdc++.h>
using namespace std;
int main()
{
    FILE *source = freopen("input.txt", "r", stdin);
    FILE *destination = freopen("output.txt", "w", stdout);
    int n;
    cout << "Enter No. of Productions: ";
    cin >> n;
    cout << n << endl;
    char left[500][500], right[500][500];
    for (int m = 0; m < n; m++)
    {
        cout << "Production " << m + 1 << ": ";
        scanf("%1s -> %s", left[m], right[m]);
        cout << left[m] << " -> " << right[m] << endl;
    }
    cout << "Grammar after performing left factoring:" << endl;
    for (int m = 0; m < n; m++)
    {
        int i = 0, j = 0, k = 0, l = 0;
        char temp1[500], temp2[500], production[500], new_prod[500], temp[500];
        bool factoring = false;
        for (i = 0; right[m][i] != '|'; i++)
            temp1[j++] = right[m][i];
        temp1[j] = '\0';
        for (j = ++i, i = 0; right[m][j] != '\0'; j++)
            temp2[i++] = right[m][j];
        temp2[i] = '\0';
        for (i = 0; i < strlen(temp1) || i < strlen(temp2); i++)
        {
            if (temp1[i] == temp2[i])
            {
                factoring = true;
                production[k++] = temp1[i];
            }
            else
            {
                new_prod[l] = temp1[i];
                temp[l] = temp2[i];
                l++;
            }
        }
        production[k++] = left[m][0], production[k++] = '\'', production[k] = '\0';
        temp[l] = '\0';
        new_prod[l++] = '|', new_prod[l] = '\0';
        strcat(new_prod, temp);
        if (strlen(production) - 2 == strlen(temp1))
            strcat(new_prod, "|(e)");
        if (strlen(production) - 2 == strlen(temp2))
            strcat(new_prod, "(e)");
        if (factoring == true)
        {
            cout << left[m] << " -> " << production << endl;
            cout << left[m] << "' -> " << new_prod << endl;
        }
        else
            cout << "Left Factoring can't be performed on Production " << m + 1 << endl;
    }
    fclose(source);
    fclose(destination);
    return 0;
}