#include "ray_bind.h"


ObjClass* vector2Class;
ObjClass* vector3Class;
ObjClass* rayCollisionClass;
ObjClass* rayClass;

LOX_METHOD(Vector3,sayHello) {

    ASSERT_ARG_COUNT("Vector3::sayHello()",0);
    RETURN_OBJ(copyString(vm,"Hello from a new C module!",26));
}

LOX_METHOD(Vector3, dbg) {
	// 1. 引数の数をチェック (dbg()は引数を取らない)
	if (argCount != 0) {
		runtimeError(vm, "dbg() expects no arguments.");
		RETURN_NIL;
	}

	// 2. レシーバ（メソッドを呼び出したインスタンス自身）を取得
	//    receiverはLOX_METHODマクロによって提供されると仮定
	if (!IS_INSTANCE(receiver)) {
		// この状況は通常発生しないはずだが、安全のためにチェック
		runtimeError(vm, "dbg() must be called on an instance.");
		RETURN_NIL;
	}
	ObjInstance* self = AS_INSTANCE(receiver);

	// 3. インスタンスから x, y, z プロパティの値を取得
	Value xVal = getObjProperty(vm, self, "x");
	Value yVal = getObjProperty(vm, self, "y");
	Value zVal = getObjProperty(vm, self, "z");

	// 4. 取得した値が数値であることを確認
	if (!IS_NUMBER(xVal) || !IS_NUMBER(yVal) || !IS_NUMBER(zVal)) {
		// プロパティが欠けているか、型が違う場合
		printf("<Vector3 object with invalid or missing properties>\n");
	} else {
		// 5. 値をdoubleに変換して、整形して出力
		double x = AS_NUMBER(xVal);
		double y = AS_NUMBER(yVal);
		double z = AS_NUMBER(zVal);
		printf("<Vector3 x: %g, y: %g, z: %g>\n", x, y, z);
	}

	// 6. メソッドの戻り値としてレシーバ自身を返す (メソッドチェーンのため)
	RETURN_VAL(receiver);
}

// --- Vector2 ---
LOX_METHOD(Vector2,__init__) {
    // 引数2つ (x, y) を期待
    if(argCount != 2) {
		printf("Vecor2 arg err\n");
        // (ここに引数エラー処理)
        RETURN_NIL;
    }
    float x = (float)AS_NUMBER(args[0]);
    float y = (float)AS_NUMBER(args[1]);

    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"x",FLOAT_VAL(x));
    setObjProperty(vm,self,"y",FLOAT_VAL(y));
    RETURN_VAL(receiver);
}

/*
example
1. var v1=Vector3(); == (0,0,0)
2. var v2=Vector3( 10.0, 20.0, 30.0);
3. var v3=Vector3( v2 );
*/
LOX_METHOD(Vector3,__init__) {

    float x=0,y=0,z=0;
    ObjInstance* vector3Class;

    switch(argCount)
    {
        case 0:
        break;

        case 1:
            vector3Class = AS_INSTANCE(args[0]);
            Value vx = getObjProperty(vm,vector3Class,"x");
            Value vy = getObjProperty(vm,vector3Class,"y");
            Value vz = getObjProperty(vm,vector3Class,"z");
            x = (float)AS_NUMBER(vx);
            y = (float)AS_NUMBER(vy);
            z = (float)AS_NUMBER(vz);
            break;

        case 3:
            x = (float)(AS_NUMBER(args[0]));
            y = (float)(AS_NUMBER(args[1]));
            z = (float)(AS_NUMBER(args[2]));
            break;
    }

    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"x",FLOAT_VAL(x));
    setObjProperty(vm,self,"y",FLOAT_VAL(y));
    setObjProperty(vm,self,"z",FLOAT_VAL(z));

    RETURN_VAL(receiver);
}

// class Vector4
LOX_METHOD(Vector4,__init__) {
    if(argCount != 4) { 
		printf("Vecor4 arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"x",args[0]);
    setObjProperty(vm,self,"y",args[1]);
    setObjProperty(vm,self,"z",args[2]);
    setObjProperty(vm,self,"w",args[3]);
    RETURN_VAL(receiver);
}

// class Matrix
LOX_METHOD(Matrix,__init__) {
    if(argCount != 16) { 
		printf("Matrix arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"m0",args[0]);
    setObjProperty(vm,self,"m4",args[1]);
    setObjProperty(vm,self,"m8",args[2]);
    setObjProperty(vm,self,"m12",args[3]);
    setObjProperty(vm,self,"m1",args[4]);
    setObjProperty(vm,self,"m5",args[5]);
    setObjProperty(vm,self,"m9",args[6]);
    setObjProperty(vm,self,"m13",args[7]);
    setObjProperty(vm,self,"m2",args[8]);
    setObjProperty(vm,self,"m6",args[9]);
    setObjProperty(vm,self,"m10",args[10]);
    setObjProperty(vm,self,"m14",args[11]);
    setObjProperty(vm,self,"m3",args[12]);
    setObjProperty(vm,self,"m7",args[13]);
    setObjProperty(vm,self,"m11",args[14]);
    setObjProperty(vm,self,"m15",args[15]);
    RETURN_VAL(receiver);
}

#if 0
// --- Color ---
LOX_METHOD(Color,__init__) {
    if(argCount != 4) { /* エラー処理 */ RETURN_NIL; }
	ASSERT_ARG_TYPE("Color::__init__(r)", 0, Int);
	ASSERT_ARG_TYPE("Color::__init__(g)", 1, Int);
	ASSERT_ARG_TYPE("Color::__init__(b)", 2, Int);
	ASSERT_ARG_TYPE("Color::__init__(a)", 3, Int);

    ObjInstance* self = AS_INSTANCE(receiver);

	setObjProperty(vm,self,"r",args[0]);
	setObjProperty(vm,self,"g",args[1]);
	setObjProperty(vm,self,"b",args[2]);
	setObjProperty(vm,self,"a",args[3]);

	RETURN_VAL(receiver);
}
#else
LOX_METHOD(Color, __init__) {

	// --- 引数が1つで、かつそれが文字列の場合 ---
	if (argCount == 1) {
		ObjString* colorName = AS_STRING(args[0]);
		Color c; // CのColor構造体

		// 文字列を比較して色を決定
		if (strcmp(colorName->chars, "LIGHTGRAY") == 0) c = LIGHTGRAY;
		else if (strcmp(colorName->chars, "GRAY") == 0) c = GRAY;
		else if (strcmp(colorName->chars, "DARKGRAY") == 0) c = DARKGRAY;
		else if (strcmp(colorName->chars, "YELLOW") == 0) c = YELLOW;
		else if (strcmp(colorName->chars, "GOLD") == 0) c = GOLD;
		else if (strcmp(colorName->chars, "ORANGE") == 0) c = ORANGE;
		else if (strcmp(colorName->chars, "PINK") == 0) c = PINK;
		else if (strcmp(colorName->chars, "RED") == 0) c = RED;
		else if (strcmp(colorName->chars, "MAROON") == 0) c = MAROON;
		else if (strcmp(colorName->chars, "GREEN") == 0) c = GREEN;
		else if (strcmp(colorName->chars, "LIME") == 0) c = LIME;
		else if (strcmp(colorName->chars, "DARKGREEN") == 0) c = DARKGREEN;
		else if (strcmp(colorName->chars, "SKYBLUE") == 0) c = SKYBLUE;
		else if (strcmp(colorName->chars, "BLUE") == 0) c = BLUE;
		else if (strcmp(colorName->chars, "DARKBLUE") == 0) c = DARKBLUE;
		else if (strcmp(colorName->chars, "SKYBLUE") == 0) c = SKYBLUE;
		else if (strcmp(colorName->chars, "BLUE") == 0) c = BLUE;
		else if (strcmp(colorName->chars, "DARKBLUE") == 0) c = DARKBLUE;
		else if (strcmp(colorName->chars, "PURPLE") == 0) c = PURPLE;
		else if (strcmp(colorName->chars, "VIOLET") == 0) c = VIOLET;
		else if (strcmp(colorName->chars, "DARKPURPLE") == 0) c = DARKPURPLE;
		else if (strcmp(colorName->chars, "BEIGE") == 0) c = BEIGE;
		else if (strcmp(colorName->chars, "BROWN") == 0) c = BROWN;
		else if (strcmp(colorName->chars, "DARKBROWN") == 0) c = DARKBROWN;

		else if (strcmp(colorName->chars, "WHITE") == 0) c = WHITE;
		else if (strcmp(colorName->chars, "BLACK") == 0) c = BLACK;
		else if (strcmp(colorName->chars, "BLANK") == 0) c = BLANK;
		else if (strcmp(colorName->chars, "MAGENTA") == 0) c = MAGENTA;
		else if (strcmp(colorName->chars, "RAYWHITE") == 0) c = RAYWHITE;
		// ...
		else {
			// エラー処理
			RETURN_NIL;
		}

		// 決定した色でインスタンスのプロパティを設定
		setObjProperty(vm, AS_INSTANCE(receiver), "r", NUMBER_VAL(c.r));
		setObjProperty(vm, AS_INSTANCE(receiver), "g", NUMBER_VAL(c.g));
		setObjProperty(vm, AS_INSTANCE(receiver), "b", NUMBER_VAL(c.b));
		setObjProperty(vm, AS_INSTANCE(receiver), "a", NUMBER_VAL(c.a));

		RETURN_VAL(receiver);
	}
	// --- 引数が4つで、かつそれが数値の場合 (今までのロジック) ---
	else if (argCount == 4 ) {
		ASSERT_ARG_TYPE("Color::__init__(r)", 0, Int);
		ASSERT_ARG_TYPE("Color::__init__(g)", 1, Int);
		ASSERT_ARG_TYPE("Color::__init__(b)", 2, Int);
		ASSERT_ARG_TYPE("Color::__init__(a)", 3, Int);

		ObjInstance* self = AS_INSTANCE(receiver);

		setObjProperty(vm,self,"r",args[0]);
		setObjProperty(vm,self,"g",args[1]);
		setObjProperty(vm,self,"b",args[2]);
		setObjProperty(vm,self,"a",args[3]);

		RETURN_VAL(receiver);	}

	// --- それ以外はエラー ---
	runtimeError(vm, "Color constructor expects (r, g, b, a) or a color name string.");
	RETURN_NIL;
}
#endif

// --- Rectangle ---
LOX_METHOD(Rectangle,__init__) {
    if(argCount != 4) { 
		printf("Rectangle arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    float x = (float)AS_NUMBER(args[0]);
    float y = (float)AS_NUMBER(args[1]);
    float width = (float)AS_NUMBER(args[2]);
    float height = (float)AS_NUMBER(args[3]);

    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"x",FLOAT_VAL(x));
    setObjProperty(vm,self,"y",FLOAT_VAL(y));
    setObjProperty(vm,self,"width",FLOAT_VAL(width));
    setObjProperty(vm,self,"height",FLOAT_VAL(height));
    RETURN_VAL(receiver);
}

// class Image
LOX_METHOD(Image,__init__) {
    if(argCount != 4) { 
		printf("Image arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"width",args[0]);
    setObjProperty(vm,self,"height",args[1]);
    setObjProperty(vm,self,"mipmaps",args[2]);
    setObjProperty(vm,self,"format",args[3]);
    RETURN_VAL(receiver);
}

// class Texture2D
LOX_METHOD(Texture2D,__init__) {
    if(argCount != 5) { 
		printf("Texture2D arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"id",args[0]);
    setObjProperty(vm,self,"width",args[1]);
    setObjProperty(vm,self,"height",args[2]);
    setObjProperty(vm,self,"mipmaps",args[3]);
    setObjProperty(vm,self,"format",args[4]);
    RETURN_VAL(receiver);
}

// class RenderTexture2D
LOX_METHOD(RenderTexture2D,__init__) {
    if(argCount != 4) { 
		printf("RenderTexture2D arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"id",args[0]);
    setObjProperty(vm,self,"texture",args[1]);
    setObjProperty(vm,self,"depth",args[2]);
    setObjProperty(vm,self,"depthTexture",args[3]);
    RETURN_VAL(receiver);
}

// class NPatchInfo
LOX_METHOD(NPatchInfo,__init__) {
    if(argCount != 6) { 
		printf("NPatchInfo arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"sourceRec",args[0]);
    setObjProperty(vm,self,"left",args[1]);
    setObjProperty(vm,self,"top",args[2]);
    setObjProperty(vm,self,"right",args[3]);
    setObjProperty(vm,self,"bottom",args[4]);
    setObjProperty(vm,self,"type",args[5]);
    RETURN_VAL(receiver);
}

// class CharInfo
LOX_METHOD(CharInfo,__init__) {
    if(argCount != 5) { 
		printf("CharInfo arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"value",args[0]);
    setObjProperty(vm,self,"rec",args[1]);
    setObjProperty(vm,self,"offsetX",args[2]);
    setObjProperty(vm,self,"offsetY",args[3]);
    setObjProperty(vm,self,"advanceX",args[4]);
    RETURN_VAL(receiver);
}

// class Font
LOX_METHOD(Font,__init__) {
    if(argCount != 3) { 
		printf("Font arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"texture",args[0]);
    setObjProperty(vm,self,"baseSize",args[1]);
    setObjProperty(vm,self,"charsCount",args[2]);
    RETURN_VAL(receiver);
}

// class Camera3D
LOX_METHOD(Camera3D,__init__) {
    if(argCount != 5) { 
		printf("Camera3D arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"position",args[0]);
    setObjProperty(vm,self,"target",args[1]);
    setObjProperty(vm,self,"up",args[2]);
    setObjProperty(vm,self,"fovy",args[3]);
    setObjProperty(vm,self,"projection",args[4]);
    RETURN_VAL(receiver);
}

// --- Camera2D ---
LOX_METHOD(Camera2D,__init__) {
    if(argCount != 4) { 
		printf("Camera2D arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    Value offset = args[0];   // Vector2 オブジェクト
    Value target = args[1];   // Vector2 オブジェクト
    float rotation = (float)AS_NUMBER(args[2]);
    float zoom = (float)AS_NUMBER(args[3]);

    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"offset",offset);
    setObjProperty(vm,self,"target",target);
    setObjProperty(vm,self,"rotation",FLOAT_VAL(rotation));
    setObjProperty(vm,self,"zoom",FLOAT_VAL(zoom));
    RETURN_VAL(receiver);
}

// class Ray
LOX_METHOD(Ray, __init__) {
	ObjInstance* self = AS_INSTANCE(receiver);

	if (argCount == 2) {
		setObjProperty(vm, self, "position", args[0]);
		setObjProperty(vm, self, "direction", args[1]);
	} 
	else if (argCount == 0) {
		// --- position用のインスタンスを生成・設定 ---
		ObjInstance* posInstance = newVector3Instance(vm, (Vector3){ 0, 0, 0 });
		push(vm, OBJ_VAL(posInstance)); // GC対策
		setObjProperty(vm, self, "position", OBJ_VAL(posInstance));
		pop(vm); // posInstanceはselfに根付いたので安全

		// --- direction用のインスタンスを生成・設定 ---
		ObjInstance* dirInstance = newVector3Instance(vm, (Vector3){ 0, 0, 0 });
		push(vm, OBJ_VAL(dirInstance)); // GC対策
		setObjProperty(vm, self, "direction", OBJ_VAL(dirInstance));
		pop(vm); // dirInstanceはselfに根付いたので安全
	}
	else {
		runtimeError(vm, "Ray() expects 0 or 2 arguments.");
		RETURN_NIL;
	}

	RETURN_VAL(receiver);
}

// class RayHitInfo
LOX_METHOD(RayHitInfo,__init__) {
    if(argCount != 4) { 
		printf("RayHitInfo arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"hit",args[0]);
    setObjProperty(vm,self,"distance",args[1]);
    setObjProperty(vm,self,"position",args[2]);
    setObjProperty(vm,self,"normal",args[3]);
    RETURN_VAL(receiver);
}

// class BoundingBox
LOX_METHOD(BoundingBox,__init__) {
    if(argCount != 2) { 
		printf("BoundingBox arg err\n");
		/* エラー処理 */ RETURN_NIL; }
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"min",args[0]);
    setObjProperty(vm,self,"max",args[1]);
    RETURN_VAL(receiver);
}

// class RayCollision
LOX_METHOD(RayCollision, __init__) {
	ObjInstance* self = AS_INSTANCE(receiver);

	if (argCount == 4) {
		setObjProperty(vm, self, "hit", args[0]);
		setObjProperty(vm, self, "distance", args[1]);
		setObjProperty(vm, self, "point", args[2]);
		setObjProperty(vm, self, "normal", args[3]);
	}
	else if (argCount == 0) {
		setObjProperty(vm, self, "hit", BOOL_VAL(false));
		setObjProperty(vm, self, "distance", NUMBER_VAL(0.0));

		// --- point用のインスタンス ---
		ObjInstance* pointInstance = newVector3Instance(vm, (Vector3){ 0, 0, 0 });
		//push(vm, OBJ_VAL(pointInstance));
		setObjProperty(vm, self, "point", OBJ_VAL(pointInstance));
		//pop(vm);

		// --- normal用のインスタンス ---
		ObjInstance* normalInstance = newVector3Instance(vm, (Vector3){ 0, 0, 0 });
		//push(vm, OBJ_VAL(normalInstance));
		setObjProperty(vm, self, "normal", OBJ_VAL(normalInstance));
		//pop(vm);
	}
	else {
		runtimeError(vm, "RayCollision() expects 0 or 4 arguments.");
		RETURN_NIL;
	}

	RETURN_VAL(receiver);
}

// 引数なしのコンストラクタを持つクラス
// (Mesh, Shader, MaterialMap, Material, Model, Transform, BoneInfo, ModelAnimation, Wave, Sound, Music, AudioStream, VrDeviceInfo)
// これらの __init__ はすべて同じ実装になります。
LOX_METHOD(Empty,__init__) {
    // 引数がないことを確認
    if(argCount != 0) { /* エラー処理 */ }
    // 何もせず、インスタンス自身を返す
    RETURN_VAL(receiver);
}



/*
static void defineNative(const char* name, NativeFn function) {
	// 関数名をLox2の文字列オブジェクトとしてヒープにコピー
	push(OBJ_VAL(copyString(name, (int)strlen(name))));
	// Cの関数ポインタをLox2のネイティブ関数オブジェクトとしてラップ
	push(OBJ_VAL(newNative(function)));
	// グローバル変数テーブルに登録
	tableSet(&vm.globals, AS_STRING(vm.stack[0]), vm.stack[1]);
	pop();
	pop();
}
*/



void registerRaylibPackage(VM* vm) {
    ObjNamespace* raylibNamespace = defineNativeNamespace(vm,"Raylib",vm->cloxNamespace);
    vm->currentNamespace = raylibNamespace;


	//ObjClass* vector2Class = defineNativeClass(vm,"Vector2");
	vector2Class = defineNativeClass(vm,"Vector2");
	//ObjClass* vector3Class = defineNativeClass(vm,"Vector3");
	vector3Class = defineNativeClass(vm,"Vector3");
	ObjClass* vector4Class = defineNativeClass(vm,"Vector4");
    ObjClass* matrixClass = defineNativeClass(vm,"Matrix");
    ObjClass* colorClass = defineNativeClass(vm,"Color");
    ObjClass* rectangleClass = defineNativeClass(vm,"Rectangle");
    ObjClass* imageClass = defineNativeClass(vm,"Image");
    ObjClass* texture2DClass = defineNativeClass(vm,"Texture2D");
    ObjClass* renderTexture2DClass = defineNativeClass(vm,"RenderTexture2D");
    ObjClass* nPatchInfoClass = defineNativeClass(vm,"NPatchInfo");
    ObjClass* charInfoClass = defineNativeClass(vm,"CharInfo");
    ObjClass* fontClass = defineNativeClass(vm,"Font");
    ObjClass* camera3DClass = defineNativeClass(vm,"Camera3D");
    ObjClass* camera2DClass = defineNativeClass(vm,"Camera2D");
	//ObjClass* rayClass = defineNativeClass(vm,"Ray");
	rayClass = defineNativeClass(vm,"Ray");
	ObjClass* rayHitInfoClass = defineNativeClass(vm,"RayHitInfo");
	ObjClass* boundingBoxClass = defineNativeClass(vm,"BoundingBox");
	//ObjClass* rayCollisionClass = defineNativeClass(vm,"rayCollision");
	rayCollisionClass = defineNativeClass(vm,"RayCollision");


    bindSuperclass(vm,vector3Class,vm->objectClass);
    vm->arrayClass->classType = OBJ_CLASS;

    // "new" の代わりに、"__init__" インターセプターを定義する
    // -1で可変
    DEF_INTERCEPTOR(vector2Class, Vector2, INTERCEPTOR_INIT, __init__,2,
    RETURN_TYPE(clox.Raylib.Vector2),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(vector3Class, Vector3, INTERCEPTOR_INIT,__init__,-1, 
    RETURN_TYPE(clox.Raylib.Vector3),PARAM_TYPE(Number));
//PARAM_TYPE(Float),PARAM_TYPE(Float),PARAM_TYPE(Float));
     //   DEF_METHOD(vector3Class,Vector3,init,3);
    DEF_INTERCEPTOR(vector4Class,Vector4,INTERCEPTOR_INIT,__init__,-1,
    RETURN_TYPE(clox.Raylib.Vector4),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(matrixClass,Matrix,INTERCEPTOR_INIT,__init__,-1,
    RETURN_TYPE(clox.Raylib.Matrix),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(colorClass, Color, INTERCEPTOR_INIT, __init__, 4,
    RETURN_TYPE(clox.Raylib.Color),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(rectangleClass, Rectangle, INTERCEPTOR_INIT, __init__, 4,
    RETURN_TYPE(clox.Raylib.Rectangle),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(imageClass,Image,INTERCEPTOR_INIT,__init__,4,
    RETURN_TYPE(clox.Raylib.Image),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(texture2DClass,Texture2D,INTERCEPTOR_INIT,__init__,5,
    RETURN_TYPE(clox.Raylib.Texture2D),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(renderTexture2DClass,RenderTexture2D,INTERCEPTOR_INIT,__init__,4,
    RETURN_TYPE(clox.Raylib.RenderTexture2D),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(nPatchInfoClass,NPatchInfo,INTERCEPTOR_INIT,__init__,6,
    RETURN_TYPE(clox.Raylib.NPatchInfo),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(charInfoClass,CharInfo,INTERCEPTOR_INIT,__init__,5,
    RETURN_TYPE(clox.Raylib.CharInfo),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(fontClass,Font,INTERCEPTOR_INIT,__init__,3,
    RETURN_TYPE(clox.Raylib.Font),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(camera3DClass,Camera3D,INTERCEPTOR_INIT,__init__,5,
    RETURN_TYPE(clox.Raylib.Camera3D),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(camera2DClass,Camera2D,INTERCEPTOR_INIT,__init__,4,
    RETURN_TYPE(clox.Raylib.Camera2D),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(rayClass,Ray,INTERCEPTOR_INIT,__init__,2,
    RETURN_TYPE(clox.Raylib.Ray),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(rayHitInfoClass,RayHitInfo,INTERCEPTOR_INIT,__init__,4,
    RETURN_TYPE(clox.Raylib.RayHitInfo),PARAM_TYPE(Number));

    DEF_INTERCEPTOR(boundingBoxClass,BoundingBox,INTERCEPTOR_INIT,__init__,2,
    RETURN_TYPE(clox.Raylib.BoundingBox),PARAM_TYPE(Number));

	DEF_INTERCEPTOR(rayCollisionClass,RayCollision,INTERCEPTOR_INIT,__init__,4,
		RETURN_TYPE(clox.Raylib.RayCollision),PARAM_TYPE(Number));




	DEF_METHOD(vector3Class,Vector3,sayHello,0);
	DEF_METHOD(vector3Class,Vector3,dbg,0);

    vm->currentNamespace = vm->rootNamespace;


}
