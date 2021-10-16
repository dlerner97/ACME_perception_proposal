#pragma once

/**
 * @brief This struct will be used to pass detection information between the human detector and position estimator classes. See the UML for more information. 
 * 
 */
struct Detection
{
    const int NO_HUMAN_DETECTED = -1;
    double probabilty{};
    int x{}, y{};
    int width{}, height{};
};
