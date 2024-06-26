/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) Mark Johnston <markj@FreeBSD.org>
 */

#include <sys/stat.h>

#include <errno.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int
l_mkdir(lua_State *L)
{
	const char *path;
	mode_t mode;
	int ret;

	path = luaL_checkstring(L, 1);
	mode = luaL_checkinteger(L, 2);

	ret = mkdir(path, mode);
	if (ret == -1) {
		lua_pushnil(L);
		lua_pushstring(L, strerror(errno));
		lua_pushinteger(L, errno);
		return (3);
	}

	lua_pushboolean(L, 1);
	return (1);
}

static const struct luaL_Reg l_mkdirtab[] = {
	{"mkdir", l_mkdir},
	{NULL, NULL},
};

int	luaopen_mkdir(lua_State *L);

int
luaopen_mkdir(lua_State *L)
{
	lua_newtable(L);
	luaL_setfuncs(L, l_mkdirtab, 0);
	return (1);
}
