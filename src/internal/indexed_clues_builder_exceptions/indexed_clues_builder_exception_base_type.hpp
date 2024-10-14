#pragma once

#include "internal/exception_base_type.hpp"

namespace ao::logic_solver_internal::indexed_clues_builder_exceptions {
	class indexed_clues_builder_exception_base_type : public exception_base_type {
		public:
		auto exception_base() const noexcept -> std::string final override {
			return "indexed_clues_builder_exceptions";
		}
	};
}
