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
#include "frameoption.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define CHECK_BITMASK(var,mask) ((var & mask) == mask)

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
    QImage applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent = 0);

    void addOption(QString optionName, FrameOption* option);
    QVariant getOption(QString optionName);
    QVariantMap options() { return m_optionsMap; }

protected:
    QVariantMap m_optionsMap;

signals:
    void optionChanged(QString optionName, QVariant optionValue);

public slots:

private slots:
    void slot_onOptionChanged();
};

#endif // FRAMEGENERATOR_H
