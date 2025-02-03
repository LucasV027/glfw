#include "Loader.h"

#include <fstream>
#include <iostream>

namespace GL {
    void Loader::Load(const std::filesystem::path &filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Error : Could not open " + filepath.string());
        }

        std::string line;
        while (std::getline(file, line)) {
            ParseLine(line);
        }

        file.close();
    }

    void Loader::PrintData() const {
        std::cout << "Sizes:" << std::endl;
        std::cout << vertices.size() << " vertices" << std::endl;
        std::cout << indices.size() << " indices" << std::endl;
        std::cout << std::endl;
        std::cout << "Vertices:" << std::endl;
        for (size_t i = 0; i < vertices.size(); i += 3) {
            std::cout << "  (" << vertices[i] << ", " << vertices[i + 1] << ", " << vertices[i + 2] << ")" << std::endl;
        }

        std::cout << "\nIndices:" << std::endl;
        for (size_t i = 0; i < indices.size(); i += 3) {
            std::cout << "  (" << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << ")" << std::endl;
        }
    }

    float *Loader::Vertices() { return vertices.data(); }
    size_t Loader::VerticesCount() const { return vertices.size(); }
    unsigned int *Loader::Indices() { return indices.data(); }
    size_t Loader::IndicesCount() const { return indices.size(); }

    void Loader::ParseLine(const std::string &line) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            ParseVertex(iss);
        } else if (prefix == "f") {
            ParseFace(iss);
        }
    }

    void Loader::ParseVertex(std::istringstream &iss) {
        float x, y, z;
        iss >> x >> y >> z;
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        dim = 3; // Assumes 3D vertices
    }

    void Loader::ParseFace(std::istringstream &iss) {
        std::string value;
        while (iss >> value) {
            std::istringstream valueStream(value);
            std::string indexStr;
            int vertexIndex = -1;

            if (std::getline(valueStream, indexStr, '/') && !indexStr.empty()) {
                vertexIndex = std::stoi(indexStr) - 1; // Adjust to 0-based index
            }

            indices.push_back(vertexIndex);
        }
    }
}
