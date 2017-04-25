#include "qstrtochararr.h"
#include "ptr.h"
#include <stdio.h>
#include <string.h>

char* QStringToCharArr(QString str) {
	char* buff = (char*) malloc(sizeof(char) * str.length());
	strcpy(buff, str.toLocal8Bit().data());
	
	return buff;
}
