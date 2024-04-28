#pragma once

#include <string>
#include <vector>
#include <cstdint>


struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color(const uint8_t r, const uint8_t g, const uint8_t b) : r(r), g(g), b(b) {}
    explicit Color(std::string hex);

    [[nodiscard]] std::string get_str() const;

    bool operator==(const Color &other) const noexcept;
    bool operator!=(const Color &other) const noexcept;
};


struct Vec2D {
    int x;
    int y;

    [[nodiscard]] std::string get_str() const;

    bool operator==(const Vec2D &other) const noexcept;
    bool operator!=(const Vec2D &other) const noexcept;
};


class SImg {
public:
    enum ImgOrientation {
        BOTTOM_RIGHT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        TOP_LEFT
    };

    SImg(const Vec2D &dimensions, const Color &color, ImgOrientation orientation = TOP_LEFT);

    void set_pixel(const Vec2D &pos, const Color& color);
    void save(const std::string &filename) const;

    [[nodiscard]] int get_width() const { return width_; }
    [[nodiscard]] int get_height() const { return height_; }

    static void open_file(const std::string &filename);

private:
    int width_;
    int height_;
    ImgOrientation img_orientation_;

    std::vector<std::string> header_lines_;
    std::vector<std::string> img_lines_;
};