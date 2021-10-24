#pragma once

/**
 * @brief This struct will be used to pass detection information between the human detector and position estimator classes. See the UML for more information. 
 * 
 */
struct Detection {
    const int NO_HUMAN_DETECTED = -1;
    double probabilty{0};
    int x{0}, y{0};
    int width{0}, height{0};
    Detection& operator=(const Detection& detect);
    Detection operator+(const Detection& detect) const;
    Detection operator-(const Detection& detect) const;
    Detection& operator+=(const Detection& detect);

    Detection() {}

    Detection(const Detection& detect) {
        this->probabilty = detect.probabilty;
        this->x = detect.x;
        this->y = detect.y;
        this->width = detect.width;
        this->height = detect.height;
    }
};