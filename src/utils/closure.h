#ifndef MYSQL_SEED_UTILS_CLOSURE_H_
#define MYSQL_SEED_UTILS_CLOSURE_H_

/* External Dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "utils/types/routine.h"
#include "utils/types/procedure.h"
#include "utils/types/handler.h"


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */

struct RoutineClosure {
	Routine *fun;
	void *arg;
};

struct ProcedureClosure {
	Procedure *fun;
	void *arg;
};

struct HandlerClosure {
	Handler *handle;
	void *arg;
};


/* RoutineClosure operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
routine_closure_init(struct RoutineClosure *const restrict routine_cl,
		     Routine *const fun,
		     void *arg)
{
	routine_cl->fun = fun;
	routine_cl->arg = arg;
}

inline void *
routine_closure_call(const struct RoutineClosure *const restrict routine_cl)
{
	return routine_cl->fun(routine_cl->arg);
}


/* ProcedureClosure operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
procedure_closure_init(struct ProcedureClosure *const restrict procedure_cl,
		       Procedure *const fun,
		       void *arg)
{
	procedure_cl->fun = fun;
	procedure_cl->arg = arg;
}

inline void
procedure_closure_call(const struct ProcedureClosure *const restrict procedure_cl)
{
	procedure_cl->fun(procedure_cl->arg);
}

/* HandlerClosure operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
handler_closure_init(struct HandlerClosure *const restrict handler_cl,
		     Handler *const handle,
		     void *arg)
{
	handler_cl->handle = handle;
	handler_cl->arg	   = arg;
}

inline void
handler_closure_call(const struct HandlerClosure *const restrict handler_cl,
		     const char *const restrict failure)
{
	handler_cl->handle(handler_cl->arg,
			   failure);
	__builtin_unreachable();
}

#endif /* ifndef MYSQL_SEED_UTILS_CLOSURE_H_ */
