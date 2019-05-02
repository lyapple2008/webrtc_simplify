// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/timer/mock_timer.h"

#include "base/bind.h"
#include "base/bind_helpers.h"
#include "base/macros.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace {

void CallMeMaybe(int *number) {
  (*number)++;
}

TEST(MockTimerTest, FiresOnce) {
  int calls = 0;
  base::MockOneShotTimer timer;
  base::TimeDelta delay = base::TimeDelta::FromSeconds(2);
  timer.Start(FROM_HERE, delay,
              base::Bind(&CallMeMaybe,
                         base::Unretained(&calls)));
  EXPECT_EQ(delay, timer.GetCurrentDelay());
  EXPECT_TRUE(timer.IsRunning());
  timer.Fire();
  EXPECT_FALSE(timer.IsRunning());
  EXPECT_EQ(1, calls);
}

TEST(MockTimerTest, FiresRepeatedly) {
  int calls = 0;
  base::MockRepeatingTimer timer;
  base::TimeDelta delay = base::TimeDelta::FromSeconds(2);
  timer.Start(FROM_HERE, delay,
              base::Bind(&CallMeMaybe,
                         base::Unretained(&calls)));
  timer.Fire();
  EXPECT_TRUE(timer.IsRunning());
  timer.Fire();
  timer.Fire();
  EXPECT_TRUE(timer.IsRunning());
  EXPECT_EQ(3, calls);
}

TEST(MockTimerTest, Stops) {
  int calls = 0;
  base::MockRepeatingTimer timer;
  base::TimeDelta delay = base::TimeDelta::FromSeconds(2);
  timer.Start(FROM_HERE, delay,
              base::Bind(&CallMeMaybe,
                         base::Unretained(&calls)));
  EXPECT_TRUE(timer.IsRunning());
  timer.Stop();
  EXPECT_FALSE(timer.IsRunning());
}

class HasWeakPtr : public base::SupportsWeakPtr<HasWeakPtr> {
 public:
  HasWeakPtr() = default;
  virtual ~HasWeakPtr() = default;

 private:
  DISALLOW_COPY_AND_ASSIGN(HasWeakPtr);
};

TEST(MockTimerTest, DoesNotRetainClosure) {
  HasWeakPtr *has_weak_ptr = new HasWeakPtr();
  base::WeakPtr<HasWeakPtr> weak_ptr(has_weak_ptr->AsWeakPtr());
  base::MockOneShotTimer timer;
  base::TimeDelta delay = base::TimeDelta::FromSeconds(2);
  ASSERT_TRUE(weak_ptr.get());
  timer.Start(FROM_HERE, delay,
              base::Bind(base::DoNothing::Repeatedly<HasWeakPtr*>(),
                         base::Owned(has_weak_ptr)));
  ASSERT_TRUE(weak_ptr.get());
  timer.Fire();
  ASSERT_FALSE(weak_ptr.get());
}

}  // namespace
