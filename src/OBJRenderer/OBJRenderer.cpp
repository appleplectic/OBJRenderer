#include "OBJRenderer.h"

#include <stdexcept>
#include <cmath>


void OBJRenderer::draw_line(Vec2D start, Vec2D end, const Color &color) {
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


void OBJRenderer::draw_triangle(Vec2D v0, Vec2D v1, Vec2D v2, const Color &color, const bool wireframe) {
    if (wireframe) {
        draw_line(v0, v1, color);
        draw_line(v1, v2, color);
        draw_line(v2, v0, color);
    } else {
        if (v1.y < v0.y) std::swap(v0, v1);
        if (v2.y < v1.y) std::swap(v1, v2);
        if (v1.y < v0.y) std::swap(v0, v1);

        auto draw_scanline = [&](const int y, int x1, int x2) {
            if (x2 < x1) std::swap(x1, x2);
            for (int x = x1; x <= x2; x++) {
                set_pixel(Vec2D{x, y}, color);
            }
        };

        auto interpolate = [](const Vec2D v_start, const Vec2D v_end, const int y) {
            if (v_start.y == v_end.y) return v_start.x;
            return v_start.x + (v_end.x - v_start.x) * (y - v_start.y) / (v_end.y - v_start.y);
        };

        int y;
        for (y = v0.y; y <= v1.y; y++) {
            const int x1 = interpolate(v0, v2, y);
            const int x2 = interpolate(v0, v1, y);
            draw_scanline(y, x1, x2);
        }

        for (; y <= v2.y; y++) {
            const int x1 = interpolate(v0, v2, y);
            const int x2 = interpolate(v1, v2, y);
            draw_scanline(y, x1, x2);
        }
    }
}
