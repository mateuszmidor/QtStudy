#ifndef CAMERA
#define CAMERA

#include <QObject>

class Camera : public QObject {
    Q_OBJECT

    Q_PROPERTY(float distance READ getDistance WRITE setDistance NOTIFY distanceChanged)
public:
    Camera() : azimuth(45.0f), elevation(30.0f), distance(-128.0f) {}

    float azimuth, elevation, distance;

    float getDistance() const {
        return distance;
    }

    void setDistance(float value) {
        if (distance != value) {
            distance = value;
            emit distanceChanged();
        }
    }

signals:
    void distanceChanged();
};

#endif // CAMERA

