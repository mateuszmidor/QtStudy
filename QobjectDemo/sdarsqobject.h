#ifndef SDARSQOBJECT
#define SDARSQOBJECT

#include <QObject>

// mythical "QObject" implementation. It enables communication with GUI through signals and slots, In both directions
class SdarsQObject : public QObject {
    Q_OBJECT

    // properties are visible from QML code
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
    // "channelName" property changed signal - to be handled in QML code
    void channelChanged();

    // "nextChannel" gui event - to be fired from QML code
    void nextChannelClicked();

private:
    QString channelName = "[no channel]";
};

#endif // SDARSQOBJECT
