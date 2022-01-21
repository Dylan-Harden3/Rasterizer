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

	size_t numVertices = posBuf.size() / 3;
	cout << "Number of vertices: " << numVertices << endl;

	size_t numTriangles = numVertices / 3;
	cout << "Number of triangles: " << numTriangles << endl;

	vector<triangle> triangles;

	// add triangles from posBuf to triangles array
	for (int i = 0; i < posBuf.size(); i += 9) {
		float v1[] = { posBuf[i], posBuf[i + 1], posBuf[i + 2] };
		float v2[] = { posBuf[i + 3], posBuf[i + 4], posBuf[i + 5] };
		float v3[] = { posBuf[i + 6], posBuf[i + 7], posBuf[i + 8] };
		triangles.push_back(triangle(v1, v2, v3));
	}

	return 0;
}