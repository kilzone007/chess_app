#include "MainWindow.h"

MainWindow::MainWindow()
{
    SetStorageDataFiles();

    m_window.create(sf::VideoMode(600, 600), "", sf::Style::Default);
    m_window.setFramerateLimit(20);

    m_buff = sf::Vector2i(INT32_MAX, INT32_MAX);
}

void MainWindow::Start()
{
    sf::Sound sound;
    while (true)
    {
        while (m_window.pollEvent(m_event))
        {
            if (m_event.type == sf::Event::Closed)
            {
                return;
            }

            if (m_event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, m_window.getSize().x, m_window.getSize().y);
                m_window.setView(sf::View(visibleArea));
            }
            else if (m_event.type == sf::Event::MouseButtonPressed && GetStatus() == Status::WHITE_TO_MOVE)
            {
                sf::Vector2i mouse = sf::Mouse::getPosition(m_window);
                sf::Vector2i cell(INT32_MAX, INT32_MAX);
                for (int32_t x = 0; x < 8; ++x)
                {
                    for (int32_t y = 0; y < 8; ++y)
                    {
                        const auto cellPosition = GetCellPosition(x, y);
                        const auto cellSize = GetCellSize();
                        if (mouse.x > cellPosition.x && mouse.y > cellPosition.y &&
                            mouse.x < cellPosition.x + cellSize.x && mouse.y < cellPosition.y + cellSize.y)
                        {
                            cell = sf::Vector2i(x, y);
                        }
                    }
                }

                if (cell != sf::Vector2i(INT32_MAX, INT32_MAX))
                {
                    uint8_t promotionFlag{};
                    const auto cellPosition = GetCellPosition(cell.x, cell.y);
                    const auto cellSize = GetCellSize();
                    if (mouse.x - cellPosition.x < cellSize.x / 2)
                    {
                        if (mouse.y - cellPosition.y < cellSize.y / 2)
                        {
                            // promotionFlag = Move::Flag::PROMOTE_TO_KING;
                        }
                        else
                        {
                            // promotionFlag = Move::Flag::PROMOTE_TO_BISHOP;
                        }
                    }
                    else
                    {
                        if (mouse.y - cellPosition.y < cellSize.y / 2)
                        {
                            // promotionFlag = Move::Flag::PROMOTE_TO_ROOK;
                        }
                        else
                        {
                            // promotionFlag = Move::Flag::PROMOTE_TO_QUEEN;
                        }
                    }

                    if (cell == m_buff)
                    {
                        m_buff = sf::Vector2i(INT32_MAX, INT32_MAX);
                        sound.setBuffer(*Storage::instance()->GetSoundBuffer("move"));
                        sound.play();
                    }
                    // else if (BOp::getBit(m_position.getPieces().getSideBitboard(SIDE::WHITE), cell.y * 8 + cell.x))
                    // {
                    //     buff = cell;
                    //     sound.setBuffer(*Storage::instance()->GetSoundBuffer("move"));
                    //     sound.play();
                    // }
                    else
                    {
                        /// \todo: Generate move
                    }
                }
            }
        }

        Update();
    }
}

void MainWindow::SetStorageDataFiles()
{
    /// \todo: Create root from cmake config file
    /// \todo: Create named constants to names
    Storage::instance()->SetRoot("../data");
    Storage::instance()->AddTexture("logotype", "images/logotype.png");
    Storage::instance()->AddTexture("whitePawn", "images/chessmen/white/pawn.png");
    Storage::instance()->AddTexture("whiteKnight", "images/chessmen/white/knight.png");
    Storage::instance()->AddTexture("whiteBishop", "images/chessmen/white/bishop.png");
    Storage::instance()->AddTexture("whiteRook", "images/chessmen/white/rook.png");
    Storage::instance()->AddTexture("whiteQueen", "images/chessmen/white/queen.png");
    Storage::instance()->AddTexture("whiteKing", "images/chessmen/white/king.png");
    Storage::instance()->AddTexture("blackPawn", "images/chessmen/black/pawn.png");
    Storage::instance()->AddTexture("blackKnight", "images/chessmen/black/knight.png");
    Storage::instance()->AddTexture("blackBishop", "images/chessmen/black/bishop.png");
    Storage::instance()->AddTexture("blackRook", "images/chessmen/black/rook.png");
    Storage::instance()->AddTexture("blackQueen", "images/chessmen/black/queen.png");
    Storage::instance()->AddTexture("blackKing", "images/chessmen/black/king.png");
    Storage::instance()->AddSoundBuffer("move", "sounds/move.ogg");
    Storage::instance()->AddSoundBuffer("capture", "sounds/capture.ogg");
    Storage::instance()->AddSoundBuffer("message", "sounds/message.ogg");
}

void MainWindow::Update()
{
    /// \todo: Make changable color
    m_window.clear(sf::Color(22, 21, 18));
    DrawCells();
    DrawPieces();
    DrawSelectedPieceMoves();
    UpdateWindowTitle();
    m_window.display();
}

void MainWindow::DrawCells()
{
    for (int32_t x = 0; x < 8; ++x)
    {
        for (int32_t y = 0; y < 8; ++y)
        {
            sf::RectangleShape cell;
            cell.setSize(GetCellSize());
            cell.setPosition(GetCellPosition(x, y));
            if ((x + y) % 2 == 0)
            {
                cell.setFillColor(sf::Color(181, 136, 99));
            }
            else
            {
                cell.setFillColor(sf::Color(240, 217, 181));
            }

            m_window.draw(cell);
        }
    }
}

void MainWindow::DrawPieces()
{
    for (int32_t x = 0; x < 8; ++x)
    {
        for (int32_t y = 0; y < 8; ++y)
        {
            sf::Sprite sprite;
            const auto name = GetTextureName(x, y);
            if (name.empty())
            {
                continue;
            }

            sprite.setTexture(*Storage::instance()->GetTexture(name));
            sprite.setScale(GetCellSize().x / sprite.getLocalBounds().width, GetCellSize().y / sprite.getLocalBounds().height);
            sprite.setPosition(GetCellPosition(x, y));
            if (sf::Vector2i(x, y) == m_buff)
            {
                sf::Vector2f oldSize(sprite.getLocalBounds().width * sprite.getScale().x, sprite.getLocalBounds().height * sprite.getScale().y);
                sprite.setScale(sprite.getScale().x * 1.2f, sprite.getScale().y * 1.2f);
                sf::Vector2f newSize(sprite.getLocalBounds().width * sprite.getScale().x, sprite.getLocalBounds().height * sprite.getScale().y);
                sprite.setPosition(sprite.getPosition().x - (newSize.x - oldSize.x) / 2, sprite.getPosition().y - (newSize.y - oldSize.y) / 2);
            }
            m_window.draw(sprite);
        }
    }
}

void MainWindow::DrawSelectedPieceMoves()
{
}

void MainWindow::UpdateWindowTitle()
{
    std::string title;
    uint8_t status = GetStatus();
    switch (status)
    {
    case Status::WHITE_TO_MOVE:
        title = "Ваш ход";
        break;
    case Status::BLACK_TO_MOVE:
        title = "Компьютер думает...";
        break;
    case Status::WHITE_WON:
        title = "Вы победили";
        break;
    case Status::BLACK_WON:
        title = "Вы проиграли";
        break;
    case Status::DRAW:
        title = "Ничья";
        break;
    }

    m_window.setTitle(title);
}

sf::Vector2f MainWindow::GetCellSize()
{
    uint32_t side = (std::min(m_window.getSize().x, m_window.getSize().y) - 2 * BOARD_MARGIN) / 8;
    return { static_cast<float>(side), static_cast<float>(side) };
}

sf::Vector2f MainWindow::GetCellPosition(int32_t x, int32_t y)
{
    sf::Vector2f size = GetCellSize();
    return { BOARD_MARGIN + size.x * x, m_window.getSize().y - BOARD_MARGIN - size.y * (y + 1) };
}

uint8_t MainWindow::GetStatus()
{
    return 0;
}

std::string MainWindow::GetTextureName(int32_t x, int32_t y) const
{
    return std::string();
}
