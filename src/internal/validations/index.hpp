#pragma once

#include <string>

#include "internal/validations/validation_exception_base_type.hpp"

namespace ao::logic_solver_internal::validations::index {
	class negative_exception_type : public validation_exception_base_type {
		public:
		negative_exception_type(
			std::string const &index_type_title,
			int const validated_count,
			int const index
		) : index_type_title(index_type_title)
		, validated_count(validated_count)
		, index(index) {}

		auto exception_title() const noexcept -> std::string override {
			return "index::negative_exception_type";
		}

		auto exception_details() const noexcept -> std::string override {
			return std::string("Value of ") + index_type_title + " index was negative. Index was " + std::to_string(index) + ". Should be >= 0 and < " + std::to_string(validated_count) + ".";
		}

		private:
		std::string const index_type_title;
		int const validated_count;
		int const index;
	};

	class too_large_exception_type : public validation_exception_base_type {
		public:
		too_large_exception_type(
			std::string const &index_type_title,
			int const validated_count,
			int const index
		) : index_type_title(index_type_title)
		, validated_count(validated_count)
		, index(index) {}

		auto exception_title() const noexcept -> std::string override {
			return "index::too_large_exception_type";
		}

		auto exception_details() const noexcept -> std::string override {
			return std::string("Value of ") + index_type_title + " index was too large. Index was " + std::to_string(index) + ". Should be >= 0 and < " + std::to_string(validated_count) + ".";
		}

		private:
		std::string const index_type_title;
		int const validated_count;
		int const index;
	};

	class validator_type {
		public:
		validator_type(
			std::string const &index_type_title,
			int const validated_count
		) : index_type_title(index_type_title)
		, validated_count(validated_count) {}

		void validate(
			int const index
		) const {
			if (index < 0) {
				throw negative_exception_type(index_type_title, validated_count, index);
			}

			if (index >= validated_count) {
				throw too_large_exception_type(index_type_title, validated_count, index);
			}
		}

		private:
		std::string const index_type_title;
		int const validated_count;
	};
}
