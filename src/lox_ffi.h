#pragma once
#ifndef clox_ffi_h
#define clox_ffi_h

#include "vm/object.h"
#include "vm/value.h"
#include "vm/vm.h"

#include "obj_ffifunction.h"

#define IS_LIBRARY(value) isObjType(value, OBJ_LIBRARY)
#define IS_FFI_FUNCTION(value) isObjType(value, OBJ_FFI_FUNCTION)

#define AS_LIBRARY(value) ((ObjLibrary *)AS_OBJ(value))
#define AS_FFI_FUNCTION(value) ((ObjFFIFunction *)AS_OBJ(value))

// Library management functions
ObjLibrary *newLibrary(VM *vm, void *handle, ObjString *path);
void *openLibrary(const char *path);
void *findSymbol(void *handle, const char *name);
void closeLibrary(void *handle);

// FFI function management
ObjFFIFunction *newFFIFunction(VM *vm, void *funcPtr, ObjString *name,
                               int arity);
Value callFFIFunction(VM *vm, ObjFFIFunction *function, int argCount,
                      Value *args);

// Type conversion helpers
void *loxTypeToFFIType(const char *typeName);
void loxValueToFFIArg(VM *vm, Value value, const char *typeName,
                      void *argBuffer);
Value ffiReturnToLoxValue(VM *vm, void *returnBuffer, const char *typeName);

// Native functions exposed to Lox
void registerFFIFunctions(VM *vm);

#endif // !clox_ffi_h
