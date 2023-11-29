#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "utility.hpp"

#include <iostream>

rgb ray_rgb(const ray& r, const hittable& world){
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)){
        return 0.5 * (rec.normal + rgb(1,1,1));
    }
    
    vec3 unit_direction = unit(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*rgb(1.0, 1.0, 1.0) + a*rgb(0.5, 0.7, 1.0);
}

int main() {
    // image 
    auto ratio = 16.0 / 9.0;
    int image_width = 1920;
    int image_height = static_cast<int>(image_width / ratio);
    
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));


    // camera
    auto focal_length = -1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width))/image_height;
    auto camera_position = point3(0,0,0);

    auto pixel_x = vec3(viewport_width, 0, 0) / image_width;
    auto pixel_y = vec3(0, viewport_height, 0) / image_height;

    auto pixel_topleft = camera_position + vec3(-viewport_width/2, viewport_height/2, focal_length) + 
                        0.5 * (pixel_x - pixel_y);
    
    std::clog << "Rendering...\n";
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++){
        for (int i = 0; i < image_width; i++){ 
            auto pixel_position = pixel_topleft + (i * pixel_x) - (j * pixel_y);
            auto ray_direction = pixel_position - camera_position;
            ray r(camera_position, ray_direction);
            rgb color = ray_rgb(r, world);
            write_rgb(std::cout, color);
        }
    }
    std::clog << "Done.\n";
}