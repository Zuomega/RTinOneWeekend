#include <iostream>

#include "color.h"
#include "vector3.h"
#include "ray.h"


bool hit_sphere(const point3& center, FLOAT_FORMAT radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b =  dot(2.0*r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

color ray_color(const ray& r)
{
    if(hit_sphere(point3(0,0,-1),0.5, r))
    {
        return color(1,1,0);
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

            color pixel_color = ray_color(r);

           write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                          \n";
}