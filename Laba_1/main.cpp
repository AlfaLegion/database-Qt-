#include "laba_1.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{QApplication a(argc, argv);
	
	QTextEdit* console=nullptr;
	
	MyWidget wgt(console);
	wgt.show();
	
	return a.exec();
}
