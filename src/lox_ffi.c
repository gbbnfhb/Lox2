#include <ffi.h>

#include "vm/memory.h"
#include "vm/native.h"
#include "vm/object.h"
#include "vm/string.h"

#include "lox_ffi.h"
#include "vm/assert.h"
#include "vm/debug.h"
#include "vm/dict.h"
#include "vm/hash.h"
#include "vm/namespace.h"

void *openLibrary(const char *path) {
#ifdef _WIN32
  return (void *)LoadLibraryA(path);
#else
  return dlopen(path, RTLD_LAZY);
#endif
}

void *findSymbol(void *handle, const char *name) {
  if (handle == NULL)
    return NULL;
#ifdef _WIN32
  return (void *)GetProcAddress((HMODULE)handle, name);
#else
  return dlsym(handle, name);
#endif
}

void closeLibrary(void *handle) {
  if (handle == NULL)
    return;
#ifdef _WIN32
  FreeLibrary((HMODULE)handle);
#else
  dlclose(handle);
#endif
}

const char *getLibraryError() {
#ifdef _WIN32
  static char buffer[256];
  DWORD error = GetLastError();
  FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                 NULL, error, 0, buffer, sizeof(buffer), NULL);
  return buffer;
#else
  return dlerror();
#endif
}

// ============================================================================
// Object Creation Functions
// ============================================================================

static ObjClass *libraryClass = NULL;
static ObjClass *ffiFunctionClass = NULL;

ObjLibrary *newLibrary(VM *vm, void *handle, ObjString *path) {
  ObjLibrary *library = ALLOCATE_OBJ(ObjLibrary, OBJ_LIBRARY, libraryClass);
  library->handle = handle;
  library->path = path;
  return library;
}

ObjFFIFunction *newFFIFunction(VM *vm, void *funcPtr, ObjString *name,
                               int arity) {
  ObjFFIFunction *function =
      ALLOCATE_OBJ(ObjFFIFunction, OBJ_FFI_FUNCTION, ffiFunctionClass);
  function->funcPtr = funcPtr;
  function->name = name;
  function->arity = arity;
  function->cif = NULL;
  function->argTypes = NULL;
  function->returnType = NULL;
  function->argTypeNames = NULL;
  function->returnTypeName = NULL;
  return function;
}

// ============================================================================
// Type Conversion Functions
// ============================================================================

void *loxTypeToFFIType(const char *typeName) {
  if (strcmp(typeName, "void") == 0)
    return &ffi_type_void;
  if (strcmp(typeName, "int") == 0)
    return &ffi_type_sint32;
  if (strcmp(typeName, "uint") == 0)
    return &ffi_type_uint32;
  if (strcmp(typeName, "long") == 0)
    return &ffi_type_slong;
  if (strcmp(typeName, "ulong") == 0)
    return &ffi_type_ulong;
  if (strcmp(typeName, "float") == 0)
    return &ffi_type_float;
  if (strcmp(typeName, "double") == 0)
    return &ffi_type_double;
  if (strcmp(typeName, "pointer") == 0 || strcmp(typeName, "string") == 0) {
    return &ffi_type_pointer;
  }
  if (strcmp(typeName, "int8") == 0)
    return &ffi_type_sint8;
  if (strcmp(typeName, "uint8") == 0)
    return &ffi_type_uint8;
  if (strcmp(typeName, "int16") == 0)
    return &ffi_type_sint16;
  if (strcmp(typeName, "uint16") == 0)
    return &ffi_type_uint16;
  if (strcmp(typeName, "int64") == 0)
    return &ffi_type_sint64;
  if (strcmp(typeName, "uint64") == 0)
    return &ffi_type_uint64;

  // Default to pointer for unknown types
  return &ffi_type_pointer;
}

void loxValueToFFIArg(VM *vm, Value value, const char *typeName,
                      void *argBuffer) {
  if (strcmp(typeName, "int") == 0 || strcmp(typeName, "int32") == 0) {
    *(int *)argBuffer = IS_INT(value) ? AS_INT(value) : (int)AS_NUMBER(value);
  } else if (strcmp(typeName, "uint") == 0 || strcmp(typeName, "uint32") == 0) {
    *(unsigned int *)argBuffer = IS_INT(value) ? (unsigned int)AS_INT(value)
                                               : (unsigned int)AS_NUMBER(value);
  } else if (strcmp(typeName, "long") == 0) {
    *(long *)argBuffer =
        IS_INT(value) ? (long)AS_INT(value) : (long)AS_NUMBER(value);
  } else if (strcmp(typeName, "ulong") == 0) {
    *(unsigned long *)argBuffer = IS_INT(value)
                                      ? (unsigned long)AS_INT(value)
                                      : (unsigned long)AS_NUMBER(value);
  } else if (strcmp(typeName, "float") == 0) {
    *(float *)argBuffer = IS_NUMBER(value) ? (float)AS_NUMBER(value) : 0.0f;
  } else if (strcmp(typeName, "double") == 0) {
    *(double *)argBuffer = IS_NUMBER(value) ? AS_NUMBER(value) : 0.0;
  } else if (strcmp(typeName, "string") == 0) {
    if (IS_STRING(value)) {
      *(const char **)argBuffer = AS_CSTRING(value);
    } else {
      *(const char **)argBuffer = NULL;
    }
  } else if (strcmp(typeName, "pointer") == 0) {
    if (IS_NIL(value)) {
      *(void **)argBuffer = NULL;
    } else if (IS_STRING(value)) {
      *(void **)argBuffer = (void *)AS_CSTRING(value);
    } else if (IS_INT(value)) {
      *(void **)argBuffer = (void *)(intptr_t)AS_INT(value);
    } else {
      *(void **)argBuffer = NULL;
    }
  } else if (strcmp(typeName, "int8") == 0) {
    *(int8_t *)argBuffer =
        IS_INT(value) ? (int8_t)AS_INT(value) : (int8_t)AS_NUMBER(value);
  } else if (strcmp(typeName, "uint8") == 0) {
    *(uint8_t *)argBuffer =
        IS_INT(value) ? (uint8_t)AS_INT(value) : (uint8_t)AS_NUMBER(value);
  } else if (strcmp(typeName, "int16") == 0) {
    *(int16_t *)argBuffer =
        IS_INT(value) ? (int16_t)AS_INT(value) : (int16_t)AS_NUMBER(value);
  } else if (strcmp(typeName, "uint16") == 0) {
    *(uint16_t *)argBuffer =
        IS_INT(value) ? (uint16_t)AS_INT(value) : (uint16_t)AS_NUMBER(value);
  } else if (strcmp(typeName, "int64") == 0) {
    *(int64_t *)argBuffer =
        IS_INT(value) ? (int64_t)AS_INT(value) : (int64_t)AS_NUMBER(value);
  } else if (strcmp(typeName, "uint64") == 0) {
    *(uint64_t *)argBuffer =
        IS_INT(value) ? (uint64_t)AS_INT(value) : (uint64_t)AS_NUMBER(value);
  } else {
    // Default: treat as pointer
    *(void **)argBuffer = NULL;
  }
}

Value ffiReturnToLoxValue(VM *vm, void *returnBuffer, const char *typeName) {
  if (strcmp(typeName, "void") == 0) {
    return NIL_VAL;
  } else if (strcmp(typeName, "int") == 0 || strcmp(typeName, "int32") == 0) {
    return INT_VAL(*(int *)returnBuffer);
  } else if (strcmp(typeName, "uint") == 0 || strcmp(typeName, "uint32") == 0) {
    return INT_VAL((int)*(unsigned int *)returnBuffer);
  } else if (strcmp(typeName, "long") == 0) {
    return INT_VAL((int)*(long *)returnBuffer);
  } else if (strcmp(typeName, "ulong") == 0) {
    return INT_VAL((int)*(unsigned long *)returnBuffer);
  } else if (strcmp(typeName, "float") == 0) {
    return FLOAT_VAL(*(float *)returnBuffer);
  } else if (strcmp(typeName, "double") == 0) {
    return FLOAT_VAL(*(double *)returnBuffer);
  } else if (strcmp(typeName, "string") == 0) {
    const char *str = *(const char **)returnBuffer;
    if (str == NULL)
      return NIL_VAL;
    return OBJ_VAL(copyString(vm, str, (int)strlen(str)));
  } else if (strcmp(typeName, "pointer") == 0) {
    void *ptr = *(void **)returnBuffer;
    if (ptr == NULL)
      return NIL_VAL;
    return INT_VAL((int)(intptr_t)ptr);
  } else if (strcmp(typeName, "int8") == 0) {
    return INT_VAL(*(int8_t *)returnBuffer);
  } else if (strcmp(typeName, "uint8") == 0) {
    return INT_VAL(*(uint8_t *)returnBuffer);
  } else if (strcmp(typeName, "int16") == 0) {
    return INT_VAL(*(int16_t *)returnBuffer);
  } else if (strcmp(typeName, "uint16") == 0) {
    return INT_VAL(*(uint16_t *)returnBuffer);
  } else if (strcmp(typeName, "int64") == 0) {
    return INT_VAL((int)*(int64_t *)returnBuffer);
  } else if (strcmp(typeName, "uint64") == 0) {
    return INT_VAL((int)*(uint64_t *)returnBuffer);
  }

  return NIL_VAL;
}

// ============================================================================
// FFI Function Call
// ============================================================================

Value callFFIFunction(VM *vm, ObjFFIFunction *function, int argCount,
                      Value *args) {
  if (function->funcPtr == NULL) {
    THROW_EXCEPTION(clox.std.lang.IllegalArgumentException,
                    "FFI function pointer is NULL");
  }

  if (argCount != function->arity) {
    THROW_EXCEPTION(clox.std.lang.IllegalArgumentException,
                    "Wrong number of arguments for FFI function");
  }

  // Prepare argument buffers
  void **argValues = NULL;
  void *argBuffers = NULL;

  if (argCount > 0) {
    argValues = (void **)malloc(sizeof(void *) * argCount);
    // Allocate space for all argument buffers (max size for each)
    argBuffers = malloc(sizeof(uint64_t) * argCount);

    for (int i = 0; i < argCount; i++) {
      void *argBuffer = (void *)((char *)argBuffers + i * sizeof(uint64_t));
      // Note: We need type information stored in the function object
      // For now, we'll assume the types are stored somewhere accessible
      loxValueToFFIArg(vm, args[i], function->argTypeNames[i], argBuffer);
      argValues[i] = argBuffer;
    }
  }

  // Prepare return buffer
  uint64_t returnBuffer = 0;

  // Call the function using libffi
  if (function->cif != NULL) {
    ffi_call((ffi_cif *)function->cif, FFI_FN(function->funcPtr), &returnBuffer,
             argValues);
  }

  // Convert return value
  Value result =
      ffiReturnToLoxValue(vm, &returnBuffer, function->returnTypeName);

  // Cleanup
  if (argValues != NULL)
    free(argValues);
  if (argBuffers != NULL)
    free(argBuffers);

  return result;
}

// ============================================================================
// Native Functions for Lox
// ============================================================================

// FFI.loadLibrary(path: String) -> Library
LOX_FUNCTION(loadLibrary) {
  if (argCount != 1 || !IS_STRING(args[0])) {
    THROW_EXCEPTION(clox.std.lang.IllegalArgumentException,
                    "loadLibrary() expects a string path");
  }

  const char *path = AS_CSTRING(args[0]);
  void *handle = openLibrary(path);

  if (handle == NULL) {
    const char *error = getLibraryError();
    THROW_EXCEPTION_FMT(clox.std.lang.RuntimeException,
                        "Failed to load library '%s': %s", path, error);
    return NIL_VAL;
  }

  ObjLibrary *library = newLibrary(vm, handle, AS_STRING(args[0]));
  RETURN_OBJ(library);
}

// Library.getFunction(name: String, returnType: String, argTypes: Array) ->
// FFIFunction
LOX_METHOD(Library, getFunction) {
  if (!IS_LIBRARY(receiver)) {
    THROW_EXCEPTION(clox.std.lang.IllegalArgumentException,
                    "Receiver must be a Library");
  }

  if (argCount < 2 || !IS_STRING(args[0]) || !IS_STRING(args[1])) {
    THROW_EXCEPTION(clox.std.lang.IllegalArgumentException,
                    "getFunction() expects (name: String, returnType: String, "
                    "[argTypes: Array])");
  }

  ObjLibrary *library = AS_LIBRARY(receiver);
  const char *funcName = AS_CSTRING(args[0]);
  const char *returnTypeName = AS_CSTRING(args[1]);

  void *funcPtr = findSymbol(library->handle, funcName);
  if (funcPtr == NULL) {
    THROW_EXCEPTION_FMT(clox.std.lang.RuntimeException,
                        "Function '%s' not found in library", funcName);
  }

  // Parse argument types
  int arity = 0;
  ffi_type **argTypes = NULL;

  if (argCount >= 3 && IS_ARRAY(args[2])) {
    ObjArray *argTypeArray = AS_ARRAY(args[2]);
    arity = argTypeArray->elements.count;

    if (arity > 0) {
      argTypes = (ffi_type **)malloc(sizeof(ffi_type *) * arity);
      for (int i = 0; i < arity; i++) {
        Value typeVal = argTypeArray->elements.values[i];
        if (!IS_STRING(typeVal)) {
          free(argTypes);
          THROW_EXCEPTION(clox.std.lang.IllegalArgumentException,
                          "Argument types must be strings");
        }
        argTypes[i] = (ffi_type *)loxTypeToFFIType(AS_CSTRING(typeVal));
      }
    }
  }

  // Create FFI function object
  ObjFFIFunction *ffiFunc =
      newFFIFunction(vm, funcPtr, AS_STRING(args[0]), arity);

  // Store type names
  if (arity > 0) {
    ffiFunc->argTypeNames = (char **)malloc(sizeof(char *) * arity);
    for (int i = 0; i < arity; i++) {
      Value typeVal = AS_ARRAY(args[2])->elements.values[i];
      const char *typeName = AS_CSTRING(typeVal);
      ffiFunc->argTypeNames[i] = _strdup(typeName);
    }
  }
  ffiFunc->returnTypeName = _strdup(returnTypeName);

  // Prepare libffi call interface
  ffi_cif *cif = (ffi_cif *)malloc(sizeof(ffi_cif));
  ffi_type *returnType = (ffi_type *)loxTypeToFFIType(returnTypeName);

  ffi_status status =
      ffi_prep_cif(cif, FFI_DEFAULT_ABI, arity, returnType, argTypes);
  if (status != FFI_OK) {
    free(cif);
    if (argTypes != NULL)
      free(argTypes);
    THROW_EXCEPTION(clox.std.lang.RuntimeException,
                    "Failed to prepare FFI call interface");
  }

  ffiFunc->cif = cif;
  ffiFunc->argTypes = argTypes;
  ffiFunc->returnType = returnType;

  RETURN_OBJ(ffiFunc);
}

// FFIFunction.arity() -> Int
LOX_METHOD(FFIFunction, arity) {
  ASSERT_ARG_COUNT("FFIFunction::arity()", 0);
  RETURN_INT(AS_FFI_FUNCTION(receiver)->arity);
}

// FFIFunction.name() -> String
LOX_METHOD(FFIFunction, name) {
  ASSERT_ARG_COUNT("FFIFunction::name()", 0);
  RETURN_OBJ(AS_FFI_FUNCTION(receiver)->name);
}

// FFIFunction.isAsync() -> Bool
LOX_METHOD(FFIFunction, isAsync) {
  ASSERT_ARG_COUNT("FFIFunction::isAsync()", 0);
  RETURN_FALSE;
}

// FFIFunction.isNative() -> Bool
LOX_METHOD(FFIFunction, isNative) {
  ASSERT_ARG_COUNT("FFIFunction::isNative()", 0);
  RETURN_TRUE;
}

// FFIFunction.isVariadic() -> Bool
LOX_METHOD(FFIFunction, isVariadic) {
  ASSERT_ARG_COUNT("FFIFunction::isVariadic()", 0);
  RETURN_FALSE;
}

// FFIFunction.__invoke__(...args) -> Value
LOX_METHOD(FFIFunction, __invoke__) {
  ObjFFIFunction *ffiFunc = AS_FFI_FUNCTION(receiver);
  // 1. 引数の数が合っているかチェック
  if (argCount != ffiFunc->arity) {
    THROW_EXCEPTION_FMT(clox.std.lang.IllegalArgumentException,
                        "Expected %d arguments but got %d.", ffiFunc->arity,
                        argCount);
  }
  // 2. Loxの引数をCの引数に変換するための配列を準備
  void **c_args = (void **)malloc(sizeof(void *) * argCount);
  // libffiは値そのものではなく、値へのポインタの配列を要求する
  // そのため、Loxの値を一時的に格納するCの変数のメモリも確保する
  // (これはもっと効率化できるが、分かりやすさのため)
  void *arg_values =
      malloc(ffiFunc->cif->bytes); // cif->bytesは全引数の合計サイズ
  char *current_arg = (char *)arg_values;
  for (int i = 0; i < argCount; i++) {
    c_args[i] = current_arg;
    ffi_type *argType = ffiFunc->cif->arg_types[i];
    // LoxのValueをCの型に変換して、current_argに書き込む
    loxValueToFFIArg(vm, args[i], ffiFunc->argTypeNames[i], current_arg);
    current_arg += argType->size;
  }
  // 3. 戻り値を格納するメモリを準備
  void *c_ret;
  // 戻り値がvoidでない場合のみメモリを確保
  if (ffiFunc->cif->rtype != &ffi_type_void) {
    // libffiの仕様上、戻り値のバッファは少なくとも sizeof(ffi_arg)
    // のサイズが必要な場合がある
    // (特に整数型の場合、レジスタサイズ分書き込まれることがあるため)
    size_t size = ffiFunc->cif->rtype->size;
    if (size < sizeof(ffi_arg)) {
      size = sizeof(ffi_arg);
    }
    c_ret = malloc(size);
  } else {
    c_ret = NULL;
  }
  // 4. ★★★ libffiを使ってC関数を呼び出す ★★★
  ffi_call(ffiFunc->cif, FFI_FN(ffiFunc->funcPtr), c_ret, c_args);
  // 5. Cの戻り値をLoxのValueに変換して返す
  Value result = ffiReturnToLoxValue(vm, c_ret, ffiFunc->returnTypeName);

  // 6. 確保したメモリを解放
  free(c_args);
  free(arg_values);
  if (c_ret != NULL) {
    free(c_ret);
  }
  // 7. Loxに結果を返す
  RETURN_VAL(result);
}

// Library.close() -> Nil
LOX_METHOD(Library, close) {
  if (!IS_LIBRARY(receiver)) {
    THROW_EXCEPTION(clox.std.lang.IllegalArgumentException,
                    "Receiver must be a Library");
  }

  ObjLibrary *library = AS_LIBRARY(receiver);
  if (library->handle != NULL) {
    closeLibrary(library->handle);
    library->handle = NULL;
  }

  RETURN_NIL;
}

LOX_METHOD(Library, equals) {
  // 1. ?????????
  ASSERT_ARG_COUNT("equals(other)", 1);
  // 2. ????(other)?Library????????????????????
  if (!IS_LIBRARY(args[0])) {
    RETURN_FALSE;
  }
  // 3. ?????Library???????????
  ObjLibrary *self = AS_LIBRARY(receiver);
  ObjLibrary *other = AS_LIBRARY(args[0]);
  // 4. ???Library?????????????????????
  //    ?????????????????????????????????????????
  RETURN_BOOL(self->handle == other->handle);
}

// ============================================================================
// Registration
// ============================================================================

void registerFFIFunctions(VM *vm) {

  // Define FFI namespace with loadLibrary function
  ObjNamespace *ffiNamespace =
      defineNativeNamespace(vm, "FFI", vm->cloxNamespace);
  vm->currentNamespace = ffiNamespace;

  // Define Library class
  libraryClass = defineNativeClass(vm, "Library");
  DEF_METHOD(libraryClass, Library, getFunction, -1, PARAM_TYPE(String),
             PARAM_TYPE(String));
  DEF_METHOD(libraryClass, Library, close, 0);
  DEF_METHOD(libraryClass, Library, equals, 1);

  // Define FFIFunction class
  ffiFunctionClass = defineNativeClass(vm, "FFIFunction");
  bindTrait(vm, ffiFunctionClass,
            getNativeClass(vm, "clox.std.lang.TCallable"));

  DEF_METHOD(ffiFunctionClass, FFIFunction, arity, 0);
  DEF_METHOD(ffiFunctionClass, FFIFunction, name, 0);
  DEF_METHOD(ffiFunctionClass, FFIFunction, isAsync, 0);
  DEF_METHOD(ffiFunctionClass, FFIFunction, isNative, 0);
  DEF_METHOD(ffiFunctionClass, FFIFunction, isVariadic, 0);
  DEF_OPERATOR(ffiFunctionClass, FFIFunction, (), __invoke__, -1);

  // DEF_FUNCTION(loadLibrary, 1, PARAM_TYPE(String));
  DEF_FUNCTION(loadLibrary, 1, RETURN_TYPE(Library), PARAM_TYPE(String));

  vm->currentNamespace = vm->rootNamespace;
  tableSet(vm, &vm->currentNamespace->values, ffiNamespace->fullName,
           OBJ_VAL(ffiNamespace));
}