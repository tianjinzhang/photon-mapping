#include "v3d.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	V3D w;
	w.show();
	return a.exec();
}
