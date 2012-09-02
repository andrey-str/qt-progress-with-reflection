#include <QApplication>
#include "dialog.h"
int main (int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	ProgressBarDialog* dialog = new ProgressBarDialog();
	dialog->show();
	
	return app.exec();
}