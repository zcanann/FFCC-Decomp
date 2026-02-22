#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/alloc.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/critical_regions.h"
#include "string.h"

typedef struct Block {
    struct Block* prev;
    struct Block* next;
    unsigned long max_size;
    unsigned long size;
} Block;

typedef struct SubBlock {
    unsigned long size;
    Block* block;
    struct SubBlock* prev;
    struct SubBlock* next;
} SubBlock;

struct FixSubBlock;

typedef struct FixBlock {
    struct FixBlock* prev_;
    struct FixBlock* next_;
    unsigned long client_size_;
    struct FixSubBlock* start_;
    unsigned long n_allocated_;
} FixBlock;

typedef struct FixSubBlock {
    FixBlock* block_;
    struct FixSubBlock* next_;
} FixSubBlock;

typedef struct FixStart {
    FixBlock* tail_;
    FixBlock* head_;
} FixStart;

typedef struct __mem_pool_obj {
    Block* start_;
    FixStart fix_start[6];
} __mem_pool_obj;

typedef struct __mem_pool {
    void* reserved[14];
} __mem_pool;

typedef long tag_word;

typedef struct block_header {
    tag_word tag;
    struct block_header* prev;
    struct block_header* next;
} block_header;

typedef struct list_header {
    block_header* rover;
    block_header header;
} list_header;

typedef struct heap_header {
    struct heap_header* prev;
    struct heap_header* next;
} heap_header;

struct mem_pool_obj;
typedef void* (*sys_alloc_ptr)(unsigned long, struct mem_pool_obj*);
typedef void (*sys_free_ptr)(void*, struct mem_pool_obj*);

typedef struct pool_options {
    sys_alloc_ptr sys_alloc_func;
    sys_free_ptr sys_free_func;
    unsigned long min_heap_size;
    int always_search_first;
} pool_options;

typedef struct mem_pool_obj {
    list_header free_list;
    pool_options options;
    heap_header* heap_list;
    void* userData;

} mem_pool_obj;

mem_pool_obj __malloc_pool;
static int initialized = 0;

static SubBlock* SubBlock_merge_prev(SubBlock*, SubBlock**);
static void SubBlock_merge_next(SubBlock*, SubBlock**);
static Block* link_new_block(__mem_pool_obj* pool_obj, unsigned long size);
static void Block_construct(Block* block, unsigned long size);
static SubBlock* Block_subBlock(Block* block, unsigned long requested_size);

static const unsigned long fix_pool_sizes[] = {4, 12, 20, 36, 52, 68};

#define SubBlock_size(ths) ((ths)->size & 0xFFFFFFF8)
#define SubBlock_block(ths) ((Block*)((unsigned long)((ths)->block) & ~0x1))
#define Block_size(ths) ((ths)->size & 0xFFFFFFF8)
#define Block_start(ths) (*(SubBlock**)((char*)(ths) + Block_size((ths)) - sizeof(unsigned long)))

#define SubBlock_set_free(ths) do {                                                                \
    unsigned long this_size = SubBlock_size((ths));                                                \
    (ths)->size &= ~0x2;                                                                           \
    *(unsigned long*)((char*)(ths) + this_size) &= ~0x4;                                           \
    *(unsigned long*)((char*)(ths) + this_size - sizeof(unsigned long)) = this_size;               \
} while(0)

#define SubBlock_is_free(ths) !((ths)->size & 2)
#define SubBlock_set_size(ths, sz) do {                                                            \
    (ths)->size &= ~0xFFFFFFF8;                                                                    \
    (ths)->size |= (sz) & 0xFFFFFFF8;                                                              \
    if (SubBlock_is_free((ths)))                                                                   \
        *(unsigned long*)((char*)(ths) + (sz) - sizeof(unsigned long)) = (sz);                    \
} while(0)

#define SubBlock_from_pointer(ptr) ((SubBlock*)((char*)(ptr)-8))
#define FixSubBlock_from_pointer(ptr) ((FixSubBlock*)((char*)(ptr)-4))

#define FixBlock_client_size(ths) ((ths)->client_size_)
#define FixSubBlock_size(ths) (FixBlock_client_size((ths)->block_))

#define classify(ptr) (*(unsigned long*)((char*)(ptr) - sizeof(unsigned long)) & 1)
#define __msize_inline(ptr)                                                                        \
    (!classify(ptr) ? FixSubBlock_size(FixSubBlock_from_pointer(ptr)) :                            \
                      SubBlock_size(SubBlock_from_pointer(ptr)) - 8)

#define Block_empty(ths)                                                                           \
    (_sb = (SubBlock*)((char*)(ths) + 16)),                                                        \
        SubBlock_is_free(_sb) && SubBlock_size(_sb) == Block_size((ths)) - 24

void __sys_free();
void* __sys_alloc(unsigned long size);

static inline SubBlock* SubBlock_merge_prev(SubBlock* ths, SubBlock** start) {
    unsigned long prevsz;
    SubBlock* p;

    if (!(ths->size & 0x04)) {
        prevsz = *(unsigned long*)((char*)ths - sizeof(unsigned long));
        if (prevsz & 0x2)
            return ths;
        p = (SubBlock*)((char*)ths - prevsz);
        SubBlock_set_size(p, prevsz + SubBlock_size(ths));

        if (*start == ths)
            *start = (*start)->next;
        ths->next->prev = ths->prev;
        ths->next->prev->next = ths->next;
        return p;
    }
    return ths;
}

static inline void SubBlock_merge_next(SubBlock* pBlock, SubBlock** pStart) {
    SubBlock* next_sub_block;
    unsigned long this_cur_size;

    next_sub_block = (SubBlock*)((char*)pBlock + (pBlock->size & 0xFFFFFFF8));

    if (!(next_sub_block->size & 2)) {
        this_cur_size = (pBlock->size & 0xFFFFFFF8) + (next_sub_block->size & 0xFFFFFFF8);

        pBlock->size &= ~0xFFFFFFF8;
        pBlock->size |= this_cur_size & 0xFFFFFFF8;

        if (!(pBlock->size & 2)) {
            *(unsigned long*)((char*)(pBlock) + (this_cur_size)-4) = (this_cur_size);
        }

        if (!(pBlock->size & 2)) {
            *(unsigned long*)((char*)pBlock + this_cur_size) &= ~4;
        } else {
            *(unsigned long*)((char*)pBlock + this_cur_size) |= 4;
        }

        if (*pStart == next_sub_block) {
            *pStart = (*pStart)->next;
        }

        if (*pStart == next_sub_block) {
            *pStart = 0;
        }

        next_sub_block->next->prev = next_sub_block->prev;
        next_sub_block->prev->next = next_sub_block->next;
    }
}

inline void Block_link(Block* ths, SubBlock* sb) {
    SubBlock** st;
    SubBlock_set_free(sb);
    st = &Block_start(ths);

    if (*st != 0) {
        sb->prev = (*st)->prev;
        sb->prev->next = sb;
        sb->next = *st;
        (*st)->prev = sb;
        *st = sb;
        *st = SubBlock_merge_prev(*st, st);
        SubBlock_merge_next(*st, st);
    } else {
        *st = sb;
        sb->prev = sb;
        sb->next = sb;
    }
    if (ths->max_size < SubBlock_size(*st))
        ths->max_size = SubBlock_size(*st);
}

static inline Block* __unlink(__mem_pool_obj* pool_obj, Block* bp) {
    Block* result = bp->next;
    if (result == bp) {
        result = 0;
    }

    if (pool_obj->start_ == bp) {
        pool_obj->start_ = result;
    }

    if (result != 0) {
        result->prev = bp->prev;
        result->prev->next = result;
    }

    bp->next = 0;
    bp->prev = 0;
    return result;
}

static void deallocate_from_var_pools(__mem_pool_obj* pool_obj, void* ptr) {
    SubBlock* sb = SubBlock_from_pointer(ptr);
    SubBlock* _sb;

    Block* bp = SubBlock_block(sb);
    Block_link(bp, sb);

    if (Block_empty(bp)) {
        __unlink(pool_obj, bp);
        __sys_free(bp);
    }
}

inline void __init_pool_obj(__mem_pool* pool_obj) {
    memset(pool_obj, 0, sizeof(__mem_pool_obj));
}

static inline __mem_pool* get_malloc_pool(void) {
    static __mem_pool protopool;
    static unsigned char init = 0;
    if (!init) {
        __init_pool_obj(&protopool);
        init = 1;
    }

    return &protopool;
}

void deallocate_from_fixed_pools(__mem_pool_obj* pool_obj, void* ptr, unsigned long size) {
    unsigned long i = 0;
    FixSubBlock* p;
    FixBlock* b;
    FixStart* fs;

    while (size > fix_pool_sizes[i]) {
        ++i;
    }

    fs = &pool_obj->fix_start[i];
    p = FixSubBlock_from_pointer(ptr);
    b = p->block_;

    if (b->start_ == 0 && fs->head_ != b) {
        if (fs->tail_ == b) {
            fs->head_ = fs->head_->prev_;
            fs->tail_ = fs->tail_->prev_;
        } else {
            b->prev_->next_ = b->next_;
            b->next_->prev_ = b->prev_;
            b->next_ = fs->head_;
            b->prev_ = b->next_->prev_;
            b->prev_->next_ = b;
            b->next_->prev_ = b;
            fs->head_ = b;
        }
    }

    p->next_ = b->start_;
    b->start_ = p;

    if (--b->n_allocated_ == 0) {
        if (fs->head_ == b) {
            fs->head_ = b->next_;
        }

        if (fs->tail_ == b) {
            fs->tail_ = b->prev_;
        }

        b->prev_->next_ = b->next_;
        b->next_->prev_ = b->prev_;

        if (fs->head_ == b) {
            fs->head_ = 0;
        }

        if (fs->tail_ == b) {
            fs->tail_ = 0;
        }

        deallocate_from_var_pools(pool_obj, b);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801B27F4
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static Block* link_new_block(__mem_pool_obj* pool_obj, unsigned long size) {
    Block* block;
    Block* start;
    unsigned long aligned_size;

    aligned_size = (size + 0x1FUL) & 0xFFFFFFF8;
    if (aligned_size < 0x10000) {
        aligned_size = 0x10000;
    }

    block = (Block*)__sys_alloc(aligned_size);
    if (block == 0) {
        return 0;
    }

    Block_construct(block, aligned_size);
    start = pool_obj->start_;
    if (start != 0) {
        block->prev = start->prev;
        block->prev->next = block;
        block->next = start;
        block->next->prev = block;
    } else {
        block->prev = block;
        block->next = block;
    }
    pool_obj->start_ = block;
    return block;
}

/*
 * --INFO--
 * PAL Address: 0x801B2A8C
 * PAL Size: 568b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void Block_construct(Block* block, unsigned long size) {
    SubBlock* sb;

    block->size = size | 3;
    sb = (SubBlock*)((char*)block + 16);
    sb->size = size - 24;
    sb->block = (Block*)((unsigned long)block | 1);
    block->max_size = size - 24;
    Block_start(block) = 0;
    Block_link(block, sb);
}

/*
 * --INFO--
 * PAL Address: 0x801B28A8
 * PAL Size: 484b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static SubBlock* Block_subBlock(Block* block, unsigned long requested_size) {
    unsigned long current_size;
    int start_offset;
    unsigned long* start;
    unsigned long* current;
    unsigned long max_size;

    start_offset = (block->size & 0xFFFFFFF8UL) - 4;
    start = *(unsigned long**)((char*)block + start_offset);
    if (start == 0) {
        block->max_size = 0;
        return 0;
    }

    current_size = *start & 0xFFFFFFF8UL;
    current = start;
    max_size = current_size;
    do {
        if (requested_size <= current_size) {
            if (0x4F < current_size - requested_size) {
                unsigned long* split_block;
                unsigned long old_size_flags;
                unsigned long block_flags;
                unsigned long prev_used_clz;
                unsigned long prev_used_is_zero_clz;

                split_block = (unsigned long*)((char*)current + requested_size);
                old_size_flags = *current;
                block_flags = current[1] & 0xFFFFFFFEUL | 1;
                current[1] = block_flags;
                prev_used_clz = __cntlzw(old_size_flags & 2);
                *current = requested_size;
                prev_used_is_zero_clz = __cntlzw(prev_used_clz >> 5);
                if ((old_size_flags & 4) != 0) {
                    *current |= 4;
                }
                if ((prev_used_is_zero_clz >> 5) == 0) {
                    split_block[-1] = requested_size;
                } else {
                    *current |= 2;
                    *split_block |= 4;
                }
                split_block[1] = block_flags;
                requested_size = (old_size_flags & 0xFFFFFFF8UL) - requested_size;
                *split_block = requested_size;
                if ((prev_used_is_zero_clz >> 5) == 0) {
                    *(unsigned long*)((char*)split_block + requested_size - 4) = requested_size;
                } else {
                    *split_block |= 4;
                    *split_block |= 2;
                    *(unsigned long*)((char*)split_block + requested_size) |= 4;
                }
                if ((prev_used_clz >> 5) != 0) {
                    split_block[3] = current[3];
                    *(unsigned long*)(split_block[3] + 8) = (unsigned long)split_block;
                    split_block[2] = (unsigned long)current;
                    current[3] = (unsigned long)split_block;
                }
            }

            *(unsigned long**)((char*)block + ((block->size & 0xFFFFFFF8UL) - 4)) = (unsigned long*)current[3];
            current_size = *current & 0xFFFFFFF8UL;
            *current |= 2;
            *(unsigned long*)((char*)current + current_size) |= 4;
            start_offset = (block->size & 0xFFFFFFF8UL) - 4;
            if (*(unsigned long**)((char*)block + start_offset) == current) {
                *(unsigned long**)((char*)block + start_offset) = (unsigned long*)current[3];
            }
            if (*(unsigned long**)((char*)block + start_offset) == current) {
                *(unsigned long**)((char*)block + start_offset) = 0;
                block->max_size = 0;
            } else {
                *(unsigned long*)(current[3] + 8) = current[2];
                *(unsigned long*)(current[2] + 12) = current[3];
            }
            return (SubBlock*)current;
        }

        current = (unsigned long*)current[3];
        current_size = *current & 0xFFFFFFF8UL;
        if (max_size < current_size) {
            max_size = current_size;
        }
    } while (current != start);

    block->max_size = max_size;
    return 0;
}

static void* allocate_from_var_pools(__mem_pool_obj* pool_obj, unsigned long size) {
    unsigned long aligned_size;
    Block* current_block;
    SubBlock* result;
    
    aligned_size = (size + 0xF) & 0xFFFFFFF8;
    if (aligned_size < 0x50) {
        aligned_size = 0x50;
    }
    
    current_block = pool_obj->start_;
    if (current_block == 0) {
        current_block = link_new_block(pool_obj, aligned_size);
    }
    
    if (current_block == 0) {
        return 0;
    }
    
    do {
        if (aligned_size <= current_block->max_size) {
            result = Block_subBlock(current_block, aligned_size);
            if (result != 0) {
                pool_obj->start_ = current_block;
                return (char*)result + 8;
            }
        }
        current_block = current_block->next;
    } while (current_block != pool_obj->start_);
    
    current_block = link_new_block(pool_obj, aligned_size);
    if (current_block == 0) {
        return 0;
    }
    
    result = Block_subBlock(current_block, aligned_size);
    if (result != 0) {
        return (char*)result + 8;
    }
    
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801b2640
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void* soft_allocate_from_var_pools(__mem_pool_obj* pool_obj, unsigned long size, unsigned long* available_size) {
    unsigned long aligned_size;
    Block* current_block;
    SubBlock* result;
    
    aligned_size = (size + 0xF) & 0xFFFFFFF8;
    if (aligned_size < 0x50) {
        aligned_size = 0x50;
    }
    
    *available_size = 0;
    current_block = pool_obj->start_;

    if (current_block == 0) {
        return 0;
    }

    do {
        if ((aligned_size <= current_block->max_size) &&
            ((result = Block_subBlock(current_block, aligned_size)) != 0)) {
            pool_obj->start_ = current_block;
            return (char*)result + 8;
        }

        if ((8 < current_block->max_size) &&
            (*available_size < current_block->max_size - 8)) {
            *available_size = current_block->max_size - 8;
        }

        current_block = current_block->next;
    } while (current_block != pool_obj->start_);

    return 0;
}

static void* allocate_from_fixed_pools(__mem_pool_obj* pool_obj, unsigned long size) {
    const unsigned long* pool_size_ptr;
    FixStart* fix_start;
    FixBlock* block;
    FixBlock* head_block;
    FixSubBlock* current_sub;
    FixSubBlock* sub_block;
    unsigned long pool_index;
    unsigned long entry_size;
    unsigned long client_size;
    unsigned long max_block_count;
    unsigned long block_count;
    unsigned long available_space;
    unsigned long local_available[4];
    unsigned long i;
    void* allocation_ptr;

    for (pool_index = 0, pool_size_ptr = fix_pool_sizes; *pool_size_ptr < size; pool_size_ptr++, pool_index++) {
    }

    fix_start = &pool_obj->fix_start[pool_index];
    if ((fix_start->head_ == 0) || (fix_start->head_->start_ == 0)) {
        client_size = *pool_size_ptr;
        entry_size = client_size + 4;
        max_block_count = 0xFEC / entry_size;
        block_count = max_block_count;
        if (max_block_count > 0x100) {
            max_block_count = 0x100;
            block_count = max_block_count;
        }

        allocation_ptr = pool_obj;
        while ((9 < block_count) &&
               ((allocation_ptr =
                     soft_allocate_from_var_pools(pool_obj, block_count * entry_size + 0x14, local_available)) == 0)) {
            if (local_available[0] < 0x15) {
                block_count = 0;
            } else {
                block_count = (local_available[0] - 0x14) / entry_size;
            }
        }

        if (((allocation_ptr == 0) && (block_count < max_block_count)) &&
            ((allocation_ptr = allocate_from_var_pools(pool_obj, max_block_count * entry_size + 0x14)) == 0)) {
            return 0;
        }

        block = (FixBlock*)((char*)allocation_ptr - 8);
        if ((*(unsigned long*)((char*)block - 4) & 1) == 0) {
            available_space = *(unsigned long*)(*(unsigned long*)((char*)block - 4) + 8);
        } else {
            available_space = (*(unsigned long*)((char*)block - 8) & 0xFFFFFFF8) - 8;
        }

        if (fix_start->head_ == 0) {
            fix_start->head_ = block;
            fix_start->tail_ = block;
        }

        block_count = (available_space - 0x14) / entry_size;
        head_block = fix_start->head_;
        block->prev_ = fix_start->tail_;
        block->next_ = head_block;
        fix_start->tail_->next_ = block;
        head_block->prev_ = block;

        block->client_size_ = client_size;
        current_sub = (FixSubBlock*)((char*)block + 0x14);
        block->start_ = current_sub;
        block->n_allocated_ = 0;

        for (i = 1; i < block_count; i++) {
            current_sub->block_ = block;
            current_sub->next_ = (FixSubBlock*)((char*)current_sub + entry_size);
            current_sub = current_sub->next_;
        }
        current_sub->block_ = block;
        current_sub->next_ = 0;

        fix_start->head_ = block;
    }

    sub_block = fix_start->head_->start_;
    fix_start->head_->start_ = sub_block->next_;
    fix_start->head_->n_allocated_++;

    if (fix_start->head_->start_ == 0) {
        fix_start->head_ = fix_start->head_->next_;
        fix_start->tail_ = fix_start->tail_->next_;
    }

    return (char*)sub_block + 4;
}

/*
 * --INFO--
 * PAL Address: 0x801b1f30
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* __pool_alloc(__mem_pool* pool, unsigned long size) {
    __mem_pool_obj* pool_obj;

    if (size == 0) {
        return 0;
    }

    if (size >= 0xFFFFFFD0UL) {
        return 0;
    }

    pool_obj = (__mem_pool_obj*)pool;
    if (size <= 68) {
        return allocate_from_fixed_pools(pool_obj, size);
    }

    return allocate_from_var_pools(pool_obj, size);
}

/*
 * --INFO--
 * PAL Address: 0x801b1e5c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* malloc(size_t size) {
    void* ptr;

    __begin_critical_region(malloc_pool_access);
    ptr = __pool_alloc(get_malloc_pool(), size);
    __end_critical_region(malloc_pool_access);
    return ptr;
}

void __pool_free(__mem_pool* pool, void* ptr) {
    __mem_pool_obj* pool_obj;
    unsigned long size;

    if (ptr == 0) {
        return;
    }

    pool_obj = (__mem_pool_obj*)pool;
    size = __msize_inline(ptr);

    if (size <= 68) {
        deallocate_from_fixed_pools(pool_obj, ptr, size);
    } else {
        deallocate_from_var_pools(pool_obj, ptr);
    }
}

void free(void* ptr) {
    __begin_critical_region(malloc_pool_access);
    __pool_free(get_malloc_pool(), ptr);
    __end_critical_region(malloc_pool_access);
}
