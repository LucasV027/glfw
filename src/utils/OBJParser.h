#pragma once

#include <filesystem>
#include <vector>

namespace GL {
    struct Mesh {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh) ;
    };

    class OBJParser {
    public:
        OBJParser() = delete;

        static Mesh Parse(const std::filesystem::path &filepath);

    private:
        static void ParseLine(const std::string &line, Mesh *result);

        static void ParseVertex(std::istringstream &iss, Mesh *result);

        static void ParseFace(std::istringstream &iss, Mesh *result);
    };
}
