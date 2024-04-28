#pragma once

#include <string>
#include <vector>


struct Vec3D {
    double x;
    double y;
    double z;

    [[nodiscard]] std::string get_str() const;

    bool operator==(const Vec3D &other) const noexcept;
    bool operator!=(const Vec3D &other) const noexcept;
};


class OBJParser {
private:
    std::vector<Vec3D> vertices;
    std::vector<std::vector<int>> faces;
public:
    explicit OBJParser(const std::string &filename);

    [[nodiscard]] std::vector<Vec3D> get_vertices() const { return vertices; }
    [[nodiscard]] std::vector<std::vector<int>> get_faces() const { return faces; }
};