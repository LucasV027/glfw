#pragma once

#include <filesystem>
#include <vector>

namespace GL {
    enum LoaderFlags {
        V, VT, VN, VP
    };

    class Loader {
    public:
        Loader() = default;

        void Load(const std::filesystem::path &filepath);

        ~Loader() = default;

    private:
        void ParseLine(const std::string &line);

    private:
        // List of geometric vertices, with (x, y, z, [w]) coordinates,
        // w is optional and defaults to 1.0.
        std::vector<float> v;

        // List of texture coordinates, in (u, [v, w]) coordinates,
        // these will vary between 0 and 1. v, w are optional and default to 0.
        std::vector<float> vt;

        // List of vertex normals in (x,y,z) form;
        // normals might not be unit vectors.
        std::vector<float> vn;

        // Parameter space vertices in (u, [v, w]) form;
        // free form geometry statement (see below)
        std::vector<float> vp;
    };
}
