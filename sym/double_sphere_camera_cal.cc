// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/cam_package/CLASS.cc.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./double_sphere_camera_cal.h"

// Camera operation implementations
namespace sym {

template <typename Scalar>
Eigen::Matrix<Scalar, 2, 1> DoubleSphereCameraCal<Scalar>::FocalLength() const {
  // Total ops: 0

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _self = Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 2, 1> _focal_length;

  _focal_length(0, 0) = _self[0];
  _focal_length(1, 0) = _self[1];

  return _focal_length;
}

template <typename Scalar>
Eigen::Matrix<Scalar, 2, 1> DoubleSphereCameraCal<Scalar>::PrincipalPoint() const {
  // Total ops: 0

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _self = Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 2, 1> _principal_point;

  _principal_point(0, 0) = _self[2];
  _principal_point(1, 0) = _self[3];

  return _principal_point;
}

template <typename Scalar>
Eigen::Matrix<Scalar, 2, 1> DoubleSphereCameraCal<Scalar>::PixelFromCameraPoint(
    const Eigen::Matrix<Scalar, 3, 1>& point, const Scalar epsilon, Scalar* const is_valid) const {
  // Total ops: 74

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _self = Data();

  // Intermediate terms (13)
  const Scalar _tmp0 = std::pow(epsilon, Scalar(2)) + std::pow(point(0, 0), Scalar(2)) +
                       std::pow(point(1, 0), Scalar(2));
  const Scalar _tmp1 = std::sqrt(Scalar(_tmp0 + std::pow(point(2, 0), Scalar(2))));
  const Scalar _tmp2 = _self[4] * _tmp1 + point(2, 0);
  const Scalar _tmp3 =
      std::min<Scalar>(0, (((_self[5] + Scalar(-0.5)) > 0) - ((_self[5] + Scalar(-0.5)) < 0)));
  const Scalar _tmp4 = 2 * _tmp3;
  const Scalar _tmp5 = _self[5] - epsilon * (_tmp4 + 1);
  const Scalar _tmp6 = -_tmp5;
  const Scalar _tmp7 =
      Scalar(1.0) /
      (std::max<Scalar>(epsilon,
                        std::fabs(_tmp2 * (_tmp6 + 1) +
                                  _tmp5 * std::sqrt(Scalar(_tmp0 + std::pow(_tmp2, Scalar(2)))))));
  const Scalar _tmp8 = _tmp3 + _tmp5;
  const Scalar _tmp9 = (Scalar(1) / Scalar(2)) * _tmp4 + _tmp6 + 1;
  const Scalar _tmp10 = std::pow(_self[4], Scalar(2));
  const Scalar _tmp11 = std::pow(_tmp9, Scalar(2)) / std::pow(_tmp8, Scalar(2));
  const Scalar _tmp12 = _tmp10 * _tmp11 - _tmp10 + 1;

  // Output terms (2)
  Eigen::Matrix<Scalar, 2, 1> _pixel;

  _pixel(0, 0) = _self[0] * _tmp7 * point(0, 0) + _self[2];
  _pixel(1, 0) = _self[1] * _tmp7 * point(1, 0) + _self[3];

  if (is_valid != nullptr) {
    Scalar& _is_valid = (*is_valid);

    _is_valid = std::max<Scalar>(
        0, std::min<Scalar>(
               std::max<Scalar>(-(((_self[4] - 1) > 0) - ((_self[4] - 1) < 0)),
                                1 - std::max<Scalar>(0, -(((_self[4] * point(2, 0) + _tmp1) > 0) -
                                                          ((_self[4] * point(2, 0) + _tmp1) < 0)))),
               std::max<Scalar>(
                   -(((_tmp12) > 0) - ((_tmp12) < 0)),
                   1 - std::max<Scalar>(0, -(((-_tmp1 * (_self[4] * _tmp11 - _self[4] -
                                                         _tmp9 *
                                                             std::sqrt(Scalar(std::max<Scalar>(
                                                                 _tmp12, std::sqrt(epsilon)))) /
                                                             _tmp8) +
                                               point(2, 0)) > 0) -
                                             ((-_tmp1 * (_self[4] * _tmp11 - _self[4] -
                                                         _tmp9 *
                                                             std::sqrt(Scalar(std::max<Scalar>(
                                                                 _tmp12, std::sqrt(epsilon)))) /
                                                             _tmp8) +
                                               point(2, 0)) < 0))))));
  }

  return _pixel;
}

template <typename Scalar>
Eigen::Matrix<Scalar, 2, 1> DoubleSphereCameraCal<Scalar>::PixelFromCameraPointWithJacobians(
    const Eigen::Matrix<Scalar, 3, 1>& point, const Scalar epsilon, Scalar* const is_valid,
    Eigen::Matrix<Scalar, 2, 6>* const pixel_D_cal,
    Eigen::Matrix<Scalar, 2, 3>* const pixel_D_point) const {
  // Total ops: 137

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _self = Data();

  // Intermediate terms (41)
  const Scalar _tmp0 = std::pow(epsilon, Scalar(2)) + std::pow(point(0, 0), Scalar(2)) +
                       std::pow(point(1, 0), Scalar(2));
  const Scalar _tmp1 = std::sqrt(Scalar(_tmp0 + std::pow(point(2, 0), Scalar(2))));
  const Scalar _tmp2 = _self[4] * _tmp1 + point(2, 0);
  const Scalar _tmp3 = std::sqrt(Scalar(_tmp0 + std::pow(_tmp2, Scalar(2))));
  const Scalar _tmp4 =
      std::min<Scalar>(0, (((_self[5] + Scalar(-0.5)) > 0) - ((_self[5] + Scalar(-0.5)) < 0)));
  const Scalar _tmp5 = 2 * _tmp4;
  const Scalar _tmp6 = _self[5] - epsilon * (_tmp5 + 1);
  const Scalar _tmp7 = -_tmp6;
  const Scalar _tmp8 = _tmp7 + 1;
  const Scalar _tmp9 = _tmp2 * _tmp8 + _tmp3 * _tmp6;
  const Scalar _tmp10 = std::fabs(_tmp9);
  const Scalar _tmp11 = std::max<Scalar>(_tmp10, epsilon);
  const Scalar _tmp12 = Scalar(1.0) / (_tmp11);
  const Scalar _tmp13 = _self[0] * _tmp12;
  const Scalar _tmp14 = _self[1] * _tmp12;
  const Scalar _tmp15 = _self[4] * point(2, 0);
  const Scalar _tmp16 = _tmp4 + _tmp6;
  const Scalar _tmp17 = (Scalar(1) / Scalar(2)) * _tmp5 + _tmp7 + 1;
  const Scalar _tmp18 = std::pow(_self[4], Scalar(2));
  const Scalar _tmp19 = std::pow(_tmp17, Scalar(2)) / std::pow(_tmp16, Scalar(2));
  const Scalar _tmp20 = _tmp18 * _tmp19 - _tmp18 + 1;
  const Scalar _tmp21 = _tmp6 / _tmp3;
  const Scalar _tmp22 = _tmp2 * _tmp21;
  const Scalar _tmp23 = _tmp1 * _tmp22 + _tmp1 * _tmp8;
  const Scalar _tmp24 = (Scalar(1) / Scalar(2)) *
                        ((((_tmp10 - epsilon) > 0) - ((_tmp10 - epsilon) < 0)) + 1) *
                        (((_tmp9) > 0) - ((_tmp9) < 0)) / std::pow(_tmp11, Scalar(2));
  const Scalar _tmp25 = _self[0] * point(0, 0);
  const Scalar _tmp26 = _tmp24 * _tmp25;
  const Scalar _tmp27 = _self[1] * point(1, 0);
  const Scalar _tmp28 = _tmp24 * _tmp27;
  const Scalar _tmp29 = _tmp24 * (-_tmp2 + _tmp3);
  const Scalar _tmp30 = Scalar(1.0) / (_tmp1);
  const Scalar _tmp31 = _self[4] * _tmp30;
  const Scalar _tmp32 = _tmp31 * _tmp8;
  const Scalar _tmp33 = 2 * point(0, 0);
  const Scalar _tmp34 = _tmp2 * _tmp31;
  const Scalar _tmp35 = (Scalar(1) / Scalar(2)) * _tmp21;
  const Scalar _tmp36 = _tmp32 * point(0, 0) + _tmp35 * (_tmp33 * _tmp34 + _tmp33);
  const Scalar _tmp37 = 2 * point(1, 0);
  const Scalar _tmp38 = _tmp32 * point(1, 0) + _tmp35 * (_tmp34 * _tmp37 + _tmp37);
  const Scalar _tmp39 = _tmp15 * _tmp30 + 1;
  const Scalar _tmp40 = _tmp22 * _tmp39 + _tmp39 * _tmp8;

  // Output terms (4)
  Eigen::Matrix<Scalar, 2, 1> _pixel;

  _pixel(0, 0) = _self[2] + _tmp13 * point(0, 0);
  _pixel(1, 0) = _self[3] + _tmp14 * point(1, 0);

  if (is_valid != nullptr) {
    Scalar& _is_valid = (*is_valid);

    _is_valid = std::max<Scalar>(
        0, std::min<Scalar>(
               std::max<Scalar>(
                   -(((_self[4] - 1) > 0) - ((_self[4] - 1) < 0)),
                   1 - std::max<Scalar>(0, -(((_tmp1 + _tmp15) > 0) - ((_tmp1 + _tmp15) < 0)))),
               std::max<Scalar>(
                   -(((_tmp20) > 0) - ((_tmp20) < 0)),
                   1 - std::max<Scalar>(
                           0, -(((-_tmp1 *
                                      (_self[4] * _tmp19 - _self[4] -
                                       _tmp17 *
                                           std::sqrt(Scalar(
                                               std::max<Scalar>(_tmp20, std::sqrt(epsilon)))) /
                                           _tmp16) +
                                  point(2, 0)) > 0) -
                                ((-_tmp1 *
                                      (_self[4] * _tmp19 - _self[4] -
                                       _tmp17 *
                                           std::sqrt(Scalar(
                                               std::max<Scalar>(_tmp20, std::sqrt(epsilon)))) /
                                           _tmp16) +
                                  point(2, 0)) < 0))))));
  }

  if (pixel_D_cal != nullptr) {
    Eigen::Matrix<Scalar, 2, 6>& _pixel_D_cal = (*pixel_D_cal);

    _pixel_D_cal(0, 0) = _tmp12 * point(0, 0);
    _pixel_D_cal(1, 0) = 0;
    _pixel_D_cal(0, 1) = 0;
    _pixel_D_cal(1, 1) = _tmp12 * point(1, 0);
    _pixel_D_cal(0, 2) = 1;
    _pixel_D_cal(1, 2) = 0;
    _pixel_D_cal(0, 3) = 0;
    _pixel_D_cal(1, 3) = 1;
    _pixel_D_cal(0, 4) = -_tmp23 * _tmp26;
    _pixel_D_cal(1, 4) = -_tmp23 * _tmp28;
    _pixel_D_cal(0, 5) = -_tmp25 * _tmp29;
    _pixel_D_cal(1, 5) = -_tmp27 * _tmp29;
  }

  if (pixel_D_point != nullptr) {
    Eigen::Matrix<Scalar, 2, 3>& _pixel_D_point = (*pixel_D_point);

    _pixel_D_point(0, 0) = _tmp13 - _tmp26 * _tmp36;
    _pixel_D_point(1, 0) = -_tmp28 * _tmp36;
    _pixel_D_point(0, 1) = -_tmp26 * _tmp38;
    _pixel_D_point(1, 1) = _tmp14 - _tmp28 * _tmp38;
    _pixel_D_point(0, 2) = -_tmp26 * _tmp40;
    _pixel_D_point(1, 2) = -_tmp28 * _tmp40;
  }

  return _pixel;
}

template <typename Scalar>
Eigen::Matrix<Scalar, 3, 1> DoubleSphereCameraCal<Scalar>::CameraRayFromPixel(
    const Eigen::Matrix<Scalar, 2, 1>& pixel, const Scalar epsilon, Scalar* const is_valid) const {
  // Total ops: 62

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _self = Data();

  // Intermediate terms (12)
  const Scalar _tmp0 = -_self[2] + pixel(0, 0);
  const Scalar _tmp1 = -_self[3] + pixel(1, 0);
  const Scalar _tmp2 = std::pow(_tmp1, Scalar(2)) / std::pow(_self[1], Scalar(2)) +
                       std::pow(_tmp0, Scalar(2)) / std::pow(_self[0], Scalar(2));
  const Scalar _tmp3 = -std::pow(_self[5], Scalar(2)) * _tmp2 + 1;
  const Scalar _tmp4 = -_tmp2 * (2 * _self[5] - 1) + 1;
  const Scalar _tmp5 =
      _self[5] * std::sqrt(Scalar(std::max<Scalar>(_tmp4, epsilon))) - _self[5] + 1;
  const Scalar _tmp6 =
      _tmp5 + epsilon * (2 * std::min<Scalar>(0, (((_tmp5) > 0) - ((_tmp5) < 0))) + 1);
  const Scalar _tmp7 = std::pow(_tmp3, Scalar(2)) / std::pow(_tmp6, Scalar(2));
  const Scalar _tmp8 = _tmp2 + _tmp7;
  const Scalar _tmp9 = _tmp3 / _tmp6;
  const Scalar _tmp10 = _tmp2 * (1 - std::pow(_self[4], Scalar(2))) + _tmp7;
  const Scalar _tmp11 =
      (_self[4] * _tmp9 + std::sqrt(Scalar(std::max<Scalar>(_tmp10, epsilon)))) /
      (_tmp8 + epsilon * (2 * std::min<Scalar>(0, (((_tmp8) > 0) - ((_tmp8) < 0))) + 1));

  // Output terms (2)
  Eigen::Matrix<Scalar, 3, 1> _camera_ray;

  _camera_ray(0, 0) = _tmp0 * _tmp11 / _self[0];
  _camera_ray(1, 0) = _tmp1 * _tmp11 / _self[1];
  _camera_ray(2, 0) = -_self[4] + _tmp11 * _tmp9;

  if (is_valid != nullptr) {
    Scalar& _is_valid = (*is_valid);

    _is_valid = std::min<Scalar>(1 - std::max<Scalar>(0, -(((_tmp10) > 0) - ((_tmp10) < 0))),
                                 1 - std::max<Scalar>(0, -(((_tmp4) > 0) - ((_tmp4) < 0))));
  }

  return _camera_ray;
}

template <typename Scalar>
Eigen::Matrix<Scalar, 3, 1> DoubleSphereCameraCal<Scalar>::CameraRayFromPixelWithJacobians(
    const Eigen::Matrix<Scalar, 2, 1>& pixel, const Scalar epsilon, Scalar* const is_valid,
    Eigen::Matrix<Scalar, 3, 6>* const point_D_cal,
    Eigen::Matrix<Scalar, 3, 2>* const point_D_pixel) const {
  // Total ops: 297

  // Input arrays
  const Eigen::Matrix<Scalar, 6, 1>& _self = Data();

  // Intermediate terms (111)
  const Scalar _tmp0 = -_self[2] + pixel(0, 0);
  const Scalar _tmp1 = Scalar(1.0) / (_self[0]);
  const Scalar _tmp2 = -_self[3] + pixel(1, 0);
  const Scalar _tmp3 = std::pow(_tmp2, Scalar(2));
  const Scalar _tmp4 = std::pow(_self[1], Scalar(-2));
  const Scalar _tmp5 = std::pow(_tmp0, Scalar(2));
  const Scalar _tmp6 = std::pow(_self[0], Scalar(-2));
  const Scalar _tmp7 = _tmp3 * _tmp4 + _tmp5 * _tmp6;
  const Scalar _tmp8 = std::pow(_self[5], Scalar(2));
  const Scalar _tmp9 = -_tmp7 * _tmp8 + 1;
  const Scalar _tmp10 = std::pow(_tmp9, Scalar(2));
  const Scalar _tmp11 = 2 * _self[5];
  const Scalar _tmp12 = _tmp11 - 1;
  const Scalar _tmp13 = -_tmp12 * _tmp7 + 1;
  const Scalar _tmp14 = std::sqrt(Scalar(std::max<Scalar>(_tmp13, epsilon)));
  const Scalar _tmp15 = _self[5] * _tmp14 - _self[5] + 1;
  const Scalar _tmp16 =
      _tmp15 + epsilon * (2 * std::min<Scalar>(0, (((_tmp15) > 0) - ((_tmp15) < 0))) + 1);
  const Scalar _tmp17 = std::pow(_tmp16, Scalar(-2));
  const Scalar _tmp18 = _tmp10 * _tmp17;
  const Scalar _tmp19 = _tmp18 + _tmp7;
  const Scalar _tmp20 =
      _tmp19 + epsilon * (2 * std::min<Scalar>(0, (((_tmp19) > 0) - ((_tmp19) < 0))) + 1);
  const Scalar _tmp21 = Scalar(1.0) / (_tmp20);
  const Scalar _tmp22 = Scalar(1.0) / (_tmp16);
  const Scalar _tmp23 = _tmp22 * _tmp9;
  const Scalar _tmp24 = 1 - std::pow(_self[4], Scalar(2));
  const Scalar _tmp25 = _tmp18 + _tmp24 * _tmp7;
  const Scalar _tmp26 = std::sqrt(Scalar(std::max<Scalar>(_tmp25, epsilon)));
  const Scalar _tmp27 = _self[4] * _tmp23 + _tmp26;
  const Scalar _tmp28 = _tmp21 * _tmp27;
  const Scalar _tmp29 = _tmp1 * _tmp28;
  const Scalar _tmp30 = Scalar(1.0) / (_self[1]);
  const Scalar _tmp31 = _tmp28 * _tmp30;
  const Scalar _tmp32 = _tmp0 * _tmp6;
  const Scalar _tmp33 = _tmp28 * _tmp32;
  const Scalar _tmp34 = _tmp0 * _tmp1;
  const Scalar _tmp35 = _tmp5 / [&]() {
    const Scalar base = _self[0];
    return base * base * base;
  }();
  const Scalar _tmp36 = 2 * _tmp35;
  const Scalar _tmp37 = _tmp17 * _tmp9;
  const Scalar _tmp38 = 4 * _tmp37;
  const Scalar _tmp39 = _tmp38 * _tmp8;
  const Scalar _tmp40 = _tmp10 / [&]() {
    const Scalar base = _tmp16;
    return base * base * base;
  }();
  const Scalar _tmp41 = -epsilon;
  const Scalar _tmp42 =
      _self[5] * ((((_tmp13 + _tmp41) > 0) - ((_tmp13 + _tmp41) < 0)) + 1) / _tmp14;
  const Scalar _tmp43 = _tmp12 * _tmp42;
  const Scalar _tmp44 = _tmp40 * _tmp43;
  const Scalar _tmp45 = _tmp35 * _tmp39 - _tmp35 * _tmp44;
  const Scalar _tmp46 = _tmp27 / std::pow(_tmp20, Scalar(2));
  const Scalar _tmp47 = _tmp46 * (-_tmp36 + _tmp45);
  const Scalar _tmp48 = (Scalar(1) / Scalar(2)) * _tmp37 * _tmp43;
  const Scalar _tmp49 = _self[4] * _tmp48;
  const Scalar _tmp50 = _self[4] * _tmp22;
  const Scalar _tmp51 = _tmp50 * _tmp8;
  const Scalar _tmp52 = ((((_tmp25 + _tmp41) > 0) - ((_tmp25 + _tmp41) < 0)) + 1) / _tmp26;
  const Scalar _tmp53 = (Scalar(1) / Scalar(4)) * _tmp52;
  const Scalar _tmp54 = -_tmp35 * _tmp49 + _tmp36 * _tmp51 + _tmp53 * (-_tmp24 * _tmp36 + _tmp45);
  const Scalar _tmp55 = _tmp21 * _tmp54;
  const Scalar _tmp56 = _tmp2 * _tmp30;
  const Scalar _tmp57 = _tmp22 * _tmp28;
  const Scalar _tmp58 = _tmp57 * _tmp8;
  const Scalar _tmp59 = _tmp28 * _tmp48;
  const Scalar _tmp60 = _tmp21 * _tmp23;
  const Scalar _tmp61 = _tmp3 / [&]() {
    const Scalar base = _self[1];
    return base * base * base;
  }();
  const Scalar _tmp62 = 2 * _tmp61;
  const Scalar _tmp63 = _tmp39 * _tmp61 - _tmp44 * _tmp61;
  const Scalar _tmp64 = _tmp46 * (-_tmp62 + _tmp63);
  const Scalar _tmp65 = -_tmp49 * _tmp61 + _tmp51 * _tmp62 + _tmp53 * (-_tmp24 * _tmp62 + _tmp63);
  const Scalar _tmp66 = _tmp21 * _tmp65;
  const Scalar _tmp67 = _tmp2 * _tmp4;
  const Scalar _tmp68 = _tmp28 * _tmp67;
  const Scalar _tmp69 = _tmp32 * _tmp49;
  const Scalar _tmp70 = 2 * _tmp32;
  const Scalar _tmp71 = _tmp51 * _tmp70;
  const Scalar _tmp72 = _tmp24 * _tmp70;
  const Scalar _tmp73 = _tmp32 * _tmp39;
  const Scalar _tmp74 = _tmp32 * _tmp44;
  const Scalar _tmp75 = _tmp73 - _tmp74;
  const Scalar _tmp76 = _tmp53 * (-_tmp72 + _tmp75) - _tmp69 + _tmp71;
  const Scalar _tmp77 = _tmp21 * _tmp76;
  const Scalar _tmp78 = _tmp46 * (-_tmp70 + _tmp75);
  const Scalar _tmp79 = _tmp58 * _tmp70;
  const Scalar _tmp80 = _tmp33 * _tmp48;
  const Scalar _tmp81 = 2 * _tmp67;
  const Scalar _tmp82 = _tmp51 * _tmp81;
  const Scalar _tmp83 = _tmp49 * _tmp67;
  const Scalar _tmp84 = _tmp24 * _tmp81;
  const Scalar _tmp85 = _tmp39 * _tmp67;
  const Scalar _tmp86 = _tmp44 * _tmp67;
  const Scalar _tmp87 = _tmp85 - _tmp86;
  const Scalar _tmp88 = _tmp53 * (-_tmp84 + _tmp87) + _tmp82 - _tmp83;
  const Scalar _tmp89 = _tmp21 * _tmp88;
  const Scalar _tmp90 = _tmp46 * (-_tmp81 + _tmp87);
  const Scalar _tmp91 = _tmp48 * _tmp68;
  const Scalar _tmp92 = _tmp58 * _tmp81;
  const Scalar _tmp93 = (Scalar(1) / Scalar(2)) * _tmp7;
  const Scalar _tmp94 = -_self[4] * _tmp52 * _tmp93 + _tmp23;
  const Scalar _tmp95 = _tmp21 * _tmp94;
  const Scalar _tmp96 = _tmp14 - _tmp42 * _tmp93 - 1;
  const Scalar _tmp97 = -_self[5] * _tmp38 * _tmp7 - 2 * _tmp40 * _tmp96;
  const Scalar _tmp98 = _tmp46 * _tmp97;
  const Scalar _tmp99 = _tmp37 * _tmp96;
  const Scalar _tmp100 = _tmp11 * _tmp7;
  const Scalar _tmp101 = -_self[4] * _tmp99 - _tmp100 * _tmp50 + _tmp53 * _tmp97;
  const Scalar _tmp102 = _tmp101 * _tmp21;
  const Scalar _tmp103 = -_tmp73 + _tmp74;
  const Scalar _tmp104 = _tmp53 * (_tmp103 + _tmp72) + _tmp69 - _tmp71;
  const Scalar _tmp105 = _tmp104 * _tmp21;
  const Scalar _tmp106 = _tmp46 * (_tmp103 + _tmp70);
  const Scalar _tmp107 = -_tmp85 + _tmp86;
  const Scalar _tmp108 = _tmp53 * (_tmp107 + _tmp84) - _tmp82 + _tmp83;
  const Scalar _tmp109 = _tmp108 * _tmp21;
  const Scalar _tmp110 = _tmp46 * (_tmp107 + _tmp81);

  // Output terms (4)
  Eigen::Matrix<Scalar, 3, 1> _camera_ray;

  _camera_ray(0, 0) = _tmp0 * _tmp29;
  _camera_ray(1, 0) = _tmp2 * _tmp31;
  _camera_ray(2, 0) = -_self[4] + _tmp23 * _tmp28;

  if (is_valid != nullptr) {
    Scalar& _is_valid = (*is_valid);

    _is_valid = std::min<Scalar>(1 - std::max<Scalar>(0, -(((_tmp13) > 0) - ((_tmp13) < 0))),
                                 1 - std::max<Scalar>(0, -(((_tmp25) > 0) - ((_tmp25) < 0))));
  }

  if (point_D_cal != nullptr) {
    Eigen::Matrix<Scalar, 3, 6>& _point_D_cal = (*point_D_cal);

    _point_D_cal(0, 0) = -_tmp33 - _tmp34 * _tmp47 + _tmp34 * _tmp55;
    _point_D_cal(1, 0) = -_tmp47 * _tmp56 + _tmp55 * _tmp56;
    _point_D_cal(2, 0) = -_tmp23 * _tmp47 - _tmp35 * _tmp59 + _tmp36 * _tmp58 + _tmp54 * _tmp60;
    _point_D_cal(0, 1) = -_tmp34 * _tmp64 + _tmp34 * _tmp66;
    _point_D_cal(1, 1) = -_tmp56 * _tmp64 + _tmp56 * _tmp66 - _tmp68;
    _point_D_cal(2, 1) = -_tmp23 * _tmp64 + _tmp58 * _tmp62 - _tmp59 * _tmp61 + _tmp60 * _tmp65;
    _point_D_cal(0, 2) = -_tmp29 + _tmp34 * _tmp77 - _tmp34 * _tmp78;
    _point_D_cal(1, 2) = _tmp56 * _tmp77 - _tmp56 * _tmp78;
    _point_D_cal(2, 2) = -_tmp23 * _tmp78 + _tmp60 * _tmp76 + _tmp79 - _tmp80;
    _point_D_cal(0, 3) = _tmp34 * _tmp89 - _tmp34 * _tmp90;
    _point_D_cal(1, 3) = -_tmp31 + _tmp56 * _tmp89 - _tmp56 * _tmp90;
    _point_D_cal(2, 3) = -_tmp23 * _tmp90 + _tmp60 * _tmp88 - _tmp91 + _tmp92;
    _point_D_cal(0, 4) = _tmp34 * _tmp95;
    _point_D_cal(1, 4) = _tmp56 * _tmp95;
    _point_D_cal(2, 4) = _tmp60 * _tmp94 - 1;
    _point_D_cal(0, 5) = _tmp102 * _tmp34 - _tmp34 * _tmp98;
    _point_D_cal(1, 5) = _tmp102 * _tmp56 - _tmp56 * _tmp98;
    _point_D_cal(2, 5) = -_tmp100 * _tmp57 + _tmp101 * _tmp60 - _tmp23 * _tmp98 - _tmp28 * _tmp99;
  }

  if (point_D_pixel != nullptr) {
    Eigen::Matrix<Scalar, 3, 2>& _point_D_pixel = (*point_D_pixel);

    _point_D_pixel(0, 0) = _tmp105 * _tmp34 - _tmp106 * _tmp34 + _tmp29;
    _point_D_pixel(1, 0) = _tmp105 * _tmp56 - _tmp106 * _tmp56;
    _point_D_pixel(2, 0) = _tmp104 * _tmp60 - _tmp106 * _tmp23 - _tmp79 + _tmp80;
    _point_D_pixel(0, 1) = _tmp109 * _tmp34 - _tmp110 * _tmp34;
    _point_D_pixel(1, 1) = _tmp109 * _tmp56 - _tmp110 * _tmp56 + _tmp31;
    _point_D_pixel(2, 1) = _tmp108 * _tmp60 - _tmp110 * _tmp23 + _tmp91 - _tmp92;
  }

  return _camera_ray;
}

// Print implementations
std::ostream& operator<<(std::ostream& os, const DoubleSphereCameraCald& a) {
  const Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n", "[", "]");
  os << "<DoubleSphereCameraCald " << a.Data().transpose().format(fmt) << ">";
  return os;
}

std::ostream& operator<<(std::ostream& os, const DoubleSphereCameraCalf& a) {
  const Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n", "[", "]");
  os << "<DoubleSphereCameraCalf " << a.Data().transpose().format(fmt) << ">";
  return os;
}

}  // namespace sym

// Concept implementations for this class
#include "./ops/double_sphere_camera_cal/storage_ops.h"

// Explicit instantiation
template class sym::DoubleSphereCameraCal<double>;
template class sym::DoubleSphereCameraCal<float>;
