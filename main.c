#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"


struct Triad {
    char    triad_block[4];
    int     min_value;
    int     mid_value;
    int     max_value;
};


struct Triad *triadConstructor(char *triadBlock, int minValue, int midValue, int maxValue)
{
    struct Triad *triad = malloc(sizeof(struct Triad));
    
    strncpy(triad->triad_block, triadBlock, 3); // Copy the content of triadBlock to triad->triad_block

    triad->triad_block[3] = '\0'; // Guarantee the string ends with null value

    triad->min_value = minValue;
    triad->mid_value = midValue;
    triad->max_value = maxValue;

    return triad;
}

// struct DictionaryBase Dictionary[] -> Dictionary is already usable

int main()
{
    struct Triad *myTriad = triadConstructor("ABC", 1, 2, 3);

    if (myTriad != NULL) {
        printf("Triad block: %s\n", myTriad->triad_block);
        printf("Min value: %d\n", myTriad->min_value);
        printf("Mid value: %d\n", myTriad->mid_value);
        printf("Max value: %d\n", myTriad->max_value);
        
        free(myTriad);
    } else {
        printf("Failed to allocate memory for Triad\n");
    }
    return 0;
}
