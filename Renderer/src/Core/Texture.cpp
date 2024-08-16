#include "Core/Texture.hpp"
#include "stb_image.h"

namespace Rasterization {
TextureStorage *TextureStorage::s_TextureStorageInstance = new TextureStorage();

Texture::Texture(const std::string &path, const uint32_t id) {
    stbi_set_flip_vertically_on_load(1);
    m_Buffer = stbi_load(path.c_str(), &m_Width, &m_height, &m_Channels, 0);
    ASSERT(m_Buffer);
}

Texture::~Texture() {
    stbi_image_free(m_Buffer);
}

TextureStorage::TextureStorage() : m_CurId{1} {}

uint32_t TextureStorage::CreateTexture(const std::string &path) {
    auto id = s_TextureStorageInstance->m_CurId;
    s_TextureStorageInstance->m_CurId++;

    s_TextureStorageInstance->m_Images[id] = CreateRef<Texture>(path, id);
    return id;
}

Ref<Texture> TextureStorage::GetTexture(const uint32_t id) {
    auto texture = s_TextureStorageInstance->m_Images[id];
    ASSERT(texture);
    return texture;
}
}  // namespace Rasterization