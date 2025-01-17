// Copyright 2021 Intel Corporation

#include "pmlc/rt/instrument.h"

#include <chrono>

#include "llvm/Support/Format.h"
#include "llvm/Support/raw_ostream.h"

#include "pmlc/rt/symbol_registry.h"
#include "pmlc/util/env.h"

namespace pmlc::rt {

using namespace std::chrono; // NOLINT

static time_point<steady_clock> initTime;
static time_point<steady_clock> globalTime;

void initInstrument() { //
  initTime = globalTime = steady_clock::now();
  if (util::getEnvVar("PLAIDML_PROFILE") == "1") {
    llvm::outs() << "\"id\",\"loc\",\"tag\",\"elapsed\",\"accumulated\"\n";
    llvm::outs().flush();
  }
}

void instrumentPoint(int64_t id, int64_t tag, const char *loc) {
  auto now = steady_clock::now();
  auto lastDuration = duration_cast<duration<double>>(now - globalTime).count();
  auto initDuration = duration_cast<duration<double>>(now - initTime).count();
  llvm::outs() << llvm::format("%03d,%s,%d,%7.6f,%7.6f\n", id, loc, tag,
                               lastDuration, initDuration);
  llvm::outs().flush();
  globalTime = now;
}

} // namespace pmlc::rt

extern "C" void _mlir_ciface_plaidml_rt_instrument(int64_t id, int64_t tag,
                                                   const char *loc) {
  pmlc::rt::instrumentPoint(id, tag, loc);
}

namespace pmlc::rt {

void registerInstrument() { //
  REGISTER_SYMBOL(_mlir_ciface_plaidml_rt_instrument);
}

} // namespace pmlc::rt
