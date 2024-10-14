#pragma once

#include <string>

#include "internal/exception_base_type.hpp"

namespace ao::logic_solver_internal::validations {
	class validation_exception_base_type : public exception_base_type {
		public:
		auto exception_base() const noexcept -> std::string final override {
			return "validations";
		}
	};
}
