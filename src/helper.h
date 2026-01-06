#pragma once


extern Vector2 loxToVector2(VM* vm,Value value);
extern Vector3 loxToVector3(VM* vm,Value value);
extern Vector4 loxToVector4(VM* vm,Value value);
extern Matrix loxToMatrix(VM* vm,Value value);
extern Color loxToColor(VM* vm,Value value);
extern Rectangle loxToRectangle(VM* vm,Value value);
extern Image loxToImage(VM* vm,Value value);
extern Camera2D loxToCamera2D(VM* vm, Value value);
extern Camera3D loxToCamera3D(VM* vm, Value value);

//------------------------------------------------------------------------------------------------------------------
//これらの関数は、raylibの関数が返したCの構造体を、 Loxのスクリプトが扱えるインスタンスに変換します。 
//------------------------------------------------------------------------------------------------------------------
Value cToLoxVector2(VM* vm,Vector2 vec);
Value cToLoxVector3(VM* vm,Vector3 vec);
Value cToLoxVector4(VM* vm, Vector4 vec);
Value cToLoxColor(VM* vm, Color color);
Value cToLoxRectangle(VM* vm, Rectangle rect);
Value cToLoxImage(VM* vm,Image image);
Value cToLox(VM* vm, const char* type, void* data);
Value cToLoxCamera2D(VM* vm, Camera2D camera);
Value cToLoxCamera3D(VM* vm, Camera3D camera);
