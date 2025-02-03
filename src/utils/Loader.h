#pragma once

#include <filesystem>
#include <vector>
#include <iostream>

namespace GL {
    enum LoaderFlags {
        V, VT, VN, VP
    };

    class Loader {
    public:
        Loader() = default;

        ~Loader() = default;

        void Load(const std::filesystem::path &filepath);

        void PrintData() const;

        float *Vertices();

        size_t VerticesCount() const;

        unsigned int *Indices();

        size_t IndicesCount() const;

    private:
        void ParseLine(const std::string &line);

        void ParseVertex(std::istringstream &iss);

        void ParseFace(std::istringstream &iss);

    private:
        unsigned int dim = 0;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };
}
