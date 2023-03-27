#pragma once

#include <vector>
#include <d2d1.h>

#define BOARD_BLOCK_SIZE        70

enum class eMenuEvent
{
    Default,
    Blocked,
    Spawn_Character,
    Spawn_Monster
};

enum class eType
{
    Tile,
    Block,
    Character,
    None
};

enum class eInGameObjType
{
    None,
    Block_Destructible,
    Block_InDestructible,
    Balloon,
    Character,
    Item,
    Monster,
    Boss,
};

enum class Item
{
    Gift_Boom,
    Gift_Bubble,
    Gift_Dart,
    Gift_Devil,
    Gift_Owl,
    Gift_Potion,
    Gift_Shoes,
    Gift_Skate,
    Gift_Turtle,
    Gift_UFO,
    Gift_None

};

typedef struct _tBlockData
{
    u_int x, y;
    u_int idx;
    eType type;
} tBlockData;

typedef struct _tMapData
{
    u_int gridX, gridY;
    std::vector<eMenuEvent> vecEventData;
    std::vector<tBlockData> vecBlockData;
}tMapData;

typedef struct _tSpriteData
{
    float pivotX = 0.5f, pivotY = 0.5f;
    D2D1_RECT_F rect = {};
    D2D1_SIZE_F size = {};
    DWORD* pixel = nullptr;
    ID2D1Bitmap* bitmap = nullptr;
    eType type;
} tSpriteData;

typedef struct _tSprite
{
    float pivotX = 0.5f, pivotY = 0.5f;
    D2D1_RECT_F rect = {}; // 비트맵 상에서 rect
    D2D1_SIZE_F size = {};
    eType type;
    u_int idx; // 몇 번째 비트맵에 속해있는지

    _tSprite(const _tSpriteData& sprite)
    {
        pivotX = sprite.pivotX;
        pivotY = sprite.pivotY;
        rect = sprite.rect;
        size = sprite.size;
        type = sprite.type;
    }
} tSprite;

typedef struct _tAnimationFrame
{
    float pivotX = 0.5f, pivotY = 0.5f;
    D2D1_RECT_F rect = {};
    D2D1_SIZE_F size = {};
    u_int bitmapIdx;

    _tAnimationFrame(const _tSpriteData& sprite)
    {
        pivotX = sprite.pivotX;
        pivotY = sprite.pivotY;
        rect = sprite.rect;
        size = sprite.size;
    }
} tAnimationFrame;
