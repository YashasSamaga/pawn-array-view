#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <sdk/amx/amx.h>
#include <sdk/plugincommon.h>

typedef void (*logprintf_t)(const char*, ...);
extern logprintf_t logprintf;

#endif /* PLE_MAIN_H_INCLUDED */