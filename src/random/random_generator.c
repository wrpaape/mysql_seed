#include "random/random_generator.h"


/* generators
 * ────────────────────────────────────────────────────────────────────────── */
/* UGenerators */
uintmax_t
generate_u_32(void)
{
	return (uintmax_t) random_uint32();
}

uintmax_t
generate_u_64(void)
{
	return (uintmax_t) random_uint64();
}

/* IGenerators */
intmax_t
generate_i_32(void)
{
	return (intmax_t) random_uint32();
}

intmax_t
generate_i_64(void)
{
	return (intmax_t) random_uint64();
}


/* BoundUGenerators */
uintmax_t
generate_u_bound_32(const union Bound *const restrict params)
{
	return (uintmax_t) random_uint32_bound(params->uint32.limit,
					       params->uint32.length);
}

uintmax_t
generate_u_bound_64(const union Bound *const restrict params)
{
	return (uintmax_t) random_uint64_bound(params->uint64.limit,
					       params->uint64.length);
}

intmax_t
generate_i_bound_32(const union Bound *const restrict params)
{
	return (intmax_t) random_uint32_bound(params->uint32.limit,
					      params->uint32.length);
}

intmax_t
generate_i_bound_64(const union Bound *const restrict params)
{
	return (intmax_t) random_uint64_bound(params->uint64.limit,
					      params->uint64.length);
}



/* UIntBoundOffsetGenerator */
uintmax_t
bound_uint32_offset_uint32(const struct BoundOffsetU *const restrict params)
{
	return (uintmax_t) (random_uint32_bound(params->bound.uint32.limit,
						params->bound.uint32.length)
			    + params->offset.uint32);
}

uintmax_t
bound_uint32_offset_uint64(const struct BoundOffsetU *const restrict params)
{
	return (uintmax_t) (random_uint32_bound(params->bound.uint32.limit,
						params->bound.uint32.length)
			    + params->offset.uint64);
}

uintmax_t
bound_uint64_offset_uint32(const struct BoundOffsetU *const restrict params)
{
	return (uintmax_t) (random_uint64_bound(params->bound.uint64.limit,
						params->bound.uint64.length)
			    + params->offset.uint32);
}

uintmax_t
bound_uint64_offset_uint64(const struct BoundOffsetU *const restrict params)
{
	return (uintmax_t) (random_uint64_bound(params->bound.uint64.limit,
						params->bound.uint64.length)
			    + params->offset.uint64);
}