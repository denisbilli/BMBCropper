#include "framegenerator.h"

#ifndef WEDDINGFRAMEGENERATOR_H
#define WEDDINGFRAMEGENERATOR_H

class WeddingFrameGenerator : public FrameGenerator
{
    Q_OBJECT
public:
    explicit WeddingFrameGenerator(QObject *parent = 0);

    QPixmap generateFrame(QImage image);
signals:

public slots:

};

#endif // WEDDINGFRAMEGENERATOR_H
