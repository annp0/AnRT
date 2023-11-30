# AnRT: A 3D Ray Tracing Rendering Engine

**This program is still in early development.**

## Output Showcase

![](image.jpeg)

## Compile

To compile the program, install the `gcc` tool chain and run

```
g++ main.cpp -o anrt -O3
```

This will produce the `anrt` binary.

## Usage

The program will log to `stdlog` and output to `stdout`. To pipe the output into a file, run 

```
./anrt > image.ppm
```

## APIs