#include "Storage.h"

void Storage::SetRoot(const std::string& root)
{
    m_root = root;
}

void Storage::AddTexture(const std::string& name, const std::string& path)
{
    m_textures[name].loadFromFile(m_root + "/" + path);
}

void Storage::AddFont(const std::string& name, const std::string& path)
{
    m_fonts[name].loadFromFile(m_root + "/" + path);
}

void Storage::AddSoundBuffer(const std::string& name, const std::string& path)
{
    m_soundBuffers[name].loadFromFile(m_root + "/" + path);
}

void Storage::AddMusic(const std::string& name, const std::string& path)
{
    m_music[name].openFromFile(m_root + "/" + path);
}

sf::Texture* Storage::GetTexture(const std::string& name)
{
    return &m_textures[name];
}

sf::Font* Storage::GetFont(const std::string& name)
{
    return &m_fonts[name];
}

sf::SoundBuffer* Storage::GetSoundBuffer(const std::string& name)
{
    return &m_soundBuffers[name];
}

sf::Music* Storage::GetMusic(const std::string& name)
{
    return &m_music[name];
}

Storage::Storage() = default;
