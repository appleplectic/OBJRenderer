#pragma once

#include "SImg/SImg.h"


class OBJRenderer : public SImg {
public:
    OBJRenderer(
        const Vec2D &dimensions,
        const Color &color,
        const ImgOrientation orientation = TOP_LEFT)
    : SImg(dimensions, color, orientation) {}

    void draw_line(Vec2D start, Vec2D end, const Color &color);
};