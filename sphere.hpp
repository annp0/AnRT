#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable{
  public:
    sphere(point3 _center, double _radius, shared_ptr<material> _material){
        center = _center;
        radius = _radius;
        mat = _material;
    }

    virtual bool hit(const ray& r, interval i, hit_record& rec) const override;

  private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
};

bool sphere::hit(const ray& r, interval i, hit_record& rec) const{
    vec3 oc = r.origin() - center;
    auto a = r.direction().norm_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.norm_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrt_d = sqrt(discriminant);

    auto root = (-half_b - sqrt_d) / a;
    if (!i.contains(root)) {
        root = (-half_b + sqrt_d) / a;
        if (!i.contains(root)){
            return false;
        }
    }

    rec.t = root;
    rec.point = r.ev(root);
    rec.normal = (rec.point - center) / radius;

    vec3 outward_normal = (rec.point - center) / radius;
    rec.set_front(r, outward_normal);
    rec.mat = mat;

    return true;
}

#endif