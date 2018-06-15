#ifndef PICWIN_H
#define PICWIN_H

#include <QWidget>
#include <QtMath>
#include <QPainter>
#include <QPen>
#define PI 3.14159265

class PicWin : public QWidget
{

    Q_OBJECT

public:
    struct DrawParameter
    {
        int type;
        float amplitude;
        float frequency;
        float phase;
        float offset;
        float inversion;
     };
    struct DrawParameter para;

protected:
    int sign(float x)
    {
        if (x > 0)
            return 1;
        else if (x==0)
            return 0;
        else
            return -1;
    }
	//重载QWidget类的paintEvent函数绘制图像
    void paintEvent(QPaintEvent *)
    {
            QPainter painter(this);
            QPen pen;
            QFont font;

            painter.setViewport(50, 50, width()-100, height()-100);//设置绘制范围距窗口的上下左右边距为50
            //将图像绘制在一个长为20高为6的矩形范围内（物理坐标系），并设置视窗观察该范围
            float xProp = 20/(2.0/para.frequency);//计算缩放比例
            float yProp = 6/(2*para.amplitude);
            QRect r = QRect(-11,-3-para.offset*yProp-1,22,8);
            painter.setWindow(r);//设置视窗位置（即设定只看物理坐标系中的某一矩形范围）, r can't be QRectF

            float posW = 0.06;
            float axisW = 0.04;
            float pointW = 0.02;
            float textW = 0.4;

            pen.setColor(Qt::black);
            pen.setStyle(Qt::SolidLine);
            pen.setWidthF(axisW);
            painter.setPen(pen);

            font.setPointSizeF(textW);
            painter.setFont(font);

            painter.fillRect(r, Qt::white);
            painter.drawLine(0,r.y(),0,r.y()+r.height());
            painter.drawLine(r.x(),0,r.x()+r.width(),0);

            pen.setWidthF(pointW);
            painter.setPen(pen);

            float tx,y,tt;
            QString pos;
            switch(para.type){
            case 0: //Sine
                for(float x=-1/para.frequency; x<=1/para.frequency; x+=0.01)
                {
                    tx = para.frequency*x+para.phase;
                    y = qSin(2*PI*tx);
                    y = para.inversion*para.amplitude*y + para.offset;
                    painter.drawPoint(QPointF(x*xProp ,-y*yProp));
                }
                pen.setStyle(Qt::DashLine);
                painter.setPen(pen);
                tt = -para.phase/para.frequency+1/(4*para.frequency);
                painter.drawLine(QPointF(tt*xProp,0),QPointF(tt*xProp,-(para.inversion*para.amplitude+para.offset)*yProp));//tmd如果坐标是小数，一定记得用QPointF
                painter.drawLine(QPointF(-para.phase/para.frequency*xProp,0),QPointF(-para.phase/para.frequency*xProp,-para.offset*yProp));
                //写一个坐标
                pos = QString("(%1,%2)").arg(-para.phase/para.frequency).arg(para.offset);
                painter.drawText(QPointF(-para.phase/para.frequency*xProp,-para.offset*yProp),pos);
                //写另一个坐标
                pos = QString("(%1,%2)").arg(tt).arg(para.inversion*para.amplitude+para.offset);
                painter.drawText(QPointF(tt*xProp,-(para.inversion*para.amplitude+para.offset)*yProp),pos);
                //画上述两个坐标的点
                pen.setWidthF(posW);
                painter.setPen(pen);
                painter.drawPoint(QPointF(-para.phase/para.frequency*xProp,-para.offset*yProp));
                painter.drawPoint(QPointF(tt*xProp,-(para.inversion*para.amplitude+para.offset)*yProp));
                break;
            case 1: //Rectangle
                for(float x=-1/para.frequency; x<=1/para.frequency; x+=0.01)
                {
                    tx = para.frequency*x+para.phase;
                    y = sign(qSin(2*PI*tx));
                    y = para.inversion*para.amplitude*y + para.offset;
                    painter.drawPoint(QPointF(x*xProp ,-y*yProp));
                }
                pen.setStyle(Qt::DashLine);
                painter.setPen(pen);
                tt = -para.phase/para.frequency+1/(2*para.frequency);
                painter.drawLine(QPointF(tt*xProp,-(-para.inversion*para.amplitude+para.offset)*yProp),QPointF(tt*xProp,-(para.inversion*para.amplitude+para.offset)*yProp));
                painter.drawLine(QPointF(-para.phase/para.frequency*xProp,-(-para.inversion*para.amplitude+para.offset)*yProp),QPointF(-para.phase/para.frequency*xProp,-(para.inversion*para.amplitude+para.offset)*yProp));
                //写一个坐标
                pos = QString("(%1,%2)").arg(-para.phase/para.frequency).arg(para.offset);
                painter.drawText(QPointF(-para.phase/para.frequency*xProp,-para.offset*yProp),pos);
                //写另一个坐标
                pos = QString("(%1,%2)").arg(tt).arg(para.inversion*para.amplitude+para.offset);
                painter.drawText(QPointF(tt*xProp,-(para.inversion*para.amplitude+para.offset)*yProp),pos);
                //画上述两个坐标的点
                pen.setWidthF(posW);
                painter.setPen(pen);
                painter.drawPoint(QPointF(-para.phase/para.frequency*xProp,-para.offset*yProp));
                painter.drawPoint(QPointF(tt*xProp,-(para.inversion*para.amplitude+para.offset)*yProp));
                break;
            case 2: //Triangle
                for(float x=-2/para.frequency; x<=2/para.frequency; x+=0.01)
                {
                    tx = para.frequency*x+para.phase;
                    y = 2*qAbs(tx-2*qFloor(tx/2)-1)-1;
                    y = para.inversion*para.amplitude*y + para.offset;
                    painter.drawPoint(QPointF(x*xProp/2 ,-y*yProp));
                }
                pen.setStyle(Qt::DashLine);
                painter.setPen(pen);
                painter.drawLine(QPointF(-para.phase/para.frequency*xProp/2,0),QPointF(-para.phase/para.frequency*xProp/2,-(para.inversion*para.amplitude+para.offset)*yProp));
                tt = -para.phase/para.frequency+1/para.frequency;
                painter.drawLine(QPointF(tt*xProp/2,0),QPointF(tt*xProp/2,-(-para.inversion*para.amplitude+para.offset)*yProp));
                //写一个坐标
                pos = QString("(%1,%2)").arg(-para.phase/para.frequency).arg(para.inversion*para.amplitude+para.offset);
                painter.drawText(QPointF(-para.phase/para.frequency*xProp/2,-(para.inversion*para.amplitude+para.offset)*yProp),pos);
                //写另一个坐标
                pos = QString("(%1,%2)").arg(tt).arg(-para.inversion*para.amplitude+para.offset);
                painter.drawText(QPointF(tt*xProp/2,-(-para.inversion*para.amplitude+para.offset)*yProp),pos);
                //画上述两个坐标的点
                pen.setWidthF(posW);
                painter.setPen(pen);
                painter.drawPoint(QPointF(-para.phase/para.frequency*xProp/2,-(para.inversion*para.amplitude+para.offset)*yProp));
                painter.drawPoint(QPointF(tt*xProp/2,-(-para.inversion*para.amplitude+para.offset)*yProp));
                break;
            case 3: //Sawtooth
                for(float x=-1/para.frequency; x<=1/para.frequency; x+=0.01)
                {
                    tx = para.frequency*x+para.phase;
                    y = 2*(tx-qFloor(tx+1/2.0));
                    y = para.inversion*para.amplitude*y + para.offset;
                    painter.drawPoint(QPointF(x*xProp ,-y*yProp));
                }
                pen.setStyle(Qt::DashLine);
                painter.setPen(pen);
                painter.drawLine(QPointF(-para.phase/para.frequency*xProp,0),QPointF(-para.phase/para.frequency*xProp,-para.offset*yProp));
                tt = -para.phase/para.frequency+1/(2*para.frequency);
                painter.drawLine(QPointF(tt*xProp,-(-para.inversion*para.amplitude+para.offset)*yProp),QPointF(tt*xProp,-(para.inversion*para.amplitude+para.offset)*yProp));
                //写一个坐标
                pos = QString("(%1,%2)").arg(-para.phase/para.frequency).arg(para.offset);
                painter.drawText(QPointF(-para.phase/para.frequency*xProp,-para.offset*yProp),pos);
                //写另一个坐标
                pos = QString("(%1,%2)").arg(tt).arg(para.inversion*para.amplitude+para.offset);
                painter.drawText(QPointF(tt*xProp,-(para.inversion*para.amplitude+para.offset)*yProp),pos);
                //画上述两个坐标的点
                pen.setWidthF(posW);
                painter.setPen(pen);
                painter.drawPoint(QPointF(-para.phase/para.frequency*xProp,-para.offset*yProp));
                painter.drawPoint(QPointF(tt*xProp,-(para.inversion*para.amplitude+para.offset)*yProp));
                break;
            }
    }
};

#endif // PICWIN_H
