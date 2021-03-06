#Homework 5

View and Perspective

视角空间和投影

1. Projections

Projection define how a virtual 3D world projects into a 2D screen such that we can see it. There are 2 kinds of projections are used in OpenGL: perspective projection and orthographic projection.

Place the cube in (0.5,-0.5,-1.5) and create a orthographic projection. Show what you get in the report. Try different parameters(i.e. left, right, bottom, top, near, far), and write down how these parameters affect result in the report.

Place the cube in (0.5,-0.5,-1.5) and create a perspective projection. Show what you get in the report. Try different parameters, and write down how these parameters affect result in the report.

Use exactly same parameters for 2 projections and discuss the differences of 2 results. Post the result in your report and discuss why.

Write down your main algrithm in the report.

2. View Changing

You are required to change the view of the camera to observe the cube.

Place the cube in (0,0,0), use the perspective projection. Import glu.h, try gluLookat(...) function. Let your camera circle around the cube, but looking at the cube all the time.

Show the results and write down your main algrithm in the report.

In practice, the camera setting is actually stored in a matrix called View matrix. The transformations is also stored in a matrix called Model matrix. However, in OpenGL, these two matrices is actually one matrix called ModelView matrix. Discuss why it is so in the report. (Hints: Is there an actual camera object in virtual world? If there is not, how to pretend we have one?)

Hints: You may want to change your camera position in a circle. Try:

camPosX=sin(clock()/1000.0)*Radius;
camPosZ=cos(clock()/1000.0)*Radius;
Since sin(x)^2+cos(x)^2=1, that make sure we form a circle in XoZ plane.

3. Bonus: the Camera Class

Implement a Camera class to provide a FPS (First Person Shooting) view, which means when you press w,a,s,d, it would feel like if you were ‘walking around’ in the virtual world. When you move your mouse, it would feel like if you were ‘looking around’.

Hints: 
The header of the Camera may be:(You can change it if you like)

class Camera{
public:
	...
	void moveForward(GLfloat const distance);
	void moveBack(GLfloat const distance);
	void moveRight(GLfloat const distance);
	void moveLeft(GLfloat const distance);
	...
	void rotate(GLfloat const pitch, GLfloat const yaw);
	...
private:
	...
	GLfloat pfov,pratio,pnear,pfar;
	GLfloat cameraPosX,cameraPosY,cameraPosZ;
	GLfloat cameraFrontX,cameraFrontY,cameraFrontZ;
	GLfloat cameraRightX,cameraRightY,cameraRightZ;
	GLfloat cameraUpX,cameraUpY,cameraUpZ;
	...
};
P.S. In the method void Camera::rotate(GLfloat const pitch, GLfloat const yaw), ‘pitch’ and ‘yaw’ means the Euler angles. Euler angles are 3 values that can represent any rotation in 3D, defined by Leonhard Euler somewhere in the 1700s.
The following image gives them a visual meaning:
https://sysucg.github.io/images/pyr.png
