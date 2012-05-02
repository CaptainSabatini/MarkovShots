#ifndef CAMERA_H
#define CAMERA_H



class Camera : public RigidBody
{
private:
        float FOV;
        float aspectRatio;
        float distance;
        float maxN;
public:
        //Constructors
    Camera();
    Camera(Camera& source);

    //Getters
    float getFOV();
    float getAspectRatio();
    float getDistance();
    float getMaxN();

    //Setters
    void setFOV(float fov);
    void setAspectRatio(float ratio);
    void setDistance(float d);
    void setmaxN(float n);

    /////////////////////////////////////////////////////////////////////
    //Returns wether the point is in view
    //This is solely determined by the point being between d and maxN
    //FOV is not taken into account because zoom could be larger than screen
    //
    //Input: Point to compare
    //Output: bool saying in or out of view
    /////////////////////////////////////////////////////////////////////
    bool isInView(Vector3f p);

    /////////////////////////////////////////////////////////////////////
    //This method projects a 3D point on the global coordinates into
    //a 2D point in the camera's image plane (can be out of field of view)
    //
    //Input: Point p to project to a Point Q(by reference)
    //Output: bool verifying projection
    /////////////////////////////////////////////////////////////////////
    //bool project(const Point3f p, Point3f& Q);

    void moveEye(int dir);
    void moveLook(int dir);
    void rotateLoc(float deg, float x, float y, float z);
    void setView();
};

#endif // CAMERA_H
