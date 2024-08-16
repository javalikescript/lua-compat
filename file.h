#ifndef JLS_LUA_FILE_H
#define JLS_LUA_FILE_H

#include <lua.h>
#include <lauxlib.h>

#if LUA_VERSION_NUM > 501

#define FILE_UDATA_NAME LUA_FILEHANDLE
#define REF_UDATA_FILE(_UDATA) (((luaL_Stream *)_UDATA)->f)
#define FILE_UDATA_TYPE luaL_Stream

#else

#define FILE_UDATA_NAME "FILE*"
#define REF_UDATA_FILE(_UDATA) (*(FILE **)_UDATA)
#define FILE_UDATA_TYPE (FILE *)

#endif

#endif /* JLS_LUA_FILE_H */
