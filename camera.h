#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

#include "color.h"
#include "hittable.h"

#include <iostream>

class camera
{
public:
    // Image Size
    FLOAT_FORMAT aspect_ratio = 4.0 / 3.0; // Ratio of image width over height
    int img_w = 400; // Rendered image width in pixel count

    int sample_per_pixel; // Count of random samples for each pixel
    int max_depth = 10; // Maximum number of ray bounces into scene
    
    camera(FLOAT_FORMAT aspect_ratio, int img_w, int sample_per_pixel, int max_depth) 
    : aspect_ratio(aspect_ratio)
    , img_w(img_w)
    , sample_per_pixel(sample_per_pixel)
    , max_depth(max_depth)
    {

    }

    void render(const hittable & world)
    {
        this->initialize();

        std::cout << "P3\n" << img_w << ' ' << img_h << "\n255\n";

            for (int j = 0; j < img_h; ++j)
        {
            std::clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;
            for(int i = 0 ; i < img_w; ++i)
            {
                color pixel_color(0,0,0);
                for (int sample = 0; sample < sample_per_pixel; sample++)
                {
                    ray r = this->get_ray(i, j);
                    pixel_color += ray_color(r,max_depth, world);
                }

            write_color(std::cout, pixel_color, sample_per_pixel);
            }
        }
    std::clog << "\rDone.                          \n"; 
    }

private:
    int img_h = 0;
    point3 camera_c;
    point3 pixelx0y0_loc;
    point3 pixel_delta_u;
    point3 pixel_delta_v;
    void initialize()
    {
        camera_c = point3(0,0,0);

        img_h = static_cast<int>(img_w / aspect_ratio);
        img_h = (img_h < 1) ? 1 : img_h;

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_h = 2.0;
        auto viewport_w = viewport_h * (static_cast<FLOAT_FORMAT>(img_w) / img_h); 
        
         // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_w, 0, 0);
        auto viewport_v = vec3(0, -viewport_h, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / img_w;
        pixel_delta_v = viewport_v / img_h;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left = camera_c + (-vec3(0, 0, focal_length)) - viewport_u/2 - viewport_v/2;
        pixelx0y0_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    }

    ray get_ray(int i, int j) const{
        // Get a randomly sampled camera ray for the pixel at location i, j.

        auto pixel_c = pixelx0y0_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
        auto pixel_sample = pixel_c + pixel_sample_square();

        auto ray_origin = camera_c;
        

        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 pixel_sample_square() const {
        // Returns a random point in the square surrounding a pixel at
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }

    color ray_color(const ray & r, int depth, const hittable & world) const{
        hit_record rec;

        if (depth <= 0)
        {
            return color(0,0,0);
        }
        interval ray_t(0.001, infinity);
        // 0.001 is to reject the inter of a reflect ray just at the surface.
        if (world.hit(r,  ray_t, rec))
        {
            vec3 direction = rec.normal + random_on_hemisphere(rec.normal);
            return 0.7 * ray_color(ray(rec.p, direction), depth-1, world);
        }
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        
        return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
        //return color(0,0,0);
    }
};

#endif