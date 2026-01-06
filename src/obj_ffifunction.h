#pragma once
#include "vm/object.h"

// FFI Library object type
typedef struct {
  Obj obj;
  void *handle;    // dlopen/LoadLibrary handle
  ObjString *path; // Library path
} ObjLibrary;

struct ffi_cif;
struct ffi_type;
// FFI Function wrapper object type
typedef struct {
  Obj obj;
  void *funcPtr;        // C function pointer
  ObjString *name;      // Function name
  int arity;            // Number of arguments
  ffi_cif *cif;         // libffi call interface (ffi_cif*)
  ffi_type **argTypes;  // Array of ffi_type pointers
  ffi_type *returnType; // Return type (ffi_type*)
  char **argTypeNames;  // Array of argument type names
  char *returnTypeName; // Return type name
} ObjFFIFunction;