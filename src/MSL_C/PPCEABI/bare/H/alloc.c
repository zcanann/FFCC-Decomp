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

static unsigned char initialized = 0;


static void SubBlock_construct(SubBlock* ths, unsigned long size, Block* bp, int prev_alloc, int this_alloc);
static SubBlock* SubBlock_split(SubBlock* ths, unsigned long sz);
static SubBlock* SubBlock_merge_prev(SubBlock*, SubBlock**);
static void SubBlock_merge_next(SubBlock*, SubBlock**);
static Block* link_new_block(__mem_pool_obj* pool_obj, unsigned long size);
static void Block_construct(Block* block, unsigned long size);
static void Block_unlink(Block* block, SubBlock* sb);
static SubBlock* Block_subBlock(Block* block, unsigned long requested_size);
static void* allocate_from_var_pools(__mem_pool_obj* pool_obj, unsigned long size);
static void* soft_allocate_from_var_pools(__mem_pool_obj* pool_obj, unsigned long size, unsigned long* available_size);
static void deallocate_from_var_pools(__mem_pool_obj* pool_obj, void* ptr);
static void* allocate_from_fixed_pools(__mem_pool_obj* pool_obj, unsigned long size);
static void deallocate_from_fixed_pools(__mem_pool_obj* pool_obj, void* ptr, unsigned long size);

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
#define FixSubBlock_construct(ths, block, next) \
    (((FixSubBlock*)(ths))->block_ = (block), ((FixSubBlock*)(ths))->next_ = (next))

#define classify(ptr) (*(unsigned long*)((char*)(ptr) - sizeof(unsigned long)) & 1)
#define __msize_inline(ptr)                                                                        \
    (!classify(ptr) ? FixSubBlock_size(FixSubBlock_from_pointer(ptr)) :                            \
                      SubBlock_size(SubBlock_from_pointer(ptr)) - 8)

#define Block_empty(ths)                                                                           \
    (_sb = (SubBlock*)((char*)(ths) + 16)),                                                        \
        SubBlock_is_free(_sb) && SubBlock_size(_sb) == Block_size((ths)) - 24

void __sys_free(void*);
void* __sys_alloc(unsigned long size);

static unsigned long __msize(void* ptr) {
    return __msize_inline(ptr);
}

static SubBlock* SubBlock_merge_prev(SubBlock* ths, SubBlock** start) {
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

static void SubBlock_merge_next(SubBlock* pBlock, SubBlock** pStart) {
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

static void Block_link(Block* ths, SubBlock* sb) {
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

static Block* __unlink(__mem_pool_obj* pool_obj, Block* bp) {
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

static void __init_pool_obj(__mem_pool* pool_obj) {
    memset(pool_obj, 0, sizeof(__mem_pool_obj));
}

static __mem_pool* get_malloc_pool(void) {
    static __mem_pool protopool;
    static unsigned char init = 0;
    if (!initialized) {
        __init_pool_obj(&protopool);
        initialized = 1;
    }

    return &protopool;
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
    *(unsigned long*)((char*)block + size - 8) = block->size;
    sb = (SubBlock*)((char*)block + 16);
    sb->block = (Block*)((unsigned long)block | 1);
    size -= 24;
    sb->size = size;
    *(unsigned long*)((char*)sb + size - sizeof(unsigned long)) = size;
    block->max_size = size;
    *(SubBlock**)((char*)block + (block->size & 0xFFFFFFF8UL) - 4) = 0;
    Block_link(block, sb);
}

static void SubBlock_construct(SubBlock* ths, unsigned long size, Block* bp, int prev_alloc, int this_alloc) {
    ths->block = (Block*)((unsigned long)bp | 0x1);
    ths->size = size;
    if (prev_alloc) {
        ths->size |= 0x4;
    }
    if (this_alloc) {
        ths->size |= 0x2;
        *(unsigned long*)((char*)ths + size) |= 0x4;
    } else {
        *(unsigned long*)((char*)ths + size - sizeof(unsigned long)) = size;
    }
}

static SubBlock* SubBlock_split(SubBlock* ths, unsigned long sz) {
    unsigned long origsize;
    int isfree;
    int isprevalloc;
    SubBlock* np;
    Block* bp;

    origsize = SubBlock_size(ths);
    isfree = SubBlock_is_free(ths);
    isprevalloc = ths->size & 0x04;
    np = (SubBlock*)((char*)ths + sz);
    bp = SubBlock_block(ths);

    SubBlock_construct(ths, sz, bp, isprevalloc, !isfree);
    SubBlock_construct(np, origsize - sz, bp, !isfree, !isfree);
    if (isfree) {
        np->next = ths->next;
        np->next->prev = np;
        np->prev = ths;
        ths->next = np;
    }
    return np;
}

static void Block_unlink(Block* block, SubBlock* sb) {
    SubBlock** st;
    unsigned long tag;
    unsigned long tag_size;

    tag = sb->size;
    sb->size = tag | 2;
    tag_size = tag & ~7;
    *(unsigned long*)((char*)sb + tag_size) |= 4;

    st = &Block_start(block);
    if (*st == sb) {
        *st = sb->next;
    }
    if (*st == sb) {
        *st = 0;
        block->max_size = 0;
    } else {
        sb->next->prev = sb->prev;
        sb->prev->next = sb->next;
    }
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
    SubBlock* sb;
    SubBlock* start;
    unsigned long sb_size;
    unsigned long max_size;

    start = Block_start(block);
    if (start == 0) {
        block->max_size = 0;
        return 0;
    }

    sb = start;
    sb_size = SubBlock_size(sb);
    max_size = sb_size;

    while (sb_size < requested_size) {
        sb = sb->next;
        sb_size = SubBlock_size(sb);
        if (max_size < sb_size) {
            max_size = sb_size;
        }
        if (sb == start) {
            block->max_size = max_size;
            return 0;
        }
    }

    if (sb_size - requested_size >= 0x50) {
        SubBlock_split(sb, requested_size);
    }

    Block_start(block) = sb->next;
    Block_unlink(block, sb);

    return sb;
}

static void link(__mem_pool_obj* pool_obj, Block* bp) {
    if (pool_obj->start_ != 0) {
        bp->prev = pool_obj->start_->prev;
        bp->prev->next = bp;
        bp->next = pool_obj->start_;
        pool_obj->start_->prev = bp;
        pool_obj->start_ = bp;
    } else {
        pool_obj->start_ = bp;
        bp->prev = bp;
        bp->next = bp;
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

    aligned_size = (size + 0x1FUL) & 0xFFFFFFF8;
    if (aligned_size < 0x10000) {
        aligned_size = 0x10000;
    }

    block = (Block*)__sys_alloc(aligned_size);
    if (block == 0) {
        return 0;
    }

    Block_construct(block, aligned_size);
    link(pool_obj, block);
    return block;
}

static void* allocate_from_var_pools(__mem_pool_obj* pool_obj, unsigned long size) {
    Block* block;
    Block* current_block;
    void* result;
    unsigned long aligned_size;

    aligned_size = (size + 0xFUL) & 0xFFFFFFF8UL;
    if (aligned_size < 0x50UL) {
        aligned_size = 0x50UL;
    }

    if (pool_obj->start_ != 0) {
        block = pool_obj->start_;
    } else {
        block = link_new_block(pool_obj, aligned_size);
    }

    current_block = block;
    if (current_block == 0) {
        result = 0;
    } else {
        do {
            if ((aligned_size <= current_block->max_size) &&
                ((result = Block_subBlock(current_block, aligned_size)) != 0)) {
                pool_obj->start_ = current_block;
                goto done;
            }
            current_block = current_block->next;
        } while (current_block != pool_obj->start_);

        current_block = link_new_block(pool_obj, aligned_size);
        if (current_block == 0) {
            result = 0;
        } else {
            result = Block_subBlock(current_block, aligned_size);
done:
            result = (char*)result + 8;
        }
    }

    return result;
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
    Block* current_block;
    SubBlock* result;

    size = (size + 0xFU) & 0xFFFFFFF8;
    if (size < 0x50) {
        size = 0x50;
    }
    *available_size = 0;
    current_block = pool_obj->start_;
    if (current_block == 0) {
        return 0;
    }

    do {
        if (size <= current_block->max_size) {
            result = Block_subBlock(current_block, size);
            if (result != 0) {
                pool_obj->start_ = current_block;
                goto found;
            }
        }
        if ((8 < current_block->max_size) && (*available_size < current_block->max_size - 8)) {
            *available_size = current_block->max_size - 8;
        }
        current_block = current_block->next;
    } while (current_block != pool_obj->start_);

    return 0;
found:
    return (char*)result + 8;
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

static void FixBlock_construct(FixBlock* ths, FixBlock* prev, FixBlock* next, unsigned long index, FixSubBlock* chunk, unsigned long chunk_size) {
    unsigned long fixSubBlock_size;
    unsigned long n;
    char* p;
    unsigned long k;
    char* np;

    ths->prev_ = prev;
    ths->next_ = next;
    prev->next_ = ths;
    next->prev_ = ths;
    ths->client_size_ = fix_pool_sizes[index];
    fixSubBlock_size = fix_pool_sizes[index] + 4;
    n = chunk_size / fixSubBlock_size;
    ths->start_ = chunk;
    p = (char*)chunk;
    for (k = 0; k < n - 1; k++) {
        np = p + fixSubBlock_size;
        ((FixSubBlock*)p)->block_ = ths;
        ((FixSubBlock*)p)->next_ = (FixSubBlock*)np;
        p = np;
    }
    ((FixSubBlock*)p)->block_ = ths;
    ((FixSubBlock*)p)->next_ = 0;
    ths->n_allocated_ = 0;
}
static void* allocate_from_fixed_pools(__mem_pool_obj* pool_obj, unsigned long size) {
    unsigned long i = 0;
    FixStart* fs;

    while (size > fix_pool_sizes[i]) {
        ++i;
    }

    fs = &pool_obj->fix_start[i];

    if ((fs->head_ == 0) || (fs->head_->start_ == 0)) {
        const unsigned long* pool_sizes = fix_pool_sizes;
        unsigned long n = 0xFEC / (pool_sizes[i] + 4);
        unsigned long max_n;
        void* block;
        unsigned long max_free_size;
        unsigned long msize;

        if (n > 0x100) {
            n = 0x100;
        }

        max_n = n;

        while (n >= 10) {
            block = soft_allocate_from_var_pools(pool_obj, n * (pool_sizes[i] + 4) + 0x14, &max_free_size);
            if (block != 0) {
                break;
            }

            if (max_free_size > 0x14) {
                n = (max_free_size - 0x14) / (pool_sizes[i] + 4);
            } else {
                n = 0;
            }
        }

        if ((block == 0) && (n < max_n)) {
            block = allocate_from_var_pools(pool_obj, max_n * (pool_sizes[i] + 4) + 0x14);
            if (block == 0) {
                return 0;
            }
        }

        msize = __msize_inline(block);

        if (fs->head_ == 0) {
            fs->head_ = (FixBlock*)block;
            fs->tail_ = (FixBlock*)block;
        }

        FixBlock_construct((FixBlock*)block, fs->tail_, fs->head_, i, (FixSubBlock*)((char*)block + 0x14), msize - 0x14);
        fs->head_ = (FixBlock*)block;
    }

    {
        FixSubBlock* p = fs->head_->start_;

        fs->head_->start_ = p->next_;
        ++fs->head_->n_allocated_;

        if (fs->head_->start_ == 0) {
            fs->head_ = fs->head_->next_;
            fs->tail_ = fs->tail_->next_;
        }

        return (char*)p + 4;
    }
}

static void deallocate_from_fixed_pools(__mem_pool_obj* pool_obj, void* ptr, unsigned long size) {
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

    if (size > 0xFFFFFFCFUL) {
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

void free(void* ptr) {
    __begin_critical_region(malloc_pool_access);
    __pool_free(get_malloc_pool(), ptr);
    __end_critical_region(malloc_pool_access);
}

void* __pool_alloc_clear(__mem_pool* pool, unsigned long size) {
    void* ptr = __pool_alloc(pool, size);
    if (ptr != 0) {
        memset(ptr, 0, size);
    }
    return ptr;
}

void __pool_free_all(__mem_pool* pool) {
    __mem_pool_obj* pool_obj = (__mem_pool_obj*)pool;
    Block* block;
    Block* next;

    if (pool_obj->start_ == 0) {
        return;
    }

    block = pool_obj->start_;
    do {
        next = block->next;
        __sys_free(block);
        block = next;
    } while (block != pool_obj->start_);

    memset(pool_obj, 0, sizeof(__mem_pool_obj));
}

void __pool_realloc(__mem_pool* pool, void* ptr, unsigned long size) {
    // UNUSED FUNCTION
}

void __malloc_free_all(void) {
    __begin_critical_region(malloc_pool_access);
    __pool_free_all(get_malloc_pool());
    __end_critical_region(malloc_pool_access);
    initialized = 0;
}

void* calloc(size_t count, size_t size) {
    void* ptr;
    unsigned long total = count * size;

    __begin_critical_region(malloc_pool_access);
    ptr = __pool_alloc(get_malloc_pool(), total);
    __end_critical_region(malloc_pool_access);

    if (ptr != 0) {
        memset(ptr, 0, total);
    }
    return ptr;
}

void* realloc(void* ptr, size_t size) {
    // UNUSED FUNCTION
    return 0;
}

static void SubBlock_report(SubBlock* sb) {
    // UNUSED FUNCTION
}

static void Block_report(Block* block) {
    // UNUSED FUNCTION
}

void __report_on_pool_heap(__mem_pool* pool) {
    // UNUSED FUNCTION
}

void __report_on_heap(void) {
    // UNUSED FUNCTION
}
