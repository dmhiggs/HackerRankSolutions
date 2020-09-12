#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight; //fixed
	int max_weight; //fixed
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;



void print_all_packages(town t) {
    //offices list pointer, offices count --> packes pointer, count --> id
    printf("%s:\n", t.name);

    int ocount = t.offices_count;
    for (int i = 0; i < ocount; i++) {
        printf("\t%d:\n", i);

        int pcount = t.offices[i].packages_count;
        for (int j = 0; j < pcount; j++) {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
    //from source.office[i] to target...etc
    //id , weight
    //check against p weight, packages, count against po

    post_office *srcPO = &source->offices[source_office_index];
    post_office *trgPO = &target->offices[target_office_index];
    
    package *p = malloc(srcPO->packages_count * sizeof(package) + 1);
    package *pt = malloc((srcPO->packages_count + trgPO->packages_count) * sizeof(package) + 1);
    int count = 0;
    int countt = 0;

    for (int i = 0; i < trgPO->packages_count; i++) {
        pt[i].id = trgPO->packages[i].id;
        pt[i].weight = trgPO->packages[i].weight;
        countt++;
    }

    int trgMin = trgPO->min_weight;
    int trgMax = trgPO->max_weight;
    for (int i = 0; i < srcPO->packages_count; i++) {

        //assuming that the source post office wouldn't accept weights that didn't fit their own guidelines

        int weight = srcPO->packages[i].weight;
        if (weight >= trgMin && weight <= trgMax) {
            //add package to moving list
            pt[countt].id = srcPO->packages[i].id;
            pt[countt].weight = weight;
            //increment count
            countt++;
        }
        else {
            //add package to keep list
            p[count].id = srcPO->packages[i].id;
            p[count].weight = weight;
            //increment count
            count++;
        }
    }

    if (countt > trgPO->packages_count) {
        trgPO->packages = realloc(trgPO->packages, countt * sizeof(package));
        trgPO->packages_count = countt;
        target->offices[target_office_index].packages_count = countt;
        trgPO->packages = pt;

        srcPO->packages = realloc(srcPO->packages, count * sizeof(package));
        srcPO->packages_count = count;
        source->offices[source_office_index].packages_count = count;
        srcPO->packages = p;
    }
}

town town_with_most_packages(town* towns, int towns_count) {
    int max = 0;
    town *mostP = &towns[0];

    for (int i = 0; i < towns_count; i++) {
        town t = towns[i];
        int ocount = t.offices_count;

        int current = 0;

        for (int j = 0; j < ocount; j++) {
            current += t.offices[j].packages_count;
        }

        if (current > max) {
            max = current;
            mostP = &towns[i];
        }
    }

    return *mostP;
}

town* find_town(town* towns, int towns_count, char* name) {
    //guaranteed town exists
    for (int i = 0; i < towns_count; i++) {
        if (strcmp(towns[i].name, name) == 0) {
            return &towns[i];
        }
    }
    return &towns[0]; //since it says it's guaranteed the town exists this shouldn't ever run
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}
