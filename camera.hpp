#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "color.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "material.hpp"

#include <iostream>

class camera{
  public:
    double ratio = 1.0;
    int image_width = 400;
    int samples_per_pixel = 10;
    int max_recursion_depth = 10;
    int night = 0;

    double v_fov = 90;
    point3 position = point3(0,0,-1);
    point3 focus = point3(0,0,0);
    vec3 up = vec3(0,1,0);

    void render(const hittable& world);

  private:
    int image_height;
    point3 pixel_topleft;
    point3 pixel_x;
    point3 pixel_y;
    vec3 u, v, w;

    void initialize();
    rgb ray_rgb(const ray& r, int depth, const hittable& world, bool night);
    ray get_ray(int i, int j) const;
    vec3 sample_pixel() const {
        return ((-0.5 + random_double()) * pixel_x) +
               ((-0.5 + random_double()) * pixel_y);
    }
};

void camera::initialize(){
    image_height = static_cast<int>(image_width / ratio);

    auto focal_length = (position - focus).norm();
    auto theta = deg_to_rad(v_fov);
    auto viewport_height = 2 * focal_length * tan(theta / 2);
    auto viewport_width = viewport_height * (static_cast<double>(image_width))/image_height;

    w = unit(position - focus);
    u = unit(cross(up, w));
    v = cross(w, u);

    vec3 viewport_u = viewport_width * u;
    vec3 viewport_v = viewport_height * (-v);

    pixel_x = viewport_u / image_width;
    pixel_y = viewport_v / image_height;

    auto viewport_topleft = position - focal_length * w - viewport_u /2 - viewport_v /2;
    pixel_topleft = viewport_topleft + 0.5 * (pixel_x + pixel_y);
}

rgb background(const vec3& r, bool night){
    if (night) return rgb(0, 0, 0);
    else{
        auto a = 0.5*(r.y() + 1.0);
        return (1.0-a)*rgb(1.0, 1.0, 1.0) + a*rgb(0.5, 0.7, 1.0);
    }
}

rgb camera::ray_rgb(const ray& r, int depth, const hittable& world, bool night){
    hit_record rec;

    if (depth <= 0) return rgb(0, 0, 0);

    if (world.hit(r, interval(0.0001, infinity), rec)){
        ray scattered;
        rgb attenuation;
        rgb emission = rec.mat->emit();
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_rgb(scattered, depth - 1, world, night);
        else return emission;
        return rgb(0,0,0);
    }
    
    vec3 unit_direction = unit(r.direction());
    return background(unit_direction, night);
}

void camera::render(const hittable& world){
    initialize();

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++){
        std::clog << "\rRendering... " << static_cast<int>(((double)j / (double)image_height) * 100) + 1 << "% " << std::flush;
        for (int i = 0; i < image_width; i++){ 
            rgb pixel_color(0,0,0);
            for (int sample = 0; sample < samples_per_pixel; sample++){
                ray r = get_ray(i,j);
                pixel_color += ray_rgb(r, max_recursion_depth, world, night);
            }
            write_rgb(std::cout, pixel_color, samples_per_pixel);
        }
        std::cout << "\n"; 
    }
    std::clog << "\nDone.\n";
}

ray camera::get_ray(int i, int j) const {
    auto pixel_center = pixel_topleft + (i * pixel_x) + (j * pixel_y);
    auto pixel_sample = pixel_center + sample_pixel();
    return ray(position, pixel_sample - position);
}

#endif