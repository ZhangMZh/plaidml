// Copyright 2020 Intel Corporation

#pragma once

#include <memory>
#include <vector>

#include "pmlc/compiler/program.h"
#include "pmlc/util/buffer.h"

namespace pmlc::rt {

class Executable {
public:
  static std::unique_ptr<Executable>
  fromProgram(const std::shared_ptr<pmlc::compiler::Program> &program,
              mlir::StringRef deviceID);

  virtual ~Executable() = default;

  virtual double invoke() = 0;

  virtual double invoke(mlir::ArrayRef<util::BufferPtr> inputBuffers,
                        mlir::ArrayRef<util::BufferPtr> outputBuffers) = 0;
};

} // namespace pmlc::rt
