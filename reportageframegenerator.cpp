#include "reportageframegenerator.h"

#include <QGraphicsDropShadowEffect>
#include <QRgb>
#include <QDebug>
#include <QBitmap>
#include <QMetaProperty>

ReportageFrameGenerator::ReportageFrameGenerator(QObject *parent) :
    FrameGenerator(parent)
{
    qRegisterMetaType<LogoPosition>("LogoPosition");
    qRegisterMetaType<LogoEffect>("LogoEffect");

    FrameOption* logoPositionOpt = new FrameOption("logoPosition", QVariant::fromValue(BottomRight),
                                                   FrameOption::Enum, this);
    FrameOption* logoMarginOpt = new FrameOption("logoMargin", 20, FrameOption::Int, this);
    logoMarginOpt->setMin(0);
    logoMarginOpt->setMax(50);
    FrameOption* logoSizeOpt = new FrameOption("logoSize", 165, FrameOption::Int, this);
    logoSizeOpt->setMin(100);
    logoSizeOpt->setMax(300);
    FrameOption* logoEffectOpt = new FrameOption("logoEffect", QVariant::fromValue(Lighten | DropShadow),
                                                 FrameOption::MultiEnum, this);

    qDebug() << "ReportageFrameGenerator" << staticMetaObject.enumeratorCount();
    qt_getEnumMetaObject(BottomRight);

    addOption("logoPosition", logoPositionOpt);
    addOption("logoMargin", logoMarginOpt);
    addOption("logoSize", logoSizeOpt);
    addOption("logoEffect", logoEffectOpt);
}

QImage ReportageFrameGenerator::lightenEffect(QImage src, QImage dst, QPoint position) {
    QImage out(dst.size(), dst.format());
    out.fill(0);

    if(src.size() == QSize(0,0)) {
        return out;
    }

    for (int y = 0; y < dst.height(); ++y) {
        QRgb *row = (QRgb*)src.scanLine(y + position.y());
        QRgb *dstRow = (QRgb*)out.scanLine(y);
        for (int x = 0; x < dst.width(); ++x) {
            QRgb dstPixel = dst.pixel(x, y);
            // 0 e' completamente trasparente
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
    int maxEdgeLength = getOption("pictureSizeW").toInt();

    int logoPosition = getOption("logoPosition").toInt();
    int logoMargin = getOption("logoMargin").toInt();
    int logoSize = getOption("logoSize").toInt();
    int logoEffect = getOption("logoEffect").toInt();
    QPoint logoPositionPoint(0,0);

    QImage logo(":/bmb-gray.png");
    logo = logo.scaled(logoSize - 10, logoSize - 10, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    qDebug() << "Has alpha channel logo: " << logo.hasAlphaChannel();

    QImage logoFx(logoSize, logoSize, QImage::Format_ARGB32);

    QPainter painterFx(&logoFx);
    painterFx.setCompositionMode (QPainter::CompositionMode_Source);
    painterFx.fillRect(logoFx.rect(), Qt::transparent);
    painterFx.setCompositionMode (QPainter::CompositionMode_SourceOver);
    painterFx.drawImage(2, 2, logo);
    painterFx.end();

    // Cerco e rimuovo i bordi bianchi dell'immagine e la scalo a 1950
    QRect whiteBox = getBoundsWithoutColor(image);
    QImage firstPass = image.copy(whiteBox);
    if(firstPass.width() > firstPass.height()) {
        // sono in formato landscape
        firstPass = firstPass.scaledToWidth(maxEdgeLength);
    } else {
        firstPass = firstPass.scaledToHeight(maxEdgeLength);
    }

    QRect outRect = QRect(0, 0, firstPass.width(), firstPass.height());
    QImage out = QImage(outRect.size(), QImage::Format_ARGB32);

    // posiziono il logo
    if(logoPosition == TopLeft) {
        logoPositionPoint.setX(logoMargin);
        logoPositionPoint.setY(logoMargin);
    } else if (logoPosition == TopRight) {
        logoPositionPoint.setX(out.width() - logoFx.width() - logoMargin);
        logoPositionPoint.setY(logoMargin);
    } else if (logoPosition == BottomLeft) {
        logoPositionPoint.setX(logoMargin);
        logoPositionPoint.setY(out.height() - logoFx.height() - logoMargin);
    } else if (logoPosition == BottomRight) {
        logoPositionPoint.setX(out.width() - logoFx.width() - logoMargin);
        logoPositionPoint.setY(out.height() - logoFx.height() - logoMargin);
    }

    QPainter painter(&out);
    painter.fillRect(outRect, Qt::white);
    painter.drawImage(0, 0, firstPass);

    if(CHECK_BITMASK(logoEffect, DropShadow)) {
        QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
        dropShadowEffect->setOffset(5);
        dropShadowEffect->setBlurRadius(5);

        logoFx = applyEffectToImage(logoFx, dropShadowEffect);
    }

    if(CHECK_BITMASK(logoEffect, Lighten)) {
        logoFx = lightenEffect(out, logoFx, logoPositionPoint);
    }

    painter.drawImage(logoPositionPoint, logoFx);
    painter.end();

    return QPixmap::fromImage(out);
}
