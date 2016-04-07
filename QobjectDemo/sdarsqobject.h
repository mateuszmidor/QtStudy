#ifndef SDARSQOBJECT
#define SDARSQOBJECT

#include <QObject>

class SdarsQObject : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString channelName READ getChannelName WRITE setChannelName NOTIFY channelChanged)

public:

    // "channelName" property getter
    QString getChannelName() const {
        return channelName;
    }

    // "channelName" property setter
    void setChannelName(const QString& newChannel) {
        if (channelName != newChannel) {
            channelName = newChannel;
            emit channelChanged();
        }
    }

signals:
    // "channelName" property changed signal
    void channelChanged();

    // "nextChannel" gui event
    void nextChannelClicked();

private:
    QString channelName = "[no channel]";
};

#endif // SDARSQOBJECT
