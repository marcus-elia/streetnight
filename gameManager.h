#ifndef FPS_TEMPLATE_GAMEMANAGER_H
#define FPS_TEMPLATE_GAMEMANAGER_H

#include <vector>
#include <memory>
#include <iostream>
#include <unordered_map>
#include "player.h"
#include "structs.h"
#include "chunk.h"
#include "mathHelper.h"
#include "button.h"
#include "lampPost.h"

enum GameStatus {Intro, Playing, End, Paused};

class GameManager
{
private:
    Player player;

    // Controls
    bool wKey, aKey, sKey, dKey, spacebar;

    // Chunks
    int chunkSize;
    int renderRadius;
    std::unordered_map<int, std::shared_ptr<Chunk>> allSeenChunks;
    std::vector<std::shared_ptr<Chunk>> currentChunks;
    int currentPlayerChunkID;

    GameStatus currentStatus;

    // UI
    int screenWidth, screenHeight;

    Button playButton;
    Button playAgainButton;
    Button quitButton;
    Button continueButton;
    std::vector<std::string> instructions;

    bool closeWindow = false;
    bool showMouse = true;

    // Lighting
    LightSource playerLight;
    std::vector<LightSource> lightSources;
    std::unordered_map<std::shared_ptr<LampPost>, bool> lampPosts; // bool determines if it is close or not

    // Game parameters
    double PLAYER_HEIGHT = 20;
    double PLAYER_RADIUS = 5;
    RGBAcolor CHUNK_GROUND_COLOR = {0, 1, 0, 1};
    double PLAYER_SPEED = 2;
    double MOUSE_SENSITIVITY = 0.03;
    int MAX_DISTANCE_FROM_SPAWN = 10240; // 10 chunks
    double GRAVITY = -0.3;
    double PLAYER_JUMP_AMOUNT = 4;
    int BUTTON_WIDTH = 128;
    int BUTTON_HEIGHT = 64;
    int BUTTON_RADIUS = 16;
    RGBAcolor PLAY_BUTTON_COLOR = {0.0, 0.0, 0.7, 1.0};   // Slightly Dark Blue
    RGBAcolor QUIT_BUTTON_COLOR = {0.7, 0.0, 0.0, 1.0};   // Slightly Dark Red
    RGBAcolor PLAY_BUTTON_COLOR_H = {0.0, 0.2, 1.0, 1.0}; // Lighter Blue
    RGBAcolor QUIT_BUTTON_COLOR_H = {1.0, 0.2, 0.0, 1.0}; // Lighter Red
    RGBAcolor BUTTON_TEXT_COLOR = {1.0,1.0,1.0,1.0};      // White
    RGBAcolor CURSOR_COLOR = {0.3, 0.3, 0.3, 1.0};        // Dark Gray
    RGBAcolor BLACK = {0.0, 0.0, 0.0, 1.0};
    double LIGHT_FADE_FACTOR = 0.001;
    double PLAYER_LIGHT_FOV = PI/4;
    int MAX_LIGHT_LEVEL = 10;
    double LAMP_POST_HEIGHT = 30;
    double LAMP_POST_RADIUS = 2;
    RGBAcolor LAMP_POST_COLOR = {0, 0.3, 0.1, 1.0};
    RGBAcolor LIGHT_COLOR = {1.0, 1.0, 0.5, 1.0};
public:
    GameManager();
    GameManager(int inputScreenWidth, int inputScreenHeight, int inputChunkSize, int inputRenderRadius);

    // Helper functions for the constructors
    void initializePlayer();
    void initializeButtons();
    void makeInstructions();
    void initializePlayerLight();

    // Getters
    Player getPlayer() const;
    bool getWKey() const;
    bool getAKey() const;
    bool getSKey() const;
    bool getDKey() const;
    bool getSpacebar() const;
    GameStatus getCurrentStatus() const;
    bool getCloseWindow() const;
    bool getShowMouse() const;

    // Setters
    void setWKey(bool input);
    void setAKey(bool input);
    void setSKey(bool input);
    void setDKey(bool input);
    void setSpacebar(bool input);
    void setCurrentStatus(GameStatus input);

    // Chunks
    void updateCurrentChunks();

    // Camera
    Point getCameraLocation() const;
    Point getCameraLookingAt() const;
    Point getCameraUp() const;

    // Mouse
    void reactToMouseMovement(int mx, int my, double theta);
    void reactToMouseClick(int mx, int my);

    // Lighting
    double determineOverallLightLevelAt(Point p) const;
    double determineChunkLightLevel(Point p) const;
    void createRandomLampPost(Point chunkCenter, int chunkSize);
    void updateLampPostCloseness();

    // Draw
    void draw() const;
    void drawLampPosts() const;

    // Tick helper functions
    void tick();
    void playerTick();

    // Game Management
    void checkForGameEnd();
    void resetGame();
    void togglePaused();

    // UI
    void drawUI() const;
    void drawCursor() const;
    void displayInstructions() const;
};

#endif //FPS_TEMPLATE_GAMEMANAGER_H
