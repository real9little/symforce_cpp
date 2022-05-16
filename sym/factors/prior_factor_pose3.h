// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <Eigen/Dense>

#include <sym/pose3.h>

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
 *     jacobian: (6x6) jacobian of res wrt arg value (6)
 *     hessian: (6x6) Gauss-Newton hessian for arg value (6)
 *     rhs: (6x1) Gauss-Newton rhs for arg value (6)
 */
template <typename Scalar>
void PriorFactorPose3(const sym::Pose3<Scalar>& value, const sym::Pose3<Scalar>& prior,
                      const Eigen::Matrix<Scalar, 6, 6>& sqrt_info, const Scalar epsilon,
                      Eigen::Matrix<Scalar, 6, 1>* const res = nullptr,
                      Eigen::Matrix<Scalar, 6, 6>* const jacobian = nullptr,
                      Eigen::Matrix<Scalar, 6, 6>* const hessian = nullptr,
                      Eigen::Matrix<Scalar, 6, 1>* const rhs = nullptr) {
  // Total ops: 812

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _value = value.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _prior = prior.Data();

  // Intermediate terms (127)
  const Scalar _tmp0 = _prior[2] * _value[3];
  const Scalar _tmp1 = _prior[1] * _value[0];
  const Scalar _tmp2 = _prior[0] * _value[1];
  const Scalar _tmp3 = _prior[3] * _value[2];
  const Scalar _tmp4 = _prior[3] * _value[3];
  const Scalar _tmp5 = _prior[2] * _value[2];
  const Scalar _tmp6 = _prior[1] * _value[1];
  const Scalar _tmp7 = _prior[0] * _value[0];
  const Scalar _tmp8 = _tmp4 + _tmp5 + _tmp6 + _tmp7;
  const Scalar _tmp9 = (((_tmp8) > 0) - ((_tmp8) < 0));
  const Scalar _tmp10 = 2 * std::min<Scalar>(0, _tmp9) + 1;
  const Scalar _tmp11 = _tmp10 * (-_tmp0 + _tmp1 - _tmp2 + _tmp3);
  const Scalar _tmp12 = std::fabs(_tmp8);
  const Scalar _tmp13 = 1 - epsilon;
  const Scalar _tmp14 = std::min<Scalar>(_tmp12, _tmp13);
  const Scalar _tmp15 = std::acos(_tmp14);
  const Scalar _tmp16 = 1 - std::pow(_tmp14, Scalar(2));
  const Scalar _tmp17 = 2 * _tmp15 / std::sqrt(_tmp16);
  const Scalar _tmp18 = _tmp11 * _tmp17;
  const Scalar _tmp19 = -_prior[6] + _value[6];
  const Scalar _tmp20 = -_prior[5] + _value[5];
  const Scalar _tmp21 = -_prior[4] + _value[4];
  const Scalar _tmp22 = _prior[2] * _value[0];
  const Scalar _tmp23 = _prior[1] * _value[3];
  const Scalar _tmp24 = _prior[0] * _value[2];
  const Scalar _tmp25 = _prior[3] * _value[1];
  const Scalar _tmp26 = -_tmp22 - _tmp23 + _tmp24 + _tmp25;
  const Scalar _tmp27 = _tmp10 * _tmp17;
  const Scalar _tmp28 = _tmp26 * _tmp27;
  const Scalar _tmp29 = _prior[2] * _value[1];
  const Scalar _tmp30 = _prior[1] * _value[2];
  const Scalar _tmp31 = _prior[0] * _value[3];
  const Scalar _tmp32 = _prior[3] * _value[0];
  const Scalar _tmp33 = _tmp29 - _tmp30 - _tmp31 + _tmp32;
  const Scalar _tmp34 = _tmp27 * _tmp33;
  const Scalar _tmp35 = _tmp18 * sqrt_info(0, 2) + _tmp19 * sqrt_info(0, 5) +
                        _tmp20 * sqrt_info(0, 4) + _tmp21 * sqrt_info(0, 3) +
                        _tmp28 * sqrt_info(0, 1) + _tmp34 * sqrt_info(0, 0);
  const Scalar _tmp36 = _tmp11 * sqrt_info(1, 2);
  const Scalar _tmp37 = _tmp17 * _tmp36 + _tmp19 * sqrt_info(1, 5) + _tmp20 * sqrt_info(1, 4) +
                        _tmp21 * sqrt_info(1, 3) + _tmp28 * sqrt_info(1, 1) +
                        _tmp34 * sqrt_info(1, 0);
  const Scalar _tmp38 = _tmp18 * sqrt_info(2, 2) + _tmp19 * sqrt_info(2, 5) +
                        _tmp20 * sqrt_info(2, 4) + _tmp21 * sqrt_info(2, 3) +
                        _tmp28 * sqrt_info(2, 1) + _tmp34 * sqrt_info(2, 0);
  const Scalar _tmp39 = _tmp18 * sqrt_info(3, 2) + _tmp19 * sqrt_info(3, 5) +
                        _tmp20 * sqrt_info(3, 4) + _tmp21 * sqrt_info(3, 3) +
                        _tmp28 * sqrt_info(3, 1) + _tmp34 * sqrt_info(3, 0);
  const Scalar _tmp40 = _tmp18 * sqrt_info(4, 2) + _tmp19 * sqrt_info(4, 5) +
                        _tmp20 * sqrt_info(4, 4) + _tmp21 * sqrt_info(4, 3) +
                        _tmp28 * sqrt_info(4, 1) + _tmp34 * sqrt_info(4, 0);
  const Scalar _tmp41 = _tmp27 * sqrt_info(5, 1);
  const Scalar _tmp42 = _tmp18 * sqrt_info(5, 2) + _tmp19 * sqrt_info(5, 5) +
                        _tmp20 * sqrt_info(5, 4) + _tmp21 * sqrt_info(5, 3) + _tmp26 * _tmp41 +
                        _tmp34 * sqrt_info(5, 0);
  const Scalar _tmp43 = (Scalar(1) / Scalar(2)) * _tmp29;
  const Scalar _tmp44 = (Scalar(1) / Scalar(2)) * _tmp30;
  const Scalar _tmp45 = (Scalar(1) / Scalar(2)) * _tmp31;
  const Scalar _tmp46 = (Scalar(1) / Scalar(2)) * _tmp32;
  const Scalar _tmp47 = -_tmp43 + _tmp44 + _tmp45 - _tmp46;
  const Scalar _tmp48 = _tmp9 * ((((-_tmp12 + _tmp13) > 0) - ((-_tmp12 + _tmp13) < 0)) + 1);
  const Scalar _tmp49 = _tmp48 / _tmp16;
  const Scalar _tmp50 = _tmp47 * _tmp49;
  const Scalar _tmp51 = _tmp10 * _tmp50;
  const Scalar _tmp52 = _tmp33 * _tmp51;
  const Scalar _tmp53 = _tmp14 * _tmp15 * _tmp48 / (_tmp16 * std::sqrt(_tmp16));
  const Scalar _tmp54 = _tmp10 * _tmp53;
  const Scalar _tmp55 = _tmp47 * _tmp54;
  const Scalar _tmp56 = _tmp26 * _tmp55;
  const Scalar _tmp57 = _tmp26 * _tmp51;
  const Scalar _tmp58 = (Scalar(1) / Scalar(2)) * _tmp0;
  const Scalar _tmp59 = (Scalar(1) / Scalar(2)) * _tmp1;
  const Scalar _tmp60 = (Scalar(1) / Scalar(2)) * _tmp2;
  const Scalar _tmp61 = (Scalar(1) / Scalar(2)) * _tmp3;
  const Scalar _tmp62 = -_tmp58 + _tmp59 - _tmp60 + _tmp61;
  const Scalar _tmp63 = _tmp27 * _tmp62;
  const Scalar _tmp64 = _tmp11 * _tmp53;
  const Scalar _tmp65 = _tmp47 * _tmp64;
  const Scalar _tmp66 = _tmp11 * _tmp50;
  const Scalar _tmp67 = _tmp33 * _tmp55;
  const Scalar _tmp68 =
      _tmp27 * ((Scalar(1) / Scalar(2)) * _tmp4 + (Scalar(1) / Scalar(2)) * _tmp5 +
                (Scalar(1) / Scalar(2)) * _tmp6 + (Scalar(1) / Scalar(2)) * _tmp7);
  const Scalar _tmp69 = (Scalar(1) / Scalar(2)) * _tmp22;
  const Scalar _tmp70 = (Scalar(1) / Scalar(2)) * _tmp23;
  const Scalar _tmp71 = (Scalar(1) / Scalar(2)) * _tmp24;
  const Scalar _tmp72 = (Scalar(1) / Scalar(2)) * _tmp25;
  const Scalar _tmp73 = _tmp69 + _tmp70 - _tmp71 - _tmp72;
  const Scalar _tmp74 = _tmp27 * _tmp73;
  const Scalar _tmp75 =
      -_tmp52 * sqrt_info(0, 0) + _tmp56 * sqrt_info(0, 1) - _tmp57 * sqrt_info(0, 1) +
      _tmp63 * sqrt_info(0, 1) + _tmp65 * sqrt_info(0, 2) - _tmp66 * sqrt_info(0, 2) +
      _tmp67 * sqrt_info(0, 0) + _tmp68 * sqrt_info(0, 0) + _tmp74 * sqrt_info(0, 2);
  const Scalar _tmp76 = _tmp47 * _tmp53;
  const Scalar _tmp77 = _tmp33 * sqrt_info(1, 0);
  const Scalar _tmp78 = _tmp27 * sqrt_info(1, 2);
  const Scalar _tmp79 = -_tmp36 * _tmp50 + _tmp36 * _tmp76 - _tmp52 * sqrt_info(1, 0) +
                        _tmp55 * _tmp77 + _tmp56 * sqrt_info(1, 1) - _tmp57 * sqrt_info(1, 1) +
                        _tmp63 * sqrt_info(1, 1) + _tmp68 * sqrt_info(1, 0) + _tmp73 * _tmp78;
  const Scalar _tmp80 = _tmp11 * sqrt_info(2, 2);
  const Scalar _tmp81 = -_tmp50 * _tmp80 - _tmp52 * sqrt_info(2, 0) + _tmp56 * sqrt_info(2, 1) -
                        _tmp57 * sqrt_info(2, 1) + _tmp63 * sqrt_info(2, 1) +
                        _tmp67 * sqrt_info(2, 0) + _tmp68 * sqrt_info(2, 0) +
                        _tmp74 * sqrt_info(2, 2) + _tmp76 * _tmp80;
  const Scalar _tmp82 = _tmp33 * sqrt_info(3, 0);
  const Scalar _tmp83 = -_tmp52 * sqrt_info(3, 0) + _tmp55 * _tmp82 + _tmp56 * sqrt_info(3, 1) -
                        _tmp57 * sqrt_info(3, 1) + _tmp63 * sqrt_info(3, 1) +
                        _tmp65 * sqrt_info(3, 2) - _tmp66 * sqrt_info(3, 2) +
                        _tmp68 * sqrt_info(3, 0) + _tmp74 * sqrt_info(3, 2);
  const Scalar _tmp84 = _tmp26 * sqrt_info(4, 1);
  const Scalar _tmp85 = _tmp64 * sqrt_info(4, 2);
  const Scalar _tmp86 = _tmp47 * _tmp85 - _tmp51 * _tmp84 - _tmp52 * sqrt_info(4, 0) +
                        _tmp55 * _tmp84 + _tmp63 * sqrt_info(4, 1) - _tmp66 * sqrt_info(4, 2) +
                        _tmp67 * sqrt_info(4, 0) + _tmp68 * sqrt_info(4, 0) +
                        _tmp74 * sqrt_info(4, 2);
  const Scalar _tmp87 = _tmp26 * sqrt_info(5, 1);
  const Scalar _tmp88 = _tmp41 * _tmp62 - _tmp51 * _tmp87 - _tmp52 * sqrt_info(5, 0) +
                        _tmp55 * _tmp87 + _tmp65 * sqrt_info(5, 2) - _tmp66 * sqrt_info(5, 2) +
                        _tmp67 * sqrt_info(5, 0) + _tmp68 * sqrt_info(5, 0) +
                        _tmp74 * sqrt_info(5, 2);
  const Scalar _tmp89 = _tmp49 * _tmp73;
  const Scalar _tmp90 = _tmp11 * _tmp89;
  const Scalar _tmp91 = _tmp58 - _tmp59 + _tmp60 - _tmp61;
  const Scalar _tmp92 = _tmp27 * _tmp91;
  const Scalar _tmp93 = _tmp10 * _tmp89;
  const Scalar _tmp94 = _tmp26 * _tmp93;
  const Scalar _tmp95 = _tmp54 * _tmp73;
  const Scalar _tmp96 = _tmp33 * _tmp95;
  const Scalar _tmp97 = _tmp64 * _tmp73;
  const Scalar _tmp98 = _tmp33 * _tmp93;
  const Scalar _tmp99 = _tmp43 - _tmp44 - _tmp45 + _tmp46;
  const Scalar _tmp100 = _tmp27 * _tmp99;
  const Scalar _tmp101 = _tmp26 * _tmp95;
  const Scalar _tmp102 =
      _tmp100 * sqrt_info(0, 2) + _tmp101 * sqrt_info(0, 1) + _tmp68 * sqrt_info(0, 1) -
      _tmp90 * sqrt_info(0, 2) + _tmp92 * sqrt_info(0, 0) - _tmp94 * sqrt_info(0, 1) +
      _tmp96 * sqrt_info(0, 0) + _tmp97 * sqrt_info(0, 2) - _tmp98 * sqrt_info(0, 0);
  const Scalar _tmp103 = _tmp53 * _tmp73;
  const Scalar _tmp104 = _tmp101 * sqrt_info(1, 1) + _tmp103 * _tmp36 - _tmp36 * _tmp89 +
                         _tmp68 * sqrt_info(1, 1) + _tmp77 * _tmp95 + _tmp78 * _tmp99 +
                         _tmp92 * sqrt_info(1, 0) - _tmp94 * sqrt_info(1, 1) -
                         _tmp98 * sqrt_info(1, 0);
  const Scalar _tmp105 = _tmp100 * sqrt_info(2, 2) + _tmp101 * sqrt_info(2, 1) + _tmp103 * _tmp80 +
                         _tmp68 * sqrt_info(2, 1) - _tmp80 * _tmp89 + _tmp92 * sqrt_info(2, 0) -
                         _tmp94 * sqrt_info(2, 1) + _tmp96 * sqrt_info(2, 0) -
                         _tmp98 * sqrt_info(2, 0);
  const Scalar _tmp106 = _tmp100 * sqrt_info(3, 2) + _tmp101 * sqrt_info(3, 1) +
                         _tmp68 * sqrt_info(3, 1) + _tmp82 * _tmp95 - _tmp90 * sqrt_info(3, 2) +
                         _tmp92 * sqrt_info(3, 0) - _tmp94 * sqrt_info(3, 1) +
                         _tmp97 * sqrt_info(3, 2) - _tmp98 * sqrt_info(3, 0);
  const Scalar _tmp107 = _tmp100 * sqrt_info(4, 2) + _tmp68 * sqrt_info(4, 1) + _tmp73 * _tmp85 -
                         _tmp84 * _tmp93 + _tmp84 * _tmp95 - _tmp90 * sqrt_info(4, 2) +
                         _tmp92 * sqrt_info(4, 0) + _tmp96 * sqrt_info(4, 0) -
                         _tmp98 * sqrt_info(4, 0);
  const Scalar _tmp108 = _tmp100 * sqrt_info(5, 2) + _tmp68 * sqrt_info(5, 1) + _tmp87 * _tmp95 -
                         _tmp90 * sqrt_info(5, 2) + _tmp92 * sqrt_info(5, 0) -
                         _tmp94 * sqrt_info(5, 1) + _tmp96 * sqrt_info(5, 0) +
                         _tmp97 * sqrt_info(5, 2) - _tmp98 * sqrt_info(5, 0);
  const Scalar _tmp109 = _tmp49 * _tmp91;
  const Scalar _tmp110 = _tmp10 * _tmp109;
  const Scalar _tmp111 = _tmp110 * _tmp26;
  const Scalar _tmp112 = _tmp110 * _tmp33;
  const Scalar _tmp113 = _tmp54 * _tmp91;
  const Scalar _tmp114 = _tmp113 * _tmp26;
  const Scalar _tmp115 = _tmp27 * (-_tmp69 - _tmp70 + _tmp71 + _tmp72);
  const Scalar _tmp116 = _tmp113 * _tmp33;
  const Scalar _tmp117 = _tmp64 * _tmp91;
  const Scalar _tmp118 = _tmp109 * _tmp11;
  const Scalar _tmp119 = _tmp27 * _tmp47;
  const Scalar _tmp120 =
      -_tmp111 * sqrt_info(0, 1) - _tmp112 * sqrt_info(0, 0) + _tmp114 * sqrt_info(0, 1) +
      _tmp115 * sqrt_info(0, 0) + _tmp116 * sqrt_info(0, 0) + _tmp117 * sqrt_info(0, 2) -
      _tmp118 * sqrt_info(0, 2) + _tmp119 * sqrt_info(0, 1) + _tmp68 * sqrt_info(0, 2);
  const Scalar _tmp121 = _tmp53 * _tmp91;
  const Scalar _tmp122 = -_tmp109 * _tmp36 - _tmp111 * sqrt_info(1, 1) - _tmp112 * sqrt_info(1, 0) +
                         _tmp113 * _tmp77 + _tmp114 * sqrt_info(1, 1) + _tmp115 * sqrt_info(1, 0) +
                         _tmp119 * sqrt_info(1, 1) + _tmp121 * _tmp36 + _tmp68 * sqrt_info(1, 2);
  const Scalar _tmp123 = -_tmp109 * _tmp80 - _tmp111 * sqrt_info(2, 1) - _tmp112 * sqrt_info(2, 0) +
                         _tmp114 * sqrt_info(2, 1) + _tmp115 * sqrt_info(2, 0) +
                         _tmp116 * sqrt_info(2, 0) + _tmp119 * sqrt_info(2, 1) + _tmp121 * _tmp80 +
                         _tmp68 * sqrt_info(2, 2);
  const Scalar _tmp124 = -_tmp111 * sqrt_info(3, 1) - _tmp112 * sqrt_info(3, 0) + _tmp113 * _tmp82 +
                         _tmp114 * sqrt_info(3, 1) + _tmp115 * sqrt_info(3, 0) +
                         _tmp117 * sqrt_info(3, 2) - _tmp118 * sqrt_info(3, 2) +
                         _tmp119 * sqrt_info(3, 1) + _tmp68 * sqrt_info(3, 2);
  const Scalar _tmp125 = -_tmp110 * _tmp84 - _tmp112 * sqrt_info(4, 0) + _tmp113 * _tmp84 +
                         _tmp115 * sqrt_info(4, 0) + _tmp116 * sqrt_info(4, 0) -
                         _tmp118 * sqrt_info(4, 2) + _tmp119 * sqrt_info(4, 1) +
                         _tmp68 * sqrt_info(4, 2) + _tmp85 * _tmp91;
  const Scalar _tmp126 = -_tmp110 * _tmp87 - _tmp112 * sqrt_info(5, 0) + _tmp113 * _tmp87 +
                         _tmp115 * sqrt_info(5, 0) + _tmp116 * sqrt_info(5, 0) +
                         _tmp117 * sqrt_info(5, 2) - _tmp118 * sqrt_info(5, 2) +
                         _tmp119 * sqrt_info(5, 1) + _tmp68 * sqrt_info(5, 2);

  // Output terms (4)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 6, 1>& _res = (*res);

    _res(0, 0) = _tmp35;
    _res(1, 0) = _tmp37;
    _res(2, 0) = _tmp38;
    _res(3, 0) = _tmp39;
    _res(4, 0) = _tmp40;
    _res(5, 0) = _tmp42;
  }

  if (jacobian != nullptr) {
    Eigen::Matrix<Scalar, 6, 6>& _jacobian = (*jacobian);

    _jacobian(0, 0) = _tmp75;
    _jacobian(1, 0) = _tmp79;
    _jacobian(2, 0) = _tmp81;
    _jacobian(3, 0) = _tmp83;
    _jacobian(4, 0) = _tmp86;
    _jacobian(5, 0) = _tmp88;
    _jacobian(0, 1) = _tmp102;
    _jacobian(1, 1) = _tmp104;
    _jacobian(2, 1) = _tmp105;
    _jacobian(3, 1) = _tmp106;
    _jacobian(4, 1) = _tmp107;
    _jacobian(5, 1) = _tmp108;
    _jacobian(0, 2) = _tmp120;
    _jacobian(1, 2) = _tmp122;
    _jacobian(2, 2) = _tmp123;
    _jacobian(3, 2) = _tmp124;
    _jacobian(4, 2) = _tmp125;
    _jacobian(5, 2) = _tmp126;
    _jacobian(0, 3) = sqrt_info(0, 3);
    _jacobian(1, 3) = sqrt_info(1, 3);
    _jacobian(2, 3) = sqrt_info(2, 3);
    _jacobian(3, 3) = sqrt_info(3, 3);
    _jacobian(4, 3) = sqrt_info(4, 3);
    _jacobian(5, 3) = sqrt_info(5, 3);
    _jacobian(0, 4) = sqrt_info(0, 4);
    _jacobian(1, 4) = sqrt_info(1, 4);
    _jacobian(2, 4) = sqrt_info(2, 4);
    _jacobian(3, 4) = sqrt_info(3, 4);
    _jacobian(4, 4) = sqrt_info(4, 4);
    _jacobian(5, 4) = sqrt_info(5, 4);
    _jacobian(0, 5) = sqrt_info(0, 5);
    _jacobian(1, 5) = sqrt_info(1, 5);
    _jacobian(2, 5) = sqrt_info(2, 5);
    _jacobian(3, 5) = sqrt_info(3, 5);
    _jacobian(4, 5) = sqrt_info(4, 5);
    _jacobian(5, 5) = sqrt_info(5, 5);
  }

  if (hessian != nullptr) {
    Eigen::Matrix<Scalar, 6, 6>& _hessian = (*hessian);

    _hessian(0, 0) = std::pow(_tmp75, Scalar(2)) + std::pow(_tmp79, Scalar(2)) +
                     std::pow(_tmp81, Scalar(2)) + std::pow(_tmp83, Scalar(2)) +
                     std::pow(_tmp86, Scalar(2)) + std::pow(_tmp88, Scalar(2));
    _hessian(1, 0) = _tmp102 * _tmp75 + _tmp104 * _tmp79 + _tmp105 * _tmp81 + _tmp106 * _tmp83 +
                     _tmp107 * _tmp86 + _tmp108 * _tmp88;
    _hessian(2, 0) = _tmp120 * _tmp75 + _tmp122 * _tmp79 + _tmp123 * _tmp81 + _tmp124 * _tmp83 +
                     _tmp125 * _tmp86 + _tmp126 * _tmp88;
    _hessian(3, 0) = _tmp75 * sqrt_info(0, 3) + _tmp79 * sqrt_info(1, 3) +
                     _tmp81 * sqrt_info(2, 3) + _tmp83 * sqrt_info(3, 3) +
                     _tmp86 * sqrt_info(4, 3) + _tmp88 * sqrt_info(5, 3);
    _hessian(4, 0) = _tmp75 * sqrt_info(0, 4) + _tmp79 * sqrt_info(1, 4) +
                     _tmp81 * sqrt_info(2, 4) + _tmp83 * sqrt_info(3, 4) +
                     _tmp86 * sqrt_info(4, 4) + _tmp88 * sqrt_info(5, 4);
    _hessian(5, 0) = _tmp75 * sqrt_info(0, 5) + _tmp79 * sqrt_info(1, 5) +
                     _tmp81 * sqrt_info(2, 5) + _tmp83 * sqrt_info(3, 5) +
                     _tmp86 * sqrt_info(4, 5) + _tmp88 * sqrt_info(5, 5);
    _hessian(0, 1) = 0;
    _hessian(1, 1) = std::pow(_tmp102, Scalar(2)) + std::pow(_tmp104, Scalar(2)) +
                     std::pow(_tmp105, Scalar(2)) + std::pow(_tmp106, Scalar(2)) +
                     std::pow(_tmp107, Scalar(2)) + std::pow(_tmp108, Scalar(2));
    _hessian(2, 1) = _tmp102 * _tmp120 + _tmp104 * _tmp122 + _tmp105 * _tmp123 + _tmp106 * _tmp124 +
                     _tmp107 * _tmp125 + _tmp108 * _tmp126;
    _hessian(3, 1) = _tmp102 * sqrt_info(0, 3) + _tmp104 * sqrt_info(1, 3) +
                     _tmp105 * sqrt_info(2, 3) + _tmp106 * sqrt_info(3, 3) +
                     _tmp107 * sqrt_info(4, 3) + _tmp108 * sqrt_info(5, 3);
    _hessian(4, 1) = _tmp102 * sqrt_info(0, 4) + _tmp104 * sqrt_info(1, 4) +
                     _tmp105 * sqrt_info(2, 4) + _tmp106 * sqrt_info(3, 4) +
                     _tmp107 * sqrt_info(4, 4) + _tmp108 * sqrt_info(5, 4);
    _hessian(5, 1) = _tmp102 * sqrt_info(0, 5) + _tmp104 * sqrt_info(1, 5) +
                     _tmp105 * sqrt_info(2, 5) + _tmp106 * sqrt_info(3, 5) +
                     _tmp107 * sqrt_info(4, 5) + _tmp108 * sqrt_info(5, 5);
    _hessian(0, 2) = 0;
    _hessian(1, 2) = 0;
    _hessian(2, 2) = std::pow(_tmp120, Scalar(2)) + std::pow(_tmp122, Scalar(2)) +
                     std::pow(_tmp123, Scalar(2)) + std::pow(_tmp124, Scalar(2)) +
                     std::pow(_tmp125, Scalar(2)) + std::pow(_tmp126, Scalar(2));
    _hessian(3, 2) = _tmp120 * sqrt_info(0, 3) + _tmp122 * sqrt_info(1, 3) +
                     _tmp123 * sqrt_info(2, 3) + _tmp124 * sqrt_info(3, 3) +
                     _tmp125 * sqrt_info(4, 3) + _tmp126 * sqrt_info(5, 3);
    _hessian(4, 2) = _tmp120 * sqrt_info(0, 4) + _tmp122 * sqrt_info(1, 4) +
                     _tmp123 * sqrt_info(2, 4) + _tmp124 * sqrt_info(3, 4) +
                     _tmp125 * sqrt_info(4, 4) + _tmp126 * sqrt_info(5, 4);
    _hessian(5, 2) = _tmp120 * sqrt_info(0, 5) + _tmp122 * sqrt_info(1, 5) +
                     _tmp123 * sqrt_info(2, 5) + _tmp124 * sqrt_info(3, 5) +
                     _tmp125 * sqrt_info(4, 5) + _tmp126 * sqrt_info(5, 5);
    _hessian(0, 3) = 0;
    _hessian(1, 3) = 0;
    _hessian(2, 3) = 0;
    _hessian(3, 3) = std::pow(sqrt_info(0, 3), Scalar(2)) + std::pow(sqrt_info(1, 3), Scalar(2)) +
                     std::pow(sqrt_info(2, 3), Scalar(2)) + std::pow(sqrt_info(3, 3), Scalar(2)) +
                     std::pow(sqrt_info(4, 3), Scalar(2)) + std::pow(sqrt_info(5, 3), Scalar(2));
    _hessian(4, 3) = sqrt_info(0, 3) * sqrt_info(0, 4) + sqrt_info(1, 3) * sqrt_info(1, 4) +
                     sqrt_info(2, 3) * sqrt_info(2, 4) + sqrt_info(3, 3) * sqrt_info(3, 4) +
                     sqrt_info(4, 3) * sqrt_info(4, 4) + sqrt_info(5, 3) * sqrt_info(5, 4);
    _hessian(5, 3) = sqrt_info(0, 3) * sqrt_info(0, 5) + sqrt_info(1, 3) * sqrt_info(1, 5) +
                     sqrt_info(2, 3) * sqrt_info(2, 5) + sqrt_info(3, 3) * sqrt_info(3, 5) +
                     sqrt_info(4, 3) * sqrt_info(4, 5) + sqrt_info(5, 3) * sqrt_info(5, 5);
    _hessian(0, 4) = 0;
    _hessian(1, 4) = 0;
    _hessian(2, 4) = 0;
    _hessian(3, 4) = 0;
    _hessian(4, 4) = std::pow(sqrt_info(0, 4), Scalar(2)) + std::pow(sqrt_info(1, 4), Scalar(2)) +
                     std::pow(sqrt_info(2, 4), Scalar(2)) + std::pow(sqrt_info(3, 4), Scalar(2)) +
                     std::pow(sqrt_info(4, 4), Scalar(2)) + std::pow(sqrt_info(5, 4), Scalar(2));
    _hessian(5, 4) = sqrt_info(0, 4) * sqrt_info(0, 5) + sqrt_info(1, 4) * sqrt_info(1, 5) +
                     sqrt_info(2, 4) * sqrt_info(2, 5) + sqrt_info(3, 4) * sqrt_info(3, 5) +
                     sqrt_info(4, 4) * sqrt_info(4, 5) + sqrt_info(5, 4) * sqrt_info(5, 5);
    _hessian(0, 5) = 0;
    _hessian(1, 5) = 0;
    _hessian(2, 5) = 0;
    _hessian(3, 5) = 0;
    _hessian(4, 5) = 0;
    _hessian(5, 5) = std::pow(sqrt_info(0, 5), Scalar(2)) + std::pow(sqrt_info(1, 5), Scalar(2)) +
                     std::pow(sqrt_info(2, 5), Scalar(2)) + std::pow(sqrt_info(3, 5), Scalar(2)) +
                     std::pow(sqrt_info(4, 5), Scalar(2)) + std::pow(sqrt_info(5, 5), Scalar(2));
  }

  if (rhs != nullptr) {
    Eigen::Matrix<Scalar, 6, 1>& _rhs = (*rhs);

    _rhs(0, 0) = _tmp35 * _tmp75 + _tmp37 * _tmp79 + _tmp38 * _tmp81 + _tmp39 * _tmp83 +
                 _tmp40 * _tmp86 + _tmp42 * _tmp88;
    _rhs(1, 0) = _tmp102 * _tmp35 + _tmp104 * _tmp37 + _tmp105 * _tmp38 + _tmp106 * _tmp39 +
                 _tmp107 * _tmp40 + _tmp108 * _tmp42;
    _rhs(2, 0) = _tmp120 * _tmp35 + _tmp122 * _tmp37 + _tmp123 * _tmp38 + _tmp124 * _tmp39 +
                 _tmp125 * _tmp40 + _tmp126 * _tmp42;
    _rhs(3, 0) = _tmp35 * sqrt_info(0, 3) + _tmp37 * sqrt_info(1, 3) + _tmp38 * sqrt_info(2, 3) +
                 _tmp39 * sqrt_info(3, 3) + _tmp40 * sqrt_info(4, 3) + _tmp42 * sqrt_info(5, 3);
    _rhs(4, 0) = _tmp35 * sqrt_info(0, 4) + _tmp37 * sqrt_info(1, 4) + _tmp38 * sqrt_info(2, 4) +
                 _tmp39 * sqrt_info(3, 4) + _tmp40 * sqrt_info(4, 4) + _tmp42 * sqrt_info(5, 4);
    _rhs(5, 0) = _tmp35 * sqrt_info(0, 5) + _tmp37 * sqrt_info(1, 5) + _tmp38 * sqrt_info(2, 5) +
                 _tmp39 * sqrt_info(3, 5) + _tmp40 * sqrt_info(4, 5) + _tmp42 * sqrt_info(5, 5);
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym