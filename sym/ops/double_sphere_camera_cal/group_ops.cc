// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/ops/CLASS/group_ops.cc.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./group_ops.h"

#include <sym/double_sphere_camera_cal.h>

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
 *     res: DoubleSphereCameraCal
 */
template <typename Scalar>
sym::DoubleSphereCameraCal<Scalar> GroupOps<DoubleSphereCameraCal<Scalar>>::Identity() {
  // Total ops: 0

  // Input arrays

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 6, 1> _res;

  _res[0] = 0;
  _res[1] = 0;
  _res[2] = 0;
  _res[3] = 0;
  _res[4] = 0;
  _res[5] = 0;

  return sym::DoubleSphereCameraCal<Scalar>(_res);
}

/**
 *
 * Inverse of the element a.
 *
 * Returns:
 *     Element: b such that a @ b = identity
 */
template <typename Scalar>
sym::DoubleSphereCameraCal<Scalar> GroupOps<DoubleSphereCameraCal<Scalar>>::Inverse(
    const sym::DoubleSphereCameraCal<Scalar>& a) {
  // Total ops: 6

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _a = a.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 6, 1> _res;

  _res[0] = -_a[0];
  _res[1] = -_a[1];
  _res[2] = -_a[2];
  _res[3] = -_a[3];
  _res[4] = -_a[4];
  _res[5] = -_a[5];

  return sym::DoubleSphereCameraCal<Scalar>(_res);
}

/**
 *
 * Composition of two elements in the group.
 *
 * Returns:
 *     Element: a @ b
 */
template <typename Scalar>
sym::DoubleSphereCameraCal<Scalar> GroupOps<DoubleSphereCameraCal<Scalar>>::Compose(
    const sym::DoubleSphereCameraCal<Scalar>& a, const sym::DoubleSphereCameraCal<Scalar>& b) {
  // Total ops: 6

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 6, 1>& _b = b.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 6, 1> _res;

  _res[0] = _a[0] + _b[0];
  _res[1] = _a[1] + _b[1];
  _res[2] = _a[2] + _b[2];
  _res[3] = _a[3] + _b[3];
  _res[4] = _a[4] + _b[4];
  _res[5] = _a[5] + _b[5];

  return sym::DoubleSphereCameraCal<Scalar>(_res);
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
sym::DoubleSphereCameraCal<Scalar> GroupOps<DoubleSphereCameraCal<Scalar>>::Between(
    const sym::DoubleSphereCameraCal<Scalar>& a, const sym::DoubleSphereCameraCal<Scalar>& b) {
  // Total ops: 6

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 6, 1>& _b = b.Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 6, 1> _res;

  _res[0] = -_a[0] + _b[0];
  _res[1] = -_a[1] + _b[1];
  _res[2] = -_a[2] + _b[2];
  _res[3] = -_a[3] + _b[3];
  _res[4] = -_a[4] + _b[4];
  _res[5] = -_a[5] + _b[5];

  return sym::DoubleSphereCameraCal<Scalar>(_res);
}

/**
 *
 * Inverse of the element a.
 *
 * Returns:
 *     Element: b such that a @ b = identity
 *     res_D_a: (6x6) jacobian of res (6) wrt arg a (6)
 */
template <typename Scalar>
sym::DoubleSphereCameraCal<Scalar> GroupOps<DoubleSphereCameraCal<Scalar>>::InverseWithJacobian(
    const sym::DoubleSphereCameraCal<Scalar>& a, SelfJacobian* const res_D_a) {
  // Total ops: 6

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _a = a.Data();

  // Intermediate terms (0)

  // Output terms (2)
  Eigen::Matrix<Scalar, 6, 1> _res;

  _res[0] = -_a[0];
  _res[1] = -_a[1];
  _res[2] = -_a[2];
  _res[3] = -_a[3];
  _res[4] = -_a[4];
  _res[5] = -_a[5];

  if (res_D_a != nullptr) {
    Eigen::Matrix<Scalar, 6, 6>& _res_D_a = (*res_D_a);

    _res_D_a.setZero();

    _res_D_a(0, 0) = -1;
    _res_D_a(1, 1) = -1;
    _res_D_a(2, 2) = -1;
    _res_D_a(3, 3) = -1;
    _res_D_a(4, 4) = -1;
    _res_D_a(5, 5) = -1;
  }

  return sym::DoubleSphereCameraCal<Scalar>(_res);
}

/**
 *
 * Composition of two elements in the group.
 *
 * Returns:
 *     Element: a @ b
 *     res_D_a: (6x6) jacobian of res (6) wrt arg a (6)
 *     res_D_b: (6x6) jacobian of res (6) wrt arg b (6)
 */
template <typename Scalar>
sym::DoubleSphereCameraCal<Scalar> GroupOps<DoubleSphereCameraCal<Scalar>>::ComposeWithJacobians(
    const sym::DoubleSphereCameraCal<Scalar>& a, const sym::DoubleSphereCameraCal<Scalar>& b,
    SelfJacobian* const res_D_a, SelfJacobian* const res_D_b) {
  // Total ops: 6

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 6, 1>& _b = b.Data();

  // Intermediate terms (0)

  // Output terms (3)
  Eigen::Matrix<Scalar, 6, 1> _res;

  _res[0] = _a[0] + _b[0];
  _res[1] = _a[1] + _b[1];
  _res[2] = _a[2] + _b[2];
  _res[3] = _a[3] + _b[3];
  _res[4] = _a[4] + _b[4];
  _res[5] = _a[5] + _b[5];

  if (res_D_a != nullptr) {
    Eigen::Matrix<Scalar, 6, 6>& _res_D_a = (*res_D_a);

    _res_D_a.setZero();

    _res_D_a(0, 0) = 1;
    _res_D_a(1, 1) = 1;
    _res_D_a(2, 2) = 1;
    _res_D_a(3, 3) = 1;
    _res_D_a(4, 4) = 1;
    _res_D_a(5, 5) = 1;
  }

  if (res_D_b != nullptr) {
    Eigen::Matrix<Scalar, 6, 6>& _res_D_b = (*res_D_b);

    _res_D_b.setZero();

    _res_D_b(0, 0) = 1;
    _res_D_b(1, 1) = 1;
    _res_D_b(2, 2) = 1;
    _res_D_b(3, 3) = 1;
    _res_D_b(4, 4) = 1;
    _res_D_b(5, 5) = 1;
  }

  return sym::DoubleSphereCameraCal<Scalar>(_res);
}

/**
 *
 * Returns the element that when composed with a produces b. For vector spaces it is b - a.
 *
 * Implementation is simply `compose(inverse(a), b)`.
 *
 * Returns:
 *     Element: c such that a @ c = b
 *     res_D_a: (6x6) jacobian of res (6) wrt arg a (6)
 *     res_D_b: (6x6) jacobian of res (6) wrt arg b (6)
 */
template <typename Scalar>
sym::DoubleSphereCameraCal<Scalar> GroupOps<DoubleSphereCameraCal<Scalar>>::BetweenWithJacobians(
    const sym::DoubleSphereCameraCal<Scalar>& a, const sym::DoubleSphereCameraCal<Scalar>& b,
    SelfJacobian* const res_D_a, SelfJacobian* const res_D_b) {
  // Total ops: 6

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 6, 1>& _b = b.Data();

  // Intermediate terms (0)

  // Output terms (3)
  Eigen::Matrix<Scalar, 6, 1> _res;

  _res[0] = -_a[0] + _b[0];
  _res[1] = -_a[1] + _b[1];
  _res[2] = -_a[2] + _b[2];
  _res[3] = -_a[3] + _b[3];
  _res[4] = -_a[4] + _b[4];
  _res[5] = -_a[5] + _b[5];

  if (res_D_a != nullptr) {
    Eigen::Matrix<Scalar, 6, 6>& _res_D_a = (*res_D_a);

    _res_D_a.setZero();

    _res_D_a(0, 0) = -1;
    _res_D_a(1, 1) = -1;
    _res_D_a(2, 2) = -1;
    _res_D_a(3, 3) = -1;
    _res_D_a(4, 4) = -1;
    _res_D_a(5, 5) = -1;
  }

  if (res_D_b != nullptr) {
    Eigen::Matrix<Scalar, 6, 6>& _res_D_b = (*res_D_b);

    _res_D_b.setZero();

    _res_D_b(0, 0) = 1;
    _res_D_b(1, 1) = 1;
    _res_D_b(2, 2) = 1;
    _res_D_b(3, 3) = 1;
    _res_D_b(4, 4) = 1;
    _res_D_b(5, 5) = 1;
  }

  return sym::DoubleSphereCameraCal<Scalar>(_res);
}

}  // namespace sym

// Explicit instantiation
template struct sym::GroupOps<sym::DoubleSphereCameraCal<double>>;
template struct sym::GroupOps<sym::DoubleSphereCameraCal<float>>;
