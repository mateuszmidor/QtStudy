#ifndef CAMERA
#define CAMERA

#include <QObject>

class Camera : public QObject {
    Q_OBJECT

    Q_PROPERTY(float distance READ getDistance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(float azimuth READ getAzimuth WRITE setAzimuth NOTIFY azimuthChanged)
    Q_PROPERTY(float elevation READ getElevation WRITE setElevation NOTIFY elevationChanged)

    float azimuth, elevation, distance;
public:
    Camera() : azimuth(45.0f), elevation(30.0f), distance(-128.0f) {}


    float getDistance() const {
        return distance;
    }

    void setDistance(float value) {
        if (distance != value) {
            distance = value;
            emit distanceChanged();
        }
    }

    float getAzimuth() const {
        return azimuth;
    }

    void setAzimuth(float value) {
        if (azimuth != value) {
            azimuth = value;
            emit azimuthChanged();
        }
    }

    float getElevation() const {
        return elevation;
    }

    void setElevation(float value) {
        if (elevation != value) {
            elevation = value;
            emit elevationChanged();
        }
    }

signals:
    void distanceChanged();
    void azimuthChanged();
    void elevationChanged();
};

#endif // CAMERA

