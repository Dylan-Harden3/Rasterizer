#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"
#include "triangle.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

double RANDOM_COLORS[7][3] = {
	{0.0000,    0.4470,    0.7410},
	{0.8500,    0.3250,    0.0980},
	{0.9290,    0.6940,    0.1250},
	{0.4940,    0.1840,    0.5560},
	{0.4660,    0.6740,    0.1880},
	{0.3010,    0.7450,    0.9330},
	{0.6350,    0.0780,    0.1840},
};

// find scale given min/max world coords and deltaimg
float findScale(float minWorld, float maxWorld, int changeImage) {
	return (changeImage / (maxWorld - minWorld));
}

// convert point from world space to image space
float convertPoint(float point, float scale, float trans) {
	return floor(scale * point + trans);
}

// color the bounding box for a given triangle
void colorBoundingBox(shared_ptr<Image>& image, triangle& triangle) {
	for (int x = triangle.minX ; x < triangle.maxX ;  x++) {
		for (int y = triangle.minY; y < triangle.maxY; y++) {
			image->setPixel(x, y, triangle.red, triangle.green, triangle.blue);
		}
	}
}

// function for task 1
void drawBoundingBoxes(vector<float>& posBuf, float imgWidth, float imgHeight, string outputFilename) {

	vector<triangle> triangles;

	// Bounding box for whole image
	float minX = posBuf[0];
	float minY = posBuf[1];
	float maxX = posBuf[0];
	float maxY = posBuf[1];

	int triangleCounter = 0;
	// add triangles from posBuf to triangles vector
	for (int i = 0; i < posBuf.size(); i += 9) {

		float v1[3] = { posBuf[i], posBuf[i + 1], posBuf[i + 2] };
		float v2[3] = { posBuf[i + 3], posBuf[i + 4], posBuf[i + 5] };
		float v3[3] = { posBuf[i + 6], posBuf[i + 7], posBuf[i + 8] };

		// update min/max x and y
		float x[3] = { posBuf[i], posBuf[i + 3], posBuf[i + 6] };
		float y[3] = { posBuf[i + 1], posBuf[i + 4], posBuf[i + 7] };

		// update bounding box
		minX = min(minX, *min_element(x, x + 3));
		minY = min(minY, *min_element(y, y + 3));
		maxX = max(maxX, *max_element(x, x + 3));
		maxY = max(maxY, *max_element(y, y + 3));

		// add triangle to list
		triangles.push_back(triangle(v1, v2, v3, (unsigned char)(RANDOM_COLORS[triangleCounter % 7][0] * 255), (unsigned char)(RANDOM_COLORS[triangleCounter % 7][1] * 255), (unsigned char)(RANDOM_COLORS[triangleCounter % 7][2] * 255)));

		triangleCounter++;
	}

	// find scale factor
	float scale = min(findScale(minX, maxX, imgWidth), findScale(minY, maxY, imgHeight));

	// find middle of image and world
	float middleImg[2] = { imgWidth / 2, imgHeight / 2 };
	float middleWorld[2] = { (minX + maxX) / 2, (minY + maxY) / 2 };

	// find translation x and y
	float transX = middleImg[0] - scale * middleWorld[0];
	float transY = middleImg[1] - scale * middleWorld[1];

	// update bounding box
	minX = convertPoint(minX, scale, transX);
	minY = convertPoint(minY, scale, transY);
	maxX = convertPoint(maxX, scale, transX);
	maxY = convertPoint(maxY, scale, transY);

	// Convert triangles to image space
	for (int i = 0; i < triangles.size(); i++) {
		triangles[i].convert(scale, transX, transY);
	}

	// Create image
	auto image = make_shared<Image>(imgWidth, imgHeight);

	// Color bounding boxs for all triangles
	for (int i = 0; i < triangles.size(); i++) {
		colorBoundingBox(image, triangles[i]);
	}

	// output image
	image->writeToFile(outputFilename);

}

// The following code for sign() and pointInTriagle() was adopted from: 
// https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle

float sign(float v1[3], float v2[3], float v3[3]) {
	return (v1[0] - v3[0]) * (v2[1] - v3[1]) - (v2[0] - v3[0]) * (v1[1] - v3[1]);
}

bool pointInTriangle(float pt[3], float v1[3], float v2[3], float v3[3]) {
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(pt, v1, v2);
	d2 = sign(pt, v2, v3);
	d3 = sign(pt, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

// color the pixels within a given triangle
void colorTriangle(shared_ptr<Image>& image, triangle& triangle) {
	for (int x = triangle.minX; x < triangle.maxX; x++) {
		for (int y = triangle.minY; y < triangle.maxY; y++) {
			float point[3] = { x, y, 0};
			if (pointInTriangle(point, triangle.v1, triangle.v2, triangle.v3)) {
				image->setPixel(x, y, triangle.red, triangle.green, triangle.blue);
			}
		}
	}
}

// function for task 2
void drawTriangles(vector<float>& posBuf, float imgWidth, float imgHeight, string outputFilename) {

	vector<triangle> triangles;

	// Bounding box for whole image
	float minX = posBuf[0];
	float minY = posBuf[1];
	float maxX = posBuf[0];
	float maxY = posBuf[1];

	int triangleCounter = 0;
	// add triangles from posBuf to triangles vector
	for (int i = 0; i < posBuf.size(); i += 9) {

		float v1[3] = { posBuf[i], posBuf[i + 1], posBuf[i + 2] };
		float v2[3] = { posBuf[i + 3], posBuf[i + 4], posBuf[i + 5] };
		float v3[3] = { posBuf[i + 6], posBuf[i + 7], posBuf[i + 8] };

		// update min/max x and y
		float x[3] = { posBuf[i], posBuf[i + 3], posBuf[i + 6] };
		float y[3] = { posBuf[i + 1], posBuf[i + 4], posBuf[i + 7] };

		// update bounding box
		minX = min(minX, *min_element(x, x + 3));
		minY = min(minY, *min_element(y, y + 3));
		maxX = max(maxX, *max_element(x, x + 3));
		maxY = max(maxY, *max_element(y, y + 3));

		// add triangle to list
		triangles.push_back(triangle(v1, v2, v3, (unsigned char)(RANDOM_COLORS[triangleCounter % 7][0] * 255), (unsigned char)(RANDOM_COLORS[triangleCounter % 7][1] * 255), (unsigned char)(RANDOM_COLORS[triangleCounter % 7][2] * 255)));

		triangleCounter++;
	}

	// find scale factor
	float scale = min(findScale(minX, maxX, imgWidth), findScale(minY, maxY, imgHeight));

	// find middle of image and world
	float middleImg[2] = { imgWidth / 2, imgHeight / 2 };
	float middleWorld[2] = { (minX + maxX) / 2, (minY + maxY) / 2 };

	// find translation x and y
	float transX = middleImg[0] - scale * middleWorld[0];
	float transY = middleImg[1] - scale * middleWorld[1];

	// update bounding box
	minX = convertPoint(minX, scale, transX);
	minY = convertPoint(minY, scale, transY);
	maxX = convertPoint(maxX, scale, transX);
	maxY = convertPoint(maxY, scale, transY);

	// Convert triangles to image space
	for (int i = 0; i < triangles.size(); i++) {
		triangles[i].convert(scale, transX, transY);
	}

	// Create image
	auto image = make_shared<Image>(imgWidth, imgHeight);

	// Color bounding boxs for all triangles
	for (int i = 0; i < triangles.size(); i++) {
		colorTriangle(image, triangles[i]);
	}

	// output image
	image->writeToFile(outputFilename);

}

int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Usage: A1 meshfile" << endl;
		return 0;
	}

	// Accept Command Line Arguments
	// Ensurre correct number of arguments
	if (argc != 6) {

		cout << "Invalid command line args, you entered:" << endl;

		for (int i = 1; i < argc; i++) {

			cout << argv[i] << endl;

		}

		cout << "Input should be in the form <input filename> <output filename> <output image width> <output image height> <task number>" << endl;

		return 0;
	}
	// Input filename of the.obj file to rasterize
	string meshName(argv[1]);

	if (meshName.substr(meshName.size() - 4) != ".obj") {
		cout << "input mesh must be a .obj file" << endl;
		return 0;
	}

	// Output image filename(should be png)
	string outputFilename = argv[2];

	if (outputFilename.substr(outputFilename.size() - 4) != ".png") {
		cout << "Output image must be a .png file" << endl;
		return 0;
	}

	// Image width
	int imgWidth = atoi(argv[3]);

	if (imgWidth <= 0) {
		cout << "image width must be positive" << endl;
		return 0;
	}

	// Image height
	int imgHeight = atoi(argv[4]);

	if (imgHeight <= 0) {
		cout << "image height must be positive" << endl;
		return 0;
	}

	// Task number(1 through 7)
	int taskNumber = atoi(argv[5]);

	if (taskNumber < 1 || taskNumber > 7) {
		cout << "task number must be 1-7 you entered " << taskNumber << endl;
		return 0;
	}

	// Load geometry
	vector<float> posBuf; // list of vertex positions
	vector<float> norBuf; // list of vertex normals
	vector<float> texBuf; // list of vertex texture coords
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if (!rc) {
		cerr << errStr << endl;
	}
	else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
					if (!attrib.normals.empty()) {
						norBuf.push_back(attrib.normals[3 * idx.normal_index + 0]);
						norBuf.push_back(attrib.normals[3 * idx.normal_index + 1]);
						norBuf.push_back(attrib.normals[3 * idx.normal_index + 2]);
					}
					if (!attrib.texcoords.empty()) {
						texBuf.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
						texBuf.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
					}
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}

	// do desired task based on input
	if (taskNumber == 1) drawBoundingBoxes(posBuf, imgWidth, imgHeight, outputFilename);
	if (taskNumber == 2) drawTriangles(posBuf, imgWidth, imgHeight, outputFilename);

	return 0;
}
