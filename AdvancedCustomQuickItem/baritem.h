#ifndef BARITEM
#define BARITEM

#include <QtGui>
#include <QQuickPaintedItem>

// Define a BarItem - single vertical bar in a BarChart
class BarItem : public QQuickItem {
    Q_OBJECT

    Q_PROPERTY(float value READ getValue WRITE setValue NOTIFY valueChanged)
    float value; // a [0.0..1.0] range bar height

public:
    // Constructor
    BarItem(QQuickItem *parent = 0) : QQuickItem(parent) {
    }

    // Value getter
    float getValue() const {
        return value;
    }

    // Value setter
    void setValue(float newValue) {
        if (newValue != value) {
            value = newValue;
            update();
            emit valueChanged();
        }
    }

signals:
    void valueChanged();
};

#endif // BARITEM

