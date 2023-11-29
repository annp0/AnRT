#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "color.hpp"
#include "hittable.hpp"
#include "ray.hpp"

#include <iostream>

class camera{
  public:
    double ratio;
    int image_width;
    int samples_per_pixel;

    void render(const hittable& world);

  private:
    int image_height;
    point3 camera_position;
    point3 pixel_topleft;
    point3 pixel_x;
    point3 pixel_y;

    void initialize();
    rgb ray_rgb(const ray& r, const hittable& world);
    ray get_ray(int i, int j) const;
    vec3 sample_pixel() const {
        return ((-0.5 + random_double()) * pixel_x) +
               ((-0.5 + random_double()) * pixel_y);
    }
};

void camera::initialize(){
    image_height = static_cast<int>(image_width / ratio);

    auto focal_length = -1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width))/image_height;
    camera_position = point3(0,0,0);

    pixel_x = vec3(viewport_width, 0, 0) / image_width;
    pixel_y = vec3(0, viewport_height, 0) / image_height;

    pixel_topleft = camera_position + vec3(-viewport_width/2, viewport_height/2, focal_length) + 
                        0.5 * (pixel_x - pixel_y);
}

rgb camera::ray_rgb(const ray& r, const hittable& world){
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)){
        return 0.5 * (rec.normal + rgb(1,1,1));
    }
    
    vec3 unit_direction = unit(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*rgb(1.0, 1.0, 1.0) + a*rgb(0.5, 0.7, 1.0);
}

void camera::render(const hittable& world){
    initialize();

    std::clog << "Rendering...\n";
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++){
        for (int i = 0; i < image_width; i++){ 
            rgb pixel_color(0,0,0);
            for (int sample = 0; sample < samples_per_pixel; sample++){
                ray r = get_ray(i,j);
                pixel_color += ray_rgb(r, world);
            }
            write_rgb(std::cout, pixel_color, samples_per_pixel);
        }
        std::cout << "\n"; 
    }
    std::clog << "Done.\n";
}

ray camera::get_ray(int i, int j) const {
    auto pixel_center = pixel_topleft + (i * pixel_x) - (j * pixel_y);
    auto pixel_sample = pixel_center + sample_pixel();
    return ray(camera_position, pixel_sample - camera_position);
}

#endif