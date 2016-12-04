#include <stdio.h>
#include <libxml/parser.h>

void ParseSuppliers(xmlDoc* doc, xmlNode* node) {
	xmlChar* content;

	for (xmlNodePtr current = node->children; current; current = current->next) {

		if ((!xmlStrcmp(current->name, (const xmlChar*) "SupplierID"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "SupplierID: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "SupplierName"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "SupplierName: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "Status"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "Status: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "City"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "City: %s", content);
			xmlFree(content);
		} else {
			fprintf(stdout, "\n");
		}
	}
}

void ParseProducts(xmlDoc* doc, xmlNode* node) {
	xmlChar* content;

	for (xmlNodePtr current = node->children; current; current = current->next) {

		if ((!xmlStrcmp(current->name, (const xmlChar*) "ProductID"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "ProductID: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "ProductName"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "ProductName: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "Color"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "Color: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "Weight"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "Weight: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "Price"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "Price: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "City"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "City: %s", content);
			xmlFree(content);
		} else {
			fprintf(stdout, "\n");
		}
	}
}

void ParseShipments(xmlDoc* doc, xmlNode* node) {
	xmlChar* content;

	for (xmlNodePtr current = node->children; current; current = current->next) {

		if ((!xmlStrcmp(current->name, (const xmlChar*) "ShipmentID"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "ShipmentID: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "SupplierID"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "SupplierID: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "ProductID"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "ProductID: %s", content);
			xmlFree(content);
		} else if ((!xmlStrcmp(current->name, (const xmlChar*) "Qty"))) {
			content = xmlNodeListGetString(doc, current->children, 1);
			fprintf(stdout, "Qty: %s", content);
			xmlFree(content);
		} else {
			fprintf(stdout, "\n");
		}
	}
}

void ReadXmlFile(const char* file_name, void (*parser)(xmlDoc*, xmlNode*)) {
	xmlDoc* file = xmlReadFile(file_name, NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);

	for (xmlNode* current = root->children; current; current = current->next) {
		parser(file, current);
	}

	xmlFree(file);
	xmlFree(root);
}

int main(const int argc, const char* argv[]) {
	ReadXmlFile("XML_Products.xml", ParseProducts);

	return 0;
}