#include "Watchy_Notchy.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "FreeMonoBold9pt7b.h"
// do not use darkmode its broken
#define DARKMODE 0;
#if DARKMODE
#define BG_COLOR GxEPD_BLACK
#define TEXT_COLOR GxEPD_WHITE
#else
#define BG_COLOR GxEPD_WHITE
#define TEXT_COLOR GxEPD_BLACK
#endif


void WatchyNotchy::drawWatchFace() {
    String timeString;
    int16_t x1, y1, lasty;
    uint16_t w, h;


    // some 0 padding for the hour
    if (currentTime.Hour < 10) {
        timeString += "0" + String(currentTime.Hour) + ":";
    }
    else {
        timeString += String(currentTime.Hour) + ":";
    }

    timeString += (currentTime.Minute < 10 ? "0" : "") + String(currentTime.Minute);


    // Draw the actual time onto the center of the watch.
    display.getTextBounds(timeString, 0, 0, &x1, &y1, &w, &h);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(BG_COLOR);


    display.setCursor(100 - 25, 110);
    display.print(timeString);

    // Calculate angle based on hour (12 o'clock is 0 degrees, 30deg+ for each hour) (360 / 12)
    double hourAngleInDegrees = (currentTime.Hour % 12) * 30; 
    double minuteAngleInDegrees = (currentTime.Minute % 60) * 6; // 6deg+ for each min (360 / 60)

    display.drawBitmap(0, 0, BG_BMP, 200, 200, BG_COLOR);
    WatchyNotchy::Point center_point = WatchyNotchy::Point(100, 100);
    double radius = 100; 

    // Adjusting to point triangles to center
    double hourAngleInRadians = (hourAngleInDegrees - 90) * M_PI / 180.0;  
    double minuteAngleInRadians = (minuteAngleInDegrees - 90) * M_PI / 180.0;

    // Hour Triangle size
    double triangleHeight = 42;  
    double halfBase = 21;        

    WatchyNotchy::Point vertex1 = WatchyNotchy::Point(
        center_point.x + radius * cos(hourAngleInRadians),
        center_point.y + radius * sin(hourAngleInRadians)
    );

    WatchyNotchy::Point vertex2 = WatchyNotchy::Point(
        vertex1.x - halfBase * cos(hourAngleInRadians + M_PI / 2),
        vertex1.y - halfBase * sin(hourAngleInRadians + M_PI / 2)
    );

    WatchyNotchy::Point vertex3 = WatchyNotchy::Point(
        vertex1.x + halfBase * cos(hourAngleInRadians + M_PI / 2),
        vertex1.y + halfBase * sin(hourAngleInRadians + M_PI / 2)
    );

    vertex1.x += triangleHeight * cos(hourAngleInRadians + M_PI);
    vertex1.y += triangleHeight * sin(hourAngleInRadians + M_PI);

    // drawing (white color) Hour Triangle
    display.fillTriangle(vertex1.x, vertex1.y, vertex2.x, vertex2.y, vertex3.x, vertex3.y, GxEPD_WHITE);


    // minute triangle points
    double secondRadius = (radius / 2) + 24;
    double secondTriangleHeight = triangleHeight;
    double secondHalfBase = halfBase;

    WatchyNotchy::Point vertex1_second = WatchyNotchy::Point(
        center_point.x + secondRadius * cos(minuteAngleInRadians),
        center_point.y + secondRadius * sin(minuteAngleInRadians)
    );

    WatchyNotchy::Point vertex2_second = WatchyNotchy::Point(
        vertex1_second.x - secondHalfBase * cos(minuteAngleInRadians + M_PI / 2),
        vertex1_second.y - secondHalfBase * sin(minuteAngleInRadians + M_PI / 2)
    );

    WatchyNotchy::Point vertex3_second = WatchyNotchy::Point(
        vertex1_second.x + secondHalfBase * cos(minuteAngleInRadians + M_PI / 2),
        vertex1_second.y + secondHalfBase * sin(minuteAngleInRadians + M_PI / 2)
    );

    vertex1_second.x += secondTriangleHeight * cos(minuteAngleInRadians + M_PI);
    vertex1_second.y += secondTriangleHeight * sin(minuteAngleInRadians + M_PI);

    // minute triangle draw
    display.fillTriangle(vertex1_second.x, vertex1_second.y, vertex2_second.x, vertex2_second.y, vertex3_second.x, vertex3_second.y, GxEPD_BLACK);

}