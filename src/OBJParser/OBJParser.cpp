#include "OBJParser.h"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>


std::vector<std::string> split(const std::string& s, const char delim) {
    std::vector<std::string> r;
    std::stringstream ss(s);
    std::string m;

    while (getline(ss, m, delim)) {
        if (!m.empty())
            r.push_back(m);
    }
    return r;
}


std::string Vec3D::get_str() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}


bool Vec3D::operator==(const Vec3D &other) const noexcept {
    return x == other.x && y == other.y && z == other.z;
}

bool Vec3D::operator!=(const Vec3D &other) const noexcept {
    return !operator==(other);
}

void Vec3D::normalize(const double min, const double max) {
    x = 2 * ((x - min) / (max - min)) - 1;
    y = 2 * ((y - min) / (max - min)) - 1;
    z = 2 * ((z - min) / (max - min)) - 1;
}


OBJParser::OBJParser(const std::string &filename) {
    std::ifstream ifs(filename);
    std::string line;

    while (std::getline(ifs, line)) {
        if (line.starts_with("v ")) {
            auto splitted = split(line);
            vertices.push_back(Vec3D {
                std::stod(splitted.at(1)),
                std::stod(splitted.at(2)),
                std::stod(splitted.at(3))
            });
        } else if (line.starts_with("f ")) {
            std::vector<int> face;
            for (const auto& s_face : split(line)) {
                if (s_face == "f")
                    continue;
                face.push_back(std::stoi(split(s_face, '/').at(0)));
            }
            faces.push_back(face);
        }
    }

    double min = std::numeric_limits<double>::infinity();
    double max = -min;

    for (const auto& [x, y, z] : vertices) {
        if (x < min) min = x;
        if (x > max) max = x;
        if (y < min) min = y;
        if (y > max) max = y;
        if (z < min) min = z;
        if (z > max) max = z;
    }

    for (auto& vertex : vertices) {
        vertex.normalize(min, max);
    }
}
