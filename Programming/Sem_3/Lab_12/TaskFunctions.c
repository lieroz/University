//
// Created by lieroz on 05.12.16.
//

#include "TaskFunctions.h"

bool find(const xmlChar* key, xmlChar** array, size_t size) {
	for (size_t i = 0; i < size; ++i) {

		if (!xmlStrcmp(key, array[i])) {
			return true;
		}
	}

	return false;
}

size_t GetCityIndex(const xmlChar* city, xmlChar** cities, size_t size) {
	for (size_t i = 0; i < size; ++i) {

		if (!xmlStrcmp(city, cities[i])) {
			return i;
		}
	}
}

void GetCityLocalizedSuppliers() {
	xmlDoc* file = xmlReadFile("XML_Suppliers.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	xmlNode*** nodes = (xmlNode***) malloc(sizeof(xmlNode**) * 256);

	for (size_t i = 0; i < 256; ++i) {
		nodes[i] = (xmlNode**) malloc(sizeof(xmlNode*) * 20);
	}

	size_t* cities_count = (size_t*) malloc(sizeof(size_t) * 256);
	xmlChar** cities = (xmlChar**) malloc(sizeof(xmlChar*) * 256);
	xmlChar* city_name = NULL;
	size_t count = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "City")) {
				city_name = xmlNodeListGetString(file, j->children, 1);

				if (!find(city_name, cities, count)) {
					cities_count[count] = 1;
					nodes[count][0] = i;
					cities[count++] = city_name;
				} else {
					nodes[GetCityIndex(city_name, cities, count)][cities_count[GetCityIndex(city_name,
					                                                                        cities,
					                                                                        count)]++] = i;
				}
			}
		}
	}

	for (size_t i = 0; i < count; ++i) {

		fprintf(stdout, BOLD(RED("%s: ")), cities[i]);

		for (size_t j = 0; j < cities_count[i]; ++j) {

			for (xmlNode* current = nodes[i][j]->children; current; current = current->next) {

				if (!xmlStrcmp(current->name, BAD_CAST "SupplierName")) {
					xmlChar* content = xmlNodeListGetString(file, current->children, 1);
					fprintf(stdout, BOLD(GREEN("%s ")) BOLD(CYAN("| ")), content);
				}
			}
		}

		fprintf(stdout, "\n");
	}

	for (size_t i = 0; i < count; ++i) {
		xmlFree(cities[i]);
	}

	free(cities_count);
	xmlFree(cities);
	xmlFree(city_name);
	xmlFree(root);
	xmlFree(file);
}
// ---------------------------------------------------------------------------------------------------------------------

void GetAllEngagedSuppliers() {
	xmlDoc* file = xmlReadFile("XML_Shipments.xml", NULL, 0);
	xmlNode* root = xmlDocGetRootElement(file);
	xmlChar** suppliers = (xmlChar**) malloc(sizeof(xmlChar*) * 256);
	xmlChar* supplier_id = NULL;
	size_t count = 0;

	for (xmlNode* i = root->children; i; i = i->next) {

		for (xmlNode* j = i->children; j; j = j->next) {

			if (!xmlStrcmp(j->name, BAD_CAST "SupplierID")) {
				supplier_id = xmlNodeListGetString(file, j->children, 1);

				if (!find(supplier_id, suppliers, count)) {
					suppliers[count++] = supplier_id;
				}
			}
		}
	}

	fprintf(stdout, BOLD(YELLOW("Engaged SupplierID's: ")));

	for (size_t i = 0; i < count; ++i) {
		fprintf(stdout, BOLD(MAGENTA("%s | ")), suppliers[i]);
	}

	fprintf(stdout, BOLD(YELLOW("\nAmount of all suppliers engaged: ")) BOLD(MAGENTA("%lu\n")), count);

	xmlFree(suppliers);
	xmlFree(supplier_id);
	xmlFree(root);
	xmlFree(file);
}
// ---------------------------------------------------------------------------------------------------------------------

