#ifndef ELLIPSEITEM
#define ELLIPSEITEM

#include <QtGui>
#include <QQuickPaintedItem>

// Custom QuickItem implementation.
// Inherit from QQuickPaintedItem to use the convenient QPainter interface
// Notice: the docs say that QQuickItem is faster. But more low-level
class EllipseItem : public QQuickPaintedItem {
    Q_OBJECT

    // Define the "color" property of our object
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
    QColor color;
public:
    // Constructor
    EllipseItem(QQuickItem *parent = 0) : QQuickPaintedItem(parent)  { }

    // Custom paint method
    void paint(QPainter *painter){
        // 1. Save the painter state
        painter->save();

        // 2. Setup the painter to desired color
        painter->setBrush(color);

        // 3. Paint the ellipse
        painter->drawEllipse(boundingRect());

        // 4. Restore the painter state
        painter->restore();
    }

    // Color getter
    const QColor& getColor() const {
        return color;
    }

    // Color setter
    void setColor(const QColor &newColor) {
        if (newColor != color) {
            color = newColor;
            update();
            emit colorChanged();
        }
    }

signals:
    void colorChanged();
};

#endif // ELLIPSEITEM

