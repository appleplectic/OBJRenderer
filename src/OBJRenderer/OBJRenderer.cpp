#include "OBJRenderer.h"

#include <stdexcept>
#include <cmath>


void OBJRenderer::draw_line(Vec2D start, Vec2D end, const Color &color) {
    if (start == end) {
        throw std::invalid_argument("Cannot draw line between points " + start.get_str() + " and " + end.get_str());
    }

    if (start.x > end.x) {
        std::swap(start, end);
    }

    const double slope = static_cast<double>(end.y - start.y) / (end.x - start.x);

    for (unsigned int i=0; i<=end.x-start.x; i++) {
        set_pixel(Vec2D{i + start.x, static_cast<unsigned int>(std::round(start.y + i * slope))}, color);
    }
}
