#include <libxml/parser.h>

#include "PrintTable.h"
#include "AddToFile.h"

int main(const int argc, const char* argv[]) {
	xmlKeepBlanksDefault(0);
	AddToFile("XML_Shipments.xml", AddShipment);

//	while (true) {
//		int choice = 0;
//
//		fprintf(stdout, "Enter your choice: ");
//		fscanf(stdin, "%d", &choice);
//
//		switch (choice) {
//
//			case 1:
//				PrintTable("XML_Suppliers.xml", PrintSuppliers);
//				break;
//
//			case 2:
//				PrintTable("XML_Products.xml", PrintProducts);
//				break;
//
//			case 3:
//				PrintTable("XML_Shipments.xml", PrintShipments);
//				break;
//
//			default:
//				return 0;
//		}
//	}
}