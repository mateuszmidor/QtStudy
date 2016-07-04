/**
 *   @file: ChannelListImpl.h
 *
 *   @date: Jun 23, 2016
 * @author: Mateusz Midor
 */

#ifndef CUSTOMPLUGIN_CHANNELLISTIMPL_H_
#define CUSTOMPLUGIN_CHANNELLISTIMPL_H_

#include "ChannelList.h"

/**
 * @class   ChannelListImpl
 * @brief   Actual implementation of the channel list to be exposed in QML
 */
class ChannelListImpl: public ChannelList {

    // define some constant channel data
    static const int NUM_CHANNELS  = 8;
    const QString DATA[NUM_CHANNELS][4] = {
            {"22", "[station]", "[artist]", "[title]"},
            {"33", "[station]", "[artist]", "[title]"},
            {"44", "[station]", "[artist]", "[title]"},
            {"55", "[station]", "[artist]", "[title]"},
            {"66", "[station]", "[artist]", "[title]"},
            {"77", "[station]", "[artist]", "[title]"},
            {"88", "[station]", "[artist]", "[title]"},
            {"99", "[station]", "[artist]", "[title]"}
    };

public:
    // QAbstractListModel pure-virtual function implementation
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[StationNum] = "StationNum";
        roles[StationName] = "StationName";
        roles[Artist] = "Artist";
        roles[Title] = "Title";
        return roles;
    }

    // QAbstractListModel pure-virtual function implementation
    int rowCount(const QModelIndex &/* index */) const override {
        return NUM_CHANNELS;
    }

    // QAbstractListModel pure-virtual function implementation
    QVariant data(const QModelIndex& modelIndex, int role) const override {
        int row = modelIndex.row();
        if (row >= NUM_CHANNELS)
            return QVariant();

        switch (role) {
        case StationNum:
            return DATA[row][0];
        case StationName:
            return DATA[row][1];
        case Artist:
            return DATA[row][2];
        case Title:
            return DATA[row][3];
        default:
            return QVariant();
        }
    }
};

#endif /* CUSTOMPLUGIN_CHANNELLISTIMPL_H_ */
