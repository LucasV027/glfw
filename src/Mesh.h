#pragma once

#include <filesystem>
#include <iostream>
#include <vector>

namespace lgl {
    class Mesh {
    public:
        explicit Mesh(const std::filesystem::path &filepath) {
            if (filepath.extension() != ".obj") {
                throw std::runtime_error(
                    "Error: creating mesh from " + filepath.string() + ", extension must be .obj");
            }

            if (!exists(filepath)) {
                throw std::runtime_error(
                    "Error: creating mesh from " + filepath.string() + ", file does not exist");
            }

            std::ifstream file(filepath, std::ios::binary);
            std::string line;

            while (std::getline(file, line)) {
                if (line.empty()) continue;

                std::istringstream iss(line);
                std::string word;
                iss >> word;

                if (word == "v") {
                    // Vertex data
                    float x;
                    for (int i = 0; i < 3; ++i) {
                        iss >> x;
                        vertices.emplace_back(x);
                    }
                } else if (word == "f") {
                    // Face data
                    unsigned int x;
                    for (int i = 0; i < 3; ++i) {
                        iss >> x;
                        indices.emplace_back(x - 1);
                    }
                }
            }
        }

        void display() const {
            std::cout << "Vertices : " << vertices.size() << std::endl;

            for (size_t i = 0; i < vertices.size(); i += 3) {
                std::cout << "v " << vertices[i] << ", " << vertices[i + 1] << ", " << vertices[i + 2] << std::endl;
            }

            std::cout << "Indices : " << indices.size() << std::endl;
            for (size_t i = 0; i < indices.size(); i += 3) {
                std::cout << "f " << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << std::endl;
            }

            std::cout << std::endl;
        }

        [[nodiscard]] size_t verticesBiteSize() const { return vertices.size() * sizeof(float); }
        [[nodiscard]] size_t indicesBiteSize() const { return indices.size() * sizeof(unsigned int); }

    public:
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };
}
