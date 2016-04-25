#ifndef CAMERA
#define CAMERA

class Camera {
public:
    Camera() : azimuth(45.0f), elevation(30.0f), distance(-128.0f) {}
    float azimuth, elevation, distance;
};

#endif // CAMERA

