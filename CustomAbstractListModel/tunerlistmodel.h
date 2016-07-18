#ifndef TUNERLISTMODEL
#define TUNERLISTMODEL

#include <QObject>
#include <QDebug>
#include <QAbstractListModel>
#include <QVector>
#include <QTime>

struct Channel {
    QString name;
    QString frequency;
};

class TunerListModel : public QAbstractListModel {
    Q_OBJECT

    // define some channel data
    QVector<Channel> channels {{"70's", "87.7 MHz"}, {"80's", "90.1 MHz"}, {"90's", "97.7 MHz"}};
public:
    // roles will be columns in the QML TableView
    enum Roles {
        Name = Qt::UserRole + 1,
        Frequency
    };
    // export enum to QML so it is accessible like: TunerListModel.Frequency
    Q_ENUM(Roles)

    // QAbstractListModel pure-virtual function 1.
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[Name] = "Name";
        roles[Frequency] = "Frequency";
        return roles;
    }

    // QAbstractListModel pure-virtual function 2.
    int rowCount(const QModelIndex &/* index */ = QModelIndex()) const override {
        return channels.length();
    }

    // QAbstractListModel pure-virtual function 3.
    Q_INVOKABLE QVariant data(const QModelIndex& modelIndex, int role) const override {
        int row = modelIndex.row();
        return get(row, role);
    }

    // data getter
    Q_INVOKABLE QVariant get(int row, int role) const {
        switch (role) {
        case Name:
            return channels[row].name;
        case Frequency:
            return channels[row].frequency;
        default:
            qDebug() << "invalid role " << role << endl;
            return QVariant();
        }
    }

    // add row at first position
    Q_INVOKABLE void addFirst() {
        beginInsertRows(QModelIndex(), 0, 0);
        Channel c {QString("First Ch."), QString("First frq")};
        channels.insert(0, c);
        endInsertRows();
    }

    // add row at last position
    Q_INVOKABLE void addLast() {
        auto rowcount = rowCount();
        beginInsertRows(QModelIndex(), rowcount, rowcount);
        Channel c {QString("Last Ch."), QString("Last frq")};
        channels.insert(rowcount, c);
        endInsertRows();
    }

    // remove row at first position
    Q_INVOKABLE void removeFirst() {
        beginRemoveRows(QModelIndex(), 0, 0);
        channels.remove(0);
        endRemoveRows();
    }

    // remove row at last position
    Q_INVOKABLE void removeLast() {
        auto rowcount = rowCount();
        beginRemoveRows(QModelIndex(), rowcount -1, rowcount -1);
        channels.remove(rowcount -1);
        endRemoveRows();
    }

    //  update row at middle position to current time
    Q_INVOKABLE void updateMiddle() {
        auto middle_idx = channels.length()/2;
        channels[middle_idx].name = QTime::currentTime().toString();
        QModelIndex topleft = createIndex(middle_idx, 0, nullptr); // row, column, some data pointer (?)
        QModelIndex bottomright = createIndex(middle_idx, 0, nullptr);
        emit dataChanged(topleft, bottomright);
    }
};

#endif // TUNERLISTMODEL

