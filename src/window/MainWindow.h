#pragma once

#include "Storage.h"

class MainWindow
{
public:
    MainWindow();

    void Start();

private:
    void SetStorageDataFiles();

    void Update();
    void DrawCells();
    void DrawPieces();
    void DrawSelectedPieceMoves();
    void UpdateWindowTitle();

    sf::Vector2f GetCellSize();
    sf::Vector2f GetCellPosition(int32_t x, int32_t y);
    uint8_t GetStatus();
    std::string GetTextureName(int32_t x, int32_t y) const;

private:
    sf::RenderWindow m_window;
    sf::Event m_event{};

    sf::Vector2i m_buff;

    static constexpr int32_t BOARD_MARGIN = 20;
    enum Status
    {
        WHITE_TO_MOVE,
        BLACK_TO_MOVE,
        WHITE_WON,
        BLACK_WON,
        DRAW,
    };
};