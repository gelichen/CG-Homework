#ifndef CAMERA_H
#define CAMERA_H
#include<math.h>

#define PI 3.14159265

class Camera {
public:
    Camera(GLfloat x = -1, GLfloat y = 0, GLfloat z = 0,
           GLfloat ux = 0, GLfloat uy = 1, GLfloat uz = 0,
           GLfloat pitch_ = 0, GLfloat yaw_ = 0, GLfloat fov_ = 60);
    //GLfloat GetFieldOfView() {return fov;}
    //void SetFieldOfView(GLfloat fov_) {fov = fov_;}
    void GluLookAt();
    void SetCameraCoordinate();
    void moveForward(GLfloat const distance);
    void moveBack(GLfloat const distance);
    void moveRight(GLfloat const distance);
    void moveLeft(GLfloat const distance);
    void rotate(GLfloat const pitch_, GLfloat const yaw_);
  private:
    GLfloat pitch, yaw, fov;
    GLfloat cameraPosX, cameraPosY, cameraPosZ;
    GLfloat cameraFrontX, cameraFrontY, cameraFrontZ;
    GLfloat cameraRightX, cameraRightY, cameraRightZ;
    GLfloat cameraUpX, cameraUpY, cameraUpZ;
    GLfloat UpX, UpY, UpZ;
};

Camera::Camera(GLfloat x, GLfloat y, GLfloat z, GLfloat ux, GLfloat uy, GLfloat uz, GLfloat pitch_, GLfloat yaw_, GLfloat fov_) {
    cameraPosX = x;
    cameraPosY = y;
    cameraPosZ = z;
    UpX = ux;
    UpY = uy;
    UpZ = uz;
    pitch = pitch_;
    yaw = yaw_;
    fov = fov_;
    SetCameraCoordinate();
}

void Camera::GluLookAt() {
    glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, 1, 0.1, 1000);
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
              cameraPosX+cameraFrontX, cameraPosY+cameraFrontY, cameraPosZ+cameraFrontZ,
              UpX, UpY, UpZ);
}

void Camera::SetCameraCoordinate() {
    //front vector determined by Euler angles
    cameraFrontX = cos(yaw*PI/180)*cos(pitch*PI/180);
    cameraFrontY = sin(pitch*PI/180);
    cameraFrontZ = cos(pitch*PI/180)*sin(yaw*PI/180);
    //the cross product of vector (a1, a2, a3) and (b1, b2, b3)
    //is (a2*b3-a3*b2, a3*b1-a1*b3, a1*b2-a2*b1)
    //right vector = front vector*Up vector(in the world/gluLookAt)
    cameraRightX = cameraFrontY*UpZ-cameraFrontZ*UpY;
    cameraRightY = cameraFrontZ*UpX-cameraFrontX*UpZ;
    cameraRightZ = cameraFrontX*UpY-cameraFrontY*UpX;
    //up vector = right vector*front vector
    cameraUpX = cameraUpY*cameraFrontZ-cameraUpZ*cameraFrontY;
    cameraUpY = cameraUpZ*cameraFrontX-cameraUpX*cameraFrontZ
    cameraUpZ = cameraUpX*cameraFrontY-cameraUpY*cameraFrontX;
}

void Camera::moveForward(GLfloat const distance) {
    cameraPosX += distance*cameraFrontX;
    cameraPosY += distance*cameraFrontY;
    cameraPosZ += distance*cameraFrontZ;
}

void Camera::moveBack(GLfloat const distance) {
    cameraPosX -= distance*cameraFrontX;
    cameraPosY -= distance*cameraFrontY;
    cameraPosZ -= distance*cameraFrontZ;
}

void Camera::moveRight(GLfloat const distance) {
    cameraPosX += distance*cameraRightX;
    cameraPosY += distance*cameraRightY;
    cameraPosZ += distance*cameraRightZ;
}

void Camera::moveLeft(GLfloat const distance) {
    cameraPosX -= distance*cameraRightX;
    cameraPosY -= distance*cameraRightY;
    cameraPosZ -= distance*cameraRightZ;    
}

void Camera::rotate(GLfloat const pitch_, GLfloat const yaw_) {
    pitch -= pitch_;
    yaw += yaw_;
    //camera's front vector cannot be the same as up vector(0,1,0)
    //pitch is less than 90 degrees.
    if (pitch > 89) pitch = 89;
    if (pitch < -89) pitch = -89;
    SetCameraCoordinate();
}

#endif