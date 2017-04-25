#include "error.h"
#include <QMessageBox>

int ErrorMessage(QWidget* parent, errs_num err) {
	QString message;
	
	switch (err) {
		case ERR_WITH_FILE: {
			message = "Не удалось открыть файл!";
			break;
		}
		case ERR_WITH_MEMORY: {
			message = "Невозможно выделить память!";
			break;
		}
		case ERR_NO_FORMAT_FILE: {
			message = "Фаил содержит некорректные данные!";
			break;
		}
		case ERR_ZERO: {
			message = "Нет точек!";
			break;
		}
		default:
			return err;
	}
	QMessageBox::critical(parent, "Ошибка", message);
	return err;
}
