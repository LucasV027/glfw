#include "Loader.h"

#include <fstream>
#include <iostream>

namespace GL {
    void Loader::Load(const std::filesystem::path &filepath) {
        std::ifstream file(filepath);
        std::string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                ParseLine(line);
            }
            file.close();
        }
    }

    void Loader::ParseLine(const std::string &line) {
        if (line.size() <= 2) return;

        char first = line[0];
        char second = line[1];

        switch (first) {
            case 'v': {
                switch (second) {
                    case ' ':
                        // TODO geometric vertices
                        break;
                    case 't':
                        // TODO texture coordinates
                        break;
                    case 'n':
                        // TODO vertex normals
                        break;
                    case 'p':
                        // TODO Parameter space vertices
                        break;
                    default:
                        break;
                }
            case 'f':
                // TODO Polygonal face element
                break;
            case 'l':
                //TODO Line element
                break;
            default:
                break;
            }
        }
    }
}
