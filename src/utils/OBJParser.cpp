#include "OBJParser.h"

#include <fstream>
#include <iostream>

namespace GL {
    std::ostream &operator<<(std::ostream &os, const Mesh &mesh) {
        os << "Sizes:\n";
        os << mesh.vertices.size() << " vertices\n";
        os << mesh.indices.size() << " indices\n\n";
        os << "Vertices:\n";
        for (size_t i = 0; i < mesh.vertices.size(); i += 3) {
            os << "  (" << mesh.vertices[i] << ", " << mesh.vertices[i + 1] << ", " << mesh.vertices[i + 2] << ")\n";
        }

        os << "\nIndices:\n";
        for (size_t i = 0; i < mesh.indices.size(); i += 3) {
            os << "  (" << mesh.indices[i] << ", " << mesh.indices[i + 1] << ", " << mesh.indices[i + 2] << ")\n";
        }
        os << std::endl;
        return os;
    }

    Mesh OBJParser::Parse(const std::filesystem::path &filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Error : Could not open " + filepath.string());
        }

        if (filepath.extension() != ".obj") {
            throw std::runtime_error("Error : File is not a .obj file");
        }

        Mesh result;
        std::string line;
        while (std::getline(file, line)) {
            ParseLine(line, &result);
        }

        file.close();
        return result;
    }

    void OBJParser::ParseLine(const std::string &line, Mesh *result) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            ParseVertex(iss, result);
        } else if (prefix == "f") {
            ParseFace(iss, result);
        }
    }

    void OBJParser::ParseVertex(std::istringstream &iss, Mesh *result) {
        float x, y, z;
        iss >> x >> y >> z;
        result->vertices.push_back(x);
        result->vertices.push_back(y);
        result->vertices.push_back(z);
    }

    void OBJParser::ParseFace(std::istringstream &iss, Mesh *result) {
        std::string value;
        while (iss >> value) {
            std::istringstream valueStream(value);
            std::string indexStr;
            int vertexIndex = -1;

            if (std::getline(valueStream, indexStr, '/') && !indexStr.empty()) {
                vertexIndex = std::stoi(indexStr) - 1; // Adjust to 0-based index
            }

            result->indices.push_back(vertexIndex);
        }
    }
}
