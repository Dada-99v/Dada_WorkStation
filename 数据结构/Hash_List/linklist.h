/**
 * Copyright(C) 2020-2022 T.WKVER | </MATRIX>. All rights reserved.
 */
/**
 * linklist.h
 * Original Author: linux fundation, 2002
 *
 * link list library
 * copy from linux kernel 2.6.32
 */

#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include <stddef.h> /* for offsetof */
#include <stdint.h>

#define prefetch(x)             __builtin_prefetch(x)
#define POISON_POINTER_DELTA    0

/**
 * These are non-NULL pointers that will result in page faults
 * under normal circumstances, used to verify that nobody uses
 * non-initialized list entries.
 */
#define LIST_POISON1 ((void *)(0x00100100 + POISON_POINTER_DELTA))
#define LIST_POISON2 ((void *)(0x00200200 + POISON_POINTER_DELTA))

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:    the pointer to the member.
 * @type:   the type of the container struct this is embedded in.
 * @member: the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member)                                        \
    ({                                                                         \
        const typeof(((type *)0)->member) *__mptr = (ptr);                     \
        (type *)((char *)__mptr - offsetof(type, member));                     \
    })

/**
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
struct list_head {
    struct list_head *next, *prev;
};

typedef struct {
    struct list_head    origin;     /* double direction circle link list origin */
    uint32_t            length;
} linklist_class_t;

static inline uint32_t linklist_length (linklist_class_t *link) {
    return link->length;
} /* linklist_length */

#define LIST_HEAD_INIT(name)                                                   \
    { &(name), &(name) }

//#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list) {
    list->next = list;
    list->prev = list;
}

static inline bool linklist_is_invalid (linklist_class_t *link) {
    return (!link->origin.next || !link->origin.prev);
} /* linklist_is_invalid */

static inline void linklist_init (linklist_class_t *link) {
    INIT_LIST_HEAD(&link->origin);
    link->length = 0;
} /* linklist_init */

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head) {
    return head->next == head;
}

/**
 * list_empty_careful - tests whether a list is empty and not being modified
 * @head: the list to test
 *
 * Description:
 * tests whether a list is empty _and_ checks that no other CPU might be
 * in the process of modifying either member (next or prev)
 *
 * NOTE: using list_empty_careful() without synchronization
 * can only be safe if the only activity that can happen
 * to the list entry is list_del_init(). Eg. it cannot be used
 * if another CPU could re-list_add() it.
 */
static inline int list_empty_careful(const struct list_head *head) {
    struct list_head *next = head->next;
    return (next == head) && (next == head->prev);
}

/**
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
#ifndef CONFIG_DEBUG_LIST
static inline void __list_add(struct list_head *new, struct list_head *prev,
                              struct list_head *next) {
    next->prev = new;
    new->next  = next;
    new->prev  = prev;
    prev->next = new;
}
#else
extern void __list_add(struct list_head *new, struct list_head *prev,
                       struct list_head *next);
#endif

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void list_add(struct list_head *new, struct list_head *head) {
    if (!list_empty(new)) {
        return;
    }
    __list_add(new, head, head->next);
}

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(struct list_head *new,
                                 struct list_head *head) {
    if (!list_empty(new)) {
        return;
    }
    __list_add(new, head->prev, head);
}

/* haed->1->2->3->... */
static inline void linklist_append (struct list_head *node, linklist_class_t *link) {
    if (!list_empty(node)) {
        return;
    }
    list_add_tail(node, &link->origin);
    ++link->length;
} /* linklist_append */

/* head->...->3->2->1 */
static inline void linklist_append_reverse (struct list_head *node, linklist_class_t *link) {
    if (!list_empty(node)) {
        return;
    }
    list_add(node, &link->origin);
    ++link->length;
} /* linklist_append_reverse */

/**
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head *prev, struct list_head *next) {
    next->prev = prev;
    prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
#ifndef CONFIG_DEBUG_LIST
static inline void list_del(struct list_head *entry) {
    __list_del(entry->prev, entry->next);
    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}
#else
extern void list_del(struct list_head *entry);
#endif

/**
 * list_replace - replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
static inline void list_replace(struct list_head *old, struct list_head *new) {
    new->next       = old->next;
    new->next->prev = new;
    new->prev       = old->prev;
    new->prev->next = new;
}

static inline void list_replace_init(struct list_head *old, struct list_head *new) {
    list_replace(old, new);
    INIT_LIST_HEAD(old);
}

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
static inline void list_del_init(struct list_head *entry) {
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}

static inline void linklist_remove (struct list_head *node, linklist_class_t *link) {
    list_del_init(node);
    --link->length;
} /* linklist_remove */

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
static inline void list_move(struct list_head *list, struct list_head *head) {
    __list_del(list->prev, list->next);
    list_add(list, head);
}

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static inline void list_move_tail(struct list_head *list,
                                  struct list_head *head) {
    __list_del(list->prev, list->next);
    list_add_tail(list, head);
}

/**
 * list_is_first - tests whether @list is the first entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int list_is_first(const struct list_head *list,
                               const struct list_head *head) {
    return list->prev == head;
}

/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int list_is_last(const struct list_head *list,
                               const struct list_head *head) {
    return list->next == head;
}

/**
 * list_is_singular - tests whether a list has just one entry.
 * @head: the list to test.
 */
static inline int list_is_singular(const struct list_head *head) {
    return !list_empty(head) && (head->next == head->prev);
}

static inline void __list_cut_position(struct list_head *list,
                                       struct list_head *head,
                                       struct list_head *entry) {
    struct list_head *new_first = entry->next;
    list->next                  = head->next;
    list->next->prev            = list;
    list->prev                  = entry;
    entry->next                 = list;
    head->next                  = new_first;
    new_first->prev             = head;
}

/**
 * list_cut_position - cut a list into two
 * @list: a new list to add all removed entries
 * @head: a list with entries
 * @entry: an entry within head, could be the head itself
 *  and if so we won't cut the list
 *
 * This helper moves the initial part of @head, up to and
 * including @entry, from @head to @list. You should
 * pass on @entry an element you know is on @head. @list
 * should be an empty list or a list you do not care about
 * losing its data.
 *
 */
static inline void list_cut_position(struct list_head *list,
                                     struct list_head *head,
                                     struct list_head *entry) {
    if (list_empty(head))
        return;
    if (list_is_singular(head) && (head->next != entry && head != entry))
        return;
    if (entry == head)
        INIT_LIST_HEAD(list);
    else
        __list_cut_position(list, head, entry);
}

static inline void __list_splice(const struct list_head *list,
                                 struct list_head *      prev,
                                 struct list_head *      next) {
    struct list_head *first = list->next;
    struct list_head *last  = list->prev;

    first->prev = prev;
    prev->next  = first;

    last->next = next;
    next->prev = last;
}

/**
 * list_splice - join two lists, this is designed for stacks
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static inline void list_splice(const struct list_head *list,
                               struct list_head *      head) {
    if (!list_empty(list))
        __list_splice(list, head, head->next);
}

/**
 * list_splice_tail - join two lists, each list being a queue
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static inline void list_splice_tail(struct list_head *list,
                                    struct list_head *head) {
    if (!list_empty(list))
        __list_splice(list, head->prev, head);
}

/**
 * list_splice_init - join two lists and reinitialise the emptied list.
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * The list at @list is reinitialised
 */
static inline void list_splice_init(struct list_head *list,
                                    struct list_head *head) {
    if (!list_empty(list)) {
        __list_splice(list, head, head->next);
        INIT_LIST_HEAD(list);
    }
}

/**
 * list_splice_tail_init - join two lists and reinitialise the emptied list
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * Each of the lists is a queue.
 * The list at @list is reinitialised
 */
static inline void list_splice_tail_init(struct list_head *list,
                                         struct list_head *head) {
    if (!list_empty(list)) {
        __list_splice(list, head->prev, head);
        INIT_LIST_HEAD(list);
    }
}

/**
 * list_entry - get the struct for this entry
 * @ptr:    the &struct list_head pointer.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @ptr:    the list head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member)                                    \
    list_entry((ptr)->next, type, member)

/**
 * list_next_entry - get the next element from a list
 * @cur_entry:  the current entry.
 * @head:       the head of list.
 *
 * Note, that list is expected to be not empty.
 */
static inline struct list_head *list_next_entry (struct list_head *cur_entry, struct list_head *head) {
    if (list_is_last(cur_entry, head)) {
        return head->next;
    }

    return cur_entry->next;
} /* list_next_entry */

/**
 * list_prev_entry - get the previous element from a list
 * @cur_entry:  the current entry.
 * @head:       the head of list.
 *
 * Note, that list is expected to be not empty.
 */
static inline struct list_head *list_prev_entry (struct list_head *cur_entry, struct list_head *head) {
    if (list_is_first(cur_entry, head)) {
        return head->prev;
    }

    return cur_entry->prev;
} /* list_prev_entry */

/**
 * list_for_each    -   iterate over a list
 * @pos:    the &struct list_head to use as a loop cursor.
 * @head:   the head for your list.
 */
#define list_for_each(pos, head)                                               \
    for (pos = (head)->next; prefetch(pos->next), pos != (head);               \
         pos = pos->next)

/**
 * list_for_each_reverse    -   iterate over a list reverse
 * @pos:    the &struct list_head to use as a loop cursor.
 * @head:   the head for your list.
 */
#define list_for_each_reverse(pos, head)                                        \
    for (pos = (head)->prev; prefetch(pos->prev), pos != (head);                \
        pos = pos->prev)

/**
 * __list_for_each  -   iterate over a list
 * @pos:    the &struct list_head to use as a loop cursor.
 * @head:   the head for your list.
 *
 * This variant differs from list_for_each() in that it's the
 * simplest possible list iteration code, no prefetching is done.
 * Use this for code that knows the list to be very short (empty
 * or 1 entry) most of the time.
 */
#define __list_for_each(pos, head)                                             \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * list_for_each_prev   -   iterate over a list backwards
 * @pos:    the &struct list_head to use as a loop cursor.
 * @head:   the head for your list.
 */
#define list_for_each_prev(pos, head)                                          \
    for (pos = (head)->prev; prefetch(pos->prev), pos != (head);               \
         pos = pos->prev)

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:    the &struct list_head to use as a loop cursor.
 * @n:      another &struct list_head to use as temporary storage
 * @head:   the head for your list.
 */
#define list_for_each_safe(pos, n, head)                                       \
    for (pos = (head)->next, n = pos->next; pos != (head);                     \
         pos = n, n = pos->next)

/**
 * list_for_each_prev_safe - iterate over a list backwards safe against removal
 * of list entry
 * @pos:    the &struct list_head to use as a loop cursor.
 * @n:      another &struct list_head to use as temporary storage
 * @head:   the head for your list.
 */
#define list_for_each_prev_safe(pos, n, head)                                  \
    for (pos = (head)->prev, n                   = pos->prev;                  \
         prefetch(pos->prev), pos != (head); pos = n, n = pos->prev)

/**
 * list_for_each_entry  -   iterate over list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, member)                                 \
    for (pos = list_entry((head)->next, typeof(*pos), member);                 \
         prefetch(pos->member.next), &pos->member != (head);                   \
         pos = list_entry(pos->member.next, typeof(*pos), member))

/**
 * list_for_each_entry_reverse - iterate backwards over list of given type.
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define list_for_each_entry_reverse(pos, head, member)                         \
    for (pos = list_entry((head)->prev, typeof(*pos), member);                 \
         prefetch(pos->member.prev), &pos->member != (head);                   \
         pos = list_entry(pos->member.prev, typeof(*pos), member))

/**
 * list_prepare_entry - prepare a pos entry for use in
 * list_for_each_entry_continue()
 * @pos:    the type * to use as a start point
 * @head:   the head of the list
 * @member: the name of the list_struct within the struct.
 *
 * Prepares a pos entry for use as a start point in
 * list_for_each_entry_continue().
 */
#define list_prepare_entry(pos, head, member)                                  \
    ((pos) ?: list_entry(head, typeof(*pos), member))

/**
 * list_for_each_entry_continue - continue iteration over list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 *
 * Continue to iterate over list of given type, continuing after
 * the current position.
 */
#define list_for_each_entry_continue(pos, head, member)                        \
    for (pos = list_entry(pos->member.next, typeof(*pos), member);             \
         prefetch(pos->member.next), &pos->member != (head);                   \
         pos = list_entry(pos->member.next, typeof(*pos), member))

/**
 * list_for_each_entry_continue_reverse - iterate backwards from the given point
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 *
 * Start to iterate over list of given type backwards, continuing after
 * the current position.
 */
#define list_for_each_entry_continue_reverse(pos, head, member)                \
    for (pos = list_entry(pos->member.prev, typeof(*pos), member);             \
         prefetch(pos->member.prev), &pos->member != (head);                   \
         pos = list_entry(pos->member.prev, typeof(*pos), member))

/**
 * list_for_each_entry_from - iterate over list of given type from the current
 * point
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 *
 * Iterate over list of given type, continuing from current position.
 */
#define list_for_each_entry_from(pos, head, member)                            \
    for (; prefetch(pos->member.next), &pos->member != (head);                 \
         pos = list_entry(pos->member.next, typeof(*pos), member))

/**
 * list_for_each_entry_safe - iterate over list of given type safe against
 * removal of list entry
 * @pos:    the type * to use as a loop cursor.
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)                         \
    for (pos = list_entry((head)->next, typeof(*pos), member),                 \
        n    = list_entry(pos->member.next, typeof(*pos), member);             \
         &pos->member != (head);                                               \
         pos = n, n = list_entry(n->member.next, typeof(*n), member))

/**
 * list_for_each_entry_safe_continue
 * @pos:    the type * to use as a loop cursor.
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 *
 * Iterate over list of given type, continuing after current point,
 * safe against removal of list entry.
 */
#define list_for_each_entry_safe_continue(pos, n, head, member)                \
    for (pos = list_entry(pos->member.next, typeof(*pos), member),             \
        n    = list_entry(pos->member.next, typeof(*pos), member);             \
         &pos->member != (head);                                               \
         pos = n, n = list_entry(n->member.next, typeof(*n), member))

/**
 * list_for_each_entry_safe_from
 * @pos:    the type * to use as a loop cursor.
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 *
 * Iterate over list of given type from current point, safe against
 * removal of list entry.
 */
#define list_for_each_entry_safe_from(pos, n, head, member)                    \
    for (n = list_entry(pos->member.next, typeof(*pos), member);               \
         &pos->member != (head);                                               \
         pos = n, n = list_entry(n->member.next, typeof(*n), member))

/**
 * list_for_each_entry_safe_reverse
 * @pos:    the type * to use as a loop cursor.
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 *
 * Iterate backwards over list of given type, safe against removal
 * of list entry.
 */
#define list_for_each_entry_safe_reverse(pos, n, head, member)                 \
    for (pos = list_entry((head)->prev, typeof(*pos), member),                 \
        n    = list_entry(pos->member.prev, typeof(*pos), member);             \
         &pos->member != (head);                                               \
         pos = n, n = list_entry(n->member.prev, typeof(*n), member))

/**
 * Double linked lists with a single pointer list head.
 * Mostly useful for hash tables where the two pointer list head is
 * too wasteful.
 * You lose the ability to access the tail in O(1).
 */

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};

#define HLIST_HEAD_INIT                                                        \
    { .first = NULL }
#define HLIST_HEAD(name) struct hlist_head name = {.first = NULL}
#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)
static inline void INIT_HLIST_NODE(struct hlist_node *h) {
    h->next  = NULL;
    h->pprev = NULL;
}

static inline int hlist_unhashed(const struct hlist_node *h) {
    return !h->pprev;
}

static inline int hlist_empty(const struct hlist_head *h) {
    return !h->first;
}

static inline void __hlist_del(struct hlist_node *n) {
    struct hlist_node * next  = n->next;
    struct hlist_node **pprev = n->pprev;
    *pprev                    = next;
    if (next)
        next->pprev = pprev;
}

static inline void hlist_del(struct hlist_node *n) {
    __hlist_del(n);
    n->next  = LIST_POISON1;
    n->pprev = LIST_POISON2;
}

static inline void hlist_del_init(struct hlist_node *n) {
    if (!hlist_unhashed(n)) {
        __hlist_del(n);
        INIT_HLIST_NODE(n);
    }
}

static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h) {
    struct hlist_node *first = h->first;
    n->next                  = first;
    if (first)
        first->pprev = &n->next;
    h->first = n;
    n->pprev = &h->first;
}

/* next must be != NULL */
static inline void hlist_add_before(struct hlist_node *n,
                                    struct hlist_node *next) {
    n->pprev    = next->pprev;
    n->next     = next;
    next->pprev = &n->next;
    *(n->pprev) = n;
}

static inline void hlist_add_after(struct hlist_node *n,
                                   struct hlist_node *next) {
    next->next  = n->next;
    n->next     = next;
    next->pprev = &n->next;

    if (next->next)
        next->next->pprev = &next->next;
}

/**
 * Move a list from one list head to another. Fixup the pprev
 * reference of the first entry if it exists.
 */
static inline void hlist_move_list(struct hlist_head *old,
                                   struct hlist_head *new) {
    new->first = old->first;
    if (new->first)
        new->first->pprev = &new->first;
    old->first = NULL;
}

#define hlist_entry(ptr, type, member) container_of(ptr, type, member)

#define hlist_for_each(pos, head)                                              \
    for (pos = (head)->first; pos && ({                                        \
                                  prefetch(pos->next);                         \
                                  1;                                           \
                              });                                              \
         pos = pos->next)

#define hlist_for_each_safe(pos, n, head)                                      \
    for (pos = (head)->first; pos && ({                                        \
                                  n = pos->next;                               \
                                  1;                                           \
                              });                                              \
         pos = n)

/**
 * hlist_for_each_entry - iterate over list of given type
 * @tpos:   the type * to use as a loop cursor.
 * @pos:    the &struct hlist_node to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry(tpos, pos, head, member)                          \
    for (pos = (head)->first; pos && ({                                        \
                                  prefetch(pos->next);                         \
                                  1;                                           \
                              }) &&                                            \
                              ({                                               \
                                  tpos =                                       \
                                      hlist_entry(pos, typeof(*tpos), member); \
                                  1;                                           \
                              });                                              \
         pos = pos->next)

/**
 * hlist_for_each_entry_continue - iterate over a hlist continuing after current
 * point
 * @tpos:   the type * to use as a loop cursor.
 * @pos:    the &struct hlist_node to use as a loop cursor.
 * @member: the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry_continue(tpos, pos, member)                       \
    for (pos = (pos)->next; pos && ({                                          \
                                prefetch(pos->next);                           \
                                1;                                             \
                            }) &&                                              \
                            ({                                                 \
                                tpos =                                         \
                                    hlist_entry(pos, typeof(*tpos), member);   \
                                1;                                             \
                            });                                                \
         pos = pos->next)

/**
 * hlist_for_each_entry_from - iterate over a hlist continuing from current
 * point
 * @tpos:   the type * to use as a loop cursor.
 * @pos:    the &struct hlist_node to use as a loop cursor.
 * @member: the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry_from(tpos, pos, member)                           \
    for (; pos && ({                                                           \
               prefetch(pos->next);                                            \
               1;                                                              \
           }) &&                                                               \
           ({                                                                  \
               tpos = hlist_entry(pos, typeof(*tpos), member);                 \
               1;                                                              \
           });                                                                 \
         pos = pos->next)

/**
 * hlist_for_each_entry_safe - iterate over list of given type safe against
 * removal of list entry
 * @tpos:   the type * to use as a loop cursor.
 * @pos:    the &struct hlist_node to use as a loop cursor.
 * @n:      another &struct hlist_node to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the hlist_node within the struct.
 */
#define hlist_for_each_entry_safe(tpos, pos, n, head, member)                  \
    for (pos = (head)->first; pos && ({                                        \
                                  n = pos->next;                               \
                                  1;                                           \
                              }) &&                                            \
                              ({                                               \
                                  tpos =                                       \
                                      hlist_entry(pos, typeof(*tpos), member); \
                                  1;                                           \
                              });                                              \
         pos = n)

/**
 * This is a priority-sorted list of nodes; each node has a
 * priority from INT_MIN (highest) to INT_MAX (lowest).
 *
 * Addition is O(K), removal is O(1), change of priority of a node is
 * O(K) and K is the number of RT priority levels used in the system.
 * (1 <= K <= 99)
 *
 * This list is really a list of lists:
 *
 *  - The tier 1 list is the prio_list, different priority nodes.
 *
 *  - The tier 2 list is the node_list, serialized nodes.
 *
 * Simple ASCII art explanation:
 *
 * |HEAD          |
 * |              |
 * |prio_list.prev|<------------------------------------|
 * |prio_list.next|<->|pl|<->|pl|<--------------->|pl|<-|
 * |10            |   |10|   |21|   |21|   |21|   |40|   (prio)
 * |              |   |  |   |  |   |  |   |  |   |  |
 * |              |   |  |   |  |   |  |   |  |   |  |
 * |node_list.next|<->|nl|<->|nl|<->|nl|<->|nl|<->|nl|<-|
 * |node_list.prev|<------------------------------------|
 *
 * The nodes on the prio_list list are sorted by priority to simplify
 * the insertion of new nodes. There are no nodes with duplicate
 * priorites on the list.
 *
 * The nodes on the node_list is ordered by priority and can contain
 * entries which have the same priority. Those entries are ordered
 * FIFO
 *
 * Addition means: look for the prio_list node in the prio_list
 * for the priority of the node and insert it before the node_list
 * entry of the next prio_list node. If it is the first node of
 * that priority, add it to the prio_list in the right position and
 * insert it into the serialized node_list list
 *
 * Removal means remove it from the node_list and remove it from
 * the prio_list if the node_list list_head is non empty. In case
 * of removal from the prio_list it must be checked whether other
 * entries of the same priority are on the list or not. If there
 * is another entry of the same priority then this entry has to
 * replace the removed entry on the prio_list. If the entry which
 * is removed is the only entry of this priority then a simple
 * remove from both list is sufficient.
 *
 * INT_MIN is the highest priority, 0 is the medium highest, INT_MAX
 * is lowest priority.
 */

struct plist_head {
    struct list_head prio_list;
    struct list_head node_list;
};

struct plist_node {
    int               prio;
    struct plist_head plist;
};

#define _PLIST_HEAD_INIT(head)                                                 \
    .prio_list = LIST_HEAD_INIT((head).prio_list),                             \
    .node_list = LIST_HEAD_INIT((head).node_list)

/**
 * PLIST_HEAD_INIT - static struct plist_head initializer
 * @head:   struct plist_head variable name
 * @_lock:  lock to initialize for this list
 */
#define PLIST_HEAD_INIT(head, _lock)                                           \
    { PLIST_HEAD_INIT(head), PLIST_HEAD_LOCK_INIT(&(_lock)) }

/**
 * PLIST_NODE_INIT - static struct plist_node initializer
 * @node:   struct plist_node variable name
 * @__prio: initial node priority
 */
#define PLIST_NODE_INIT(node, __prio)                                          \
    { .prio = (__prio), .plist = {_PLIST_HEAD_INIT((node).plist)}, }

/**
 * plist_head_init - dynamic struct plist_head initializer
 * @head:   &struct plist_head pointer
 */
static inline void plist_head_init(struct plist_head *head) {
    INIT_LIST_HEAD(&head->prio_list);
    INIT_LIST_HEAD(&head->node_list);
}

/**
 * plist_node_init - Dynamic struct plist_node initializer
 * @node:   &struct plist_node pointer
 * @prio:   initial node priority
 */
static inline void plist_node_init(struct plist_node *node, int prio) {
    node->prio = prio;
    plist_head_init(&node->plist);
}

extern void plist_add(struct plist_node *node, struct plist_head *head);
extern void plist_del(struct plist_node *node, struct plist_head *head);

/**
 * plist_for_each - iterate over the plist
 * @pos:    the type * to use as a loop counter
 * @head:   the head for your list
 */
#define plist_for_each(pos, head)                                              \
    list_for_each_entry(pos, &(head)->node_list, plist.node_list)

/**
 * plist_for_each_safe - iterate safely over a plist of given type
 * @pos:    the type * to use as a loop counter
 * @n:  another type * to use as temporary storage
 * @head:   the head for your list
 *
 * Iterate over a plist of given type, safe against removal of list entry.
 */
#define plist_for_each_safe(pos, n, head)                                      \
    list_for_each_entry_safe(pos, n, &(head)->node_list, plist.node_list)

/**
 * plist_for_each_entry - iterate over list of given type
 * @pos:    the type * to use as a loop counter
 * @head:   the head for your list
 * @mem:    the name of the list_struct within the struct
 */
#define plist_for_each_entry(pos, head, mem)                                   \
    list_for_each_entry(pos, &(head)->node_list, mem.plist.node_list)

/**
 * plist_for_each_entry_safe - iterate safely over list of given type
 * @pos:    the type * to use as a loop counter
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list
 * @m:      the name of the list_struct within the struct
 *
 * Iterate over list of given type, safe against removal of list entry.
 */
#define plist_for_each_entry_safe(pos, n, head, m)                             \
    list_for_each_entry_safe(pos, n, &(head)->node_list, m.plist.node_list)

/**
 * plist_head_empty - return !0 if a plist_head is empty
 * @head:   &struct plist_head pointer
 */
static inline int plist_head_empty(const struct plist_head *head) {
    return list_empty(&head->node_list);
}

/**
 * plist_node_empty - return !0 if plist_node is not on a list
 * @node:   &struct plist_node pointer
 */
static inline int plist_node_empty(const struct plist_node *node) {
    return plist_head_empty(&node->plist);
}

/* All functions below assume the plist_head is not empty. */

/**
 * plist_first_entry - get the struct for the first entry
 * @head:   the &struct plist_head pointer
 * @type:   the type of the struct this is embedded in
 * @member: the name of the list_struct within the struct
 */
#define plist_first_entry(head, type, member)                                  \
    container_of(plist_first(head), type, member)

/**
 * plist_first - return the first node (and thus, highest priority)
 * @head:   the &struct plist_head pointer
 *
 * Assumes the plist is _not_ empty.
 */
static inline struct plist_node *plist_first(const struct plist_head *head) {
    return list_entry(head->node_list.next, struct plist_node, plist.node_list);
}

#endif /* _LINKLIST_H_ */
