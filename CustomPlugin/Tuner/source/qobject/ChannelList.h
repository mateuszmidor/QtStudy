/**
 *   @file: ChannelList.h
 *
 *   @date: Jun 23, 2016
 * @author: Mateusz Midor
 */

#ifndef CUSTOMPLUGIN_CHANNELLIST_H_
#define CUSTOMPLUGIN_CHANNELLIST_H_

#include <QtCore/QAbstractListModel>

/**
 * @class   ChannelList
 * @brief   Channel list interface in form of QML-understandable QObject
 */
class ChannelList : public QAbstractListModel {

public:
    enum Roles {
       StationNum = Qt::UserRole + 1,
       StationName,
       Artist,
       Title
   };
    Q_ENUM(Roles)

    ChannelList(QObject* parent = 0) : QAbstractListModel(parent) {}
};

#endif /* CUSTOMPLUGIN_CHANNELLIST_H_ */
