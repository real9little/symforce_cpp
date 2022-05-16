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
 * Return the 2dof residual of reprojecting the landmark ray into the target spherical camera and
 * comparing it against the correspondence.
 *
 * The landmark is specified as a camera point in the source camera with an inverse range; this
 * means the landmark is fixed in the source camera and always has residual 0 there (this 0 residual
 * is not returned, only the residual in the target camera is returned).
 *
 * The norm of the residual is whitened using the Barron noise model.  Whitening each component of
 * the reprojection error separately would result in rejecting individual components as outliers.
 * Instead, we minimize the whitened norm of the full reprojection error for each point.  See the
 * docstring for `NoiseModel.whiten_norm` for more information on this, and the docstring of
 * `BarronNoiseModel` for more information on the noise model.
 *
 * Args:
 *     source_pose: The pose of the source camera
 *     target_pose: The pose of the target camera
 *     target_calibration_storage: The storage vector of the target spherical camera calibration
 *     source_inverse_range: The inverse range of the landmark in the source camera
 *     p_camera_source: The location of the landmark in the source camera coordinate, will be
 * normalized target_pixel: The location of the correspondence in the target camera weight: The
 * weight of the factor gnc_mu: The mu convexity parameter for the Barron noise model gnc_scale: The
 * scale parameter for the Barron noise model epsilon: Small positive value
 *     target_camera_model_class: The subclass of CameraCal to use as the target camera model
 *
 * Outputs:
 *     res: 2dof whiten residual of the reprojection
 *     jacobian: (2x13) jacobian of res wrt args source_pose (6), target_pose (6),
 *               source_inverse_range (1)
 *     hessian: (13x13) Gauss-Newton hessian for args source_pose (6), target_pose (6),
 *              source_inverse_range (1)
 *     rhs: (13x1) Gauss-Newton rhs for args source_pose (6), target_pose (6), source_inverse_range
 *          (1)
 */
template <typename Scalar>
void InverseRangeLandmarkSphericalReprojectionErrorFactor(
    const sym::Pose3<Scalar>& source_pose, const sym::Pose3<Scalar>& target_pose,
    const Eigen::Matrix<Scalar, 9, 1>& target_calibration_storage,
    const Scalar source_inverse_range, const Eigen::Matrix<Scalar, 3, 1>& p_camera_source,
    const Eigen::Matrix<Scalar, 2, 1>& target_pixel, const Scalar weight, const Scalar gnc_mu,
    const Scalar gnc_scale, const Scalar epsilon, Eigen::Matrix<Scalar, 2, 1>* const res = nullptr,
    Eigen::Matrix<Scalar, 2, 13>* const jacobian = nullptr,
    Eigen::Matrix<Scalar, 13, 13>* const hessian = nullptr,
    Eigen::Matrix<Scalar, 13, 1>* const rhs = nullptr) {
  // Total ops: 1221

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _source_pose = source_pose.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _target_pose = target_pose.Data();

  // Intermediate terms (317)
  const Scalar _tmp0 = std::pow(_target_pose[2], Scalar(2));
  const Scalar _tmp1 = -2 * _tmp0;
  const Scalar _tmp2 = std::pow(_target_pose[1], Scalar(2));
  const Scalar _tmp3 = 1 - 2 * _tmp2;
  const Scalar _tmp4 = _tmp1 + _tmp3;
  const Scalar _tmp5 = 2 * _source_pose[1];
  const Scalar _tmp6 = _source_pose[0] * _tmp5;
  const Scalar _tmp7 = 2 * _source_pose[2];
  const Scalar _tmp8 = _source_pose[3] * _tmp7;
  const Scalar _tmp9 = -_tmp8;
  const Scalar _tmp10 = _tmp6 + _tmp9;
  const Scalar _tmp11 = std::pow(Scalar(epsilon + std::pow(p_camera_source(0, 0), Scalar(2)) +
                                        std::pow(p_camera_source(1, 0), Scalar(2)) +
                                        std::pow(p_camera_source(2, 0), Scalar(2))),
                                 Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp12 = _tmp11 * p_camera_source(1, 0);
  const Scalar _tmp13 = _source_pose[0] * _tmp7;
  const Scalar _tmp14 = _source_pose[3] * _tmp5;
  const Scalar _tmp15 = _tmp13 + _tmp14;
  const Scalar _tmp16 = _tmp11 * p_camera_source(2, 0);
  const Scalar _tmp17 = std::pow(_source_pose[2], Scalar(2));
  const Scalar _tmp18 = -2 * _tmp17;
  const Scalar _tmp19 = std::pow(_source_pose[1], Scalar(2));
  const Scalar _tmp20 = 1 - 2 * _tmp19;
  const Scalar _tmp21 = _tmp11 * p_camera_source(0, 0);
  const Scalar _tmp22 = _source_pose[4] - _target_pose[4];
  const Scalar _tmp23 = _tmp10 * _tmp12 + _tmp15 * _tmp16 + _tmp21 * (_tmp18 + _tmp20) +
                        _tmp22 * source_inverse_range;
  const Scalar _tmp24 = 2 * _target_pose[2];
  const Scalar _tmp25 = _target_pose[0] * _tmp24;
  const Scalar _tmp26 = 2 * _target_pose[1];
  const Scalar _tmp27 = _target_pose[3] * _tmp26;
  const Scalar _tmp28 = -_tmp27;
  const Scalar _tmp29 = _tmp25 + _tmp28;
  const Scalar _tmp30 = 2 * _source_pose[0] * _source_pose[3];
  const Scalar _tmp31 = _source_pose[1] * _tmp7;
  const Scalar _tmp32 = _tmp30 + _tmp31;
  const Scalar _tmp33 = -_tmp14;
  const Scalar _tmp34 = _tmp13 + _tmp33;
  const Scalar _tmp35 = std::pow(_source_pose[0], Scalar(2));
  const Scalar _tmp36 = -2 * _tmp35;
  const Scalar _tmp37 = _source_pose[6] - _target_pose[6];
  const Scalar _tmp38 = _tmp12 * _tmp32 + _tmp16 * (_tmp20 + _tmp36) + _tmp21 * _tmp34 +
                        _tmp37 * source_inverse_range;
  const Scalar _tmp39 = _target_pose[3] * _tmp24;
  const Scalar _tmp40 = _target_pose[0] * _tmp26;
  const Scalar _tmp41 = _tmp39 + _tmp40;
  const Scalar _tmp42 = _tmp6 + _tmp8;
  const Scalar _tmp43 = -_tmp30;
  const Scalar _tmp44 = _tmp31 + _tmp43;
  const Scalar _tmp45 = _source_pose[5] - _target_pose[5];
  const Scalar _tmp46 = _tmp12 * (_tmp18 + _tmp36 + 1) + _tmp16 * _tmp44 + _tmp21 * _tmp42 +
                        _tmp45 * source_inverse_range;
  const Scalar _tmp47 = _tmp29 * _tmp38 + _tmp41 * _tmp46;
  const Scalar _tmp48 = _tmp23 * _tmp4 + _tmp47;
  const Scalar _tmp49 = std::pow(_tmp48, Scalar(2));
  const Scalar _tmp50 = std::pow(_target_pose[0], Scalar(2));
  const Scalar _tmp51 = -2 * _tmp50;
  const Scalar _tmp52 = _tmp1 + _tmp51 + 1;
  const Scalar _tmp53 = _target_pose[2] * _tmp26;
  const Scalar _tmp54 = 2 * _target_pose[0] * _target_pose[3];
  const Scalar _tmp55 = _tmp53 + _tmp54;
  const Scalar _tmp56 = -_tmp39;
  const Scalar _tmp57 = _tmp40 + _tmp56;
  const Scalar _tmp58 = _tmp23 * _tmp57 + _tmp38 * _tmp55;
  const Scalar _tmp59 = _tmp46 * _tmp52 + _tmp58;
  const Scalar _tmp60 = std::pow(_tmp59, Scalar(2));
  const Scalar _tmp61 = _tmp49 + _tmp60 + epsilon;
  const Scalar _tmp62 = std::sqrt(_tmp61);
  const Scalar _tmp63 = Scalar(1.0) / (_tmp62);
  const Scalar _tmp64 = _tmp48 * _tmp63;
  const Scalar _tmp65 = _tmp3 + _tmp51;
  const Scalar _tmp66 = -_tmp54;
  const Scalar _tmp67 = _tmp53 + _tmp66;
  const Scalar _tmp68 = _tmp25 + _tmp27;
  const Scalar _tmp69 = _tmp23 * _tmp68 + _tmp46 * _tmp67;
  const Scalar _tmp70 = _tmp38 * _tmp65 + _tmp69;
  const Scalar _tmp71 = std::atan2(_tmp62, _tmp70);
  const Scalar _tmp72 = -epsilon;
  const Scalar _tmp73 = std::min<Scalar>(_tmp71, _tmp72 + target_calibration_storage(4, 0));
  const Scalar _tmp74 = std::pow(_tmp73, Scalar(9)) * target_calibration_storage(8, 0) +
                        std::pow(_tmp73, Scalar(7)) * target_calibration_storage(7, 0) +
                        std::pow(_tmp73, Scalar(5)) * target_calibration_storage(6, 0) +
                        [&]() {
                          const Scalar base = _tmp73;
                          return base * base * base;
                        }() *
                            target_calibration_storage(5, 0) +
                        _tmp73;
  const Scalar _tmp75 = _tmp74 * target_calibration_storage(0, 0);
  const Scalar _tmp76 = _tmp64 * _tmp75 + target_calibration_storage(2, 0) - target_pixel(0, 0);
  const Scalar _tmp77 = _tmp63 * target_calibration_storage(1, 0);
  const Scalar _tmp78 = _tmp59 * _tmp77;
  const Scalar _tmp79 = _tmp74 * _tmp78 + target_calibration_storage(3, 0) - target_pixel(1, 0);
  const Scalar _tmp80 = std::pow(_tmp76, Scalar(2)) + std::pow(_tmp79, Scalar(2)) + epsilon;
  const Scalar _tmp81 = std::pow(_tmp80, Scalar(Scalar(-1) / Scalar(2)));
  const Scalar _tmp82 = std::sqrt(weight);
  const Scalar _tmp83 = -_tmp71 + target_calibration_storage(4, 0);
  const Scalar _tmp84 = std::max<Scalar>(0, (((_tmp83) > 0) - ((_tmp83) < 0)));
  const Scalar _tmp85 = Scalar(1.0) / (epsilon - gnc_mu + 1);
  const Scalar _tmp86 = epsilon + std::fabs(_tmp85);
  const Scalar _tmp87 = std::pow(gnc_scale, Scalar(-2));
  const Scalar _tmp88 = _tmp80 * _tmp87 / _tmp86 + 1;
  const Scalar _tmp89 = 2 - _tmp85;
  const Scalar _tmp90 =
      _tmp89 + epsilon * (2 * std::min<Scalar>(0, (((_tmp89) > 0) - ((_tmp89) < 0))) + 1);
  const Scalar _tmp91 = (Scalar(1) / Scalar(2)) * _tmp90;
  const Scalar _tmp92 =
      std::sqrt(Scalar(2)) * std::sqrt(Scalar(_tmp86 * (std::pow(_tmp88, _tmp91) - 1) / _tmp90));
  const Scalar _tmp93 = _tmp82 * _tmp84 * _tmp92;
  const Scalar _tmp94 = _tmp81 * _tmp93;
  const Scalar _tmp95 = _tmp76 * _tmp94;
  const Scalar _tmp96 = _tmp79 * _tmp94;
  const Scalar _tmp97 = std::pow(_source_pose[3], Scalar(2));
  const Scalar _tmp98 = -_tmp97;
  const Scalar _tmp99 = -_tmp19;
  const Scalar _tmp100 = _tmp12 * _tmp44 + _tmp16 * (_tmp17 + _tmp35 + _tmp98 + _tmp99);
  const Scalar _tmp101 = -_tmp31;
  const Scalar _tmp102 = _tmp97 + _tmp99;
  const Scalar _tmp103 = -_tmp35;
  const Scalar _tmp104 = _tmp103 + _tmp17;
  const Scalar _tmp105 = _tmp12 * (_tmp102 + _tmp104) + _tmp16 * (_tmp101 + _tmp43);
  const Scalar _tmp106 = -_tmp6;
  const Scalar _tmp107 = _tmp12 * _tmp15 + _tmp16 * (_tmp106 + _tmp8);
  const Scalar _tmp108 = std::pow(_tmp70, Scalar(2));
  const Scalar _tmp109 = _tmp62 / _tmp108;
  const Scalar _tmp110 = _tmp100 * _tmp52 + _tmp105 * _tmp55 + _tmp107 * _tmp57;
  const Scalar _tmp111 = 2 * _tmp59;
  const Scalar _tmp112 = _tmp100 * _tmp41 + _tmp105 * _tmp29 + _tmp107 * _tmp4;
  const Scalar _tmp113 = 2 * _tmp48;
  const Scalar _tmp114 = _tmp110 * _tmp111 + _tmp112 * _tmp113;
  const Scalar _tmp115 = Scalar(1.0) / (_tmp70);
  const Scalar _tmp116 = _tmp115 * _tmp63;
  const Scalar _tmp117 = (Scalar(1) / Scalar(2)) * _tmp116;
  const Scalar _tmp118 =
      -_tmp109 * (_tmp100 * _tmp67 + _tmp105 * _tmp65 + _tmp107 * _tmp68) + _tmp114 * _tmp117;
  const Scalar _tmp119 =
      ((((_tmp72 + _tmp83) > 0) - ((_tmp72 + _tmp83) < 0)) + 1) / (_tmp108 + _tmp61);
  const Scalar _tmp120 = _tmp108 * _tmp119;
  const Scalar _tmp121 = (Scalar(1) / Scalar(2)) * _tmp120;
  const Scalar _tmp122 = std::pow(_tmp73, Scalar(4)) * target_calibration_storage(6, 0);
  const Scalar _tmp123 = (Scalar(5) / Scalar(2)) * _tmp122;
  const Scalar _tmp124 = _tmp120 * _tmp123;
  const Scalar _tmp125 = std::pow(_tmp73, Scalar(6)) * target_calibration_storage(7, 0);
  const Scalar _tmp126 = (Scalar(7) / Scalar(2)) * _tmp125;
  const Scalar _tmp127 = _tmp120 * _tmp126;
  const Scalar _tmp128 = std::pow(_tmp73, Scalar(8)) * target_calibration_storage(8, 0);
  const Scalar _tmp129 = (Scalar(9) / Scalar(2)) * _tmp128;
  const Scalar _tmp130 = _tmp120 * _tmp129;
  const Scalar _tmp131 = std::pow(_tmp73, Scalar(2)) * target_calibration_storage(5, 0);
  const Scalar _tmp132 = (Scalar(3) / Scalar(2)) * _tmp131;
  const Scalar _tmp133 = _tmp120 * _tmp132;
  const Scalar _tmp134 = _tmp118 * _tmp121 + _tmp118 * _tmp124 + _tmp118 * _tmp127 +
                         _tmp118 * _tmp130 + _tmp118 * _tmp133;
  const Scalar _tmp135 = _tmp64 * target_calibration_storage(0, 0);
  const Scalar _tmp136 = _tmp63 * _tmp75;
  const Scalar _tmp137 = std::pow(_tmp61, Scalar(Scalar(-3) / Scalar(2)));
  const Scalar _tmp138 = _tmp137 * _tmp75;
  const Scalar _tmp139 = _tmp138 * _tmp48;
  const Scalar _tmp140 = (Scalar(1) / Scalar(2)) * _tmp139;
  const Scalar _tmp141 = _tmp112 * _tmp136 - _tmp114 * _tmp140 + _tmp134 * _tmp135;
  const Scalar _tmp142 = 2 * _tmp76;
  const Scalar _tmp143 = _tmp137 * _tmp74 * target_calibration_storage(1, 0);
  const Scalar _tmp144 = _tmp143 * _tmp59;
  const Scalar _tmp145 = (Scalar(1) / Scalar(2)) * _tmp144;
  const Scalar _tmp146 = _tmp74 * _tmp77;
  const Scalar _tmp147 = _tmp110 * _tmp146 - _tmp114 * _tmp145 + _tmp134 * _tmp78;
  const Scalar _tmp148 = 2 * _tmp79;
  const Scalar _tmp149 = _tmp141 * _tmp142 + _tmp147 * _tmp148;
  const Scalar _tmp150 = (Scalar(1) / Scalar(2)) * _tmp76;
  const Scalar _tmp151 = _tmp93 / (_tmp80 * std::sqrt(_tmp80));
  const Scalar _tmp152 = _tmp150 * _tmp151;
  const Scalar _tmp153 =
      _tmp81 * _tmp82 * _tmp84 * _tmp87 * std::pow(_tmp88, Scalar(_tmp91 - 1)) / _tmp92;
  const Scalar _tmp154 = _tmp150 * _tmp153;
  const Scalar _tmp155 = _tmp141 * _tmp94 - _tmp149 * _tmp152 + _tmp149 * _tmp154;
  const Scalar _tmp156 = (Scalar(1) / Scalar(2)) * _tmp79;
  const Scalar _tmp157 = _tmp151 * _tmp156;
  const Scalar _tmp158 = _tmp153 * _tmp156;
  const Scalar _tmp159 = _tmp147 * _tmp94 - _tmp149 * _tmp157 + _tmp149 * _tmp158;
  const Scalar _tmp160 = -_tmp13;
  const Scalar _tmp161 = -_tmp17;
  const Scalar _tmp162 = _tmp161 + _tmp35;
  const Scalar _tmp163 = _tmp16 * (_tmp102 + _tmp162) + _tmp21 * (_tmp160 + _tmp33);
  const Scalar _tmp164 = _tmp19 + _tmp98;
  const Scalar _tmp165 = _tmp16 * _tmp34 + _tmp21 * (_tmp162 + _tmp164);
  const Scalar _tmp166 = _tmp16 * _tmp42 + _tmp21 * (_tmp101 + _tmp30);
  const Scalar _tmp167 = _tmp163 * _tmp57 + _tmp165 * _tmp55 + _tmp166 * _tmp52;
  const Scalar _tmp168 = _tmp163 * _tmp4 + _tmp165 * _tmp29 + _tmp166 * _tmp41;
  const Scalar _tmp169 = _tmp111 * _tmp167 + _tmp113 * _tmp168;
  const Scalar _tmp170 =
      -_tmp109 * (_tmp163 * _tmp68 + _tmp165 * _tmp65 + _tmp166 * _tmp67) + _tmp117 * _tmp169;
  const Scalar _tmp171 = _tmp121 * _tmp170 + _tmp124 * _tmp170 + _tmp127 * _tmp170 +
                         _tmp130 * _tmp170 + _tmp133 * _tmp170;
  const Scalar _tmp172 = -_tmp145 * _tmp169 + _tmp146 * _tmp167 + _tmp171 * _tmp78;
  const Scalar _tmp173 = _tmp135 * _tmp171 + _tmp136 * _tmp168 - _tmp140 * _tmp169;
  const Scalar _tmp174 = _tmp142 * _tmp173 + _tmp148 * _tmp172;
  const Scalar _tmp175 = -_tmp152 * _tmp174 + _tmp154 * _tmp174 + _tmp173 * _tmp94;
  const Scalar _tmp176 = -_tmp157 * _tmp174 + _tmp158 * _tmp174 + _tmp172 * _tmp94;
  const Scalar _tmp177 = _tmp12 * (_tmp14 + _tmp160) + _tmp21 * _tmp32;
  const Scalar _tmp178 =
      _tmp12 * (_tmp106 + _tmp9) + _tmp21 * (_tmp103 + _tmp161 + _tmp19 + _tmp97);
  const Scalar _tmp179 = _tmp10 * _tmp21 + _tmp12 * (_tmp104 + _tmp164);
  const Scalar _tmp180 = _tmp177 * _tmp29 + _tmp178 * _tmp41 + _tmp179 * _tmp4;
  const Scalar _tmp181 = _tmp177 * _tmp55 + _tmp178 * _tmp52 + _tmp179 * _tmp57;
  const Scalar _tmp182 =
      (Scalar(1) / Scalar(2)) * _tmp111 * _tmp181 + (Scalar(1) / Scalar(2)) * _tmp113 * _tmp180;
  const Scalar _tmp183 =
      -_tmp109 * (_tmp177 * _tmp65 + _tmp178 * _tmp67 + _tmp179 * _tmp68) + _tmp116 * _tmp182;
  const Scalar _tmp184 = _tmp121 * _tmp183 + _tmp124 * _tmp183 + _tmp127 * _tmp183 +
                         _tmp130 * _tmp183 + _tmp133 * _tmp183;
  const Scalar _tmp185 = -_tmp144 * _tmp182 + _tmp146 * _tmp181 + _tmp184 * _tmp78;
  const Scalar _tmp186 = _tmp135 * _tmp184 + _tmp136 * _tmp180 - _tmp139 * _tmp182;
  const Scalar _tmp187 = _tmp142 * _tmp186 + _tmp148 * _tmp185;
  const Scalar _tmp188 = _tmp150 * _tmp187;
  const Scalar _tmp189 = -_tmp151 * _tmp188 + _tmp153 * _tmp188 + _tmp186 * _tmp94;
  const Scalar _tmp190 = -_tmp157 * _tmp187 + _tmp158 * _tmp187 + _tmp185 * _tmp94;
  const Scalar _tmp191 = _tmp113 * source_inverse_range;
  const Scalar _tmp192 = _tmp191 * _tmp4;
  const Scalar _tmp193 = _tmp111 * source_inverse_range;
  const Scalar _tmp194 = _tmp193 * _tmp57;
  const Scalar _tmp195 = _tmp192 + _tmp194;
  const Scalar _tmp196 = _tmp109 * source_inverse_range;
  const Scalar _tmp197 = _tmp196 * _tmp68;
  const Scalar _tmp198 = _tmp117 * _tmp195 - _tmp197;
  const Scalar _tmp199 = _tmp120 * _tmp198;
  const Scalar _tmp200 = _tmp121 * _tmp198 + _tmp123 * _tmp199 + _tmp127 * _tmp198 +
                         _tmp129 * _tmp199 + _tmp133 * _tmp198;
  const Scalar _tmp201 = _tmp136 * source_inverse_range;
  const Scalar _tmp202 = _tmp201 * _tmp4;
  const Scalar _tmp203 = _tmp135 * _tmp200 - _tmp140 * _tmp195 + _tmp202;
  const Scalar _tmp204 = _tmp146 * source_inverse_range;
  const Scalar _tmp205 = _tmp204 * _tmp57;
  const Scalar _tmp206 = -_tmp145 * _tmp195 + _tmp200 * _tmp78 + _tmp205;
  const Scalar _tmp207 = _tmp142 * _tmp203 + _tmp148 * _tmp206;
  const Scalar _tmp208 = -_tmp152 * _tmp207 + _tmp154 * _tmp207 + _tmp203 * _tmp94;
  const Scalar _tmp209 = -_tmp157 * _tmp207 + _tmp158 * _tmp207 + _tmp206 * _tmp94;
  const Scalar _tmp210 = _tmp191 * _tmp41;
  const Scalar _tmp211 = _tmp193 * _tmp52;
  const Scalar _tmp212 = _tmp210 + _tmp211;
  const Scalar _tmp213 = _tmp196 * _tmp67;
  const Scalar _tmp214 = _tmp117 * _tmp212 - _tmp213;
  const Scalar _tmp215 = _tmp121 * _tmp214 + _tmp124 * _tmp214 + _tmp127 * _tmp214 +
                         _tmp130 * _tmp214 + _tmp133 * _tmp214;
  const Scalar _tmp216 = _tmp201 * _tmp41;
  const Scalar _tmp217 = _tmp135 * _tmp215 - _tmp140 * _tmp212 + _tmp216;
  const Scalar _tmp218 = _tmp204 * _tmp52;
  const Scalar _tmp219 = -_tmp145 * _tmp212 + _tmp215 * _tmp78 + _tmp218;
  const Scalar _tmp220 = _tmp142 * _tmp217 + _tmp148 * _tmp219;
  const Scalar _tmp221 = -_tmp152 * _tmp220 + _tmp154 * _tmp220 + _tmp217 * _tmp94;
  const Scalar _tmp222 = -_tmp157 * _tmp220 + _tmp158 * _tmp220 + _tmp219 * _tmp94;
  const Scalar _tmp223 = _tmp191 * _tmp29;
  const Scalar _tmp224 = _tmp193 * _tmp55;
  const Scalar _tmp225 = _tmp223 + _tmp224;
  const Scalar _tmp226 = _tmp196 * _tmp65;
  const Scalar _tmp227 = _tmp117 * _tmp225 - _tmp226;
  const Scalar _tmp228 = _tmp120 * _tmp227;
  const Scalar _tmp229 = _tmp121 * _tmp227 + _tmp123 * _tmp228 + _tmp126 * _tmp228 +
                         _tmp129 * _tmp228 + _tmp133 * _tmp227;
  const Scalar _tmp230 = _tmp204 * _tmp55;
  const Scalar _tmp231 = -_tmp145 * _tmp225 + _tmp229 * _tmp78 + _tmp230;
  const Scalar _tmp232 = _tmp201 * _tmp29;
  const Scalar _tmp233 = _tmp135 * _tmp229 - _tmp140 * _tmp225 + _tmp232;
  const Scalar _tmp234 = _tmp142 * _tmp233 + _tmp148 * _tmp231;
  const Scalar _tmp235 = -_tmp152 * _tmp234 + _tmp154 * _tmp234 + _tmp233 * _tmp94;
  const Scalar _tmp236 = -_tmp157 * _tmp234 + _tmp158 * _tmp234 + _tmp231 * _tmp94;
  const Scalar _tmp237 = -_tmp53;
  const Scalar _tmp238 = std::pow(_target_pose[3], Scalar(2));
  const Scalar _tmp239 = -_tmp238;
  const Scalar _tmp240 = _tmp239 + _tmp50;
  const Scalar _tmp241 = -_tmp2;
  const Scalar _tmp242 = _tmp0 + _tmp241;
  const Scalar _tmp243 = -_tmp40;
  const Scalar _tmp244 = -_tmp50;
  const Scalar _tmp245 = _tmp238 + _tmp244;
  const Scalar _tmp246 = _tmp38 * (_tmp242 + _tmp245) + _tmp69;
  const Scalar _tmp247 = _tmp246 * _tmp59;
  const Scalar _tmp248 = -_tmp109 * (_tmp23 * (_tmp243 + _tmp39) + _tmp38 * (_tmp237 + _tmp66) +
                                     _tmp46 * (_tmp240 + _tmp242)) +
                         _tmp116 * _tmp247;
  const Scalar _tmp249 = _tmp120 * _tmp248;
  const Scalar _tmp250 = _tmp121 * _tmp248 + _tmp123 * _tmp249 + _tmp126 * _tmp249 +
                         _tmp129 * _tmp249 + _tmp132 * _tmp249;
  const Scalar _tmp251 = _tmp135 * _tmp250 - _tmp139 * _tmp247;
  const Scalar _tmp252 = -_tmp143 * _tmp246 * _tmp60 + _tmp146 * _tmp246 + _tmp250 * _tmp78;
  const Scalar _tmp253 = _tmp142 * _tmp251 + _tmp148 * _tmp252;
  const Scalar _tmp254 = -_tmp152 * _tmp253 + _tmp154 * _tmp253 + _tmp251 * _tmp94;
  const Scalar _tmp255 = -_tmp157 * _tmp253 + _tmp158 * _tmp253 + _tmp252 * _tmp94;
  const Scalar _tmp256 = -_tmp0;
  const Scalar _tmp257 = _tmp2 + _tmp256;
  const Scalar _tmp258 = -_tmp25;
  const Scalar _tmp259 =
      _tmp23 * (_tmp258 + _tmp28) + _tmp38 * (_tmp240 + _tmp257) + _tmp46 * (_tmp237 + _tmp54);
  const Scalar _tmp260 = -_tmp109 * (_tmp23 * (_tmp238 + _tmp241 + _tmp256 + _tmp50) + _tmp47) +
                         _tmp115 * _tmp259 * _tmp64;
  const Scalar _tmp261 = _tmp121 * _tmp260 + _tmp124 * _tmp260 + _tmp127 * _tmp260 +
                         _tmp130 * _tmp260 + _tmp133 * _tmp260;
  const Scalar _tmp262 = -_tmp144 * _tmp259 * _tmp48 + _tmp261 * _tmp78;
  const Scalar _tmp263 = _tmp135 * _tmp261 + _tmp136 * _tmp259 - _tmp138 * _tmp259 * _tmp49;
  const Scalar _tmp264 = _tmp142 * _tmp263 + _tmp148 * _tmp262;
  const Scalar _tmp265 = -_tmp152 * _tmp264 + _tmp154 * _tmp264 + _tmp263 * _tmp94;
  const Scalar _tmp266 = -_tmp157 * _tmp264 + _tmp158 * _tmp264 + _tmp262 * _tmp94;
  const Scalar _tmp267 = _tmp46 * (_tmp245 + _tmp257) + _tmp58;
  const Scalar _tmp268 = _tmp23 * (_tmp0 + _tmp2 + _tmp239 + _tmp244) +
                         _tmp38 * (_tmp258 + _tmp27) + _tmp46 * (_tmp243 + _tmp56);
  const Scalar _tmp269 = _tmp111 * _tmp268 + _tmp113 * _tmp267;
  const Scalar _tmp270 = _tmp119 * _tmp269 * _tmp63 * _tmp70;
  const Scalar _tmp271 =
      (Scalar(5) / Scalar(4)) * _tmp122 * _tmp270 + (Scalar(7) / Scalar(4)) * _tmp125 * _tmp270 +
      (Scalar(9) / Scalar(4)) * _tmp128 * _tmp270 + (Scalar(3) / Scalar(4)) * _tmp131 * _tmp270 +
      (Scalar(1) / Scalar(4)) * _tmp270;
  const Scalar _tmp272 = _tmp135 * _tmp271 + _tmp136 * _tmp267 - _tmp140 * _tmp269;
  const Scalar _tmp273 = -_tmp145 * _tmp269 + _tmp146 * _tmp268 + _tmp271 * _tmp78;
  const Scalar _tmp274 = _tmp142 * _tmp272 + _tmp148 * _tmp273;
  const Scalar _tmp275 = -_tmp152 * _tmp274 + _tmp154 * _tmp274 + _tmp272 * _tmp94;
  const Scalar _tmp276 = -_tmp157 * _tmp274 + _tmp158 * _tmp274 + _tmp273 * _tmp94;
  const Scalar _tmp277 = -_tmp192 - _tmp194;
  const Scalar _tmp278 = _tmp117 * _tmp277 + _tmp197;
  const Scalar _tmp279 = _tmp120 * _tmp278;
  const Scalar _tmp280 = _tmp121 * _tmp278 + _tmp123 * _tmp279 + _tmp127 * _tmp278 +
                         _tmp129 * _tmp279 + _tmp133 * _tmp278;
  const Scalar _tmp281 = _tmp135 * _tmp280 - _tmp140 * _tmp277 - _tmp202;
  const Scalar _tmp282 = -_tmp145 * _tmp277 - _tmp205 + _tmp280 * _tmp78;
  const Scalar _tmp283 = _tmp142 * _tmp281 + _tmp148 * _tmp282;
  const Scalar _tmp284 = _tmp151 * _tmp283;
  const Scalar _tmp285 = -_tmp150 * _tmp284 + _tmp154 * _tmp283 + _tmp281 * _tmp94;
  const Scalar _tmp286 = -_tmp156 * _tmp284 + _tmp158 * _tmp283 + _tmp282 * _tmp94;
  const Scalar _tmp287 = -_tmp210 - _tmp211;
  const Scalar _tmp288 = _tmp117 * _tmp287 + _tmp213;
  const Scalar _tmp289 = _tmp120 * _tmp288;
  const Scalar _tmp290 = _tmp121 * _tmp288 + _tmp123 * _tmp289 + _tmp126 * _tmp289 +
                         _tmp129 * _tmp289 + _tmp132 * _tmp289;
  const Scalar _tmp291 = (Scalar(1) / Scalar(2)) * _tmp287;
  const Scalar _tmp292 = _tmp135 * _tmp290 - _tmp139 * _tmp291 - _tmp216;
  const Scalar _tmp293 = -_tmp144 * _tmp291 - _tmp218 + _tmp290 * _tmp78;
  const Scalar _tmp294 = _tmp142 * _tmp292 + _tmp148 * _tmp293;
  const Scalar _tmp295 = -_tmp152 * _tmp294 + _tmp154 * _tmp294 + _tmp292 * _tmp94;
  const Scalar _tmp296 = -_tmp157 * _tmp294 + _tmp158 * _tmp294 + _tmp293 * _tmp94;
  const Scalar _tmp297 = -_tmp223 - _tmp224;
  const Scalar _tmp298 = _tmp117 * _tmp297 + _tmp226;
  const Scalar _tmp299 = _tmp120 * _tmp298;
  const Scalar _tmp300 = _tmp121 * _tmp298 + _tmp123 * _tmp299 + _tmp126 * _tmp299 +
                         _tmp129 * _tmp299 + _tmp133 * _tmp298;
  const Scalar _tmp301 = _tmp135 * _tmp300 - _tmp140 * _tmp297 - _tmp232;
  const Scalar _tmp302 = -_tmp145 * _tmp297 - _tmp230 + _tmp300 * _tmp78;
  const Scalar _tmp303 = _tmp142 * _tmp301 + _tmp148 * _tmp302;
  const Scalar _tmp304 = -_tmp152 * _tmp303 + _tmp154 * _tmp303 + _tmp301 * _tmp94;
  const Scalar _tmp305 = -_tmp157 * _tmp303 + _tmp158 * _tmp303 + _tmp302 * _tmp94;
  const Scalar _tmp306 = _tmp22 * _tmp4 + _tmp29 * _tmp37 + _tmp41 * _tmp45;
  const Scalar _tmp307 = _tmp22 * _tmp57 + _tmp37 * _tmp55 + _tmp45 * _tmp52;
  const Scalar _tmp308 = _tmp111 * _tmp307 + _tmp113 * _tmp306;
  const Scalar _tmp309 =
      -_tmp109 * (_tmp22 * _tmp68 + _tmp37 * _tmp65 + _tmp45 * _tmp67) + _tmp117 * _tmp308;
  const Scalar _tmp310 = _tmp120 * _tmp309;
  const Scalar _tmp311 = _tmp121 * _tmp309 + _tmp123 * _tmp310 + _tmp126 * _tmp310 +
                         _tmp129 * _tmp310 + _tmp133 * _tmp309;
  const Scalar _tmp312 = _tmp135 * _tmp311 + _tmp136 * _tmp306 - _tmp140 * _tmp308;
  const Scalar _tmp313 = -_tmp145 * _tmp308 + _tmp146 * _tmp307 + _tmp311 * _tmp78;
  const Scalar _tmp314 = _tmp142 * _tmp312 + _tmp148 * _tmp313;
  const Scalar _tmp315 = -_tmp152 * _tmp314 + _tmp154 * _tmp314 + _tmp312 * _tmp94;
  const Scalar _tmp316 = -_tmp157 * _tmp314 + _tmp158 * _tmp314 + _tmp313 * _tmp94;

  // Output terms (4)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 2, 1>& _res = (*res);

    _res(0, 0) = _tmp95;
    _res(1, 0) = _tmp96;
  }

  if (jacobian != nullptr) {
    Eigen::Matrix<Scalar, 2, 13>& _jacobian = (*jacobian);

    _jacobian(0, 0) = _tmp155;
    _jacobian(1, 0) = _tmp159;
    _jacobian(0, 1) = _tmp175;
    _jacobian(1, 1) = _tmp176;
    _jacobian(0, 2) = _tmp189;
    _jacobian(1, 2) = _tmp190;
    _jacobian(0, 3) = _tmp208;
    _jacobian(1, 3) = _tmp209;
    _jacobian(0, 4) = _tmp221;
    _jacobian(1, 4) = _tmp222;
    _jacobian(0, 5) = _tmp235;
    _jacobian(1, 5) = _tmp236;
    _jacobian(0, 6) = _tmp254;
    _jacobian(1, 6) = _tmp255;
    _jacobian(0, 7) = _tmp265;
    _jacobian(1, 7) = _tmp266;
    _jacobian(0, 8) = _tmp275;
    _jacobian(1, 8) = _tmp276;
    _jacobian(0, 9) = _tmp285;
    _jacobian(1, 9) = _tmp286;
    _jacobian(0, 10) = _tmp295;
    _jacobian(1, 10) = _tmp296;
    _jacobian(0, 11) = _tmp304;
    _jacobian(1, 11) = _tmp305;
    _jacobian(0, 12) = _tmp315;
    _jacobian(1, 12) = _tmp316;
  }

  if (hessian != nullptr) {
    Eigen::Matrix<Scalar, 13, 13>& _hessian = (*hessian);

    _hessian(0, 0) = std::pow(_tmp155, Scalar(2)) + std::pow(_tmp159, Scalar(2));
    _hessian(1, 0) = _tmp155 * _tmp175 + _tmp159 * _tmp176;
    _hessian(2, 0) = _tmp155 * _tmp189 + _tmp159 * _tmp190;
    _hessian(3, 0) = _tmp155 * _tmp208 + _tmp159 * _tmp209;
    _hessian(4, 0) = _tmp155 * _tmp221 + _tmp159 * _tmp222;
    _hessian(5, 0) = _tmp155 * _tmp235 + _tmp159 * _tmp236;
    _hessian(6, 0) = _tmp155 * _tmp254 + _tmp159 * _tmp255;
    _hessian(7, 0) = _tmp155 * _tmp265 + _tmp159 * _tmp266;
    _hessian(8, 0) = _tmp155 * _tmp275 + _tmp159 * _tmp276;
    _hessian(9, 0) = _tmp155 * _tmp285 + _tmp159 * _tmp286;
    _hessian(10, 0) = _tmp155 * _tmp295 + _tmp159 * _tmp296;
    _hessian(11, 0) = _tmp155 * _tmp304 + _tmp159 * _tmp305;
    _hessian(12, 0) = _tmp155 * _tmp315 + _tmp159 * _tmp316;
    _hessian(0, 1) = 0;
    _hessian(1, 1) = std::pow(_tmp175, Scalar(2)) + std::pow(_tmp176, Scalar(2));
    _hessian(2, 1) = _tmp175 * _tmp189 + _tmp176 * _tmp190;
    _hessian(3, 1) = _tmp175 * _tmp208 + _tmp176 * _tmp209;
    _hessian(4, 1) = _tmp175 * _tmp221 + _tmp176 * _tmp222;
    _hessian(5, 1) = _tmp175 * _tmp235 + _tmp176 * _tmp236;
    _hessian(6, 1) = _tmp175 * _tmp254 + _tmp176 * _tmp255;
    _hessian(7, 1) = _tmp175 * _tmp265 + _tmp176 * _tmp266;
    _hessian(8, 1) = _tmp175 * _tmp275 + _tmp176 * _tmp276;
    _hessian(9, 1) = _tmp175 * _tmp285 + _tmp176 * _tmp286;
    _hessian(10, 1) = _tmp175 * _tmp295 + _tmp176 * _tmp296;
    _hessian(11, 1) = _tmp175 * _tmp304 + _tmp176 * _tmp305;
    _hessian(12, 1) = _tmp175 * _tmp315 + _tmp176 * _tmp316;
    _hessian(0, 2) = 0;
    _hessian(1, 2) = 0;
    _hessian(2, 2) = std::pow(_tmp189, Scalar(2)) + std::pow(_tmp190, Scalar(2));
    _hessian(3, 2) = _tmp189 * _tmp208 + _tmp190 * _tmp209;
    _hessian(4, 2) = _tmp189 * _tmp221 + _tmp190 * _tmp222;
    _hessian(5, 2) = _tmp189 * _tmp235 + _tmp190 * _tmp236;
    _hessian(6, 2) = _tmp189 * _tmp254 + _tmp190 * _tmp255;
    _hessian(7, 2) = _tmp189 * _tmp265 + _tmp190 * _tmp266;
    _hessian(8, 2) = _tmp189 * _tmp275 + _tmp190 * _tmp276;
    _hessian(9, 2) = _tmp189 * _tmp285 + _tmp190 * _tmp286;
    _hessian(10, 2) = _tmp189 * _tmp295 + _tmp190 * _tmp296;
    _hessian(11, 2) = _tmp189 * _tmp304 + _tmp190 * _tmp305;
    _hessian(12, 2) = _tmp189 * _tmp315 + _tmp190 * _tmp316;
    _hessian(0, 3) = 0;
    _hessian(1, 3) = 0;
    _hessian(2, 3) = 0;
    _hessian(3, 3) = std::pow(_tmp208, Scalar(2)) + std::pow(_tmp209, Scalar(2));
    _hessian(4, 3) = _tmp208 * _tmp221 + _tmp209 * _tmp222;
    _hessian(5, 3) = _tmp208 * _tmp235 + _tmp209 * _tmp236;
    _hessian(6, 3) = _tmp208 * _tmp254 + _tmp209 * _tmp255;
    _hessian(7, 3) = _tmp208 * _tmp265 + _tmp209 * _tmp266;
    _hessian(8, 3) = _tmp208 * _tmp275 + _tmp209 * _tmp276;
    _hessian(9, 3) = _tmp208 * _tmp285 + _tmp209 * _tmp286;
    _hessian(10, 3) = _tmp208 * _tmp295 + _tmp209 * _tmp296;
    _hessian(11, 3) = _tmp208 * _tmp304 + _tmp209 * _tmp305;
    _hessian(12, 3) = _tmp208 * _tmp315 + _tmp209 * _tmp316;
    _hessian(0, 4) = 0;
    _hessian(1, 4) = 0;
    _hessian(2, 4) = 0;
    _hessian(3, 4) = 0;
    _hessian(4, 4) = std::pow(_tmp221, Scalar(2)) + std::pow(_tmp222, Scalar(2));
    _hessian(5, 4) = _tmp221 * _tmp235 + _tmp222 * _tmp236;
    _hessian(6, 4) = _tmp221 * _tmp254 + _tmp222 * _tmp255;
    _hessian(7, 4) = _tmp221 * _tmp265 + _tmp222 * _tmp266;
    _hessian(8, 4) = _tmp221 * _tmp275 + _tmp222 * _tmp276;
    _hessian(9, 4) = _tmp221 * _tmp285 + _tmp222 * _tmp286;
    _hessian(10, 4) = _tmp221 * _tmp295 + _tmp222 * _tmp296;
    _hessian(11, 4) = _tmp221 * _tmp304 + _tmp222 * _tmp305;
    _hessian(12, 4) = _tmp221 * _tmp315 + _tmp222 * _tmp316;
    _hessian(0, 5) = 0;
    _hessian(1, 5) = 0;
    _hessian(2, 5) = 0;
    _hessian(3, 5) = 0;
    _hessian(4, 5) = 0;
    _hessian(5, 5) = std::pow(_tmp235, Scalar(2)) + std::pow(_tmp236, Scalar(2));
    _hessian(6, 5) = _tmp235 * _tmp254 + _tmp236 * _tmp255;
    _hessian(7, 5) = _tmp235 * _tmp265 + _tmp236 * _tmp266;
    _hessian(8, 5) = _tmp235 * _tmp275 + _tmp236 * _tmp276;
    _hessian(9, 5) = _tmp235 * _tmp285 + _tmp236 * _tmp286;
    _hessian(10, 5) = _tmp235 * _tmp295 + _tmp236 * _tmp296;
    _hessian(11, 5) = _tmp235 * _tmp304 + _tmp236 * _tmp305;
    _hessian(12, 5) = _tmp235 * _tmp315 + _tmp236 * _tmp316;
    _hessian(0, 6) = 0;
    _hessian(1, 6) = 0;
    _hessian(2, 6) = 0;
    _hessian(3, 6) = 0;
    _hessian(4, 6) = 0;
    _hessian(5, 6) = 0;
    _hessian(6, 6) = std::pow(_tmp254, Scalar(2)) + std::pow(_tmp255, Scalar(2));
    _hessian(7, 6) = _tmp254 * _tmp265 + _tmp255 * _tmp266;
    _hessian(8, 6) = _tmp254 * _tmp275 + _tmp255 * _tmp276;
    _hessian(9, 6) = _tmp254 * _tmp285 + _tmp255 * _tmp286;
    _hessian(10, 6) = _tmp254 * _tmp295 + _tmp255 * _tmp296;
    _hessian(11, 6) = _tmp254 * _tmp304 + _tmp255 * _tmp305;
    _hessian(12, 6) = _tmp254 * _tmp315 + _tmp255 * _tmp316;
    _hessian(0, 7) = 0;
    _hessian(1, 7) = 0;
    _hessian(2, 7) = 0;
    _hessian(3, 7) = 0;
    _hessian(4, 7) = 0;
    _hessian(5, 7) = 0;
    _hessian(6, 7) = 0;
    _hessian(7, 7) = std::pow(_tmp265, Scalar(2)) + std::pow(_tmp266, Scalar(2));
    _hessian(8, 7) = _tmp265 * _tmp275 + _tmp266 * _tmp276;
    _hessian(9, 7) = _tmp265 * _tmp285 + _tmp266 * _tmp286;
    _hessian(10, 7) = _tmp265 * _tmp295 + _tmp266 * _tmp296;
    _hessian(11, 7) = _tmp265 * _tmp304 + _tmp266 * _tmp305;
    _hessian(12, 7) = _tmp265 * _tmp315 + _tmp266 * _tmp316;
    _hessian(0, 8) = 0;
    _hessian(1, 8) = 0;
    _hessian(2, 8) = 0;
    _hessian(3, 8) = 0;
    _hessian(4, 8) = 0;
    _hessian(5, 8) = 0;
    _hessian(6, 8) = 0;
    _hessian(7, 8) = 0;
    _hessian(8, 8) = std::pow(_tmp275, Scalar(2)) + std::pow(_tmp276, Scalar(2));
    _hessian(9, 8) = _tmp275 * _tmp285 + _tmp276 * _tmp286;
    _hessian(10, 8) = _tmp275 * _tmp295 + _tmp276 * _tmp296;
    _hessian(11, 8) = _tmp275 * _tmp304 + _tmp276 * _tmp305;
    _hessian(12, 8) = _tmp275 * _tmp315 + _tmp276 * _tmp316;
    _hessian(0, 9) = 0;
    _hessian(1, 9) = 0;
    _hessian(2, 9) = 0;
    _hessian(3, 9) = 0;
    _hessian(4, 9) = 0;
    _hessian(5, 9) = 0;
    _hessian(6, 9) = 0;
    _hessian(7, 9) = 0;
    _hessian(8, 9) = 0;
    _hessian(9, 9) = std::pow(_tmp285, Scalar(2)) + std::pow(_tmp286, Scalar(2));
    _hessian(10, 9) = _tmp285 * _tmp295 + _tmp286 * _tmp296;
    _hessian(11, 9) = _tmp285 * _tmp304 + _tmp286 * _tmp305;
    _hessian(12, 9) = _tmp285 * _tmp315 + _tmp286 * _tmp316;
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
    _hessian(10, 10) = std::pow(_tmp295, Scalar(2)) + std::pow(_tmp296, Scalar(2));
    _hessian(11, 10) = _tmp295 * _tmp304 + _tmp296 * _tmp305;
    _hessian(12, 10) = _tmp295 * _tmp315 + _tmp296 * _tmp316;
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
    _hessian(11, 11) = std::pow(_tmp304, Scalar(2)) + std::pow(_tmp305, Scalar(2));
    _hessian(12, 11) = _tmp304 * _tmp315 + _tmp305 * _tmp316;
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
    _hessian(12, 12) = std::pow(_tmp315, Scalar(2)) + std::pow(_tmp316, Scalar(2));
  }

  if (rhs != nullptr) {
    Eigen::Matrix<Scalar, 13, 1>& _rhs = (*rhs);

    _rhs(0, 0) = _tmp155 * _tmp95 + _tmp159 * _tmp96;
    _rhs(1, 0) = _tmp175 * _tmp95 + _tmp176 * _tmp96;
    _rhs(2, 0) = _tmp189 * _tmp95 + _tmp190 * _tmp96;
    _rhs(3, 0) = _tmp208 * _tmp95 + _tmp209 * _tmp96;
    _rhs(4, 0) = _tmp221 * _tmp95 + _tmp222 * _tmp96;
    _rhs(5, 0) = _tmp235 * _tmp95 + _tmp236 * _tmp96;
    _rhs(6, 0) = _tmp254 * _tmp95 + _tmp255 * _tmp96;
    _rhs(7, 0) = _tmp265 * _tmp95 + _tmp266 * _tmp96;
    _rhs(8, 0) = _tmp275 * _tmp95 + _tmp276 * _tmp96;
    _rhs(9, 0) = _tmp285 * _tmp95 + _tmp286 * _tmp96;
    _rhs(10, 0) = _tmp295 * _tmp95 + _tmp296 * _tmp96;
    _rhs(11, 0) = _tmp304 * _tmp95 + _tmp305 * _tmp96;
    _rhs(12, 0) = _tmp315 * _tmp95 + _tmp316 * _tmp96;
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym