#include "sphere.hpp"
#include "hittable.hpp"
#include "utility.hpp"
#include "camera.hpp"

int main(){
    hittable_list world;

    auto material_ground = make_shared<diffuse>(rgb(0.8, 0.8, 0.0));
    auto material_center = make_shared<diffuse>(rgb(0.7, 0.3, 0.3));
    auto material_left   = make_shared<metal>(rgb(0.8, 0.8, 0.8));
    auto material_right  = make_shared<metal>(rgb(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    -0.4, -1.0),   0.1, material_center));
    world.add(make_shared<sphere>(point3(-0.5,    -0.1, -1.2),   0.4, material_left));
    world.add(make_shared<sphere>(point3( 0.3,    -0.3, -1.3),   0.2, material_right));
    camera cam;

    cam.ratio = 16.0 / 9.0;
    cam.image_width = 1080;
    cam.samples_per_pixel = 100;
    cam.max_recursion_depth = 50;
    
    cam.render(world);
}