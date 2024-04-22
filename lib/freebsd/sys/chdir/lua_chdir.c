/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) Mark Johnston <markj@FreeBSD.org>
 */

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int
l_chdir(lua_State *L)
{
	const char *path;
	int ret;

	path = luaL_checkstring(L, 1);

	ret = chdir(path);
	if (ret == -1) {
		lua_pushnil(L);
		lua_pushstring(L, strerror(errno));
		lua_pushinteger(L, errno);
		return (3);
	}

	lua_pushboolean(L, 1);
	return (1);
}

static const struct luaL_Reg l_chdirtab[] = {
	{"chdir", l_chdir},
	{NULL, NULL},
};

int	luaopen_chdir(lua_State *L);

int
luaopen_chdir(lua_State *L)
{
	lua_newtable(L);

	luaL_setfuncs(L, l_chdirtab, 0);

	return (1);
}
