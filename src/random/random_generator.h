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
	struct Bound32 small;
	struct Bound64 large;
};

struct BoundOffsetU32 {
	uint32_t limit;
	uint32_t length;
	uint32_t offset;
};

struct BoundOffsetU64 {
	uint64_t limit;
	uint64_t length;
	uint64_t offset;
};

union BoundOffsetU {
	struct BoundOffsetU32 small;
	struct BoundOffsetU64 large;
};

struct BoundOffsetI32 {
	uint32_t limit;
	uint32_t length;
	int32_t offset;
};

struct BoundOffsetI64 {
	uint64_t limit;
	uint64_t length;
	int64_t offset;
};

union BoundOffsetI {
	struct BoundOffsetI32 small;
	struct BoundOffsetI64 large;
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
BoundOffsetUGenerator(const union BoundOffsetU *const restrict params);
struct BoundOffsetUGeneratorClosure {
	union BoundOffsetU params;
	BoundOffsetUGenerator *generate;
};


/* from ... INT32|64_MAX, min ... max */
typedef intmax_t
BoundOffsetIGenerator(const union BoundOffsetI *const restrict params);
struct BoundOffsetIGeneratorClosure {
	union BoundOffsetI params;
	BoundOffsetIGenerator *generate;
};


/* generators
 * ────────────────────────────────────────────────────────────────────────── */
/* UGenerators */
uintmax_t
generate_u_small(void);
uintmax_t
generate_u_large(void);
/* IGenerators */
intmax_t
generate_i_small(void);
intmax_t
generate_i_large(void);

/* BoundUGenerators */
uintmax_t
generate_u_bound_small(const union Bound *const restrict params);
uintmax_t
generate_u_bound_large(const union Bound *const restrict params);
/* BoundIGenerators */
intmax_t
generate_i_bound_small(const union Bound *const restrict params);
intmax_t
generate_i_bound_large(const union Bound *const restrict params);

/* BoundOffsetUGenerators */
uintmax_t
generate_u_bound_offset_small(const union BoundOffsetU *const restrict params);
uintmax_t
generate_u_bound_offset_large(const union BoundOffsetU *const restrict params);

/* BoundOffsetIGenerators */
intmax_t
generate_i_bound_offset_small(const union BoundOffsetI *const restrict params);
intmax_t
generate_i_bound_offset_large(const union BoundOffsetI *const restrict params);
#endif /* ifndef MYSQL_SEED_RANDOM_RANDOM_GENERATOR_H_ */
