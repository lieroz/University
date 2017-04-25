#ifndef ERROR
#define ERROR
#include <QWidget>

enum errs_num {
	ERR_WITH_FILE,
	ERR_WITH_MEMORY,
	ERR_NO_FORMAT_FILE,
	NO_ERR,
	ERR_ZERO
};

int ErrorMessage(QWidget *parent,errs_num err);

#endif // ERROR

