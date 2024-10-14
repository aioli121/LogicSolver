#pragma once

#include <exception>
#include <string>

namespace ao::logic_solver_internal {
	class exception_base_type : public std::exception {
		public:
		auto what() const noexcept -> char const * final override {
			return (
				std::string("Exception encountered: ") +
				exception_details() +
				" (ao::logic_solver_internal::" +
				exception_base() +
				"::" +
				exception_title() +
				")"
			).c_str();
		}

		virtual auto exception_base() const noexcept -> std::string = 0;
		virtual auto exception_title() const noexcept -> std::string = 0;
		virtual auto exception_details() const noexcept -> std::string = 0;
	};
}
