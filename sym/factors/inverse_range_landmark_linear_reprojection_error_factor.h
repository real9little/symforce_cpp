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
 * Return the 2dof residual of reprojecting the landmark into the target camera and comparing
 * against the correspondence in the target camera.
 *
 * The landmark is specified as a pixel in the source camera and an inverse range; this means the
 * landmark is fixed in the source camera and always has residual 0 there (this 0 residual is not
 * returned, only the residual in the target camera is returned).
 *
 * The norm of the residual is whitened using the Barron noise model.  Whitening each component of
 * the reprojection error separately would result in rejecting individual components as outliers.
 * Instead, we minimize the whitened norm of the full reprojection error for each point.  See the
 * docstring for `NoiseModel.whiten_norm` for more information on this, and the docstring of
 * `BarronNoiseModel` for more information on the noise model.
 *
 * Args:
 *     source_pose: The pose of the source camera
 *     source_calibration_storage: The storage vector of the source camera calibration
 *     target_pose: The pose of the target camera
 *     target_calibration_storage: The storage vector of the target camera calibration
 *     source_inverse_range: The inverse range of the landmark in the source camera
 *     source_pixel: The location of the landmark in the source camera
 *     target_pixel: The location of the correspondence in the target camera
 *     weight: The weight of the factor
 *     gnc_mu: The mu convexity parameter for the Barron noise model
 *     gnc_scale: The scale parameter for the Barron noise model
 *     epsilon: Small positive value
 *     camera_model_class: The subclass of CameraCal to use as the camera model
 *
 * Outputs:
 *     res: 2dof residual of the reprojection
 *     jacobian: (2x13) jacobian of res wrt args source_pose (6), target_pose (6),
 *               source_inverse_range (1)
 *     hessian: (13x13) Gauss-Newton hessian for args source_pose (6), target_pose (6),
 *              source_inverse_range (1)
 *     rhs: (13x1) Gauss-Newton rhs for args source_pose (6), target_pose (6), source_inverse_range
 *          (1)
 */
template <typename Scalar>
void InverseRangeLandmarkLinearReprojectionErrorFactor(
    const sym::Pose3<Scalar>& source_pose,
    const Eigen::Matrix<Scalar, 4, 1>& source_calibration_storage,
    const sym::Pose3<Scalar>& target_pose,
    const Eigen::Matrix<Scalar, 4, 1>& target_calibration_storage,
    const Scalar source_inverse_range, const Eigen::Matrix<Scalar, 2, 1>& source_pixel,
    const Eigen::Matrix<Scalar, 2, 1>& target_pixel, const Scalar weight, const Scalar gnc_mu,
    const Scalar gnc_scale, const Scalar epsilon, Eigen::Matrix<Scalar, 2, 1>* const res = nullptr,
    Eigen::Matrix<Scalar, 2, 13>* const jacobian = nullptr,
    Eigen::Matrix<Scalar, 13, 13>* const hessian = nullptr,
    Eigen::Matrix<Scalar, 13, 1>* const rhs = nullptr) {
  // Total ops: 909

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _source_pose = source_pose.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _target_pose = target_pose.Data();

  // Intermediate terms (230)
  const Scalar _tmp0 = std::pow(_target_pose[1], Scalar(2));
  const Scalar _tmp1 = -2 * _tmp0;
  const Scalar _tmp2 = std::pow(_target_pose[2], Scalar(2));
  const Scalar _tmp3 = -2 * _tmp2;
  const Scalar _tmp4 = _tmp1 + _tmp3 + 1;
  const Scalar _tmp5 = 2 * _source_pose[0];
  const Scalar _tmp6 = _source_pose[2] * _tmp5;
  const Scalar _tmp7 = 2 * _source_pose[3];
  const Scalar _tmp8 = _source_pose[1] * _tmp7;
  const Scalar _tmp9 = -source_calibration_storage(3, 0) + source_pixel(1, 0);
  const Scalar _tmp10 = -source_calibration_storage(2, 0) + source_pixel(0, 0);
  const Scalar _tmp11 = std::pow(
      Scalar(std::pow(_tmp10, Scalar(2)) / std::pow(source_calibration_storage(0, 0), Scalar(2)) +
             std::pow(_tmp9, Scalar(2)) / std::pow(source_calibration_storage(1, 0), Scalar(2)) +
             1),
      Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp12 = _tmp11 * (_tmp6 + _tmp8);
  const Scalar _tmp13 = _source_pose[1] * _tmp5;
  const Scalar _tmp14 = _source_pose[2] * _tmp7;
  const Scalar _tmp15 = -_tmp14;
  const Scalar _tmp16 = _tmp13 + _tmp15;
  const Scalar _tmp17 = _tmp9 / source_calibration_storage(1, 0);
  const Scalar _tmp18 = _tmp11 * _tmp17;
  const Scalar _tmp19 = std::pow(_source_pose[1], Scalar(2));
  const Scalar _tmp20 = -2 * _tmp19;
  const Scalar _tmp21 = std::pow(_source_pose[2], Scalar(2));
  const Scalar _tmp22 = 1 - 2 * _tmp21;
  const Scalar _tmp23 = _tmp10 / source_calibration_storage(0, 0);
  const Scalar _tmp24 = _tmp11 * _tmp23;
  const Scalar _tmp25 = _source_pose[4] - _target_pose[4];
  const Scalar _tmp26 =
      _tmp12 + _tmp16 * _tmp18 + _tmp24 * (_tmp20 + _tmp22) + _tmp25 * source_inverse_range;
  const Scalar _tmp27 = 2 * _target_pose[2];
  const Scalar _tmp28 = _target_pose[0] * _tmp27;
  const Scalar _tmp29 = 2 * _target_pose[3];
  const Scalar _tmp30 = _target_pose[1] * _tmp29;
  const Scalar _tmp31 = -_tmp30;
  const Scalar _tmp32 = _tmp28 + _tmp31;
  const Scalar _tmp33 = std::pow(_source_pose[0], Scalar(2));
  const Scalar _tmp34 = -2 * _tmp33;
  const Scalar _tmp35 = -_tmp8;
  const Scalar _tmp36 = _tmp11 * (_tmp35 + _tmp6);
  const Scalar _tmp37 = _source_pose[6] - _target_pose[6];
  const Scalar _tmp38 = _source_pose[3] * _tmp5;
  const Scalar _tmp39 = 2 * _source_pose[1] * _source_pose[2];
  const Scalar _tmp40 = _tmp38 + _tmp39;
  const Scalar _tmp41 = _tmp11 * (_tmp20 + _tmp34 + 1) + _tmp18 * _tmp40 + _tmp23 * _tmp36 +
                        _tmp37 * source_inverse_range;
  const Scalar _tmp42 = _target_pose[3] * _tmp27;
  const Scalar _tmp43 = 2 * _target_pose[0] * _target_pose[1];
  const Scalar _tmp44 = _tmp42 + _tmp43;
  const Scalar _tmp45 = -_tmp38;
  const Scalar _tmp46 = _tmp11 * (_tmp39 + _tmp45);
  const Scalar _tmp47 = _tmp11 * (_tmp13 + _tmp14);
  const Scalar _tmp48 = _source_pose[5] - _target_pose[5];
  const Scalar _tmp49 =
      _tmp18 * (_tmp22 + _tmp34) + _tmp23 * _tmp47 + _tmp46 + _tmp48 * source_inverse_range;
  const Scalar _tmp50 = _tmp32 * _tmp41 + _tmp44 * _tmp49;
  const Scalar _tmp51 = _tmp26 * _tmp4 + _tmp50;
  const Scalar _tmp52 = std::pow(_target_pose[0], Scalar(2));
  const Scalar _tmp53 = 1 - 2 * _tmp52;
  const Scalar _tmp54 = _tmp1 + _tmp53;
  const Scalar _tmp55 = _tmp28 + _tmp30;
  const Scalar _tmp56 = _target_pose[1] * _tmp27;
  const Scalar _tmp57 = _target_pose[0] * _tmp29;
  const Scalar _tmp58 = -_tmp57;
  const Scalar _tmp59 = _tmp56 + _tmp58;
  const Scalar _tmp60 = _tmp26 * _tmp55 + _tmp49 * _tmp59;
  const Scalar _tmp61 = _tmp41 * _tmp54 + _tmp60;
  const Scalar _tmp62 = std::fabs(_tmp61);
  const Scalar _tmp63 = std::max<Scalar>(_tmp62, epsilon);
  const Scalar _tmp64 = Scalar(1.0) / (_tmp63);
  const Scalar _tmp65 = _tmp64 * target_calibration_storage(0, 0);
  const Scalar _tmp66 = _tmp51 * _tmp65 + target_calibration_storage(2, 0) - target_pixel(0, 0);
  const Scalar _tmp67 = _tmp3 + _tmp53;
  const Scalar _tmp68 = _tmp56 + _tmp57;
  const Scalar _tmp69 = -_tmp42;
  const Scalar _tmp70 = _tmp43 + _tmp69;
  const Scalar _tmp71 = _tmp26 * _tmp70 + _tmp41 * _tmp68;
  const Scalar _tmp72 = _tmp49 * _tmp67 + _tmp71;
  const Scalar _tmp73 = _tmp64 * target_calibration_storage(1, 0);
  const Scalar _tmp74 = _tmp72 * _tmp73 + target_calibration_storage(3, 0) - target_pixel(1, 0);
  const Scalar _tmp75 = std::pow(_tmp66, Scalar(2)) + std::pow(_tmp74, Scalar(2)) + epsilon;
  const Scalar _tmp76 = std::pow(_tmp75, Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp77 = std::sqrt(weight);
  const Scalar _tmp78 = Scalar(1.0) / (epsilon - gnc_mu + 1);
  const Scalar _tmp79 = epsilon + std::fabs(_tmp78);
  const Scalar _tmp80 = 2 - _tmp78;
  const Scalar _tmp81 =
      _tmp80 + epsilon * (2 * std::min<Scalar>(0, (((_tmp80) > 0) - ((_tmp80) < 0))) + 1);
  const Scalar _tmp82 = std::pow(gnc_scale, Scalar(-2));
  const Scalar _tmp83 = _tmp75 * _tmp82 / _tmp79 + 1;
  const Scalar _tmp84 = (Scalar(1) / Scalar(2)) * _tmp81;
  const Scalar _tmp85 =
      std::sqrt(Scalar(2)) * std::sqrt(Scalar(_tmp79 * (std::pow(_tmp83, _tmp84) - 1) / _tmp81));
  const Scalar _tmp86 = (((_tmp61) > 0) - ((_tmp61) < 0));
  const Scalar _tmp87 = std::max<Scalar>(0, _tmp86);
  const Scalar _tmp88 = _tmp77 * _tmp85 * _tmp87;
  const Scalar _tmp89 = _tmp76 * _tmp88;
  const Scalar _tmp90 = _tmp66 * _tmp89;
  const Scalar _tmp91 = _tmp74 * _tmp89;
  const Scalar _tmp92 = _tmp51 * target_calibration_storage(0, 0);
  const Scalar _tmp93 = -_tmp39;
  const Scalar _tmp94 = std::pow(_source_pose[3], Scalar(2));
  const Scalar _tmp95 = -_tmp19;
  const Scalar _tmp96 = _tmp94 + _tmp95;
  const Scalar _tmp97 = -_tmp33;
  const Scalar _tmp98 = _tmp21 + _tmp97;
  const Scalar _tmp99 = _tmp11 * (_tmp45 + _tmp93) + _tmp18 * (_tmp96 + _tmp98);
  const Scalar _tmp100 = -_tmp94;
  const Scalar _tmp101 = _tmp11 * (_tmp100 + _tmp21 + _tmp33 + _tmp95) + _tmp17 * _tmp46;
  const Scalar _tmp102 = -_tmp13;
  const Scalar _tmp103 = _tmp11 * (_tmp102 + _tmp14) + _tmp12 * _tmp17;
  const Scalar _tmp104 = _tmp86 * ((((_tmp62 - epsilon) > 0) - ((_tmp62 - epsilon) < 0)) + 1) /
                         std::pow(_tmp63, Scalar(2));
  const Scalar _tmp105 = (Scalar(1) / Scalar(2)) * _tmp104;
  const Scalar _tmp106 = _tmp105 * (_tmp101 * _tmp59 + _tmp103 * _tmp55 + _tmp54 * _tmp99);
  const Scalar _tmp107 =
      -_tmp106 * _tmp92 + _tmp65 * (_tmp101 * _tmp44 + _tmp103 * _tmp4 + _tmp32 * _tmp99);
  const Scalar _tmp108 = 2 * _tmp66;
  const Scalar _tmp109 = _tmp72 * target_calibration_storage(1, 0);
  const Scalar _tmp110 =
      -_tmp106 * _tmp109 + _tmp73 * (_tmp101 * _tmp67 + _tmp103 * _tmp70 + _tmp68 * _tmp99);
  const Scalar _tmp111 = 2 * _tmp74;
  const Scalar _tmp112 = _tmp107 * _tmp108 + _tmp110 * _tmp111;
  const Scalar _tmp113 = (Scalar(1) / Scalar(2)) * _tmp66;
  const Scalar _tmp114 = _tmp88 / (_tmp75 * std::sqrt(_tmp75));
  const Scalar _tmp115 = _tmp113 * _tmp114;
  const Scalar _tmp116 =
      _tmp76 * _tmp77 * _tmp82 * std::pow(_tmp83, Scalar(_tmp84 - 1)) * _tmp87 / _tmp85;
  const Scalar _tmp117 = _tmp113 * _tmp116;
  const Scalar _tmp118 = _tmp107 * _tmp89 - _tmp112 * _tmp115 + _tmp112 * _tmp117;
  const Scalar _tmp119 = (Scalar(1) / Scalar(2)) * _tmp74;
  const Scalar _tmp120 = _tmp116 * _tmp119;
  const Scalar _tmp121 = _tmp114 * _tmp119;
  const Scalar _tmp122 = _tmp110 * _tmp89 + _tmp112 * _tmp120 - _tmp112 * _tmp121;
  const Scalar _tmp123 = -_tmp21;
  const Scalar _tmp124 = _tmp123 + _tmp33;
  const Scalar _tmp125 = _tmp100 + _tmp19;
  const Scalar _tmp126 = _tmp24 * (_tmp124 + _tmp125) + _tmp36;
  const Scalar _tmp127 = _tmp24 * (_tmp38 + _tmp93) + _tmp47;
  const Scalar _tmp128 = -_tmp6;
  const Scalar _tmp129 = _tmp11 * (_tmp124 + _tmp96) + _tmp24 * (_tmp128 + _tmp35);
  const Scalar _tmp130 = _tmp126 * _tmp54 + _tmp127 * _tmp59 + _tmp129 * _tmp55;
  const Scalar _tmp131 = _tmp105 * _tmp92;
  const Scalar _tmp132 =
      -_tmp130 * _tmp131 + _tmp65 * (_tmp126 * _tmp32 + _tmp127 * _tmp44 + _tmp129 * _tmp4);
  const Scalar _tmp133 = _tmp105 * _tmp109;
  const Scalar _tmp134 =
      -_tmp130 * _tmp133 + _tmp73 * (_tmp126 * _tmp68 + _tmp127 * _tmp67 + _tmp129 * _tmp70);
  const Scalar _tmp135 = _tmp108 * _tmp132 + _tmp111 * _tmp134;
  const Scalar _tmp136 = -_tmp115 * _tmp135 + _tmp117 * _tmp135 + _tmp132 * _tmp89;
  const Scalar _tmp137 = _tmp120 * _tmp135 - _tmp121 * _tmp135 + _tmp134 * _tmp89;
  const Scalar _tmp138 =
      _tmp18 * (_tmp102 + _tmp15) + _tmp24 * (_tmp123 + _tmp19 + _tmp94 + _tmp97);
  const Scalar _tmp139 = _tmp18 * (_tmp128 + _tmp8) + _tmp24 * _tmp40;
  const Scalar _tmp140 = _tmp16 * _tmp24 + _tmp18 * (_tmp125 + _tmp98);
  const Scalar _tmp141 = _tmp105 * (_tmp138 * _tmp59 + _tmp139 * _tmp54 + _tmp140 * _tmp55);
  const Scalar _tmp142 =
      -_tmp109 * _tmp141 + _tmp73 * (_tmp138 * _tmp67 + _tmp139 * _tmp68 + _tmp140 * _tmp70);
  const Scalar _tmp143 =
      -_tmp141 * _tmp92 + _tmp65 * (_tmp138 * _tmp44 + _tmp139 * _tmp32 + _tmp140 * _tmp4);
  const Scalar _tmp144 = _tmp108 * _tmp143 + _tmp111 * _tmp142;
  const Scalar _tmp145 = -_tmp115 * _tmp144 + _tmp117 * _tmp144 + _tmp143 * _tmp89;
  const Scalar _tmp146 = _tmp120 * _tmp144 - _tmp121 * _tmp144 + _tmp142 * _tmp89;
  const Scalar _tmp147 = _tmp55 * source_inverse_range;
  const Scalar _tmp148 = _tmp133 * _tmp147;
  const Scalar _tmp149 = _tmp73 * source_inverse_range;
  const Scalar _tmp150 = _tmp149 * _tmp70;
  const Scalar _tmp151 = -_tmp148 + _tmp150;
  const Scalar _tmp152 = _tmp65 * source_inverse_range;
  const Scalar _tmp153 = _tmp152 * _tmp4;
  const Scalar _tmp154 = _tmp131 * _tmp147;
  const Scalar _tmp155 = _tmp153 - _tmp154;
  const Scalar _tmp156 = _tmp108 * _tmp155 + _tmp111 * _tmp151;
  const Scalar _tmp157 = _tmp113 * _tmp156;
  const Scalar _tmp158 = -_tmp114 * _tmp157 + _tmp116 * _tmp157 + _tmp155 * _tmp89;
  const Scalar _tmp159 = _tmp120 * _tmp156 - _tmp121 * _tmp156 + _tmp151 * _tmp89;
  const Scalar _tmp160 = _tmp59 * source_inverse_range;
  const Scalar _tmp161 = _tmp131 * _tmp160;
  const Scalar _tmp162 = _tmp152 * _tmp44;
  const Scalar _tmp163 = -_tmp161 + _tmp162;
  const Scalar _tmp164 = _tmp133 * _tmp160;
  const Scalar _tmp165 = _tmp149 * _tmp67;
  const Scalar _tmp166 = -_tmp164 + _tmp165;
  const Scalar _tmp167 = _tmp108 * _tmp163 + _tmp111 * _tmp166;
  const Scalar _tmp168 = _tmp114 * _tmp167;
  const Scalar _tmp169 = -_tmp113 * _tmp168 + _tmp117 * _tmp167 + _tmp163 * _tmp89;
  const Scalar _tmp170 = -_tmp119 * _tmp168 + _tmp120 * _tmp167 + _tmp166 * _tmp89;
  const Scalar _tmp171 = _tmp54 * source_inverse_range;
  const Scalar _tmp172 = _tmp133 * _tmp171;
  const Scalar _tmp173 = _tmp149 * _tmp68;
  const Scalar _tmp174 = -_tmp172 + _tmp173;
  const Scalar _tmp175 = _tmp131 * _tmp171;
  const Scalar _tmp176 = _tmp152 * _tmp32;
  const Scalar _tmp177 = -_tmp175 + _tmp176;
  const Scalar _tmp178 = _tmp108 * _tmp177 + _tmp111 * _tmp174;
  const Scalar _tmp179 = -_tmp115 * _tmp178 + _tmp117 * _tmp178 + _tmp177 * _tmp89;
  const Scalar _tmp180 = _tmp120 * _tmp178 - _tmp121 * _tmp178 + _tmp174 * _tmp89;
  const Scalar _tmp181 = -_tmp56;
  const Scalar _tmp182 = -_tmp43;
  const Scalar _tmp183 = std::pow(_target_pose[3], Scalar(2));
  const Scalar _tmp184 = -_tmp183;
  const Scalar _tmp185 = _tmp184 + _tmp52;
  const Scalar _tmp186 = -_tmp0;
  const Scalar _tmp187 = _tmp186 + _tmp2;
  const Scalar _tmp188 =
      _tmp26 * (_tmp182 + _tmp42) + _tmp41 * (_tmp181 + _tmp58) + _tmp49 * (_tmp185 + _tmp187);
  const Scalar _tmp189 = -_tmp52;
  const Scalar _tmp190 = _tmp183 + _tmp189;
  const Scalar _tmp191 = -_tmp133 * _tmp188 + _tmp73 * (_tmp41 * (_tmp187 + _tmp190) + _tmp60);
  const Scalar _tmp192 = -_tmp104 * _tmp188 * _tmp66 * _tmp92 + _tmp111 * _tmp191;
  const Scalar _tmp193 = -_tmp115 * _tmp192 + _tmp117 * _tmp192 - _tmp131 * _tmp188 * _tmp89;
  const Scalar _tmp194 = _tmp120 * _tmp192 - _tmp121 * _tmp192 + _tmp191 * _tmp89;
  const Scalar _tmp195 = -_tmp2;
  const Scalar _tmp196 = _tmp26 * (_tmp183 + _tmp186 + _tmp195 + _tmp52) + _tmp50;
  const Scalar _tmp197 = _tmp109 * _tmp196;
  const Scalar _tmp198 = _tmp0 + _tmp195;
  const Scalar _tmp199 = -_tmp28;
  const Scalar _tmp200 =
      -_tmp131 * _tmp196 + _tmp65 * (_tmp26 * (_tmp199 + _tmp31) + _tmp41 * (_tmp185 + _tmp198) +
                                     _tmp49 * (_tmp181 + _tmp57));
  const Scalar _tmp201 = -_tmp104 * _tmp197 * _tmp74 + _tmp108 * _tmp200;
  const Scalar _tmp202 = -_tmp115 * _tmp201 + _tmp117 * _tmp201 + _tmp200 * _tmp89;
  const Scalar _tmp203 = -_tmp105 * _tmp197 * _tmp89 + _tmp120 * _tmp201 - _tmp121 * _tmp201;
  const Scalar _tmp204 = _tmp65 * (_tmp49 * (_tmp190 + _tmp198) + _tmp71);
  const Scalar _tmp205 = _tmp73 * (_tmp26 * (_tmp0 + _tmp184 + _tmp189 + _tmp2) +
                                   _tmp41 * (_tmp199 + _tmp30) + _tmp49 * (_tmp182 + _tmp69));
  const Scalar _tmp206 = _tmp108 * _tmp204 + _tmp111 * _tmp205;
  const Scalar _tmp207 = -_tmp115 * _tmp206 + _tmp117 * _tmp206 + _tmp204 * _tmp89;
  const Scalar _tmp208 = _tmp120 * _tmp206 - _tmp121 * _tmp206 + _tmp205 * _tmp89;
  const Scalar _tmp209 = _tmp148 - _tmp150;
  const Scalar _tmp210 = -_tmp153 + _tmp154;
  const Scalar _tmp211 = _tmp108 * _tmp210 + _tmp111 * _tmp209;
  const Scalar _tmp212 = -_tmp115 * _tmp211 + _tmp117 * _tmp211 + _tmp210 * _tmp89;
  const Scalar _tmp213 = _tmp120 * _tmp211 - _tmp121 * _tmp211 + _tmp209 * _tmp89;
  const Scalar _tmp214 = _tmp161 - _tmp162;
  const Scalar _tmp215 = _tmp164 - _tmp165;
  const Scalar _tmp216 = _tmp108 * _tmp214 + _tmp111 * _tmp215;
  const Scalar _tmp217 = -_tmp115 * _tmp216 + _tmp117 * _tmp216 + _tmp214 * _tmp89;
  const Scalar _tmp218 = _tmp120 * _tmp216 - _tmp121 * _tmp216 + _tmp215 * _tmp89;
  const Scalar _tmp219 = _tmp172 - _tmp173;
  const Scalar _tmp220 = _tmp175 - _tmp176;
  const Scalar _tmp221 = _tmp108 * _tmp220 + _tmp111 * _tmp219;
  const Scalar _tmp222 = -_tmp115 * _tmp221 + _tmp117 * _tmp221 + _tmp220 * _tmp89;
  const Scalar _tmp223 = _tmp120 * _tmp221 - _tmp121 * _tmp221 + _tmp219 * _tmp89;
  const Scalar _tmp224 = _tmp105 * (_tmp25 * _tmp55 + _tmp37 * _tmp54 + _tmp48 * _tmp59);
  const Scalar _tmp225 =
      -_tmp109 * _tmp224 + _tmp73 * (_tmp25 * _tmp70 + _tmp37 * _tmp68 + _tmp48 * _tmp67);
  const Scalar _tmp226 =
      -_tmp224 * _tmp92 + _tmp65 * (_tmp25 * _tmp4 + _tmp32 * _tmp37 + _tmp44 * _tmp48);
  const Scalar _tmp227 = _tmp108 * _tmp226 + _tmp111 * _tmp225;
  const Scalar _tmp228 = -_tmp115 * _tmp227 + _tmp117 * _tmp227 + _tmp226 * _tmp89;
  const Scalar _tmp229 = _tmp120 * _tmp227 - _tmp121 * _tmp227 + _tmp225 * _tmp89;

  // Output terms (4)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 2, 1>& _res = (*res);

    _res(0, 0) = _tmp90;
    _res(1, 0) = _tmp91;
  }

  if (jacobian != nullptr) {
    Eigen::Matrix<Scalar, 2, 13>& _jacobian = (*jacobian);

    _jacobian(0, 0) = _tmp118;
    _jacobian(1, 0) = _tmp122;
    _jacobian(0, 1) = _tmp136;
    _jacobian(1, 1) = _tmp137;
    _jacobian(0, 2) = _tmp145;
    _jacobian(1, 2) = _tmp146;
    _jacobian(0, 3) = _tmp158;
    _jacobian(1, 3) = _tmp159;
    _jacobian(0, 4) = _tmp169;
    _jacobian(1, 4) = _tmp170;
    _jacobian(0, 5) = _tmp179;
    _jacobian(1, 5) = _tmp180;
    _jacobian(0, 6) = _tmp193;
    _jacobian(1, 6) = _tmp194;
    _jacobian(0, 7) = _tmp202;
    _jacobian(1, 7) = _tmp203;
    _jacobian(0, 8) = _tmp207;
    _jacobian(1, 8) = _tmp208;
    _jacobian(0, 9) = _tmp212;
    _jacobian(1, 9) = _tmp213;
    _jacobian(0, 10) = _tmp217;
    _jacobian(1, 10) = _tmp218;
    _jacobian(0, 11) = _tmp222;
    _jacobian(1, 11) = _tmp223;
    _jacobian(0, 12) = _tmp228;
    _jacobian(1, 12) = _tmp229;
  }

  if (hessian != nullptr) {
    Eigen::Matrix<Scalar, 13, 13>& _hessian = (*hessian);

    _hessian(0, 0) = std::pow(_tmp118, Scalar(2)) + std::pow(_tmp122, Scalar(2));
    _hessian(1, 0) = _tmp118 * _tmp136 + _tmp122 * _tmp137;
    _hessian(2, 0) = _tmp118 * _tmp145 + _tmp122 * _tmp146;
    _hessian(3, 0) = _tmp118 * _tmp158 + _tmp122 * _tmp159;
    _hessian(4, 0) = _tmp118 * _tmp169 + _tmp122 * _tmp170;
    _hessian(5, 0) = _tmp118 * _tmp179 + _tmp122 * _tmp180;
    _hessian(6, 0) = _tmp118 * _tmp193 + _tmp122 * _tmp194;
    _hessian(7, 0) = _tmp118 * _tmp202 + _tmp122 * _tmp203;
    _hessian(8, 0) = _tmp118 * _tmp207 + _tmp122 * _tmp208;
    _hessian(9, 0) = _tmp118 * _tmp212 + _tmp122 * _tmp213;
    _hessian(10, 0) = _tmp118 * _tmp217 + _tmp122 * _tmp218;
    _hessian(11, 0) = _tmp118 * _tmp222 + _tmp122 * _tmp223;
    _hessian(12, 0) = _tmp118 * _tmp228 + _tmp122 * _tmp229;
    _hessian(0, 1) = 0;
    _hessian(1, 1) = std::pow(_tmp136, Scalar(2)) + std::pow(_tmp137, Scalar(2));
    _hessian(2, 1) = _tmp136 * _tmp145 + _tmp137 * _tmp146;
    _hessian(3, 1) = _tmp136 * _tmp158 + _tmp137 * _tmp159;
    _hessian(4, 1) = _tmp136 * _tmp169 + _tmp137 * _tmp170;
    _hessian(5, 1) = _tmp136 * _tmp179 + _tmp137 * _tmp180;
    _hessian(6, 1) = _tmp136 * _tmp193 + _tmp137 * _tmp194;
    _hessian(7, 1) = _tmp136 * _tmp202 + _tmp137 * _tmp203;
    _hessian(8, 1) = _tmp136 * _tmp207 + _tmp137 * _tmp208;
    _hessian(9, 1) = _tmp136 * _tmp212 + _tmp137 * _tmp213;
    _hessian(10, 1) = _tmp136 * _tmp217 + _tmp137 * _tmp218;
    _hessian(11, 1) = _tmp136 * _tmp222 + _tmp137 * _tmp223;
    _hessian(12, 1) = _tmp136 * _tmp228 + _tmp137 * _tmp229;
    _hessian(0, 2) = 0;
    _hessian(1, 2) = 0;
    _hessian(2, 2) = std::pow(_tmp145, Scalar(2)) + std::pow(_tmp146, Scalar(2));
    _hessian(3, 2) = _tmp145 * _tmp158 + _tmp146 * _tmp159;
    _hessian(4, 2) = _tmp145 * _tmp169 + _tmp146 * _tmp170;
    _hessian(5, 2) = _tmp145 * _tmp179 + _tmp146 * _tmp180;
    _hessian(6, 2) = _tmp145 * _tmp193 + _tmp146 * _tmp194;
    _hessian(7, 2) = _tmp145 * _tmp202 + _tmp146 * _tmp203;
    _hessian(8, 2) = _tmp145 * _tmp207 + _tmp146 * _tmp208;
    _hessian(9, 2) = _tmp145 * _tmp212 + _tmp146 * _tmp213;
    _hessian(10, 2) = _tmp145 * _tmp217 + _tmp146 * _tmp218;
    _hessian(11, 2) = _tmp145 * _tmp222 + _tmp146 * _tmp223;
    _hessian(12, 2) = _tmp145 * _tmp228 + _tmp146 * _tmp229;
    _hessian(0, 3) = 0;
    _hessian(1, 3) = 0;
    _hessian(2, 3) = 0;
    _hessian(3, 3) = std::pow(_tmp158, Scalar(2)) + std::pow(_tmp159, Scalar(2));
    _hessian(4, 3) = _tmp158 * _tmp169 + _tmp159 * _tmp170;
    _hessian(5, 3) = _tmp158 * _tmp179 + _tmp159 * _tmp180;
    _hessian(6, 3) = _tmp158 * _tmp193 + _tmp159 * _tmp194;
    _hessian(7, 3) = _tmp158 * _tmp202 + _tmp159 * _tmp203;
    _hessian(8, 3) = _tmp158 * _tmp207 + _tmp159 * _tmp208;
    _hessian(9, 3) = _tmp158 * _tmp212 + _tmp159 * _tmp213;
    _hessian(10, 3) = _tmp158 * _tmp217 + _tmp159 * _tmp218;
    _hessian(11, 3) = _tmp158 * _tmp222 + _tmp159 * _tmp223;
    _hessian(12, 3) = _tmp158 * _tmp228 + _tmp159 * _tmp229;
    _hessian(0, 4) = 0;
    _hessian(1, 4) = 0;
    _hessian(2, 4) = 0;
    _hessian(3, 4) = 0;
    _hessian(4, 4) = std::pow(_tmp169, Scalar(2)) + std::pow(_tmp170, Scalar(2));
    _hessian(5, 4) = _tmp169 * _tmp179 + _tmp170 * _tmp180;
    _hessian(6, 4) = _tmp169 * _tmp193 + _tmp170 * _tmp194;
    _hessian(7, 4) = _tmp169 * _tmp202 + _tmp170 * _tmp203;
    _hessian(8, 4) = _tmp169 * _tmp207 + _tmp170 * _tmp208;
    _hessian(9, 4) = _tmp169 * _tmp212 + _tmp170 * _tmp213;
    _hessian(10, 4) = _tmp169 * _tmp217 + _tmp170 * _tmp218;
    _hessian(11, 4) = _tmp169 * _tmp222 + _tmp170 * _tmp223;
    _hessian(12, 4) = _tmp169 * _tmp228 + _tmp170 * _tmp229;
    _hessian(0, 5) = 0;
    _hessian(1, 5) = 0;
    _hessian(2, 5) = 0;
    _hessian(3, 5) = 0;
    _hessian(4, 5) = 0;
    _hessian(5, 5) = std::pow(_tmp179, Scalar(2)) + std::pow(_tmp180, Scalar(2));
    _hessian(6, 5) = _tmp179 * _tmp193 + _tmp180 * _tmp194;
    _hessian(7, 5) = _tmp179 * _tmp202 + _tmp180 * _tmp203;
    _hessian(8, 5) = _tmp179 * _tmp207 + _tmp180 * _tmp208;
    _hessian(9, 5) = _tmp179 * _tmp212 + _tmp180 * _tmp213;
    _hessian(10, 5) = _tmp179 * _tmp217 + _tmp180 * _tmp218;
    _hessian(11, 5) = _tmp179 * _tmp222 + _tmp180 * _tmp223;
    _hessian(12, 5) = _tmp179 * _tmp228 + _tmp180 * _tmp229;
    _hessian(0, 6) = 0;
    _hessian(1, 6) = 0;
    _hessian(2, 6) = 0;
    _hessian(3, 6) = 0;
    _hessian(4, 6) = 0;
    _hessian(5, 6) = 0;
    _hessian(6, 6) = std::pow(_tmp193, Scalar(2)) + std::pow(_tmp194, Scalar(2));
    _hessian(7, 6) = _tmp193 * _tmp202 + _tmp194 * _tmp203;
    _hessian(8, 6) = _tmp193 * _tmp207 + _tmp194 * _tmp208;
    _hessian(9, 6) = _tmp193 * _tmp212 + _tmp194 * _tmp213;
    _hessian(10, 6) = _tmp193 * _tmp217 + _tmp194 * _tmp218;
    _hessian(11, 6) = _tmp193 * _tmp222 + _tmp194 * _tmp223;
    _hessian(12, 6) = _tmp193 * _tmp228 + _tmp194 * _tmp229;
    _hessian(0, 7) = 0;
    _hessian(1, 7) = 0;
    _hessian(2, 7) = 0;
    _hessian(3, 7) = 0;
    _hessian(4, 7) = 0;
    _hessian(5, 7) = 0;
    _hessian(6, 7) = 0;
    _hessian(7, 7) = std::pow(_tmp202, Scalar(2)) + std::pow(_tmp203, Scalar(2));
    _hessian(8, 7) = _tmp202 * _tmp207 + _tmp203 * _tmp208;
    _hessian(9, 7) = _tmp202 * _tmp212 + _tmp203 * _tmp213;
    _hessian(10, 7) = _tmp202 * _tmp217 + _tmp203 * _tmp218;
    _hessian(11, 7) = _tmp202 * _tmp222 + _tmp203 * _tmp223;
    _hessian(12, 7) = _tmp202 * _tmp228 + _tmp203 * _tmp229;
    _hessian(0, 8) = 0;
    _hessian(1, 8) = 0;
    _hessian(2, 8) = 0;
    _hessian(3, 8) = 0;
    _hessian(4, 8) = 0;
    _hessian(5, 8) = 0;
    _hessian(6, 8) = 0;
    _hessian(7, 8) = 0;
    _hessian(8, 8) = std::pow(_tmp207, Scalar(2)) + std::pow(_tmp208, Scalar(2));
    _hessian(9, 8) = _tmp207 * _tmp212 + _tmp208 * _tmp213;
    _hessian(10, 8) = _tmp207 * _tmp217 + _tmp208 * _tmp218;
    _hessian(11, 8) = _tmp207 * _tmp222 + _tmp208 * _tmp223;
    _hessian(12, 8) = _tmp207 * _tmp228 + _tmp208 * _tmp229;
    _hessian(0, 9) = 0;
    _hessian(1, 9) = 0;
    _hessian(2, 9) = 0;
    _hessian(3, 9) = 0;
    _hessian(4, 9) = 0;
    _hessian(5, 9) = 0;
    _hessian(6, 9) = 0;
    _hessian(7, 9) = 0;
    _hessian(8, 9) = 0;
    _hessian(9, 9) = std::pow(_tmp212, Scalar(2)) + std::pow(_tmp213, Scalar(2));
    _hessian(10, 9) = _tmp212 * _tmp217 + _tmp213 * _tmp218;
    _hessian(11, 9) = _tmp212 * _tmp222 + _tmp213 * _tmp223;
    _hessian(12, 9) = _tmp212 * _tmp228 + _tmp213 * _tmp229;
    _hessian(0, 10) = 0;
    _hessian(1, 10) = 0;
    _hessian(2, 10) = 0;
    _hessian(3, 10) = 0;
    _hessian(4, 10) = 0;
    _hessian(5, 10) = 0;
    _hessian(6, 10) = 0;
    _hessian(7, 10) = 0;
    _hessian(8, 10) = 0;
    _hessian(9, 10) = 0;
    _hessian(10, 10) = std::pow(_tmp217, Scalar(2)) + std::pow(_tmp218, Scalar(2));
    _hessian(11, 10) = _tmp217 * _tmp222 + _tmp218 * _tmp223;
    _hessian(12, 10) = _tmp217 * _tmp228 + _tmp218 * _tmp229;
    _hessian(0, 11) = 0;
    _hessian(1, 11) = 0;
    _hessian(2, 11) = 0;
    _hessian(3, 11) = 0;
    _hessian(4, 11) = 0;
    _hessian(5, 11) = 0;
    _hessian(6, 11) = 0;
    _hessian(7, 11) = 0;
    _hessian(8, 11) = 0;
    _hessian(9, 11) = 0;
    _hessian(10, 11) = 0;
    _hessian(11, 11) = std::pow(_tmp222, Scalar(2)) + std::pow(_tmp223, Scalar(2));
    _hessian(12, 11) = _tmp222 * _tmp228 + _tmp223 * _tmp229;
    _hessian(0, 12) = 0;
    _hessian(1, 12) = 0;
    _hessian(2, 12) = 0;
    _hessian(3, 12) = 0;
    _hessian(4, 12) = 0;
    _hessian(5, 12) = 0;
    _hessian(6, 12) = 0;
    _hessian(7, 12) = 0;
    _hessian(8, 12) = 0;
    _hessian(9, 12) = 0;
    _hessian(10, 12) = 0;
    _hessian(11, 12) = 0;
    _hessian(12, 12) = std::pow(_tmp228, Scalar(2)) + std::pow(_tmp229, Scalar(2));
  }

  if (rhs != nullptr) {
    Eigen::Matrix<Scalar, 13, 1>& _rhs = (*rhs);

    _rhs(0, 0) = _tmp118 * _tmp90 + _tmp122 * _tmp91;
    _rhs(1, 0) = _tmp136 * _tmp90 + _tmp137 * _tmp91;
    _rhs(2, 0) = _tmp145 * _tmp90 + _tmp146 * _tmp91;
    _rhs(3, 0) = _tmp158 * _tmp90 + _tmp159 * _tmp91;
    _rhs(4, 0) = _tmp169 * _tmp90 + _tmp170 * _tmp91;
    _rhs(5, 0) = _tmp179 * _tmp90 + _tmp180 * _tmp91;
    _rhs(6, 0) = _tmp193 * _tmp90 + _tmp194 * _tmp91;
    _rhs(7, 0) = _tmp202 * _tmp90 + _tmp203 * _tmp91;
    _rhs(8, 0) = _tmp207 * _tmp90 + _tmp208 * _tmp91;
    _rhs(9, 0) = _tmp212 * _tmp90 + _tmp213 * _tmp91;
    _rhs(10, 0) = _tmp217 * _tmp90 + _tmp218 * _tmp91;
    _rhs(11, 0) = _tmp222 * _tmp90 + _tmp223 * _tmp91;
    _rhs(12, 0) = _tmp228 * _tmp90 + _tmp229 * _tmp91;
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
