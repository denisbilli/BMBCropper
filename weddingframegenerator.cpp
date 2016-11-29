#include "weddingframegenerator.h"

WeddingFrameGenerator::WeddingFrameGenerator(QObject *parent) :
    FrameGenerator(parent)
{
}

QPixmap WeddingFrameGenerator::generateFrame(QImage image)
{
    int fixedBorders = m_borderSize;
    int logoSize = 165;
    int maxEdgeLength = 1950;

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
