#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vector3.h"

class sphere : public hittable{
    public:
        sphere(point3 _center, FLOAT_FORMAT _radius) : center(_center), radius(_radius){}

        bool hit(const ray& r, FLOAT_FORMAT ray_tmin, FLOAT_FORMAT ray_tmax, hit_record& rec) const override 
        {
            vec3 oc = r.origin() - center;
            auto a = r.direction().length_squared();
            auto half_b = dot(oc, r.direction());
            auto c = oc.length_squared() - radius * radius;

            auto discriminant = half_b * half_b - a * c;
            if(discriminant < 0) return false;
            auto sqrtd = sqrt(discriminant);

            // find the nearest root that lies in the acceptable range.
            auto root = (-half_b - sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
            {
                root = (-half_b + sqrtd) / a;
                if (root <= ray_tmin || ray_tmax <= root)
                {
                    return false;
                }
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            // rec.normal = (rec.p - center) / radius;

            return true;
        }

    private:
        point3 center;
        FLOAT_FORMAT radius;
};

#endif