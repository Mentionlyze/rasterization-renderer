#pragma once

#include "Base.hpp"
#include "Core/Math.hpp"
#include "Math.hpp"
#include <unordered_map>

namespace Rasterization {
class Texture {
public:
    Texture(const std::string& path, const uint32_t id);

    ~Texture() = default;

    Color GetColor(const uint32_t x, const uint32_t y) const {
        auto r = m_Buffer[y * m_Width * m_Channels + x * m_Channels + 0];
        auto g = m_Buffer[y * m_Width * m_Channels + x * m_Channels + 1];
        auto b = m_Buffer[y * m_Width * m_Channels + x * m_Channels + 2];
        auto a = m_Channels == 4
                     ? m_Buffer[y * m_Width * m_Channels + x * m_Channels + 3]
                     : (unsigned char)(255);

        return Color{UChar2Float(r), UChar2Float(g), UChar2Float(b),
                     UChar2Float(a)};
    }

private:
    uint32_t m_TextureId;
    int32_t m_Width, m_height, m_Channels;
    unsigned char* m_Buffer;
};

class TextureStorage {
public:
    TextureStorage();

    ~TextureStorage() {
        if (s_TextureStorageInstances != nullptr) {
            delete s_TextureStorageInstances;
        }
    };

    static uint32_t CreateTexture(const std::string& path);
    static Ref<Texture> GetTexture(const uint32_t id);

private:
    uint32_t m_CurId;
    std::unordered_map<uint32_t, Ref<Texture>> m_Images;

    static TextureStorage* s_TextureStorageInstances;
};
}  // namespace Rasterization