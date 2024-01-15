#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "utils.h"
#include "interval.h"

//#include "material.h"

class material;
class hit_record{
    public:
        point3 p; // hit point
        vec3 normal;
        FLOAT_FORMAT t;
        bool front_face;

        shared_ptr<material> mat;

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

        virtual bool hit(const ray& r,  interval ray_t, hit_record& rec) const = 0;
};


#endif