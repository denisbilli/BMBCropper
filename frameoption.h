#ifndef FRAMEOPTION_H
#define FRAMEOPTION_H

#include "abstractoption.h"

#include <QComboBox>
#include <QSlider>
#include <QObject>
#include <QVariant>
#include <QMetaObject>
#include <QDebug>
#include <QMetaEnum>
#include <QMetaType>

class FrameOption : public AbstractOption
{
    Q_OBJECT

public:
    explicit FrameOption(QObject* parent = 0);
    virtual ~FrameOption() {}

    typedef int (*int_funct_ptr)(int);
    typedef qreal (*real_funct_ptr)(qreal);
    typedef QString (*text_funct_ptr)(QString);

    typedef enum OptionType {
        Int = 0,
        Float,
        Enum,
        MultiEnum,
        Text
    } OptionType;

    explicit FrameOption(QString name = "New Option", QVariant value = 0, OptionType type = Int, QObject* parent = 0);

    virtual QString name() { return m_name; }
    virtual void setName(QString name) { m_name = name; }

    virtual QVariant value() { return m_value; }
    virtual void setValue(QVariant value);

    virtual QVariant max() { return m_max; }
    virtual void setMax(QVariant max);

    virtual QVariant min() { return m_min; }
    virtual void setMin(QVariant min);

    virtual OptionType type() { return m_type; }
    virtual void setType(OptionType type) { m_type = type; }

    QWidget* widget() { return m_widget; }

    void refreshIntWidget();
    void refreshEnumWidget(QVariant t);

protected:
    QVariant m_value;
    QVariant m_max;
    QVariant m_min;
    QString m_name;
    OptionType m_type;

    QWidget* m_widget;

signals:
    void optionChanged();

public slots:
    void slot_onValueChangedFromExt();

};

Q_DECLARE_METATYPE(FrameOption*)

#endif // FRAMEOPTION_H
