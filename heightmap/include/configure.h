#pragma once

#include <string>


namespace heightmap {


/**
* Пути к данным в файловой системе.
*/
static const std::string PATH_MEDIA = "media";




/**
* Для отладки.
*/
#ifdef _DEBUG
#define ASSERT(EXPR)   assert(EXPR);
#define DASSERT(EXPR)  if (!(EXPR)) __debugbreak();

#define QUOTE_(WHAT)      #WHAT
#define QUOTE(WHAT)       QUOTE_(WHAT)
#define DBG(format, ...)  printf("%s: "format, __FILE__":"QUOTE(__LINE__), ## __VA_ARGS__)

#define CONSOLE  std::cout

#else
#define ASSERT(EXPR)      ((void)0)
#define DASSERT(EXPR)     ((void)0)
#define DBG(format, ...)  ((void)0)
#define CONSOLE           ((void)0)

#endif


} // heightmap
