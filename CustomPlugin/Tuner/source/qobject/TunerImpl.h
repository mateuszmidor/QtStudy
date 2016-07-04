/**
 *   @file: TunerImpl.h
 *
 *   @date: Jun 23, 2016
 * @author: Mateusz Midor
 */

#ifndef CUSTOMPLUGIN_TUNERIMPL_H_
#define CUSTOMPLUGIN_TUNERIMPL_H_

#include "ChannelListImpl.h"
#include "Tuner.h"

/**
 * @class   TunerImpl
 * @brief   Actual implementation of the root object to be exposed in QML
 */
class TunerImpl : public Tuner {
    ChannelListImpl channel_list;
    int current_channelid = -1; // channel currently tuned to
    QString current_contentdescription;

public:
    TunerImpl(QObject* parent = 0);
    virtual ~TunerImpl();

    ChannelList* channelList() override;

    int32_t currentChannelId() const override;
    void setCurrentChannelId(int32_t serviceId) override;

    QString contentDescription() const override;

private slots:
    void onContentDescriptionArrived(const QString description);
};

#endif /* CUSTOMPLUGIN_TUNERIMPL_H_ */
