#include "random/random_generator.h"


/* generators
 * ────────────────────────────────────────────────────────────────────────── */
/* UGenerators */
uintmax_t
generate_u_small(void)
{
	return (uintmax_t) random_uint32();
}

uintmax_t
generate_u_large(void)
{
	return (uintmax_t) random_uint64();
}

/* IGenerators */
intmax_t
generate_i_small(void)
{
	return (intmax_t) random_uint32();
}

intmax_t
generate_i_large(void)
{
	return (intmax_t) random_uint64();
}


/* BoundUGenerators */
uintmax_t
generate_u_bound_small(const union Bound *const restrict params)
{
	return (uintmax_t) random_uint32_bound(params->small.limit,
					       params->small.length);
}

uintmax_t
generate_u_bound_large(const union Bound *const restrict params)
{
	return (uintmax_t) random_uint64_bound(params->large.limit,
					       params->large.length);
}

intmax_t
generate_i_bound_small(const union Bound *const restrict params)
{
	return (intmax_t) (random_uint32_bound(params->small.limit,
					       params->small.length)
			   + INT32_MIN);
}

intmax_t
generate_i_bound_large(const union Bound *const restrict params)
{
	return (intmax_t) (random_uint64_bound(params->large.limit,
					       params->large.length)
			   + INT64_MIN);
}


/* BoundOffsetUGenerators */
uintmax_t
generate_u_bound_offset_small(const union BoundOffsetU *const restrict params)
{
	return (uintmax_t) (random_uint32_bound(params->small.limit,
						params->small.length)
			    + params->small.offset);
}


uintmax_t
generate_u_bound_offset_large(const union BoundOffsetU *const restrict params)
{
	return (uintmax_t) (random_uint64_bound(params->large.limit,
						params->large.length)
			    + params->large.offset);
}


/* BoundOffsetIGenerators */
intmax_t
generate_i_bound_offset_small(const union BoundOffsetI *const restrict params)
{
	return (intmax_t) (random_uint32_bound(params->small.limit,
					       params->small.length)
			   + params->small.offset);
}


intmax_t
generate_i_bound_offset_large(const union BoundOffsetI *const restrict params)
{
	return (intmax_t) (random_uint64_bound(params->large.limit,
					       params->large.length)
			   + params->large.offset);
}
