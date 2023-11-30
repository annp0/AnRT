#include "sphere.hpp"
#include "hittable.hpp"
#include "utility.hpp"
#include "camera.hpp"

int main(){
    hittable_list world;

    auto ground_material = make_shared<diffuse>(rgb(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material1));
    world.add(make_shared<sphere>(point3(3, 0.2, 1.1), 0.2, material1));
    world.add(make_shared<sphere>(point3(3, 0.2, -2.1), 0.2, material1));
    world.add(make_shared<sphere>(point3(3, 0.2, 2), 0.2, material1));

    world.add(make_shared<sphere>(point3(0, 0.5, 0), 0.5, material1));
    world.add(make_shared<sphere>(point3(-3, 0.1, 2), 0.1, 
    make_shared<diffuse_light>(rgb(10, 10, 10))));
    world.add(make_shared<sphere>(point3(-4, 3, 1), 1, 
    make_shared<diffuse_light>(rgb(50, 50, 50))));

    auto material3 = make_shared<metal>(rgb(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material3));

    camera cam;

    cam.ratio = 16.0 / 9.0;
    cam.image_width = 1920;
    cam.samples_per_pixel = 500;
    cam.max_recursion_depth = 50;

    cam.v_fov = 20;
    cam.position = point3(13,2,3);
    cam.focus = point3(0,0,0);
    cam.up = vec3(0,1,0);
    cam.night = 1;
    cam.render(world);
}