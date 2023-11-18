#include <stdio.h>
#include "dictionary.h"

int main()
{
    for (int i = 0; Dictionary[i].key != 0; i++)
    {
        printf("Dict key %s\ndict value %s\n\n", Dictionary[i].key, Dictionary[i].value);
    }
    return 0;
}
