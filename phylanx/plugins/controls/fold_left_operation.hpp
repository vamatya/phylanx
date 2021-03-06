// Copyright (c) 2018-2019 Hartmut Kaiser
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(PHYLANX_FOLD_LEFT_OPERATION_MAR_15_2018_0214PM)
#define PHYLANX_FOLD_LEFT_OPERATION_MAR_15_2018_0214PM

#include <phylanx/config.hpp>
#include <phylanx/execution_tree/primitives/base_primitive.hpp>
#include <phylanx/execution_tree/primitives/primitive_component_base.hpp>

#include <hpx/lcos/future.hpp>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace phylanx { namespace execution_tree { namespace primitives
{
    class fold_left_operation
      : public primitive_component_base
      , public std::enable_shared_from_this<fold_left_operation>
    {
    public:
        static match_pattern_type const match_data;

        fold_left_operation() = default;

        fold_left_operation(primitive_arguments_type&& operands,
            std::string const& name, std::string const& codename);

    protected:
        hpx::future<primitive_argument_type> eval(
            primitive_arguments_type const& operands,
            primitive_arguments_type const& args,
            eval_context ctx) const override;

        primitive_argument_type fold_left_list(
            primitive_argument_type&& bound_func,
            primitive_argument_type&& initial, primitive_argument_type&& data,
            eval_context ctx) const;

        template <typename T>
        primitive_argument_type fold_left_array_helper_1d(
            primitive_argument_type&& bound_func,
            primitive_argument_type&& initial, ir::node_data<T>&& data,
            eval_context ctx) const;

        template <typename T>
        primitive_argument_type fold_left_array_helper_2d(
            primitive_argument_type&& bound_func,
            primitive_argument_type&& initial, ir::node_data<T>&& data,
            eval_context ctx) const;

        template <typename T>
        primitive_argument_type fold_left_array_helper_3d(
            primitive_argument_type&& bound_func,
            primitive_argument_type&& initial, ir::node_data<T>&& data,
            eval_context ctx) const;

        template <typename T>
        primitive_argument_type fold_left_array_helper(
            primitive_argument_type&& bound_func,
            primitive_argument_type&& initial, ir::node_data<T>&& data,
            eval_context ctx) const;

        primitive_argument_type fold_left_array(
            primitive_argument_type&& bound_func,
            primitive_argument_type&& initial, primitive_argument_type&& data,
            eval_context ctx) const;
    };

    inline primitive create_fold_left_operation(hpx::id_type const& locality,
        primitive_arguments_type&& operands,
        std::string const& name = "", std::string const& codename = "")
    {
        return create_primitive_component(
            locality, "fold_left", std::move(operands), name, codename);
    }
}}}

#endif
