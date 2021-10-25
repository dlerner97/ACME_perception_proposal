#pragma once

/**
 * @brief This struct will be used to pass detection information between the human detector and position estimator classes. See the UML for more information. 
 * 
 */
struct Detection {
    int x{0}, y{0};
    int width{0}, height{0};
    Detection& operator=(const Detection& detect);
    Detection operator+(const Detection& detect) const;
    Detection operator-(const Detection& detect) const;
    Detection& operator+=(const Detection& detect);

    Detection() {}

    Detection(double prob, int x_, int y_, int w, int h) {
        this->x = x_;
        this->y = y_;
        this->width = w;
        this->height = h;
    }

    Detection(const Detection& detect) {
        this->x = detect.x;
        this->y = detect.y;
        this->width = detect.width;
        this->height = detect.height;
    }
};