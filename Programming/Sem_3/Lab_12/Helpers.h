//
// Created by lieroz on 04.12.16.
//

#ifndef LAB_12_HELPERS_H
#define LAB_12_HELPERS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <libxml/parser.h>

void ScanInput(char* buffer, size_t size, const char* name, bool is_null);

bool SearchForPrimaryKey(int primary_key, const char* file_name, const char* tag_name);

bool SearchForPair(int supplier_id, int product_id);

#endif //LAB_12_HELPERS_H