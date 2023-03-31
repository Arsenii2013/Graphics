#include "camera.h"

Camera::Camera()
{
    mAdditional.perspective(60.0f, 16.f/9.0f, 0.1f, 10.0f);
}
