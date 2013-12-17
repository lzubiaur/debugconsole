/*
** Lua binding: command
** Generated automatically by tolua++-1.0.92 on Mon Dec 16 18:54:22 2013.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_command_open (lua_State* tolua_S);

#include "console/command.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_pix2d_console__Command (lua_State* tolua_S)
{
 pix2d_console::Command* self = (pix2d_console::Command*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"pix2d_console::Command");
}

/* method: new of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_new00
static int tolua_command_pix2d_console_Command_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d_console::Command* tolua_ret = (pix2d_console::Command*)  Mtolua_new((pix2d_console::Command)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d_console::Command");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_new00_local
static int tolua_command_pix2d_console_Command_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d_console::Command* tolua_ret = (pix2d_console::Command*)  Mtolua_new((pix2d_console::Command)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d_console::Command");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_delete00
static int tolua_command_pix2d_console_Command_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d_console::Command* self = (pix2d_console::Command*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reloadLevel of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_reloadLevel00
static int tolua_command_pix2d_console_Command_reloadLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d_console::Command* self = (pix2d_console::Command*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reloadLevel'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->reloadLevel();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reloadLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reloadLevel of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_reloadLevel01
static int tolua_command_pix2d_console_Command_reloadLevel01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  pix2d_console::Command* self = (pix2d_console::Command*)  tolua_tousertype(tolua_S,1,0);
  const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reloadLevel'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->reloadLevel(data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_command_pix2d_console_Command_reloadLevel00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateSpriteFrames of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_updateSpriteFrames00
static int tolua_command_pix2d_console_Command_updateSpriteFrames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d_console::Command* self = (pix2d_console::Command*)  tolua_tousertype(tolua_S,1,0);
  const char* plist_data = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* texture_data = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateSpriteFrames'", NULL);
#endif
  {
   self->updateSpriteFrames(plist_data,texture_data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateSpriteFrames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_command_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"pix2d_console",0);
  tolua_beginmodule(tolua_S,"pix2d_console");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Command","pix2d_console::Command","",tolua_collect_pix2d_console__Command);
   #else
   tolua_cclass(tolua_S,"Command","pix2d_console::Command","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Command");
    tolua_function(tolua_S,"new",tolua_command_pix2d_console_Command_new00);
    tolua_function(tolua_S,"new_local",tolua_command_pix2d_console_Command_new00_local);
    tolua_function(tolua_S,".call",tolua_command_pix2d_console_Command_new00_local);
    tolua_function(tolua_S,"delete",tolua_command_pix2d_console_Command_delete00);
    tolua_function(tolua_S,"reloadLevel",tolua_command_pix2d_console_Command_reloadLevel00);
    tolua_function(tolua_S,"reloadLevel",tolua_command_pix2d_console_Command_reloadLevel01);
    tolua_function(tolua_S,"updateSpriteFrames",tolua_command_pix2d_console_Command_updateSpriteFrames00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_command (lua_State* tolua_S) {
 return tolua_command_open(tolua_S);
};
#endif

