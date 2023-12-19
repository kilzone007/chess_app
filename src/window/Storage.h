#pragma once

#include "Singleton.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <unordered_map>

class Storage : public Singleton<Storage>
{
    MAKE_SINGLETON(Storage);

public:
    Storage(const Storage& other) = delete;

    void SetRoot(const std::string& root);

    void AddTexture(const std::string& name, const std::string& path);
    void AddFont(const std::string& name, const std::string& path);
    void AddSoundBuffer(const std::string& name, const std::string& path);
    void AddMusic(const std::string& name, const std::string& path);

    sf::Texture* GetTexture(const std::string& name);
    sf::Font* GetFont(const std::string& name);
    sf::SoundBuffer* GetSoundBuffer(const std::string& name);
    sf::Music* GetMusic(const std::string& name);

private:
    Storage();

    std::string m_root;
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
    std::unordered_map<std::string, sf::Music> m_music;
};