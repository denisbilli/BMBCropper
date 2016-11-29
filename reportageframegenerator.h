#include "framegenerator.h"

#ifndef REPORTAGEFRAMEGENERATOR_H
#define REPORTAGEFRAMEGENERATOR_H

class ReportageFrameGenerator : public FrameGenerator
{
    Q_OBJECT
public:
    explicit ReportageFrameGenerator(QObject *parent = 0);

    QPixmap generateFrame(QImage image);
    QImage lightenEffect(QImage p, QImage dst, QPoint position);
signals:

public slots:

};

#endif // REPORTAGEFRAMEGENERATOR_H
