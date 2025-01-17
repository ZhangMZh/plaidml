// Copyright (C) 2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "plaidml_ops.hpp"

#include "ngraph/opsets/opset.hpp"
#include "ngraph/opsets/opset1.hpp"

#include "plaidml/op/op.h"

using namespace plaidml;          // NOLINT[build/namespaces]
using namespace InferenceEngine;  // NOLINT[build/namespaces]

namespace PlaidMLPlugin {

void registerSquaredDifference() {
  registerOp("SquaredDifference", [](const Context& ctx) {
    IE_ASSERT(ctx.operands.size() == 2);
    auto A = ctx.operands.at(0);
    auto B = ctx.operands.at(1);
    return edsl::make_tuple(op::square(A - B));
  });
}

}  // namespace PlaidMLPlugin
