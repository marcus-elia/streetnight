#include "gameManager.h"

GameManager::GameManager()
{
    screenWidth = 1024;
    screenHeight = 512;
    chunkSize = 24;
    renderRadius = 20;
    viewDistance = renderRadius*chunkSize;

    initializePlayer();
    updateCurrentChunks();
    initializeButtons();
    makeInstructions();
    initializePlayerLight();
    makeTrain();
}
GameManager::GameManager(int inputScreenWidth, int inputScreenHeight, int inputChunkSize, int inputRenderRadius)
{
    screenWidth = inputScreenWidth;
    screenHeight = inputScreenHeight;
    chunkSize = inputChunkSize;
    renderRadius = inputRenderRadius;
    viewDistance = renderRadius*chunkSize;

    initializePlayer();
    updateCurrentChunks();
    initializeButtons();
    makeInstructions();
    initializePlayerLight();
    makeTrain();
}

// =================================
//
//     Initialization Functions
//
// =================================

void GameManager::initializePlayer()
{
    Point playerStartLoc = {0, PLAYER_HEIGHT/2, 0};
    Point playerStartLook = {0, PLAYER_HEIGHT/2, -10};
    Point playerStartUp = {0, PLAYER_HEIGHT, 0};
    player = Player(playerStartLoc, playerStartLook, playerStartUp, PLAYER_SPEED, MOUSE_SENSITIVITY,
                    PLAYER_HEIGHT, PLAYER_RADIUS, MAX_DISTANCE_FROM_SPAWN, GRAVITY, PLAYER_JUMP_AMOUNT);
    currentPlayerChunkID = getChunkIDContainingPoint(player.getLocation(), chunkSize);
}

void GameManager::initializeButtons()
{
    playButton = Button(screenWidth/2, screenHeight/2, BUTTON_WIDTH, BUTTON_HEIGHT,
            BUTTON_RADIUS, "Play", PLAY_BUTTON_COLOR, BUTTON_TEXT_COLOR, PLAY_BUTTON_COLOR_H);
    playAgainButton = Button(screenWidth/2, screenHeight/2, BUTTON_WIDTH, BUTTON_HEIGHT,
            BUTTON_RADIUS, "Play Again", PLAY_BUTTON_COLOR, BUTTON_TEXT_COLOR, PLAY_BUTTON_COLOR_H);
    continueButton = Button(screenWidth/2, screenHeight/2, BUTTON_WIDTH, BUTTON_HEIGHT,
            BUTTON_RADIUS, "Continue", PLAY_BUTTON_COLOR, BUTTON_TEXT_COLOR, PLAY_BUTTON_COLOR_H);
    quitButton = Button(screenWidth/2, screenHeight/2 - BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT,
            BUTTON_RADIUS, "Quit", QUIT_BUTTON_COLOR, BUTTON_TEXT_COLOR, QUIT_BUTTON_COLOR_H);
}

void GameManager::makeInstructions()
{
    instructions.push_back("Use w,a,s,d to move and spacebar to jump. Press p to pause.");
}

void GameManager::initializePlayerLight()
{
    playerLight = {player.getLocation(), player.getXZAngle(), player.getYAngle(), PLAYER_LIGHT_FOV, MAX_LIGHT_LEVEL};
}

// ===========================
//
//          Getters
//
// ===========================

Player GameManager::getPlayer() const
{
    return player;
}
bool GameManager::getWKey() const
{
    return wKey;
}
bool GameManager::getAKey() const
{
    return aKey;
}
bool GameManager::getSKey() const
{
    return sKey;
}
bool GameManager::getDKey() const
{
    return dKey;
}
bool GameManager::getSpacebar() const
{
    return spacebar;
}
GameStatus GameManager::getCurrentStatus() const
{
    return currentStatus;
}
bool GameManager::getCloseWindow() const
{
    return closeWindow;
}
bool GameManager::getShowMouse() const
{
    return showMouse;
}

// =============================
//
//           Setters
//
// =============================
void GameManager::setWKey(bool input)
{
    wKey = input;
    player.setVelocity(wKey, aKey, sKey, dKey);
}
void GameManager::setAKey(bool input)
{
    aKey = input;
    player.setVelocity(wKey, aKey, sKey, dKey);
}
void GameManager::setSKey(bool input)
{
    sKey = input;
    player.setVelocity(wKey, aKey, sKey, dKey);
}
void GameManager::setDKey(bool input)
{
    dKey = input;
    player.setVelocity(wKey, aKey, sKey, dKey);
}
void GameManager::setSpacebar(bool input)
{
    spacebar = input;
}
void GameManager::setCurrentStatus(GameStatus input)
{
    currentStatus = input;
}

// Chunks
void GameManager::updateCurrentChunks()
{
    // Update the list of current chunks
    currentChunks = std::vector<std::shared_ptr<Chunk>>();
    std::vector<Point2D> chunksInRadius = getChunkTopLeftCornersAroundPoint(currentPlayerChunkID, renderRadius);
    for(Point2D p : chunksInRadius)
    {
        int index = point2DtoChunkID(p);
        if(allSeenChunks.count(index) == 0) // if the chunk has never been seen before
        {
            // Create and add a new Chunk
            allSeenChunks[index] = std::make_shared<Chunk>(p, chunkSize, CHUNK_GROUND_COLOR);

            // Make a lamp post sometimes
            if(rand() % 1000 < 4)
            {
                createRandomLampPost(allSeenChunks[index]->getCenter(), chunkSize);
            }
        }
        currentChunks.push_back(allSeenChunks[index]);
    }
}

void GameManager::makeTrain()
{
    double randAngle = player.getXZAngle() + (rand() % 100)*PI/4 / 100 - (rand() % 100)*PI/2 / 100;
    double x = player.getLocation().x + cos(randAngle)*viewDistance;
    double y = TRAIN_HEIGHT/2;
    double z = player.getLocation().z + sin(randAngle)*viewDistance;
    double trainAngle = atan2(player.getLocation().z - z, player.getLocation().x - x);
    train = Train({x,y,z}, TRAIN_COLOR, TRAIN_WIDTH, TRAIN_HEIGHT, TRAIN_LENGTH, TRAIN_SPEED, trainAngle);
}


// =================================
//
//             Camera
//
// =================================
Point GameManager::getCameraLocation() const
{
    return player.getLocation();
}
Point GameManager::getCameraLookingAt() const
{
    return player.getLookingAt();
}
Point GameManager::getCameraUp() const
{
    return player.getUp();
}

// Mouse
void GameManager::reactToMouseMovement(int mx, int my, double theta)
{
    if(currentStatus == Intro)
    {
        playButton.setIsHighlighted(playButton.containsPoint(mx, screenHeight - my));

        quitButton.setIsHighlighted(quitButton.containsPoint(mx, screenHeight - my));
    }
    else if(currentStatus == Playing)
    {
        player.updateAngles(theta);
        player.updateSphericalDirectionBasedOnAngles();
        player.setVelocity(wKey, aKey, sKey, dKey);
    }
    else if(currentStatus == Paused)
    {
        continueButton.setIsHighlighted(continueButton.containsPoint(mx, screenHeight - my));

        quitButton.setIsHighlighted(quitButton.containsPoint(mx, screenHeight - my));
    }
    else if(currentStatus == End)
    {
        playAgainButton.setIsHighlighted(playAgainButton.containsPoint(mx, screenHeight - my));

        quitButton.setIsHighlighted(quitButton.containsPoint(mx, screenHeight - my));
    }
}
void GameManager::reactToMouseClick(int mx, int my)
{
    if(currentStatus == Intro)
    {
        if(playButton.containsPoint(mx, screenHeight - my))
        {
            showMouse = false;
            currentStatus = Playing;
            resetGame();
        }
        else if(quitButton.containsPoint(mx, screenHeight - my))
        {
            closeWindow = true;
        }
    }
    else if(currentStatus == Playing)
    {
    }
    else if(currentStatus == Paused)
    {
        if(continueButton.containsPoint(mx, screenHeight - my))
        {
            showMouse = false;
            currentStatus = Playing;
        }
        else if(quitButton.containsPoint(mx,screenHeight -  my))
        {
            closeWindow = true;
        }
    }
    else if(currentStatus == End)
    {
        if(playAgainButton.containsPoint(mx, screenHeight - my))
        {
            showMouse = false;
            resetGame();
        }
        else if(quitButton.containsPoint(mx,screenHeight -  my))
        {
            closeWindow = true;
        }
    }
}

// ===============================
//
//           Lighting
//
// ===============================

double GameManager::determineOverallLightLevelAt(Point p) const
{
    double maxSeen = 0.0;
    for(LightSource ls : lightSources)
    {
        double curIntensity = determineLightLevelAt(p, ls, LIGHT_FADE_FACTOR);
        if(curIntensity > maxSeen)
        {
            maxSeen = curIntensity;
        }
    }
    maxSeen = fmax(maxSeen, determineLightLevelAt(p, playerLight, LIGHT_FADE_FACTOR));
    return fmin(1.0, maxSeen / MAX_LIGHT_LEVEL);
}
double GameManager::determineChunkLightLevel(Point p) const
{
    double maxSeen = 0.0;
    for(LightSource ls : lightSources)
    {
        double curIntensity = determineLightIntensityAt(p, ls, LIGHT_FADE_FACTOR);
        if(curIntensity > maxSeen)
        {
            maxSeen = curIntensity;
        }
    }
    maxSeen = fmax(maxSeen, determineLightIntensityAt(p, playerLight, LIGHT_FADE_FACTOR));
    return fmin(1.0, maxSeen / MAX_LIGHT_LEVEL);
}
void GameManager::createRandomLampPost(Point chunkCenter, int chunkSize)
{
    double x = chunkCenter.x + chunkSize/2 - (rand() % chunkSize);
    double z = chunkCenter.z + chunkSize/2 - (rand() % chunkSize);
    Point location = {x, LAMP_POST_HEIGHT/2, z};
    std::shared_ptr<LampPost> lamp = std::make_shared<LampPost>(LampPost(location, LAMP_POST_RADIUS, LAMP_POST_HEIGHT,
            LAMP_POST_RADIUS+1, LAMP_POST_RADIUS*2, LAMP_POST_COLOR, LIGHT_COLOR, MAX_LIGHT_LEVEL/2));
    lampPosts[lamp] = false;
    lightSources.push_back({lamp->getLightLocation(), 0, 0, 2*PI, static_cast<int>(lamp->getLightIntensity())});
}
void GameManager::updateLampPostCloseness()
{
    for(std::pair<std::shared_ptr<LampPost>, bool> element : lampPosts)
    {
        if(distance2d(element.first->getLocation(), player.getLocation()) < renderRadius*chunkSize)
        {
            lampPosts[element.first] = true;
        }
        else
        {
            lampPosts[element.first] = false;
        }
    }
}

// ================================
//
//              Draw
//
// ================================
void GameManager::draw() const
{
    if(currentStatus == Playing || currentStatus == Paused)
    {
        drawChunks();
        drawLampPosts();
        drawTrain();
    }
}
void GameManager::drawLampPosts() const
{
    for(std::pair<std::shared_ptr<LampPost>, bool> element : lampPosts)
    {
        if(element.second)
        {
            element.first->draw(element.first->getLightIntensity() / MAX_LIGHT_LEVEL);
        }
    }
}
void GameManager::drawChunks() const
{
    for(std::shared_ptr<Chunk> c : currentChunks)
    {
        double lightLevel = determineChunkLightLevel(c->getCenter());
        if(lightLevel > 0.01) // for performance, don't draw if it's too dark
        {
            c->draw(lightLevel);
        }
    }
}
void GameManager::drawTrain() const
{
    double lightLevel = determineOverallLightLevelAt(train.getLocation());
    train.draw(lightLevel);
}


// ================================
//
//              Tick
//
// ================================
void GameManager::tick()
{
    if(currentStatus == Playing)
    {
        playerTick();
        updateLampPostCloseness();
        trainTick();
    }
}
void GameManager::playerTick()
{
    player.tick();
    if(spacebar)
    {
        player.tryToJump();
    }

    // Check if the player has entered a new chunk
    int newPlayerChunkID = getChunkIDContainingPoint(player.getLocation(), chunkSize);
    if(newPlayerChunkID != currentPlayerChunkID)
    {
        currentPlayerChunkID = newPlayerChunkID;
        updateCurrentChunks();
    }

    playerLight.location = player.getLocation();
    playerLight.xzAngle = player.getXZAngle();
    playerLight.yAngle = player.getYAngle();
}
void GameManager::trainTick()
{
    train.tick();
    if(distance2d(train.getLocation(), player.getLocation()) > 1.5*viewDistance)
    {
        makeTrain();
    }
}

// Game Management
void GameManager::resetGame()
{
    initializePlayer();
    currentStatus = Playing;
}
void GameManager::togglePaused()
{
    if(currentStatus == Paused)
    {
        currentStatus = Playing;
        showMouse = false;
    }
    else if(currentStatus == Playing)
    {
        currentStatus = Paused;
        showMouse = true;
    }
}

// UI
void GameManager::drawUI() const
{
    if(currentStatus == Intro)
    {
        playButton.draw();
        quitButton.draw();
        displayInstructions();
    }
    else if(currentStatus == Playing)
    {
        drawCursor();
    }
    else if(currentStatus == Paused)
    {
        continueButton.draw();
        quitButton.draw();
    }
    else if(currentStatus == End)
    {
        playAgainButton.draw();
        quitButton.draw();
    }
}
void GameManager::drawCursor() const
{
    setGLColor(CURSOR_COLOR);
    glBegin(GL_QUADS);    // Draw a + shape with two quads
    glVertex2f(screenWidth/2 - 5, screenHeight/2 + 2);
    glVertex2f(screenWidth/2 - 5, screenHeight/2 - 2);
    glVertex2f(screenWidth/2 + 5, screenHeight/2 - 2);
    glVertex2f(screenWidth/2 + 5, screenHeight/2 + 2);


    glVertex2f(screenWidth/2 - 2, screenHeight/2 + 5);
    glVertex2f(screenWidth/2 - 2, screenHeight/2 - 5);
    glVertex2f(screenWidth/2 + 2, screenHeight/2 - 5);
    glVertex2f(screenWidth/2 + 2, screenHeight/2 + 5);
    glEnd();
}

void GameManager::displayInstructions() const
{
    setGLColor(BLACK);
    for(int i = 0; i < instructions.size(); i++)
    {
        std::string s = instructions[i];
        glRasterPos2i(10, screenHeight - 15*i - 15);
        for(const char &letter : s)
        {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
        }
    }
}