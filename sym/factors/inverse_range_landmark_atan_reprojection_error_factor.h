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
void InverseRangeLandmarkAtanReprojectionErrorFactor(
    const sym::Pose3<Scalar>& source_pose,
    const Eigen::Matrix<Scalar, 5, 1>& source_calibration_storage,
    const sym::Pose3<Scalar>& target_pose,
    const Eigen::Matrix<Scalar, 5, 1>& target_calibration_storage,
    const Scalar source_inverse_range, const Eigen::Matrix<Scalar, 2, 1>& source_pixel,
    const Eigen::Matrix<Scalar, 2, 1>& target_pixel, const Scalar weight, const Scalar gnc_mu,
    const Scalar gnc_scale, const Scalar epsilon, Eigen::Matrix<Scalar, 2, 1>* const res = nullptr,
    Eigen::Matrix<Scalar, 2, 13>* const jacobian = nullptr,
    Eigen::Matrix<Scalar, 13, 13>* const hessian = nullptr,
    Eigen::Matrix<Scalar, 13, 1>* const rhs = nullptr) {
  // Total ops: 1235

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _source_pose = source_pose.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _target_pose = target_pose.Data();

  // Intermediate terms (350)
  const Scalar _tmp0 = std::pow(_target_pose[1], Scalar(2));
  const Scalar _tmp1 = -2 * _tmp0;
  const Scalar _tmp2 = std::pow(_target_pose[2], Scalar(2));
  const Scalar _tmp3 = 1 - 2 * _tmp2;
  const Scalar _tmp4 = _tmp1 + _tmp3;
  const Scalar _tmp5 = std::pow(_source_pose[2], Scalar(2));
  const Scalar _tmp6 = -2 * _tmp5;
  const Scalar _tmp7 = std::pow(_source_pose[1], Scalar(2));
  const Scalar _tmp8 = -2 * _tmp7;
  const Scalar _tmp9 = _tmp6 + _tmp8 + 1;
  const Scalar _tmp10 = -source_calibration_storage(3, 0) + source_pixel(1, 0);
  const Scalar _tmp11 =
      std::pow(_tmp10, Scalar(2)) / std::pow(source_calibration_storage(1, 0), Scalar(2));
  const Scalar _tmp12 = Scalar(0.5) * source_calibration_storage(4, 0);
  const Scalar _tmp13 = std::tan(_tmp12);
  const Scalar _tmp14 = -source_calibration_storage(2, 0) + source_pixel(0, 0);
  const Scalar _tmp15 =
      std::pow(_tmp14, Scalar(2)) / std::pow(source_calibration_storage(0, 0), Scalar(2));
  const Scalar _tmp16 = _tmp11 + _tmp15 + epsilon;
  const Scalar _tmp17 = std::sqrt(_tmp16);
  const Scalar _tmp18 = _tmp17 * source_calibration_storage(4, 0);
  const Scalar _tmp19 = std::tan(_tmp18);
  const Scalar _tmp20 = (Scalar(1) / Scalar(4)) * std::pow(_tmp19, Scalar(2)) / _tmp16;
  const Scalar _tmp21 = _tmp20 / std::pow(_tmp13, Scalar(2));
  const Scalar _tmp22 =
      std::pow(Scalar(_tmp11 * _tmp21 + _tmp15 * _tmp21 + 1), Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp23 = (Scalar(1) / Scalar(2)) * _tmp19 / _tmp17;
  const Scalar _tmp24 = _tmp22 * _tmp23 / _tmp13;
  const Scalar _tmp25 = _tmp14 / source_calibration_storage(0, 0);
  const Scalar _tmp26 = _tmp24 * _tmp25;
  const Scalar _tmp27 = 2 * _source_pose[0];
  const Scalar _tmp28 = _source_pose[2] * _tmp27;
  const Scalar _tmp29 = 2 * _source_pose[1] * _source_pose[3];
  const Scalar _tmp30 = _tmp28 + _tmp29;
  const Scalar _tmp31 = _source_pose[1] * _tmp27;
  const Scalar _tmp32 = 2 * _source_pose[2];
  const Scalar _tmp33 = _source_pose[3] * _tmp32;
  const Scalar _tmp34 = -_tmp33;
  const Scalar _tmp35 = _tmp31 + _tmp34;
  const Scalar _tmp36 = _tmp10 / source_calibration_storage(1, 0);
  const Scalar _tmp37 = _tmp24 * _tmp36;
  const Scalar _tmp38 = _source_pose[4] - _target_pose[4];
  const Scalar _tmp39 = _tmp38 * source_inverse_range;
  const Scalar _tmp40 = _tmp22 * _tmp30 + _tmp26 * _tmp9 + _tmp35 * _tmp37 + _tmp39;
  const Scalar _tmp41 = 2 * _target_pose[3];
  const Scalar _tmp42 = _target_pose[2] * _tmp41;
  const Scalar _tmp43 = 2 * _target_pose[0] * _target_pose[1];
  const Scalar _tmp44 = _tmp42 + _tmp43;
  const Scalar _tmp45 = std::pow(_source_pose[0], Scalar(2));
  const Scalar _tmp46 = 1 - 2 * _tmp45;
  const Scalar _tmp47 = _tmp46 + _tmp6;
  const Scalar _tmp48 = _source_pose[3] * _tmp27;
  const Scalar _tmp49 = -_tmp48;
  const Scalar _tmp50 = _source_pose[1] * _tmp32;
  const Scalar _tmp51 = _tmp49 + _tmp50;
  const Scalar _tmp52 = _tmp31 + _tmp33;
  const Scalar _tmp53 = _source_pose[5] - _target_pose[5];
  const Scalar _tmp54 = _tmp53 * source_inverse_range;
  const Scalar _tmp55 = _tmp22 * _tmp51 + _tmp26 * _tmp52 + _tmp37 * _tmp47 + _tmp54;
  const Scalar _tmp56 = 2 * _target_pose[2];
  const Scalar _tmp57 = _target_pose[0] * _tmp56;
  const Scalar _tmp58 = _target_pose[1] * _tmp41;
  const Scalar _tmp59 = -_tmp58;
  const Scalar _tmp60 = _tmp57 + _tmp59;
  const Scalar _tmp61 = _tmp46 + _tmp8;
  const Scalar _tmp62 = _tmp48 + _tmp50;
  const Scalar _tmp63 = _tmp36 * _tmp62;
  const Scalar _tmp64 = -_tmp29;
  const Scalar _tmp65 = _tmp28 + _tmp64;
  const Scalar _tmp66 = _source_pose[6] - _target_pose[6];
  const Scalar _tmp67 = _tmp66 * source_inverse_range;
  const Scalar _tmp68 = _tmp22 * _tmp61 + _tmp24 * _tmp63 + _tmp26 * _tmp65 + _tmp67;
  const Scalar _tmp69 = _tmp4 * _tmp40 + _tmp44 * _tmp55 + _tmp60 * _tmp68;
  const Scalar _tmp70 = _tmp57 + _tmp58;
  const Scalar _tmp71 = _target_pose[1] * _tmp56;
  const Scalar _tmp72 = _target_pose[0] * _tmp41;
  const Scalar _tmp73 = -_tmp72;
  const Scalar _tmp74 = _tmp71 + _tmp73;
  const Scalar _tmp75 = std::pow(_target_pose[0], Scalar(2));
  const Scalar _tmp76 = -2 * _tmp75;
  const Scalar _tmp77 = _tmp1 + _tmp76 + 1;
  const Scalar _tmp78 = _tmp40 * _tmp70 + _tmp55 * _tmp74 + _tmp68 * _tmp77;
  const Scalar _tmp79 = std::max<Scalar>(epsilon, std::fabs(_tmp78));
  const Scalar _tmp80 = std::pow(_tmp79, Scalar(-2));
  const Scalar _tmp81 = -_tmp42;
  const Scalar _tmp82 = _tmp43 + _tmp81;
  const Scalar _tmp83 = _tmp3 + _tmp76;
  const Scalar _tmp84 = _tmp71 + _tmp72;
  const Scalar _tmp85 = _tmp40 * _tmp82 + _tmp55 * _tmp83 + _tmp68 * _tmp84;
  const Scalar _tmp86 = std::sqrt(Scalar(std::pow(_tmp69, Scalar(2)) * _tmp80 +
                                         _tmp80 * std::pow(_tmp85, Scalar(2)) + epsilon));
  const Scalar _tmp87 = Scalar(0.5) * target_calibration_storage(4, 0);
  const Scalar _tmp88 = std::atan(2 * _tmp86 * std::tan(_tmp87)) / (_tmp79 * _tmp86);
  const Scalar _tmp89 = Scalar(1.0) / (target_calibration_storage(4, 0));
  const Scalar _tmp90 = _tmp89 * target_calibration_storage(0, 0);
  const Scalar _tmp91 = target_calibration_storage(2, 0) - target_pixel(0, 0);
  const Scalar _tmp92 = _tmp69 * _tmp88 * _tmp90 + _tmp91;
  const Scalar _tmp93 = _tmp89 * target_calibration_storage(1, 0);
  const Scalar _tmp94 = target_calibration_storage(3, 0) - target_pixel(1, 0);
  const Scalar _tmp95 = _tmp85 * _tmp88 * _tmp93 + _tmp94;
  const Scalar _tmp96 = std::pow(_tmp92, Scalar(2)) + std::pow(_tmp95, Scalar(2)) + epsilon;
  const Scalar _tmp97 = Scalar(1.0) / (epsilon - gnc_mu + 1);
  const Scalar _tmp98 = epsilon + std::fabs(_tmp97);
  const Scalar _tmp99 = std::pow(gnc_scale, Scalar(-2));
  const Scalar _tmp100 = _tmp99 / _tmp98;
  const Scalar _tmp101 = 2 - _tmp97;
  const Scalar _tmp102 =
      _tmp101 + epsilon * (2 * std::min<Scalar>(0, (((_tmp101) > 0) - ((_tmp101) < 0))) + 1);
  const Scalar _tmp103 = (Scalar(1) / Scalar(2)) * _tmp102;
  const Scalar _tmp104 = 2 * _tmp98 / _tmp102;
  const Scalar _tmp105 =
      std::sqrt(weight) * std::max<Scalar>(0, (((-std::fabs(_tmp18) + Scalar(M_PI_2)) > 0) -
                                               ((-std::fabs(_tmp18) + Scalar(M_PI_2)) < 0)));
  const Scalar _tmp106 =
      _tmp105 * std::sqrt(Scalar(_tmp104 * (std::pow(Scalar(_tmp100 * _tmp96 + 1), _tmp103) - 1))) *
      std::max<Scalar>(0, (((_tmp78) > 0) - ((_tmp78) < 0))) / std::sqrt(_tmp96);
  const Scalar _tmp107 = _tmp106 * _tmp92;
  const Scalar _tmp108 = _tmp106 * _tmp95;
  const Scalar _tmp109 = std::pow(_source_pose[3], Scalar(2));
  const Scalar _tmp110 = -_tmp109;
  const Scalar _tmp111 = _tmp110 + _tmp5;
  const Scalar _tmp112 = -_tmp7;
  const Scalar _tmp113 = _tmp112 + _tmp45;
  const Scalar _tmp114 = std::tan(_tmp12);
  const Scalar _tmp115 = _tmp20 / std::pow(_tmp114, Scalar(2));
  const Scalar _tmp116 =
      std::pow(Scalar(_tmp11 * _tmp115 + _tmp115 * _tmp15 + 1), Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp117 = _tmp116 * _tmp51;
  const Scalar _tmp118 = _tmp23 / _tmp114;
  const Scalar _tmp119 = _tmp118 * _tmp36;
  const Scalar _tmp120 = _tmp116 * (_tmp111 + _tmp113) + _tmp117 * _tmp119;
  const Scalar _tmp121 = -_tmp50;
  const Scalar _tmp122 = -_tmp45;
  const Scalar _tmp123 = _tmp116 * _tmp119;
  const Scalar _tmp124 =
      _tmp116 * (_tmp121 + _tmp49) + _tmp123 * (_tmp109 + _tmp112 + _tmp122 + _tmp5);
  const Scalar _tmp125 = -_tmp31;
  const Scalar _tmp126 = _tmp116 * _tmp30;
  const Scalar _tmp127 = _tmp116 * (_tmp125 + _tmp33) + _tmp119 * _tmp126;
  const Scalar _tmp128 = _tmp120 * _tmp83 + _tmp124 * _tmp84 + _tmp127 * _tmp82;
  const Scalar _tmp129 = _tmp116 * _tmp52;
  const Scalar _tmp130 = _tmp118 * _tmp25;
  const Scalar _tmp131 = _tmp117 + _tmp123 * _tmp47 + _tmp129 * _tmp130 + _tmp54;
  const Scalar _tmp132 = _tmp116 * _tmp118;
  const Scalar _tmp133 = _tmp132 * _tmp25;
  const Scalar _tmp134 = _tmp123 * _tmp35 + _tmp126 + _tmp133 * _tmp9 + _tmp39;
  const Scalar _tmp135 = _tmp116 * _tmp65;
  const Scalar _tmp136 = _tmp116 * _tmp61 + _tmp130 * _tmp135 + _tmp132 * _tmp63 + _tmp67;
  const Scalar _tmp137 = _tmp134 * _tmp82 + _tmp136 * _tmp84;
  const Scalar _tmp138 = _tmp131 * _tmp83 + _tmp137;
  const Scalar _tmp139 = std::pow(_tmp138, Scalar(2));
  const Scalar _tmp140 = _tmp131 * _tmp74 + _tmp134 * _tmp70;
  const Scalar _tmp141 = _tmp136 * _tmp77 + _tmp140;
  const Scalar _tmp142 = std::fabs(_tmp141);
  const Scalar _tmp143 = std::max<Scalar>(_tmp142, epsilon);
  const Scalar _tmp144 = std::pow(_tmp143, Scalar(-2));
  const Scalar _tmp145 = _tmp131 * _tmp44 + _tmp136 * _tmp60;
  const Scalar _tmp146 = _tmp134 * _tmp4 + _tmp145;
  const Scalar _tmp147 = std::pow(_tmp146, Scalar(2));
  const Scalar _tmp148 = _tmp139 * _tmp144 + _tmp144 * _tmp147 + epsilon;
  const Scalar _tmp149 = std::sqrt(_tmp148);
  const Scalar _tmp150 = Scalar(1.0) / (_tmp149);
  const Scalar _tmp151 = Scalar(1.0) / (_tmp143);
  const Scalar _tmp152 = std::tan(_tmp87);
  const Scalar _tmp153 = std::atan(2 * _tmp149 * _tmp152);
  const Scalar _tmp154 = _tmp151 * _tmp153;
  const Scalar _tmp155 = _tmp150 * _tmp154;
  const Scalar _tmp156 = _tmp155 * _tmp93;
  const Scalar _tmp157 = _tmp120 * _tmp74 + _tmp124 * _tmp77 + _tmp127 * _tmp70;
  const Scalar _tmp158 = _tmp138 * _tmp93;
  const Scalar _tmp159 = (((_tmp141) > 0) - ((_tmp141) < 0));
  const Scalar _tmp160 = _tmp159 * ((((_tmp142 - epsilon) > 0) - ((_tmp142 - epsilon) < 0)) + 1);
  const Scalar _tmp161 = (Scalar(1) / Scalar(2)) * _tmp144 * _tmp150 * _tmp153 * _tmp160;
  const Scalar _tmp162 = _tmp158 * _tmp161;
  const Scalar _tmp163 = 2 * _tmp144;
  const Scalar _tmp164 = _tmp138 * _tmp163;
  const Scalar _tmp165 = _tmp160 / [&]() {
    const Scalar base = _tmp143;
    return base * base * base;
  }();
  const Scalar _tmp166 = _tmp147 * _tmp165;
  const Scalar _tmp167 = _tmp120 * _tmp44 + _tmp124 * _tmp60 + _tmp127 * _tmp4;
  const Scalar _tmp168 = _tmp146 * _tmp163;
  const Scalar _tmp169 = _tmp139 * _tmp165;
  const Scalar _tmp170 =
      _tmp128 * _tmp164 - _tmp157 * _tmp166 - _tmp157 * _tmp169 + _tmp167 * _tmp168;
  const Scalar _tmp171 = (Scalar(1) / Scalar(2)) * _tmp154 / (_tmp148 * std::sqrt(_tmp148));
  const Scalar _tmp172 = _tmp158 * _tmp171;
  const Scalar _tmp173 =
      _tmp151 * _tmp152 / (_tmp148 * (4 * _tmp148 * std::pow(_tmp152, Scalar(2)) + 1));
  const Scalar _tmp174 = _tmp158 * _tmp173;
  const Scalar _tmp175 =
      _tmp128 * _tmp156 - _tmp157 * _tmp162 - _tmp170 * _tmp172 + _tmp170 * _tmp174;
  const Scalar _tmp176 = _tmp138 * _tmp156 + _tmp94;
  const Scalar _tmp177 = 2 * _tmp176;
  const Scalar _tmp178 = _tmp146 * _tmp90;
  const Scalar _tmp179 = _tmp161 * _tmp178;
  const Scalar _tmp180 = _tmp155 * _tmp90;
  const Scalar _tmp181 = _tmp171 * _tmp178;
  const Scalar _tmp182 = _tmp173 * _tmp178;
  const Scalar _tmp183 =
      -_tmp157 * _tmp179 + _tmp167 * _tmp180 - _tmp170 * _tmp181 + _tmp170 * _tmp182;
  const Scalar _tmp184 = _tmp146 * _tmp180 + _tmp91;
  const Scalar _tmp185 = 2 * _tmp184;
  const Scalar _tmp186 = _tmp175 * _tmp177 + _tmp183 * _tmp185;
  const Scalar _tmp187 = std::max<Scalar>(0, _tmp159);
  const Scalar _tmp188 = std::pow(_tmp176, Scalar(2)) + std::pow(_tmp184, Scalar(2)) + epsilon;
  const Scalar _tmp189 = std::pow(_tmp188, Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp190 = _tmp100 * _tmp188 + 1;
  const Scalar _tmp191 = std::sqrt(Scalar(_tmp104 * (std::pow(_tmp190, _tmp103) - 1)));
  const Scalar _tmp192 =
      _tmp105 * _tmp187 * _tmp189 * std::pow(_tmp190, Scalar(_tmp103 - 1)) * _tmp99 / _tmp191;
  const Scalar _tmp193 = (Scalar(1) / Scalar(2)) * _tmp192;
  const Scalar _tmp194 = _tmp184 * _tmp193;
  const Scalar _tmp195 = _tmp105 * _tmp187 * _tmp191;
  const Scalar _tmp196 = _tmp189 * _tmp195;
  const Scalar _tmp197 = _tmp195 / (_tmp188 * std::sqrt(_tmp188));
  const Scalar _tmp198 = (Scalar(1) / Scalar(2)) * _tmp197;
  const Scalar _tmp199 = _tmp184 * _tmp198;
  const Scalar _tmp200 = _tmp183 * _tmp196 + _tmp186 * _tmp194 - _tmp186 * _tmp199;
  const Scalar _tmp201 = _tmp176 * _tmp193;
  const Scalar _tmp202 = _tmp176 * _tmp198;
  const Scalar _tmp203 = _tmp175 * _tmp196 + _tmp186 * _tmp201 - _tmp186 * _tmp202;
  const Scalar _tmp204 = -_tmp5;
  const Scalar _tmp205 = _tmp133 * (_tmp110 + _tmp204 + _tmp45 + _tmp7) + _tmp135;
  const Scalar _tmp206 = _tmp109 + _tmp204;
  const Scalar _tmp207 = -_tmp28;
  const Scalar _tmp208 = _tmp116 * (_tmp113 + _tmp206) + _tmp133 * (_tmp207 + _tmp64);
  const Scalar _tmp209 = _tmp129 + _tmp133 * (_tmp121 + _tmp48);
  const Scalar _tmp210 = _tmp205 * _tmp77 + _tmp208 * _tmp70 + _tmp209 * _tmp74;
  const Scalar _tmp211 = _tmp205 * _tmp60 + _tmp208 * _tmp4 + _tmp209 * _tmp44;
  const Scalar _tmp212 = _tmp205 * _tmp84 + _tmp208 * _tmp82 + _tmp209 * _tmp83;
  const Scalar _tmp213 =
      _tmp164 * _tmp212 - _tmp166 * _tmp210 + _tmp168 * _tmp211 - _tmp169 * _tmp210;
  const Scalar _tmp214 =
      -_tmp179 * _tmp210 + _tmp180 * _tmp211 - _tmp181 * _tmp213 + _tmp182 * _tmp213;
  const Scalar _tmp215 =
      _tmp156 * _tmp212 - _tmp162 * _tmp210 - _tmp172 * _tmp213 + _tmp174 * _tmp213;
  const Scalar _tmp216 =
      (Scalar(1) / Scalar(2)) * _tmp177 * _tmp215 + (Scalar(1) / Scalar(2)) * _tmp185 * _tmp214;
  const Scalar _tmp217 = _tmp184 * _tmp216;
  const Scalar _tmp218 = _tmp192 * _tmp217 + _tmp196 * _tmp214 - _tmp197 * _tmp217;
  const Scalar _tmp219 = _tmp176 * _tmp216;
  const Scalar _tmp220 = _tmp192 * _tmp219 + _tmp196 * _tmp215 - _tmp197 * _tmp219;
  const Scalar _tmp221 = _tmp123 * (_tmp207 + _tmp29) + _tmp133 * _tmp62;
  const Scalar _tmp222 = _tmp122 + _tmp7;
  const Scalar _tmp223 = _tmp123 * (_tmp111 + _tmp222) + _tmp133 * _tmp35;
  const Scalar _tmp224 = _tmp123 * (_tmp125 + _tmp34) + _tmp133 * (_tmp206 + _tmp222);
  const Scalar _tmp225 = _tmp221 * _tmp60 + _tmp223 * _tmp4 + _tmp224 * _tmp44;
  const Scalar _tmp226 = _tmp221 * _tmp77 + _tmp223 * _tmp70 + _tmp224 * _tmp74;
  const Scalar _tmp227 = _tmp221 * _tmp84 + _tmp223 * _tmp82 + _tmp224 * _tmp83;
  const Scalar _tmp228 =
      _tmp164 * _tmp227 - _tmp166 * _tmp226 + _tmp168 * _tmp225 - _tmp169 * _tmp226;
  const Scalar _tmp229 =
      -_tmp179 * _tmp226 + _tmp180 * _tmp225 - _tmp181 * _tmp228 + _tmp182 * _tmp228;
  const Scalar _tmp230 =
      _tmp156 * _tmp227 - _tmp162 * _tmp226 - _tmp172 * _tmp228 + _tmp174 * _tmp228;
  const Scalar _tmp231 = _tmp177 * _tmp230 + _tmp185 * _tmp229;
  const Scalar _tmp232 = _tmp194 * _tmp231 + _tmp196 * _tmp229 - _tmp199 * _tmp231;
  const Scalar _tmp233 = _tmp196 * _tmp230 + _tmp201 * _tmp231 - _tmp202 * _tmp231;
  const Scalar _tmp234 = _tmp162 * source_inverse_range;
  const Scalar _tmp235 = _tmp234 * _tmp70;
  const Scalar _tmp236 = _tmp168 * source_inverse_range;
  const Scalar _tmp237 = _tmp236 * _tmp4;
  const Scalar _tmp238 = _tmp166 * source_inverse_range;
  const Scalar _tmp239 = _tmp238 * _tmp70;
  const Scalar _tmp240 = _tmp164 * source_inverse_range;
  const Scalar _tmp241 = _tmp240 * _tmp82;
  const Scalar _tmp242 = _tmp169 * source_inverse_range;
  const Scalar _tmp243 = _tmp242 * _tmp70;
  const Scalar _tmp244 = _tmp237 - _tmp239 + _tmp241 - _tmp243;
  const Scalar _tmp245 = _tmp156 * source_inverse_range;
  const Scalar _tmp246 = _tmp245 * _tmp82;
  const Scalar _tmp247 = -_tmp172 * _tmp244 + _tmp174 * _tmp244 - _tmp235 + _tmp246;
  const Scalar _tmp248 = _tmp180 * source_inverse_range;
  const Scalar _tmp249 = _tmp248 * _tmp4;
  const Scalar _tmp250 = _tmp179 * source_inverse_range;
  const Scalar _tmp251 = _tmp250 * _tmp70;
  const Scalar _tmp252 = -_tmp181 * _tmp244 + _tmp182 * _tmp244 + _tmp249 - _tmp251;
  const Scalar _tmp253 = _tmp177 * _tmp247 + _tmp185 * _tmp252;
  const Scalar _tmp254 = _tmp194 * _tmp253 + _tmp196 * _tmp252 - _tmp199 * _tmp253;
  const Scalar _tmp255 = _tmp196 * _tmp247 + _tmp201 * _tmp253 - _tmp202 * _tmp253;
  const Scalar _tmp256 = _tmp74 * source_inverse_range;
  const Scalar _tmp257 = _tmp179 * _tmp256;
  const Scalar _tmp258 = _tmp169 * _tmp256;
  const Scalar _tmp259 = _tmp240 * _tmp83;
  const Scalar _tmp260 = _tmp236 * _tmp44;
  const Scalar _tmp261 = _tmp166 * _tmp256;
  const Scalar _tmp262 = -_tmp258 + _tmp259 + _tmp260 - _tmp261;
  const Scalar _tmp263 = _tmp248 * _tmp44;
  const Scalar _tmp264 = -_tmp181 * _tmp262 + _tmp182 * _tmp262 - _tmp257 + _tmp263;
  const Scalar _tmp265 = _tmp162 * _tmp256;
  const Scalar _tmp266 = _tmp245 * _tmp83;
  const Scalar _tmp267 = -_tmp172 * _tmp262 + _tmp174 * _tmp262 - _tmp265 + _tmp266;
  const Scalar _tmp268 = _tmp177 * _tmp267 + _tmp185 * _tmp264;
  const Scalar _tmp269 = _tmp194 * _tmp268 + _tmp196 * _tmp264 - _tmp199 * _tmp268;
  const Scalar _tmp270 = _tmp196 * _tmp267 + _tmp201 * _tmp268 - _tmp202 * _tmp268;
  const Scalar _tmp271 = _tmp248 * _tmp60;
  const Scalar _tmp272 = _tmp250 * _tmp77;
  const Scalar _tmp273 = _tmp236 * _tmp60;
  const Scalar _tmp274 = _tmp240 * _tmp84;
  const Scalar _tmp275 = _tmp242 * _tmp77;
  const Scalar _tmp276 = _tmp238 * _tmp77;
  const Scalar _tmp277 = _tmp273 + _tmp274 - _tmp275 - _tmp276;
  const Scalar _tmp278 = -_tmp181 * _tmp277 + _tmp182 * _tmp277 + _tmp271 - _tmp272;
  const Scalar _tmp279 = _tmp234 * _tmp77;
  const Scalar _tmp280 = _tmp245 * _tmp84;
  const Scalar _tmp281 = -_tmp172 * _tmp277 + _tmp174 * _tmp277 - _tmp279 + _tmp280;
  const Scalar _tmp282 = _tmp177 * _tmp281 + _tmp185 * _tmp278;
  const Scalar _tmp283 = _tmp194 * _tmp282 + _tmp196 * _tmp278 - _tmp199 * _tmp282;
  const Scalar _tmp284 = _tmp196 * _tmp281 + _tmp201 * _tmp282 - _tmp202 * _tmp282;
  const Scalar _tmp285 = -_tmp0;
  const Scalar _tmp286 = _tmp2 + _tmp285;
  const Scalar _tmp287 = -_tmp75;
  const Scalar _tmp288 = std::pow(_target_pose[3], Scalar(2));
  const Scalar _tmp289 = _tmp287 + _tmp288;
  const Scalar _tmp290 = _tmp136 * (_tmp286 + _tmp289) + _tmp140;
  const Scalar _tmp291 = -_tmp288;
  const Scalar _tmp292 = _tmp291 + _tmp75;
  const Scalar _tmp293 = -_tmp43;
  const Scalar _tmp294 = -_tmp71;
  const Scalar _tmp295 =
      _tmp131 * (_tmp286 + _tmp292) + _tmp134 * (_tmp293 + _tmp42) + _tmp136 * (_tmp294 + _tmp73);
  const Scalar _tmp296 = _tmp164 * _tmp290 - _tmp166 * _tmp295 - _tmp169 * _tmp295;
  const Scalar _tmp297 = -_tmp179 * _tmp295 - _tmp181 * _tmp296 + _tmp182 * _tmp296;
  const Scalar _tmp298 =
      _tmp156 * _tmp290 - _tmp162 * _tmp295 - _tmp172 * _tmp296 + _tmp174 * _tmp296;
  const Scalar _tmp299 = _tmp177 * _tmp298 + _tmp185 * _tmp297;
  const Scalar _tmp300 = _tmp194 * _tmp299 + _tmp196 * _tmp297 - _tmp199 * _tmp299;
  const Scalar _tmp301 = _tmp196 * _tmp298 + _tmp201 * _tmp299 - _tmp202 * _tmp299;
  const Scalar _tmp302 = -_tmp2;
  const Scalar _tmp303 = _tmp134 * (_tmp285 + _tmp288 + _tmp302 + _tmp75) + _tmp145;
  const Scalar _tmp304 = -_tmp57;
  const Scalar _tmp305 = _tmp0 + _tmp302;
  const Scalar _tmp306 =
      _tmp131 * (_tmp294 + _tmp72) + _tmp134 * (_tmp304 + _tmp59) + _tmp136 * (_tmp292 + _tmp305);
  const Scalar _tmp307 = -_tmp166 * _tmp303 + _tmp168 * _tmp306 - _tmp169 * _tmp303;
  const Scalar _tmp308 =
      -_tmp179 * _tmp303 + _tmp180 * _tmp306 - _tmp181 * _tmp307 + _tmp182 * _tmp307;
  const Scalar _tmp309 = -_tmp162 * _tmp303 - _tmp172 * _tmp307 + _tmp174 * _tmp307;
  const Scalar _tmp310 = _tmp177 * _tmp309 + _tmp185 * _tmp308;
  const Scalar _tmp311 = _tmp194 * _tmp310 + _tmp196 * _tmp308 - _tmp199 * _tmp310;
  const Scalar _tmp312 = _tmp196 * _tmp309 + _tmp201 * _tmp310 - _tmp202 * _tmp310;
  const Scalar _tmp313 = _tmp131 * (_tmp289 + _tmp305) + _tmp137;
  const Scalar _tmp314 = _tmp131 * (_tmp293 + _tmp81) +
                         _tmp134 * (_tmp0 + _tmp2 + _tmp287 + _tmp291) +
                         _tmp136 * (_tmp304 + _tmp58);
  const Scalar _tmp315 = _tmp164 * _tmp314 + _tmp168 * _tmp313;
  const Scalar _tmp316 = _tmp180 * _tmp313 - _tmp181 * _tmp315 + _tmp182 * _tmp315;
  const Scalar _tmp317 = _tmp158 * _tmp315;
  const Scalar _tmp318 = _tmp156 * _tmp314 - _tmp171 * _tmp317 + _tmp173 * _tmp317;
  const Scalar _tmp319 = _tmp177 * _tmp318 + _tmp185 * _tmp316;
  const Scalar _tmp320 = _tmp194 * _tmp319 + _tmp196 * _tmp316 - _tmp199 * _tmp319;
  const Scalar _tmp321 = _tmp196 * _tmp318 + _tmp201 * _tmp319 - _tmp202 * _tmp319;
  const Scalar _tmp322 = -_tmp237 + _tmp239 - _tmp241 + _tmp243;
  const Scalar _tmp323 = -_tmp172 * _tmp322 + _tmp174 * _tmp322 + _tmp235 - _tmp246;
  const Scalar _tmp324 = -_tmp181 * _tmp322 + _tmp182 * _tmp322 - _tmp249 + _tmp251;
  const Scalar _tmp325 = _tmp177 * _tmp323 + _tmp185 * _tmp324;
  const Scalar _tmp326 = _tmp194 * _tmp325 + _tmp196 * _tmp324 - _tmp199 * _tmp325;
  const Scalar _tmp327 = _tmp196 * _tmp323 + _tmp201 * _tmp325 - _tmp202 * _tmp325;
  const Scalar _tmp328 = _tmp258 - _tmp259 - _tmp260 + _tmp261;
  const Scalar _tmp329 = -_tmp172 * _tmp328 + _tmp174 * _tmp328 + _tmp265 - _tmp266;
  const Scalar _tmp330 = -_tmp181 * _tmp328 + _tmp182 * _tmp328 + _tmp257 - _tmp263;
  const Scalar _tmp331 = _tmp177 * _tmp329 + _tmp185 * _tmp330;
  const Scalar _tmp332 = _tmp194 * _tmp331 + _tmp196 * _tmp330 - _tmp199 * _tmp331;
  const Scalar _tmp333 = _tmp196 * _tmp329 + _tmp201 * _tmp331 - _tmp202 * _tmp331;
  const Scalar _tmp334 = -_tmp273 - _tmp274 + _tmp275 + _tmp276;
  const Scalar _tmp335 = -_tmp181 * _tmp334 + _tmp182 * _tmp334 - _tmp271 + _tmp272;
  const Scalar _tmp336 = -_tmp172 * _tmp334 + _tmp174 * _tmp334 + _tmp279 - _tmp280;
  const Scalar _tmp337 = _tmp177 * _tmp336 + _tmp185 * _tmp335;
  const Scalar _tmp338 = _tmp194 * _tmp337 + _tmp196 * _tmp335 - _tmp199 * _tmp337;
  const Scalar _tmp339 = _tmp196 * _tmp336 + _tmp201 * _tmp337 - _tmp202 * _tmp337;
  const Scalar _tmp340 = _tmp38 * _tmp70 + _tmp53 * _tmp74 + _tmp66 * _tmp77;
  const Scalar _tmp341 = _tmp38 * _tmp4 + _tmp44 * _tmp53 + _tmp60 * _tmp66;
  const Scalar _tmp342 = _tmp38 * _tmp82 + _tmp53 * _tmp83 + _tmp66 * _tmp84;
  const Scalar _tmp343 =
      _tmp164 * _tmp342 - _tmp166 * _tmp340 + _tmp168 * _tmp341 - _tmp169 * _tmp340;
  const Scalar _tmp344 = _tmp178 * _tmp343;
  const Scalar _tmp345 =
      -_tmp171 * _tmp344 + _tmp173 * _tmp344 - _tmp179 * _tmp340 + _tmp180 * _tmp341;
  const Scalar _tmp346 =
      _tmp156 * _tmp342 - _tmp162 * _tmp340 - _tmp172 * _tmp343 + _tmp174 * _tmp343;
  const Scalar _tmp347 = _tmp177 * _tmp346 + _tmp185 * _tmp345;
  const Scalar _tmp348 = _tmp194 * _tmp347 + _tmp196 * _tmp345 - _tmp199 * _tmp347;
  const Scalar _tmp349 = _tmp196 * _tmp346 + _tmp201 * _tmp347 - _tmp202 * _tmp347;

  // Output terms (4)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 2, 1>& _res = (*res);

    _res(0, 0) = _tmp107;
    _res(1, 0) = _tmp108;
  }

  if (jacobian != nullptr) {
    Eigen::Matrix<Scalar, 2, 13>& _jacobian = (*jacobian);

    _jacobian(0, 0) = _tmp200;
    _jacobian(1, 0) = _tmp203;
    _jacobian(0, 1) = _tmp218;
    _jacobian(1, 1) = _tmp220;
    _jacobian(0, 2) = _tmp232;
    _jacobian(1, 2) = _tmp233;
    _jacobian(0, 3) = _tmp254;
    _jacobian(1, 3) = _tmp255;
    _jacobian(0, 4) = _tmp269;
    _jacobian(1, 4) = _tmp270;
    _jacobian(0, 5) = _tmp283;
    _jacobian(1, 5) = _tmp284;
    _jacobian(0, 6) = _tmp300;
    _jacobian(1, 6) = _tmp301;
    _jacobian(0, 7) = _tmp311;
    _jacobian(1, 7) = _tmp312;
    _jacobian(0, 8) = _tmp320;
    _jacobian(1, 8) = _tmp321;
    _jacobian(0, 9) = _tmp326;
    _jacobian(1, 9) = _tmp327;
    _jacobian(0, 10) = _tmp332;
    _jacobian(1, 10) = _tmp333;
    _jacobian(0, 11) = _tmp338;
    _jacobian(1, 11) = _tmp339;
    _jacobian(0, 12) = _tmp348;
    _jacobian(1, 12) = _tmp349;
  }

  if (hessian != nullptr) {
    Eigen::Matrix<Scalar, 13, 13>& _hessian = (*hessian);

    _hessian(0, 0) = std::pow(_tmp200, Scalar(2)) + std::pow(_tmp203, Scalar(2));
    _hessian(1, 0) = _tmp200 * _tmp218 + _tmp203 * _tmp220;
    _hessian(2, 0) = _tmp200 * _tmp232 + _tmp203 * _tmp233;
    _hessian(3, 0) = _tmp200 * _tmp254 + _tmp203 * _tmp255;
    _hessian(4, 0) = _tmp200 * _tmp269 + _tmp203 * _tmp270;
    _hessian(5, 0) = _tmp200 * _tmp283 + _tmp203 * _tmp284;
    _hessian(6, 0) = _tmp200 * _tmp300 + _tmp203 * _tmp301;
    _hessian(7, 0) = _tmp200 * _tmp311 + _tmp203 * _tmp312;
    _hessian(8, 0) = _tmp200 * _tmp320 + _tmp203 * _tmp321;
    _hessian(9, 0) = _tmp200 * _tmp326 + _tmp203 * _tmp327;
    _hessian(10, 0) = _tmp200 * _tmp332 + _tmp203 * _tmp333;
    _hessian(11, 0) = _tmp200 * _tmp338 + _tmp203 * _tmp339;
    _hessian(12, 0) = _tmp200 * _tmp348 + _tmp203 * _tmp349;
    _hessian(0, 1) = 0;
    _hessian(1, 1) = std::pow(_tmp218, Scalar(2)) + std::pow(_tmp220, Scalar(2));
    _hessian(2, 1) = _tmp218 * _tmp232 + _tmp220 * _tmp233;
    _hessian(3, 1) = _tmp218 * _tmp254 + _tmp220 * _tmp255;
    _hessian(4, 1) = _tmp218 * _tmp269 + _tmp220 * _tmp270;
    _hessian(5, 1) = _tmp218 * _tmp283 + _tmp220 * _tmp284;
    _hessian(6, 1) = _tmp218 * _tmp300 + _tmp220 * _tmp301;
    _hessian(7, 1) = _tmp218 * _tmp311 + _tmp220 * _tmp312;
    _hessian(8, 1) = _tmp218 * _tmp320 + _tmp220 * _tmp321;
    _hessian(9, 1) = _tmp218 * _tmp326 + _tmp220 * _tmp327;
    _hessian(10, 1) = _tmp218 * _tmp332 + _tmp220 * _tmp333;
    _hessian(11, 1) = _tmp218 * _tmp338 + _tmp220 * _tmp339;
    _hessian(12, 1) = _tmp218 * _tmp348 + _tmp220 * _tmp349;
    _hessian(0, 2) = 0;
    _hessian(1, 2) = 0;
    _hessian(2, 2) = std::pow(_tmp232, Scalar(2)) + std::pow(_tmp233, Scalar(2));
    _hessian(3, 2) = _tmp232 * _tmp254 + _tmp233 * _tmp255;
    _hessian(4, 2) = _tmp232 * _tmp269 + _tmp233 * _tmp270;
    _hessian(5, 2) = _tmp232 * _tmp283 + _tmp233 * _tmp284;
    _hessian(6, 2) = _tmp232 * _tmp300 + _tmp233 * _tmp301;
    _hessian(7, 2) = _tmp232 * _tmp311 + _tmp233 * _tmp312;
    _hessian(8, 2) = _tmp232 * _tmp320 + _tmp233 * _tmp321;
    _hessian(9, 2) = _tmp232 * _tmp326 + _tmp233 * _tmp327;
    _hessian(10, 2) = _tmp232 * _tmp332 + _tmp233 * _tmp333;
    _hessian(11, 2) = _tmp232 * _tmp338 + _tmp233 * _tmp339;
    _hessian(12, 2) = _tmp232 * _tmp348 + _tmp233 * _tmp349;
    _hessian(0, 3) = 0;
    _hessian(1, 3) = 0;
    _hessian(2, 3) = 0;
    _hessian(3, 3) = std::pow(_tmp254, Scalar(2)) + std::pow(_tmp255, Scalar(2));
    _hessian(4, 3) = _tmp254 * _tmp269 + _tmp255 * _tmp270;
    _hessian(5, 3) = _tmp254 * _tmp283 + _tmp255 * _tmp284;
    _hessian(6, 3) = _tmp254 * _tmp300 + _tmp255 * _tmp301;
    _hessian(7, 3) = _tmp254 * _tmp311 + _tmp255 * _tmp312;
    _hessian(8, 3) = _tmp254 * _tmp320 + _tmp255 * _tmp321;
    _hessian(9, 3) = _tmp254 * _tmp326 + _tmp255 * _tmp327;
    _hessian(10, 3) = _tmp254 * _tmp332 + _tmp255 * _tmp333;
    _hessian(11, 3) = _tmp254 * _tmp338 + _tmp255 * _tmp339;
    _hessian(12, 3) = _tmp254 * _tmp348 + _tmp255 * _tmp349;
    _hessian(0, 4) = 0;
    _hessian(1, 4) = 0;
    _hessian(2, 4) = 0;
    _hessian(3, 4) = 0;
    _hessian(4, 4) = std::pow(_tmp269, Scalar(2)) + std::pow(_tmp270, Scalar(2));
    _hessian(5, 4) = _tmp269 * _tmp283 + _tmp270 * _tmp284;
    _hessian(6, 4) = _tmp269 * _tmp300 + _tmp270 * _tmp301;
    _hessian(7, 4) = _tmp269 * _tmp311 + _tmp270 * _tmp312;
    _hessian(8, 4) = _tmp269 * _tmp320 + _tmp270 * _tmp321;
    _hessian(9, 4) = _tmp269 * _tmp326 + _tmp270 * _tmp327;
    _hessian(10, 4) = _tmp269 * _tmp332 + _tmp270 * _tmp333;
    _hessian(11, 4) = _tmp269 * _tmp338 + _tmp270 * _tmp339;
    _hessian(12, 4) = _tmp269 * _tmp348 + _tmp270 * _tmp349;
    _hessian(0, 5) = 0;
    _hessian(1, 5) = 0;
    _hessian(2, 5) = 0;
    _hessian(3, 5) = 0;
    _hessian(4, 5) = 0;
    _hessian(5, 5) = std::pow(_tmp283, Scalar(2)) + std::pow(_tmp284, Scalar(2));
    _hessian(6, 5) = _tmp283 * _tmp300 + _tmp284 * _tmp301;
    _hessian(7, 5) = _tmp283 * _tmp311 + _tmp284 * _tmp312;
    _hessian(8, 5) = _tmp283 * _tmp320 + _tmp284 * _tmp321;
    _hessian(9, 5) = _tmp283 * _tmp326 + _tmp284 * _tmp327;
    _hessian(10, 5) = _tmp283 * _tmp332 + _tmp284 * _tmp333;
    _hessian(11, 5) = _tmp283 * _tmp338 + _tmp284 * _tmp339;
    _hessian(12, 5) = _tmp283 * _tmp348 + _tmp284 * _tmp349;
    _hessian(0, 6) = 0;
    _hessian(1, 6) = 0;
    _hessian(2, 6) = 0;
    _hessian(3, 6) = 0;
    _hessian(4, 6) = 0;
    _hessian(5, 6) = 0;
    _hessian(6, 6) = std::pow(_tmp300, Scalar(2)) + std::pow(_tmp301, Scalar(2));
    _hessian(7, 6) = _tmp300 * _tmp311 + _tmp301 * _tmp312;
    _hessian(8, 6) = _tmp300 * _tmp320 + _tmp301 * _tmp321;
    _hessian(9, 6) = _tmp300 * _tmp326 + _tmp301 * _tmp327;
    _hessian(10, 6) = _tmp300 * _tmp332 + _tmp301 * _tmp333;
    _hessian(11, 6) = _tmp300 * _tmp338 + _tmp301 * _tmp339;
    _hessian(12, 6) = _tmp300 * _tmp348 + _tmp301 * _tmp349;
    _hessian(0, 7) = 0;
    _hessian(1, 7) = 0;
    _hessian(2, 7) = 0;
    _hessian(3, 7) = 0;
    _hessian(4, 7) = 0;
    _hessian(5, 7) = 0;
    _hessian(6, 7) = 0;
    _hessian(7, 7) = std::pow(_tmp311, Scalar(2)) + std::pow(_tmp312, Scalar(2));
    _hessian(8, 7) = _tmp311 * _tmp320 + _tmp312 * _tmp321;
    _hessian(9, 7) = _tmp311 * _tmp326 + _tmp312 * _tmp327;
    _hessian(10, 7) = _tmp311 * _tmp332 + _tmp312 * _tmp333;
    _hessian(11, 7) = _tmp311 * _tmp338 + _tmp312 * _tmp339;
    _hessian(12, 7) = _tmp311 * _tmp348 + _tmp312 * _tmp349;
    _hessian(0, 8) = 0;
    _hessian(1, 8) = 0;
    _hessian(2, 8) = 0;
    _hessian(3, 8) = 0;
    _hessian(4, 8) = 0;
    _hessian(5, 8) = 0;
    _hessian(6, 8) = 0;
    _hessian(7, 8) = 0;
    _hessian(8, 8) = std::pow(_tmp320, Scalar(2)) + std::pow(_tmp321, Scalar(2));
    _hessian(9, 8) = _tmp320 * _tmp326 + _tmp321 * _tmp327;
    _hessian(10, 8) = _tmp320 * _tmp332 + _tmp321 * _tmp333;
    _hessian(11, 8) = _tmp320 * _tmp338 + _tmp321 * _tmp339;
    _hessian(12, 8) = _tmp320 * _tmp348 + _tmp321 * _tmp349;
    _hessian(0, 9) = 0;
    _hessian(1, 9) = 0;
    _hessian(2, 9) = 0;
    _hessian(3, 9) = 0;
    _hessian(4, 9) = 0;
    _hessian(5, 9) = 0;
    _hessian(6, 9) = 0;
    _hessian(7, 9) = 0;
    _hessian(8, 9) = 0;
    _hessian(9, 9) = std::pow(_tmp326, Scalar(2)) + std::pow(_tmp327, Scalar(2));
    _hessian(10, 9) = _tmp326 * _tmp332 + _tmp327 * _tmp333;
    _hessian(11, 9) = _tmp326 * _tmp338 + _tmp327 * _tmp339;
    _hessian(12, 9) = _tmp326 * _tmp348 + _tmp327 * _tmp349;
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
    _hessian(10, 10) = std::pow(_tmp332, Scalar(2)) + std::pow(_tmp333, Scalar(2));
    _hessian(11, 10) = _tmp332 * _tmp338 + _tmp333 * _tmp339;
    _hessian(12, 10) = _tmp332 * _tmp348 + _tmp333 * _tmp349;
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
    _hessian(11, 11) = std::pow(_tmp338, Scalar(2)) + std::pow(_tmp339, Scalar(2));
    _hessian(12, 11) = _tmp338 * _tmp348 + _tmp339 * _tmp349;
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
    _hessian(12, 12) = std::pow(_tmp348, Scalar(2)) + std::pow(_tmp349, Scalar(2));
  }

  if (rhs != nullptr) {
    Eigen::Matrix<Scalar, 13, 1>& _rhs = (*rhs);

    _rhs(0, 0) = _tmp107 * _tmp200 + _tmp108 * _tmp203;
    _rhs(1, 0) = _tmp107 * _tmp218 + _tmp108 * _tmp220;
    _rhs(2, 0) = _tmp107 * _tmp232 + _tmp108 * _tmp233;
    _rhs(3, 0) = _tmp107 * _tmp254 + _tmp108 * _tmp255;
    _rhs(4, 0) = _tmp107 * _tmp269 + _tmp108 * _tmp270;
    _rhs(5, 0) = _tmp107 * _tmp283 + _tmp108 * _tmp284;
    _rhs(6, 0) = _tmp107 * _tmp300 + _tmp108 * _tmp301;
    _rhs(7, 0) = _tmp107 * _tmp311 + _tmp108 * _tmp312;
    _rhs(8, 0) = _tmp107 * _tmp320 + _tmp108 * _tmp321;
    _rhs(9, 0) = _tmp107 * _tmp326 + _tmp108 * _tmp327;
    _rhs(10, 0) = _tmp107 * _tmp332 + _tmp108 * _tmp333;
    _rhs(11, 0) = _tmp107 * _tmp338 + _tmp108 * _tmp339;
    _rhs(12, 0) = _tmp107 * _tmp348 + _tmp108 * _tmp349;
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym