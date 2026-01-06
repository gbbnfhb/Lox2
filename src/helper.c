#include "raylib.h"
// (あなたのVMのヘッダーファイル)
#define NOGDI // Rectangle の衝突を回避
#define NOWINMESSAGES // CloseWindow などの衝突を回避
#include "vm/vm.h"
#include "vm/object.h"

// --- Lox to C Converters ---

Vector2 loxToVector2(VM* vm, Value value) {
    if (!IS_INSTANCE(value)) {
        // TODO: エラー処理: インスタンスではありません
        return (Vector2){ 0.0f, 0.0f };
    }
    ObjInstance* instance = AS_INSTANCE(value);
    
    Value x_val, y_val;
    Vector2 vec;

    if (getObjProperty(vm, instance, "x", &x_val) && IS_NUMBER(x_val)) {
        vec.x = (float)AS_NUMBER(x_val);
    } else {
        vec.x = 0.0f; // プロパティがない、または型が違う場合のデフォルト値
    }

    if (getObjProperty(vm, instance, "y", &y_val) && IS_NUMBER(y_val)) {
        vec.y = (float)AS_NUMBER(y_val);
    } else {
        vec.y = 0.0f;
    }
    return vec;
}

Vector3 loxToVector3(VM* vm, Value value) {
    if (!IS_INSTANCE(value)) {
        return (Vector3){ 0.0f, 0.0f, 0.0f };
    }
    ObjInstance* instance = AS_INSTANCE(value);
    
    Value x_val, y_val, z_val;
    Vector3 vec;

    if (getObjProperty(vm, instance, "x", &x_val) && IS_NUMBER(x_val)) vec.x = (float)AS_NUMBER(x_val);
    else vec.x = 0.0f;

    if (getObjProperty(vm, instance, "y", &y_val) && IS_NUMBER(y_val)) vec.y = (float)AS_NUMBER(y_val);
    else vec.y = 0.0f;
    
    if (getObjProperty(vm, instance, "z", &z_val) && IS_NUMBER(z_val)) vec.z = (float)AS_NUMBER(z_val);
    else vec.z = 0.0f;

    return vec;
}

Vector4 loxToVector4(VM* vm, Value value) {
    // Quaternionも同じ構造なので、この関数を共用できます
    if (!IS_INSTANCE(value)) {
        return (Vector4){ 0.0f, 0.0f, 0.0f, 0.0f };
    }
    ObjInstance* instance = AS_INSTANCE(value);
    
    Value x_val, y_val, z_val, w_val;
    Vector4 vec;

    if (getObjProperty(vm, instance, "x", &x_val) && IS_NUMBER(x_val)) vec.x = (float)AS_NUMBER(x_val);
    else vec.x = 0.0f;

    if (getObjProperty(vm, instance, "y", &y_val) && IS_NUMBER(y_val)) vec.y = (float)AS_NUMBER(y_val);
    else vec.y = 0.0f;
    
    if (getObjProperty(vm, instance, "z", &z_val) && IS_NUMBER(z_val)) vec.z = (float)AS_NUMBER(z_val);
    else vec.z = 0.0f;

    if (getObjProperty(vm, instance, "w", &w_val) && IS_NUMBER(w_val)) vec.w = (float)AS_NUMBER(w_val);
    else vec.w = 0.0f;

    return vec;
}

// Matrixは16個のfloatを持つので、Lox側では16要素のリストとして渡すのが現実的かもしれません。
// ここではインスタンスのプロパティ(m0, m1, ...)から読み取る例を示します。
Matrix loxToMatrix(VM* vm, Value value) {
    if (!IS_INSTANCE(value)) {
        return (Matrix){ 0 };
    }
    ObjInstance* instance = AS_INSTANCE(value);
    Matrix mat;
    
    char prop_name[4]; // "m0" から "m15"
    float* m = &mat.m0;

    for (int i = 0; i < 16; i++) {
        sprintf(prop_name, "m%d", i);
        Value val;
        if (getObjProperty(vm, instance, prop_name, &val) && IS_NUMBER(val)) {
            m[i] = (float)AS_NUMBER(val);
        } else {
            m[i] = 0.0f;
        }
    }
    return mat;
}

Color loxToColor(VM* vm, Value value) {
    if (!IS_INSTANCE(value)) {
        return (Color){ 0, 0, 0, 0 };
    }
    ObjInstance* instance = AS_INSTANCE(value);
    
    Value r_val, g_val, b_val, a_val;
    Color color;

    if (getObjProperty(vm, instance, "r", &r_val) && IS_NUMBER(r_val)) color.r = (unsigned char)AS_NUMBER(r_val);
    else color.r = 0;

    if (getObjProperty(vm, instance, "g", &g_val) && IS_NUMBER(g_val)) color.g = (unsigned char)AS_NUMBER(g_val);
    else color.g = 0;

    if (getObjProperty(vm, instance, "b", &b_val) && IS_NUMBER(b_val)) color.b = (unsigned char)AS_NUMBER(b_val);
    else color.b = 0;

    if (getObjProperty(vm, instance, "a", &a_val) && IS_NUMBER(a_val)) color.a = (unsigned char)AS_NUMBER(a_val);
    else color.a = 255; // aがない場合は不透明が一般的

    return color;
}

Rectangle loxToRectangle(VM* vm, Value value) {
    if (!IS_INSTANCE(value)) {
        return (Rectangle){ 0, 0, 0, 0 };
    }
    ObjInstance* instance = AS_INSTANCE(value);
    
    Value x_val, y_val, w_val, h_val;
    Rectangle rect;

    if (getObjProperty(vm, instance, "x", &x_val) && IS_NUMBER(x_val)) rect.x = (float)AS_NUMBER(x_val);
    else rect.x = 0.0f;

    if (getObjProperty(vm, instance, "y", &y_val) && IS_NUMBER(y_val)) rect.y = (float)AS_NUMBER(y_val);
    else rect.y = 0.0f;

    if (getObjProperty(vm, instance, "width", &w_val) && IS_NUMBER(w_val)) rect.width = (float)AS_NUMBER(w_val);
    else rect.width = 0.0f;

    if (getObjProperty(vm, instance, "height", &h_val) && IS_NUMBER(h_val)) rect.height = (float)AS_NUMBER(h_val);
    else rect.height = 0.0f;

    return rect;
}

Image loxToImage(VM* vm,Value value) {
    if(!IS_INSTANCE(value)) {
        return (Image){ .data = NULL };
    }
    ObjInstance* instance = AS_INSTANCE(value);

    Image image = { 0 };
    Value prop_val;

    // width, heightなどは数値プロパティから取得
    if(getObjProperty(vm,instance,"width",&prop_val) && IS_NUMBER(prop_val)) image.width = (int)AS_NUMBER(prop_val);
    if(getObjProperty(vm,instance,"height",&prop_val) && IS_NUMBER(prop_val)) image.height = (int)AS_NUMBER(prop_val);
    if(getObjProperty(vm,instance,"mipmaps",&prop_val) && IS_NUMBER(prop_val)) image.mipmaps = (int)AS_NUMBER(prop_val);
    if(getObjProperty(vm,instance,"format",&prop_val) && IS_NUMBER(prop_val)) image.format = (int)AS_NUMBER(prop_val);

    // 'data' プロパティは、文字列 (ObjString) であると期待する
    if(getObjProperty(vm,instance,"data",&prop_val)) {
        if(IS_STRING(prop_val)) {
            ObjString* str_obj = AS_STRING(prop_val);

            // ★★★ 文字列をバイト配列として扱う ★★★
            // Loxの文字列が管理するメモリを「借用」する
            image.data = str_obj->chars;

            // サイズチェック (重要！)
            // 文字列の長さ (str_obj->length) が期待されるピクセルデータサイズと一致するか確認
            int expected_size = GetPixelDataSize(image.width,image.height,image.format);
            if(str_obj->length < expected_size) {
                // TODO: 実行時エラー: データ文字列の長さが足りません
            }
        }
        else {
            image.data = NULL;
        }
    }
    else {
        image.data = NULL;
    }

    return image;
}

Camera2D loxToCamera2D(VM* vm, Value value) {
    if (!IS_INSTANCE(value)) {
        // エラー: インスタンスではありません
        return (Camera2D){ 
            .offset = { 0.0f, 0.0f }, 
            .target = { 0.0f, 0.0f }, 
            .rotation = 0.0f, 
            .zoom = 1.0f 
        };
    }
    ObjInstance* instance = AS_INSTANCE(value);
    
    Camera2D camera = { .zoom = 1.0f }; // zoomはデフォルトで1.0にしておくのが一般的
    Value prop_val;

    // 'offset' プロパティを取得し、loxToVector2で変換
    if (getObjProperty(vm, instance, "offset", &prop_val)) {
        camera.offset = loxToVector2(vm, prop_val);
    } else {
        camera.offset = (Vector2){ 0.0f, 0.0f };
    }

    // 'target' プロパティを取得し、loxToVector2で変換
    if (getObjProperty(vm, instance, "target", &prop_val)) {
        camera.target = loxToVector2(vm, prop_val);
    } else {
        camera.target = (Vector2){ 0.0f, 0.0f };
    }

    // 'rotation' と 'zoom' は単純な数値プロパティとして取得
    if (getObjProperty(vm, instance, "rotation", &prop_val) && IS_NUMBER(prop_val)) {
        camera.rotation = (float)AS_NUMBER(prop_val);
    } else {
        camera.rotation = 0.0f;
    }

    if (getObjProperty(vm, instance, "zoom", &prop_val) && IS_NUMBER(prop_val)) {
        camera.zoom = (float)AS_NUMBER(prop_val);
    }
    // zoomプロパティがない場合は、初期値の1.0が使われる

    return camera;
}

Camera3D loxToCamera3D(VM* vm, Value value) {
    if (!IS_INSTANCE(value)) {
        // エラー: インスタンスではありません
        return (Camera3D){
            .position = { 0.0f, 0.0f, 0.0f },
            .target = { 0.0f, 0.0f, 0.0f },
            .up = { 0.0f, 1.0f, 0.0f }, // 'up'のデフォルトはY軸の正方向が一般的
            .fovy = 0.0f,
            .projection = CAMERA_PERSPECTIVE
        };
    }
    ObjInstance* instance = AS_INSTANCE(value);
    
    Camera3D camera = { 
        .up = { 0.0f, 1.0f, 0.0f }, 
        .projection = CAMERA_PERSPECTIVE 
    };
    Value prop_val;

    // 'position' プロパティを取得し、loxToVector3で変換
    if (getObjProperty(vm, instance, "position", &prop_val)) {
        camera.position = loxToVector3(vm, prop_val);
    } else {
        camera.position = (Vector3){ 0.0f, 0.0f, 0.0f };
    }

    // 'target' プロパティを取得し、loxToVector3で変換
    if (getObjProperty(vm, instance, "target", &prop_val)) {
        camera.target = loxToVector3(vm, prop_val);
    } else {
        camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    }

    // 'up' プロパティを取得し、loxToVector3で変換
    if (getObjProperty(vm, instance, "up", &prop_val)) {
        camera.up = loxToVector3(vm, prop_val);
    }
    // 'up' がない場合は、初期値の { 0, 1, 0 } が使われる

    // 'fovy' (視野角) と 'projection' (投影法) は単純な数値プロパティとして取得
    if (getObjProperty(vm, instance, "fovy", &prop_val) && IS_NUMBER(prop_val)) {
        camera.fovy = (float)AS_NUMBER(prop_val);
    } else {
        camera.fovy = 0.0f;
    }

    if (getObjProperty(vm, instance, "projection", &prop_val) && IS_NUMBER(prop_val)) {
        camera.projection = (int)AS_NUMBER(prop_val);
    }
    // 'projection' がない場合は、初期値の CAMERA_PERSPECTIVE が使われる

    return camera;
}

//------------------------------------------------------------------------------------------------------------------
//これらの関数は、raylibの関数が返したCの構造体を、 Loxのスクリプトが扱えるインスタンスに変換します。 
//------------------------------------------------------------------------------------------------------------------


// --- C to Lox Converters ---

// getNativeClass(vm, "Vector2") のような、クラスオブジェクトを取得するヘルパー関数がVMにあると仮定
// extern ObjClass* getNativeClass(VM* vm, const char* name);

Value cToLoxVector2(VM* vm, Vector2 vec) {
    ObjClass* klass = getNativeClass(vm, "Vector2");
    if (klass == NULL) return NIL_VAL; // クラスが未定義
    ObjInstance* instance = newInstance(vm, klass);
    
    setObjProperty(vm, instance, "x", NUMBER_VAL(vec.x));
    setObjProperty(vm, instance, "y", NUMBER_VAL(vec.y));
    
    return OBJ_VAL(instance);
}

Value cToLoxVector3(VM* vm, Vector3 vec) {
    ObjClass* klass = getNativeClass(vm, "Vector3");
    if (klass == NULL) return NIL_VAL;
    ObjInstance* instance = newInstance(vm, klass);
    
    setObjProperty(vm, instance, "x", NUMBER_VAL(vec.x));
    setObjProperty(vm, instance, "y", NUMBER_VAL(vec.y));
    setObjProperty(vm, instance, "z", NUMBER_VAL(vec.z));
    
    return OBJ_VAL(instance);
}

Value cToLoxVector4(VM* vm, Vector4 vec) {
    ObjClass* klass = getNativeClass(vm, "Vector4");
    if (klass == NULL) return NIL_VAL;
    ObjInstance* instance = newInstance(vm, klass);
    
    setObjProperty(vm, instance, "x", NUMBER_VAL(vec.x));
    setObjProperty(vm, instance, "y", NUMBER_VAL(vec.y));
    setObjProperty(vm, instance, "z", NUMBER_VAL(vec.z));
    setObjProperty(vm, instance, "w", NUMBER_VAL(vec.w));
    
    return OBJ_VAL(instance);
}

Value cToLoxColor(VM* vm, Color color) {
    ObjClass* klass = getNativeClass(vm, "Color");
    if (klass == NULL) return NIL_VAL;
    ObjInstance* instance = newInstance(vm, klass);
    
    setObjProperty(vm, instance, "r", NUMBER_VAL(color.r));
    setObjProperty(vm, instance, "g", NUMBER_VAL(color.g));
    setObjProperty(vm, instance, "b", NUMBER_VAL(color.b));
    setObjProperty(vm, instance, "a", NUMBER_VAL(color.a));
    
    return OBJ_VAL(instance);
}

Value cToLoxRectangle(VM* vm, Rectangle rect) {
    ObjClass* klass = getNativeClass(vm, "Rectangle");
    if (klass == NULL) return NIL_VAL;
    ObjInstance* instance = newInstance(vm, klass);
    
    setObjProperty(vm, instance, "x", NUMBER_VAL(rect.x));
    setObjProperty(vm, instance, "y", NUMBER_VAL(rect.y));
    setObjProperty(vm, instance, "width", NUMBER_VAL(rect.width));
    setObjProperty(vm, instance, "height", NUMBER_VAL(rect.height));
    
    return OBJ_VAL(instance);
}

Value cToLoxImage(VM* vm,Image image) {
    ObjClass* klass = getNativeClass(vm,"Image");
    if(klass == NULL) return NIL_VAL;
    ObjInstance* instance = newInstance(vm,klass);

    setObjProperty(vm,instance,"width",NUMBER_VAL(image.width));
    setObjProperty(vm,instance,"height",NUMBER_VAL(image.height));
    setObjProperty(vm,instance,"mipmaps",NUMBER_VAL(image.mipmaps));
    setObjProperty(vm,instance,"format",NUMBER_VAL(image.format));

    if(image.data != NULL) {
        int size = GetPixelDataSize(image.width,image.height,image.format);

        // ★★★ バイト配列を文字列としてコピーする ★★★
        // Cのメモリ (image.data) から、指定された長さ (size) で新しいObjStringを作成する
        // copyString はヌル終端を仮定しないバージョンである必要がある
        // (cloxの takeString/copyString はこの用途に使える)
        ObjString* data_str = copyString(vm,(const char*)image.data,size);

        setObjProperty(vm,instance,"data",OBJ_VAL(data_str));

        // CのメモリはLoxの文字列にコピーされたので、元は解放する
        RL_FREE(image.data);
    }
    else {
        setObjProperty(vm,instance,"data",NIL_VAL);
    }

    return OBJ_VAL(instance);
}

Value cToLoxCamera2D(VM* vm, Camera2D camera) {
    // Lox側に "Camera2D" クラスが定義されていると仮定
    ObjClass* klass = getNativeClass(vm, "Camera2D");
    if (klass == NULL) {
        return NIL_VAL; // クラスが未定義
    }
    ObjInstance* instance = newInstance(vm, klass);

    // cToLoxVector2ヘルパーを使って、CのVector2をLoxのVector2インスタンスに変換し、プロパティとして設定
    setObjProperty(vm, instance, "offset", cToLoxVector2(vm, camera.offset));
    setObjProperty(vm, instance, "target", cToLoxVector2(vm, camera.target));

    // rotationとzoomは単純な数値として設定
    setObjProperty(vm, instance, "rotation", NUMBER_VAL(camera.rotation));
    setObjProperty(vm, instance, "zoom", NUMBER_VAL(camera.zoom));
    
    return OBJ_VAL(instance);
}

Value cToLoxCamera3D(VM* vm, Camera3D camera) {
    // Lox側に "Camera3D" クラスが定義されていると仮定
    ObjClass* klass = getNativeClass(vm, "Camera3D");
    if (klass == NULL) {
        return NIL_VAL; // クラスが未定義
    }
    ObjInstance* instance = newInstance(vm, klass);

    // cToLoxVector3ヘルパーを使って、CのVector3をLoxのVector3インスタンスに変換し、プロパティとして設定
    setObjProperty(vm, instance, "position", cToLoxVector3(vm, camera.position));
    setObjProperty(vm, instance, "target", cToLoxVector3(vm, camera.target));
    setObjProperty(vm, instance, "up", cToLoxVector3(vm, camera.up));

    // fovyとprojectionは単純な数値として設定
    setObjProperty(vm, instance, "fovy", NUMBER_VAL(camera.fovy));
    setObjProperty(vm, instance, "projection", NUMBER_VAL(camera.projection));
    
    return OBJ_VAL(instance);
}

// 汎用的な cToLox ラッパー
Value cToLox(VM* vm, const char* type, void* data) {
    if (strcmp(type, "Vector2") == 0) return cToLoxVector2(vm, *(Vector2*)data);
    if (strcmp(type, "Vector3") == 0) return cToLoxVector3(vm, *(Vector3*)data);
    if (strcmp(type, "Color") == 0) return cToLoxColor(vm, *(Color*)data);
    if (strcmp(type, "Rectangle") == 0) return cToLoxRectangle(vm, *(Rectangle*)data);
    if (strcmp(type, "bool") == 0) return BOOL_VAL(*(bool*)data);
    if (strcmp(type, "int") == 0) return NUMBER_VAL(*(int*)data);
    if (strcmp(type, "float") == 0) return NUMBER_VAL(*(float*)data);
    // ... 他の型も追加 ...
    
    return NIL_VAL; // 不明な型
}
