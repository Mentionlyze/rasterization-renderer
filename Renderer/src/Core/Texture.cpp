#include "Core/Texture.hpp"
#include "stb_image.h"

namespace Rasterization {
TextureStorage *TextureStorage::s_TextureStorageInstances = new TextureStorage();

Texture::Texture(const std::string &path, const uint32_t id) {
    stbi_set_flip_vertically_on_load(1);
    auto data = stbi_load(path.c_str(), &m_Width, &m_height, &m_Channels, 0);
    ASSERT(data);

    m_Buffer = (unsigned char *)(data);
    stbi_image_free(data);
}

TextureStorage::TextureStorage() : m_CurId{0} {}

uint32_t TextureStorage::CreateTexture(const std::string &path) {
    auto id = s_TextureStorageInstances->m_CurId;
    s_TextureStorageInstances->m_CurId++;

    s_TextureStorageInstances->m_Images[id] = CreateRef<Texture>(path, id);
    return id;
}

Ref<Texture> TextureStorage::GetTexture(const uint32_t id) {
    auto texture = s_TextureStorageInstances->m_Images[id];
    ASSERT(texture);
    return texture;
}
}  // namespace Rasterization