#ifndef PREVIEWOBJECT_H
#define PREVIEWOBJECT_H

#include <QObject>
#include <QImage>
#include <QThread>
#include <QTime>

//project puts this on a different thread to run preview animation

class PreviewObject : public QObject
{
    Q_OBJECT

public:

    QImage* image;
    explicit PreviewObject(QImage* image, QObject *parent = Q_NULLPTR);

signals:

    //sent to project AND mainwindow
    void thread_end(QImage *image);

public slots:

    void thread_start();
};

#endif // PREVIEWOBJECT_H
