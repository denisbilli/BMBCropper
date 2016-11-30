#include "frameoption.h"

#include <QDebug>

void FrameOption::setValue(QVariant value) {
    m_value = value;
    qDebug() << "FrameOption::setValue" << this << m_value << value;
    emit optionChanged();
}

void FrameOption::setMax(QVariant max) {
    m_max = max;
    switch (type()) {
    case Int:
        refreshIntWidget();
        break;
    default:
        break;
    }
}

void FrameOption::setMin(QVariant min) {
    m_min = min;
    switch (type()) {
    case Int:
        refreshIntWidget();
        break;
    default:
        break;
    }
}

void FrameOption::slot_onValueChangedFromExt()
{
    if(m_widget == NULL) {
        return;
    }
    QVariant newValue;
    switch (m_type) {
    case Int:
        qDebug() << "slot_onValueChangedFromExt" << this << ((QSlider*)m_widget)->value();
        newValue = ((QSlider*)m_widget)->value();
        break;
    default:
        break;
    }
    setValue(newValue);
}

FrameOption::FrameOption(QObject *parent) :
    AbstractOption(parent)
{

}

void FrameOption::refreshIntWidget()
{
    ((QSlider*)m_widget)->setOrientation(Qt::Horizontal);
    ((QSlider*)m_widget)->setMaximum(max().toInt());
    ((QSlider*)m_widget)->setMinimum(min().toInt());
    ((QSlider*)m_widget)->setValue(value().toInt());
}

void FrameOption::refreshEnumWidget(QVariant t)
{
    int enumCount = parent()->staticMetaObject.enumeratorCount();
    qDebug() << "refreshEnumWidget" << QString(t.typeName()) << parent() << enumCount;
    QStringList values;
    for (int enumIdx = 0; enumIdx < enumCount; ++enumIdx) {
        QMetaEnum metaEnum = parent()->staticMetaObject.enumerator(enumCount);
        qDebug() << "refreshEnumWidget" << enumIdx << metaEnum.name();
        if(QString(metaEnum.name()) == QString(parent()->staticMetaObject.className())) {
            for (int i = 0; i < metaEnum.keyCount(); ++i) {
                values << metaEnum.valueToKey(i);
            }
            break;
        }
    }

    ((QComboBox*)m_widget)->addItems(values);
    ((QComboBox*)m_widget)->setCurrentIndex(value().toInt());
}

FrameOption::FrameOption(QString name, QVariant value, OptionType type, QObject *parent) :
    AbstractOption(parent)
{
    m_widget = NULL;
    m_value = value;
    m_max = 0;
    m_min = 0;
    m_name = name;
    m_type = type;

    switch (type) {
    case Int:
        m_widget = new QSlider(0);
        qDebug() << "FrameOption" << name << this;
        refreshIntWidget();
        connect(((QSlider*)m_widget), SIGNAL(sliderReleased()), this, SLOT(slot_onValueChangedFromExt()));
        break;
    case Enum:
        m_widget = new QComboBox(0);
        refreshEnumWidget(m_value);
        break;
    default:
        break;
    }
}
