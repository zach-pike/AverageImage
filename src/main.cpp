#include <png++/png.hpp>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <cmath>

#include "resize.hpp"

namespace fs = std::filesystem;

const int outputWidth = 2560;
const int outputHeight = 1440;
const char* outputFileName = "final.png";

int main(void) {
    std::vector<std::string> filenames;

    for (const auto& path : fs::directory_iterator("imgs/")) {
        filenames.push_back(fs::absolute(path.path()));
    }

    std::vector<png::basic_rgb_pixel<std::uint64_t>> pixels;
    pixels.resize(outputWidth*outputHeight);

    int index = 0;

    for (const auto& filepath : filenames) {
        png::image<png::rgb_pixel> img(filepath);
        scalar_resize(img, outputWidth, outputHeight);

        for (int y=0; y<outputHeight; y++) {
            for (int x=0; x<outputWidth; x++) {
                int array_index = y * outputWidth + x;

                auto& pixel = pixels.at(array_index);
                auto img_pixel = img.get_pixel(x, y);

                pixel.red += img_pixel.red;
                pixel.green += img_pixel.green;
                pixel.blue += img_pixel.blue;
            }
        }

        std::cout << index << std::endl;
        index ++;
    }

    // Create the new image
    png::image<png::rgb_pixel> image(outputWidth, outputHeight);

    float number_of_images = filenames.size();

    for (int y=0; y<outputHeight; y++) {
            for (int x=0; x<outputWidth; x++) {
            int index = y * outputWidth + x;
            auto pixel = pixels[index];
            
            int new_red = (float)pixel.red / number_of_images;
            int new_green = (float)pixel.green / number_of_images;
            int new_blue = (float)pixel.blue / number_of_images;

            auto new_pixel = png::rgb_pixel(new_red, new_green, new_blue);

            image.set_pixel(x, y, new_pixel);
        }
    }

    image.write(outputFileName);
}