// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <Eigen/Dense>

namespace sym {

/**
 * Residual that penalizes the difference between a value and prior (desired / measured value).
 *
 * In vector space terms that would be:
 *     prior - value
 *
 * In lie group terms:
 *     to_tangent(compose(inverse(value), prior))
 *
 * Args:
 *     sqrt_info: Square root information matrix to whiten residual. This can be computed from
 *                a covariance matrix as the cholesky decomposition of the inverse. In the case
 *                of a diagonal it will contain 1/sigma values. Must match the tangent dim.
 *     jacobian: (3x3) jacobian of res wrt arg value (3)
 *     hessian: (3x3) Gauss-Newton hessian for arg value (3)
 *     rhs: (3x1) Gauss-Newton rhs for arg value (3)
 */
template <typename Scalar>
void PriorFactorMatrix31(const Eigen::Matrix<Scalar, 3, 1>& value,
                         const Eigen::Matrix<Scalar, 3, 1>& prior,
                         const Eigen::Matrix<Scalar, 3, 3>& sqrt_info, const Scalar epsilon,
                         Eigen::Matrix<Scalar, 3, 1>* const res = nullptr,
                         Eigen::Matrix<Scalar, 3, 3>* const jacobian = nullptr,
                         Eigen::Matrix<Scalar, 3, 3>* const hessian = nullptr,
                         Eigen::Matrix<Scalar, 3, 1>* const rhs = nullptr) {
  // Total ops: 63

  // Input arrays

  // Intermediate terms (6)
  const Scalar _tmp0 = -prior(1, 0) + value(1, 0);
  const Scalar _tmp1 = -prior(2, 0) + value(2, 0);
  const Scalar _tmp2 = -prior(0, 0) + value(0, 0);
  const Scalar _tmp3 = _tmp0 * sqrt_info(0, 1) + _tmp1 * sqrt_info(0, 2) + _tmp2 * sqrt_info(0, 0);
  const Scalar _tmp4 = _tmp0 * sqrt_info(1, 1) + _tmp1 * sqrt_info(1, 2) + _tmp2 * sqrt_info(1, 0);
  const Scalar _tmp5 = _tmp0 * sqrt_info(2, 1) + _tmp1 * sqrt_info(2, 2) + _tmp2 * sqrt_info(2, 0);

  // Output terms (4)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 3, 1>& _res = (*res);

    _res(0, 0) = _tmp3;
    _res(1, 0) = _tmp4;
    _res(2, 0) = _tmp5;
  }

  if (jacobian != nullptr) {
    Eigen::Matrix<Scalar, 3, 3>& _jacobian = (*jacobian);

    _jacobian(0, 0) = sqrt_info(0, 0);
    _jacobian(1, 0) = sqrt_info(1, 0);
    _jacobian(2, 0) = sqrt_info(2, 0);
    _jacobian(0, 1) = sqrt_info(0, 1);
    _jacobian(1, 1) = sqrt_info(1, 1);
    _jacobian(2, 1) = sqrt_info(2, 1);
    _jacobian(0, 2) = sqrt_info(0, 2);
    _jacobian(1, 2) = sqrt_info(1, 2);
    _jacobian(2, 2) = sqrt_info(2, 2);
  }

  if (hessian != nullptr) {
    Eigen::Matrix<Scalar, 3, 3>& _hessian = (*hessian);

    _hessian(0, 0) = std::pow(sqrt_info(0, 0), Scalar(2)) + std::pow(sqrt_info(1, 0), Scalar(2)) +
                     std::pow(sqrt_info(2, 0), Scalar(2));
    _hessian(1, 0) = sqrt_info(0, 0) * sqrt_info(0, 1) + sqrt_info(1, 0) * sqrt_info(1, 1) +
                     sqrt_info(2, 0) * sqrt_info(2, 1);
    _hessian(2, 0) = sqrt_info(0, 0) * sqrt_info(0, 2) + sqrt_info(1, 0) * sqrt_info(1, 2) +
                     sqrt_info(2, 0) * sqrt_info(2, 2);
    _hessian(0, 1) = 0;
    _hessian(1, 1) = std::pow(sqrt_info(0, 1), Scalar(2)) + std::pow(sqrt_info(1, 1), Scalar(2)) +
                     std::pow(sqrt_info(2, 1), Scalar(2));
    _hessian(2, 1) = sqrt_info(0, 1) * sqrt_info(0, 2) + sqrt_info(1, 1) * sqrt_info(1, 2) +
                     sqrt_info(2, 1) * sqrt_info(2, 2);
    _hessian(0, 2) = 0;
    _hessian(1, 2) = 0;
    _hessian(2, 2) = std::pow(sqrt_info(0, 2), Scalar(2)) + std::pow(sqrt_info(1, 2), Scalar(2)) +
                     std::pow(sqrt_info(2, 2), Scalar(2));
  }

  if (rhs != nullptr) {
    Eigen::Matrix<Scalar, 3, 1>& _rhs = (*rhs);

    _rhs(0, 0) = _tmp3 * sqrt_info(0, 0) + _tmp4 * sqrt_info(1, 0) + _tmp5 * sqrt_info(2, 0);
    _rhs(1, 0) = _tmp3 * sqrt_info(0, 1) + _tmp4 * sqrt_info(1, 1) + _tmp5 * sqrt_info(2, 1);
    _rhs(2, 0) = _tmp3 * sqrt_info(0, 2) + _tmp4 * sqrt_info(1, 2) + _tmp5 * sqrt_info(2, 2);
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
