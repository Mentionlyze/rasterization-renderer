#pragma once

#include "Base.hpp"
#include "stb_image.h"
#include <cstdint>
#include <filesystem>
#include <string>
#include <unordered_map>

namespace Rasterization {
class Texture {
public:
    Texture(const std::filesystem::path path, const uint32_t id) {
        stbi_set_flip_vertically_on_load(1);
        int width, height, nrComponents;
        // unsigned char *data =
        //     stbi_load((path).string().c_str(), &width, &height,
        //     &nrComponents, 0);
        // if (data == nullptr) {
        //   ASSERT(data);
        // }
        // auto a = sizeof(data);

        m_TextureId = id;
        // stbi_image_free(data);
    };

    ~Texture() = default;

private:
    uint32_t m_TextureId;
};

class TextureStorage {
public:
    TextureStorage() { m_CurId = 0; };

    ~TextureStorage() = default;

    uint32_t CreateTexture(const std::string &path) {
        auto id = m_CurId;
        m_CurId++;
        auto t = CreateRef<Texture>(path, id);

        return id;
    }

private:
    uint32_t m_CurId;
    std::unordered_map<uint32_t, Ref<Texture>> m_Images;
};
}  // namespace Rasterization