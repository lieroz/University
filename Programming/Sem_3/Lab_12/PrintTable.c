//
// Created by lieroz on 04.12.16.
//

#include "PrintTable.h"

void PrintSuppliers(xmlDoc* file, xmlNode* root) {
	xmlChar* content;

	for (xmlNode* current = root->children; current; current = current->next) {

		if ((!xmlStrcmp(current->name, (const xmlChar*) "SupplierID"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(RED("SupplierID: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "SupplierName"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(GREEN("SupplierName: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "Status"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(YELLOW("Status: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "City"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(BLUE("City: ")) BOLD("%s"), content);
			xmlFree(content);
		}
	}
}

void PrintProducts(xmlDoc* file, xmlNode* root) {
	xmlChar* content;

	for (xmlNodePtr current = root->children; current; current = current->next) {

		if ((!xmlStrcmp(current->name, (const xmlChar*) "ProductID"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(RED("ProductID: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "ProductName"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(GREEN("ProductName: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "Color"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(YELLOW("Color: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "Weight"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(BLUE("Weight: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "Price"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(MAGENTA("Price: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "City"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(CYAN("City: ")) BOLD("%s"), content);
			xmlFree(content);
		}
	}
}

void PrintShipments(xmlDoc* file, xmlNode* root) {
	xmlChar* content;

	for (xmlNodePtr current = root->children; current; current = current->next) {

		if ((!xmlStrcmp(current->name, (const xmlChar*) "ShipmentID"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(RED("ShipmentID: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "SupplierID"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(GREEN("SupplierID: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "ProductID"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(YELLOW("ProductID: ")) BOLD("%s"), content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "Qty"))) {
			content = xmlNodeListGetString(file, current->children, 1);
			FPRINTF(BOLD(BLUE("Qty: ")) BOLD("%s"), content);
			xmlFree(content);
		}
	}
}

void PrintTable(const char* file_name, void (*print)(xmlDoc*, xmlNode*)) {
	xmlDoc* file = xmlReadFile(file_name, NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);

	for (xmlNode* current = root->children; current; current = current->next) {
		print(file, current);
		fprintf(stdout, "\n");
	}

	xmlFree(file);
	xmlFree(root);
}