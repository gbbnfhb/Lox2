#include "ray_bind.h"

bool valueToVector2(VM* vm, Value value, Vector2* vec) {
	// 1. Valueがインスタンスでなければ、変換不可能
	if (!IS_INSTANCE(value)) {
		// この関数自体はエラーメッセージを出さず、呼び出し元に判断を委ねるのが一般的
		return false;
	}
	ObjInstance* instance = AS_INSTANCE(value);

	// (任意だが推奨) インスタンスが本当にVector3クラスのものかチェック
	// if (instance->klass != vector3Class) {
	//     return false;
	// }

	// 2. getObjPropertyを使ってx, y, zの各プロパティを取得
	Value xVal = getObjProperty(vm, instance, "x");
	Value yVal = getObjProperty(vm, instance, "y");
//	Value zVal = getObjProperty(vm, instance, "z");

	// 3. 取得した各Valueが数値(Number)であるかチェック
	if (!IS_NUMBER(xVal) || !IS_NUMBER(yVal) /*|| !IS_NUMBER(zVal)*/) {
		// プロパティが存在しない(NIL)か、型が違う場合はエラー
		runtimeError(vm, "Vector3 object properties 'x', 'y', 'z' must be numbers.");
		return false;
	}

	// 4. ValueをCのdouble/floatに変換し、Vector3構造体に設定
	vec->x = AS_NUMBER(xVal);
	vec->y = AS_NUMBER(yVal);
//	vec->z = AS_NUMBER(zVal);

	return true;
}

bool valueToVector3(VM* vm, Value value, Vector3* vec) {
	// 1. Valueがインスタンスでなければ、変換不可能
	if (!IS_INSTANCE(value)) {
		// この関数自体はエラーメッセージを出さず、呼び出し元に判断を委ねるのが一般的
		return false;
	}
	ObjInstance* instance = AS_INSTANCE(value);

	// (任意だが推奨) インスタンスが本当にVector3クラスのものかチェック
	// if (instance->klass != vector3Class) {
	//     return false;
	// }

	// 2. getObjPropertyを使ってx, y, zの各プロパティを取得
	Value xVal = getObjProperty(vm, instance, "x");
	Value yVal = getObjProperty(vm, instance, "y");
	Value zVal = getObjProperty(vm, instance, "z");

	// 3. 取得した各Valueが数値(Number)であるかチェック
	if (!IS_NUMBER(xVal) || !IS_NUMBER(yVal) || !IS_NUMBER(zVal)) {
		// プロパティが存在しない(NIL)か、型が違う場合はエラー
		runtimeError(vm, "Vector3 object properties 'x', 'y', 'z' must be numbers.");
		return false;
	}

	// 4. ValueをCのdouble/floatに変換し、Vector3構造体に設定
	vec->x = AS_NUMBER(xVal);
	vec->y = AS_NUMBER(yVal);
	vec->z = AS_NUMBER(zVal);

	return true;
}

// LoxのValueからCのBoundingBox構造体に変換するヘルパー関数
bool valueToBoundingBox(VM* vm, Value value, BoundingBox* box) {
	if (!IS_INSTANCE(value)) return false;
	ObjInstance* instance = AS_INSTANCE(value);

	Value minVal, maxVal;
	Vector3 min, max;

	minVal = getObjProperty(vm, instance, "min"); 
	if (!valueToVector3(vm, minVal, &min)) {
		runtimeError(vm, "BoundingBox object must have a 'min' property of type Vector3.");
		return false;
	}

	maxVal = getObjProperty(vm, instance, "max");
	if ( !valueToVector3(vm, maxVal, &max)) {
		runtimeError(vm, "BoundingBox object must have a 'max' property of type Vector3.");
		return false;
	}

	box->min = min;
	box->max = max;
	return true;
}

bool valueToRay(VM* vm, Value value, Ray* ray) {
	if (!IS_INSTANCE(value)) return false;
	ObjInstance* instance = AS_INSTANCE(value);

	// Rayクラスのインスタンスかチェック (任意だが推奨)
	// if (instance->klass != rayClass) return false;

	Value positionVal, directionVal;
	Vector3 position, direction;

	// "position"プロパティを取得してVector3に変換
	positionVal = getObjProperty(vm, instance, "position");
	if (!valueToVector3(vm, positionVal, &position)) {
		runtimeError(vm, "Ray object must have a 'position' property of type Vector3.");
		return false;
	}

	// "direction"プロパティを取得してVector3に変換
	directionVal = getObjProperty(vm, instance, "direction"); 
	if (!valueToVector3(vm, directionVal, &direction)) {
		runtimeError(vm, "Ray object must have a 'direction' property of type Vector3.");
		return false;
	}

	ray->position = position;
	ray->direction = direction;
	return true;
}


bool valueToColor(VM* vm, Value value, Color* color) {
	// 1. まず、渡されたValueがインスタンスであることを確認
	if (!IS_INSTANCE(value)) {
		runtimeError(vm, "Expected a Color object, but got a non-instance value.");
		return false;
	}
	ObjInstance* instance = AS_INSTANCE(value);


	// 3. インスタンスから "r", "g", "b", "a" のプロパティを取得
	Value rVal, gVal, bVal, aVal;
	rVal = getObjProperty(vm, instance, "r");
	gVal = getObjProperty(vm, instance, "g");
	bVal = getObjProperty(vm, instance, "b");
	aVal = getObjProperty(vm, instance, "a");

	// 4. 取得したプロパティが数値であることを確認
	if (!IS_NUMBER(rVal) || !IS_NUMBER(gVal) || !IS_NUMBER(bVal) || !IS_NUMBER(aVal)) {
		runtimeError(vm, "Color properties 'r', 'g', 'b', 'a' must be numbers.");
		return false;
	}

	// 5. CのColor構造体に値をセット
	//    RaylibのColorメンバは unsigned char なので、範囲チェックとキャストを行う
	color->r = (unsigned char) AS_NUMBER(rVal);
	color->g = (unsigned char) AS_NUMBER(gVal);
	color->b = (unsigned char) AS_NUMBER(bVal);
	color->a = (unsigned char) AS_NUMBER(aVal);

	return true;
}

/**
* @brief LoxのValueをCのCamera3D構造体に変換する。
* 
* @param vm VMへのポインタ。
* @param value 変換元のValue。Camera3Dインスタンスである必要がある。
* @param camera [out] 変換結果を格納するCのCamera3D構造体へのポインタ。
* @return 変換に成功した場合はtrue、失敗した場合はfalseを返す。
*         失敗した場合、VMにランタイムエラーが設定されることがある。
*/
bool valueToCamera3D(VM* vm, Value value, Camera3D* camera) {
	// 1. Valueがインスタンスでなければ、変換不可能
	if (!IS_INSTANCE(value)) {
		runtimeError(vm, "Argument must be a Camera3D instance.");
		return false;
	}
	ObjInstance* instance = AS_INSTANCE(value);

	// (任意だが推奨) インスタンスが本当にCamera3Dクラスのものかチェック
	// if (instance->klass != camera3DClass) {
	//     runtimeError(vm, "Argument is not of type Camera3D.");
	//     return false;
	// }

	// --- Vector3型のプロパティを変換 ---
	Value positionVal = getObjProperty(vm, instance, "position");
	if (!valueToVector3(vm, positionVal, &camera->position)) {
		runtimeError(vm, "Camera3D 'position' property is missing or not a Vector3.");
		return false;
	}

	Value targetVal = getObjProperty(vm, instance, "target");
	if (!valueToVector3(vm, targetVal, &camera->target)) {
		runtimeError(vm, "Camera3D 'target' property is missing or not a Vector3.");
		return false;
	}

	Value upVal = getObjProperty(vm, instance, "up");
	if (!valueToVector3(vm, upVal, &camera->up)) {
		runtimeError(vm, "Camera3D 'up' property is missing or not a Vector3.");
		return false;
	}

	// --- float/int型のプロパティを変換 ---
	Value fovyVal = getObjProperty(vm, instance, "fovy");
	if (!IS_NUMBER(fovyVal)) {
		runtimeError(vm, "Camera3D 'fovy' property is missing or not a number.");
		return false;
	}
	camera->fovy = (float)AS_NUMBER(fovyVal);

	Value projectionVal = getObjProperty(vm, instance, "projection");
	if (!IS_NUMBER(projectionVal)) {
		runtimeError(vm, "Camera3D 'projection' property is missing or not a number.");
		return false;
	}
	camera->projection = (int)AS_NUMBER(projectionVal);

	// 全てのプロパティの変換に成功
	return true;
}