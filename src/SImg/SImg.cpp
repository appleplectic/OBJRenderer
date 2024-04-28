#include "SImg.h"

#include <ranges>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <cstdint>
#include <sstream>
#include <vector>
#include <fstream>


Color::Color(std::string hex) {
    if (hex.size() == 7) {
        hex.erase(hex.begin());
    } else if (hex.size() != 6) {
        throw std::invalid_argument("An invalid hex color code was provided " + hex);
    }
    if (!std::ranges::all_of(hex.begin(), hex.end(), [](const char c) {
        return std::isxdigit(static_cast<uint8_t>(c));
    })) {
        throw std::invalid_argument("An invalid hex color code was provided " + hex);
    }

    int i_hex;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> i_hex;

    r = ((i_hex >> 16) & 0xFF) / 255;
    g = ((i_hex >> 8) & 0xFF) / 255;
    b = ((i_hex) & 0xFF) / 255;
}

std::string Color::get_str() const {
    return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);
}

bool Color::operator==(const Color &other) const noexcept {
    return r == other.r && g == other.g && b == other.b;
}

bool Color::operator!=(const Color &other) const noexcept {
    return !operator==(other);
}


std::string Vec2D::get_str() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}


bool Vec2D::operator==(const Vec2D &other) const noexcept {
    return x == other.x && y == other.y;
}

bool Vec2D::operator!=(const Vec2D &other) const noexcept {
    return !operator==(other);
}


SImg::SImg(const Vec2D &dimensions, const Color &color, const ImgOrientation orientation) {
    if (dimensions.x == 0 || dimensions.y == 0) {
        throw std::invalid_argument("Invalid dimensions " + dimensions.get_str() + " cannot be an image.");
    }

    img_orientation_ = orientation;
    width_ = dimensions.x;
    height_ = dimensions.y;

    header_lines_.emplace_back("P3");
    header_lines_.emplace_back(std::to_string(width_) + " " + std::to_string(height_));
    header_lines_.emplace_back("255");

    for (int i=0; i<width_; i++) {
        for (int j=0; j<height_; j++) {
            img_lines_.push_back(color.get_str());
        }
    }
}

void SImg::set_pixel(const Vec2D &pos, const Color &color) {
    if (pos.x >= width_ || pos.y >= height_) {
        throw std::invalid_argument("Position " + pos.get_str() + " cannot be set.");
    }

    const int index = pos.y*width_ + pos.x;
    img_lines_.at(index) = color.get_str();
}

void SImg::save(const std::string &filename) const {
    std::ofstream open_file(filename);
    if (!open_file.is_open()) {
        throw std::runtime_error("Unable to open file " + filename);
    }
    for (const auto& str : header_lines_) {
        open_file << str << '\n';
    }

    switch (img_orientation_) {
        case TOP_LEFT:
            for (const auto& str : img_lines_) {
                open_file << str << '\n';
            }
            break;
        case TOP_RIGHT:
            for (int i = 0; i < height_; i++) {
                for (int j = width_ - 1; j >= 0; j--) {
                    open_file << img_lines_[i * width_ + j] << '\n';
                }
            }
            break;
        case BOTTOM_LEFT:
            for (int i = height_ - 1; i >= 0; i--) {
                for (int j = 0; j < width_; j++) {
                    open_file << img_lines_.at(i * width_ + j) << '\n';
                }
            }
            break;
        case BOTTOM_RIGHT:
            for (int i = height_ - 1; i >= 0; i--) {
                for (int j = width_ - 1; j >= 0; j--) {
                    open_file << img_lines_.at(i * width_ + j) << '\n';
                }
            }
            break;
    }
    open_file.close();
}

void SImg::open_file(const std::string &filename) {
#if defined(_WIN32)
    std::string command = "explorer.exe \"" + filename + "\"";
#elif defined(__APPLE__)
    std::string command = "open \"" + filename + "\"";
#elif defined(__linux__)
    std::string command = "xdg-open \"" + filename + "\"";
#else
#error "Platform not supported"
#endif
    if (system(command.c_str()) != 0) {
        throw std::runtime_error("Unable to open file " + filename);
    }
}
