#pragma once

#define OutputLog(format, ...) outputLog(__FILE__, __LINE__, format, __VA_ARGS__);

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
