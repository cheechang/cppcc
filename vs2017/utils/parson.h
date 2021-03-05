/*
 Parson ( http://kgabis.github.com/parson/ )
 Copyright (c) 2012 - 2015 Krzysztof Gabis
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#ifndef parson_parson_h
#define parson_parson_h

#ifdef  _WIN32
typedef   char					int8;
typedef   unsigned char			uint8;
typedef   short					int16;
typedef   unsigned short		uint16;
typedef   int					int32;
typedef   unsigned int			uint32;
typedef   __int64				int64;
typedef   unsigned  __int64		uint64;
#elif  defined(__linux__)
#include <stdint.h>
typedef   int8_t     int8;
typedef   uint8_t    uint8;
typedef   int16_t    int16;
typedef   uint16_t   uint16;
typedef   int32_t    int32;
typedef   uint32_t   uint32;
typedef   int64_t    int64;
typedef   uint64_t   uint64;
#elif  defined(__APPLE__)
#include <stdint.h>
typedef   int8_t     int8;
typedef   uint8_t    uint8;
typedef   int16_t    int16;
typedef   uint16_t   uint16;
typedef   int32_t    int32;
typedef   uint32_t   uint32;
typedef   int64_t    int64;
typedef   uint64_t   uint64;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>   /* size_t */

/* Types and enums */
typedef struct json_object_t JSON_Object;
typedef struct json_array_t  JSON_Array;
typedef struct json_value_t  JSON_Value;

#ifdef _WIN32
    #ifdef COMM_EXPORT
        #define  COMM_EXPORT_API __declspec(dllexport)
    #else
        #define  COMM_EXPORT_API __declspec(dllimport)
    #endif
#else
    #define  COMM_EXPORT_API
#endif

enum json_value_type {
    JSONError   = -1,
    JSONNull    = 1,
    JSONString  = 2,
    JSONNumber  = 3,
    JSONObject  = 4,
    JSONArray   = 5,
    JSONBoolean = 6
};
typedef int JSON_Value_Type;
    
enum json_result_t {
    JSONSuccess = 0,
    JSONFailure = -1
};
typedef int JSON_Status;
    
typedef void * (*JSON_Malloc_Function)(size_t);
typedef void   (*JSON_Free_Function)(void *);

/* Call only once, before calling any other function from parson API. If not called, malloc and free
   from stdlib will be used for all allocations */
COMM_EXPORT_API void json_set_allocation_functions(JSON_Malloc_Function malloc_fun, JSON_Free_Function free_fun);
    
/* Parses first JSON value in a file, returns NULL in case of error */
COMM_EXPORT_API JSON_Value * json_parse_file(const char *filename);

/* Parses first JSON value in a file and ignores comments (/ * * / and //),
   returns NULL in case of error */
COMM_EXPORT_API JSON_Value * json_parse_file_with_comments(const char *filename);
    
/*  Parses first JSON value in a string, returns NULL in case of error */
COMM_EXPORT_API JSON_Value * json_parse_string(const char *string);

/*  Parses first JSON value in a string and ignores comments (/ * * / and //),
    returns NULL in case of error */
COMM_EXPORT_API JSON_Value * json_parse_string_with_comments(const char *string);
    
/* Serialization */
COMM_EXPORT_API size_t      json_serialization_size(const JSON_Value *value); /* returns 0 on fail */
COMM_EXPORT_API JSON_Status json_serialize_to_buffer(const JSON_Value *value, char *buf, size_t buf_size_in_bytes);
COMM_EXPORT_API JSON_Status json_serialize_to_file(const JSON_Value *value, const char *filename);
COMM_EXPORT_API char *      json_serialize_to_string(const JSON_Value *value);

/* Pretty serialization */
COMM_EXPORT_API size_t      json_serialization_size_pretty(const JSON_Value *value); /* returns 0 on fail */
COMM_EXPORT_API JSON_Status json_serialize_to_buffer_pretty(const JSON_Value *value, char *buf, size_t buf_size_in_bytes);
COMM_EXPORT_API JSON_Status json_serialize_to_file_pretty(const JSON_Value *value, const char *filename);
COMM_EXPORT_API char *      json_serialize_to_string_pretty(const JSON_Value *value);

COMM_EXPORT_API void        json_free_serialized_string(char *string); /* frees string from json_serialize_to_string and json_serialize_to_string_pretty */

/* Comparing */
COMM_EXPORT_API int  json_value_equals(const JSON_Value *a, const JSON_Value *b);
    
/* Validation
   This is *NOT* JSON Schema. It validates json by checking if object have identically 
   named fields with matching types.
   For example schema {"name":"", "age":0} will validate 
   {"name":"Joe", "age":25} and {"name":"Joe", "age":25, "gender":"m"},
   but not {"name":"Joe"} or {"name":"Joe", "age":"Cucumber"}.
   In case of arrays, only first value in schema is checked against all values in tested array.
   Empty objects ({}) validate all objects, empty arrays ([]) validate all arrays,
   null validates values of every type.
 */
COMM_EXPORT_API JSON_Status json_validate(const JSON_Value *schema, const JSON_Value *value);
    
/*
 * JSON Object
 */
COMM_EXPORT_API JSON_Value  * json_object_get_value(const JSON_Object *object, const char *name);
COMM_EXPORT_API const char  * json_object_get_string(const JSON_Object *object, const char *name);
COMM_EXPORT_API JSON_Object * json_object_get_object(const JSON_Object *object, const char *name);
COMM_EXPORT_API JSON_Array  * json_object_get_array(const JSON_Object *object, const char *name);
COMM_EXPORT_API double        json_object_get_number(const JSON_Object *object, const char *name); /* returns 0 on fail */
COMM_EXPORT_API int64         json_object_get_int64(const JSON_Object *object, const char *name); /* returns 0 on fail */
COMM_EXPORT_API int           json_object_get_boolean(const JSON_Object *object, const char *name); /* returns -1 on fail */

/* dotget functions enable addressing values with dot notation in nested objects,
 just like in structs or c++/java/c# objects (e.g. objectA.objectB.value).
 Because valid names in JSON can contain dots, some values may be inaccessible
 this way. */
COMM_EXPORT_API JSON_Value  * json_object_dotget_value(const JSON_Object *object, const char *name);
COMM_EXPORT_API const char  * json_object_dotget_string(const JSON_Object *object, const char *name);
COMM_EXPORT_API JSON_Object * json_object_dotget_object(const JSON_Object *object, const char *name);
COMM_EXPORT_API JSON_Array  * json_object_dotget_array(const JSON_Object *object, const char *name);
COMM_EXPORT_API double        json_object_dotget_number(const JSON_Object *object, const char *name); /* returns 0 on fail */
COMM_EXPORT_API int           json_object_dotget_boolean(const JSON_Object *object, const char *name); /* returns -1 on fail */

/* Functions to get available names */
COMM_EXPORT_API size_t        json_object_get_count(const JSON_Object *object);
COMM_EXPORT_API const char  * json_object_get_name(const JSON_Object *object, size_t index);
    
/* Creates new name-value pair or frees and replaces old value with a new one. 
 * json_object_set_value does not copy passed value so it shouldn't be freed afterwards. */
COMM_EXPORT_API JSON_Status json_object_set_value(JSON_Object *object, const char *name, JSON_Value *value);
COMM_EXPORT_API JSON_Status json_object_set_string(JSON_Object *object, const char *name, const char *string);
COMM_EXPORT_API JSON_Status json_object_set_number(JSON_Object *object, const char *name, double number);
COMM_EXPORT_API JSON_Status json_object_set_boolean(JSON_Object *object, const char *name, int boolean);
COMM_EXPORT_API JSON_Status json_object_set_null(JSON_Object *object, const char *name);

/* Works like dotget functions, but creates whole hierarchy if necessary.
 * json_object_dotset_value does not copy passed value so it shouldn't be freed afterwards. */
COMM_EXPORT_API JSON_Status json_object_dotset_value(JSON_Object *object, const char *name, JSON_Value *value);
COMM_EXPORT_API JSON_Status json_object_dotset_string(JSON_Object *object, const char *name, const char *string);
COMM_EXPORT_API JSON_Status json_object_dotset_number(JSON_Object *object, const char *name, double number);
COMM_EXPORT_API JSON_Status json_object_dotset_boolean(JSON_Object *object, const char *name, int boolean);
COMM_EXPORT_API JSON_Status json_object_dotset_null(JSON_Object *object, const char *name);

/* Frees and removes name-value pair */
COMM_EXPORT_API JSON_Status json_object_remove(JSON_Object *object, const char *name);

/* Works like dotget function, but removes name-value pair only on exact match. */
COMM_EXPORT_API JSON_Status json_object_dotremove(JSON_Object *object, const char *key);

/* Removes all name-value pairs in object */
COMM_EXPORT_API JSON_Status json_object_clear(JSON_Object *object);
    
/* 
 *JSON Array 
 */
COMM_EXPORT_API JSON_Value  * json_array_get_value(const JSON_Array *array, size_t index);
COMM_EXPORT_API const char  * json_array_get_string(const JSON_Array *array, size_t index);
COMM_EXPORT_API JSON_Object * json_array_get_object(const JSON_Array *array, size_t index);
COMM_EXPORT_API JSON_Array  * json_array_get_array(const JSON_Array *array, size_t index);
COMM_EXPORT_API double        json_array_get_number(const JSON_Array *array, size_t index); /* returns 0 on fail */
COMM_EXPORT_API int64         json_array_get_int64(const JSON_Array *array, size_t index); /* returns 0 on fail */
COMM_EXPORT_API int           json_array_get_boolean(const JSON_Array *array, size_t index); /* returns -1 on fail */
COMM_EXPORT_API size_t        json_array_get_count(const JSON_Array *array);
    
/* Frees and removes value at given index, does nothing and returns JSONFailure if index doesn't exist.
 * Order of values in array may change during execution.  */
JSON_Status json_array_remove(JSON_Array *array, size_t i);

/* Frees and removes from array value at given index and replaces it with given one.
 * Does nothing and returns JSONFailure if index doesn't exist. 
 * json_array_replace_value does not copy passed value so it shouldn't be freed afterwards. */
COMM_EXPORT_API JSON_Status json_array_replace_value(JSON_Array *array, size_t i, JSON_Value *value);
COMM_EXPORT_API JSON_Status json_array_replace_string(JSON_Array *array, size_t i, const char* string);
COMM_EXPORT_API JSON_Status json_array_replace_number(JSON_Array *array, size_t i, double number);
COMM_EXPORT_API JSON_Status json_array_replace_boolean(JSON_Array *array, size_t i, int boolean);
COMM_EXPORT_API JSON_Status json_array_replace_null(JSON_Array *array, size_t i);

/* Frees and removes all values from array */
COMM_EXPORT_API JSON_Status json_array_clear(JSON_Array *array);

/* Appends new value at the end of array.
 * json_array_append_value does not copy passed value so it shouldn't be freed afterwards. */
COMM_EXPORT_API JSON_Status json_array_append_value(JSON_Array *array, JSON_Value *value);
COMM_EXPORT_API JSON_Status json_array_append_string(JSON_Array *array, const char *string);
COMM_EXPORT_API JSON_Status json_array_append_number(JSON_Array *array, double number);
COMM_EXPORT_API JSON_Status json_array_append_boolean(JSON_Array *array, int boolean);
COMM_EXPORT_API JSON_Status json_array_append_null(JSON_Array *array);
    
/*
 *JSON Value
 */
COMM_EXPORT_API JSON_Value * json_value_init_object(void);
COMM_EXPORT_API JSON_Value * json_value_init_array(void);
COMM_EXPORT_API JSON_Value * json_value_init_string(const char *string); /* copies passed string */
COMM_EXPORT_API JSON_Value * json_value_init_number(double number);
COMM_EXPORT_API JSON_Value * json_value_init_boolean(int boolean);
COMM_EXPORT_API JSON_Value * json_value_init_null(void);
COMM_EXPORT_API JSON_Value * json_value_init_llnumber(double number, int64 llnum);
COMM_EXPORT_API JSON_Value * json_value_deep_copy(const JSON_Value *value);
COMM_EXPORT_API void         json_value_free(JSON_Value *value);

COMM_EXPORT_API JSON_Value_Type json_value_get_type(const JSON_Value *value);
COMM_EXPORT_API JSON_Object *   json_value_get_object(const JSON_Value *value);
COMM_EXPORT_API JSON_Array  *   json_value_get_array(const JSON_Value *value);
COMM_EXPORT_API const char  *   json_value_get_string(const JSON_Value *value);
COMM_EXPORT_API double          json_value_get_number(const JSON_Value *value);
COMM_EXPORT_API int             json_value_get_boolean(const JSON_Value *value);
COMM_EXPORT_API int64           json_value_get_int64(const JSON_Value *value);

/* Same as above, but shorter */
COMM_EXPORT_API JSON_Value_Type json_type(const JSON_Value *value);
COMM_EXPORT_API JSON_Object *   json_object(const JSON_Value *value);
COMM_EXPORT_API JSON_Array  *   json_array(const JSON_Value *value);
COMM_EXPORT_API const char  *   json_string(const JSON_Value *value);
COMM_EXPORT_API double          json_number(const JSON_Value *value);
COMM_EXPORT_API int             json_boolean(const JSON_Value *value);
    
#ifdef __cplusplus
}
#endif

#endif
