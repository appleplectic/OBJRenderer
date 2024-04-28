#pragma once

#include <functional>
#include <string>
#include <unordered_map>


struct OBJRendererSettings {
    bool help = false;
    bool openfile = false;

    std::string infile;
    std::string outfile = "out.ppm";

    int width = 0;
    int height = 0;

    void validate_settings() const;
};


typedef std::function<void(OBJRendererSettings&)> NoArgHandle;

#define S(str, f, v) {str, [](OBJRendererSettings &s) { s.f = v; }}
const std::unordered_map<std::string, NoArgHandle> NoArgs {
    S("--help", help, true),

    S("--openfile", openfile, true),
    S("-of", openfile, true),
};
#undef S


typedef std::function<void(OBJRendererSettings&, const std::string&)> OneArgHandle;

#define S(str, f, v) {str, [](OBJRendererSettings &s, const std::string& arg) { s.f = v; }}
const std::unordered_map<std::string, OneArgHandle> OneArgs {
    S("--output", outfile, arg),
    S("-o", outfile, arg),

    S("--width", width, std::stoi(arg)),
    S("-w", width, std::stoi(arg)),

    S("--height", height, std::stoi(arg)),
    S("-h", height, std::stoi(arg)),
};
#undef S

OBJRendererSettings parse_args(int argc, const char* argv[]);
