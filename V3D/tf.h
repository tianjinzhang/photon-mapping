#ifndef TF_H
#define TF_H

#include <QtGui/QWidget>
#include <QIcon>
#include "shadewidget.h"
class TF : public QWidget
{
	Q_OBJECT

public:
	TF(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TF();

	void resizeEvent( QResizeEvent * event );
	void closeEvent(QCloseEvent *event);
	

	unsigned char *tfData;
	int*count;
	float hightCount;

	//save and load gradientStop,points;
	void saveData(const char* file);
	void loadData(const char* file);
private:

    ShadeWidget*  m_alpha_shade;
	bool loadFromFile;
public slots:
	void pointsUpdated();

signals:
	void tfChange();
};

#endif // TF_H
