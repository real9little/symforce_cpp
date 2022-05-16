// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/ops/CLASS/group_ops.cc.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./group_ops.h"

#include <sym/linear_camera_cal.h>

namespace sym {

/**
 *
 * This function was autogenerated from a symbolic function. Do not modify by hand.
 *
 * Symbolic function: <lambda>
 *
 * Args:
 *
 * Outputs:
 *     res: LinearCameraCal
 */
template <typename Scalar>
sym::LinearCameraCal<Scalar> GroupOps<LinearCameraCal<Scalar>>::Identity() {
  // Total ops: 0

  // Input arrays

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 4, 1> _res;

  _res[0] = 0;
  _res[1] = 0;
  _res[2] = 0;
  _res[3] = 0;

  return sym::LinearCameraCal<Scalar>(_res);
}

/**
 *
 * Inverse of the element a.
 *
 * Returns:
 *     Element: b such that a @ b = identity
 */
template <typename Scalar>
sym::LinearCameraCal<Scalar> GroupOps<LinearCameraCal<Scalar>>::Inverse(
    const sym::LinearCameraCal<Scalar>& a) {
  // Total ops: 4

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 4, 1> _res;

  _res[0] = -_a[0];
  _res[1] = -_a[1];
  _res[2] = -_a[2];
  _res[3] = -_a[3];

  return sym::LinearCameraCal<Scalar>(_res);
}

/**
 *
 * Composition of two elements in the group.
 *
 * Returns:
 *     Element: a @ b
 */
template <typename Scalar>
sym::LinearCameraCal<Scalar> GroupOps<LinearCameraCal<Scalar>>::Compose(
    const sym::LinearCameraCal<Scalar>& a, const sym::LinearCameraCal<Scalar>& b) {
  // Total ops: 4

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 4, 1>& _b = b.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 4, 1> _res;

  _res[0] = _a[0] + _b[0];
  _res[1] = _a[1] + _b[1];
  _res[2] = _a[2] + _b[2];
  _res[3] = _a[3] + _b[3];

  return sym::LinearCameraCal<Scalar>(_res);
}

/**
 *
 * Returns the element that when composed with a produces b. For vector spaces it is b - a.
 *
 * Implementation is simply `compose(inverse(a), b)`.
 *
 * Returns:
 *     Element: c such that a @ c = b
 */
template <typename Scalar>
sym::LinearCameraCal<Scalar> GroupOps<LinearCameraCal<Scalar>>::Between(
    const sym::LinearCameraCal<Scalar>& a, const sym::LinearCameraCal<Scalar>& b) {
  // Total ops: 4

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 4, 1>& _b = b.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 4, 1> _res;

  _res[0] = -_a[0] + _b[0];
  _res[1] = -_a[1] + _b[1];
  _res[2] = -_a[2] + _b[2];
  _res[3] = -_a[3] + _b[3];

  return sym::LinearCameraCal<Scalar>(_res);
}

/**
 *
 * Inverse of the element a.
 *
 * Returns:
 *     Element: b such that a @ b = identity
 *     res_D_a: (4x4) jacobian of res (4) wrt arg a (4)
 */
template <typename Scalar>
sym::LinearCameraCal<Scalar> GroupOps<LinearCameraCal<Scalar>>::InverseWithJacobian(
    const sym::LinearCameraCal<Scalar>& a, SelfJacobian* const res_D_a) {
  // Total ops: 4

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();

  // Intermediate terms (0)

  // Output terms (2)
  Eigen::Matrix<Scalar, 4, 1> _res;

  _res[0] = -_a[0];
  _res[1] = -_a[1];
  _res[2] = -_a[2];
  _res[3] = -_a[3];

  if (res_D_a != nullptr) {
    Eigen::Matrix<Scalar, 4, 4>& _res_D_a = (*res_D_a);

    _res_D_a.setZero();

    _res_D_a(0, 0) = -1;
    _res_D_a(1, 1) = -1;
    _res_D_a(2, 2) = -1;
    _res_D_a(3, 3) = -1;
  }

  return sym::LinearCameraCal<Scalar>(_res);
}

/**
 *
 * Composition of two elements in the group.
 *
 * Returns:
 *     Element: a @ b
 *     res_D_a: (4x4) jacobian of res (4) wrt arg a (4)
 *     res_D_b: (4x4) jacobian of res (4) wrt arg b (4)
 */
template <typename Scalar>
sym::LinearCameraCal<Scalar> GroupOps<LinearCameraCal<Scalar>>::ComposeWithJacobians(
    const sym::LinearCameraCal<Scalar>& a, const sym::LinearCameraCal<Scalar>& b,
    SelfJacobian* const res_D_a, SelfJacobian* const res_D_b) {
  // Total ops: 4

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 4, 1>& _b = b.Data();

  // Intermediate terms (0)

  // Output terms (3)
  Eigen::Matrix<Scalar, 4, 1> _res;

  _res[0] = _a[0] + _b[0];
  _res[1] = _a[1] + _b[1];
  _res[2] = _a[2] + _b[2];
  _res[3] = _a[3] + _b[3];

  if (res_D_a != nullptr) {
    Eigen::Matrix<Scalar, 4, 4>& _res_D_a = (*res_D_a);

    _res_D_a.setZero();

    _res_D_a(0, 0) = 1;
    _res_D_a(1, 1) = 1;
    _res_D_a(2, 2) = 1;
    _res_D_a(3, 3) = 1;
  }

  if (res_D_b != nullptr) {
    Eigen::Matrix<Scalar, 4, 4>& _res_D_b = (*res_D_b);

    _res_D_b.setZero();

    _res_D_b(0, 0) = 1;
    _res_D_b(1, 1) = 1;
    _res_D_b(2, 2) = 1;
    _res_D_b(3, 3) = 1;
  }

  return sym::LinearCameraCal<Scalar>(_res);
}

/**
 *
 * Returns the element that when composed with a produces b. For vector spaces it is b - a.
 *
 * Implementation is simply `compose(inverse(a), b)`.
 *
 * Returns:
 *     Element: c such that a @ c = b
 *     res_D_a: (4x4) jacobian of res (4) wrt arg a (4)
 *     res_D_b: (4x4) jacobian of res (4) wrt arg b (4)
 */
template <typename Scalar>
sym::LinearCameraCal<Scalar> GroupOps<LinearCameraCal<Scalar>>::BetweenWithJacobians(
    const sym::LinearCameraCal<Scalar>& a, const sym::LinearCameraCal<Scalar>& b,
    SelfJacobian* const res_D_a, SelfJacobian* const res_D_b) {
  // Total ops: 4

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 4, 1>& _b = b.Data();

  // Intermediate terms (0)

  // Output terms (3)
  Eigen::Matrix<Scalar, 4, 1> _res;

  _res[0] = -_a[0] + _b[0];
  _res[1] = -_a[1] + _b[1];
  _res[2] = -_a[2] + _b[2];
  _res[3] = -_a[3] + _b[3];

  if (res_D_a != nullptr) {
    Eigen::Matrix<Scalar, 4, 4>& _res_D_a = (*res_D_a);

    _res_D_a.setZero();

    _res_D_a(0, 0) = -1;
    _res_D_a(1, 1) = -1;
    _res_D_a(2, 2) = -1;
    _res_D_a(3, 3) = -1;
  }

  if (res_D_b != nullptr) {
    Eigen::Matrix<Scalar, 4, 4>& _res_D_b = (*res_D_b);

    _res_D_b.setZero();

    _res_D_b(0, 0) = 1;
    _res_D_b(1, 1) = 1;
    _res_D_b(2, 2) = 1;
    _res_D_b(3, 3) = 1;
  }

  return sym::LinearCameraCal<Scalar>(_res);
}

}  // namespace sym

// Explicit instantiation
template struct sym::GroupOps<sym::LinearCameraCal<double>>;
template struct sym::GroupOps<sym::LinearCameraCal<float>>;
