/**
 *   @file: TunerImpl.cpp
 *
 *   @date: Jun 23, 2016
 * @author: Mateusz Midor
 */

#include "TunerImpl.h"

#include <cstdio> // printf

/**
 * Constructor.
 * @param   parent QT parent object
 */
TunerImpl::TunerImpl(QObject* parent) : Tuner(parent) {
    current_contentdescription = "[content dscr]";
}

TunerImpl::~TunerImpl() {
}

/**
 * @name    channelList
 * @brief   channel list getter
 * @note    it should be made const returning const in the future
 * @return  Channel list in form of QObject that can be used in QML
 */
ChannelList* TunerImpl::channelList() {
    return &channel_list;
}

/**
 * @name    currentChannelId
 * @return  id of channel we are currently tuned to
 */
int32_t TunerImpl::currentChannelId() const {
    return current_channelid;
}

/**
 * @name    setCurrentChannelId
 * @brief   effectively tune  to given serviceId
 * @param   id Service id to tune to
 */
void TunerImpl::setCurrentChannelId(int32_t id) {
    if (id == current_channelid)
        return;

    current_channelid = id;
    onContentDescriptionArrived("channel: " + QString::number(id));
}

/**
 * @name    contentDescription
 * @brief   current channel contentDescription getter
 * @return  contentDescription for current channel if available, "[not available]" otherwise
 */
QString TunerImpl::contentDescription() const {
    return current_contentdescription;
}

/**
 * @name    onContentDescriptionArrived
 * @brief   slot for updating currently played content description text
 * @param   description Description text of currently played content
 */
void TunerImpl::onContentDescriptionArrived(const QString description) {
    if (current_contentdescription == description)
        return;

    current_contentdescription = description;
    emit contentDescriptionChanged();
}
