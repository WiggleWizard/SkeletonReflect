// Minimal implementations for EASTL allocator.
// Can put this code anywhere, as long as it's compiled by your project. It's only here to avoid polluting other source
// files.

#include <EABase/eabase.h>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
	return new uint8_t[size];
}
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
	return new uint8_t[size];
}