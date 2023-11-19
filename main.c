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
    triad->next = NULL;
    struct Triad *last = &container->head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = triad;
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

void appendString(char *out, const char *str) {
    strcat(out, str);
    strcat(out, " ");
}

struct ListNode {
    char value[50];
    struct ListNode* next;
};

struct ListNode* createNode(const char* value) {
    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    strcpy(newNode->value, value);
    newNode->next = NULL;
    return newNode;
}

void appendToList(struct ListNode** head, const char* value) {
    struct ListNode* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct ListNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printListReverse(struct ListNode* head) {
    if (head == NULL) {
        return;
    }
    printListReverse(head->next);
    printf("%s", head->value);
}

void freeList(struct ListNode* head) {
    struct ListNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printNumber(struct Container* container, struct ListNode** list) {

    struct Triad* curr = &container->head;
    char str_max[4];
    char mid_min[3];
    char single[3];
    char single_mid[3];
    char tmp_str[256];
    int idx = 0; // The idx needs to increase to reverse the order when printing

    // Keeping in mind that I have to reverse the content block by block, I have to also reverse the logic
    // To print from hundreths to triad_block, i first attach the triad block, then the dec, num, and then the cents
    while (curr != NULL) {
        printf("Debug: Triad block: %s, Min: %d, Mid: %d, Max: %d\n", curr->triad_block, curr->min_value, curr->mid_value, curr->max_value);
        if (strcmp(curr->triad_block, "1") != 0 && (curr->max_value + curr->mid_value + curr->min_value) != 0) {
            sprintf(tmp_str, "%s ", findValueByKey(curr->triad_block, Dictionary, 100));
            appendToList(list, tmp_str);
            idx++;
        }

        if (curr->mid_value + curr->min_value <= 20 && curr->mid_value + curr->min_value != 0) {
            sprintf(mid_min, "%d", curr->mid_value + curr->min_value);
            sprintf(tmp_str, "%s ", findValueByKey(mid_min, Dictionary, 100));
            appendToList(list, tmp_str);
            idx++;

        } else if (curr->min_value == 0 && curr->mid_value != 0) {
            sprintf(single, "%d", curr->mid_value);
            sprintf(tmp_str, "%s ", findValueByKey(single, Dictionary, 100));
            appendToList(list, tmp_str);
            idx++;

        } else if (curr->mid_value == 0 && curr->min_value != 0) {
            sprintf(single, "%d", curr->min_value);
            sprintf(tmp_str, "%s ", findValueByKey(single, Dictionary, 100));
            appendToList(list, tmp_str);
            idx++;

        } else if (curr->min_value != 0 && curr->mid_value != 0) {
            sprintf(single, "%d", curr->min_value);
            sprintf(single_mid, "%d", curr->mid_value);
            sprintf(tmp_str, "%s-%s ", findValueByKey(single_mid, Dictionary, 100),
                    findValueByKey(single, Dictionary, 100));
            appendToList(list, tmp_str);
            idx++;
        }

        if (curr->max_value > 0) {
            sprintf(str_max, "%d", curr->max_value);
            sprintf(tmp_str, "%s %s ", findValueByKey(str_max, Dictionary, 100), findValueByKey("100", Dictionary, 100));
            appendToList(list, tmp_str);
            idx++;
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

int main() {
    struct Container* triad_container = malloc(sizeof(struct Container));
    struct ListNode* list = NULL;
    char *input;

    // Allocate memory for the input string
    input = (char *)malloc(256 * sizeof(char));  // Adjust the size as needed

    if (input == NULL) {
        printf("Memory allocation failed.\n");
        return 1;  // Exit with an error code
    }

    printf("Enter your number: ");
    scanf("%s", input);

    // Free the allocated memory

    generateTriad(input, triad_container);

    free(input);

    printNumber(triad_container, &list);

    printListReverse(list);

    freeList(list);
    free(triad_container);
    return 0;
}
