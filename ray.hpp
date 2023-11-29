#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray{
  public:

    ray(const point3& orig, const vec3& direc){ ori = orig; dir = direc;}

    point3 origin() const {return ori;}
    vec3 direction() const {return dir;}

    point3 ev(double t) const {
        return ori + t * dir;
    }

  private:
    point3 ori;
    point3 dir;
};

#endif