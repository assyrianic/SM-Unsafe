#if defined _unsafe_included
	#endinput
#endif
#define _unsafe_included


/// Assumes pointers are 4 bytes in size.
enum { SIZEOF_PTR = 4 };

native int Unsafe_GetMyPluginCtxt();

native any Unsafe_Load(int address, int bytes);
native void Unsafe_Store(int address, int bytes, any value);

native int Unsafe_GetArrayPtr(any[] arr);
native int Unsafe_GetStrPtr(char[] str);
native int Unsafe_GetCellPtr(any cell);

/// strides by SIZEOF_PTR.
native int Unsafe_GetEntityVTable(int entity_addr);
native int Unsafe_GetFuncFromVTable(int table, int offset);


stock Address Unsafe_ToAddress(int a) { return view_as< Address >(a); }
stock int     Unsafe_ToInt(Address a) { return view_as< int >(a);     }
stock int Unsafe_GetEntityPtr(int entity) {
	return Unsafe_ToInt(GetEntityAddress(entity));
}
stock int Unsafe_GameConfGetPtr(Handle gameconf, const char[] name) {
	return Unsafe_ToInt(GameConfGetAddress(gameconf, name));
}


/**
 * Do not edit below this line!
 */
public Extension __ext_unsafe = {
	name = "Unsafe",
	file = "unsafe.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};

public void __ext_unsafe_SetNTVOptional()
{
	MarkNativeAsOptional("Unsafe_GetMyPluginCtxt");
	MarkNativeAsOptional("Unsafe_Load");
	MarkNativeAsOptional("Unsafe_Store");
	MarkNativeAsOptional("Unsafe_GetPtrSize");
	MarkNativeAsOptional("Unsafe_GetArrayPtr");
	MarkNativeAsOptional("Unsafe_GetStrPtr");
	MarkNativeAsOptional("Unsafe_GetCellPtr");
	MarkNativeAsOptional("Unsafe_GetEntityVTable");
}