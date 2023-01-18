/*
Calculating FIRST & FOLLOW of Given Grammar
*/

#include <bits/stdc++.h>
using namespace std;

int n, no_of_unique = 500, cnt = 0;
char production[500][500], first_out[500][500], follow_out[500][500], first[500], follow[500];
void firstlist(char, int, int);
void firstfollow(char, int, int);
void followstart(char);

int main()
{
	FILE *source = freopen("input.txt", "r", stdin);
	FILE *destination = freopen("output.txt", "w", stdout);
	cout << "Enter No. of Productions: ";
	cin >> n;
	cout << n << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "Production " << i + 1 << ": ";
		cin >> production[i];
		cout << production[i] << endl;
	}
	cout << endl;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < no_of_unique; j++)
			first_out[i][j] = '!';

	int x = 0, y = 0, kx = 0, calculated = 0;
	char temp, list[n];
	bool done = 0, exist = 0;
	for (int i = 0; i < n; i++)
	{
		temp = production[i][0], y = 0, done = 0;
		for (int j = 0; j < calculated; j++)
			if (temp == list[j])
				done = 1;
		if (done == 1)
			continue;

		list[calculated] = temp, first_out[x][y++] = temp;
		cout << "FIRST(" << temp << ") = { ";
		firstlist(temp, 0, 0);

		for (int k = kx; k < cnt; k++)
		{
			exist = 0;
			for (int l = 0; l < y; l++)
			{
				if (first[k] == first_out[x][l])
				{
					exist = 1;
					break;
				}
			}
			if (exist == 0)
			{
				if (y != 1)
					cout << ", ";
				if (first[k] == '#')
					printf("%c", 238);
				else
					cout << first[k];
				first_out[x][y++] = first[k];
			}
		}
		cout << " }" << endl;
		calculated += 1, kx = cnt, x++;
	}
	printf("\n");

	for (int i = 0; i < n; i++)
		for (int j = 0; j < no_of_unique; j++)
			follow_out[i][j] = '!';

	x = 0, y = 0, kx = 0, calculated = 0;
	char list2[n];
	done = 0, exist = 0;
	cnt = 0;
	for (int i = 0; i < n; i++)
	{
		temp = production[i][0], y = 0, done = 0;
		for (int j = 0; j < calculated; j++)
			if (temp == list2[j])
				done = 1;
		if (done == 1)
			continue;

		list2[calculated] = temp, follow_out[x][y++] = temp;
		cout << "FOLLOW(" << temp << ") = { ";
		followstart(temp);

		for (int k = kx; k < cnt; k++)
		{
			exist = 0;
			for (int l = 0; l < y; l++)
			{
				if (follow[k] == follow_out[x][l])
				{
					exist = 1;
					break;
				}
			}
			if (exist == 0)
			{
				if (y != 1)
					cout << ", ";
				cout << follow[k];
				follow_out[x][y++] = follow[k];
			}
		}
		cout << " }" << endl;
		calculated += 1, kx = cnt, x++;
	}
	fclose(source);
	fclose(destination);
	return 0;
}

void firstlist(char temp, int pos1, int pos2)
{
	if (!isupper(temp))
		first[cnt++] = temp;
	for (int i = 0; i < n; i++)
	{
		if (production[i][0] == temp)
		{
			if (production[i][2] == '#')
			{
				if (production[pos1][pos2] == '\0')
					first[cnt++] = '#';
				else if ((pos1 != 0 || pos2 != 0) && production[pos1][pos2] != '\0')
					firstlist(production[pos1][pos2], pos1, (pos2 + 1));
				else
					first[cnt++] = '#';
			}
			else if (!isupper(production[i][2]))
				first[cnt++] = production[i][2];
			else
				firstlist(production[i][2], i, 3);
		}
	}
}

void firstfollow(char temp, int pos1, int pos2)
{
	if (!(isupper(temp)))
		follow[cnt++] = temp;
	else
	{
		int i = 0, j = 0;
		for (i = 0; i < n; i++)
			if (first_out[i][0] == temp)
				break;

		while (first_out[i][++j] != '!')
		{
			if (first_out[i][j] != '#')
				follow[cnt++] = first_out[i][j];
			else
			{
				if (production[pos1][pos2] == '\0')
					followstart(production[pos1][0]);
				else
					firstfollow(production[pos1][pos2], pos1, pos2 + 1);
			}
		}
	}
}

void followstart(char temp)
{
	if (production[0][0] == temp)
		follow[cnt++] = '$';
	for (int i = 0; i < n; i++)
	{
		for (int j = 2; j < n; j++)
		{
			if (production[i][j] == temp)
			{
				if (production[i][j + 1] != '\0')
					firstfollow(production[i][j + 1], i, (j + 2));
				if (production[i][j + 1] == '\0' && temp != production[i][0])
					followstart(production[i][0]);
			}
		}
	}
}
