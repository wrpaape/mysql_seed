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


/* 0 ... U|INT32|64_MAX */
typedef uintmax_t
UGenerator(void);
typedef intmax_t
IGenerator(void);

/* 0 ... upto */
typedef uintmax_t
BoundUGenerator(const union Bound *const restrict params);
typedef intmax_t
BoundIGenerator(const union Bound *const restrict params);

struct BoundUGeneratorClosure {
	union Bound params;
	BoundUGenerator *generate;
};

struct BoundIGeneratorClosure {
	union Bound params;
	BoundIGenerator *generate;
};

/* from ... U|INT32|64_MAX, min ... max */
typedef uintmax_t
UIntBoundOffsetGenerator(const struct BoundOffsetU *const restrict params);

struct UIntBoundOffsetClosure {
	struct BoundOffsetU params;
	UIntBoundOffsetGenerator *generate;
};


/* signed integers */
union IntOffset {
	int32_t int32;
	int64_t int64;
};

struct IntBoundOffset {
	union Bound bound;
	union IntOffset offset;
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

/* UIntBoundOffsetGenerator */
uintmax_t
uint_bound_uint32_offset_uint32(const struct BoundOffsetU *const restrict params);
uintmax_t
uint_bound_uint32_offset_uint64(const struct BoundOffsetU *const restrict params);
uintmax_t
uint_bound_uint64_offset_uint32(const struct BoundOffsetU *const restrict params);
uintmax_t
uint_bound_uint64_offset_uint64(const struct BoundOffsetU *const restrict params);


