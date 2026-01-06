#pragma once

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
#include "clox_raylib.h"  // <-- ‚±‚ê‚ğ’Ç‰Á

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
#define PlaySound      rl_PlaySound
#include <raylib.h>  // include raylib here <---

extern ObjClass* vector2Class;
extern ObjClass* vector3Class;
extern ObjClass* rayCollisionClass;
extern ObjClass* rayClass;

extern ObjInstance* newVector3Instance(VM* vm, Vector3 vec);
extern ObjInstance* newRayCollisionInstance(VM* vm, RayCollision collision);
extern ObjInstance* newRayInstance(VM* vm, Ray ray);
