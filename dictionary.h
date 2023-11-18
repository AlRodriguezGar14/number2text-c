#ifndef DICTIONARY_H
#define DICTIONARY_H

struct DictionaryBase
{
    const char  *key;
    const char  *value;
};

extern struct DictionaryBase Dictionary[];

#endif
