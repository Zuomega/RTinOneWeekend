#include <iostream>

#include "color.h"
#include "vector3.h"
#include "ray.h"
#include "utils.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"


// FLOAT_FORMAT hit_sphere(const point3& center, FLOAT_FORMAT radius, const ray& r)
// {
//     vec3 oc = r.origin() - center;
//     auto a = r.direction().length_squared();
//     auto half_b =  dot(oc, r.direction());
//     auto c = oc.length_squared() - radius * radius;
//     auto discriminant = half_b*half_b - a*c;
//     if (discriminant < 0)
//     {
//         return -1.0;
//     }
//     else
//     {
//         return (-half_b - sqrt(discriminant)) /  a;
//     }
// }

color ray_color(const ray& r, const hittable& world)
{
    hit_record rec;
   if (world.hit(r, 0, infinity, rec))
   {
    return 0.5 * (rec.normal + color(1,1,1));
   }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    
    return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
    //return color(0,0,0);
}

int main()
{
    // Image Size
    auto aspect_ratio = 4.0 / 3.0;
    int img_w = 400;

    int img_h = static_cast<int>(img_w / aspect_ratio);
    img_h = (img_h < 1) ? 1 : img_h;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    auto focal_length = 1.0;
    auto viewport_h = 2.0;
    auto viewport_w = viewport_h * (static_cast<FLOAT_FORMAT>(img_w) / img_h); 
    auto camera_c = point3(0,0,0);

    auto viewport_u = vec3(viewport_w, 0, 0);
    auto viewport_v = vec3(0, -viewport_h, 0);

    auto pixel_delta_u = viewport_u / img_w;
    auto pixel_delta_v = viewport_v / img_h;

    auto viewport_upper_left = camera_c - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixelx0y0_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Output to file
    std::cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

    for (int j = 0; j < img_h; ++j)
    {
        std::clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;
        for(int i = 0 ; i < img_w; ++i)
        {
            auto pixel_c = pixelx0y0_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
            auto ray_direction = pixel_c - camera_c;
            ray r(camera_c, ray_direction);

            color pixel_color = ray_color(r, world);

           write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                          \n";
}