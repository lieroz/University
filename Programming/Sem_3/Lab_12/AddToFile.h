//
// Created by lieroz on 04.12.16.
//

#ifndef LAB_12_ADDTOFILE_H
#define LAB_12_ADDTOFILE_H

#include <libxml/parser.h>
#include <assert.h>

#include "Helpers.h"

void AddSupplier(const char* file_name, xmlDoc* file, xmlNode* root);

void AddProduct(const char* file_name, xmlDoc* file, xmlNode* root);

void AddShipment(const char* file_name, xmlDoc* file, xmlNode* root);

void AddToFile(const char* file_name, void (*add)(const char*, xmlDoc*, xmlNode*));

#endif //LAB_12_ADDTOFILE_H
