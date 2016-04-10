#ifndef SOMECHANNELS
#define SOMECHANNELS

#include <QString>

class SomeChannels {
    static const int CHANNEL_COUNT { 5 };
    const QString CHANNELS[CHANNEL_COUNT] = { "40's", "70's", "90's", "Rock", "Dance" };
    int currChannelIdx { 0 };

public:
    QString nextChannel() {
        QString channel = CHANNELS[currChannelIdx];
        currChannelIdx = (currChannelIdx + 1) % CHANNEL_COUNT;
        return channel;
    }
};

#endif // SOMECHANNELS

