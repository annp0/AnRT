#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "utility.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "hittable.hpp"

class material{
  public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, rgb& attenuation, ray&scattered) const = 0;
};

class diffuse: public material{
  public:
    diffuse(const rgb& color) {albedo = color;}
    virtual bool scatter(const ray& r_in, const hit_record& rec, rgb& attenuation, ray&scattered) const override;

  private:
    rgb albedo;
};

bool diffuse::scatter(const ray& r_in, const hit_record& rec, rgb& attenuation, ray&scattered) const{
    auto scatter_direction = rec.normal + random_unit_vec();

    if (is_near_zero(scatter_direction)) scatter_direction = rec.normal;

    scattered = ray(rec.point, scatter_direction);
    attenuation = albedo;
    return true;
}

class metal: public material{
  public:
    metal(const rgb& color) {albedo = color;}
    virtual bool scatter(const ray& r_in, const hit_record& rec, rgb& attenuation, ray&scattered) const override;

  private:
    rgb albedo;
};

bool metal::scatter(const ray& r_in, const hit_record& rec, rgb& attenuation, ray&scattered) const{
    vec3 reflected = reflect(unit(r_in.direction()), rec.normal);
    scattered = ray(rec.point, reflected);
    attenuation = albedo;
    return true;
}

#endif