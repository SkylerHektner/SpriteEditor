#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);

    void PosWhileDownEvent(QMouseEvent *ev);
    void MouseDownEvent(QMouseEvent *ev);
    void MouseUpEvent(QMouseEvent *ev);
    void LeftCanvasEvent(QEvent *);

    int x;
    int y;

signals:

    void Mouse_DownPos();
    void Mouse_Down();
    void Mouse_Up();
    void Mouse_Left();

public slots:
};

#endif // CANVAS_H
