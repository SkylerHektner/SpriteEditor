#ifndef FRAME_H
#define FRAME_H
#include <QImage>;
#include <QColor>;

//frame will contain our methods of manipulating QImages in this project

class Frame {
private:
    QImage *image;
public:
    Frame(int x, int y);
    ~Frame();

    void editPixel(int x, int y, QColor color);

    void rotateImage(int angle);

    QImage getImage();

    //shrink/enlarge

    //mirror

    //resize an image while maintaining current pixel organization
};

#endif // FRAME_H
