#pragma once

#include "internal/solution_context_type.hpp"

namespace ao::logic_solver_internal {
	class indexed_clue_type {
		public:
		virtual void evaluate(
			solution_context_type &solution_context
		) const = 0;
	};
}
