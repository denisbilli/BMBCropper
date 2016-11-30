#include "framegenerator.h"

#ifndef REPORTAGEFRAMEGENERATOR_H
#define REPORTAGEFRAMEGENERATOR_H

class ReportageFrameGenerator : public FrameGenerator
{
    Q_OBJECT
    Q_ENUMS(ReportageFrameGenerator::LogoPosition)
    Q_ENUMS(ReportageFrameGenerator::LogoEffect)

public:
    enum LogoPosition {
        TopLeft = 0,
        TopRight,
        BottomLeft,
        BottomRight
    };

    enum LogoEffect {
        Lighten     = 0x1,
        DropShadow  = 0x2
    };

    explicit ReportageFrameGenerator(QObject *parent = 0);

    QPixmap generateFrame(QImage image);
    QImage lightenEffect(QImage p, QImage dst, QPoint position);
signals:

public slots:

};
Q_DECLARE_METATYPE(ReportageFrameGenerator::LogoPosition)
Q_DECLARE_METATYPE(ReportageFrameGenerator::LogoEffect)

#endif // REPORTAGEFRAMEGENERATOR_H
