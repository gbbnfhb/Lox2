#include <stdio.h>
#include <string.h>

#include "vm/memory.h"
#include "vm/object.h"
#include "vm/table.h"
#include "vm/vm.h"

// A helper to allocate an object of a given size and type.
// This is a foundational function required by most other `new_*` functions.
#define ALLOCATE_OBJ(type, object_type) \
    (type*)allocate_object(vm, sizeof(type), object_type)

Obj* allocate_object(VM* vm, size_t size, ObjType type) {
    Obj* object = (Obj*)reallocate(vm, NULL, 0, size);
    object->type = type;
    // TODO: Add logic for garbage collection if your VM has it.
    // object->isMarked = false;
    // object->next = vm->objects;
    // vm->objects = object;
    return object;
}

// --- Implementation of `is_obj_type` ---
bool is_obj_type(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

// --- Implementation of `new_class` ---
ObjClass* new_class(VM* vm, ObjString* name) {
    ObjClass* klass = ALLOCATE_OBJ(ObjClass, OBJ_CLASS);
    klass->name = name;
    init_table(&klass->methods);
    return klass;
}

// --- Implementation of `new_instance` ---
ObjInstance* new_instance(VM* vm, ObjClass* klass) {
    ObjInstance* instance = ALLOCATE_OBJ(ObjInstance, OBJ_INSTANCE);
    instance->klass = klass;
    init_table(&instance->fields);
    return instance;
}

// --- Implementation of `define_global` ---
void define_global(VM* vm, ObjString* name, Value value) {
    push(vm, value); // GC protection
    tableSet(vm, &vm->globals, name, value);
    pop(vm);
}

// --- Implementation of `copy_string` ---
// This also handles string interning.
static ObjString* allocate_string(VM* vm, char* chars, int length, uint32_t hash) {
    ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    string->length = length;
    string->chars = chars;
    string->hash = hash;
    
    // GC Protection before tableSet
    push(vm, OBJ_VAL(string));
    tableSet(vm, &vm->strings, string, NIL_VAL);
    pop(vm);

    return string;
}

// FNV-1a hash function
static uint32_t hash_string(const char* key, int length) {
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++) {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }
    return hash;
}

ObjString* copy_string(VM* vm, const char* chars, int length) {
    uint32_t hash = hash_string(chars, length);
    ObjString* interned = tableFindString(&vm->strings, chars, length, hash);
    if (interned != NULL) return interned;

    char* heap_chars = ALLOCATE(vm, char, length + 1);
    memcpy(heap_chars, chars, length);
    heap_chars[length] = '\0';
    return allocate_string(vm, heap_chars, length, hash);
}


// --- Implementation of Native Binding Helpers ---

// --- Implementation of `new_native_function` ---
ObjNative* new_native_function(VM* vm, NativeFn function) {
    ObjNative* native = ALLOCATE_OBJ(ObjNative, OBJ_NATIVE);
    native->function = function;
    return native;
}

// --- Implementation of `new_native_ptr` ---
ObjNativePtr* new_native_ptr(VM* vm, void* data, void (*free_func)(void*)) {
    ObjNativePtr* native_ptr = ALLOCATE_OBJ(ObjNativePtr, OBJ_NATIVE_PTR);
    native_ptr->data = data;
    native_ptr->free_func = free_func;
    return native_ptr;
}
