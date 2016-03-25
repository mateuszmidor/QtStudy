#ifndef BARCHARTITEM_H
#define BARCHARTITEM_H

#include <QtGui>
#include <QQuickPaintedItem>
#include "baritem.h"

// Convenience type alias for Q_PROPERTY
// typedef QQmlListProperty<BarItem> BarList;
// - DONT DO THIS, BECAUSE :
// "Invalid property assignment: "bars" is a read-only property"



// Advanced custom QuickItem implementation; with list properties and enums.
// Inherit from QQuickPaintedItem to use the convenient QPainter interface
// Notice: the docs say that QQuickItem is faster. But more low-level
class BarChartItem : public QQuickPaintedItem {
    Q_OBJECT

    // Define properties of our object. They will be available to QML
    Q_PROPERTY(Style style READ getStyle WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(QQmlListProperty<BarItem> bars READ getBars NOTIFY barsChanged) // WRITE is not needed for this property to be writable

public:
    // Define custom enum. It must be defined inside the class!!!
    enum Style { Outline, Fill };

    // Register the custom enum.
    // Note that, in QML, it will be accessed through BarItem, eg BarItem.Outline instead of Style.Outline!!!
    Q_ENUM(Style)


    // Constructor
    BarChartItem(QQuickItem *parent = 0) : QQuickPaintedItem(parent) {
    }

    // Custom paint method
    void paint(QPainter *painter){
        // 1. Save the painter state
        painter->save();

        // 2. Setup the painter
        setupFilledOutlineStyle(painter);
        setupUpsideDownTransform(painter);

        // 3. Draw the bars
        drawBars(painter);

        // 4. Restore the painter state
        painter->restore();
    }

    // Style getter
    const Style& getStyle() const {
        return style;
    }

    // Style setter
    void setStyle(const Style &newStyle) {
        if (newStyle != style) {
            style = newStyle;
            update();
            emit styleChanged();
        }
    }

    // Bars getter
    QQmlListProperty<BarItem> getBars()  {
        return QQmlListProperty<BarItem>(this, bars);
    }

// Signals can be emitted from C++ and handled in QML (onStyleChanged)
signals:
    void styleChanged();
    void barsChanged();

// Public slots can be called from QML and handled in C++
public slots:
    void toggleFillStyle() {
        setStyle(style == Style::Outline ? Style::Fill : Style::Outline);
    }

private:
    // Hold the style information
    Style style;

    // Hold the bars list
    QList<BarItem*> bars;


    // Setup Fill/Outline drawing style
    void setupFilledOutlineStyle(QPainter *painter)
    {
        if (style == Style::Outline) {
            painter->setBrush(Qt::NoBrush);
            painter->setPen(QColor("black"));
        }
        else {
            painter->setPen(QColor("black"));
            painter->setBrush(QColor("red"));
        }
    }

    // Set upside-down transformation - to have (0, 0) in the left-lower corner
    void setupUpsideDownTransform(QPainter *painter)
    {
        painter->translate(0, height());
        painter->scale(1.0, -1.0);
    }

    // Draw the chart bars
    void drawBars(QPainter *painter)
    {
        unsigned numBars = bars.length();
        unsigned barWidth = width() / numBars;

        for (unsigned i = 0; i < numBars; ++i) {
            BarItem &b = *bars.at(i);
            unsigned left = i * barWidth + 1;
            unsigned barHeight = height() * b.getValue();
            painter->drawRect(left, 0, barWidth, barHeight);
        }
    }
};


#endif // BARCHARTITEM_H
