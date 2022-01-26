#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <algorithm>
using namespace std;
class triangle {
    
    public:

    const double RANDOM_COLORS[7][3] = {
        {0.0000,    0.4470,    0.7410},
        {0.8500,    0.3250,    0.0980},
        {0.9290,    0.6940,    0.1250},
        {0.4940,    0.1840,    0.5560},
        {0.4660,    0.6740,    0.1880},
        {0.3010,    0.7450,    0.9330},
        {0.6350,    0.0780,    0.1840},
    };

    // vertices
    float v1[3], v2[3], v3[3];
    // bounding box
    float minX, maxX, minY, maxY;
    // colors
    unsigned char red, green, blue;
    // per vertex colors (task 3)
    float v1Color[3], v2Color[3], v3Color[3];

    void setboundingbox() {

        // x, y z
        float x[3] = { v1[0], v2[0], v3[0] };
        float y[3] = { v1[1], v2[1], v3[1] };
        float z[3] = { v1[2], v2[2], v3[2] };

        // get min/max x and y coordinates
        this->minX = *min_element(x, x + 3);
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

    // make a triangle out of 3 vertices without colors
    triangle(float vertex1[3], float vertex2[3], float vertex3[3], int triangleCounter) :
        v1{ vertex1[0], vertex1[1], vertex1[2] },
        v2{ vertex2[0], vertex2[1], vertex2[2] },
        v3{ vertex3[0], vertex3[1], vertex3[2] } {

        this->v1Color[0] = this->RANDOM_COLORS[triangleCounter % 7][0];
        this->v1Color[1] = this->RANDOM_COLORS[triangleCounter % 7][1];
        this->v1Color[2] = this->RANDOM_COLORS[triangleCounter % 7][2];

        this->v2Color[0] = this->RANDOM_COLORS[(triangleCounter + 1) % 7][0];
        this->v2Color[1] = this->RANDOM_COLORS[(triangleCounter + 1) % 7][1];
        this->v2Color[2] = this->RANDOM_COLORS[(triangleCounter + 1) % 7][2];

        this->v3Color[0] = this->RANDOM_COLORS[(triangleCounter + 2) % 7][0];
        this->v3Color[1] = this->RANDOM_COLORS[(triangleCounter + 2) % 7][1];
        this->v3Color[2] = this->RANDOM_COLORS[(triangleCounter + 2) % 7][2];

        //cout << this->v1Color[0] << " " << this->v2Color[0] << " " << this->v3Color[0] << endl;
       
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