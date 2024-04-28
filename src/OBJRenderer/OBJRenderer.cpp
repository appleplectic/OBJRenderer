#include "OBJRenderer.h"

#include <stdexcept>
#include <cmath>


void OBJRenderer::draw_line(Vec2D start, Vec2D end, const Color &color) {
    if (start == end) {
        // throw std::invalid_argument("Cannot draw line between points " + start.get_str() + " and " + end.get_str());
        return;
    }

    const bool steep = std::abs(end.y - start.y) > std::abs(end.x - start.x);
    if (steep) {
        std::swap(start.x, start.y);
        std::swap(end.x, end.y);
    }

    if (start.x > end.x) {
        std::swap(start, end);
    }

    const int dx = end.x - start.x;
    const int dy = std::abs(end.y - start.y);
    int error = dx / 2;
    const int ystep = (start.y < end.y) ? 1 : -1;
    int y = start.y;

    for (int x=start.x; x<=end.x; x++) {
        if (steep) {
            set_pixel(Vec2D{y, x}, color);
        } else {
            set_pixel(Vec2D{x, y}, color);
        }
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}
