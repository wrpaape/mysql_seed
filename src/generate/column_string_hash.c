#include "generate/column_string_hash.h"

void
build_column_string_hash(void *arg);

/* hash_t hash_bytes(byte_t *bytes, */
/* 		  const size_t length, */
/* 		  const hash_t m_prime) */
/* { */

/* 	/1* size_t rem_words = length / sizeof(hash_t); *1/ */
/* 	size_t rem_bytes = length % sizeof(hash_t); */

/* 	ptrdiff_t i = length - rem_bytes; */

/* 	hash_t *word = (hash_t *) bytes; */

/* 	hash_t hash = (word[i] << (sizeof(hash_t) - rem_bytes)) & m_prime; */

/* 	i -= rem_bytes; */

/* 	if (i < 0l) */
/* 		return hash; */

/* 	const hash_t base_mod_size = HASH_MAX & m_prime; */

/* 	do { */
/* 		hash += (base_mod_size * (word[i] & m_prime)) & m_prime; */
/* 		i -= sizeof(hash_t); */

/* 	} while (i >= 0l); */

/* 	return hash; */
/* } */
