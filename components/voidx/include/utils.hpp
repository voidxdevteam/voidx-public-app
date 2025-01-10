#pragma once
#include <stdio.h>
#include <string>

#define SEC_TO_USEC(x) (1000*1000*x)
#define MSEC_TO_USEC(x) (1000*x)
#define STR_TO_RGB(str) ((int)strtol(str.c_str(), 0, 16))

int tryParseInt(char *str, int *output, char end);
std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
int count(std::string s, char c);

#define SERIALIZATION_STR_MAX_LEN 24

typedef struct {
    char * stream_ptr;
    char * data_ptr;
    char * next_ptr;
    char * name;
    char * parent;
    int version;
    int stream_size;
    int data_size;
} SERIALIZATION_DATA;

int serialize_encrypt(SERIALIZATION_DATA* stream, const char key[32]);
int serialize_decrypt(SERIALIZATION_DATA* stream, const char key[32]);
int serialization_check(SERIALIZATION_DATA * info, const char * name, int version);
int serialize(char * stream, const char * name, char * data, int size, int version, SERIALIZATION_DATA * info);
int serialize_internal(SERIALIZATION_DATA * stream, const char * name, char * data, int size, int version, SERIALIZATION_DATA * info);
int deserialize(char * stream, SERIALIZATION_DATA * info);
int deserialize_internal(SERIALIZATION_DATA * stream, SERIALIZATION_DATA * info);
int deserialize_next(SERIALIZATION_DATA * info);

