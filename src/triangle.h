#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <algorithm>
using namespace std;
class triangle {
    
    public:
    // vertices
    float v1[3], v2[3], v3[3];
    // bounding box
    float minX, maxX, minY, maxY;
    // colors
    unsigned char red, green, blue;

    void setboundingbox() {

        // x, y z
        float x[3] = { v1[0], v2[0], v3[0] };
        float y[3] = { v1[1], v2[1], v3[1] };
        float z[3] = { v1[2], v2[2], v3[2] };

        // get min/max x and y coordinates
        this->minX = *min_element(x, x+3);
        this->minY = *min_element(y, y + 3);
        this->maxX = *max_element(x, x + 3);
        this->maxY = *max_element(y, y + 3);

    }

    // make a triangle out of 3 vertices
    triangle(float vertex1[3], float vertex2[3], float vertex3[3], unsigned char red, unsigned char green, unsigned char blue) : 
        v1{ vertex1[0], vertex1[1], vertex1[2] }, 
        v2{ vertex2[0], vertex2[1], vertex2[2] }, 
        v3{ vertex3[0], vertex3[1], vertex3[2] },
        red(red), green(green), blue(blue) {

        this->setboundingbox();

    }

    // Convert points to image space
    void convert(float scale, float transX, float transY) {
        
        // convert vertices
        this->v1[0] = floor(scale * this->v1[0] + transX);
        this->v1[1] = floor(scale * this->v1[1] + transY);
        this->v2[0] = floor(scale * this->v2[0] + transX);
        this->v2[1] = floor(scale * this->v2[1] + transY);
        this->v3[0] = floor(scale * this->v3[0] + transX);
        this->v3[1] = floor(scale * this->v3[1] + transY);

        this->setboundingbox();

    }

};

#endif /* TRIANGLE_H */