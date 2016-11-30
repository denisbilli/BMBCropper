#ifndef ABSTRACTOPTION_H
#define ABSTRACTOPTION_H

#include <QObject>

class AbstractOption : public QObject
{
    Q_OBJECT
public:
    explicit AbstractOption(QObject *parent = 0);

signals:

public slots:

};
//Q_DECLARE_METATYPE(AbstractOption*)

#endif // ABSTRACTOPTION_H
