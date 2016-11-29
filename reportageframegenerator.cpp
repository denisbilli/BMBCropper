#include "reportageframegenerator.h"

#include <QGraphicsDropShadowEffect>
#include <QRgb>
#include <QDebug>

#define ChannelBlend_Lighten(A,B)       ((uint8)((B > A) ? B:A))
#define ColorBlend_Buffer(T,A,B,M)      (T)[0] = ChannelBlend_Lighten((A)[0], (B)[0]),\
                                        (T)[1] = ChannelBlend_Lighten((A)[1], (B)[1]),\
                                        (T)[2] = ChannelBlend_Lighten((A)[2], (B)[2])
#define ColorBlend_Lighten(T,A,B)       (ColorBlend_Buffer(T,A,B,Lighten))

//#define ImageTColorR = ChannelBlend_Lighten(ImageAColorR, ImageBColorR);
//#define ImageTColorB = ChannelBlend_Lighten(ImageAColorB, ImageBColorB);
//#define ImageTColorG = ChannelBlend_Lighten(ImageAColorG, ImageBColorG);

//#define ImageTColor = RGB(ImageTColorR, ImageTColorB, ImageTColorG);

ReportageFrameGenerator::ReportageFrameGenerator(QObject *parent) :
    FrameGenerator(parent)
{
}

QImage ReportageFrameGenerator::lightenEffect(QImage src, QImage dst, QPoint position) {
//    int l = p.width(), r = 0, t = p.height(), b = 0;
    QImage out(src.size(), src.format());
    QRect dstRect(position, dst.size());

    qDebug() << "ReportageFrameGenerator::lightenEffect" << src.size() << out.size();

    for (int y = 0; y < src.height(); ++y) {
        QRgb *row = (QRgb*)src.scanLine(y);
        QRgb *dstRow = (QRgb*)out.scanLine(y);
        for (int x = 0; x < src.width(); ++x) {
            if(!dstRect.contains(x,y,true)) {
                dstRow[x] = row[x];
            } else {
                QRgb dstPixel = dst.pixel(x - position.x(),y - position.y());
                QRgb rgb = lightenRGB(row[x], dstPixel, qAlpha(dstPixel));
                dstRow[x] = rgb;
            }
        }
    }

    return out;
}

QPixmap ReportageFrameGenerator::generateFrame(QImage image)
{
    int fixedBorders = 0;
    int logoSize = 165;
    int maxEdgeLength = 1950;

    QImage logo(":/bmb-gray.png");
    QPixmap logoFx(logoSize, logoSize);
    QPainter painterFx(&logoFx);
    painterFx.setCompositionMode (QPainter::CompositionMode_Source);
    painterFx.fillRect(logoFx.rect(), Qt::transparent);
    painterFx.setCompositionMode (QPainter::CompositionMode_SourceOver);
    painterFx.drawImage(0, 0, logo.scaled(logoSize-10, logoSize-10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    painterFx.end();

    QImage logoFxImg = logoFx.toImage();

    // Cerco e rimuovo i bordi bianchi dell'immagine e la scalo a 1950
    QRect whiteBox = getBoundsWithoutColor(image);
    QImage firstPass = image.copy(whiteBox);
    if(firstPass.width() > firstPass.height()) {
        // sono in formato landscape
        firstPass = firstPass.scaledToWidth(maxEdgeLength);
    } else {
        firstPass = firstPass.scaledToHeight(maxEdgeLength);
    }

    QRect outRect = QRect(0, 0, firstPass.width() + fixedBorders*2, firstPass.height() + fixedBorders);
    QPixmap out = QPixmap(outRect.size());
    QPainter painter(&out);
    painter.fillRect(outRect, Qt::white);
    painter.drawImage(fixedBorders, fixedBorders, firstPass);

#if 0
    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
    dropShadowEffect->setOffset(5);
    dropShadowEffect->setBlurRadius(5);

    logoFxImg = applyEffectToImage(logoFxImg, dropShadowEffect);

    painter.setOpacity(0.8);
    painter.drawImage(out.width()-logoFx.width()-20, out.height()-logoFx.height()-20, logoFxImg);
    painter.end();

//    QImage outLogoFxImg = lightenEffect(out.toImage(), logoFxImg, QPoint(out.width()-logoFx.width()-20, out.height()-logoFx.height()-20));

//    return QPixmap::fromImage(outLogoFxImg);
    return out;
#else
    painter.end();

    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
    dropShadowEffect->setOffset(5);
    dropShadowEffect->setBlurRadius(5);

    logoFxImg = applyEffectToImage(logoFxImg, dropShadowEffect);

    QImage outLogoFxImg = lightenEffect(out.toImage(), logoFxImg, QPoint(out.width()-logoFx.width()-20, out.height()-logoFx.height()-20));

    return QPixmap::fromImage(outLogoFxImg);
#endif
}
