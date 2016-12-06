#include "PrintTable.h"
#include "AddToFile.h"
#include "RemoveFromFile.h"
#include "ModifyTableContent.h"
#include "TaskFunctions.h"

int main(const int argc, const char* argv[]) {
	xmlInitParser();
	xmlKeepBlanksDefault(0);

//	ModifyTableContent("XML_Suppliers.xml", "SupplierID", 674, ModifySupplier);
//	GetCityLocalizedSuppliers();
//	GetAllEngagedSuppliers();
	GetTotalProductCostBySupplier(448);
	GetProductColorBySupplier(448);
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
	xmlCleanupParser();
}