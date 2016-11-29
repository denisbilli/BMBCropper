#include "reportageframegenerator.h"

#include <QGraphicsDropShadowEffect>
#include <QRgb>
#include <QDebug>
#include <QBitmap>

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
    QImage out(dst.size(), dst.format());
    out.fill(0);
    //dst.createAlphaMask().save("C:\\Users\\denis\\Desktop\\Test\\out.png");

    qDebug() << "ReportageFrameGenerator::lightenEffect" << src.size() << out.size();

    if(src.size() == QSize(0,0)) {
        return out;
    }

    for (int y = 0; y < dst.height(); ++y) {
        QRgb *row = (QRgb*)src.scanLine(y + position.y());
        QRgb *dstRow = (QRgb*)out.scanLine(y);
        for (int x = 0; x < dst.width(); ++x) {
            QRgb dstPixel = dst.pixel(x, y);
            // 0 è completamente trasparente
            if(qAlpha(dstPixel) == 0) {
                dstRow[x] = qRgba(0,0,0,0);
                continue;
            }
            QRgb rgb = lightenRGB(row[x + position.x()], dstPixel, qAlpha(dstPixel));
            dstRow[x] = rgb;
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
    logo = logo.scaled(logoSize-10, logoSize-10, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    qDebug() << "Has alpha channel logo: " << logo.hasAlphaChannel();

    QImage logoFx(logoSize, logoSize, QImage::Format_ARGB32);

    QPainter painterFx(&logoFx);
    painterFx.setCompositionMode (QPainter::CompositionMode_Source);
    painterFx.fillRect(logoFx.rect(), Qt::transparent);
    painterFx.setCompositionMode (QPainter::CompositionMode_SourceOver);
    painterFx.drawImage(2, 2, logo);
    painterFx.end();

    logoFx.save("D:\\Foto\\VorwerkBimby\\out.png");

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
    QImage out = QImage(outRect.size(), QImage::Format_ARGB32);
    QPainter painter(&out);
    painter.fillRect(outRect, Qt::white);
    painter.drawImage(fixedBorders, fixedBorders, firstPass);

#if 1
    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
    dropShadowEffect->setOffset(5);
    dropShadowEffect->setBlurRadius(5);

    logoFx = applyEffectToImage(logoFx, dropShadowEffect);
    logoFx.save("D:\\Foto\\VorwerkBimby\\out1.png");
    qDebug() << "Has alpha channel 1: " << logoFx.hasAlphaChannel();

    logoFx = lightenEffect(out, logoFx, QPoint(out.width()-logoFx.width()-20, out.height()-logoFx.height()-20));
    logoFx.save("D:\\Foto\\VorwerkBimby\\out2.png");
    qDebug() << "Has alpha channel 2: " << logoFx.hasAlphaChannel();

    painter.drawImage(out.width()-logoFx.width()-20, out.height()-logoFx.height()-20, logoFx);
    painter.end();

    return QPixmap::fromImage(out);
#else
    painter.end();
    qDebug() << "Has alpha channel: " << logoFx.hasAlphaChannel();
    QImage outLogoFxImg = lightenEffect(out.toImage(), logoFx, QPoint(out.width()-logoFx.width()-20, out.height()-logoFx.height()-20));
    outLogoFxImg.save("D:\\Foto\\VorwerkBimby\\out1.png");

    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
    dropShadowEffect->setOffset(5);
    dropShadowEffect->setBlurRadius(5);

    QImage shadowImg = applyEffectToImage(outLogoFxImg, dropShadowEffect);
    shadowImg.save("D:\\Foto\\VorwerkBimby\\out2.png");

    painter.begin(&out);
    painter.setOpacity(0.8);
    painter.drawImage(out.width()-outLogoFxImg.width()-20, out.height()-outLogoFxImg.height()-20, outLogoFxImg);
    painter.end();

    return out;
#endif
}
