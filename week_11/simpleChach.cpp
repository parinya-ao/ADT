#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma GCC optimize("Ofast")

typedef struct cell
{
    int mem_addr;
    int data;
} cell_t;

typedef struct hash
{
    cell_t *table;
    int cache_size;
} hash_t;
typedef hash_t cache_t;
typedef int memory_t;
memory_t *init_memory(int size)
{
    memory_t *memory = (memory_t *)malloc(
        sizeof(memory_t) * size);
    int i = 0;
    for (i = 0; i < size; i++)
        memory[i] = rand();
    return memory;
}

cache_t *init_cache(int cache_size)
{
    cache_t *cache = (cache_t *)malloc(sizeof(cache_t));
    cache->cache_size = cache_size;
    cache->table = (cell_t *)malloc(cache_size * sizeof(cell_t));
    memset(cache->table, 0, cache_size * sizeof(cell_t));
    return cache;
}

void get_data(int address, memory_t *memory, cache_t *cache)
{
    int i = address % cache->cache_size;
    if (cache->table[i].data == 0)
    {
        printf("Load from memory\n");
        cache->table[i].data = memory[address];
        cache->table[i].mem_addr = address;
    }
    else if (cache->table[i].data == memory[address])
    {
        printf("Address %d is loaded\n", address);
    }
    else
    {
        printf("Index: %d is used\n", i);
        cache->table[i].data = memory[address];
        cache->table[i].mem_addr = address;
        printf("Load from memory\n");
    }
    printf("Data: %d\n", memory[address]);
}

int main(void)
{
    memory_t *memory = NULL;
    cache_t *cache = NULL;
    int memory_size, cache_size;
    int i, n, addr;
    scanf("%d %d %d", &memory_size, &cache_size, &n);
    memory = init_memory(memory_size);
    cache = init_cache(cache_size);
    for (i = 0; i < n; i++)
    {
        printf("Load address: ");
        scanf("%d", &addr);
        get_data(addr, memory, cache);
    }

    return 0;
}