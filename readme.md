# AnRT: A 3D Ray Tracing Rendering Engine

## Output Showcase

![](image.jpeg)

## Compilation

To compile the program, install the `gcc` tool chain and run

```
g++ main.cpp -o anrt -O3
```

This will produce the `anrt` binary. From my experience, the `-O3` flag significantly improves the performance of the program.

## Usage

The program will log to `stdlog` and output to `stdout`. To pipe the output into a file, run 

```
./anrt > image.ppm
```
and logs will be displayed on the terminal, like this:
```
Rendering... 100% 
Done.
```

## APIs

The objects that need to be rendered are stored in `hittable_list world`. To append an object to `world`, simply use `hittable_list::add`.

Currently there is only one avaliable class of objects `sphere`. `sphere::sphere(point3& p, double r, material& mat)` returns a sphere centered at `p` with radius `r` and material `mat`.

There are 4 types of materials:

- `diffuse`: The diffuse reflection surface. Takes one argument, which determines its color.

- `diffuse_light`: The diffuse light source. Takes one argument that determines its color and brightness (the higher the rgb value, the brighter it is).

- `metal`: The specular relection surface. Takes two arguments: one for its color, and the other for the fuziness.

- `dielectric`: Class for glass-like objects. Takes in one argument - its refractive index relative to air.

The parameters for class `camera` is straightforward. When `night` is set to `0`, the background will be the while-blue sky-like texture and will light up the scene. When `night` is set to `1`, the background will be pure darkness and explicit lighting is required to light up the scene.