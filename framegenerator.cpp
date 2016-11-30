#include "framegenerator.h"

#include <QDebug>

FrameGenerator::FrameGenerator(QObject *parent) :
    QObject(parent)
{
    FrameOption* pictureSizeWOpt = new FrameOption("pictureSizeW", 1950, FrameOption::Int, this);
    pictureSizeWOpt->setMin(400);
    pictureSizeWOpt->setMax(9999);

    addOption("pictureSizeW", pictureSizeWOpt);
}

QRect FrameGenerator::crop(QImage p) {
    int l = p.width(), r = 0, t = p.height(), b = 0;
    for (int y = 0; y < p.height(); ++y) {
        QRgb *row = (QRgb*)p.scanLine(y);
        bool rowFilled = false;
        for (int x = 0; x < p.width(); ++x) {
            if(isSimilarRgb(row[x], 255)) {
                rowFilled = true;
                r = std::max(r, x);
                if (l > x) {
                    l = x;
                    x = r; // shortcut to only search for new right bound from here
                }
            }
        }
        if (rowFilled) {
            t = std::min(t, y);
            b = y;
        }
    }
    return QRect(l, t, l+r, t+b);
}

QImage FrameGenerator::applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent)
{
    if(src.isNull()) return QImage();   //No need to do anything else!
    if(!effect) return src;             //No need to do anything else!
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(src));
    item.setGraphicsEffect(effect);
    scene.addItem(&item);
    QImage res(src.size()+QSize(extent*2, extent*2), QImage::Format_ARGB32);
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, src.width()+extent*2, src.height()+extent*2 ) );
    return res;
}

void FrameGenerator::addOption(QString optionName, FrameOption *option) {
    m_optionsMap.insert(optionName, QVariant::fromValue<FrameOption*>(option));
    connect(option, SIGNAL(optionChanged()), SLOT(slot_onOptionChanged()));
}

QVariant FrameGenerator::getOption(QString optionName) {
    qDebug() << "FrameGenerator::getOption" << optionName << m_optionsMap.value(optionName).value<FrameOption*>()
                << m_optionsMap.value(optionName).value<FrameOption*>()->value();
    return m_optionsMap.value(optionName).value<FrameOption*>()->value();
}

void FrameGenerator::slot_onOptionChanged()
{
    FrameOption* option = qobject_cast<FrameOption*>(QObject::sender());
    if(option == NULL) {
        return;
    }
    emit optionChanged(option->name(), option->value());
}

QRect FrameGenerator::getBoundsWithoutColor(QImage p, const QColor &exclusionColor, const int tolerance)
{
    QRect rect;

    int maxX = 0; int minX = p.width();
    int maxY = 0; int minY = p.height();

    for(int y=0; y < p.height(); y++) {
        QRgb *row = (QRgb*)p.scanLine(y);
        for(int x=0; x < p.width(); x++) {
            int diff = abs(exclusionColor.red()-qRed(row[x])) +
                    abs(exclusionColor.green()-qGreen(row[x])) +
                    abs(exclusionColor.blue()-qBlue(row[x]));
            if(diff > tolerance) {
                if(x < minX) minX = x;
                if(x > maxX) maxX = x;
                if(y < minY) minY = y;
                if(y > maxY) maxY = y;
            }
        }

        if (minX > maxX || minY > maxY) {
            // The whole picture is white. How you wanna handle this case is up to you.
        } else {
            rect.setCoords(minX, minY, maxX, maxY);
        }
    }

    return rect;
}
