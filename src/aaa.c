#define NOGDI // Rectangle ‚ÌÕ“Ë‚ğ‰ñ”ğ
#define NOWINMESSAGES // CloseWindow ‚È‚Ç‚ÌÕ“Ë‚ğ‰ñ”ğ

#include "common/common.h"
#include "vm/assert.h"
#include "vm/interceptor.h"
#include "vm/object.h"
#include "vm/memory.h"
#include "vm/vm.h"
#include "vm/native.h"
#include "vm/string.h"
#include "std/util.h"
#include "clox_raylib.h"

#undef CloseWindow  
#undef ShowCursor      
#undef LoadImage      
#undef DrawText      
#undef DrawTextEx      
#undef PlaySound      

#define CloseWindow     rl_CloseWindow
#define ShowCursor      rl_ShowCursor
#define LoadImage      rl_LoadImage
#define DrawText      rl_DrawText
#define DrawTextEx      rl_DrawTextEx
#include <raylib.h>  // include raylib here <---
#include "helper.h"




// Lox class for: struct Vector2
LOX_METHOD(Vector2, __init__) {
    if (argCount != 2) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "x;", args[0]);
    setObjProperty(vm, self, "y;", args[1]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Vector3
LOX_METHOD(Vector3, __init__) {
    if (argCount != 3) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "x;", args[0]);
    setObjProperty(vm, self, "y;", args[1]);
    setObjProperty(vm, self, "z;", args[2]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Vector4
LOX_METHOD(Vector4, __init__) {
    if (argCount != 4) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "x;", args[0]);
    setObjProperty(vm, self, "y;", args[1]);
    setObjProperty(vm, self, "z;", args[2]);
    setObjProperty(vm, self, "w;", args[3]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Matrix
LOX_METHOD(Matrix, __init__) {
    if (argCount != 16) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "m0;", args[0]);
    setObjProperty(vm, self, "m4;", args[1]);
    setObjProperty(vm, self, "m8;", args[2]);
    setObjProperty(vm, self, "m12;", args[3]);
    setObjProperty(vm, self, "m1;", args[4]);
    setObjProperty(vm, self, "m5;", args[5]);
    setObjProperty(vm, self, "m9;", args[6]);
    setObjProperty(vm, self, "m13;", args[7]);
    setObjProperty(vm, self, "m2;", args[8]);
    setObjProperty(vm, self, "m6;", args[9]);
    setObjProperty(vm, self, "m10;", args[10]);
    setObjProperty(vm, self, "m14;", args[11]);
    setObjProperty(vm, self, "m3;", args[12]);
    setObjProperty(vm, self, "m7;", args[13]);
    setObjProperty(vm, self, "m11;", args[14]);
    setObjProperty(vm, self, "m15;", args[15]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Color
LOX_METHOD(Color, __init__) {
    if (argCount != 4) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "r;", args[0]);
    setObjProperty(vm, self, "g;", args[1]);
    setObjProperty(vm, self, "b;", args[2]);
    setObjProperty(vm, self, "a;", args[3]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Rectangle
LOX_METHOD(Rectangle, __init__) {
    if (argCount != 4) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "x;", args[0]);
    setObjProperty(vm, self, "y;", args[1]);
    setObjProperty(vm, self, "width;", args[2]);
    setObjProperty(vm, self, "height;", args[3]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Image
LOX_METHOD(Image, __init__) {
    if (argCount != 4) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "width;", args[0]);
    setObjProperty(vm, self, "height;", args[1]);
    setObjProperty(vm, self, "mipmaps;", args[2]);
    setObjProperty(vm, self, "format;", args[3]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Texture2D
LOX_METHOD(Texture2D, __init__) {
    if (argCount != 5) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "id;", args[0]);
    setObjProperty(vm, self, "width;", args[1]);
    setObjProperty(vm, self, "height;", args[2]);
    setObjProperty(vm, self, "mipmaps;", args[3]);
    setObjProperty(vm, self, "format;", args[4]);
    RETURN_VAL(receiver);
}

// Lox class for: struct RenderTexture2D
LOX_METHOD(RenderTexture2D, __init__) {
    if (argCount != 4) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "id;", args[0]);
    setObjProperty(vm, self, "texture;", args[1]);
    setObjProperty(vm, self, "depth;", args[2]);
    setObjProperty(vm, self, "depthTexture;", args[3]);
    RETURN_VAL(receiver);
}

// Lox class for: struct NPatchInfo
LOX_METHOD(NPatchInfo, __init__) {
    if (argCount != 6) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "sourceRec;", args[0]);
    setObjProperty(vm, self, "left;", args[1]);
    setObjProperty(vm, self, "top;", args[2]);
    setObjProperty(vm, self, "right;", args[3]);
    setObjProperty(vm, self, "bottom;", args[4]);
    setObjProperty(vm, self, "type;", args[5]);
    RETURN_VAL(receiver);
}

// Lox class for: struct CharInfo
LOX_METHOD(CharInfo, __init__) {
    if (argCount != 5) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "value;", args[0]);
    setObjProperty(vm, self, "rec;", args[1]);
    setObjProperty(vm, self, "offsetX;", args[2]);
    setObjProperty(vm, self, "offsetY;", args[3]);
    setObjProperty(vm, self, "advanceX;", args[4]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Font
LOX_METHOD(Font, __init__) {
    if (argCount != 3) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "texture;", args[0]);
    setObjProperty(vm, self, "baseSize;", args[1]);
    setObjProperty(vm, self, "charsCount;", args[2]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Camera3D
LOX_METHOD(Camera3D, __init__) {
    if (argCount != 5) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "position;", args[0]);
    setObjProperty(vm, self, "target;", args[1]);
    setObjProperty(vm, self, "up;", args[2]);
    setObjProperty(vm, self, "fovy;", args[3]);
    setObjProperty(vm, self, "type;", args[4]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Camera2D
LOX_METHOD(Camera2D, __init__) {
    if (argCount != 4) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "offset;", args[0]);
    setObjProperty(vm, self, "target;", args[1]);
    setObjProperty(vm, self, "rotation;", args[2]);
    setObjProperty(vm, self, "zoom;", args[3]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Mesh
LOX_METHOD(Mesh, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct Shader
LOX_METHOD(Shader, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct MaterialMap
LOX_METHOD(MaterialMap, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct Material
LOX_METHOD(Material, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct Model
LOX_METHOD(Model, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct Transform
LOX_METHOD(Transform, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct BoneInfo
LOX_METHOD(BoneInfo, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct ModelAnimation
LOX_METHOD(ModelAnimation, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct Ray
LOX_METHOD(Ray, __init__) {
    if (argCount != 2) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "position;", args[0]);
    setObjProperty(vm, self, "direction;", args[1]);
    RETURN_VAL(receiver);
}

// Lox class for: struct RayHitInfo
LOX_METHOD(RayHitInfo, __init__) {
    if (argCount != 4) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "hit;", args[0]);
    setObjProperty(vm, self, "distance;", args[1]);
    setObjProperty(vm, self, "position;", args[2]);
    setObjProperty(vm, self, "normal;", args[3]);
    RETURN_VAL(receiver);
}

// Lox class for: struct BoundingBox
LOX_METHOD(BoundingBox, __init__) {
    if (argCount != 2) { /* TODO: Error handling */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm, self, "min;", args[0]);
    setObjProperty(vm, self, "max;", args[1]);
    RETURN_VAL(receiver);
}

// Lox class for: struct Wave
LOX_METHOD(Wave, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct Sound
LOX_METHOD(Sound, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct Music
LOX_METHOD(Music, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct AudioStream
LOX_METHOD(AudioStream, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox class for: struct VrDeviceInfo
LOX_METHOD(VrDeviceInfo, __init__) {
    if (argCount != 0) { /* TODO: Error handling */ RETURN_NIL; }
    RETURN_VAL(receiver);
}

// Lox function for: void InitWindow(int width, int height, const char* title);
LOX_FUNCTION(InitWindow) {
    if (argCount != 3) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);
    const char* title = AS_CSTRING(args[2]);

    InitWindow(width, height, title);

    RETURN_NIL;
}

// Lox function for: bool WindowShouldClose(void);
LOX_FUNCTION(WindowShouldClose) {
    if (argCount != 0) { RETURN_NIL; }

    bool result = (bool)WindowShouldClose();

    RETURN_BOOL(result);
}

// Lox function for: void CloseWindow(void);
LOX_FUNCTION(CloseWindow) {
    if (argCount != 0) { RETURN_NIL; }

    CloseWindow();

    RETURN_NIL;
}

// Lox function for: bool IsWindowReady(void);
LOX_FUNCTION(IsWindowReady) {
    if (argCount != 0) { RETURN_NIL; }

    bool result = (bool)IsWindowReady();

    RETURN_BOOL(result);
}

// Lox function for: bool IsWindowMinimized(void);
LOX_FUNCTION(IsWindowMinimized) {
    if (argCount != 0) { RETURN_NIL; }

    bool result = (bool)IsWindowMinimized();

    RETURN_BOOL(result);
}

// Lox function for: bool IsWindowResized(void);
LOX_FUNCTION(IsWindowResized) {
    if (argCount != 0) { RETURN_NIL; }

    bool result = (bool)IsWindowResized();

    RETURN_BOOL(result);
}

// Lox function for: bool IsWindowHidden(void);
LOX_FUNCTION(IsWindowHidden) {
    if (argCount != 0) { RETURN_NIL; }

    bool result = (bool)IsWindowHidden();

    RETURN_BOOL(result);
}

// Lox function for: void ToggleFullscreen(void);
LOX_FUNCTION(ToggleFullscreen) {
    if (argCount != 0) { RETURN_NIL; }

    ToggleFullscreen();

    RETURN_NIL;
}

// Lox function for: void UnhideWindow(void);
LOX_FUNCTION(UnhideWindow) {
    if (argCount != 0) { RETURN_NIL; }

    UnhideWindow();

    RETURN_NIL;
}

// Lox function for: void HideWindow(void);
LOX_FUNCTION(HideWindow) {
    if (argCount != 0) { RETURN_NIL; }

    HideWindow();

    RETURN_NIL;
}

// Lox function for: void SetWindowIcon(Image image);
LOX_FUNCTION(SetWindowIcon) {
    if (argCount != 1) { RETURN_NIL; }
    Image image = loxToImage(vm, args[0]);

    SetWindowIcon(image);

    RETURN_NIL;
}

// Lox function for: void SetWindowTitle(const char* title);
LOX_FUNCTION(SetWindowTitle) {
    if (argCount != 1) { RETURN_NIL; }
    const char* title = AS_CSTRING(args[0]);

    SetWindowTitle(title);

    RETURN_NIL;
}

// Lox function for: void SetWindowPosition(int x, int y);
LOX_FUNCTION(SetWindowPosition) {
    if (argCount != 2) { RETURN_NIL; }
    int x = (int)AS_NUMBER(args[0]);
    int y = (int)AS_NUMBER(args[1]);

    SetWindowPosition(x, y);

    RETURN_NIL;
}

// Lox function for: void SetWindowMonitor(int monitor);
LOX_FUNCTION(SetWindowMonitor) {
    if (argCount != 1) { RETURN_NIL; }
    int monitor = (int)AS_NUMBER(args[0]);

    SetWindowMonitor(monitor);

    RETURN_NIL;
}

// Lox function for: void SetWindowMinSize(int width, int height);
LOX_FUNCTION(SetWindowMinSize) {
    if (argCount != 2) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);

    SetWindowMinSize(width, height);

    RETURN_NIL;
}

// Lox function for: void SetWindowSize(int width, int height);
LOX_FUNCTION(SetWindowSize) {
    if (argCount != 2) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);

    SetWindowSize(width, height);

    RETURN_NIL;
}

// Lox function for: int GetScreenWidth(void);
LOX_FUNCTION(GetScreenWidth) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetScreenWidth();

    RETURN_NUMBER(result);
}

// Lox function for: int GetScreenHeight(void);
LOX_FUNCTION(GetScreenHeight) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetScreenHeight();

    RETURN_NUMBER(result);
}

// Lox function for: int GetMonitorCount(void);
LOX_FUNCTION(GetMonitorCount) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetMonitorCount();

    RETURN_NUMBER(result);
}

// Lox function for: int GetMonitorWidth(int monitor);
LOX_FUNCTION(GetMonitorWidth) {
    if (argCount != 1) { RETURN_NIL; }
    int monitor = (int)AS_NUMBER(args[0]);

    int result = (int)GetMonitorWidth(monitor);

    RETURN_NUMBER(result);
}

// Lox function for: int GetMonitorHeight(int monitor);
LOX_FUNCTION(GetMonitorHeight) {
    if (argCount != 1) { RETURN_NIL; }
    int monitor = (int)AS_NUMBER(args[0]);

    int result = (int)GetMonitorHeight(monitor);

    RETURN_NUMBER(result);
}

// Lox function for: int GetMonitorPhysicalWidth(int monitor);
LOX_FUNCTION(GetMonitorPhysicalWidth) {
    if (argCount != 1) { RETURN_NIL; }
    int monitor = (int)AS_NUMBER(args[0]);

    int result = (int)GetMonitorPhysicalWidth(monitor);

    RETURN_NUMBER(result);
}

// Lox function for: int GetMonitorPhysicalHeight(int monitor);
LOX_FUNCTION(GetMonitorPhysicalHeight) {
    if (argCount != 1) { RETURN_NIL; }
    int monitor = (int)AS_NUMBER(args[0]);

    int result = (int)GetMonitorPhysicalHeight(monitor);

    RETURN_NUMBER(result);
}

// Lox function for: const char* GetMonitorName(int monitor);
LOX_FUNCTION(GetMonitorName) {
    if (argCount != 1) { RETURN_NIL; }
    int monitor = (int)AS_NUMBER(args[0]);

    const char* result = (const char*)GetMonitorName(monitor);

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: const char* GetClipboardText(void);
LOX_FUNCTION(GetClipboardText) {
    if (argCount != 0) { RETURN_NIL; }

    const char* result = (const char*)GetClipboardText();

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: void SetClipboardText(const char* text);
LOX_FUNCTION(SetClipboardText) {
    if (argCount != 1) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);

    SetClipboardText(text);

    RETURN_NIL;
}

// Lox function for: void ShowCursor(void);
LOX_FUNCTION(ShowCursor) {
    if (argCount != 0) { RETURN_NIL; }

    ShowCursor();

    RETURN_NIL;
}

// Lox function for: void HideCursor(void);
LOX_FUNCTION(HideCursor) {
    if (argCount != 0) { RETURN_NIL; }

    HideCursor();

    RETURN_NIL;
}

// Lox function for: bool IsCursorHidden(void);
LOX_FUNCTION(IsCursorHidden) {
    if (argCount != 0) { RETURN_NIL; }

    bool result = (bool)IsCursorHidden();

    RETURN_BOOL(result);
}

// Lox function for: void EnableCursor(void);
LOX_FUNCTION(EnableCursor) {
    if (argCount != 0) { RETURN_NIL; }

    EnableCursor();

    RETURN_NIL;
}

// Lox function for: void DisableCursor(void);
LOX_FUNCTION(DisableCursor) {
    if (argCount != 0) { RETURN_NIL; }

    DisableCursor();

    RETURN_NIL;
}

// Lox function for: void ClearBackground(Color color);
LOX_FUNCTION(ClearBackground) {
    if (argCount != 1) { RETURN_NIL; }
    Color color = loxToColor(vm, args[0]);

    ClearBackground(color);

    RETURN_NIL;
}

// Lox function for: void BeginDrawing(void);
LOX_FUNCTION(BeginDrawing) {
    if (argCount != 0) { RETURN_NIL; }

    BeginDrawing();

    RETURN_NIL;
}

// Lox function for: void EndDrawing(void);
LOX_FUNCTION(EndDrawing) {
    if (argCount != 0) { RETURN_NIL; }

    EndDrawing();

    RETURN_NIL;
}

// Lox function for: void BeginMode2D(Camera2D camera);
LOX_FUNCTION(BeginMode2D) {
    if (argCount != 1) { RETURN_NIL; }
    Camera2D camera = loxToCamera2D(vm, args[0]);

    BeginMode2D(camera);

    RETURN_NIL;
}

// Lox function for: void EndMode2D(void);
LOX_FUNCTION(EndMode2D) {
    if (argCount != 0) { RETURN_NIL; }

    EndMode2D();

    RETURN_NIL;
}

// Lox function for: void BeginMode3D(Camera3D camera);
LOX_FUNCTION(BeginMode3D) {
    if (argCount != 1) { RETURN_NIL; }
    Camera3D camera = loxToCamera3D(vm, args[0]);

    BeginMode3D(camera);

    RETURN_NIL;
}

// Lox function for: void EndMode3D(void);
LOX_FUNCTION(EndMode3D) {
    if (argCount != 0) { RETURN_NIL; }

    EndMode3D();

    RETURN_NIL;
}

// Lox function for: void BeginTextureMode(RenderTexture2D target);
LOX_FUNCTION(BeginTextureMode) {
    if (argCount != 1) { RETURN_NIL; }
    RenderTexture2D target = loxToRenderTexture2D(vm, args[0]);

    BeginTextureMode(target);

    RETURN_NIL;
}

// Lox function for: void EndTextureMode(void);
LOX_FUNCTION(EndTextureMode) {
    if (argCount != 0) { RETURN_NIL; }

    EndTextureMode();

    RETURN_NIL;
}

// Lox function for: Ray GetMouseRay(Vector2 mousePosition, Camera3D camera);
LOX_FUNCTION(GetMouseRay) {
    if (argCount != 2) { RETURN_NIL; }
    Vector2 mousePosition = loxToVector2(vm, args[0]);
    Camera3D camera = loxToCamera3D(vm, args[1]);

    Ray result = (Ray)GetMouseRay(mousePosition, camera);

    RETURN_VAL(cToLoxRay(vm, result));
}

// Lox function for: Vector2 GetWorldToScreen(Vector3 position, Camera3D camera);
LOX_FUNCTION(GetWorldToScreen) {
    if (argCount != 2) { RETURN_NIL; }
    Vector3 position = loxToVector3(vm, args[0]);
    Camera3D camera = loxToCamera3D(vm, args[1]);

    Vector2 result = GetWorldToScreen(position, camera);

    RETURN_VAL(cToLoxVector2(vm, result));
}

// Lox function for: Matrix GetCameraMatrix(Camera3D camera);
LOX_FUNCTION(GetCameraMatrix) {
    if (argCount != 1) { RETURN_NIL; }
    Camera3D camera = loxToCamera3D(vm, args[0]);

    Matrix result = (Matrix)GetCameraMatrix(camera);

    RETURN_VAL(cToLoxMatrix(vm, result));
}

// Lox function for: void SetTargetFPS(int fps);
LOX_FUNCTION(SetTargetFPS) {
    if (argCount != 1) { RETURN_NIL; }
    int fps = (int)AS_NUMBER(args[0]);

    SetTargetFPS(fps);

    RETURN_NIL;
}

// Lox function for: int GetFPS(void);
LOX_FUNCTION(GetFPS) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetFPS();

    RETURN_NUMBER(result);
}

// Lox function for: float GetFrameTime(void);
LOX_FUNCTION(GetFrameTime) {
    if (argCount != 0) { RETURN_NIL; }

    float result = (float)GetFrameTime();

    RETURN_NUMBER(result);
}

// Lox function for: float GetTime(void);
LOX_FUNCTION(GetTime) {
    if (argCount != 0) { RETURN_NIL; }

    float result = (float)GetTime();

    RETURN_NUMBER(result);
}

// Lox function for: int ColorToInt(Color color);
LOX_FUNCTION(ColorToInt) {
    if (argCount != 1) { RETURN_NIL; }
    Color color = loxToColor(vm, args[0]);

    int result = (int)ColorToInt(color);

    RETURN_NUMBER(result);
}

// Lox function for: Vector4 ColorNormalize(Color color);
LOX_FUNCTION(ColorNormalize) {
    if (argCount != 1) { RETURN_NIL; }
    Color color = loxToColor(vm, args[0]);

    Vector4 result = (Vector4)ColorNormalize(color);

    RETURN_VAL(cToLoxVector4(vm, result));
}

// Lox function for: Vector3 ColorToHSV(Color color);
LOX_FUNCTION(ColorToHSV) {
    if (argCount != 1) { RETURN_NIL; }
    Color color = loxToColor(vm, args[0]);

    Vector3 result = (Vector3)ColorToHSV(color);

    RETURN_VAL(cToLoxVector3(vm, result));
}

// Lox function for: Color ColorFromHSV((float hue, float saturation, float value);
LOX_FUNCTION(ColorFromHSV) {
    if (argCount != 3) { RETURN_NIL; }
    (float hue = loxTofloat(vm, args[0]);
    float saturation = (float)AS_NUMBER(args[1]);
    float value = (float)AS_NUMBER(args[2]);

    Color result = (Color)ColorFromHSV(hue, saturation, value);

    RETURN_VAL(cToLoxColor(vm, result));
}

// Lox function for: Color GetColor(int hexValue);
LOX_FUNCTION(GetColor) {
    if (argCount != 1) { RETURN_NIL; }
    int hexValue = (int)AS_NUMBER(args[0]);

    Color result = (Color)GetColor(hexValue);

    RETURN_VAL(cToLoxColor(vm, result));
}

// Lox function for: Color Fade(Color color, float alpha);
LOX_FUNCTION(Fade) {
    if (argCount != 2) { RETURN_NIL; }
    Color color = loxToColor(vm, args[0]);
    float alpha = (float)AS_NUMBER(args[1]);

    Color result = (Color)Fade(color, alpha);

    RETURN_VAL(cToLoxColor(vm, result));
}

// Lox function for: void SetConfigFlags(unsigned char flags);
LOX_FUNCTION(SetConfigFlags) {
    if (argCount != 1) { RETURN_NIL; }
    unsigned char flags = (unsigned char)AS_NUMBER(args[0]);

    SetConfigFlags(flags);

    RETURN_NIL;
}

// Lox function for: void SetTraceLogLevel(int logType);
LOX_FUNCTION(SetTraceLogLevel) {
    if (argCount != 1) { RETURN_NIL; }
    int logType = (int)AS_NUMBER(args[0]);

    SetTraceLogLevel(logType);

    RETURN_NIL;
}

// Lox function for: void SetTraceLogExit(int logType);
LOX_FUNCTION(SetTraceLogExit) {
    if (argCount != 1) { RETURN_NIL; }
    int logType = (int)AS_NUMBER(args[0]);

    SetTraceLogExit(logType);

    RETURN_NIL;
}

// Lox function for: void TakeScreenshot(const char* fileName);
LOX_FUNCTION(TakeScreenshot) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    TakeScreenshot(fileName);

    RETURN_NIL;
}

// Lox function for: int GetRandomValue(int min, int max);
LOX_FUNCTION(GetRandomValue) {
    if (argCount != 2) { RETURN_NIL; }
    int min = (int)AS_NUMBER(args[0]);
    int max = (int)AS_NUMBER(args[1]);

    int result = (int)GetRandomValue(min, max);

    RETURN_NUMBER(result);
}

// Lox function for: bool FileExists(const char* fileName);
LOX_FUNCTION(FileExists) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    bool result = (bool)FileExists(fileName);

    RETURN_BOOL(result);
}

// Lox function for: bool IsFileExtension(const char* fileName, const char* ext);
LOX_FUNCTION(IsFileExtension) {
    if (argCount != 2) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);
    const char* ext = AS_CSTRING(args[1]);

    bool result = (bool)IsFileExtension(fileName, ext);

    RETURN_BOOL(result);
}

// Lox function for: const char* GetExtension(const char* fileName);
LOX_FUNCTION(GetExtension) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    const char* result = (const char*)GetExtension(fileName);

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: const char* GetFileName(const char* filePath);
LOX_FUNCTION(GetFileName) {
    if (argCount != 1) { RETURN_NIL; }
    const char* filePath = AS_CSTRING(args[0]);

    const char* result = (const char*)GetFileName(filePath);

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: const char* GetFileNameWithoutExt(const char* filePath);
LOX_FUNCTION(GetFileNameWithoutExt) {
    if (argCount != 1) { RETURN_NIL; }
    const char* filePath = AS_CSTRING(args[0]);

    const char* result = (const char*)GetFileNameWithoutExt(filePath);

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: const char* GetDirectoryPath(const char* fileName);
LOX_FUNCTION(GetDirectoryPath) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    const char* result = (const char*)GetDirectoryPath(fileName);

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: const char* GetWorkingDirectory(void);
LOX_FUNCTION(GetWorkingDirectory) {
    if (argCount != 0) { RETURN_NIL; }

    const char* result = (const char*)GetWorkingDirectory();

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: void ClearDirectoryFiles(void);
LOX_FUNCTION(ClearDirectoryFiles) {
    if (argCount != 0) { RETURN_NIL; }

    ClearDirectoryFiles();

    RETURN_NIL;
}

// Lox function for: bool ChangeDirectory(const char* dir);
LOX_FUNCTION(ChangeDirectory) {
    if (argCount != 1) { RETURN_NIL; }
    const char* dir = AS_CSTRING(args[0]);

    bool result = (bool)ChangeDirectory(dir);

    RETURN_BOOL(result);
}

// Lox function for: bool IsFileDropped(void);
LOX_FUNCTION(IsFileDropped) {
    if (argCount != 0) { RETURN_NIL; }

    bool result = (bool)IsFileDropped();

    RETURN_BOOL(result);
}

// Lox function for: void ClearDroppedFiles(void);
LOX_FUNCTION(ClearDroppedFiles) {
    if (argCount != 0) { RETURN_NIL; }

    ClearDroppedFiles();

    RETURN_NIL;
}

// Lox function for: void StorageSaveValue(int position, int value);
LOX_FUNCTION(StorageSaveValue) {
    if (argCount != 2) { RETURN_NIL; }
    int position = (int)AS_NUMBER(args[0]);
    int value = (int)AS_NUMBER(args[1]);

    StorageSaveValue(position, value);

    RETURN_NIL;
}

// Lox function for: int StorageLoadValue(int position);
LOX_FUNCTION(StorageLoadValue) {
    if (argCount != 1) { RETURN_NIL; }
    int position = (int)AS_NUMBER(args[0]);

    int result = (int)StorageLoadValue(position);

    RETURN_NUMBER(result);
}

// Lox function for: void OpenURL(const char* url);
LOX_FUNCTION(OpenURL) {
    if (argCount != 1) { RETURN_NIL; }
    const char* url = AS_CSTRING(args[0]);

    OpenURL(url);

    RETURN_NIL;
}

// Lox function for: bool IsKeyPressed(int key);
LOX_FUNCTION(IsKeyPressed) {
    if (argCount != 1) { RETURN_NIL; }
    int key = (int)AS_NUMBER(args[0]);

    bool result = (bool)IsKeyPressed(key);

    RETURN_BOOL(result);
}

// Lox function for: bool IsKeyDown(int key);
LOX_FUNCTION(IsKeyDown) {
    if (argCount != 1) { RETURN_NIL; }
    int key = (int)AS_NUMBER(args[0]);

    bool result = (bool)IsKeyDown(key);

    RETURN_BOOL(result);
}

// Lox function for: bool IsKeyReleased(int key);
LOX_FUNCTION(IsKeyReleased) {
    if (argCount != 1) { RETURN_NIL; }
    int key = (int)AS_NUMBER(args[0]);

    bool result = (bool)IsKeyReleased(key);

    RETURN_BOOL(result);
}

// Lox function for: bool IsKeyUp(int key);
LOX_FUNCTION(IsKeyUp) {
    if (argCount != 1) { RETURN_NIL; }
    int key = (int)AS_NUMBER(args[0]);

    bool result = (bool)IsKeyUp(key);

    RETURN_BOOL(result);
}

// Lox function for: int GetKeyPressed(void);
LOX_FUNCTION(GetKeyPressed) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetKeyPressed();

    RETURN_NUMBER(result);
}

// Lox function for: void SetExitKey(int key);
LOX_FUNCTION(SetExitKey) {
    if (argCount != 1) { RETURN_NIL; }
    int key = (int)AS_NUMBER(args[0]);

    SetExitKey(key);

    RETURN_NIL;
}

// Lox function for: bool IsGamepadAvailable(int gamepad);
LOX_FUNCTION(IsGamepadAvailable) {
    if (argCount != 1) { RETURN_NIL; }
    int gamepad = (int)AS_NUMBER(args[0]);

    bool result = (bool)IsGamepadAvailable(gamepad);

    RETURN_BOOL(result);
}

// Lox function for: bool IsGamepadName(int gamepad, const char* name);
LOX_FUNCTION(IsGamepadName) {
    if (argCount != 2) { RETURN_NIL; }
    int gamepad = (int)AS_NUMBER(args[0]);
    const char* name = AS_CSTRING(args[1]);

    bool result = (bool)IsGamepadName(gamepad, name);

    RETURN_BOOL(result);
}

// Lox function for: const char* GetGamepadName(int gamepad);
LOX_FUNCTION(GetGamepadName) {
    if (argCount != 1) { RETURN_NIL; }
    int gamepad = (int)AS_NUMBER(args[0]);

    const char* result = (const char*)GetGamepadName(gamepad);

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: bool IsGamepadButtonPressed(int gamepad, int button);
LOX_FUNCTION(IsGamepadButtonPressed) {
    if (argCount != 2) { RETURN_NIL; }
    int gamepad = (int)AS_NUMBER(args[0]);
    int button = (int)AS_NUMBER(args[1]);

    bool result = (bool)IsGamepadButtonPressed(gamepad, button);

    RETURN_BOOL(result);
}

// Lox function for: bool IsGamepadButtonDown(int gamepad, int button);
LOX_FUNCTION(IsGamepadButtonDown) {
    if (argCount != 2) { RETURN_NIL; }
    int gamepad = (int)AS_NUMBER(args[0]);
    int button = (int)AS_NUMBER(args[1]);

    bool result = (bool)IsGamepadButtonDown(gamepad, button);

    RETURN_BOOL(result);
}

// Lox function for: bool IsGamepadButtonReleased(int gamepad, int button);
LOX_FUNCTION(IsGamepadButtonReleased) {
    if (argCount != 2) { RETURN_NIL; }
    int gamepad = (int)AS_NUMBER(args[0]);
    int button = (int)AS_NUMBER(args[1]);

    bool result = (bool)IsGamepadButtonReleased(gamepad, button);

    RETURN_BOOL(result);
}

// Lox function for: bool IsGamepadButtonUp(int gamepad, int button);
LOX_FUNCTION(IsGamepadButtonUp) {
    if (argCount != 2) { RETURN_NIL; }
    int gamepad = (int)AS_NUMBER(args[0]);
    int button = (int)AS_NUMBER(args[1]);

    bool result = (bool)IsGamepadButtonUp(gamepad, button);

    RETURN_BOOL(result);
}

// Lox function for: int GetGamepadButtonPressed(void);
LOX_FUNCTION(GetGamepadButtonPressed) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetGamepadButtonPressed();

    RETURN_NUMBER(result);
}

// Lox function for: int GetGamepadAxisCount(int gamepad);
LOX_FUNCTION(GetGamepadAxisCount) {
    if (argCount != 1) { RETURN_NIL; }
    int gamepad = (int)AS_NUMBER(args[0]);

    int result = (int)GetGamepadAxisCount(gamepad);

    RETURN_NUMBER(result);
}

// Lox function for: float GetGamepadAxisMovement(int gamepad, int axis);
LOX_FUNCTION(GetGamepadAxisMovement) {
    if (argCount != 2) { RETURN_NIL; }
    int gamepad = (int)AS_NUMBER(args[0]);
    int axis = (int)AS_NUMBER(args[1]);

    float result = (float)GetGamepadAxisMovement(gamepad, axis);

    RETURN_NUMBER(result);
}

// Lox function for: bool IsMouseButtonPressed(int button);
LOX_FUNCTION(IsMouseButtonPressed) {
    if (argCount != 1) { RETURN_NIL; }
    int button = (int)AS_NUMBER(args[0]);

    bool result = (bool)IsMouseButtonPressed(button);

    RETURN_BOOL(result);
}

// Lox function for: bool IsMouseButtonDown(int button);
LOX_FUNCTION(IsMouseButtonDown) {
    if (argCount != 1) { RETURN_NIL; }
    int button = (int)AS_NUMBER(args[0]);

    bool result = (bool)IsMouseButtonDown(button);

    RETURN_BOOL(result);
}

// Lox function for: bool IsMouseButtonReleased(int button);
LOX_FUNCTION(IsMouseButtonReleased) {
    if (argCount != 1) { RETURN_NIL; }
    int button = (int)AS_NUMBER(args[0]);

    bool result = (bool)IsMouseButtonReleased(button);

    RETURN_BOOL(result);
}

// Lox function for: bool IsMouseButtonUp(int button);
LOX_FUNCTION(IsMouseButtonUp) {
    if (argCount != 1) { RETURN_NIL; }
    int button = (int)AS_NUMBER(args[0]);

    bool result = (bool)IsMouseButtonUp(button);

    RETURN_BOOL(result);
}

// Lox function for: int GetMouseX(void);
LOX_FUNCTION(GetMouseX) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetMouseX();

    RETURN_NUMBER(result);
}

// Lox function for: int GetMouseY(void);
LOX_FUNCTION(GetMouseY) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetMouseY();

    RETURN_NUMBER(result);
}

// Lox function for: Vector2 GetMousePosition(void);
LOX_FUNCTION(GetMousePosition) {
    if (argCount != 0) { RETURN_NIL; }

    Vector2 result = (Vector2)GetMousePosition();

    RETURN_VAL(cToLoxVector2(vm, result));
}

// Lox function for: void SetMousePosition(int x, int y);
LOX_FUNCTION(SetMousePosition) {
    if (argCount != 2) { RETURN_NIL; }
    int x = (int)AS_NUMBER(args[0]);
    int y = (int)AS_NUMBER(args[1]);

    SetMousePosition(x, y);

    RETURN_NIL;
}

// Lox function for: void SetMouseOffset(int offsetX, int offsetY);
LOX_FUNCTION(SetMouseOffset) {
    if (argCount != 2) { RETURN_NIL; }
    int offsetX = (int)AS_NUMBER(args[0]);
    int offsetY = (int)AS_NUMBER(args[1]);

    SetMouseOffset(offsetX, offsetY);

    RETURN_NIL;
}

// Lox function for: void SetMouseScale(float scaleX, float scaleY);
LOX_FUNCTION(SetMouseScale) {
    if (argCount != 2) { RETURN_NIL; }
    float scaleX = (float)AS_NUMBER(args[0]);
    float scaleY = (float)AS_NUMBER(args[1]);

    SetMouseScale(scaleX, scaleY);

    RETURN_NIL;
}

// Lox function for: int GetMouseWheelMove(void);
LOX_FUNCTION(GetMouseWheelMove) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetMouseWheelMove();

    RETURN_NUMBER(result);
}

// Lox function for: int GetTouchX(void);
LOX_FUNCTION(GetTouchX) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetTouchX();

    RETURN_NUMBER(result);
}

// Lox function for: int GetTouchY(void);
LOX_FUNCTION(GetTouchY) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetTouchY();

    RETURN_NUMBER(result);
}

// Lox function for: Vector2 GetTouchPosition(int index);
LOX_FUNCTION(GetTouchPosition) {
    if (argCount != 1) { RETURN_NIL; }
    int index = (int)AS_NUMBER(args[0]);

    Vector2 result = (Vector2)GetTouchPosition(index);

    RETURN_VAL(cToLoxVector2(vm, result));
}

// Lox function for: void SetGesturesEnabled(unsigned int gestureFlags);
LOX_FUNCTION(SetGesturesEnabled) {
    if (argCount != 1) { RETURN_NIL; }
    unsigned int gestureFlags = (unsigned int)AS_NUMBER(args[0]);

    SetGesturesEnabled(gestureFlags);

    RETURN_NIL;
}

// Lox function for: bool IsGestureDetected(int gesture);
LOX_FUNCTION(IsGestureDetected) {
    if (argCount != 1) { RETURN_NIL; }
    int gesture = (int)AS_NUMBER(args[0]);

    bool result = (bool)IsGestureDetected(gesture);

    RETURN_BOOL(result);
}

// Lox function for: int GetGestureDetected(void);
LOX_FUNCTION(GetGestureDetected) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetGestureDetected();

    RETURN_NUMBER(result);
}

// Lox function for: int GetTouchPointsCount(void);
LOX_FUNCTION(GetTouchPointsCount) {
    if (argCount != 0) { RETURN_NIL; }

    int result = (int)GetTouchPointsCount();

    RETURN_NUMBER(result);
}

// Lox function for: float GetGestureHoldDuration(void);
LOX_FUNCTION(GetGestureHoldDuration) {
    if (argCount != 0) { RETURN_NIL; }

    float result = (float)GetGestureHoldDuration();

    RETURN_NUMBER(result);
}

// Lox function for: Vector2 GetGestureDragVector(void);
LOX_FUNCTION(GetGestureDragVector) {
    if (argCount != 0) { RETURN_NIL; }

    Vector2 result = (Vector2)GetGestureDragVector();

    RETURN_VAL(cToLoxVector2(vm, result));
}

// Lox function for: float GetGestureDragAngle(void);
LOX_FUNCTION(GetGestureDragAngle) {
    if (argCount != 0) { RETURN_NIL; }

    float result = (float)GetGestureDragAngle();

    RETURN_NUMBER(result);
}

// Lox function for: Vector2 GetGesturePinchVector(void);
LOX_FUNCTION(GetGesturePinchVector) {
    if (argCount != 0) { RETURN_NIL; }

    Vector2 result = (Vector2)GetGesturePinchVector();

    RETURN_VAL(cToLoxVector2(vm, result));
}

// Lox function for: float GetGesturePinchAngle(void);
LOX_FUNCTION(GetGesturePinchAngle) {
    if (argCount != 0) { RETURN_NIL; }

    float result = (float)GetGesturePinchAngle();

    RETURN_NUMBER(result);
}

// Lox function for: void SetCameraMode(Camera3D camera, int mode);
LOX_FUNCTION(SetCameraMode) {
    if (argCount != 2) { RETURN_NIL; }
    Camera3D camera = loxToCamera3D(vm, args[0]);
    int mode = (int)AS_NUMBER(args[1]);

    SetCameraMode(camera, mode);

    RETURN_NIL;
}

// Lox function for: void UpdateCamera(Camera3D* camera);
LOX_FUNCTION(UpdateCamera) {
    if (argCount != 1) { RETURN_NIL; }
    Camera3D* camera = loxToCamera3D(vm, args[0]);

    UpdateCamera(camera);

    RETURN_NIL;
}

// Lox function for: void SetCameraPanControl(int panKey);
LOX_FUNCTION(SetCameraPanControl) {
    if (argCount != 1) { RETURN_NIL; }
    int panKey = (int)AS_NUMBER(args[0]);

    SetCameraPanControl(panKey);

    RETURN_NIL;
}

// Lox function for: void SetCameraAltControl(int altKey);
LOX_FUNCTION(SetCameraAltControl) {
    if (argCount != 1) { RETURN_NIL; }
    int altKey = (int)AS_NUMBER(args[0]);

    SetCameraAltControl(altKey);

    RETURN_NIL;
}

// Lox function for: void SetCameraSmoothZoomControl(int szKey);
LOX_FUNCTION(SetCameraSmoothZoomControl) {
    if (argCount != 1) { RETURN_NIL; }
    int szKey = (int)AS_NUMBER(args[0]);

    SetCameraSmoothZoomControl(szKey);

    RETURN_NIL;
}

// Lox function for: void SetCameraMoveControls(int frontKey, int backKey, int rightKey, int leftKey, int upKey, int downKey);
LOX_FUNCTION(SetCameraMoveControls) {
    if (argCount != 6) { RETURN_NIL; }
    int frontKey = (int)AS_NUMBER(args[0]);
    int backKey = (int)AS_NUMBER(args[1]);
    int rightKey = (int)AS_NUMBER(args[2]);
    int leftKey = (int)AS_NUMBER(args[3]);
    int upKey = (int)AS_NUMBER(args[4]);
    int downKey = (int)AS_NUMBER(args[5]);

    SetCameraMoveControls(frontKey, backKey, rightKey, leftKey, upKey, downKey);

    RETURN_NIL;
}

// Lox function for: void DrawPixel(int posX, int posY, Color color);
LOX_FUNCTION(DrawPixel) {
    if (argCount != 3) { RETURN_NIL; }
    int posX = (int)AS_NUMBER(args[0]);
    int posY = (int)AS_NUMBER(args[1]);
    Color color = loxToColor(vm, args[2]);

    DrawPixel(posX, posY, color);

    RETURN_NIL;
}

// Lox function for: void DrawPixelV(Vector2 position, Color color);
LOX_FUNCTION(DrawPixelV) {
    if (argCount != 2) { RETURN_NIL; }
    Vector2 position = loxToVector2(vm, args[0]);
    Color color = loxToColor(vm, args[1]);

    DrawPixelV(position, color);

    RETURN_NIL;
}

// Lox function for: void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);
LOX_FUNCTION(DrawLine) {
    if (argCount != 5) { RETURN_NIL; }
    int startPosX = (int)AS_NUMBER(args[0]);
    int startPosY = (int)AS_NUMBER(args[1]);
    int endPosX = (int)AS_NUMBER(args[2]);
    int endPosY = (int)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawLine(startPosX, startPosY, endPosX, endPosY, color);

    RETURN_NIL;
}

// Lox function for: void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);
LOX_FUNCTION(DrawLineV) {
    if (argCount != 3) { RETURN_NIL; }
    Vector2 startPos = loxToVector2(vm, args[0]);
    Vector2 endPos = loxToVector2(vm, args[1]);
    Color color = loxToColor(vm, args[2]);

    DrawLineV(startPos, endPos, color);

    RETURN_NIL;
}

// Lox function for: void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);
LOX_FUNCTION(DrawLineEx) {
    if (argCount != 4) { RETURN_NIL; }
    Vector2 startPos = loxToVector2(vm, args[0]);
    Vector2 endPos = loxToVector2(vm, args[1]);
    float thick = (float)AS_NUMBER(args[2]);
    Color color = loxToColor(vm, args[3]);

    DrawLineEx(startPos, endPos, thick, color);

    RETURN_NIL;
}

// Lox function for: void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);
LOX_FUNCTION(DrawLineBezier) {
    if (argCount != 4) { RETURN_NIL; }
    Vector2 startPos = loxToVector2(vm, args[0]);
    Vector2 endPos = loxToVector2(vm, args[1]);
    float thick = (float)AS_NUMBER(args[2]);
    Color color = loxToColor(vm, args[3]);

    DrawLineBezier(startPos, endPos, thick, color);

    RETURN_NIL;
}

// Lox function for: void DrawCircle(int centerX, int centerY, float radius, Color color);
LOX_FUNCTION(DrawCircle) {
    if (argCount != 4) { RETURN_NIL; }
    int centerX = (int)AS_NUMBER(args[0]);
    int centerY = (int)AS_NUMBER(args[1]);
    float radius = (float)AS_NUMBER(args[2]);
    Color color = loxToColor(vm, args[3]);

    DrawCircle(centerX, centerY, radius, color);

    RETURN_NIL;
}

// Lox function for: void DrawCircleSector(Vector2 center, float radius, int startAngle, int endAngle, int segments, Color color);
LOX_FUNCTION(DrawCircleSector) {
    if (argCount != 6) { RETURN_NIL; }
    Vector2 center = loxToVector2(vm, args[0]);
    float radius = (float)AS_NUMBER(args[1]);
    int startAngle = (int)AS_NUMBER(args[2]);
    int endAngle = (int)AS_NUMBER(args[3]);
    int segments = (int)AS_NUMBER(args[4]);
    Color color = loxToColor(vm, args[5]);

    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);

    RETURN_NIL;
}

// Lox function for: void DrawCircleSectorLines(Vector2 center, float radius, int startAngle, int endAngle, int segments, Color color);
LOX_FUNCTION(DrawCircleSectorLines) {
    if (argCount != 6) { RETURN_NIL; }
    Vector2 center = loxToVector2(vm, args[0]);
    float radius = (float)AS_NUMBER(args[1]);
    int startAngle = (int)AS_NUMBER(args[2]);
    int endAngle = (int)AS_NUMBER(args[3]);
    int segments = (int)AS_NUMBER(args[4]);
    Color color = loxToColor(vm, args[5]);

    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);

    RETURN_NIL;
}

// Lox function for: void DrawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2);
LOX_FUNCTION(DrawCircleGradient) {
    if (argCount != 5) { RETURN_NIL; }
    int centerX = (int)AS_NUMBER(args[0]);
    int centerY = (int)AS_NUMBER(args[1]);
    float radius = (float)AS_NUMBER(args[2]);
    Color color1 = loxToColor(vm, args[3]);
    Color color2 = loxToColor(vm, args[4]);

    DrawCircleGradient(centerX, centerY, radius, color1, color2);

    RETURN_NIL;
}

// Lox function for: void DrawCircleV(Vector2 center, float radius, Color color);
LOX_FUNCTION(DrawCircleV) {
    if (argCount != 3) { RETURN_NIL; }
    Vector2 center = loxToVector2(vm, args[0]);
    float radius = (float)AS_NUMBER(args[1]);
    Color color = loxToColor(vm, args[2]);

    DrawCircleV(center, radius, color);

    RETURN_NIL;
}

// Lox function for: void DrawCircleLines(int centerX, int centerY, float radius, Color color);
LOX_FUNCTION(DrawCircleLines) {
    if (argCount != 4) { RETURN_NIL; }
    int centerX = (int)AS_NUMBER(args[0]);
    int centerY = (int)AS_NUMBER(args[1]);
    float radius = (float)AS_NUMBER(args[2]);
    Color color = loxToColor(vm, args[3]);

    DrawCircleLines(centerX, centerY, radius, color);

    RETURN_NIL;
}

// Lox function for: void DrawRing(Vector2 center, float innerRadius, float outerRadius, int startAngle, int endAngle, int segments, Color color);
LOX_FUNCTION(DrawRing) {
    if (argCount != 7) { RETURN_NIL; }
    Vector2 center = loxToVector2(vm, args[0]);
    float innerRadius = (float)AS_NUMBER(args[1]);
    float outerRadius = (float)AS_NUMBER(args[2]);
    int startAngle = (int)AS_NUMBER(args[3]);
    int endAngle = (int)AS_NUMBER(args[4]);
    int segments = (int)AS_NUMBER(args[5]);
    Color color = loxToColor(vm, args[6]);

    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);

    RETURN_NIL;
}

// Lox function for: void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, int startAngle, int endAngle, int segments, Color color);
LOX_FUNCTION(DrawRingLines) {
    if (argCount != 7) { RETURN_NIL; }
    Vector2 center = loxToVector2(vm, args[0]);
    float innerRadius = (float)AS_NUMBER(args[1]);
    float outerRadius = (float)AS_NUMBER(args[2]);
    int startAngle = (int)AS_NUMBER(args[3]);
    int endAngle = (int)AS_NUMBER(args[4]);
    int segments = (int)AS_NUMBER(args[5]);
    Color color = loxToColor(vm, args[6]);

    DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);

    RETURN_NIL;
}

// Lox function for: void DrawRectangle(int posX, int posY, int width, int height, Color color);
LOX_FUNCTION(DrawRectangle) {
    if (argCount != 5) { RETURN_NIL; }
    int posX = (int)AS_NUMBER(args[0]);
    int posY = (int)AS_NUMBER(args[1]);
    int width = (int)AS_NUMBER(args[2]);
    int height = (int)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawRectangle(posX, posY, width, height, color);

    RETURN_NIL;
}

// Lox function for: void DrawRectangleV(Vector2 position, Vector2 size, Color color);
LOX_FUNCTION(DrawRectangleV) {
    if (argCount != 3) { RETURN_NIL; }
    Vector2 position = loxToVector2(vm, args[0]);
    Vector2 size = loxToVector2(vm, args[1]);
    Color color = loxToColor(vm, args[2]);

    DrawRectangleV(position, size, color);

    RETURN_NIL;
}

// Lox function for: void DrawRectangleRec(Rectangle rec, Color color);
LOX_FUNCTION(DrawRectangleRec) {
    if (argCount != 2) { RETURN_NIL; }
    Rectangle rec = loxToRectangle(vm, args[0]);
    Color color = loxToColor(vm, args[1]);

    DrawRectangleRec(rec, color);

    RETURN_NIL;
}

// Lox function for: void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);
LOX_FUNCTION(DrawRectanglePro) {
    if (argCount != 4) { RETURN_NIL; }
    Rectangle rec = loxToRectangle(vm, args[0]);
    Vector2 origin = loxToVector2(vm, args[1]);
    float rotation = (float)AS_NUMBER(args[2]);
    Color color = loxToColor(vm, args[3]);

    DrawRectanglePro(rec, origin, rotation, color);

    RETURN_NIL;
}

// Lox function for: void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);
LOX_FUNCTION(DrawRectangleGradientV) {
    if (argCount != 6) { RETURN_NIL; }
    int posX = (int)AS_NUMBER(args[0]);
    int posY = (int)AS_NUMBER(args[1]);
    int width = (int)AS_NUMBER(args[2]);
    int height = (int)AS_NUMBER(args[3]);
    Color color1 = loxToColor(vm, args[4]);
    Color color2 = loxToColor(vm, args[5]);

    DrawRectangleGradientV(posX, posY, width, height, color1, color2);

    RETURN_NIL;
}

// Lox function for: void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2);
LOX_FUNCTION(DrawRectangleGradientH) {
    if (argCount != 6) { RETURN_NIL; }
    int posX = (int)AS_NUMBER(args[0]);
    int posY = (int)AS_NUMBER(args[1]);
    int width = (int)AS_NUMBER(args[2]);
    int height = (int)AS_NUMBER(args[3]);
    Color color1 = loxToColor(vm, args[4]);
    Color color2 = loxToColor(vm, args[5]);

    DrawRectangleGradientH(posX, posY, width, height, color1, color2);

    RETURN_NIL;
}

// Lox function for: void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4);
LOX_FUNCTION(DrawRectangleGradientEx) {
    if (argCount != 5) { RETURN_NIL; }
    Rectangle rec = loxToRectangle(vm, args[0]);
    Color col1 = loxToColor(vm, args[1]);
    Color col2 = loxToColor(vm, args[2]);
    Color col3 = loxToColor(vm, args[3]);
    Color col4 = loxToColor(vm, args[4]);

    DrawRectangleGradientEx(rec, col1, col2, col3, col4);

    RETURN_NIL;
}

// Lox function for: void DrawRectangleLines(int posX, int posY, int width, int height, Color color);
LOX_FUNCTION(DrawRectangleLines) {
    if (argCount != 5) { RETURN_NIL; }
    int posX = (int)AS_NUMBER(args[0]);
    int posY = (int)AS_NUMBER(args[1]);
    int width = (int)AS_NUMBER(args[2]);
    int height = (int)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawRectangleLines(posX, posY, width, height, color);

    RETURN_NIL;
}

// Lox function for: void DrawRectangleLinesEx(Rectangle rec, int lineThick, Color color);
LOX_FUNCTION(DrawRectangleLinesEx) {
    if (argCount != 3) { RETURN_NIL; }
    Rectangle rec = loxToRectangle(vm, args[0]);
    int lineThick = (int)AS_NUMBER(args[1]);
    Color color = loxToColor(vm, args[2]);

    DrawRectangleLinesEx(rec, lineThick, color);

    RETURN_NIL;
}

// Lox function for: void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);
LOX_FUNCTION(DrawRectangleRounded) {
    if (argCount != 4) { RETURN_NIL; }
    Rectangle rec = loxToRectangle(vm, args[0]);
    float roundness = (float)AS_NUMBER(args[1]);
    int segments = (int)AS_NUMBER(args[2]);
    Color color = loxToColor(vm, args[3]);

    DrawRectangleRounded(rec, roundness, segments, color);

    RETURN_NIL;
}

// Lox function for: void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, int lineThick, Color color);
LOX_FUNCTION(DrawRectangleRoundedLines) {
    if (argCount != 5) { RETURN_NIL; }
    Rectangle rec = loxToRectangle(vm, args[0]);
    float roundness = (float)AS_NUMBER(args[1]);
    int segments = (int)AS_NUMBER(args[2]);
    int lineThick = (int)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawRectangleRoundedLines(rec, roundness, segments, lineThick, color);

    RETURN_NIL;
}

// Lox function for: void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);
LOX_FUNCTION(DrawTriangle) {
    if (argCount != 4) { RETURN_NIL; }
    Vector2 v1 = loxToVector2(vm, args[0]);
    Vector2 v2 = loxToVector2(vm, args[1]);
    Vector2 v3 = loxToVector2(vm, args[2]);
    Color color = loxToColor(vm, args[3]);

    DrawTriangle(v1, v2, v3, color);

    RETURN_NIL;
}

// Lox function for: void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);
LOX_FUNCTION(DrawTriangleLines) {
    if (argCount != 4) { RETURN_NIL; }
    Vector2 v1 = loxToVector2(vm, args[0]);
    Vector2 v2 = loxToVector2(vm, args[1]);
    Vector2 v3 = loxToVector2(vm, args[2]);
    Color color = loxToColor(vm, args[3]);

    DrawTriangleLines(v1, v2, v3, color);

    RETURN_NIL;
}

// Lox function for: void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);
LOX_FUNCTION(DrawPoly) {
    if (argCount != 5) { RETURN_NIL; }
    Vector2 center = loxToVector2(vm, args[0]);
    int sides = (int)AS_NUMBER(args[1]);
    float radius = (float)AS_NUMBER(args[2]);
    float rotation = (float)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawPoly(center, sides, radius, rotation, color);

    RETURN_NIL;
}

// Lox function for: void SetShapesTexture(Texture2D texture, Rectangle source);
LOX_FUNCTION(SetShapesTexture) {
    if (argCount != 2) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    Rectangle source = loxToRectangle(vm, args[1]);

    SetShapesTexture(texture, source);

    RETURN_NIL;
}

// Lox function for: bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);
LOX_FUNCTION(CheckCollisionRecs) {
    if (argCount != 2) { RETURN_NIL; }
    Rectangle rec1 = loxToRectangle(vm, args[0]);
    Rectangle rec2 = loxToRectangle(vm, args[1]);

    bool result = (bool)CheckCollisionRecs(rec1, rec2);

    RETURN_BOOL(result);
}

// Lox function for: bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);
LOX_FUNCTION(CheckCollisionCircles) {
    if (argCount != 4) { RETURN_NIL; }
    Vector2 center1 = loxToVector2(vm, args[0]);
    float radius1 = (float)AS_NUMBER(args[1]);
    Vector2 center2 = loxToVector2(vm, args[2]);
    float radius2 = (float)AS_NUMBER(args[3]);

    bool result = (bool)CheckCollisionCircles(center1, radius1, center2, radius2);

    RETURN_BOOL(result);
}

// Lox function for: bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);
LOX_FUNCTION(CheckCollisionCircleRec) {
    if (argCount != 3) { RETURN_NIL; }
    Vector2 center = loxToVector2(vm, args[0]);
    float radius = (float)AS_NUMBER(args[1]);
    Rectangle rec = loxToRectangle(vm, args[2]);

    bool result = (bool)CheckCollisionCircleRec(center, radius, rec);

    RETURN_BOOL(result);
}

// Lox function for: Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);
LOX_FUNCTION(GetCollisionRec) {
    if (argCount != 2) { RETURN_NIL; }
    Rectangle rec1 = loxToRectangle(vm, args[0]);
    Rectangle rec2 = loxToRectangle(vm, args[1]);

    Rectangle result = (Rectangle)GetCollisionRec(rec1, rec2);

    RETURN_VAL(cToLoxRectangle(vm, result));
}

// Lox function for: bool CheckCollisionPointRec(Vector2 point, Rectangle rec);
LOX_FUNCTION(CheckCollisionPointRec) {
    if (argCount != 2) { RETURN_NIL; }
    Vector2 point = loxToVector2(vm, args[0]);
    Rectangle rec = loxToRectangle(vm, args[1]);

    bool result = (bool)CheckCollisionPointRec(point, rec);

    RETURN_BOOL(result);
}

// Lox function for: bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);
LOX_FUNCTION(CheckCollisionPointCircle) {
    if (argCount != 3) { RETURN_NIL; }
    Vector2 point = loxToVector2(vm, args[0]);
    Vector2 center = loxToVector2(vm, args[1]);
    float radius = (float)AS_NUMBER(args[2]);

    bool result = (bool)CheckCollisionPointCircle(point, center, radius);

    RETURN_BOOL(result);
}

// Lox function for: bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);
LOX_FUNCTION(CheckCollisionPointTriangle) {
    if (argCount != 4) { RETURN_NIL; }
    Vector2 point = loxToVector2(vm, args[0]);
    Vector2 p1 = loxToVector2(vm, args[1]);
    Vector2 p2 = loxToVector2(vm, args[2]);
    Vector2 p3 = loxToVector2(vm, args[3]);

    bool result = (bool)CheckCollisionPointTriangle(point, p1, p2, p3);

    RETURN_BOOL(result);
}

// Lox function for: Image LoadImage(const char* fileName);
LOX_FUNCTION(LoadImage) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    Image result = (Image)LoadImage(fileName);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image LoadImageRaw(const char* fileName, int width, int height, int format, int headerSize);
LOX_FUNCTION(LoadImageRaw) {
    if (argCount != 5) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);
    int width = (int)AS_NUMBER(args[1]);
    int height = (int)AS_NUMBER(args[2]);
    int format = (int)AS_NUMBER(args[3]);
    int headerSize = (int)AS_NUMBER(args[4]);

    Image result = (Image)LoadImageRaw(fileName, width, height, format, headerSize);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: void ExportImage(Image image, const char* fileName);
LOX_FUNCTION(ExportImage) {
    if (argCount != 2) { RETURN_NIL; }
    Image image = loxToImage(vm, args[0]);
    const char* fileName = AS_CSTRING(args[1]);

    ExportImage(image, fileName);

    RETURN_NIL;
}

// Lox function for: void ExportImageAsCode(Image image, const char* fileName);
LOX_FUNCTION(ExportImageAsCode) {
    if (argCount != 2) { RETURN_NIL; }
    Image image = loxToImage(vm, args[0]);
    const char* fileName = AS_CSTRING(args[1]);

    ExportImageAsCode(image, fileName);

    RETURN_NIL;
}

// Lox function for: Texture2D LoadTexture(const char* fileName);
LOX_FUNCTION(LoadTexture) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    Texture2D result = (Texture2D)LoadTexture(fileName);

    RETURN_VAL(cToLoxTexture2D(vm, result));
}

// Lox function for: Texture2D LoadTextureFromImage(Image image);
LOX_FUNCTION(LoadTextureFromImage) {
    if (argCount != 1) { RETURN_NIL; }
    Image image = loxToImage(vm, args[0]);

    Texture2D result = (Texture2D)LoadTextureFromImage(image);

    RETURN_VAL(cToLoxTexture2D(vm, result));
}

// Lox function for: Texture2D LoadTextureCubemap(Image image, int layoutType);
LOX_FUNCTION(LoadTextureCubemap) {
    if (argCount != 2) { RETURN_NIL; }
    Image image = loxToImage(vm, args[0]);
    int layoutType = (int)AS_NUMBER(args[1]);

    Texture2D result = (Texture2D)LoadTextureCubemap(image, layoutType);

    RETURN_VAL(cToLoxTexture2D(vm, result));
}

// Lox function for: RenderTexture2D LoadRenderTexture(int width, int height);
LOX_FUNCTION(LoadRenderTexture) {
    if (argCount != 2) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);

    RenderTexture2D result = (RenderTexture2D)LoadRenderTexture(width, height);

    RETURN_VAL(cToLoxRenderTexture2D(vm, result));
}

// Lox function for: void UnloadImage(Image image);
LOX_FUNCTION(UnloadImage) {
    if (argCount != 1) { RETURN_NIL; }
    Image image = loxToImage(vm, args[0]);

    UnloadImage(image);

    RETURN_NIL;
}

// Lox function for: void UnloadTexture(Texture2D texture);
LOX_FUNCTION(UnloadTexture) {
    if (argCount != 1) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);

    UnloadTexture(texture);

    RETURN_NIL;
}

// Lox function for: void UnloadRenderTexture(RenderTexture2D target);
LOX_FUNCTION(UnloadRenderTexture) {
    if (argCount != 1) { RETURN_NIL; }
    RenderTexture2D target = loxToRenderTexture2D(vm, args[0]);

    UnloadRenderTexture(target);

    RETURN_NIL;
}

// Lox function for: int GetPixelDataSize(int width, int height, int format);
LOX_FUNCTION(GetPixelDataSize) {
    if (argCount != 3) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);
    int format = (int)AS_NUMBER(args[2]);

    int result = (int)GetPixelDataSize(width, height, format);

    RETURN_NUMBER(result);
}

// Lox function for: Image GetTextureData(Texture2D texture);
LOX_FUNCTION(GetTextureData) {
    if (argCount != 1) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);

    Image result = (Image)GetTextureData(texture);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image GetScreenData(void);
LOX_FUNCTION(GetScreenData) {
    if (argCount != 0) { RETURN_NIL; }

    Image result = (Image)GetScreenData();

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image ImageCopy(Image image);
LOX_FUNCTION(ImageCopy) {
    if (argCount != 1) { RETURN_NIL; }
    Image image = loxToImage(vm, args[0]);

    Image result = (Image)ImageCopy(image);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: void ImageToPOT(Image* image, Color fillColor);
LOX_FUNCTION(ImageToPOT) {
    if (argCount != 2) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    Color fillColor = loxToColor(vm, args[1]);

    ImageToPOT(image, fillColor);

    RETURN_NIL;
}

// Lox function for: void ImageFormat(Image* image, int newFormat);
LOX_FUNCTION(ImageFormat) {
    if (argCount != 2) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    int newFormat = (int)AS_NUMBER(args[1]);

    ImageFormat(image, newFormat);

    RETURN_NIL;
}

// Lox function for: void ImageAlphaMask(Image* image, Image alphaMask);
LOX_FUNCTION(ImageAlphaMask) {
    if (argCount != 2) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    Image alphaMask = loxToImage(vm, args[1]);

    ImageAlphaMask(image, alphaMask);

    RETURN_NIL;
}

// Lox function for: void ImageAlphaClear(Image* image, Color color, float threshold);
LOX_FUNCTION(ImageAlphaClear) {
    if (argCount != 3) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    Color color = loxToColor(vm, args[1]);
    float threshold = (float)AS_NUMBER(args[2]);

    ImageAlphaClear(image, color, threshold);

    RETURN_NIL;
}

// Lox function for: void ImageAlphaCrop(Image* image, float threshold);
LOX_FUNCTION(ImageAlphaCrop) {
    if (argCount != 2) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    float threshold = (float)AS_NUMBER(args[1]);

    ImageAlphaCrop(image, threshold);

    RETURN_NIL;
}

// Lox function for: void ImageAlphaPremultiply(Image* image);
LOX_FUNCTION(ImageAlphaPremultiply) {
    if (argCount != 1) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);

    ImageAlphaPremultiply(image);

    RETURN_NIL;
}

// Lox function for: void ImageCrop(Image* image, Rectangle crop);
LOX_FUNCTION(ImageCrop) {
    if (argCount != 2) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    Rectangle crop = loxToRectangle(vm, args[1]);

    ImageCrop(image, crop);

    RETURN_NIL;
}

// Lox function for: void ImageResize(Image* image, int newWidth, int newHeight);
LOX_FUNCTION(ImageResize) {
    if (argCount != 3) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    int newWidth = (int)AS_NUMBER(args[1]);
    int newHeight = (int)AS_NUMBER(args[2]);

    ImageResize(image, newWidth, newHeight);

    RETURN_NIL;
}

// Lox function for: void ImageResizeNN(Image* image, int newWidth,int newHeight);
LOX_FUNCTION(ImageResizeNN) {
    if (argCount != 3) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    int newWidth = (int)AS_NUMBER(args[1]);
    int newHeight = (int)AS_NUMBER(args[2]);

    ImageResizeNN(image, newWidth, newHeight);

    RETURN_NIL;
}

// Lox function for: void ImageResizeCanvas(Image* image, int newWidth, int newHeight, int offsetX, int offsetY, Color color);
LOX_FUNCTION(ImageResizeCanvas) {
    if (argCount != 6) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    int newWidth = (int)AS_NUMBER(args[1]);
    int newHeight = (int)AS_NUMBER(args[2]);
    int offsetX = (int)AS_NUMBER(args[3]);
    int offsetY = (int)AS_NUMBER(args[4]);
    Color color = loxToColor(vm, args[5]);

    ImageResizeCanvas(image, newWidth, newHeight, offsetX, offsetY, color);

    RETURN_NIL;
}

// Lox function for: void ImageMipmaps(Image* image);
LOX_FUNCTION(ImageMipmaps) {
    if (argCount != 1) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);

    ImageMipmaps(image);

    RETURN_NIL;
}

// Lox function for: void ImageDither(Image* image, int rBpp, int gBpp, int bBpp, int aBpp);
LOX_FUNCTION(ImageDither) {
    if (argCount != 5) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    int rBpp = (int)AS_NUMBER(args[1]);
    int gBpp = (int)AS_NUMBER(args[2]);
    int bBpp = (int)AS_NUMBER(args[3]);
    int aBpp = (int)AS_NUMBER(args[4]);

    ImageDither(image, rBpp, gBpp, bBpp, aBpp);

    RETURN_NIL;
}

// Lox function for: Image ImageText(const char* text, int fontSize, Color color);
LOX_FUNCTION(ImageText) {
    if (argCount != 3) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);
    int fontSize = (int)AS_NUMBER(args[1]);
    Color color = loxToColor(vm, args[2]);

    Image result = (Image)ImageText(text, fontSize, color);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image ImageTextEx(Font font, const char* text, float fontSize, float spacing, Color tint);
LOX_FUNCTION(ImageTextEx) {
    if (argCount != 5) { RETURN_NIL; }
    Font font = loxToFont(vm, args[0]);
    const char* text = AS_CSTRING(args[1]);
    float fontSize = (float)AS_NUMBER(args[2]);
    float spacing = (float)AS_NUMBER(args[3]);
    Color tint = loxToColor(vm, args[4]);

    Image result = (Image)ImageTextEx(font, text, fontSize, spacing, tint);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: void ImageDraw(Image* dst, Image src, Rectangle srcRec, Rectangle dstRec);
LOX_FUNCTION(ImageDraw) {
    if (argCount != 4) { RETURN_NIL; }
    Image* dst = loxToImage(vm, args[0]);
    Image src = loxToImage(vm, args[1]);
    Rectangle srcRec = loxToRectangle(vm, args[2]);
    Rectangle dstRec = loxToRectangle(vm, args[3]);

    ImageDraw(dst, src, srcRec, dstRec);

    RETURN_NIL;
}

// Lox function for: void ImageDrawRectangle(Image* dst, Rectangle rec, Color color);
LOX_FUNCTION(ImageDrawRectangle) {
    if (argCount != 3) { RETURN_NIL; }
    Image* dst = loxToImage(vm, args[0]);
    Rectangle rec = loxToRectangle(vm, args[1]);
    Color color = loxToColor(vm, args[2]);

    ImageDrawRectangle(dst, rec, color);

    RETURN_NIL;
}

// Lox function for: void ImageDrawRectangleLines(Image* dst, Rectangle rec, int thick, Color color);
LOX_FUNCTION(ImageDrawRectangleLines) {
    if (argCount != 4) { RETURN_NIL; }
    Image* dst = loxToImage(vm, args[0]);
    Rectangle rec = loxToRectangle(vm, args[1]);
    int thick = (int)AS_NUMBER(args[2]);
    Color color = loxToColor(vm, args[3]);

    ImageDrawRectangleLines(dst, rec, thick, color);

    RETURN_NIL;
}

// Lox function for: void ImageDrawText(Image* dst, Vector2 position, const char* text, int fontSize, Color color);
LOX_FUNCTION(ImageDrawText) {
    if (argCount != 5) { RETURN_NIL; }
    Image* dst = loxToImage(vm, args[0]);
    Vector2 position = loxToVector2(vm, args[1]);
    const char* text = AS_CSTRING(args[2]);
    int fontSize = (int)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    ImageDrawText(dst, position, text, fontSize, color);

    RETURN_NIL;
}

// Lox function for: void ImageDrawTextEx(Image* dst, Vector2 position, Font font, const char* text, float fontSize, float spacing, Color color);
LOX_FUNCTION(ImageDrawTextEx) {
    if (argCount != 7) { RETURN_NIL; }
    Image* dst = loxToImage(vm, args[0]);
    Vector2 position = loxToVector2(vm, args[1]);
    Font font = loxToFont(vm, args[2]);
    const char* text = AS_CSTRING(args[3]);
    float fontSize = (float)AS_NUMBER(args[4]);
    float spacing = (float)AS_NUMBER(args[5]);
    Color color = loxToColor(vm, args[6]);

    ImageDrawTextEx(dst, position, font, text, fontSize, spacing, color);

    RETURN_NIL;
}

// Lox function for: void ImageFlipVertical(Image* image);
LOX_FUNCTION(ImageFlipVertical) {
    if (argCount != 1) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);

    ImageFlipVertical(image);

    RETURN_NIL;
}

// Lox function for: void ImageFlipHorizontal(Image* image);
LOX_FUNCTION(ImageFlipHorizontal) {
    if (argCount != 1) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);

    ImageFlipHorizontal(image);

    RETURN_NIL;
}

// Lox function for: void ImageRotateCW(Image* image);
LOX_FUNCTION(ImageRotateCW) {
    if (argCount != 1) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);

    ImageRotateCW(image);

    RETURN_NIL;
}

// Lox function for: void ImageRotateCCW(Image* image);
LOX_FUNCTION(ImageRotateCCW) {
    if (argCount != 1) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);

    ImageRotateCCW(image);

    RETURN_NIL;
}

// Lox function for: void ImageColorTint(Image* image, Color color);
LOX_FUNCTION(ImageColorTint) {
    if (argCount != 2) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    Color color = loxToColor(vm, args[1]);

    ImageColorTint(image, color);

    RETURN_NIL;
}

// Lox function for: void ImageColorInvert(Image* image);
LOX_FUNCTION(ImageColorInvert) {
    if (argCount != 1) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);

    ImageColorInvert(image);

    RETURN_NIL;
}

// Lox function for: void ImageColorGrayscale(Image* image);
LOX_FUNCTION(ImageColorGrayscale) {
    if (argCount != 1) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);

    ImageColorGrayscale(image);

    RETURN_NIL;
}

// Lox function for: void ImageColorContrast(Image* image, float contrast);
LOX_FUNCTION(ImageColorContrast) {
    if (argCount != 2) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    float contrast = (float)AS_NUMBER(args[1]);

    ImageColorContrast(image, contrast);

    RETURN_NIL;
}

// Lox function for: void ImageColorBrightness(Image* image, int brightness);
LOX_FUNCTION(ImageColorBrightness) {
    if (argCount != 2) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    int brightness = (int)AS_NUMBER(args[1]);

    ImageColorBrightness(image, brightness);

    RETURN_NIL;
}

// Lox function for: void ImageColorReplace(Image* image, Color color, Color replace);
LOX_FUNCTION(ImageColorReplace) {
    if (argCount != 3) { RETURN_NIL; }
    Image* image = loxToImage(vm, args[0]);
    Color color = loxToColor(vm, args[1]);
    Color replace = loxToColor(vm, args[2]);

    ImageColorReplace(image, color, replace);

    RETURN_NIL;
}

// Lox function for: Image GenImageColor(int width, int height, Color color);
LOX_FUNCTION(GenImageColor) {
    if (argCount != 3) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);
    Color color = loxToColor(vm, args[2]);

    Image result = (Image)GenImageColor(width, height, color);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image GenImageGradientV(int width, int height, Color top, Color bottom);
LOX_FUNCTION(GenImageGradientV) {
    if (argCount != 4) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);
    Color top = loxToColor(vm, args[2]);
    Color bottom = loxToColor(vm, args[3]);

    Image result = (Image)GenImageGradientV(width, height, top, bottom);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image GenImageGradientH(int width, int height, Color left, Color right);
LOX_FUNCTION(GenImageGradientH) {
    if (argCount != 4) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);
    Color left = loxToColor(vm, args[2]);
    Color right = loxToColor(vm, args[3]);

    Image result = (Image)GenImageGradientH(width, height, left, right);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);
LOX_FUNCTION(GenImageGradientRadial) {
    if (argCount != 5) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);
    float density = (float)AS_NUMBER(args[2]);
    Color inner = loxToColor(vm, args[3]);
    Color outer = loxToColor(vm, args[4]);

    Image result = (Image)GenImageGradientRadial(width, height, density, inner, outer);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);
LOX_FUNCTION(GenImageChecked) {
    if (argCount != 6) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);
    int checksX = (int)AS_NUMBER(args[2]);
    int checksY = (int)AS_NUMBER(args[3]);
    Color col1 = loxToColor(vm, args[4]);
    Color col2 = loxToColor(vm, args[5]);

    Image result = (Image)GenImageChecked(width, height, checksX, checksY, col1, col2);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image GenImageWhiteNoise(int width, int height, float factor);
LOX_FUNCTION(GenImageWhiteNoise) {
    if (argCount != 3) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);
    float factor = (float)AS_NUMBER(args[2]);

    Image result = (Image)GenImageWhiteNoise(width, height, factor);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale);
LOX_FUNCTION(GenImagePerlinNoise) {
    if (argCount != 5) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);
    int offsetX = (int)AS_NUMBER(args[2]);
    int offsetY = (int)AS_NUMBER(args[3]);
    float scale = (float)AS_NUMBER(args[4]);

    Image result = (Image)GenImagePerlinNoise(width, height, offsetX, offsetY, scale);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: Image GenImageCellular(int width, int height, int tileSize);
LOX_FUNCTION(GenImageCellular) {
    if (argCount != 3) { RETURN_NIL; }
    int width = (int)AS_NUMBER(args[0]);
    int height = (int)AS_NUMBER(args[1]);
    int tileSize = (int)AS_NUMBER(args[2]);

    Image result = (Image)GenImageCellular(width, height, tileSize);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: void GenTextureMipmaps(Texture2D* texture);
LOX_FUNCTION(GenTextureMipmaps) {
    if (argCount != 1) { RETURN_NIL; }
    Texture2D* texture = loxToTexture2D(vm, args[0]);

    GenTextureMipmaps(texture);

    RETURN_NIL;
}

// Lox function for: void SetTextureFilter(Texture2D texture, int filterMode);
LOX_FUNCTION(SetTextureFilter) {
    if (argCount != 2) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    int filterMode = (int)AS_NUMBER(args[1]);

    SetTextureFilter(texture, filterMode);

    RETURN_NIL;
}

// Lox function for: void SetTextureWrap(Texture2D texture, int wrapMode);
LOX_FUNCTION(SetTextureWrap) {
    if (argCount != 2) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    int wrapMode = (int)AS_NUMBER(args[1]);

    SetTextureWrap(texture, wrapMode);

    RETURN_NIL;
}

// Lox function for: void DrawTexture(Texture2D texture, int posX, int posY, Color tint);
LOX_FUNCTION(DrawTexture) {
    if (argCount != 4) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    int posX = (int)AS_NUMBER(args[1]);
    int posY = (int)AS_NUMBER(args[2]);
    Color tint = loxToColor(vm, args[3]);

    DrawTexture(texture, posX, posY, tint);

    RETURN_NIL;
}

// Lox function for: void DrawTextureV(Texture2D texture, Vector2 position, Color tint);
LOX_FUNCTION(DrawTextureV) {
    if (argCount != 3) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    Vector2 position = loxToVector2(vm, args[1]);
    Color tint = loxToColor(vm, args[2]);

    DrawTextureV(texture, position, tint);

    RETURN_NIL;
}

// Lox function for: void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);
LOX_FUNCTION(DrawTextureEx) {
    if (argCount != 5) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    Vector2 position = loxToVector2(vm, args[1]);
    float rotation = (float)AS_NUMBER(args[2]);
    float scale = (float)AS_NUMBER(args[3]);
    Color tint = loxToColor(vm, args[4]);

    DrawTextureEx(texture, position, rotation, scale, tint);

    RETURN_NIL;
}

// Lox function for: void DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint);
LOX_FUNCTION(DrawTextureRec) {
    if (argCount != 4) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    Rectangle sourceRec = loxToRectangle(vm, args[1]);
    Vector2 position = loxToVector2(vm, args[2]);
    Color tint = loxToColor(vm, args[3]);

    DrawTextureRec(texture, sourceRec, position, tint);

    RETURN_NIL;
}

// Lox function for: void DrawTextureQuad(Texture2D texture, Vector2 tiling, Vector2 offset, Rectangle quad, Color tint);
LOX_FUNCTION(DrawTextureQuad) {
    if (argCount != 5) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    Vector2 tiling = loxToVector2(vm, args[1]);
    Vector2 offset = loxToVector2(vm, args[2]);
    Rectangle quad = loxToRectangle(vm, args[3]);
    Color tint = loxToColor(vm, args[4]);

    DrawTextureQuad(texture, tiling, offset, quad, tint);

    RETURN_NIL;
}

// Lox function for: void DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin, float rotation, Color tint);
LOX_FUNCTION(DrawTexturePro) {
    if (argCount != 6) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    Rectangle sourceRec = loxToRectangle(vm, args[1]);
    Rectangle destRec = loxToRectangle(vm, args[2]);
    Vector2 origin = loxToVector2(vm, args[3]);
    float rotation = (float)AS_NUMBER(args[4]);
    Color tint = loxToColor(vm, args[5]);

    DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);

    RETURN_NIL;
}

// Lox function for: void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle destRec, Vector2 origin, float rotation, Color tint);
LOX_FUNCTION(DrawTextureNPatch) {
    if (argCount != 6) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    NPatchInfo nPatchInfo = loxToNPatchInfo(vm, args[1]);
    Rectangle destRec = loxToRectangle(vm, args[2]);
    Vector2 origin = loxToVector2(vm, args[3]);
    float rotation = (float)AS_NUMBER(args[4]);
    Color tint = loxToColor(vm, args[5]);

    DrawTextureNPatch(texture, nPatchInfo, destRec, origin, rotation, tint);

    RETURN_NIL;
}

// Lox function for: Font GetFontDefault(void);
LOX_FUNCTION(GetFontDefault) {
    if (argCount != 0) { RETURN_NIL; }

    Font result = (Font)GetFontDefault();

    RETURN_VAL(cToLoxFont(vm, result));
}

// Lox function for: Font LoadFont(const char* fileName);
LOX_FUNCTION(LoadFont) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    Font result = (Font)LoadFont(fileName);

    RETURN_VAL(cToLoxFont(vm, result));
}

// Lox function for: Font LoadFontFromImage(Image image, Color key, int firstChar);
LOX_FUNCTION(LoadFontFromImage) {
    if (argCount != 3) { RETURN_NIL; }
    Image image = loxToImage(vm, args[0]);
    Color key = loxToColor(vm, args[1]);
    int firstChar = (int)AS_NUMBER(args[2]);

    Font result = (Font)LoadFontFromImage(image, key, firstChar);

    RETURN_VAL(cToLoxFont(vm, result));
}

// Lox function for: Image GenImageFontAtlas(CharInfo* chars, int charsCount, int fontSize, int padding, int packMethod);
LOX_FUNCTION(GenImageFontAtlas) {
    if (argCount != 5) { RETURN_NIL; }
    CharInfo* chars = loxToCharInfo(vm, args[0]);
    int charsCount = (int)AS_NUMBER(args[1]);
    int fontSize = (int)AS_NUMBER(args[2]);
    int padding = (int)AS_NUMBER(args[3]);
    int packMethod = (int)AS_NUMBER(args[4]);

    Image result = (Image)GenImageFontAtlas(chars, charsCount, fontSize, padding, packMethod);

    RETURN_VAL(cToLoxImage(vm, result));
}

// Lox function for: void UnloadFont(Font font);
LOX_FUNCTION(UnloadFont) {
    if (argCount != 1) { RETURN_NIL; }
    Font font = loxToFont(vm, args[0]);

    UnloadFont(font);

    RETURN_NIL;
}

// Lox function for: void DrawFPS(int posX, int posY);
LOX_FUNCTION(DrawFPS) {
    if (argCount != 2) { RETURN_NIL; }
    int posX = (int)AS_NUMBER(args[0]);
    int posY = (int)AS_NUMBER(args[1]);

    DrawFPS(posX, posY);

    RETURN_NIL;
}

// Lox function for: void DrawText(const char* text, int posX, int posY, int fontSize, Color color);
LOX_FUNCTION(DrawText) {
    if (argCount != 5) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);
    int posX = (int)AS_NUMBER(args[1]);
    int posY = (int)AS_NUMBER(args[2]);
    int fontSize = (int)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawText(text, posX, posY, fontSize, color);

    RETURN_NIL;
}

// Lox function for: void DrawTextEx(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color tint);
LOX_FUNCTION(DrawTextEx) {
    if (argCount != 6) { RETURN_NIL; }
    Font font = loxToFont(vm, args[0]);
    const char* text = AS_CSTRING(args[1]);
    Vector2 position = loxToVector2(vm, args[2]);
    float fontSize = (float)AS_NUMBER(args[3]);
    float spacing = (float)AS_NUMBER(args[4]);
    Color tint = loxToColor(vm, args[5]);

    DrawTextEx(font, text, position, fontSize, spacing, tint);

    RETURN_NIL;
}

// Lox function for: void DrawTextRec(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);
LOX_FUNCTION(DrawTextRec) {
    if (argCount != 7) { RETURN_NIL; }
    Font font = loxToFont(vm, args[0]);
    const char* text = AS_CSTRING(args[1]);
    Rectangle rec = loxToRectangle(vm, args[2]);
    float fontSize = (float)AS_NUMBER(args[3]);
    float spacing = (float)AS_NUMBER(args[4]);
    bool wordWrap = AS_BOOL(args[5]);
    Color tint = loxToColor(vm, args[6]);

    DrawTextRec(font, text, rec, fontSize, spacing, wordWrap, tint);

    RETURN_NIL;
}

// Lox function for: void DrawTextRecEx(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectText, Color selectBack);
LOX_FUNCTION(DrawTextRecEx) {
    if (argCount != 11) { RETURN_NIL; }
    Font font = loxToFont(vm, args[0]);
    const char* text = AS_CSTRING(args[1]);
    Rectangle rec = loxToRectangle(vm, args[2]);
    float fontSize = (float)AS_NUMBER(args[3]);
    float spacing = (float)AS_NUMBER(args[4]);
    bool wordWrap = AS_BOOL(args[5]);
    Color tint = loxToColor(vm, args[6]);
    int selectStart = (int)AS_NUMBER(args[7]);
    int selectLength = (int)AS_NUMBER(args[8]);
    Color selectText = loxToColor(vm, args[9]);
    Color selectBack = loxToColor(vm, args[10]);

    DrawTextRecEx(font, text, rec, fontSize, spacing, wordWrap, tint, selectStart, selectLength, selectText, selectBack);

    RETURN_NIL;
}

// Lox function for: int MeasureText(const char* text, int fontSize);
LOX_FUNCTION(MeasureText) {
    if (argCount != 2) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);
    int fontSize = (int)AS_NUMBER(args[1]);

    int result = (int)MeasureText(text, fontSize);

    RETURN_NUMBER(result);
}

// Lox function for: Vector2 MeasureTextEx(Font font, const char* text, float fontSize, float spacing);
LOX_FUNCTION(MeasureTextEx) {
    if (argCount != 4) { RETURN_NIL; }
    Font font = loxToFont(vm, args[0]);
    const char* text = AS_CSTRING(args[1]);
    float fontSize = (float)AS_NUMBER(args[2]);
    float spacing = (float)AS_NUMBER(args[3]);

    Vector2 result = (Vector2)MeasureTextEx(font, text, fontSize, spacing);

    RETURN_VAL(cToLoxVector2(vm, result));
}

// Lox function for: int GetGlyphIndex(Font font, int character);
LOX_FUNCTION(GetGlyphIndex) {
    if (argCount != 2) { RETURN_NIL; }
    Font font = loxToFont(vm, args[0]);
    int character = (int)AS_NUMBER(args[1]);

    int result = (int)GetGlyphIndex(font, character);

    RETURN_NUMBER(result);
}

// Lox function for: bool TextIsEqual(const char* text1, const char* text2);
LOX_FUNCTION(TextIsEqual) {
    if (argCount != 2) { RETURN_NIL; }
    const char* text1 = AS_CSTRING(args[0]);
    const char* text2 = AS_CSTRING(args[1]);

    bool result = (bool)TextIsEqual(text1, text2);

    RETURN_BOOL(result);
}

// Lox function for: unsigned int TextLength(const char* text);
LOX_FUNCTION(TextLength) {
    if (argCount != 1) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);

    unsigned int result = (unsigned int)TextLength(text);

    RETURN_NUMBER(result);
}

// Lox function for: const char* TextSubtext(const char* text, int position, int length);
LOX_FUNCTION(TextSubtext) {
    if (argCount != 3) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);
    int position = (int)AS_NUMBER(args[1]);
    int length = (int)AS_NUMBER(args[2]);

    const char* result = (const char*)TextSubtext(text, position, length);

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: int TextFindIndex(const char* text, const char* find);
LOX_FUNCTION(TextFindIndex) {
    if (argCount != 2) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);
    const char* find = AS_CSTRING(args[1]);

    int result = (int)TextFindIndex(text, find);

    RETURN_NUMBER(result);
}

// Lox function for: const char* TextToUpper(const char* text);
LOX_FUNCTION(TextToUpper) {
    if (argCount != 1) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);

    const char* result = (const char*)TextToUpper(text);

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: const char* TextToLower(const char* text);
LOX_FUNCTION(TextToLower) {
    if (argCount != 1) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);

    const char* result = (const char*)TextToLower(text);

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: const char* TextToPascal(const char* text);
LOX_FUNCTION(TextToPascal) {
    if (argCount != 1) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);

    const char* result = (const char*)TextToPascal(text);

    RETURN_OBJ(copyString(vm, result, strlen(result)));
}

// Lox function for: int TextToInteger(const char* text);
LOX_FUNCTION(TextToInteger) {
    if (argCount != 1) { RETURN_NIL; }
    const char* text = AS_CSTRING(args[0]);

    int result = (int)TextToInteger(text);

    RETURN_NUMBER(result);
}

// Lox function for: void DrawLine3D(Vector3 startPos, Vector3 endPos, Color color);
LOX_FUNCTION(DrawLine3D) {
    if (argCount != 3) { RETURN_NIL; }
    Vector3 startPos = loxToVector3(vm, args[0]);
    Vector3 endPos = loxToVector3(vm, args[1]);
    Color color = loxToColor(vm, args[2]);

    DrawLine3D(startPos, endPos, color);

    RETURN_NIL;
}

// Lox function for: void DrawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color);
LOX_FUNCTION(DrawCircle3D) {
    if (argCount != 5) { RETURN_NIL; }
    Vector3 center = loxToVector3(vm, args[0]);
    float radius = (float)AS_NUMBER(args[1]);
    Vector3 rotationAxis = loxToVector3(vm, args[2]);
    float rotationAngle = (float)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);

    RETURN_NIL;
}

// Lox function for: void DrawCube(Vector3 position, float width, float height, float length, Color color);
LOX_FUNCTION(DrawCube) {
    if (argCount != 5) { RETURN_NIL; }
    Vector3 position = loxToVector3(vm, args[0]);
    float width = (float)AS_NUMBER(args[1]);
    float height = (float)AS_NUMBER(args[2]);
    float length = (float)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawCube(position, width, height, length, color);

    RETURN_NIL;
}

// Lox function for: void DrawCubeV(Vector3 position, Vector3 size, Color color);
LOX_FUNCTION(DrawCubeV) {
    if (argCount != 3) { RETURN_NIL; }
    Vector3 position = loxToVector3(vm, args[0]);
    Vector3 size = loxToVector3(vm, args[1]);
    Color color = loxToColor(vm, args[2]);

    DrawCubeV(position, size, color);

    RETURN_NIL;
}

// Lox function for: void DrawCubeWires(Vector3 position, float width, float height, float length, Color color);
LOX_FUNCTION(DrawCubeWires) {
    if (argCount != 5) { RETURN_NIL; }
    Vector3 position = loxToVector3(vm, args[0]);
    float width = (float)AS_NUMBER(args[1]);
    float height = (float)AS_NUMBER(args[2]);
    float length = (float)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawCubeWires(position, width, height, length, color);

    RETURN_NIL;
}

// Lox function for: void DrawCubeWiresV(Vector3 position, Vector3 size, Color color);
LOX_FUNCTION(DrawCubeWiresV) {
    if (argCount != 3) { RETURN_NIL; }
    Vector3 position = loxToVector3(vm, args[0]);
    Vector3 size = loxToVector3(vm, args[1]);
    Color color = loxToColor(vm, args[2]);

    DrawCubeWiresV(position, size, color);

    RETURN_NIL;
}

// Lox function for: void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color);
LOX_FUNCTION(DrawCubeTexture) {
    if (argCount != 6) { RETURN_NIL; }
    Texture2D texture = loxToTexture2D(vm, args[0]);
    Vector3 position = loxToVector3(vm, args[1]);
    float width = (float)AS_NUMBER(args[2]);
    float height = (float)AS_NUMBER(args[3]);
    float length = (float)AS_NUMBER(args[4]);
    Color color = loxToColor(vm, args[5]);

    DrawCubeTexture(texture, position, width, height, length, color);

    RETURN_NIL;
}

// Lox function for: void DrawSphere(Vector3 centerPos, float radius, Color color);
LOX_FUNCTION(DrawSphere) {
    if (argCount != 3) { RETURN_NIL; }
    Vector3 centerPos = loxToVector3(vm, args[0]);
    float radius = (float)AS_NUMBER(args[1]);
    Color color = loxToColor(vm, args[2]);

    DrawSphere(centerPos, radius, color);

    RETURN_NIL;
}

// Lox function for: void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color);
LOX_FUNCTION(DrawSphereEx) {
    if (argCount != 5) { RETURN_NIL; }
    Vector3 centerPos = loxToVector3(vm, args[0]);
    float radius = (float)AS_NUMBER(args[1]);
    int rings = (int)AS_NUMBER(args[2]);
    int slices = (int)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawSphereEx(centerPos, radius, rings, slices, color);

    RETURN_NIL;
}

// Lox function for: void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color);
LOX_FUNCTION(DrawSphereWires) {
    if (argCount != 5) { RETURN_NIL; }
    Vector3 centerPos = loxToVector3(vm, args[0]);
    float radius = (float)AS_NUMBER(args[1]);
    int rings = (int)AS_NUMBER(args[2]);
    int slices = (int)AS_NUMBER(args[3]);
    Color color = loxToColor(vm, args[4]);

    DrawSphereWires(centerPos, radius, rings, slices, color);

    RETURN_NIL;
}

// Lox function for: void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color);
LOX_FUNCTION(DrawCylinder) {
    if (argCount != 6) { RETURN_NIL; }
    Vector3 position = loxToVector3(vm, args[0]);
    float radiusTop = (float)AS_NUMBER(args[1]);
    float radiusBottom = (float)AS_NUMBER(args[2]);
    float height = (float)AS_NUMBER(args[3]);
    int slices = (int)AS_NUMBER(args[4]);
    Color color = loxToColor(vm, args[5]);

    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);

    RETURN_NIL;
}

// Lox function for: void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color);
LOX_FUNCTION(DrawCylinderWires) {
    if (argCount != 6) { RETURN_NIL; }
    Vector3 position = loxToVector3(vm, args[0]);
    float radiusTop = (float)AS_NUMBER(args[1]);
    float radiusBottom = (float)AS_NUMBER(args[2]);
    float height = (float)AS_NUMBER(args[3]);
    int slices = (int)AS_NUMBER(args[4]);
    Color color = loxToColor(vm, args[5]);

    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);

    RETURN_NIL;
}

// Lox function for: void DrawPlane(Vector3 centerPos, Vector2 size, Color color);
LOX_FUNCTION(DrawPlane) {
    if (argCount != 3) { RETURN_NIL; }
    Vector3 centerPos = loxToVector3(vm, args[0]);
    Vector2 size = loxToVector2(vm, args[1]);
    Color color = loxToColor(vm, args[2]);

    DrawPlane(centerPos, size, color);

    RETURN_NIL;
}

// Lox function for: void DrawRay(Ray ray, Color color);
LOX_FUNCTION(DrawRay) {
    if (argCount != 2) { RETURN_NIL; }
    Ray ray = loxToRay(vm, args[0]);
    Color color = loxToColor(vm, args[1]);

    DrawRay(ray, color);

    RETURN_NIL;
}

// Lox function for: void DrawGrid(int slices, float spacing);
LOX_FUNCTION(DrawGrid) {
    if (argCount != 2) { RETURN_NIL; }
    int slices = (int)AS_NUMBER(args[0]);
    float spacing = (float)AS_NUMBER(args[1]);

    DrawGrid(slices, spacing);

    RETURN_NIL;
}

// Lox function for: void DrawGizmo(Vector3 position);
LOX_FUNCTION(DrawGizmo) {
    if (argCount != 1) { RETURN_NIL; }
    Vector3 position = loxToVector3(vm, args[0]);

    DrawGizmo(position);

    RETURN_NIL;
}

// Lox function for: Model LoadModel(const char* fileName);
LOX_FUNCTION(LoadModel) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    Model result = (Model)LoadModel(fileName);

    RETURN_VAL(cToLoxModel(vm, result));
}

// Lox function for: Model LoadModelFromMesh(Mesh mesh);
LOX_FUNCTION(LoadModelFromMesh) {
    if (argCount != 1) { RETURN_NIL; }
    Mesh mesh = loxToMesh(vm, args[0]);

    Model result = (Model)LoadModelFromMesh(mesh);

    RETURN_VAL(cToLoxModel(vm, result));
}

// Lox function for: void UnloadModel(Model model);
LOX_FUNCTION(UnloadModel) {
    if (argCount != 1) { RETURN_NIL; }
    Model model = loxToModel(vm, args[0]);

    UnloadModel(model);

    RETURN_NIL;
}

// Lox function for: void ExportMesh(Mesh mesh, const char* fileName);
LOX_FUNCTION(ExportMesh) {
    if (argCount != 2) { RETURN_NIL; }
    Mesh mesh = loxToMesh(vm, args[0]);
    const char* fileName = AS_CSTRING(args[1]);

    ExportMesh(mesh, fileName);

    RETURN_NIL;
}

// Lox function for: void UnloadMesh(Mesh* mesh);
LOX_FUNCTION(UnloadMesh) {
    if (argCount != 1) { RETURN_NIL; }
    Mesh* mesh = loxToMesh(vm, args[0]);

    UnloadMesh(mesh);

    RETURN_NIL;
}

// Lox function for: Material LoadMaterialDefault(void);
LOX_FUNCTION(LoadMaterialDefault) {
    if (argCount != 0) { RETURN_NIL; }

    Material result = (Material)LoadMaterialDefault();

    RETURN_VAL(cToLoxMaterial(vm, result));
}

// Lox function for: void UnloadMaterial(Material material);
LOX_FUNCTION(UnloadMaterial) {
    if (argCount != 1) { RETURN_NIL; }
    Material material = loxToMaterial(vm, args[0]);

    UnloadMaterial(material);

    RETURN_NIL;
}

// Lox function for: void SetMaterialTexture(Material* material, int mapType, Texture2D texture);
LOX_FUNCTION(SetMaterialTexture) {
    if (argCount != 3) { RETURN_NIL; }
    Material* material = loxToMaterial(vm, args[0]);
    int mapType = (int)AS_NUMBER(args[1]);
    Texture2D texture = loxToTexture2D(vm, args[2]);

    SetMaterialTexture(material, mapType, texture);

    RETURN_NIL;
}

// Lox function for: void SetModelMeshMaterial(Model* model, int meshId, int materialId);
LOX_FUNCTION(SetModelMeshMaterial) {
    if (argCount != 3) { RETURN_NIL; }
    Model* model = loxToModel(vm, args[0]);
    int meshId = (int)AS_NUMBER(args[1]);
    int materialId = (int)AS_NUMBER(args[2]);

    SetModelMeshMaterial(model, meshId, materialId);

    RETURN_NIL;
}

// Lox function for: void UpdateModelAnimation(Model model, ModelAnimation anim, int frame);
LOX_FUNCTION(UpdateModelAnimation) {
    if (argCount != 3) { RETURN_NIL; }
    Model model = loxToModel(vm, args[0]);
    ModelAnimation anim = loxToModelAnimation(vm, args[1]);
    int frame = (int)AS_NUMBER(args[2]);

    UpdateModelAnimation(model, anim, frame);

    RETURN_NIL;
}

// Lox function for: void UnloadModelAnimation(ModelAnimation anim);
LOX_FUNCTION(UnloadModelAnimation) {
    if (argCount != 1) { RETURN_NIL; }
    ModelAnimation anim = loxToModelAnimation(vm, args[0]);

    UnloadModelAnimation(anim);

    RETURN_NIL;
}

// Lox function for: bool IsModelAnimationValid(Model model, ModelAnimation anim);
LOX_FUNCTION(IsModelAnimationValid) {
    if (argCount != 2) { RETURN_NIL; }
    Model model = loxToModel(vm, args[0]);
    ModelAnimation anim = loxToModelAnimation(vm, args[1]);

    bool result = (bool)IsModelAnimationValid(model, anim);

    RETURN_BOOL(result);
}

// Lox function for: Mesh GenMeshPoly(int sides, float radius);
LOX_FUNCTION(GenMeshPoly) {
    if (argCount != 2) { RETURN_NIL; }
    int sides = (int)AS_NUMBER(args[0]);
    float radius = (float)AS_NUMBER(args[1]);

    Mesh result = (Mesh)GenMeshPoly(sides, radius);

    RETURN_VAL(cToLoxMesh(vm, result));
}

// Lox function for: Mesh GenMeshPlane(float width, float length, int resX, int resZ);
LOX_FUNCTION(GenMeshPlane) {
    if (argCount != 4) { RETURN_NIL; }
    float width = (float)AS_NUMBER(args[0]);
    float length = (float)AS_NUMBER(args[1]);
    int resX = (int)AS_NUMBER(args[2]);
    int resZ = (int)AS_NUMBER(args[3]);

    Mesh result = (Mesh)GenMeshPlane(width, length, resX, resZ);

    RETURN_VAL(cToLoxMesh(vm, result));
}

// Lox function for: Mesh GenMeshCube(float width, float height, float length);
LOX_FUNCTION(GenMeshCube) {
    if (argCount != 3) { RETURN_NIL; }
    float width = (float)AS_NUMBER(args[0]);
    float height = (float)AS_NUMBER(args[1]);
    float length = (float)AS_NUMBER(args[2]);

    Mesh result = (Mesh)GenMeshCube(width, height, length);

    RETURN_VAL(cToLoxMesh(vm, result));
}

// Lox function for: Mesh GenMeshSphere(float radius, int rings, int slices);
LOX_FUNCTION(GenMeshSphere) {
    if (argCount != 3) { RETURN_NIL; }
    float radius = (float)AS_NUMBER(args[0]);
    int rings = (int)AS_NUMBER(args[1]);
    int slices = (int)AS_NUMBER(args[2]);

    Mesh result = (Mesh)GenMeshSphere(radius, rings, slices);

    RETURN_VAL(cToLoxMesh(vm, result));
}

// Lox function for: Mesh GenMeshHemiSphere(float radius, int rings, int slices);
LOX_FUNCTION(GenMeshHemiSphere) {
    if (argCount != 3) { RETURN_NIL; }
    float radius = (float)AS_NUMBER(args[0]);
    int rings = (int)AS_NUMBER(args[1]);
    int slices = (int)AS_NUMBER(args[2]);

    Mesh result = (Mesh)GenMeshHemiSphere(radius, rings, slices);

    RETURN_VAL(cToLoxMesh(vm, result));
}

// Lox function for: Mesh GenMeshCylinder(float radius, float height, int slices);
LOX_FUNCTION(GenMeshCylinder) {
    if (argCount != 3) { RETURN_NIL; }
    float radius = (float)AS_NUMBER(args[0]);
    float height = (float)AS_NUMBER(args[1]);
    int slices = (int)AS_NUMBER(args[2]);

    Mesh result = (Mesh)GenMeshCylinder(radius, height, slices);

    RETURN_VAL(cToLoxMesh(vm, result));
}

// Lox function for: Mesh GenMeshTorus(float radius, float size, int radSeg, int sides);
LOX_FUNCTION(GenMeshTorus) {
    if (argCount != 4) { RETURN_NIL; }
    float radius = (float)AS_NUMBER(args[0]);
    float size = (float)AS_NUMBER(args[1]);
    int radSeg = (int)AS_NUMBER(args[2]);
    int sides = (int)AS_NUMBER(args[3]);

    Mesh result = (Mesh)GenMeshTorus(radius, size, radSeg, sides);

    RETURN_VAL(cToLoxMesh(vm, result));
}

// Lox function for: Mesh GenMeshKnot(float radius, float size, int radSeg, int sides);
LOX_FUNCTION(GenMeshKnot) {
    if (argCount != 4) { RETURN_NIL; }
    float radius = (float)AS_NUMBER(args[0]);
    float size = (float)AS_NUMBER(args[1]);
    int radSeg = (int)AS_NUMBER(args[2]);
    int sides = (int)AS_NUMBER(args[3]);

    Mesh result = (Mesh)GenMeshKnot(radius, size, radSeg, sides);

    RETURN_VAL(cToLoxMesh(vm, result));
}

// Lox function for: Mesh GenMeshHeightmap(Image heightmap, Vector3 size);
LOX_FUNCTION(GenMeshHeightmap) {
    if (argCount != 2) { RETURN_NIL; }
    Image heightmap = loxToImage(vm, args[0]);
    Vector3 size = loxToVector3(vm, args[1]);

    Mesh result = (Mesh)GenMeshHeightmap(heightmap, size);

    RETURN_VAL(cToLoxMesh(vm, result));
}

// Lox function for: Mesh GenMeshCubicmap(Image cubicmap, Vector3 cubeSize);
LOX_FUNCTION(GenMeshCubicmap) {
    if (argCount != 2) { RETURN_NIL; }
    Image cubicmap = loxToImage(vm, args[0]);
    Vector3 cubeSize = loxToVector3(vm, args[1]);

    Mesh result = (Mesh)GenMeshCubicmap(cubicmap, cubeSize);

    RETURN_VAL(cToLoxMesh(vm, result));
}

// Lox function for: BoundingBox MeshBoundingBox(Mesh mesh);
LOX_FUNCTION(MeshBoundingBox) {
    if (argCount != 1) { RETURN_NIL; }
    Mesh mesh = loxToMesh(vm, args[0]);

    BoundingBox result = (BoundingBox)MeshBoundingBox(mesh);

    RETURN_VAL(cToLoxBoundingBox(vm, result));
}

// Lox function for: void MeshTangents(Mesh* mesh);
LOX_FUNCTION(MeshTangents) {
    if (argCount != 1) { RETURN_NIL; }
    Mesh* mesh = loxToMesh(vm, args[0]);

    MeshTangents(mesh);

    RETURN_NIL;
}

// Lox function for: void MeshBinormals(Mesh* mesh);
LOX_FUNCTION(MeshBinormals) {
    if (argCount != 1) { RETURN_NIL; }
    Mesh* mesh = loxToMesh(vm, args[0]);

    MeshBinormals(mesh);

    RETURN_NIL;
}

// Lox function for: void DrawModel(Model model, Vector3 position, float scale, Color tint);
LOX_FUNCTION(DrawModel) {
    if (argCount != 4) { RETURN_NIL; }
    Model model = loxToModel(vm, args[0]);
    Vector3 position = loxToVector3(vm, args[1]);
    float scale = (float)AS_NUMBER(args[2]);
    Color tint = loxToColor(vm, args[3]);

    DrawModel(model, position, scale, tint);

    RETURN_NIL;
}

// Lox function for: void DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);
LOX_FUNCTION(DrawModelEx) {
    if (argCount != 6) { RETURN_NIL; }
    Model model = loxToModel(vm, args[0]);
    Vector3 position = loxToVector3(vm, args[1]);
    Vector3 rotationAxis = loxToVector3(vm, args[2]);
    float rotationAngle = (float)AS_NUMBER(args[3]);
    Vector3 scale = loxToVector3(vm, args[4]);
    Color tint = loxToColor(vm, args[5]);

    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);

    RETURN_NIL;
}

// Lox function for: void DrawModelWires(Model model, Vector3 position, float scale, Color tint);
LOX_FUNCTION(DrawModelWires) {
    if (argCount != 4) { RETURN_NIL; }
    Model model = loxToModel(vm, args[0]);
    Vector3 position = loxToVector3(vm, args[1]);
    float scale = (float)AS_NUMBER(args[2]);
    Color tint = loxToColor(vm, args[3]);

    DrawModelWires(model, position, scale, tint);

    RETURN_NIL;
}

// Lox function for: void DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);
LOX_FUNCTION(DrawModelWiresEx) {
    if (argCount != 6) { RETURN_NIL; }
    Model model = loxToModel(vm, args[0]);
    Vector3 position = loxToVector3(vm, args[1]);
    Vector3 rotationAxis = loxToVector3(vm, args[2]);
    float rotationAngle = (float)AS_NUMBER(args[3]);
    Vector3 scale = loxToVector3(vm, args[4]);
    Color tint = loxToColor(vm, args[5]);

    DrawModelWiresEx(model, position, rotationAxis, rotationAngle, scale, tint);

    RETURN_NIL;
}

// Lox function for: void DrawBoundingBox(BoundingBox box, Color color);
LOX_FUNCTION(DrawBoundingBox) {
    if (argCount != 2) { RETURN_NIL; }
    BoundingBox box = loxToBoundingBox(vm, args[0]);
    Color color = loxToColor(vm, args[1]);

    DrawBoundingBox(box, color);

    RETURN_NIL;
}

// Lox function for: void DrawBillboard(Camera3D camera, Texture2D texture, Vector3 center, float size, Color tint);
LOX_FUNCTION(DrawBillboard) {
    if (argCount != 5) { RETURN_NIL; }
    Camera3D camera = loxToCamera3D(vm, args[0]);
    Texture2D texture = loxToTexture2D(vm, args[1]);
    Vector3 center = loxToVector3(vm, args[2]);
    float size = (float)AS_NUMBER(args[3]);
    Color tint = loxToColor(vm, args[4]);

    DrawBillboard(camera, texture, center, size, tint);

    RETURN_NIL;
}

// Lox function for: void DrawBillboardRec(Camera3D camera, Texture2D texture, Rectangle sourceRec, Vector3 center, float size, Color tint);
LOX_FUNCTION(DrawBillboardRec) {
    if (argCount != 6) { RETURN_NIL; }
    Camera3D camera = loxToCamera3D(vm, args[0]);
    Texture2D texture = loxToTexture2D(vm, args[1]);
    Rectangle sourceRec = loxToRectangle(vm, args[2]);
    Vector3 center = loxToVector3(vm, args[3]);
    float size = (float)AS_NUMBER(args[4]);
    Color tint = loxToColor(vm, args[5]);

    DrawBillboardRec(camera, texture, sourceRec, center, size, tint);

    RETURN_NIL;
}

// Lox function for: bool CheckCollisionSpheres(Vector3 centerA, float radiusA, Vector3 centerB, float radiusB);
LOX_FUNCTION(CheckCollisionSpheres) {
    if (argCount != 4) { RETURN_NIL; }
    Vector3 centerA = loxToVector3(vm, args[0]);
    float radiusA = (float)AS_NUMBER(args[1]);
    Vector3 centerB = loxToVector3(vm, args[2]);
    float radiusB = (float)AS_NUMBER(args[3]);

    bool result = (bool)CheckCollisionSpheres(centerA, radiusA, centerB, radiusB);

    RETURN_BOOL(result);
}

// Lox function for: bool CheckCollisionBoxes(BoundingBox box1, BoundingBox box2);
LOX_FUNCTION(CheckCollisionBoxes) {
    if (argCount != 2) { RETURN_NIL; }
    BoundingBox box1 = loxToBoundingBox(vm, args[0]);
    BoundingBox box2 = loxToBoundingBox(vm, args[1]);

    bool result = (bool)CheckCollisionBoxes(box1, box2);

    RETURN_BOOL(result);
}

// Lox function for: bool CheckCollisionBoxSphere(BoundingBox box, Vector3 centerSphere, float radiusSphere);
LOX_FUNCTION(CheckCollisionBoxSphere) {
    if (argCount != 3) { RETURN_NIL; }
    BoundingBox box = loxToBoundingBox(vm, args[0]);
    Vector3 centerSphere = loxToVector3(vm, args[1]);
    float radiusSphere = (float)AS_NUMBER(args[2]);

    bool result = (bool)CheckCollisionBoxSphere(box, centerSphere, radiusSphere);

    RETURN_BOOL(result);
}

// Lox function for: bool CheckCollisionRaySphere(Ray ray, Vector3 spherePosition, float sphereRadius);
LOX_FUNCTION(CheckCollisionRaySphere) {
    if (argCount != 3) { RETURN_NIL; }
    Ray ray = loxToRay(vm, args[0]);
    Vector3 spherePosition = loxToVector3(vm, args[1]);
    float sphereRadius = (float)AS_NUMBER(args[2]);

    bool result = (bool)CheckCollisionRaySphere(ray, spherePosition, sphereRadius);

    RETURN_BOOL(result);
}

// Lox function for: bool CheckCollisionRaySphereEx(Ray ray, Vector3 spherePosition, float sphereRadius, Vector3* collisionPoint);
LOX_FUNCTION(CheckCollisionRaySphereEx) {
    if (argCount != 4) { RETURN_NIL; }
    Ray ray = loxToRay(vm, args[0]);
    Vector3 spherePosition = loxToVector3(vm, args[1]);
    float sphereRadius = (float)AS_NUMBER(args[2]);
    Vector3* collisionPoint = loxToVector3(vm, args[3]);

    bool result = (bool)CheckCollisionRaySphereEx(ray, spherePosition, sphereRadius, collisionPoint);

    RETURN_BOOL(result);
}

// Lox function for: bool CheckCollisionRayBox(Ray ray, BoundingBox box);
LOX_FUNCTION(CheckCollisionRayBox) {
    if (argCount != 2) { RETURN_NIL; }
    Ray ray = loxToRay(vm, args[0]);
    BoundingBox box = loxToBoundingBox(vm, args[1]);

    bool result = (bool)CheckCollisionRayBox(ray, box);

    RETURN_BOOL(result);
}

// Lox function for: RayHitInfo GetCollisionRayModel(Ray ray, Model* model);
LOX_FUNCTION(GetCollisionRayModel) {
    if (argCount != 2) { RETURN_NIL; }
    Ray ray = loxToRay(vm, args[0]);
    Model* model = loxToModel(vm, args[1]);

    RayHitInfo result = (RayHitInfo)GetCollisionRayModel(ray, model);

    RETURN_VAL(cToLoxRayHitInfo(vm, result));
}

// Lox function for: RayHitInfo GetCollisionRayTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3);
LOX_FUNCTION(GetCollisionRayTriangle) {
    if (argCount != 4) { RETURN_NIL; }
    Ray ray = loxToRay(vm, args[0]);
    Vector3 p1 = loxToVector3(vm, args[1]);
    Vector3 p2 = loxToVector3(vm, args[2]);
    Vector3 p3 = loxToVector3(vm, args[3]);

    RayHitInfo result = (RayHitInfo)GetCollisionRayTriangle(ray, p1, p2, p3);

    RETURN_VAL(cToLoxRayHitInfo(vm, result));
}

// Lox function for: RayHitInfo GetCollisionRayGround(Ray ray, float groundHeight);
LOX_FUNCTION(GetCollisionRayGround) {
    if (argCount != 2) { RETURN_NIL; }
    Ray ray = loxToRay(vm, args[0]);
    float groundHeight = (float)AS_NUMBER(args[1]);

    RayHitInfo result = (RayHitInfo)GetCollisionRayGround(ray, groundHeight);

    RETURN_VAL(cToLoxRayHitInfo(vm, result));
}

// Lox function for: Shader LoadShader(const char* vsFileName, const char* fsFileName);
LOX_FUNCTION(LoadShader) {
    if (argCount != 2) { RETURN_NIL; }
    const char* vsFileName = AS_CSTRING(args[0]);
    const char* fsFileName = AS_CSTRING(args[1]);

    Shader result = (Shader)LoadShader(vsFileName, fsFileName);

    RETURN_VAL(cToLoxShader(vm, result));
}

// Lox function for: void UnloadShader(Shader shader);
LOX_FUNCTION(UnloadShader) {
    if (argCount != 1) { RETURN_NIL; }
    Shader shader = loxToShader(vm, args[0]);

    UnloadShader(shader);

    RETURN_NIL;
}

// Lox function for: Shader GetShaderDefault(void);
LOX_FUNCTION(GetShaderDefault) {
    if (argCount != 0) { RETURN_NIL; }

    Shader result = (Shader)GetShaderDefault();

    RETURN_VAL(cToLoxShader(vm, result));
}

// Lox function for: Texture2D GetTextureDefault(void);
LOX_FUNCTION(GetTextureDefault) {
    if (argCount != 0) { RETURN_NIL; }

    Texture2D result = (Texture2D)GetTextureDefault();

    RETURN_VAL(cToLoxTexture2D(vm, result));
}

// Lox function for: int GetShaderLocation(Shader shader, const char* uniformName);
LOX_FUNCTION(GetShaderLocation) {
    if (argCount != 2) { RETURN_NIL; }
    Shader shader = loxToShader(vm, args[0]);
    const char* uniformName = AS_CSTRING(args[1]);

    int result = (int)GetShaderLocation(shader, uniformName);

    RETURN_NUMBER(result);
}

// Lox function for: void SetShaderValueMatrix(Shader shader, int uniformLoc, Matrix mat);
LOX_FUNCTION(SetShaderValueMatrix) {
    if (argCount != 3) { RETURN_NIL; }
    Shader shader = loxToShader(vm, args[0]);
    int uniformLoc = (int)AS_NUMBER(args[1]);
    Matrix mat = loxToMatrix(vm, args[2]);

    SetShaderValueMatrix(shader, uniformLoc, mat);

    RETURN_NIL;
}

// Lox function for: void SetShaderValueTexture(Shader shader, int uniformLoc, Texture2D texture);
LOX_FUNCTION(SetShaderValueTexture) {
    if (argCount != 3) { RETURN_NIL; }
    Shader shader = loxToShader(vm, args[0]);
    int uniformLoc = (int)AS_NUMBER(args[1]);
    Texture2D texture = loxToTexture2D(vm, args[2]);

    SetShaderValueTexture(shader, uniformLoc, texture);

    RETURN_NIL;
}

// Lox function for: void SetMatrixProjection(Matrix proj);
LOX_FUNCTION(SetMatrixProjection) {
    if (argCount != 1) { RETURN_NIL; }
    Matrix proj = loxToMatrix(vm, args[0]);

    SetMatrixProjection(proj);

    RETURN_NIL;
}

// Lox function for: void SetMatrixModelview(Matrix view);
LOX_FUNCTION(SetMatrixModelview) {
    if (argCount != 1) { RETURN_NIL; }
    Matrix view = loxToMatrix(vm, args[0]);

    SetMatrixModelview(view);

    RETURN_NIL;
}

// Lox function for: Matrix GetMatrixModelview();
LOX_FUNCTION(GetMatrixModelview) {
    if (argCount != 0) { RETURN_NIL; }

    Matrix result = (Matrix)GetMatrixModelview();

    RETURN_VAL(cToLoxMatrix(vm, result));
}

// Lox function for: void BeginShaderMode(Shader shader);
LOX_FUNCTION(BeginShaderMode) {
    if (argCount != 1) { RETURN_NIL; }
    Shader shader = loxToShader(vm, args[0]);

    BeginShaderMode(shader);

    RETURN_NIL;
}

// Lox function for: void EndShaderMode(void);
LOX_FUNCTION(EndShaderMode) {
    if (argCount != 0) { RETURN_NIL; }

    EndShaderMode();

    RETURN_NIL;
}

// Lox function for: void BeginBlendMode(int mode);
LOX_FUNCTION(BeginBlendMode) {
    if (argCount != 1) { RETURN_NIL; }
    int mode = (int)AS_NUMBER(args[0]);

    BeginBlendMode(mode);

    RETURN_NIL;
}

// Lox function for: void EndBlendMode(void);
LOX_FUNCTION(EndBlendMode) {
    if (argCount != 0) { RETURN_NIL; }

    EndBlendMode();

    RETURN_NIL;
}

// Lox function for: void BeginScissorMode(int x, int y, int width, int height);
LOX_FUNCTION(BeginScissorMode) {
    if (argCount != 4) { RETURN_NIL; }
    int x = (int)AS_NUMBER(args[0]);
    int y = (int)AS_NUMBER(args[1]);
    int width = (int)AS_NUMBER(args[2]);
    int height = (int)AS_NUMBER(args[3]);

    BeginScissorMode(x, y, width, height);

    RETURN_NIL;
}

// Lox function for: void EndScissorMode(void);
LOX_FUNCTION(EndScissorMode) {
    if (argCount != 0) { RETURN_NIL; }

    EndScissorMode();

    RETURN_NIL;
}

// Lox function for: void InitVrSimulator(void);
LOX_FUNCTION(InitVrSimulator) {
    if (argCount != 0) { RETURN_NIL; }

    InitVrSimulator();

    RETURN_NIL;
}

// Lox function for: void CloseVrSimulator(void);
LOX_FUNCTION(CloseVrSimulator) {
    if (argCount != 0) { RETURN_NIL; }

    CloseVrSimulator();

    RETURN_NIL;
}

// Lox function for: void UpdateVrTracking(Camera3D* camera);
LOX_FUNCTION(UpdateVrTracking) {
    if (argCount != 1) { RETURN_NIL; }
    Camera3D* camera = loxToCamera3D(vm, args[0]);

    UpdateVrTracking(camera);

    RETURN_NIL;
}

// Lox function for: void SetVrConfiguration(VrDeviceInfo info, Shader distortion);
LOX_FUNCTION(SetVrConfiguration) {
    if (argCount != 2) { RETURN_NIL; }
    VrDeviceInfo info = loxToVrDeviceInfo(vm, args[0]);
    Shader distortion = loxToShader(vm, args[1]);

    SetVrConfiguration(info, distortion);

    RETURN_NIL;
}

// Lox function for: bool IsVrSimulatorReady(void);
LOX_FUNCTION(IsVrSimulatorReady) {
    if (argCount != 0) { RETURN_NIL; }

    bool result = (bool)IsVrSimulatorReady();

    RETURN_BOOL(result);
}

// Lox function for: void ToggleVrMode(void);
LOX_FUNCTION(ToggleVrMode) {
    if (argCount != 0) { RETURN_NIL; }

    ToggleVrMode();

    RETURN_NIL;
}

// Lox function for: void BeginVrDrawing(void);
LOX_FUNCTION(BeginVrDrawing) {
    if (argCount != 0) { RETURN_NIL; }

    BeginVrDrawing();

    RETURN_NIL;
}

// Lox function for: void EndVrDrawing(void);
LOX_FUNCTION(EndVrDrawing) {
    if (argCount != 0) { RETURN_NIL; }

    EndVrDrawing();

    RETURN_NIL;
}

// Lox function for: void InitAudioDevice(void);
LOX_FUNCTION(InitAudioDevice) {
    if (argCount != 0) { RETURN_NIL; }

    InitAudioDevice();

    RETURN_NIL;
}

// Lox function for: void CloseAudioDevice(void);
LOX_FUNCTION(CloseAudioDevice) {
    if (argCount != 0) { RETURN_NIL; }

    CloseAudioDevice();

    RETURN_NIL;
}

// Lox function for: bool IsAudioDeviceReady(void);
LOX_FUNCTION(IsAudioDeviceReady) {
    if (argCount != 0) { RETURN_NIL; }

    bool result = (bool)IsAudioDeviceReady();

    RETURN_BOOL(result);
}

// Lox function for: void SetMasterVolume(float volume);
LOX_FUNCTION(SetMasterVolume) {
    if (argCount != 1) { RETURN_NIL; }
    float volume = (float)AS_NUMBER(args[0]);

    SetMasterVolume(volume);

    RETURN_NIL;
}

// Lox function for: Wave LoadWave(const char* fileName);
LOX_FUNCTION(LoadWave) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    Wave result = (Wave)LoadWave(fileName);

    RETURN_VAL(cToLoxWave(vm, result));
}

// Lox function for: Sound LoadSound(const char* fileName);
LOX_FUNCTION(LoadSound) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    Sound result = (Sound)LoadSound(fileName);

    RETURN_VAL(cToLoxSound(vm, result));
}

// Lox function for: Sound LoadSoundFromWave(Wave wave);
LOX_FUNCTION(LoadSoundFromWave) {
    if (argCount != 1) { RETURN_NIL; }
    Wave wave = loxToWave(vm, args[0]);

    Sound result = (Sound)LoadSoundFromWave(wave);

    RETURN_VAL(cToLoxSound(vm, result));
}

// Lox function for: void UnloadWave(Wave wave);
LOX_FUNCTION(UnloadWave) {
    if (argCount != 1) { RETURN_NIL; }
    Wave wave = loxToWave(vm, args[0]);

    UnloadWave(wave);

    RETURN_NIL;
}

// Lox function for: void UnloadSound(Sound sound);
LOX_FUNCTION(UnloadSound) {
    if (argCount != 1) { RETURN_NIL; }
    Sound sound = loxToSound(vm, args[0]);

    UnloadSound(sound);

    RETURN_NIL;
}

// Lox function for: void ExportWave(Wave wave, const char* fileName);
LOX_FUNCTION(ExportWave) {
    if (argCount != 2) { RETURN_NIL; }
    Wave wave = loxToWave(vm, args[0]);
    const char* fileName = AS_CSTRING(args[1]);

    ExportWave(wave, fileName);

    RETURN_NIL;
}

// Lox function for: void ExportWaveAsCode(Wave wave, const char* fileName);
LOX_FUNCTION(ExportWaveAsCode) {
    if (argCount != 2) { RETURN_NIL; }
    Wave wave = loxToWave(vm, args[0]);
    const char* fileName = AS_CSTRING(args[1]);

    ExportWaveAsCode(wave, fileName);

    RETURN_NIL;
}

// Lox function for: void PlaySound(Sound sound);
LOX_FUNCTION(PlaySound) {
    if (argCount != 1) { RETURN_NIL; }
    Sound sound = loxToSound(vm, args[0]);

    PlaySound(sound);

    RETURN_NIL;
}

// Lox function for: void PauseSound(Sound sound);
LOX_FUNCTION(PauseSound) {
    if (argCount != 1) { RETURN_NIL; }
    Sound sound = loxToSound(vm, args[0]);

    PauseSound(sound);

    RETURN_NIL;
}

// Lox function for: void ResumeSound(Sound sound);
LOX_FUNCTION(ResumeSound) {
    if (argCount != 1) { RETURN_NIL; }
    Sound sound = loxToSound(vm, args[0]);

    ResumeSound(sound);

    RETURN_NIL;
}

// Lox function for: void StopSound(Sound sound);
LOX_FUNCTION(StopSound) {
    if (argCount != 1) { RETURN_NIL; }
    Sound sound = loxToSound(vm, args[0]);

    StopSound(sound);

    RETURN_NIL;
}

// Lox function for: bool IsSoundPlaying(Sound sound);
LOX_FUNCTION(IsSoundPlaying) {
    if (argCount != 1) { RETURN_NIL; }
    Sound sound = loxToSound(vm, args[0]);

    bool result = (bool)IsSoundPlaying(sound);

    RETURN_BOOL(result);
}

// Lox function for: void SetSoundVolume(Sound sound, float volume);
LOX_FUNCTION(SetSoundVolume) {
    if (argCount != 2) { RETURN_NIL; }
    Sound sound = loxToSound(vm, args[0]);
    float volume = (float)AS_NUMBER(args[1]);

    SetSoundVolume(sound, volume);

    RETURN_NIL;
}

// Lox function for: void SetSoundPitch(Sound sound, float pitch);
LOX_FUNCTION(SetSoundPitch) {
    if (argCount != 2) { RETURN_NIL; }
    Sound sound = loxToSound(vm, args[0]);
    float pitch = (float)AS_NUMBER(args[1]);

    SetSoundPitch(sound, pitch);

    RETURN_NIL;
}

// Lox function for: void WaveFormat(Wave* wave, int sampleRate, int sampleSize, int channels);
LOX_FUNCTION(WaveFormat) {
    if (argCount != 4) { RETURN_NIL; }
    Wave* wave = loxToWave(vm, args[0]);
    int sampleRate = (int)AS_NUMBER(args[1]);
    int sampleSize = (int)AS_NUMBER(args[2]);
    int channels = (int)AS_NUMBER(args[3]);

    WaveFormat(wave, sampleRate, sampleSize, channels);

    RETURN_NIL;
}

// Lox function for: Wave WaveCopy(Wave wave);
LOX_FUNCTION(WaveCopy) {
    if (argCount != 1) { RETURN_NIL; }
    Wave wave = loxToWave(vm, args[0]);

    Wave result = (Wave)WaveCopy(wave);

    RETURN_VAL(cToLoxWave(vm, result));
}

// Lox function for: void WaveCrop(Wave* wave, int initSample, int finalSample);
LOX_FUNCTION(WaveCrop) {
    if (argCount != 3) { RETURN_NIL; }
    Wave* wave = loxToWave(vm, args[0]);
    int initSample = (int)AS_NUMBER(args[1]);
    int finalSample = (int)AS_NUMBER(args[2]);

    WaveCrop(wave, initSample, finalSample);

    RETURN_NIL;
}

// Lox function for: Music LoadMusicStream(const char* fileName);
LOX_FUNCTION(LoadMusicStream) {
    if (argCount != 1) { RETURN_NIL; }
    const char* fileName = AS_CSTRING(args[0]);

    Music result = (Music)LoadMusicStream(fileName);

    RETURN_VAL(cToLoxMusic(vm, result));
}

// Lox function for: void UnloadMusicStream(Music music);
LOX_FUNCTION(UnloadMusicStream) {
    if (argCount != 1) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);

    UnloadMusicStream(music);

    RETURN_NIL;
}

// Lox function for: void PlayMusicStream(Music music);
LOX_FUNCTION(PlayMusicStream) {
    if (argCount != 1) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);

    PlayMusicStream(music);

    RETURN_NIL;
}

// Lox function for: void UpdateMusicStream(Music music);
LOX_FUNCTION(UpdateMusicStream) {
    if (argCount != 1) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);

    UpdateMusicStream(music);

    RETURN_NIL;
}

// Lox function for: void StopMusicStream(Music music);
LOX_FUNCTION(StopMusicStream) {
    if (argCount != 1) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);

    StopMusicStream(music);

    RETURN_NIL;
}

// Lox function for: void PauseMusicStream(Music music);
LOX_FUNCTION(PauseMusicStream) {
    if (argCount != 1) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);

    PauseMusicStream(music);

    RETURN_NIL;
}

// Lox function for: void ResumeMusicStream(Music music);
LOX_FUNCTION(ResumeMusicStream) {
    if (argCount != 1) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);

    ResumeMusicStream(music);

    RETURN_NIL;
}

// Lox function for: bool IsMusicPlaying(Music music);
LOX_FUNCTION(IsMusicPlaying) {
    if (argCount != 1) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);

    bool result = (bool)IsMusicPlaying(music);

    RETURN_BOOL(result);
}

// Lox function for: void SetMusicVolume(Music music, float volume);
LOX_FUNCTION(SetMusicVolume) {
    if (argCount != 2) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);
    float volume = (float)AS_NUMBER(args[1]);

    SetMusicVolume(music, volume);

    RETURN_NIL;
}

// Lox function for: void SetMusicPitch(Music music, float pitch);
LOX_FUNCTION(SetMusicPitch) {
    if (argCount != 2) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);
    float pitch = (float)AS_NUMBER(args[1]);

    SetMusicPitch(music, pitch);

    RETURN_NIL;
}

// Lox function for: void SetMusicLoopCount(Music music, int count);
LOX_FUNCTION(SetMusicLoopCount) {
    if (argCount != 2) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);
    int count = (int)AS_NUMBER(args[1]);

    SetMusicLoopCount(music, count);

    RETURN_NIL;
}

// Lox function for: float GetMusicTimeLength(Music music);
LOX_FUNCTION(GetMusicTimeLength) {
    if (argCount != 1) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);

    float result = (float)GetMusicTimeLength(music);

    RETURN_NUMBER(result);
}

// Lox function for: float GetMusicTimePlayed(Music music);
LOX_FUNCTION(GetMusicTimePlayed) {
    if (argCount != 1) { RETURN_NIL; }
    Music music = loxToMusic(vm, args[0]);

    float result = (float)GetMusicTimePlayed(music);

    RETURN_NUMBER(result);
}

// Lox function for: AudioStream InitAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels);
LOX_FUNCTION(InitAudioStream) {
    if (argCount != 3) { RETURN_NIL; }
    unsigned int sampleRate = (unsigned int)AS_NUMBER(args[0]);
    unsigned int sampleSize = (unsigned int)AS_NUMBER(args[1]);
    unsigned int channels = (unsigned int)AS_NUMBER(args[2]);

    AudioStream result = (AudioStream)InitAudioStream(sampleRate, sampleSize, channels);

    RETURN_VAL(cToLoxAudioStream(vm, result));
}

// Lox function for: void CloseAudioStream(AudioStream stream);
LOX_FUNCTION(CloseAudioStream) {
    if (argCount != 1) { RETURN_NIL; }
    AudioStream stream = loxToAudioStream(vm, args[0]);

    CloseAudioStream(stream);

    RETURN_NIL;
}

// Lox function for: bool IsAudioBufferProcessed(AudioStream stream);
LOX_FUNCTION(IsAudioBufferProcessed) {
    if (argCount != 1) { RETURN_NIL; }
    AudioStream stream = loxToAudioStream(vm, args[0]);

    bool result = (bool)IsAudioBufferProcessed(stream);

    RETURN_BOOL(result);
}

// Lox function for: void PlayAudioStream(AudioStream stream);
LOX_FUNCTION(PlayAudioStream) {
    if (argCount != 1) { RETURN_NIL; }
    AudioStream stream = loxToAudioStream(vm, args[0]);

    PlayAudioStream(stream);

    RETURN_NIL;
}

// Lox function for: void PauseAudioStream(AudioStream stream);
LOX_FUNCTION(PauseAudioStream) {
    if (argCount != 1) { RETURN_NIL; }
    AudioStream stream = loxToAudioStream(vm, args[0]);

    PauseAudioStream(stream);

    RETURN_NIL;
}

// Lox function for: void ResumeAudioStream(AudioStream stream);
LOX_FUNCTION(ResumeAudioStream) {
    if (argCount != 1) { RETURN_NIL; }
    AudioStream stream = loxToAudioStream(vm, args[0]);

    ResumeAudioStream(stream);

    RETURN_NIL;
}

// Lox function for: bool IsAudioStreamPlaying(AudioStream stream);
LOX_FUNCTION(IsAudioStreamPlaying) {
    if (argCount != 1) { RETURN_NIL; }
    AudioStream stream = loxToAudioStream(vm, args[0]);

    bool result = (bool)IsAudioStreamPlaying(stream);

    RETURN_BOOL(result);
}

// Lox function for: void StopAudioStream(AudioStream stream);
LOX_FUNCTION(StopAudioStream) {
    if (argCount != 1) { RETURN_NIL; }
    AudioStream stream = loxToAudioStream(vm, args[0]);

    StopAudioStream(stream);

    RETURN_NIL;
}

// Lox function for: void SetAudioStreamVolume(AudioStream stream, float volume);
LOX_FUNCTION(SetAudioStreamVolume) {
    if (argCount != 2) { RETURN_NIL; }
    AudioStream stream = loxToAudioStream(vm, args[0]);
    float volume = (float)AS_NUMBER(args[1]);

    SetAudioStreamVolume(stream, volume);

    RETURN_NIL;
}

// Lox function for: void SetAudioStreamPitch(AudioStream stream, float pitch);
LOX_FUNCTION(SetAudioStreamPitch) {
    if (argCount != 2) { RETURN_NIL; }
    AudioStream stream = loxToAudioStream(vm, args[0]);
    float pitch = (float)AS_NUMBER(args[1]);

    SetAudioStreamPitch(stream, pitch);

    RETURN_NIL;
}


