/**
 * @file
 *
 * Header file for icl_hash routines.
 *
 */
/* $Id$ */
/* $UTK_Copyright: $ */

#ifndef icl_hash_h
#define icl_hash_h

#define _POSIX_C_SOURCE 200809L
#include <pthread.h>
#include <stdio.h>

#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

typedef struct icl_entry_s {
  void* key;
  void* data;
  struct icl_entry_s* next;
} icl_entry_t;

typedef struct icl_hash_s {
  size_t nbuckets;
  size_t nentries;
  pthread_rwlock_t* listrwlockes;
  pthread_mutex_t fieldMutex;
  icl_entry_t** buckets;
  unsigned int (*hash_function)(void*);
  int (*hash_key_compare)(void*, void*);
} icl_hash_t;

icl_hash_t* icl_hash_create(size_t nbucketsHint,
                            unsigned int (*hash_function)(void*),
                            int (*hash_key_compare)(void*, void*));

void* icl_hash_find(icl_hash_t*, void*);

int icl_hash_update(icl_hash_t*, void*, void*);

icl_entry_t* icl_hash_insert(icl_hash_t*, void*, void*);

int icl_hash_destroy(icl_hash_t*, void (*)(void*), void (*)(void*)),
    icl_hash_dump(FILE*, icl_hash_t*);

int icl_hash_delete(icl_hash_t* ht,
                    void* key,
                    void (*free_key)(void*),
                    void (*free_data)(void*));

#define icl_hash_foreach(ht, tmpint, tmpent, kp, dp)       \
  for (tmpint = 0; tmpint < ht->nbuckets; tmpint++)        \
    for (tmpent = ht->buckets[tmpint];                     \
         tmpent != NULL && ((kp = tmpent->key) != NULL) && \
         ((dp = tmpent->data) != NULL);                    \
         tmpent = tmpent->next)

#if defined(c_plusplus) || defined(__cplusplus)
}
#endif

#endif /* icl_hash_h */
