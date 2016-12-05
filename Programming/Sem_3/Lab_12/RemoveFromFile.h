//
// Created by lieroz on 05.12.16.
//

#ifndef LAB_12_REMOVEFROMFILE_H
#define LAB_12_REMOVEFROMFILE_H

#include <string.h>

#include <libxml/parser.h>

void RemoveSupplier(const char* file_name, const char* tag_name, xmlDoc* file, xmlNode* root, int primary_key);

void RemoveProduct(const char* file_name, const char* tag_name, xmlDoc* file, xmlNode* root, int primary_key);

void RemoveShipment(const char* file_name, const char* tag_name, xmlDoc* file, xmlNode* root, int primary_key);

void RemoveFromFile(const char* file_name,
                    const char* tag_name,
                    int primary_key,
                    void (* remove)(const char*, const char*, xmlDoc*, xmlNode*, int));

#endif //LAB_12_REMOVEFROMFILE_H
