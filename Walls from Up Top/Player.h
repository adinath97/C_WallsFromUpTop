#include <iostream>
#include "Vector2.h"

void Draw(SDL_Renderer* mRenderer);
void UpdatePosition(Vector2 newPosition);
bool CheckForCollision(Vector2 playerPos);

const int PLAYER_HEIGHT = 150;
const int PLAYER_WIDTH = 100;
const int WHEEL_WIDTH = 15;
const int WHEEL_HEIGHT = 10;

class Player {
    public:
        Player(Vector2 position): position(position) {
            PlayerRect.x = static_cast<int>(position.x);
            PlayerRect.y = static_cast<int>(position.y);
            PlayerRect.w = PLAYER_WIDTH;
            PlayerRect.h = PLAYER_HEIGHT;
        }
    
        Vector2 position;
        SDL_Rect PlayerRect, upperRightWheelRect, lowerRightWheelRect, upperLeftWheelRect, lowerLeftWheelRect;

        void Draw(SDL_Renderer* mRenderer);
        void UpdatePosition(Vector2 newPosition);
        bool CheckForCollision(Vector2 playerPos);
};

void Player::Draw(SDL_Renderer* mRenderer) {
    PlayerRect.x = static_cast<int>(position.x);
    PlayerRect.y = static_cast<int>(position.y);
    
    upperRightWheelRect.x = static_cast<int>(position.x);
    

    SDL_RenderFillRect(mRenderer, &PlayerRect);
}

void Player::UpdatePosition(Vector2 newPosition) {
    position = newPosition;
}
