#include "PlayerModel.h"
#include <cmath>

class Vector2D
{
private:
    float x;
    float y;

public:
    explicit Vector2D(const float& x=0, const float& y=0) : x(x), y(y) {}
    Vector2D(const Vector2D& src) : x(src.x), y(src.y) {}
    virtual ~Vector2D() {}

    // Accessors

     float X() const { return x; }
     float Y() const { return y; }
     float X(const float& x) { this->x = x; }
     float Y(const float& y) { this->y = y; }

     float operator*(const Vector2D& v) const
    { return x*v.x + y*v.y; }

    Vector2D operator-() const
    { return Vector2D(-x, -y); }

    inline Vector2D operator-(const Vector2D& v) const
    { return Vector2D(x-v.x, y-v.y); }
    // l-2 norm
    float norm() const { return sqrt(x*x + y*y); }

    // inner angle (radians)
    static float angle(const Vector2D& v1, const Vector2D& v2)
    {
        return acos( (v1 * v2) / (v1.norm() * v2.norm()) );
    }
};


PlayerModel::PlayerModel(float startX, float startY, float width, float height, float sightToX, float sightToY)
        : width(width), height(height), sightToX(sightToX), sightToY(sightToY) {
    position.x = startX;
    position.y = startY;

    Vector2D p1(startX, startY);
    Vector2D p2(sightToY, sightToY);
    Vector2D p3(startX, startY - 1);

    float rad = Vector2D::angle(p2-p1, p3-p1);
    float deg = rad * 180.0 / M_PI;

    model.setPosition(position.x, position.y);
    //model.setOrigin(position.x, position.y);
    model.rotate(-deg);
    //model.rotate(30);
}

// 9 - 23, 42 - 64
PlayerModel::~PlayerModel() = default;

void PlayerModel::draw(sf::RenderTarget &renderTarget, sf::RenderStates renderStates) {

    renderTarget.draw(model);
}

void PlayerModel::setTexture(const sf::Texture &texture) {
    model.setTexture(texture);
}

void PlayerModel::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

PlayerModel::PlayerModel() = default;
