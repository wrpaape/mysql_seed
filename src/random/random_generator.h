#ifndef MYSQL_SEED_RANDOM_RANDOM_GENERATOR_H_
#define MYSQL_SEED_RANDOM_RANDOM_GENERATOR_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "random/random.h"	/* random number generator */


/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
/* unsigned integers */
struct Bound32 {
	uint32_t limit;
	uint32_t length;
};

struct Bound64 {
	uint64_t limit;
	uint64_t length;
};

union Bound {
	struct Bound32 uint32;
	struct Bound64 uint64;
};

union OffsetU {
	uint32_t uint32;
	uint64_t uint64;
};

union OffsetI {
	int32_t int32;
	int64_t int64;
};

struct BoundOffsetU {
	union Bound bound;
	union OffsetU offset;
};

struct BoundOffsetI {
	union Bound bound;
	union OffsetI offset;
};


/* 0 ... UINT32|64_MAX */
typedef uintmax_t
UGenerator(void);
/* INT32|64_MIN ... INT32|64_MAX */
typedef intmax_t
IGenerator(void);

/* 0 ... upto */
typedef uintmax_t
BoundUGenerator(const union Bound *const restrict params);
struct BoundUGeneratorClosure {
	union Bound params;
	BoundUGenerator *generate;
};

/* INT32|64_MIN ... upto */
typedef intmax_t
BoundIGenerator(const union Bound *const restrict params);
struct BoundIGeneratorClosure {
	union Bound params;
	BoundIGenerator *generate;
};

/* from ... UINT32|64_MAX, min ... max */
typedef uintmax_t
BoundOffsetUGenerator(const struct BoundOffsetU *const restrict params);
struct BoundOffsetUGeneratorClosure {
	struct BoundOffsetU params;
	BoundOffsetUGenerator *generate;
};


/* from ... INT32|64_MAX, min ... max */
typedef intmax_t
BoundOffsetIGenerator(const struct BoundOffsetI *const restrict params);
struct BoundOffsetIGeneratorClosure {
	struct BoundOffsetI params;
	BoundOffsetIGenerator *generate;
};


/* generators
 * ────────────────────────────────────────────────────────────────────────── */
/* UGenerators */
uintmax_t
generate_u_32(void);
uintmax_t
generate_u_64(void);
/* IGenerators */
intmax_t
generate_i_32(void);
intmax_t
generate_i_64(void);

/* BoundUGenerators */
uintmax_t
generate_u_bound_32(const union Bound *const restrict params);
uintmax_t
generate_u_bound_64(const union Bound *const restrict params);
/* BoundIGenerators */
intmax_t
generate_i_bound_32(const union Bound *const restrict params);
intmax_t
generate_i_bound_64(const union Bound *const restrict params);

/* BoundOffsetUGenerators */
uintmax_t
generate_u_bound_32_offset_32(const struct BoundOffsetU *const restrict params);
uintmax_t
generate_u_bound_32_offset_64(const struct BoundOffsetU *const restrict params);
uintmax_t
generate_u_bound_64_offset_32(const struct BoundOffsetU *const restrict params);
uintmax_t
generate_u_bound_64_offset_64(const struct BoundOffsetU *const restrict params);

/* BoundOffsetIGenerators */
intmax_t
generate_i_bound_32_offset_32(const struct BoundOffsetI *const restrict params);
intmax_t
generate_i_bound_32_offset_64(const struct BoundOffsetI *const restrict params);
intmax_t
generate_i_bound_64_offset_32(const struct BoundOffsetI *const restrict params);
intmax_t
generate_i_bound_64_offset_64(const struct BoundOffsetI *const restrict params);
