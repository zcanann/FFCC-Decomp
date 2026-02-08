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
    unsigned long aligned_size;

    aligned_size = (size + 0x1F) & 0xFFFFFFF8;
    if (aligned_size < 0x10000) {
        aligned_size = 0x10000;
    }

    block = (Block*)__sys_alloc(aligned_size);
    if (block != 0) {
        Block_construct(block, aligned_size);
        if (pool_obj->start_ == 0) {
            pool_obj->start_ = block;
            block->prev = block;
            block->next = block;
        } else {
            block->prev = pool_obj->start_->prev;
            block->prev->next = block;
            block->next = pool_obj->start_;
            block->next->prev = block;
            pool_obj->start_ = block;
        }
    }
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

static SubBlock* Block_subBlock(Block* block, unsigned long requested_size) {
    SubBlock** start_ptr;
    SubBlock* current;
    SubBlock* best_fit = 0;
    unsigned long current_size;
    unsigned long best_size = 0xFFFFFFFF;
    
    start_ptr = &Block_start(block);
    current = *start_ptr;
    
    if (current == 0) {
        block->max_size = 0;
        return 0;
    }
    
    do {
        current_size = SubBlock_size(current);
        if (requested_size <= current_size) {
            if (current_size < best_size) {
                best_fit = current;
                best_size = current_size;
            }
        }
        current = current->next;
    } while (current != *start_ptr);
    
    if (best_fit == 0) {
        return 0;
    }
    
    if (best_size > requested_size + 80) {
        SubBlock* remainder = (SubBlock*)((char*)best_fit + requested_size);
        remainder->size = best_size - requested_size;
        remainder->block = best_fit->block;
        remainder->next = best_fit->next;
        remainder->prev = best_fit;
        best_fit->next->prev = remainder;
        best_fit->next = remainder;
        
        SubBlock_set_size(best_fit, requested_size);
        SubBlock_set_free(remainder);
    }
    
    if (*start_ptr == best_fit) {
        *start_ptr = best_fit->next;
    }
    if (*start_ptr == best_fit) {
        *start_ptr = 0;
        block->max_size = 0;
    } else {
        best_fit->next->prev = best_fit->prev;
        best_fit->prev->next = best_fit->next;
    }
    
    best_fit->size |= 2;
    
    return best_fit;
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

static void* soft_allocate_from_var_pools(__mem_pool_obj* pool_obj, unsigned long size, unsigned long* available_size) {
    unsigned long aligned_size;
    Block* current_block;
    SubBlock* result;
    unsigned long block_available;
    
    aligned_size = (size + 0xF) & 0xFFFFFFF8;
    if (aligned_size < 0x50) {
        aligned_size = 0x50;
    }
    
    *available_size = 0;
    current_block = pool_obj->start_;
    
    if (current_block != 0) {
        do {
            if (aligned_size <= current_block->max_size) {
                result = Block_subBlock(current_block, aligned_size);
                if (result != 0) {
                    pool_obj->start_ = current_block;
                    return (char*)result + 8;
                }
            }
            
            if (current_block->max_size > 8) {
                block_available = current_block->max_size - 8;
                if (*available_size < block_available) {
                    *available_size = block_available;
                }
            }
            
            current_block = current_block->next;
        } while (current_block != pool_obj->start_);
    }
    
    return 0;
}

static void* allocate_from_fixed_pools(__mem_pool_obj* pool_obj, unsigned long size) {
    unsigned long pool_index = 0;
    FixStart* fix_start;
    FixBlock* block;
    FixSubBlock* sub_block;
    FixSubBlock* current_sub;
    FixSubBlock* new_sub;
    void* allocation_ptr;
    unsigned long block_count;
    unsigned long client_size;
    unsigned long total_size;
    unsigned long available_space;
    unsigned long local_array[4];
    unsigned long i;
    
    // Find the appropriate fixed pool size
    while (size > fix_pool_sizes[pool_index]) {
        pool_index++;
    }
    
    fix_start = &pool_obj->fix_start[pool_index];
    
    // Check if we need to allocate a new block
    if (fix_start->head_ == 0 || fix_start->head_->start_ == 0) {
        block_count = 0xFEC / (fix_pool_sizes[pool_index] + 4);
        if (block_count > 0x100) {
            block_count = 0x100;
        }
        
        // Try soft allocation first
        while (block_count > 9) {
            allocation_ptr = soft_allocate_from_var_pools(pool_obj, 
                block_count * (fix_pool_sizes[pool_index] + 4) + 0x14, local_array);
            if (allocation_ptr != 0) {
                break;
            }
            
            if (local_array[0] < 0x15) {
                block_count = 0;
            } else {
                block_count = (local_array[0] - 0x14) / (fix_pool_sizes[pool_index] + 4);
            }
        }
        
        // If soft allocation failed, try hard allocation
        if (allocation_ptr == 0 && block_count < 0x100) {
            allocation_ptr = allocate_from_var_pools(pool_obj, 
                0x100 * (fix_pool_sizes[pool_index] + 4) + 0x14);
            if (allocation_ptr == 0) {
                return 0;
            }
        }
        
        // Get the actual available space
        block = (FixBlock*)((char*)allocation_ptr - 8);
        if ((*(unsigned long*)((char*)block - 4) & 1) == 0) {
            available_space = *(unsigned long*)(*(unsigned long*)((char*)block - 4) + 8);
        } else {
            available_space = (*(unsigned long*)((char*)block - 8) & 0xFFFFFFF8) - 8;
        }
        
        // Initialize the block
        if (fix_start->head_ == 0) {
            fix_start->head_ = block;
            fix_start->tail_ = block;
        }
        
        client_size = fix_pool_sizes[pool_index];
        total_size = client_size + 4;
        block_count = (available_space - 0x14) / total_size;
        
        // Set up block linkage
        if (fix_start->tail_ != 0) {
            block->prev_ = fix_start->tail_;
            block->next_ = fix_start->head_;
            fix_start->tail_->next_ = block;
            fix_start->head_->prev_ = block;
        } else {
            block->prev_ = block;
            block->next_ = block;
        }
        
        block->client_size_ = client_size;
        
        // Initialize the sub-block chain
        current_sub = (FixSubBlock*)((char*)block + 0x14);
        block->start_ = current_sub;
        block->n_allocated_ = 0;
        
        for (i = 0; i < block_count; i++) {
            current_sub->block_ = block;
            if (i < block_count - 1) {
                new_sub = (FixSubBlock*)((char*)current_sub + total_size);
                current_sub->next_ = new_sub;
                current_sub = new_sub;
            } else {
                current_sub->next_ = 0;
            }
        }
        
        fix_start->head_ = block;
    }
    
    // Allocate from the existing block
    sub_block = fix_start->head_->start_;
    fix_start->head_->start_ = sub_block->next_;
    fix_start->head_->n_allocated_++;
    
    if (fix_start->head_->start_ == 0) {
        fix_start->head_ = fix_start->head_->next_;
        if (fix_start->tail_->next_ == fix_start->head_) {
            fix_start->tail_ = fix_start->tail_->prev_;
        }
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
