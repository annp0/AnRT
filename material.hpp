#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "utility.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "hittable.hpp"

class material{
  public:
    virtual rgb emit() const {return rgb(0,0,0);}
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
    metal(const rgb& color, double f) {
        albedo = color;
        fuzz = f < 1 ? f : 1;
    }
    virtual bool scatter(const ray& r_in, const hit_record& rec, rgb& attenuation, ray&scattered) const override;

  private:
    rgb albedo;
    double fuzz;
};

bool metal::scatter(const ray& r_in, const hit_record& rec, rgb& attenuation, ray&scattered) const{
    vec3 reflected = reflect(unit(r_in.direction()), rec.normal);
    scattered = ray(rec.point, reflected + fuzz * random_unit_vec());
    attenuation = albedo;
    return true;
}

class dielectric: public material{
  public:
    dielectric(double _ri) {ri = _ri;}
    virtual bool scatter(const ray& r_in, const hit_record& rec, rgb& attenuation, ray&scattered) const override;

  private:
    double ri;
    static double reflectance(double cos, double index){
      auto r0 = (1 - index) / (1 + index);
      return r0 * r0 + (1 - r0 * r0)*pow((1-cos), 5);
    }
};

bool dielectric::scatter(const ray& r_in, const hit_record& rec, rgb& attenuation, ray&scattered) const{
    attenuation = rgb(1.0, 1.0, 1.0);
    double ratio = rec.front? (1.0/ri) : ri;
    vec3 unit_direction = unit(r_in.direction());
    double cos = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin = sqrt(1.0 - cos * cos);
    vec3 direction;
    if (ratio * sin > 1.0 || reflectance(cos, ratio) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else direction = refract(unit_direction, rec.normal, ratio);
    scattered = ray(rec.point, direction);
    return true;
}

class diffuse_light: public material{
  public:
    diffuse_light(rgb _c){color = _c;}
    virtual bool scatter(const ray& r_in, const hit_record& rec, rgb& attenuation, ray&scattered) const override {return false;}
    virtual rgb emit() const override{return color;}

  private:
    rgb color;
};

#endif