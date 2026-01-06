#define NOGDI // Rectangle の衝突を回避
#define NOWINMESSAGES // CloseWindow などの衝突を回避

#include "common/common.h"
#include "vm/assert.h"
#include "ray_bind.h"


static Value InitWindowNativeFunction(VM* vm, int argCount, Value* args) {
	// 引数の数をチェック (width, height, title の3つ)
	if (argCount != 3) {
		// 【訂正箇所】runtimeErrorにvmを渡す
		runtimeError(vm, "Expected 3 arguments but got %d.", argCount);
		return NIL_VAL;
	}

	// 第2引数(height)と第1引数(width)が数値であることを確認
	if (!IS_NUMBER(args[1]) || !IS_NUMBER(args[0])) {
		// 【訂正箇所】runtimeErrorにvmを渡す
		runtimeError(vm, "Window width and height must be numbers.");
		return NIL_VAL;
	}

	// 第3引数(title)が文字列であることを確認
	if (!IS_STRING(args[2])) {
		// 【訂正箇所】runtimeErrorにvmを渡す
		runtimeError(vm, "Window title must be a string.");
		return NIL_VAL;
	}

	// Lox2のValue型からC言語の型へ変換
	int width = AS_NUMBER(args[0]);
	int height = AS_NUMBER(args[1]);
	const char* title = AS_CSTRING(args[2]);

	// RaylibのInitWindow関数を呼び出す
	InitWindow(width, height, title);

	// Lox2には何も返さない (nil)
	return NIL_VAL;
}

static Value DrawTextNativeFunction(VM* vm, int argCount, Value* args) {
	// 引数の型チェック (text, x, y, fontSize, color)
	if (!IS_STRING(args[0])) {
		runtimeError(vm, "Argument 1 must be a string for the text.");
		return NIL_VAL;
	}
	if (!IS_NUMBER(args[1]) || !IS_NUMBER(args[2]) || !IS_NUMBER(args[3])) {
		runtimeError(vm, "Arguments 2, 3, and 4 (position and font size) must be numbers.");
		return NIL_VAL;
	}

	// Lox2のValueをCの型に変換
	const char* text = AS_CSTRING(args[0]);
	int posX = (int)AS_NUMBER(args[1]);
	int posY = (int)AS_NUMBER(args[2]);
	int fontSize = (int)AS_NUMBER(args[3]);

	Color color;
	// ヘルパー関数を使ってColorを取得
	if (!valueToColor(vm, args[4], &color)) {
		return NIL_VAL; // valueToColor内でエラーメッセージは出力済み
	}

	// RaylibのDrawText関数を呼び出す
	DrawText(text, posX, posY, fontSize, color);

	return NIL_VAL;
}

LOX_FUNCTION(SetTargetFPS){
	ASSERT_ARG_COUNT("SetTargetFPS(message)", 1);
	int fps = (int)AS_NUMBER(args[0]);
	SetTargetFPS(fps);
	RETURN_NIL;
}

LOX_FUNCTION(BeginDrawing){
	ASSERT_ARG_COUNT("BeginDrawing(message)", 0);
	BeginDrawing();
	RETURN_NIL;
}

LOX_FUNCTION(EndDrawing){
	ASSERT_ARG_COUNT("EndDrawing(message)", 0);
	EndDrawing();
	RETURN_NIL;
}

LOX_FUNCTION(CloseWindow){
	ASSERT_ARG_COUNT("CloseWindow(message)", 0);
	CloseWindow();
	RETURN_NIL;
}

LOX_FUNCTION(WindowShouldClose){
	ASSERT_ARG_COUNT("WindowShouldClose(message)", 0);
	bool ret = WindowShouldClose();
	RETURN_BOOL(ret);
}

static Value ClearBackgroundNativeFunction(VM* vm, int argCount, Value* args) {

	Color color;
	// ヘルパー関数を使ってColorを取得
	if (!valueToColor(vm, args[0], &color)) {
		return NIL_VAL; // valueToColor内でエラーメッセージは出力済み
	}
	ClearBackground(color);
	RETURN_NIL;

}

static Value GetMousePositionNativeFunction(VM* vm, int argCount, Value* args) {
	// --- 引数チェック ---
	if (argCount != 0) {
		runtimeError(vm, "GetMousePosition() expects no arguments.");
		RETURN_NIL;
	}

	// --- Raylibの関数を呼び出す ---
	Vector2 v = GetMousePosition();

	// --- Vector2クラスの新しいインスタンスを生成 ---
	// newInstance は、指定されたクラスの空のインスタンスを作成するヘルパー関数
	ObjInstance* instance = newInstance(vm, vector2Class);

	// --- インスタンスにプロパティを設定 ---
	// setObjProperty は、インスタンス、プロパティ名(char*)、値(Value) を取る
	setObjProperty(vm, instance, "x", NUMBER_VAL(v.x));
	setObjProperty(vm, instance, "y", NUMBER_VAL(v.y));

	// --- 作成したインスタンスを返す ---
	RETURN_OBJ(instance);
}







static Value GetRayCollisionBoxNativeFunction(VM* vm, int argCount, Value* args) {
	// --- 1. 引数の数をチェック ---
	if (argCount != 2) {
		runtimeError(vm, "GetRayCollisionBox() expects 2 arguments (Ray, BoundingBox).");
		RETURN_NIL;
	}

	// --- 2. Loxの引数をCの構造体に変換 ---
	Ray ray;
	BoundingBox box;

	// 第1引数をRayに変換
	if (!valueToRay(vm, args[0], &ray)) {
		runtimeError(vm, "Argument 1 must be a Ray object.");
		RETURN_NIL;
	}

	// 第2引数をBoundingBoxに変換
	if (!valueToBoundingBox(vm, args[1], &box)) {
		runtimeError(vm, "Argument 2 must be a BoundingBox object.");
		RETURN_NIL;
	}

	// --- 3. Raylibの関数を呼び出す ---
	RayCollision result = GetRayCollisionBox(ray, box);

	// --- 4. Cの戻り値をLoxのオブジェクトに変換して返す ---
	ObjInstance* resultInstance = newRayCollisionInstance(vm, result);
	RETURN_OBJ(resultInstance);
}

LOX_FUNCTION(IsCursorHidden){
	ASSERT_ARG_COUNT("IsCursorHidden(message)", 0);
	bool ret = IsCursorHidden();
	RETURN_BOOL(ret);
}

LOX_FUNCTION(EnableCursor){
	ASSERT_ARG_COUNT("EnableCursor(message)", 0);
	EnableCursor();
	RETURN_NIL;
}

LOX_FUNCTION(DisableCursor){
	ASSERT_ARG_COUNT("DisableCursor(message)", 0);
	DisableCursor();
	RETURN_NIL;
}

static Value DrawCubeNativeFunction(VM* vm, int argCount, Value* args) {


	// Lox2のValueをCの型に変換
	// ヘルパー関数を使ってColorを取得
	Vector3 v;
	if (!valueToVector3(vm, args[0], &v)) {
		return NIL_VAL; // valueToColor内でエラーメッセージは出力済み
	}

	float width = (float)AS_FLOAT(args[1]);
	float height = (float)AS_FLOAT(args[2]);
	float length = (float)AS_FLOAT(args[3]);

	Color color;
	// ヘルパー関数を使ってColorを取得
	if (!valueToColor(vm, args[4], &color)) {
		return NIL_VAL; // valueToColor内でエラーメッセージは出力済み
	}

	// RaylibのDrawText関数を呼び出す
	DrawCube(v, width, height, length, color);

	return NIL_VAL;
}

static Value DrawCubeWiresNativeFunction(VM* vm, int argCount, Value* args) {


	// Lox2のValueをCの型に変換
	// ヘルパー関数を使ってColorを取得
	Vector3 v;
	if (!valueToVector3(vm, args[0], &v)) {
		return NIL_VAL; // valueToColor内でエラーメッセージは出力済み
	}

	float width = (float)AS_FLOAT(args[1]);
	float height = (float)AS_FLOAT(args[2]);
	float length = (float)AS_FLOAT(args[3]);

	Color color;
	// ヘルパー関数を使ってColorを取得
	if (!valueToColor(vm, args[4], &color)) {
		return NIL_VAL; // valueToColor内でエラーメッセージは出力済み
	}

	// RaylibのDrawText関数を呼び出す
	DrawCubeWires(v, width, height, length, color);

	return NIL_VAL;
}

static Value BeginMode3DNativeFunction(VM* vm, int argCount, Value* args) {
	Camera3D camera;
	if (!valueToCamera3D(vm, args[0], &camera)) {
		return NIL_VAL; // valueToColor内でエラーメッセージは出力済み
	}
	BeginMode3D(camera);
	return NIL_VAL;
}

LOX_FUNCTION(EndMode3D){
	ASSERT_ARG_COUNT("EndMode3D(message)", 0);
	EndMode3D();
	RETURN_NIL;
}

static Value IsMouseButtonPressedNativeFunction(VM* vm, int argCount, Value* args) {
	int button = (int)AS_NUMBER(args[0]);

	bool ret = IsMouseButtonPressed(button);
	RETURN_BOOL(ret);
}

static Value DrawRayNativeFunction(VM* vm, int argCount, Value* args) {

	Ray ray;
	if (!valueToRay(vm, args[0], &ray)) {
		return NIL_VAL;
	}

	Color color;
	// ヘルパー関数を使ってColorを取得
	if (!valueToColor(vm, args[1], &color)) {
		return NIL_VAL; // valueToColor内でエラーメッセージは出力済み
	}
	
	DrawRay( ray, color);                                                                // Draw a ray line

	RETURN_NIL;
}

static Value DrawGridNativeFunction(VM* vm, int argCount, Value* args) {

	int slices = (int)AS_INT(args[0]);
	float spacing = (int)AS_FLOAT(args[1]);

	DrawGrid( slices, spacing);                                                          // Draw a grid (centered at (0, 0, 0))

	RETURN_NIL;
}

static Value UpdateCameraNativeFunction(VM* vm, int argCount, Value* args) {
	Camera camera;
	if (!valueToCamera3D(vm, args[0], &camera)) {
		return NIL_VAL;
	}

	int mode = (int)AS_INT(args[1]);
	UpdateCamera(&camera, mode);

	RETURN_NIL;
}

static Value GetScreenToWorldRayNativeFunction(VM* vm, int argCount, Value* args) {
	// --- 1. 引数の数をチェック ---
	if (argCount != 2) {
		runtimeError(vm, "GetScreenToWorldRay() expects 2 arguments (Vector2, Camera).");
		RETURN_NIL;
	}

	// --- 2. Loxの引数をCの構造体に変換 ---
	Vector2 position;
	Camera3D camera;

	// 第1引数をVector2に変換
	// (valueToVector2はvalueToVector3と同様の実装と仮定)
	if (!valueToVector2(vm, args[0], &position)) {
		runtimeError(vm, "Argument 1 must be a Vector2 object.");
		RETURN_NIL;
	}

	// 第2引数をCamera3Dに変換
	if (!valueToCamera3D(vm, args[1], &camera)) {
		// valueToCamera3Dが詳細なエラーメッセージを設定してくれる
		RETURN_NIL;
	}

	// --- 3. Raylibの関数を呼び出す ---
	Ray resultRay = GetScreenToWorldRay(position, camera);

	// --- 4. Cの戻り値をLoxのRayオブジェクトに変換して返す ---
	ObjInstance* resultInstance = newRayInstance(vm, resultRay);
	if (resultInstance == NULL) {
		// newRayInstance内でエラーが発生した場合
		RETURN_NIL;
	}

	RETURN_OBJ(resultInstance);
}

static Value MeasureTextNativeFunction(VM* vm, int argCount, Value* args) {
	const char *text = (const char *)AS_OBJ(args[0]);
	int fontSize = (int)AS_INT(args[1]);

	int ret = MeasureText(text, fontSize);
	RETURN_NUMBER(ret);
}

static Value DrawFPSNativeFunction(VM* vm, int argCount, Value* args) {
	int posX = (int)AS_INT(args[0]);
	int posY = (int)AS_INT(args[1]);

	DrawFPS( posX, posY);                                                          // Draw a grid (centered at (0, 0, 0))

	RETURN_NIL;
}

/*
LOX_FUNCTION(print){
ASSERT_ARG_COUNT("print(message)", 1);
printValue(args[0]);
RETURN_NIL;
}
*/

void registerRaylibFunctions(VM* vm){
	DEF_FUNCTION(InitWindow, 3, RETURN_TYPE(void), PARAM_TYPE(Number), PARAM_TYPE(Number), PARAM_TYPE(String));
	DEF_FUNCTION(DrawText, 5, RETURN_TYPE(void), PARAM_TYPE(String), PARAM_TYPE(Number), PARAM_TYPE(Number), PARAM_TYPE(Number), PARAM_TYPE(Object));
	
	DEF_FUNCTION(SetTargetFPS, 1 ,RETURN_TYPE(void), PARAM_TYPE(Number) );

	DEF_FUNCTION(BeginDrawing, 0 ,RETURN_TYPE(void) );
	DEF_FUNCTION(EndDrawing, 0 ,RETURN_TYPE(void) );
	DEF_FUNCTION(CloseWindow, 0 ,RETURN_TYPE(void) );
	DEF_FUNCTION(WindowShouldClose, 0 ,RETURN_TYPE(Bool) );

	DEF_FUNCTION(ClearBackground, 1 ,RETURN_TYPE(void), PARAM_TYPE(Object) );

	DEF_FUNCTION(GetMousePosition, 0 ,RETURN_TYPE(Object) );
	DEF_FUNCTION(GetRayCollisionBox, 2 ,RETURN_TYPE(Object), PARAM_TYPE(Object), PARAM_TYPE(Object) );

	DEF_FUNCTION(IsCursorHidden, 0 ,RETURN_TYPE(Bool) );
	DEF_FUNCTION(EnableCursor, 0 ,RETURN_TYPE(void) );
	DEF_FUNCTION(DisableCursor, 0 ,RETURN_TYPE(void) );

	DEF_FUNCTION(DrawCube, 5 ,RETURN_TYPE(void), PARAM_TYPE(Object), PARAM_TYPE(Number), PARAM_TYPE(Number), PARAM_TYPE(Number), PARAM_TYPE(Object) );
	DEF_FUNCTION(DrawCubeWires, 5 ,RETURN_TYPE(void), PARAM_TYPE(Object), PARAM_TYPE(Number), PARAM_TYPE(Number), PARAM_TYPE(Number), PARAM_TYPE(Object) );

	DEF_FUNCTION(BeginMode3D , 1 ,RETURN_TYPE(void), PARAM_TYPE(Object));
	DEF_FUNCTION(EndMode3D, 0, RETURN_TYPE(void));

	DEF_FUNCTION(IsMouseButtonPressed, 1, RETURN_TYPE(Bool), PARAM_TYPE(Number));

	DEF_FUNCTION(DrawRay, 2, RETURN_TYPE(void), PARAM_TYPE(Object), PARAM_TYPE(Object));
	DEF_FUNCTION(DrawGrid, 2, RETURN_TYPE(void), PARAM_TYPE(Number), PARAM_TYPE(Number));

	DEF_FUNCTION(UpdateCamera, 2, RETURN_TYPE(void), PARAM_TYPE(Object), PARAM_TYPE(Number));
	DEF_FUNCTION(GetScreenToWorldRay, 2, RETURN_TYPE(Object), PARAM_TYPE(Object), PARAM_TYPE(Object));
	DEF_FUNCTION(MeasureText, 2, RETURN_TYPE(Number), PARAM_TYPE(Object), PARAM_TYPE(Number));
	DEF_FUNCTION(DrawFPS, 2, RETURN_TYPE(void), PARAM_TYPE(Number), PARAM_TYPE(Number));

}

