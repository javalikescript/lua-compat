#ifndef JLS_LUA_COMPAT_H
#define JLS_LUA_COMPAT_H

#include <lua.h>
#include <lauxlib.h>

#if LUA_VERSION_NUM < 503

#define luaL_checkinteger luaL_checknumber
#define lua_isinteger lua_isnumber
#define lua_tointeger lua_tonumber

#endif

#if LUA_VERSION_NUM < 502

// From Lua 5.3 lauxlib.c
LUALIB_API void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) {
  luaL_checkstack(L, nup, "too many upvalues");
  for (; l->name != NULL; l++) {  /* fill the table with given functions */
    int i;
    for (i = 0; i < nup; i++)  /* copy upvalues to the top */
      lua_pushvalue(L, -nup);
    lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
    lua_setfield(L, -(nup + 2), l->name);
  }
  lua_pop(L, nup);  /* remove upvalues */
}

LUALIB_API void *luaL_testudata (lua_State *L, int ud, const char *tname) {
  void *p = lua_touserdata(L, ud);
  if (p != NULL) {  /* value is a userdata? */
    if (lua_getmetatable(L, ud)) {  /* does it have a metatable? */
      luaL_getmetatable(L, tname);  /* get correct metatable */
      if (!lua_rawequal(L, -1, -2))  /* not the same? */
        p = NULL;  /* value is a userdata with wrong metatable */
      lua_pop(L, 2);  /* remove both metatables */
      return p;
    }
  }
  return NULL;  /* value is not a userdata with a metatable */
}

LUA_API int lua_geti (lua_State *L, int idx, int n) {
	lua_rawgeti(L, idx, n); // we should use lua_gettable
	return lua_type(L, -1);
}

#define lua_rawlen lua_objlen
#define lua_len lua_objlen

#endif

#endif /* JLS_LUA_COMPAT_H */
