#include "ArgvParser.h"

#include <iostream>
#include <fstream>
#include <optional>


void print_help() {
    std::cout <<
R"(Usage: objrenderer(.exe) [options] <input_file>

This application processes an OBJ file and outputs a rendered PPM image.

Arguments:
  input_file                   The file path of the input image. This argument is required.

Options:
  --help                       Show this help message and exit.
  --openfile, -of              Open the outputted file automatically in the default application after processing.
  --output, -o <outfile>       Specify the output file path. Default is "out.ppm".
  --width, -w <width>          Specify the width of the output image in pixels. This option is required.
  --height, -h <height>        Specify the height of the output image in pixels. This option is required.

Examples:
    objrenderer -w 800 -h 600 path/to/input.obj
    objrenderer --width 1024 --height 768 --output path/to/output.ppm --openfile path/to/input.obj

  Note: Ensure that the input file path is accessible and the specified dimensions are valid for image processing.
)";
}


/// Parse argc and argv[] and return an OBJRendererSettings object if okay, or {} if the args were invalid
std::optional<OBJRendererSettings> parse_args(const int argc, const char* argv[]) {
    OBJRendererSettings settings;
    for (int i=1; i<argc; i++) {
        std::string option = argv[i];
        if (auto j = NoArgs.find(option); j != NoArgs.end()) {
            j->second(settings);
        } else if (auto k = OneArgs.find(option); k != OneArgs.end()) {
            if (++i < argc) {
                k->second(settings, {argv[i]});
            } else {
                std::cerr << "Missing parameter after " + option << "\n";
                print_help();
                return {};
            }
        } else {
            if (std::ifstream test_file(option); !test_file.is_open()) {
                std::cerr << "Unrecognized command-line option or invalid input file " << option << " passed.\n";
                print_help();
                return {};
            }
            settings.infile = option;
        }
    }

    if (settings.help) {
        print_help();
        return {};
    }

    if (settings.height <= 0 || settings.width <= 0) {
        std::cerr << "Provide a valid width and height for the output image.\n";
        print_help();
        return {};
    }

    return settings;
}
