#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record{
    public:
        point3 p;
        vec3 normal;
        FLOAT_FORMAT t;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal)
        {
            // Sets the hit record normal vector.
            // NOTE: the parameter is assumed have unit length.

            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class hittable{
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, FLOAT_FORMAT ray_tmin, FLOAT_FORMAT ray_tmax, hit_record& rec) const = 0;
};


#endif