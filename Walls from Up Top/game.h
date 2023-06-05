#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h> 
#include <cstdlib>
#include <ctime>

#include "Vector2.h"
#include "Player.h"
#include "Obstacle.h"
#include "RoadLine.h"

    void ResetGame();
    bool Initialize();
    void StartingText();
    void EndingText();
    void DisplayText();
    void InitSDLText();

    bool Initialize();
    void RunLoop();
    void ShutDown();
    void ProcessInput();
    void UpdateGame();
    void CheckForCollision();
    void InstantiateObstacle(Vector2 obstaclePosition);
    void InstantiateRoadLine(Vector2 roadLinePosition);
    void GenerateOutput();

class Game {

    public:
        Game():mWindow(nullptr), mIsRunning(true) {
            mTicksCount = 0;
        }

        bool Initialize();
        void RunLoop();
        void ShutDown();
    
    private:

        //used to track state of snake
        enum State {
            EActive,
            EPaused,
            EDead
        };

        //used to track direction of snake
        enum Direction {
            Right,
            Left,
            None,
        };

        Direction mPlayerDir;

        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

        Uint32 mTicksCount;

        Vector2 mPlayerPosition = Vector2(75,500);
        Vector2 mTargetPosition = Vector2(75,500);

        const float thickness = 16.0f;

        float moveSpeed = 50.0f;

        int resetClicks = 0, playerScore = 0;

        float deltaTime, increment, obstacleTimer, obstacleMoveSpeed = 75.0f;
        
        bool resetGame = true, mIsRunning, startRound, gameOver;

        std::string playerScoreStr;

        SDL_Rect playerRect;

        std::vector<RoadLine*> mRoadLines;
        std::vector<Obstacle*> mObstacles;
        std::vector<Vector2> mObstaclePositions;
        std::vector<Vector2> mRoadLinePositions;

        void ProcessInput();
        void UpdateGame();
        void CheckForCollision();
        void InstantiateObstacle(Vector2 obstaclePosition);
        void InstantiateRoadLine(Vector2 roadLinePosition);
        void GenerateOutput();
        void StartingText();
        void EndingText();
        void DisplayText();
        void InitSDLText();
        void ResetGame();

};

bool Game::Initialize() {
    //random number generator seed
    srand (time(NULL));

    //initialize SDL library
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    //initialize text
    InitSDLText();

    if(sdlResult != 0) {
        //initialization failed
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    //if initialization successful, create window
    mWindow = SDL_CreateWindow(
        "Walls From Up Top",
        100,
        100,
        768,
        720,
        0 // Flags
    );

    if(!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //initialization flags. use accelerated renderer and enable vsync
    );

    mPlayerDir = None;

    return true;
}

void Game::ResetGame() {
    //reset variables
    gameOver = false;
    startRound = false;
    mObstacles.clear();
    mObstaclePositions.clear();
    mPlayerPosition.x = 75.0f;
    mTargetPosition.x = 75.0f;
    mPlayerDir = None;
    resetClicks = 0;
    playerScore = 0;
}

void Game::InitSDLText() {
    //initialize, else load error
    if(TTF_Init() == -1) {
        std::cout << "Failed to initialize text.Error: " << TTF_GetError() << std::endl;
    }
}

void Game::StartingText() {
    SDL_SetRenderDrawColor( //pointer, RGBA
            mRenderer,
            0,
            0,
            0,
            0
        );

        SDL_RenderClear(mRenderer);

        //draw game scene
        SDL_SetRenderDrawColor( //pointer, RGBA
            mRenderer,
            255,
            255,
            255,
            255
        );

        TTF_Font* ourFont;
        SDL_Surface * titleSurfaceText;	
        SDL_Surface * optionSurfaceText;
        SDL_Texture * titleTexture;
        SDL_Texture * optionTexture;

        SDL_Rect titleText = {210,100,300,200};
        SDL_Rect optionText = {110,400,500,100};

        //load font file and set size
        ourFont = TTF_OpenFont("AldotheApache.ttf",1000);

        //confirm font loaded
        if(ourFont == nullptr) {
            std::cout << "Could not load font" << std::endl;
            exit(1);
        }

        SDL_Color textColor = {255,255,255,255};

        //pixels from text
        titleSurfaceText = TTF_RenderText_Solid(ourFont,"WALLS FROM UP TOP",textColor);
        optionSurfaceText = TTF_RenderText_Solid(ourFont,"HIT SPACEBAR TO PLAY",textColor);

        //set up texture
        titleTexture = SDL_CreateTextureFromSurface(mRenderer,titleSurfaceText);
        optionTexture = SDL_CreateTextureFromSurface(mRenderer,optionSurfaceText);

        SDL_FreeSurface(titleSurfaceText);
        SDL_FreeSurface(optionSurfaceText);

        SDL_RenderCopy(mRenderer,titleTexture,NULL,&titleText);
        SDL_RenderCopy(mRenderer,optionTexture,NULL,&optionText);

        //destroy texture
        SDL_DestroyTexture(titleTexture);
        SDL_DestroyTexture(optionTexture);

        //close font
        TTF_CloseFont(ourFont);

        SDL_RenderPresent(mRenderer); //swap front and back buffers
}

void Game::EndingText() {
    //std::cout << "CONTINUE ON!" << std::endl;
            SDL_SetRenderDrawColor( //pointer, RGBA
                mRenderer,
                0,
                0,
                0,
                0
            );

            SDL_RenderClear(mRenderer);

            //draw game scene
            SDL_SetRenderDrawColor( //pointer, RGBA
                mRenderer,
                255,
                255,
                255,
                255
            );
            TTF_Font* ourFont;
            SDL_Surface * titleSurfaceText;	
            SDL_Surface * optionSurfaceText;
            SDL_Texture * titleTexture;
            SDL_Texture * optionTexture;

            SDL_Rect titleText = {210,100,300,200};
            SDL_Rect optionText = {110,400,500,100};

            //load font file and set size
            ourFont = TTF_OpenFont("AldotheApache.ttf",1000);

            //confirm font loaded
            if(ourFont == nullptr) {
                std::cout << "Could not load font" << std::endl;
                exit(1);
            }

            SDL_Color textColor = {255,255,255,255};

            //pixels from text
            titleSurfaceText = TTF_RenderText_Solid(ourFont,"WALLS FROM UP TOP",textColor);
            optionSurfaceText = TTF_RenderText_Solid(ourFont,"EVERYONE WINS! A FOR EFFORT",textColor);

            //set up texture
            titleTexture = SDL_CreateTextureFromSurface(mRenderer,titleSurfaceText);
            optionTexture = SDL_CreateTextureFromSurface(mRenderer,optionSurfaceText);

            SDL_FreeSurface(titleSurfaceText);
            SDL_FreeSurface(optionSurfaceText);

            SDL_RenderCopy(mRenderer,titleTexture,NULL,&titleText);
            SDL_RenderCopy(mRenderer,optionTexture,NULL,&optionText);

            //destroy texture
            SDL_DestroyTexture(titleTexture);
            SDL_DestroyTexture(optionTexture);

            //close font
            TTF_CloseFont(ourFont);

            SDL_RenderPresent(mRenderer); //swap front and back buffers
        
}

void Game::DisplayText() {
    //add text
    TTF_Font* ourFont;
    SDL_Surface * playerSurfaceText;	
    SDL_Surface * AISurfaceText;
    SDL_Texture * playerTexture;
    SDL_Texture * AITexture;

    SDL_Rect playerScoreText = {700,25,50,50};

    //load font file and set size
    ourFont = TTF_OpenFont("AldotheApache.ttf",1000);

    //confirm font loaded
    if(ourFont == nullptr) {
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }

    SDL_Color textColor = {255,255,255,255};

    playerScoreStr = std::to_string(playerScore);
    char const *pchar = playerScoreStr.c_str();  //use char const* as target type

    //pixels from text
    playerSurfaceText = TTF_RenderText_Solid(ourFont,pchar,textColor);

    //set up texture
    playerTexture = SDL_CreateTextureFromSurface(mRenderer,playerSurfaceText);

    SDL_FreeSurface(playerSurfaceText);

    SDL_RenderCopy(mRenderer,playerTexture,NULL,&playerScoreText);

    //destroy texture
    SDL_DestroyTexture(playerTexture);

    //close font
    TTF_CloseFont(ourFont);

    SDL_RenderPresent(mRenderer); //swap front and back buffers
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ShutDown() {
    //destroy SDL_Window
    SDL_DestroyWindow(mWindow);

    //destroy SDL_Renderer
    SDL_DestroyRenderer(mRenderer);

    //close SDL
    SDL_Quit();
}

void Game::ProcessInput() {

    SDL_Event event;

    //go through all events and respond as desired/appropriate
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ) {
                    case SDLK_SPACE:
                        if(!gameOver && !startRound && resetClicks < 2) {
                            resetClicks++;
                            startRound = true;
                        }
                        else if(gameOver && resetClicks >= 2) {
                            ResetGame();
                        }
                        break;
                }
                break;
        }

        if(!startRound) { return; }

        if(event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            if(event.key.keysym.sym == SDLK_RIGHT) {
                mPlayerDir = Right;
                mTargetPosition.x += 250.0f;
                if(mTargetPosition.x > 575.0f) {
                    mTargetPosition.x = 575.0f;
                }
            }
            if(event.key.keysym.sym == SDLK_LEFT) {
                mPlayerDir = Left;
                mTargetPosition.x -= 250.0f;
                if(mTargetPosition.x < 75.0f) {
                    mTargetPosition.x = 75.0f;
                }
            }
        }
    }

    // Retrieve the state of all of the keys then scan each as desired
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }

}

void Game::UpdateGame() {
    if(gameOver) { return; }

    bool removeElement = false, removeNetElement1 = false, removeNetElement2 = false;
    int removalIndex = 100, netRemovalIndex1 = 1000, netRemovalIndex2 = 1000;

    if(mRoadLines.size() > 0) {
        //removeNetElement1 = false;
        for(int i = 0; i < mRoadLines.size(); i++) {
            /* if(mRoadLinePositions[i].y > 1100.0f && !removeNetElement1) {
                //std::cout << "HELLOOOOO" << std::endl;
                //removeNetElement1 = true;
                //netRemovalIndex1 = i;
            }*/
        }
    }

    /* if(mObstacles.size() > 0) {
        for(int i = 0; i < mObstacles.size(); i++) {
            if(removeElement) { continue; }
            if(mObstaclePositions[i].y > 1000.0f && !removeElement) {
                removeElement = true;
                removalIndex = i;
            }
        }
    } */

    //update frame at fixed intervals (fixedDeltaTime)
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    //get deltaTime
    deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    mTicksCount = SDL_GetTicks();

    //clamp deltaTime
    if(deltaTime > .05f) {
        deltaTime = 0.05f;
    }

    if(!startRound) { return; }

    switch(mPlayerDir) {
        case Left:
            mPlayerPosition.x -= moveSpeed;
            break;
        case Right:
            mPlayerPosition.x += moveSpeed;
            break;
        case None:
            break;
        default:
            break;
    }

    increment = 0;

    obstacleTimer += deltaTime;

    if(obstacleTimer > 3.0f) {
        //std::cout << "INSTANTIATING!!!" << std::endl;
        obstacleTimer = 0.0f;
        int xPos = 0, x = rand() % 3;

        switch(x) {
            case 0:
                xPos = 0;
                break;
            case 1:
                xPos = 250;
                break;
            case 2:
                xPos = 500;
                break;
            default:
                xPos = 0;
                break;
        }

        //instantiate obstacle
        InstantiateObstacle(Vector2(xPos,0));
    }

    //instantiate road lines
    /* if(mRoadLines.size() == 0) {
        for(int i = 0; i < 40; i++) {
            if(i < 20) {
                InstantiateRoadLine(Vector2(250,i * 50));
            } else {
                InstantiateRoadLine(Vector2(500,(i - 20) * 50));
            } 
        }
    } */

    /*for(int i = 0; i < mRoadLines.size(); i++) {
        std::cout << mRoadLinePositions[i].x << "," << mRoadLinePositions[i].y << std::endl;
    }*/


    //update obstacle positions
    if(mObstacles.size() > 0) {
        for(int i = 0; i < mObstacles.size(); i++) {
            mObstaclePositions[i].y += deltaTime * obstacleMoveSpeed;
            if(mObstaclePositions[i].y > 700.0f) {
                removeElement = true;
            }
        }
    }

    if(removeElement) {
        removeElement = false;
        mObstaclePositions.erase(mObstaclePositions.begin());
        mObstacles.erase(mObstacles.begin());
        playerScore++;
    }
    

    //move 'net' downwards to create illusion of motion
    /* if(mRoadLines.size() > 0) {
        for(int i = 0; i < mRoadLines.size(); i++) {
            mRoadLinePositions[i].y += deltaTime * obstacleMoveSpeed;
        }
    } */

    //check for collisions with obstacles
    if(mObstacles.size() > 0) {
        //std::cout << "CHECKING!" << std::endl;
        CheckForCollision();
    }

    //remove excess net elements
    if(removeNetElement1) {
        //remove first obstacle (swap with final position, remove!)
        std::swap(mRoadLinePositions[netRemovalIndex1], mRoadLinePositions.back());
        mRoadLinePositions.pop_back();
        //remove obstacle position
        std::swap(mRoadLines[netRemovalIndex1], mRoadLines.back());
        mRoadLines.pop_back();
    }
    
    if(mPlayerPosition.x == mTargetPosition.x) { mPlayerDir = None; } 
}

void Game::CheckForCollision() {
    SDL_bool collision;
    SDL_Rect currentObstacle;
    int removeObstacleIndex = mObstacles.size() + 1;

    playerRect.x = mPlayerPosition.x;
    playerRect.y = mPlayerPosition.y;
    playerRect.w = 150;
    playerRect.h = 100;

    for(int i = 0; i < mObstacles.size(); i++) {
        currentObstacle.x = mObstaclePositions[i].x;
        currentObstacle.y = mObstaclePositions[i].y;
        currentObstacle.w = 200;
        currentObstacle.h = 50;

        collision = SDL_HasIntersection(&currentObstacle, &playerRect);

        if(collision) {
            gameOver = true;
            resetClicks++;
        }

        /* if(collision && removeObstacleIndex > mObstacles.size()) {
            //std::cout << "AHHHHHHHHHH" << std::endl;
            removeObstacleIndex = i;
        } */
    }

    /* if(removeObstacleIndex <= mObstacles.size()) {
        //std::cout << "REMOVING!!!!" << std::endl;
        //remove first obstacle (swap with final position, remove!)
        std::swap(mObstaclePositions[removeObstacleIndex], mObstaclePositions.back());
        mObstaclePositions.pop_back();
        //remove obstacle position
        std::swap(mObstacles[removeObstacleIndex], mObstacles.back());
        mObstacles.pop_back();
    } */
}

void Game::InstantiateObstacle(Vector2 obstaclePosition) {
    Obstacle obstacle(obstaclePosition + Vector2(25,0));
    Obstacle* obstaclePtr = &obstacle; 
    mObstaclePositions.push_back(obstaclePosition + Vector2(25,0));
    mObstacles.push_back(obstaclePtr);
}

void Game::InstantiateRoadLine(Vector2 roadLinePosition) {
    RoadLine roadLine(roadLinePosition);
    RoadLine* roadLinePtr = &roadLine; 
    mRoadLinePositions.push_back(roadLinePosition);
    mRoadLines.push_back(roadLinePtr);
}

void Game::GenerateOutput() {

    if(!gameOver && !startRound && resetClicks == 0) { //game not started yet 
        StartingText();
        return;
    } else if(gameOver) { //game played till end
        if(resetClicks == 2) {
            EndingText();
            return;
        }
    } 
    
    SDL_SetRenderDrawColor(mRenderer,0,0,0,0);

    SDL_RenderClear(mRenderer); //clear back buffer to current draw color

    SDL_SetRenderDrawColor(mRenderer,255,255,255,255);

    SDL_Rect topWall = {0,0,768,thickness};
    SDL_Rect bottomWall = {0,1008,768,thickness};
    SDL_Rect leftWall = {0,0,thickness,1024};
    SDL_Rect rightWall = {752,0,thickness,1024};
    
    if(mPlayerPosition.x >= 575) {
        mPlayerPosition.x = 575.0f;
    } else if(mPlayerPosition.x <= 75) {
        mPlayerPosition.x = 75.0f;
    }
    
    //create player
    Player playerInstance(mPlayerPosition);

    //draw player
    playerInstance.Draw(mRenderer);

    //draw road lines
    /* if(mRoadLines.size() != 0) {
        //std::cout << mRoadLines.size() << std::endl;
        for(int i = 0; i < 40; i++) {
            mRoadLinePositions[i].y += deltaTime * obstacleMoveSpeed;
            if(mRoadLinePositions[i].y > 750) {
                mRoadLinePositions[i].y = 0;
            }
            mRoadLines[i]->UpdatePosition(Vector2(mRoadLinePositions[i].x,mRoadLinePositions[i].y));
            Vector2 vecPos = Vector2(mRoadLinePositions[i].x,mRoadLinePositions[i].y);
            std:: cout << vecPos.x << "," << vecPos.y << std::endl;
            mRoadLines[i]->Draw(mRenderer,vecPos);
        }
    } */

    //draw obstacles
    if(mObstacles.size() != 0) {
        for(int i = 0; i < mObstacles.size(); i++) {
            mObstacles[i]->UpdatePosition(Vector2(mObstaclePositions[i].x,mObstaclePositions[i].y));
            Vector2 vecPos = Vector2(mObstaclePositions[i].x,mObstaclePositions[i].y);
            mObstacles[i]->Draw(mRenderer,vecPos);
    } }

    SDL_RenderFillRect(mRenderer,&topWall);
    SDL_RenderFillRect(mRenderer,&rightWall);
    SDL_RenderFillRect(mRenderer,&leftWall);
    SDL_RenderFillRect(mRenderer,&bottomWall);

    //SDL_RenderPresent(mRenderer);

    DisplayText();
}
