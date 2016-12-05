//
// Created by lieroz on 05.12.16.
//

#include "RemoveFromFile.h"

void RemoveSupplier(const char* file_name, xmlDoc* file, xmlNode* root, int primary_key) {
	xmlChar* temp = NULL;
	int compared_key = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "SupplierID")) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == primary_key) {
					xmlUnlinkNode(i);
					xmlFree(i);
				}
			}
		}
	}

	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);

	xmlFree(temp);
}

void RemoveProduct(const char* file_name, xmlDoc* file, xmlNode* root, int primary_key) {
	xmlChar* temp = NULL;
	int compared_key = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "ProductID")) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == primary_key) {
					xmlUnlinkNode(i);
					xmlFree(i);
				}
			}
		}
	}

	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);

	xmlFree(temp);
}

void RemoveShipment(const char* file_name, xmlDoc* file, xmlNode* root, int primary_key) {
	xmlChar* temp = NULL;
	int compared_key = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "ShipmentID")) {
				temp = xmlNodeListGetString(file, j->children, 1);
				sscanf((const char*) temp, "%d", &compared_key);

				if (compared_key == primary_key) {
					xmlUnlinkNode(i);
					xmlFree(i);
				}
			}
		}
	}

	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);

	xmlFree(temp);
}

void RemoveFromFile(const char* file_name, int primary_key, void (* remove)(const char*, xmlDoc*, xmlNode*, int)) {
	xmlDoc* file = xmlReadFile(file_name, NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);

//	remove(file_name, file, root, primary_key);
	remove(NULL, file, root, primary_key);

	xmlFree(root);
	xmlFree(file);
}