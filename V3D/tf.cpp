#include "tf.h"

inline static bool x_less_than(const QPointF &p1, const QPointF &p2)
{
    return p1.x() < p2.x();
}
inline static bool x_less_than_QGradientStop(const QGradientStop &p1, const  QGradientStop &p2)
{
    return p1.first < p2.first;
}
static void set_shade_points(const QPolygonF &points, ShadeWidget *shade)
{
    shade->hoverPoints()->setPoints(points);
    shade->hoverPoints()->setPointLock(0, HoverPoints::LockToLeft);
    shade->hoverPoints()->setPointLock(points.size() - 1, HoverPoints::LockToRight);
    shade->update();
}

TF::TF(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	 setWindowTitle("transform function");
	 QIcon icon("/faicon.png");
	 setWindowIcon(icon);
	 setGeometry(100,650,1024,256);
	 tfData = new unsigned char[256 * 4];
	 count = new int[256];
	 loadFromFile = false;

	
     m_alpha_shade = new ShadeWidget(ShadeWidget::ARGBShade, this);
    connect(m_alpha_shade, SIGNAL(colorsChanged()), this, SLOT(pointsUpdated()));
	
}

TF::~TF()
{
	delete[] tfData;
	delete[] count;
	delete m_alpha_shade;

}
void TF::resizeEvent( QResizeEvent * e ) 
{
    m_alpha_shade ->setGeometry(0,0,this->width(),this->height());

	QPolygonF countPoint;
	QPainterPath countPath;
	countPoint.reserve(256);
	int mostHigh = 0;
	int mostHighX = 0;
	for(int i = 0;i<256;i++)
	{
		if(count[i] > mostHigh)
		{
			mostHigh = count[i];
		}
	}

	
	QPointF pbegin(0,(this ->height() - 1));
	countPoint.push_back(pbegin);
	for(int i = 0;i < 256;i++)
	{
		QPointF po;
		if(0 == count[i])
		{
			 po = QPointF(i/255.0*(this ->width() -1),this ->height() - 1);
		}
		else
		{
			 po = QPointF(i/255.0*(this ->width() -1),(1 - qLn(count[i])/qLn(mostHigh))*(this ->height() - 1));
		}
		countPoint.push_back(po);

	}
	QPoint pend(this ->width(),this ->height());
	countPoint.push_back(pend);
	/*countPath.moveTo(countPoint.at(0));
	for (int i = 1; i<256; ++i) 
	{
		QPointF p1 = countPoint.at(i-1);
		QPointF p2 = countPoint.at(i);
		qreal distance = p2.x() - p1.x();

		countPath.cubicTo(p1.x() + distance / 2, p1.y(),
		p1.x() + distance / 2, p2.y(),
	    p2.x(), p2.y());
    }

	*/
	//m_alpha_shade ->countPoints =countPoint;
	countPath.addPolygon(countPoint);
    m_alpha_shade ->countPath = countPath;

		
	

   //qDebug() <<".......................";

	
   
}
void TF::closeEvent(QCloseEvent *event)
{
	this ->hide();
}	

void TF::pointsUpdated()
{
    qreal w = m_alpha_shade->width();
	qreal h = m_alpha_shade->height();
    QGradientStops colors;
	QGradientStops temp;
	QGradientStop t;


    QPolygonF points;

    points = m_alpha_shade->points();
	colors = m_alpha_shade->colors();   


	for(int i = 0;i < colors.size();i++)
	{
		t = colors.at(i);
		if(t.first != -1.0)
		{
			t = qMakePair(points.at(i).x()/w,t.second);
			temp << t;
		    
		}

	}

    qSort(temp.begin(), temp.end(), x_less_than_QGradientStop);

    m_alpha_shade->setGradientStops(temp);
	qSort(points.begin(), points.end(), x_less_than);

	if(this ->loadFromFile)
	{
		this ->loadFromFile = false;
		emit tfChange();
		return;
	}

	for(int i = 0;i < points.size() - 1;i++)
	{
		qreal now_x = points.at(i).x()/w * 255;
		qreal now_alpha = ( h - points.at(i).y())/h * 255;
		qreal next_x = points.at(i + 1).x()/w * 255;
		qreal next_alpha =( h - points.at(i + 1).y())/h * 255;

		tfData[(int)now_x * 4 + 3] = (int)now_alpha;
		tfData[(int)next_x * 4 + 3] = (int)next_alpha;

		if(((int)next_x - (int)now_x)  < 2)
			continue;

		if(next_alpha > now_alpha)
		{
			qreal high = next_alpha - now_alpha;
			qreal start = now_x;

            for(int i = (int)now_x + 1; i < (int)next_x;i++)
			{
				tfData[i * 4 +3] = (int)((i - (int)start) / (next_x - now_x) * high + now_alpha);

			}

		}
		else if(next_alpha < now_alpha)
		{
			qreal high = now_alpha - next_alpha;
			qreal start = next_x;

			for(int i = (int)now_x + 1; i < (int)next_x;i++)
			{
				tfData[i * 4 +3] = (int)(((int)start - i) / (next_x - now_x) * high + next_alpha);

			}

		}
		else
		{
			for(int i = (int)now_x + 1; i < (int)next_x;i++)
			{
				tfData[i * 4 +3] = (int)now_alpha;

			}
			
	     }
	}

	int step = (this ->m_alpha_shade ->m_shade).width() - 1;
	int height = this ->m_alpha_shade ->m_shade.height() - 1;
    for(int i = 0;i < 256;i++)
	{
		
		QRgb c = (this ->m_alpha_shade ->m_shade).pixel((int)(i/255.0 * step),height-1);
		tfData[i * 4 + 0] = qRed(c);
		tfData[i * 4 + 1] = qGreen(c);
		tfData[i * 4 + 2] = qBlue(c);

	}
 /* for(int i = 0;i < 256;i++)
   {
	   qDebug() << tf[i * 4 + 0]<< " "<<tf[i * 4 + 1] <<" "<<tf[i * 4 + 2] << "," << tf[i * 4 + 3];
   }
   qDebug() <<".......................";*/
   emit tfChange();
}

//load and save TF data
//data format
//4*256 unsigned char
//sizeof points int
//for(i;sizeof points)
//p.x,p.y qreal,qreal + f,r,g,b,a, qreal,int,int,int
//
void TF::saveData(const char *file)
{
	FILE *fp;
	fp= fopen(file,"wb+");
	if(NULL == fp)
	{
		qDebug() << "....................................................write tf file error";
		fclose(fp);
	
	}
	
	fwrite(this ->tfData,256 * 4,1,fp);
	int size = (this ->m_alpha_shade->points()).size();
	fwrite(&size,sizeof(int),1,fp);
	qreal x;
	qreal y;
	int r;
	int g;
	int b;
	int a;
	for(int i = 0;i < size;i++)
	{
		QPointF p = this ->m_alpha_shade ->points().at(i);
		x = p.x();
		y = p.y();
        fwrite(&x,sizeof(qreal),1,fp);
		fwrite(&y,sizeof(qreal),1,fp);
		QGradientStop c = this ->m_alpha_shade ->colors().at(i);
		qreal f = c.first;
		
		r = c.second.red();
		g = c.second.green();
		b = c.second.blue();
		a = c.second.alpha();
		fwrite(&f,sizeof(qreal),1,fp);
		fwrite(&r,sizeof(int),1,fp);
		fwrite(&g,sizeof(int),1,fp);
		fwrite(&b,sizeof(int),1,fp);
		fwrite(&a,sizeof(int),1,fp);
		
	}

	QMessageBox::information(NULL, "result", "DONE!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	fclose(fp);
	
}
void TF::loadData(const char *file)
{
	FILE *fp;
	fp= fopen(file,"rb");
	if(NULL == fp)
	{
		qDebug() << "....................................................read tf file error";
		fclose(fp);
	
	}
	this ->loadFromFile = true;
	fread(this ->tfData,256 * 4,1,fp);

	int size;
	fread(&size,sizeof(int),1,fp);
	
	QPolygonF ploygonF;
	QGradientStops colors;
	qreal x ;
	qreal y ;
	qreal f;
	int r;
	int g;
	int b;
	int a;
	for(int i = 0;i < size;i++)
	{
		
        fread(&x,sizeof(qreal),1,fp);
		fread(&y,sizeof(qreal),1,fp);
		QPointF p(x,y);
		ploygonF.push_back(p);
		
        fread(&f,sizeof(qreal),1,fp);
		fread(&r,sizeof(int),1,fp);
		fread(&g,sizeof(int),1,fp);
		fread(&b,sizeof(int),1,fp);
		fread(&a,sizeof(int),1,fp);
		QGradientStop c = qMakePair(f,QColor(r,g,b,a));
		colors.push_back(c);
	}
   fclose(fp);

   this ->m_alpha_shade->hoverPoints() ->setPoints(ploygonF);
   this ->m_alpha_shade->hoverPoints() ->m_colors = colors;

   this ->m_alpha_shade->hoverPoints() ->paintPoints();
   pointsUpdated();

}