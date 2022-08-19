#include <png++/png.hpp>
#include <cstdint>
#include <cmath>

template <typename T>
void scalar_resize(png::image<T>& img, std::size_t newWidth, std::size_t newHeight) {
    png::image<T> newImg(newWidth, newHeight);

    for (int y=0; y<newHeight; y++) {
        for (int x=0; x<newWidth; x++) {

            double scaledX = (double)x / (double)newWidth;
            double scaledY = (double)y / (double)newHeight;

            std::size_t newX = std::floor(scaledX * (float)img.get_width());
            std::size_t newY = std::floor(scaledY * (float)img.get_height());

            newImg.set_pixel(x, y, img.get_pixel(newX, newY));
        }        
    }

    img = newImg;
}