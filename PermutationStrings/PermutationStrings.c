#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/
    int tempi = 0;
    int inReverse = 1;

    for (int i = 0; i + 1 < n; i++) {
        if (strcmp(s[n-1-i],s[n-2-i]) > 0 && inReverse) {
            inReverse = 0;
            tempi = n - 2 - i;
        }
    }

    if (inReverse) {
        return 0;
    }


    //big change... p r r w w y --> ... --> p y w w r r --> r p r w w y
    int i = n - 1;
    while (strcmp(s[tempi], s[i]) >= 0 && i > 0) {
        if (s[tempi] == s[i]) {
            tempi--;
            continue;
        }
        i--;
    }

    //flip
    int len = 11;
    char placeholder[len];
    strcpy(placeholder, s[tempi]);
    strcpy(s[tempi], s[i]);
    strcpy(s[i], placeholder);

    // printf("%s %s\n", s[tempi], s[i]);

    //sort everything after temp
    for (int j = 0; j < n - 1; j++) {
        for (int k = tempi + 1; k < n - j - 1; k++) {
            if (strcmp(s[k], s[k+1]) > 0) {
                //swap
                char holder[len];
                strcpy(holder, s[k]);
                strcpy(s[k], s[k+1]);
                strcpy(s[k+1], holder);
            }
        }
    }

    return 1;
}

int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}