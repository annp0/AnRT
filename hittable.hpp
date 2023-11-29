#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hit_record{
  public:
    point3 point;
    vec3 normal;
    double t;
    bool front;

    void set_front(const ray& r, const vec3& outward_normal){
        front = dot(r.direction(), outward_normal) < 0;
        normal = front? outward_normal : - outward_normal;
    }
};

class hittable{
  public:
    virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const = 0;
};

class hittable_list: public hittable {
  public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list(){}

    void add(shared_ptr<hittable> object){
        objects.push_back(object);
    }

    bool hit(const ray& r, double tmin, double tmax, hit_record& rec)const override;
};

bool hittable_list::hit(const ray& r, double tmin, double tmax, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_any = false;
    auto closest_so_far = tmax;

    for (const auto& object : objects){
        if (object->hit(r, tmin, closest_so_far, temp_rec)){
            hit_any = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_any;
}

#endif