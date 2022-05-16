/* ----------------------------------------------------------------------------
 * SymForce - Copyright 2022, Skydio, Inc.
 * This source code is under the Apache 2.0 license found in the LICENSE file.
 * ---------------------------------------------------------------------------- */

#include "./epsilon.h"

// Explicit instantiation
template const double sym::kDefaultEpsilon<double>;
template const float sym::kDefaultEpsilon<float>;
