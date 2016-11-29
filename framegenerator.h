#ifndef FRAMEGENERATOR_H
#define FRAMEGENERATOR_H

#include <QObject>
#include <QRect>
#include <QImage>
#include <QColor>
#include <QPixmap>
#include <QPainter>
#include <QRgb>
#include <QGraphicsEffect>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#define SMALL 10
#define isSimilar(A, B) ( ((A-B) < SMALL) && ((A-B) > - SMALL) )
#define isSimilarRgb(A, B) (isSimilar(qRed(A),qRed(B)) && isSimilar(qGreen(A),qGreen(B)) && isSimilar(qBlue(A),qBlue(B)))

#define lighten(A, B)   (B > A ? B : A)
#define lightenRGB(A, B, alpha)   (qRgba(lighten(qRed(A), qRed(B)), lighten(qGreen(A), qGreen(B)), lighten(qBlue(A), qBlue(B)), alpha))

class FrameGenerator : public QObject
{
    Q_OBJECT
public:
    explicit FrameGenerator(QObject *parent = 0);

    virtual QPixmap generateFrame(QImage image) = 0;
    QRect crop(QImage p);
    QRect getBoundsWithoutColor(QImage p, const QColor &exclusionColor = Qt::white, const int tolerance=30);

    void setBorderSize(int borderSize);
    int borderSize() { return m_borderSize; }

    QImage applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent = 0);
protected:
    int m_borderSize;

signals:

public slots:

};

#endif // FRAMEGENERATOR_H
