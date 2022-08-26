
# Rasterizer
Reades in vertex positions from .obj file and colors each pixel based on which task is entered along with the image size.

## Task 1: Bounding boxes
Colors the bounding box for each triangle in the mesh, cycling through 7 different colors.
<br>
<br>
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene1-bunny.png" width=300 />
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene1-teapot.png" width=300 />

## Task 2: Triangles
Colors each triangle in the mesh, cycling through those same 7 colors.
<br>
<br>
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene2-bunny.png" width=300 />
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene2-teapot.png" width=300 />

## Task 3: Interpolating Per-Vertex
Colors each pixel using its barycentric coordinates weighted with each of the 3 vertices.
<br>
<br>
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene3-bunny.png" width=300 />
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene3-teapot.png" width=300 />

## Task 4: Vertical Color
Colors each mesh with a linear gradient from red to blue.
<br>
<br>
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene4-bunny.png" width=300 />
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene4-teapot.png" width=300 />

## Task 5: Z-Buffer
Colors each pixel based on its z-value, mapped to red. Closer is brighter and farther away is darker.
<br>
<br>
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene5-bunny.png" width=300 />
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene5-teapot.png" width=300 />

## Task 6: Normal Coloring
Colors each pixel based on the vertex normals, mapped as: x->red y->blue z->green.
<br>
<br>
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene6-bunny.png" width=300 />
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene6-teapot.png" width=300 />

## Task 7: Lighting 
Adds lighting based on the dot product between the light vector and normal, mapped to (r,g,b) equally.
<br>
<br>
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene7-bunny.png" width=300 />
<img src="https://github.com/Dylan-Harden3/Rasterizer/blob/master/results/scene7-teapot.png" width=300 />
