#include <iostream>

#include "internal/indexed_clues_builder_type.hpp"

int main() {
	std::cout << "start\n";

	ao::logic_solver_internal::indexed_clues_builder_type(3, 4)
	.try_append_association_clue({{0, 3}, {1, 1}})
	.try_append_association_clue({{0, 2}, {1, 0}})
	.try_append_offset_clue({1, 0}, -1, 0, {2, 0})
	.try_append_offset_clue({2, 3}, +1, 0, {1, 2})
	.try_append_either_clue({1, 0}, {{0, 1}, {2, 2}})
	;

	std::cout << "end\n";
}
