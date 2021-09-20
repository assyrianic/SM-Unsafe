#include "natives.h"
#include <cstdlib>


/// int Unsafe_GetMyPluginCtxt();
static cell_t Native_Unsafe_GetMyPluginCtxt(IPluginContext *const pContext, const cell_t params[]) {
	return ( cell_t )(pContext);
}

/// any Unsafe_Load(int address, int bytes);
static cell_t Native_Unsafe_Load(IPluginContext *const pContext, const cell_t params[]) {
	cell_t value = 0;
	const size_t bytes = ( size_t )(params[2]);
	if( bytes & 1 || (bytes - 1) > (4 - 1) )
		return value;
	
	const void *const p = ( const void* )(params[1]);
	if( p==nullptr )
		return value;
	
	memcpy(&value, p, bytes);
	return value;
}

/// void Unsafe_Store(int address, int bytes, any value);
static cell_t Native_Unsafe_Store(IPluginContext *const pContext, const cell_t params[]) {
	const size_t bytes = ( size_t )(params[2]);
	if( bytes & 1 || (bytes - 1) > (4 - 1) )
		return 0;
	
	void *const p = ( void* )(params[1]);
	if( p==nullptr )
		return value;
	
	const cell_t value = params[3];
	memcpy(p, &value, bytes);
	return 0;
}

/// int Unsafe_GetArrayPtr(const any[] arr);
static cell_t Native_Unsafe_GetArrayPtr(IPluginContext *const pContext, const cell_t params[]) {
	const cell_t *s = nullptr; pContext->LocalToPhysAddr(params[1], &s);
	return ( cell_t )(s);
}

/// int Unsafe_GetStrPtr(const char[] str);
static cell_t Native_Unsafe_GetStrPtr(IPluginContext *const pContext, const cell_t params[]) {
	const char *s = nullptr; pContext->LocalToString(params[1], &s);
	return ( cell_t )(s);
}

/// int Unsafe_GetCellPtr(any cell);
static cell_t Native_Unsafe_GetCellPtr(IPluginContext *const pContext, const cell_t params[]) {
	const cell_t *s = nullptr; pContext->LocalToPhysAddr(params[1], &s);
	return ( cell_t )(s);
}


template < typename T >
static inline void** GetVTable(T *obj) {
	return *(( void*** )(obj));
}

/// int Unsafe_GetEntityVTable(int entity_addr);
static cell_t Native_Unsafe_GetEntityVTable(IPluginContext *const pContext, const cell_t params[]) {
	void *const p = ( void* )(params[1]);
	if( p==nullptr )
		return 0;
	
	void **vtable = *( void*** )(p);
	return ( cell_t )(vtable);
}

/// int Unsafe_GetFuncFromVTable(int table, int offset);
static cell_t Native_Unsafe_GetFuncFromVTable(IPluginContext *const pContext, const cell_t params[]) {
	void **const vtable = ( void** )(params[1]);
	if( vtable==nullptr )
		return 0;
	
	const cell_t offset = params[2];
	return ( offset < 0 )? 0 : ( cell_t )(vtable[offset]);
}


sp_nativeinfo_t g_Natives[] = {
	{"Unsafe_GetMyPluginCtxt", Native_Unsafe_GetMyPluginCtxt},
	{"Unsafe_Load",            Native_Unsafe_Load},
	{"Unsafe_Store",           Native_Unsafe_Store},
	{"Unsafe_GetArrayPtr",     Native_Unsafe_GetArrayPtr},
	{"Unsafe_GetStrPtr",       Native_Unsafe_GetStrPtr},
	{"Unsafe_GetCellPtr",      Native_Unsafe_GetCellPtr},
	{"Unsafe_GetEntityVTable", Native_Unsafe_GetEntityVTable},
	{"Unsafe_GetFuncFromVTable", Native_Unsafe_GetFuncFromVTable},
	{NULL,NULL}
};
