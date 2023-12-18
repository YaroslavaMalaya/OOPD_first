#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace sf;
using namespace std;

int blockShapes[7][4][4][4] = {
        // Type: O
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                }
        },

        // Type: I
        {
                {
                        { 0, 0, 0, 0 },
                        { 1, 1, 2, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 1, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 1, 1, 2, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 1, 0 }
                }
        },

        // Type: S
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 0, 2, 1 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 1 },
                        { 0, 0, 0, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 0, 2, 1 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 1 },
                        { 0, 0, 0, 1 },
                        { 0, 0, 0, 0 }
                }
        },

        // Type: Z
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 0, 1, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 1 },
                        { 0, 0, 2, 1 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 0, 1, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 1 },
                        { 0, 0, 2, 1 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                }
        },

        // Type: L
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 1 },
                        { 0, 1, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 0 },
                        { 0, 0, 1, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 0, 1 },
                        { 0, 1, 2, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 1, 0 },
                        { 0, 0, 2, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                }
        },

        // Type: J
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 1 },
                        { 0, 0, 0, 1 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 1 },
                        { 0, 0, 2, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 1, 0, 0 },
                        { 0, 1, 2, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 0 },
                        { 0, 1, 1, 0 },
                        { 0, 0, 0, 0 }
                }
        },

        // Type: T
        {
                {
                        { 0, 0, 0, 0 },
                        { 0, 1, 2, 1 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 0, 2, 1 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 1, 2, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 }
                },
                {
                        { 0, 0, 1, 0 },
                        { 0, 1, 2, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 0, 0 }
                }
        }
};

class Map {
private:
    int width;
    int height;
    int removedLines;
    RectangleShape field;
    vector<vector<int>> grid;
    const int DEFAULT_ROWS_COUNT = 23;
    const int DEFAULT_COLUMNS_COUNT = 12;
    const int DEFAULT_CELL_SIZE = 35;
    friend class Block;

public:
    Map(int w, int h) : width(w), height(h), removedLines(0) {
        field.setSize(Vector2f(width, height));
        field.setFillColor(Color::Black);
        field.setPosition((1000 - width) / 2.0f,0);

        // emptyCellNumber = -1;
        grid.resize(DEFAULT_ROWS_COUNT, vector<int>(DEFAULT_COLUMNS_COUNT, -1));
    }

    void draw(RenderWindow& window) {
        window.draw(field);

        // draw the grid
        for (int row = 0; row < DEFAULT_ROWS_COUNT; ++row) {
            for (int col = 0; col < DEFAULT_COLUMNS_COUNT; ++col) {
                RectangleShape cell(Vector2f(DEFAULT_CELL_SIZE, DEFAULT_CELL_SIZE));
                cell.setPosition(field.getPosition().x + col * DEFAULT_CELL_SIZE,
                                 field.getPosition().y + row * DEFAULT_CELL_SIZE);
                cell.setFillColor(grid[row][col] == -1 ? Color::Transparent : Color::White);
                cell.setOutlineColor(Color(55, 55, 55));
                cell.setOutlineThickness(1);
                window.draw(cell);
            }
        }
    }

    bool canPlaceBlock(int x, int y, int shape[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[i][j] != 0) {
                    int gridX = x + j;
                    int gridY = y + i;
                    if (gridX < 0 || gridX >= DEFAULT_COLUMNS_COUNT || gridY < 0 ||
                    gridY >= DEFAULT_ROWS_COUNT || grid[gridY][gridX] != -1) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void dropBlock(int x, int y, int shape[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[i][j] != 0) {
                    grid[y + i][x + j] = shape[i][j];
                }
            }
        }
    }

    bool checkLine();
    void removeLine();
    void changeSize();
};

class Block {
public:
    enum class Type { O, I, S, Z, L, J, T };

private:
    Type type;
    Color color;
    Time delay;
    int shape[4][4];
    int rotationState;
    friend class GameMenu;

public:
    Block(Type& type) : type(type), rotationState(0) {
        // copying a block of memory from one location to another
        // destination (where to copy), source (where to copy from) and size of the memory block to be copied
        memcpy(shape, blockShapes[static_cast<int>(type)][rotationState], sizeof(shape));
    }

    void rotate() {
        rotationState = (rotationState + 1) % 4;
        memcpy(shape, blockShapes[static_cast<int>(type)][rotationState], sizeof(shape));
    }

    void draw(RenderWindow &window,Map& map, int x, int y) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[i][j] != 0) {
                    RectangleShape cell(Vector2f(map.DEFAULT_CELL_SIZE, map.DEFAULT_CELL_SIZE));
                    cell.setPosition(map.field.getPosition().x + (x + j) * map.DEFAULT_CELL_SIZE,
                                     map.field.getPosition().y + (y + i) * map.DEFAULT_CELL_SIZE);
                    cell.setFillColor(Color::White);
                    window.draw(cell);
                }
            }
        }
    }

};

class Player {
private:
    string name;
    int currentScore;
    int bestScore;
    string currentTime;
    string bestTime;

public:
    void displayBestScore();
    void updateTime(int time);
    void updateBestTime(int time);
};

class ScoreSystem {
private:
    int lastScore;
    int bestScore;

public:
    int calculateScore(int lines);
    int bonusScore(int consecutiveLines);
    void updateScore(int score);
    void updateBestScore(int score);
};

class GameDataStorage {
private:
    vector<Player*> players;

public:
    void savePlayerData(Player player);
    Player* loadPlayerData();
};

class GameStateManager {
private:
    string currentState;

public:
    void changeState(string newState);
    string getState();
    void pauseGame();
    void resumeGame();
};

class Button {
private:
    Sprite sprite;
    bool isHovered(RenderWindow& window) {
        auto mousePos = Mouse::getPosition(window);
        return sprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));
    }

public:
    Button(Texture& texture, float x, float y) {
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
    }
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }
    bool isClicked(RenderWindow& window) {
        return isHovered(window) && Mouse::isButtonPressed(Mouse::Left);
    }
};

class GameMenu {
private:
    bool gameOver;
    Block::Type types[7] = {Block::Type::O, Block::Type::I, Block::Type::S, Block::Type::Z,
                            Block::Type::L, Block::Type::J, Block::Type::T};

public:
    GameMenu(): gameOver(false){};

    Block generateRandomBlock() {
        int randIndex = rand() % 7;
        return Block(types[randIndex]);
    }

    void startGame(){
        RenderWindow window(VideoMode(1000, 805), "Tetris game from Yarrochka");
        Texture backgroundImage;
        backgroundImage.loadFromFile("../Images/background1.png");

        Sprite backgroundSprite;
        backgroundSprite.setTexture(backgroundImage);
        backgroundSprite.setScale(
                float(window.getSize().x) / backgroundImage.getSize().x,
                float(window.getSize().y) / backgroundImage.getSize().y
        );

        Texture playImage, exitImage;
        playImage.loadFromFile("../Images/Buttons/play.png");
        exitImage.loadFromFile("../Images/Buttons/exit.png");

        Button playButton(playImage, 100, 100);
        Button exitButton(exitImage, 122, 250);
        bool isMenu = true;
        Texture backgroundImageForGame;
        backgroundImageForGame.loadFromFile("../Images/background2.png");
        Sprite backgroundImageForGameSprite;
        backgroundImageForGameSprite.setTexture(backgroundImageForGame);
        backgroundImageForGameSprite.setScale(
                float(window.getSize().x) / backgroundImageForGame.getSize().x,
                float(window.getSize().y) / backgroundImageForGame.getSize().y
        );
        Map gameMap(420, 805);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }

            window.clear();

            if (isMenu) {
                window.draw(backgroundSprite);
                playButton.draw(window);
                exitButton.draw(window);

                if (playButton.isClicked(window)) {
                    isMenu = false;
                }
                if (exitButton.isClicked(window)) {
                    window.close();
                }
            } else {
                while (!gameOver && window.isOpen()) {
                    Block currentBlock = generateRandomBlock(); // generate a new block
                    Vector2i blockPosition(7, 0);

                    bool blockPlaced = false;
                    while (!blockPlaced && window.isOpen()) {
                        while (window.pollEvent(event)) {
                            if (event.type == Event::Closed)
                                window.close();
                        }

                        // move block left
                        if (Keyboard::isKeyPressed(Keyboard::Left)) {
                            if (gameMap.canPlaceBlock(blockPosition.x - 1, blockPosition.y, currentBlock.shape)) {
                                blockPosition.x -= 1;
                            }
                        }

                        // move block right
                        if (Keyboard::isKeyPressed(Keyboard::Right)) {
                            if (gameMap.canPlaceBlock(blockPosition.x + 1, blockPosition.y, currentBlock.shape)) {
                                blockPosition.x += 1;
                            }
                        }

                        // speed up the block
                        if (Keyboard::isKeyPressed(Keyboard::Down)) {
                            if (gameMap.canPlaceBlock(blockPosition.x + 1, blockPosition.y, currentBlock.shape)) {
                                blockPosition.y += 1;
                            }
                        }

                        if (Keyboard::isKeyPressed(Keyboard::Up)) {
                            int previousRotationState = currentBlock.rotationState;
                            currentBlock.rotate();

                            // check if the new rotation is possible, if not revert
                            if (!gameMap.canPlaceBlock(blockPosition.x, blockPosition.y, currentBlock.shape)) {
                                currentBlock.rotationState = previousRotationState;
                                memcpy(currentBlock.shape, blockShapes[static_cast<int>(currentBlock.type)][currentBlock.rotationState], sizeof(currentBlock.shape));
                            }
                        }

                        if (gameMap.canPlaceBlock(blockPosition.x, blockPosition.y + 1, currentBlock.shape)) {
                            blockPosition.y++;
                        } else {
                            gameMap.dropBlock(blockPosition.x, blockPosition.y, currentBlock.shape);
                            blockPlaced = true;
                        }

                        // draw the block at its current position
                        window.draw(backgroundImageForGameSprite);
                        gameMap.draw(window);
                        currentBlock.draw(window, gameMap, blockPosition.x, blockPosition.y);
                        window.display();

                        this_thread::sleep_for(chrono::milliseconds(450));

                        if (!gameMap.canPlaceBlock(7, 0, currentBlock.shape)) {
                            gameOver = true;
                        }
                    }

                    // After placing a block, check for full lines and remove them
                    // gameMap.removeFullLines(); // This method should be implemented
                }
            }

            window.display();
        }
    };

    void endGame();
    void checkGameOver();
    void displayPlayerData();
};

int main() {
    GameMenu gameMenu;
    gameMenu.startGame();

    return 0;
}
