#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable{
  public:
    sphere(point3 _center, double _radius){
        center = _center;
        radius = _radius;
    }

    virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override;

  private:
    point3 center;
    double radius;
};

bool sphere::hit(const ray& r, double tmin, double tmax, hit_record& rec) const{
    vec3 oc = r.origin() - center;
    auto a = r.direction().norm_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.norm_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrt_d = sqrt(discriminant);

    auto root = (-half_b - sqrt_d) / a;
    if (root <= tmin || tmax <= root) {
        root = (-half_b + sqrt_d) / a;
        if (root <= tmin || tmax <= root){
            return false;
        }
    }

    rec.t = root;
    rec.point = r.ev(root);
    rec.normal = (rec.point - center) / radius;

    vec3 outward_normal = (rec.point - center) / radius;
    rec.set_front(r, outward_normal);

    return true;
}

#endif