#define CloseWindow     rl_CloseWindow
#define ShowCursor      rl_ShowCursor
#include <raylib.h>  // include raylib here <---
#undef CloseWindow  
#undef ShowCursor      

#define NOGDI // Rectangle の衝突を回避
#define NOWINMESSAGES // CloseWindow などの衝突を回避

#include "common/common.h"
#include "vm/assert.h"
#include "vm/interceptor.h"
#include "vm/object.h"
#include "vm/memory.h"
#include "vm/vm.h"
#include "vm/native.h"
#include "vm/string.h"
#include "std/util.h"
#include "clox_raylib.h"  // <-- これを追加



// 1. メソッドの実体を定義するマクロ
LOX_METHOD(Vector3,sayHello) {
    ASSERT_ARG_COUNT("Vector3::sayHello()",0);
    RETURN_OBJ(copyString(vm,"Hello from a new C module!",26));
}

LOX_METHOD(Vector3,__init__) {

    ASSERT_ARG_COUNT("Vector3::__init__()",3);
    ObjInstance* self = AS_INSTANCE(receiver);
    setObjProperty(vm,self,"x",args[0]);
    setObjProperty(vm,self,"y",args[1]);
    setObjProperty(vm,self,"z",args[2]);

    RETURN_VAL(receiver);
}

/*
LOX_METHOD(Vector3,__add__) {
    ASSERT_ARG_COUNT("Vector3::+(other)",1);
    //ASSERT_ARG_TYPE("Vector3::+(other)",0,Vector3);
    ObjInstance* self = AS_INSTANCE(receiver);
    Vector3 v;
    v.x = ((Vector3*)args[0])->x + ((Vector3*)args[1])->x ;
    v.y = ((Vector3*)args[0])->y + ((Vector3*)args[1])->y ;
    v.z = ((Vector3*)args[0])->z + ((Vector3*)args[1])->z ;
    setObjProperty(vm,self,"x",FLOAT_VAL(v.x));
    setObjProperty(vm,self,"y",FLOAT_VAL(v.y));
    setObjProperty(vm,self,"z",FLOAT_VAL(v.z));

    RETURN_VAL(receiver);
}
*/
// LOX_METHODマクロで '-' 演算子の実体を定義する
LOX_METHOD(Vector3,subtract) {
    // ... 引き算の実装 ...
}


// 2. 登録関数
void registerRaylibPackage(VM* vm) {
    ObjNamespace* raylibNamespace = defineNativeNamespace(vm,"Raylib",vm->cloxNamespace);
    vm->currentNamespace = raylibNamespace;


    ObjClass* vector3Class = defineNativeClass(vm,"Vector3");
    bindSuperclass(vm,vector3Class,vm->objectClass);
    vm->arrayClass->classType = OBJ_CLASS;

    // "new" の代わりに、"__init__" インターセプターを定義する
    // 引数は x, y, z の3つ
    DEF_INTERCEPTOR(vector3Class,Vector3,INTERCEPTOR_INIT,__init__,3,RETURN_TYPE(clox.Raylib.Vector3)
        ,PARAM_TYPE(Float),PARAM_TYPE(Float),PARAM_TYPE(Float));

    DEF_METHOD(vector3Class,Vector3,sayHello,0);

    // '+' 演算子をオーバーロードする
  /*  DEF_OPERATOR(vector3Class,Vector3,+,__add__,2,
                 RETURN_TYPE(clox.Raylib.Vector3),
                 PARAM_TYPE(clox.Raylib.Vector3),PARAM_TYPE(clox.Raylib.Vector3));
*/
    vm->currentNamespace = vm->rootNamespace;

}

