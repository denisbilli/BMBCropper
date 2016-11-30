#include "weddingframegenerator.h"

#include <QDebug>

WeddingFrameGenerator::WeddingFrameGenerator(QObject *parent) :
    FrameGenerator(parent)
{
    FrameOption* borderSizeOpt = new FrameOption("borderSize", 16, FrameOption::Int, this);
    borderSizeOpt->setMin(0);
    borderSizeOpt->setMax(50);

    FrameOption* logoSizeOpt = new FrameOption("logoSize", 165, FrameOption::Int, this);
    logoSizeOpt->setMin(100);
    logoSizeOpt->setMax(300);

    addOption("borderSize", borderSizeOpt);
    addOption("logoSize", logoSizeOpt);
}

QPixmap WeddingFrameGenerator::generateFrame(QImage image)
{
    int fixedBorders = getOption("borderSize").toInt();
    qDebug() << "WeddingFrameGenerator::generateFrame" << fixedBorders;
    int logoSize = getOption("logoSize").toInt();
    int maxEdgeLength = getOption("pictureSizeW").toInt();

    // Cerco e rimuovo i bordi bianchi dell'immagine e la scalo a 1950
    QRect whiteBox = getBoundsWithoutColor(image);
    QImage firstPass = image.copy(whiteBox);
    if(firstPass.width() > firstPass.height()) {
        // sono in formato landscape
        firstPass = firstPass.scaledToWidth(maxEdgeLength);
    } else {
        firstPass = firstPass.scaledToHeight(maxEdgeLength);
    }

    QRect outRect = QRect(0, 0, firstPass.width() + fixedBorders*2, firstPass.height() + fixedBorders+logoSize);
    QPixmap out = QPixmap(outRect.size());
    QPainter painter(&out);
    painter.fillRect(outRect, Qt::white);
    painter.drawImage(fixedBorders, fixedBorders, firstPass);
    QImage logo(":/bmb-logo");
    painter.drawImage((out.width()-logo.width())/2, out.height()-(logoSize+logo.height())/2, logo);
    painter.end();

    return out;
}
