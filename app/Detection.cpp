#include <cmath>

#include "../include/Detection.hpp"

Detection& Detection::operator=(const Detection& detect) {
    this->probabilty = detect.probabilty;
    this->x = detect.x;
    this->y = detect.y;
    this->width = detect.width;
    this->height = detect.height;
    return *this;
}

Detection Detection::operator+(const Detection& detect) const {
    Detection res;
    res.x = this->x + detect.x;
    res.y = this->y + detect.y;
    res.width = this->width + detect.width;
    res.height = this->height + detect.height;
    return res;
}

Detection Detection::operator-(const Detection& detect) const {
    Detection res;
    res.x = std::abs(this->x - detect.x);
    res.y = std::abs(this->y - detect.y);
    res.width = std::abs(this->width - detect.width);
    res.height = std::abs(this->height - detect.height);
    return res;
}

Detection& Detection::operator+=(const Detection& detect) {
    this->x += detect.x;
    this->y += detect.y;
    this->width += detect.width;
    this->height += detect.height;
    return *this;
}
