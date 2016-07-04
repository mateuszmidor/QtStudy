/**
 *   @file: Tuner.h
 *
 *   @date: Jun 23, 2016
 * @author: Mateusz Midor
 */

#ifndef CUSTOMPLUGIN_TUNER_H_
#define CUSTOMPLUGIN_TUNER_H_

#include <QtCore/QObject>
#include "ChannelList.h"

/**
 * @class   Tuner
 * @brief   A root object interface to be exposed in QML
 */
class Tuner : public QObject {
    Q_OBJECT

    // access entire channel list
    Q_PROPERTY(QObject* channelList READ channelList CONSTANT)

    // service id of channel that the tuner is currently tuned to
    Q_PROPERTY(short currentChannelId READ currentChannelId WRITE setCurrentChannelId NOTIFY currentChannelIdChanged)

    // contentDescription text of channel that the tuner is currently tuned to
    Q_PROPERTY(QString contentDescription READ contentDescription NOTIFY contentDescriptionChanged)

public:
    Tuner(QObject* parent = 0) : QObject(parent) {}
    virtual ~Tuner() {}

    virtual ChannelList* channelList() = 0;

    virtual int32_t currentChannelId() const = 0;
    virtual void setCurrentChannelId(int32_t service_id) = 0;

    virtual QString contentDescription() const = 0;

signals:
    void currentChannelIdChanged(int32_t service_id);
    void contentDescriptionChanged();
};

#endif /* CUSTOMPLUGIN_TUNER_H_ */
