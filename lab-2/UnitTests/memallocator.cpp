#include "../memallocator.h"
#include "../memallocator.c"

extern "C" {

void SetListStart(void* ptr) {
  s_memInfo.startList = (descriptor_t*)ptr;
}

void SetListEnd(void* ptr) {
  s_memInfo.endList = (descriptor_t*)ptr;
}

void SetBeforeLastAlloc(void* ptr) {
  s_memInfo.beforeLastAlloc = (descriptor_t*)ptr;
}

}
