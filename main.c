#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

struct Triad {
    char    triad_block[30];
    int     min_value;
    int     mid_value;
    int     max_value;
    int     created;
    struct Triad *next;
};

struct Container {
    int             length;
    struct Triad    head;
};

struct Triad *triadConstructor(char *triadBlock, int minValue, int midValue, int maxValue)
{
    struct Triad *triad = malloc(sizeof(struct Triad));
    
    strncpy(triad->triad_block, triadBlock, sizeof(triad->triad_block) - 1);

    triad->triad_block[sizeof(triad->triad_block) - 1] = '\0'; // Guarantee the string ends with null value

    triad->min_value = minValue;
    triad->mid_value = midValue;
    triad->max_value = maxValue;
    triad->next = NULL;
    triad->created = 1;

    return triad;
}

void insertTriad(struct Container *container, struct Triad *triad) {
    if (container->head.created != 1) {
        container->head = *triad;
    } else {
        triad->next = container->head.next;
        container->head.next = triad;
    }
}

void printTriads(struct Container *container) {
   struct Triad *curr = &container->head;
    while (curr != NULL) {
        printf("Triad block: %s\n", curr->triad_block);
        printf("Min value: %d\n", curr->min_value);
        printf("Mid value: %d\n", curr->mid_value);
        printf("Max value: %d\n", curr->max_value);
        printf("\n");
        curr = curr->next;
    }
}

const char *findValueByKey(char *key, struct DictionaryBase *dict, int dictLength) {
    for (size_t i = 0; i < dictLength; i++) {
        if (strcmp(dict[i].key, key) == 0) {
            return dict[i].value;
        }
    }
    return NULL; // Key not found
}

void printNumber(struct Container *container) {

   struct Triad *curr = &container->head;
   char out[256];
   char str_max[4];
   char mid_min[3];
   char single[2];
   char single_mid[3];

    while (curr != NULL) {
        if (curr->max_value > 0) {
            sprintf(str_max, "%d", curr->max_value);
            printf("%s %s ", findValueByKey(str_max, Dictionary, 100), findValueByKey("100", Dictionary, 100)); // use 100 as dict size until I know a way to calculate it

        }

        if (curr->mid_value + curr->min_value <= 20 && curr->mid_value + curr->min_value != 0) {
            sprintf(mid_min, "%d", curr->mid_value + curr->min_value);
            printf("%s ", findValueByKey(mid_min, Dictionary, 100));
        } else if (curr->min_value == 0 && curr->mid_value != 0) {
            sprintf(single, "%d", curr->mid_value);
            printf("%s ", findValueByKey(single, Dictionary, 100));
        } else if (curr->mid_value == 0 && curr->min_value != 0) {
            sprintf(single, "%d", curr->min_value);
            printf("%s ", findValueByKey(single, Dictionary, 100));
        } else if (curr->min_value != 0 && curr->mid_value != 0) {
            sprintf(single, "%d", curr->min_value);
            sprintf(single_mid, "%d", curr->mid_value);
            printf("%s-%s ", findValueByKey(single_mid, Dictionary, 100), findValueByKey(single, Dictionary, 100));
        }
        if (strcmp(curr->triad_block, "1") != 0 && (curr->max_value + curr->mid_value + curr->min_value) != 0) {
            printf("%s ", findValueByKey(curr->triad_block, Dictionary, 100));
        }
        curr = curr->next;
    }
}


void generateTriad(char *input, struct Container *container) {
    
    int idx = 0;
    int total = atoi(input);
    char    triad_block[30] = "1";

    while (input[idx + 1] != '\0')
        idx++;

    while (idx >= 0)
    {
        char str_num = input[idx];
        int num = atoi(&str_num);

        int dec = 0;
        if (idx >= 1) {
            char str_dec = input[idx - 1];
            dec = atoi(&str_dec) * 10;
        }

        int cent = 0;
        if (idx >= 2) {
            char str_cent = input[idx - 2];
            cent = atoi(&str_cent);
        }

        insertTriad(container, triadConstructor(triad_block, num, dec, cent));

        strcat(triad_block, "000");
        idx -= 3;
    }
}


// struct DictionaryBase Dictionary[] -> Dictionary is already usable

int main()
{
    struct Container *triad_container = malloc(sizeof(struct Container));

    generateTriad("4321", triad_container);
    // printTriads(triad_container);
    printNumber(triad_container);

    free(triad_container);
    return 0;
}
