//===---------- Linux implementation of the shm_open function -------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "src/sys/mman/shm_open.h"
#include "hdr/types/mode_t.h"
#include "src/__support/macros/config.h"
#include "src/fcntl/open.h"
#include "src/sys/mman/linux/shm_common.h"

namespace LIBC_NAMESPACE_DECL {

static constexpr int DEFAULT_OFLAGS = O_NOFOLLOW | O_CLOEXEC | O_NONBLOCK;

LLVM_LIBC_FUNCTION(int, shm_open, (const char *name, int oflags, mode_t mode)) {
  using namespace shm_common;
  if (cpp::optional<SHMPath> buffer = translate_name(name))
    return open(buffer->data(), oflags | DEFAULT_OFLAGS, mode);
  return -1;
}

} // namespace LIBC_NAMESPACE_DECL
