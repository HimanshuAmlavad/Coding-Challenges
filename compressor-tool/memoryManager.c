#include <stdlib.h>

typedef struct MemoryBlock
{
    size_t size;
    void *memory;
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct LeakInfo
{
    size_t size;
    size_t leakCount;
    void *address;
} LeakInfo;

MemoryBlock *getMemoryBlock(void);
LeakInfo *MGetLeaks(void);
int MFreeAll(void);
int MFree(void *);
void *MMalloc(size_t);
void *MCalloc(size_t, size_t);
void *MRealloc(void *, size_t);

MemoryBlock *MemoryBlockHead = NULL, *MemoryBlockTail = NULL;

MemoryBlock *getMemoryBlock(void)
{
    MemoryBlock *block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
    if (!block)
        return NULL;
    block->next = NULL;
    return block;
}

void *MRealloc(void *ptr, size_t size)
{
    if (!size)
    {
        MFree(ptr);
        return NULL;
    }
    if (!ptr)
        return MMalloc(size);
    MemoryBlock *block = MemoryBlockHead;
    while (block)
    {
        if (block->memory == ptr)
            break;
        block = block->next;
    }
    if (!block)
        return NULL;
    void *reallocMemory = realloc(ptr, size);
    if (!reallocMemory)
        return NULL;
    block->size = size;
    block->memory = reallocMemory;
    return reallocMemory;
}

void *MMalloc(size_t size)
{
    if (!size)
        return NULL;
    void *mallocMemory = malloc(size);
    if (!mallocMemory)
        return NULL;
    MemoryBlock *block = getMemoryBlock();
    if (!block)
    {
        free(mallocMemory);
        return NULL;
    }
    block->size = size;
    block->memory = mallocMemory;
    if (!MemoryBlockHead)
        MemoryBlockHead = MemoryBlockTail = block;
    else
    {
        MemoryBlockTail->next = block;
        MemoryBlockTail = block;
    }
    return mallocMemory;
}

void *MCalloc(size_t size, size_t typeSize)
{
    if (!(size && typeSize))
        return NULL;
    void *callocMemory = calloc(size, typeSize);
    if (!callocMemory)
        return NULL;
    MemoryBlock *block = getMemoryBlock();
    if (!block)
    {
        free(callocMemory);
        return NULL;
    }
    block->size = size * typeSize;
    block->memory = callocMemory;
    if (!MemoryBlockHead)
        MemoryBlockHead = MemoryBlockTail = block;
    else
    {
        MemoryBlockTail->next = block;
        MemoryBlockTail = block;
    }
    return callocMemory;
}

int MFree(void *ptr)
{
    if (!ptr)
        return 0;
    MemoryBlock *temp = MemoryBlockHead, *prev = NULL;
    while (temp)
    {
        if (temp->memory == ptr)
        {
            if (prev)
                prev->next = temp->next;
            else
                MemoryBlockHead = temp->next;
            if (temp == MemoryBlockTail)
                MemoryBlockTail = prev;

            free(temp->memory);
            free(temp);
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}

int MFreeAll(void)
{
    MemoryBlock *temp = MemoryBlockHead;
    while (MemoryBlockHead)
    {
        MemoryBlockHead = temp->next;
        free(temp->memory);
        free(temp);
        temp = MemoryBlockHead;
    }
    return ((!MemoryBlockHead) ? 1 : 0);
}

LeakInfo *MGetLeaks(void)
{
    size_t actualSize = 0, index = 0;
    for (MemoryBlock *i = MemoryBlockHead; i; i = i->next)
        actualSize++;
    if (!actualSize)
        return NULL;
    LeakInfo *leaks = (LeakInfo *)malloc(actualSize * sizeof(LeakInfo));
    if (!leaks)
    return NULL;
    leaks->leakCount = actualSize;
    for (MemoryBlock *i = MemoryBlockHead; i; i = i->next, index++)
    {
        leaks[index].address = i->memory;
        leaks[index].size = i->size;
    }
    return leaks;
}