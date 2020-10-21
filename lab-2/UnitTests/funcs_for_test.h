extern "C" {
void SetListStart(void* ptr);
void SetListEnd(void* ptr);
void SetBeforeLastAlloc(void* ptr);
void InitNoCheck(void *pMemory, int size);
}