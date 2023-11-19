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
   struct Triad *current = &container->head;
    while (current != NULL) {
        printf("Triad block: %s\n", current->triad_block);
        printf("Min value: %d\n", current->min_value);
        printf("Mid value: %d\n", current->mid_value);
        printf("Max value: %d\n", current->max_value);
        printf("\n");
        current = current->next;
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
            dec = atoi(&str_dec);
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
    printTriads(triad_container);

    free(triad_container);
    return 0;
}
