//
// Created by lieroz on 04.12.16.
//

#include "AddToFile.h"

void AddSupplier(const char* file_name, xmlDoc* file, xmlNode* root) {
	xmlNode* current = root->children;

	while (current->next != NULL) {
		current = current->next;
	}

	xmlNode* new_node = xmlNewChild(root, 0, (const xmlChar*) "Supplier", 0);
	xmlChar* table_child = xmlNodeListGetString(file, current->children->children, 1);
	int key = 0;

	sscanf((const char*) table_child, "%d", &key);
	sprintf((char*) table_child, "%d", ++key);
	xmlNewChild(new_node, 0, (const xmlChar*) "SupplierID", table_child);

	fprintf(stdout, "Enter SupplierName: ");

	if (fscanf(stdin, "%s", table_child) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	xmlNewChild(new_node, 0, (const xmlChar*) "SupplierName", table_child);

	fprintf(stdout, "Enter Status: ");

	if (fscanf(stdin, "%d", &key) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	sprintf((char*) table_child, "%d", key);
	xmlNewChild(new_node, 0, (const xmlChar*) "Status", table_child);

	fprintf(stdout, "Enter City: ");

	if (fscanf(stdin, "%s", table_child) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	xmlNewChild(new_node, 0, (const xmlChar*) "City", table_child);

	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);

ERROR:
	xmlFree(table_child);
	xmlFree(new_node);
	xmlFree(current);
}

void AddProduct(const char* file_name, xmlDoc* file, xmlNode* root) {
	xmlNode* current = root->children;

	while (current->next != NULL) {
		current = current->next;
	}

	xmlNode* new_node = xmlNewChild(root, 0, (const xmlChar*) "Product", 0);
	xmlChar* table_child = xmlNodeListGetString(file, current->children->children, 1);
	int key = 0;

	sscanf((const char*) table_child, "%d", &key);
	sprintf((char*) table_child, "%d", ++key);
	xmlNewChild(new_node, 0, (const xmlChar*) "ProductID", table_child);

	fprintf(stdout, "Enter ProductName: ");

	if (fscanf(stdin, "%s", table_child) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	xmlNewChild(new_node, 0, (const xmlChar*) "ProductName", table_child);

	fprintf(stdout, "Enter Color: ");

	if (fscanf(stdin, "%s", table_child) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	xmlNewChild(new_node, 0, (const xmlChar*) "Color", table_child);

	double temp = 0;
	fprintf(stdout, "Enter Weight: ");

	if (fscanf(stdin, "%lf", &temp) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	sprintf((char*) table_child, "%.2lf", temp);
	xmlNewChild(new_node, 0, (const xmlChar*) "SupplierID", table_child);

	fprintf(stdout, "Enter Price: ");

	if (fscanf(stdin, "%lf", &temp) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	sprintf((char*) table_child, "%.2lf", temp);
	xmlNewChild(new_node, 0, (const xmlChar*) "Price", table_child);

	fprintf(stdout, "Enter City: ");

	if (fscanf(stdin, "%s", table_child) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	xmlNewChild(new_node, 0, (const xmlChar*) "City", table_child);

	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);

ERROR:
	xmlFree(table_child);
	xmlFree(new_node);
	xmlFree(current);
}

void AddShipment(const char* file_name, xmlDoc* file, xmlNode* root) {
	xmlNode* current = root->children;

	while (current->next != NULL) {
		current = current->next;
	}

	xmlNode* new_node = xmlNewChild(root, 0, (const xmlChar*) "Shipment", 0);
	xmlChar* table_child = xmlNodeListGetString(file, current->children->children, 1);
	int key = 0;

	sscanf((const char*) table_child, "%d", &key);
	sprintf((char*) table_child, "%d", ++key);
	xmlNewChild(new_node, 0, (const xmlChar*) "ShipmentID", table_child);

	fprintf(stdout, "Enter SupplierID: ");

	if (fscanf(stdin, "%d", &key) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	sprintf((char*) table_child, "%d", key);
	xmlNewChild(new_node, 0, (const xmlChar*) "SupplierID", table_child);

	fprintf(stdout, "Enter ProductID: ");

	if (fscanf(stdin, "%d", &key) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	sprintf((char*) table_child, "%d", key);
	xmlNewChild(new_node, 0, (const xmlChar*) "ProductID", table_child);

	fprintf(stdout, "Enter Qty: ");

	if (fscanf(stdin, "%d", &key) != 1) {
		fprintf(stderr, "ERROR: INVALID INPUT");
		goto ERROR;
	}

	assert(key > 0);

	sprintf((char*) table_child, "%d", key);
	xmlNewChild(new_node, 0, (const xmlChar*) "Qty", table_child);

	xmlSaveFormatFileEnc(file_name ? file_name : "-", file, "UTF-8", 1);

ERROR:
	xmlFree(table_child);
	xmlFree(new_node);
	xmlFree(current);
}

void AddToFile(const char* file_name, void (*add)(const char*, xmlDoc*, xmlNode*)) {
	xmlDoc* file = xmlReadFile(file_name, NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);

//	add(file_name, file, root);
	add(NULL, file, root);

	xmlFree(root);
	xmlFree(file);
}