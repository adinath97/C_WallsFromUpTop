#include <iostream>
#include "Vector2.h"

void Draw(SDL_Renderer* mRenderer, Vector2 vecPos);
void UpdatePosition(Vector2 newPosition);
bool CheckForCollision(Vector2 obstaclePos);

const int OBSTACLE_HEIGHT = 50;
const int OBSTACLE_WIDTH = 200;

class Obstacle {
    public:
        Obstacle(Vector2 position): position(position) {
            ObstacleRect.x = static_cast<int>(position.x);
            ObstacleRect.y = static_cast<int>(position.y);
            ObstacleRect.w = OBSTACLE_WIDTH;
            ObstacleRect.h = OBSTACLE_HEIGHT;
        }
    
        Vector2 position;
        SDL_Rect ObstacleRect;

        void Draw(SDL_Renderer* mRenderer, Vector2 vecPos);
        void UpdatePosition(Vector2 newPosition);
        bool CheckForCollision(Vector2 obstaclePos);
};

void Obstacle::Draw(SDL_Renderer* mRenderer, Vector2 vecPos) {
    ObstacleRect.x = static_cast<int>(vecPos.x);
    ObstacleRect.y = static_cast<int>(vecPos.y);

    if(ObstacleRect.w != OBSTACLE_WIDTH) { ObstacleRect.w = OBSTACLE_WIDTH; }
    if(ObstacleRect.h != OBSTACLE_HEIGHT) { ObstacleRect.h = OBSTACLE_HEIGHT; }
    
    SDL_RenderFillRect(mRenderer, &ObstacleRect);
}

void Obstacle::UpdatePosition(Vector2 newPosition) {
    position = newPosition;
}


