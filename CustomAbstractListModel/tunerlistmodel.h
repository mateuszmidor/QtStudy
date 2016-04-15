#ifndef TUNERLISTMODEL
#define TUNERLISTMODEL

#include <QAbstractListModel>
class TunerListModel : public QAbstractListModel {

    // define some constant channel data
    static const int NUM_CHANNELS  = 3;
    const QString DATA[NUM_CHANNELS][2] = {{"70's", "87.7 MHz"}, {"80's", "90.1 MHz"}, {"90's", "97.7 MHz"}};

    // roles will be columns in the QML TableView
    enum Roles {
        Name = Qt::UserRole + 1,
        Frequency
    };

public:
    // QAbstractListModel pure-virtual function 1.
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[Name] = "Name";
        roles[Frequency] = "Frequency";
        return roles;
    }

    // QAbstractListModel pure-virtual function 2.
    int rowCount(const QModelIndex &/* index */) const override {
        return NUM_CHANNELS;
    }

    // QAbstractListModel pure-virtual function 3.
    QVariant data(const QModelIndex& modelIndex, int role) const override {
        int row = modelIndex.row();
        switch (role) {
        case Name:
            return DATA[row][0];
        case Frequency:
            return DATA[row][1];
        default:
            return "No such role";
        }
    }


};

#endif // TUNERLISTMODEL

