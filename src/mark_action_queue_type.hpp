#pragma once

#include <queue>
#include <memory>

#include "field_id_type.hpp"

namespace ao::logic_solver_internal
{
    class mark_action_queue_type
    {
        public:
            mark_action_queue_type()
            : action_queue()
            {}

            void
            enqueue_association_action(
                field_id_type field_ids[2]
            )
            {}

            void
            enqueue_disassociation_action(
                field_id_type field_ids[2]
            )
            {}

        private:
            class mark_action_type
            {
                public:
            };

            // TODO: create mark_association_action_type and mark_disassociation_action_type

            std::queue<std::unique_ptr<mark_action_type>> action_queue;
    };
}
