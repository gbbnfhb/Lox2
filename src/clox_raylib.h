    #ifndef clox_raylib_h
    #define clox_raylib_h
   
    #include "vm/vm.h"
   
    //このモジュールのネイティブクラス・メソッドを登録するための関数
    void registerRaylibPackage(VM* vm);
   
    #endif