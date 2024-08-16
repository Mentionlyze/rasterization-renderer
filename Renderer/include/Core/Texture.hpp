#pragma once

#include "Base.hpp"
#include "Core/Math.hpp"
#include "Math.hpp"
#include <unordered_map>

namespace Rasterization {
class Texture {
public:
    Texture(const std::string& path, const uint32_t id);

    ~Texture();

    int32_t GetWidth() const { return m_Width; }

    int32_t GetHeight() const { return m_height; }

    Color GetColor(const uint32_t x, const uint32_t y) const {
        auto location = (y * m_Width + x) * m_Channels;
        auto r = UChar2Float(m_Buffer[location + 0]);
        auto g = UChar2Float(m_Buffer[location + 1]);
        auto b = UChar2Float(m_Buffer[location + 2]);
        auto a = m_Channels == 3 ? UChar2Float(m_Buffer[location + 3]) : 1.0f;

        return Color{r, g, b, a};
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
        if (s_TextureStorageInstance != nullptr) {
            delete s_TextureStorageInstance;
        }
    };

    static uint32_t CreateTexture(const std::string& path);
    static Ref<Texture> GetTexture(const uint32_t id);

private:
    uint32_t m_CurId;
    std::unordered_map<uint32_t, Ref<Texture>> m_Images;

    static TextureStorage* s_TextureStorageInstance;
};
}  // namespace Rasterization