//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// rwmutex.h
//
// Identification: src/include/common/rwlatch.h
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <mutex>  // NOLINT
#include <shared_mutex>

#include "common/macros.h"

namespace bustub {

/**
 * Reader-Writer latch backed by std::mutex.
 */
class ReaderWriterLatch {
 public:
  /**
   * Acquire a write latch.
   */
  void WLock() { mutex_.lock(); }

  /**
   * Release a write latch.
   */
  void WUnlock() { mutex_.unlock(); }

  /**
   * Acquire a read latch.
   */
  void RLock() { mutex_.lock_shared(); }

  /**
   * Release a read latch.
   */
  void RUnlock() { mutex_.unlock_shared(); }

 private:
  std::shared_mutex mutex_;
};

class lock_guard_r {
 private:
  ReaderWriterLatch &rwlock_;

 public:
  explicit lock_guard_r(ReaderWriterLatch &rwlock) : rwlock_(rwlock) { rwlock_.RLock(); }
  ~lock_guard_r() { rwlock_.RUnlock(); }
};
class lock_guard_w {
 private:
  ReaderWriterLatch &rwlock_;

 public:
  explicit lock_guard_w(ReaderWriterLatch &rwlock) : rwlock_(rwlock) { rwlock_.WLock(); }
  ~lock_guard_w() { rwlock_.WUnlock(); }
};

}  // namespace bustub
