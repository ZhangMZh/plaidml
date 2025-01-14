// Copyright 2020 Intel Corporation

#pragma once

#include <memory>
#include <regex>
#include <string>
#include <unordered_map>

#include "mlir/Support/LLVM.h"
#include "pmlc/rt/runtime.h"

namespace pmlc::rt {

// getDeviceIDRegex returns the regular expression used to match device
// identifiers.
//
// When matching a device identifier, match[1] will be the runtime identifier,
// and match[3] will be the device index within that runtime.
const std::regex &getDeviceIDRegex();

// getRuntime returns a specific runtime from the runtime map.
Runtime *getRuntime(mlir::StringRef id);

// getRuntimeMap returns the current map of runtimes available to the current
// process.
const std::unordered_map<std::string, std::shared_ptr<Runtime>> &
getRuntimeMap();

} // namespace pmlc::rt
