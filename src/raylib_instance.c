#define NOGDI // Rectangle の衝突を回避
#define NOWINMESSAGES // CloseWindow などの衝突を回避

#include "common/common.h"
#include "vm/assert.h"
#include "ray_bind.h"



ObjInstance* newVector3Instance(VM* vm, Vector3 vec) {
	// (前提) `vector3Class` はVM初期化時に設定済みのグローバル変数
	if (vector3Class == NULL) {
		// 安全のためのチェック。本来はここに来るべきではない。
		runtimeError(vm, "Vector3 class is not registered.");
		return NULL; // または適切なエラー処理
	}

	// 1. Vector3クラスの空のインスタンスを生成
	ObjInstance* instance = newInstance(vm, vector3Class);

	// 2. インスタンスのプロパティに値を設定
	//    setObjPropertyは、インスタンス、プロパティ名(char*)、値(Value)を引数に取る
	setObjProperty(vm, instance, "x", NUMBER_VAL(vec.x));
	setObjProperty(vm, instance, "y", NUMBER_VAL(vec.y));
	setObjProperty(vm, instance, "z", NUMBER_VAL(vec.z));

	return instance;
}

ObjInstance* newRayCollisionInstance(VM* vm, RayCollision collision) {
	// RayCollisionクラスの新しいインスタンスを生成
	ObjInstance* instance = newInstance(vm, rayCollisionClass);

	// 各プロパティを設定
	setObjProperty(vm, instance, "hit", BOOL_VAL(collision.hit));
	setObjProperty(vm, instance, "distance", NUMBER_VAL(collision.distance));
	setObjProperty(vm, instance, "point", OBJ_VAL(newVector3Instance(vm, collision.point)));
	setObjProperty(vm, instance, "normal", OBJ_VAL(newVector3Instance(vm, collision.normal)));

	return instance;
}

ObjInstance* newRayInstance(VM* vm, Ray ray) {
	// (前提) `rayClass` はVM初期化時に設定済みのグローバル変数
	if (rayClass == NULL) {
		runtimeError(vm, "Ray class is not registered.");
		return NULL;
	}

	// 1. Rayクラスの空のインスタンスを生成
	ObjInstance* instance = newInstance(vm, rayClass);

	// 2. インスタンスのプロパティに値を設定
	//    newVector3Instanceを使って、CのVector3をLoxのVector3インスタンスに変換する
	setObjProperty(vm, instance, "position", OBJ_VAL(newVector3Instance(vm, ray.position)));
	setObjProperty(vm, instance, "direction", OBJ_VAL(newVector3Instance(vm, ray.direction)));
	return instance;
}
