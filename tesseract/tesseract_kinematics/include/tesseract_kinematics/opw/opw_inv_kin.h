/**
 * @file opw_inv_kin.h
 * @brief Tesseract OPW Inverse kinematics Wrapper
 *
 * @author Levi Armstrong
 * @date Dec 18, 2017
 * @version TODO
 * @bug No known bugs
 *
 * @copyright Copyright (c) 2017, Southwest Research Institute
 *
 * @par License
 * Software License Agreement (Apache License)
 * @par
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * @par
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef TESSERACT_KINEMATICS_OPW_INV_KIN_H
#define TESSERACT_KINEMATICS_OPW_INV_KIN_H

#include <tesseract_common/macros.h>
TESSERACT_COMMON_IGNORE_WARNINGS_PUSH
#include <opw_kinematics/opw_parameters.h>
TESSERACT_COMMON_IGNORE_WARNINGS_POP

#include <tesseract_kinematics/core/inverse_kinematics.h>

namespace tesseract_kinematics
{
/**@brief OPW Inverse Kinematics Implmentation. */
class OPWInvKin : public InverseKinematics
{
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  using Ptr = std::shared_ptr<OPWInvKin>;
  using ConstPtr = std::shared_ptr<const OPWInvKin>;

  OPWInvKin(const std::string name,
            const opw_kinematics::Parameters<double> params,
            const std::string base_link_name,
            const std::string tip_link_name,
            const std::vector<std::string> joint_names,
            const std::vector<std::string> link_names,
            const std::vector<std::string> active_link_names,
            const Eigen::MatrixX2d joint_limits);

  bool calcInvKin(Eigen::VectorXd& solutions,
                  const Eigen::Isometry3d& pose,
                  const Eigen::Ref<const Eigen::VectorXd>& seed) const override;

  bool calcInvKin(Eigen::VectorXd& solutions,
                  const Eigen::Isometry3d& pose,
                  const Eigen::Ref<const Eigen::VectorXd>& seed,
                  const std::string& link_name) const override;

  bool checkJoints(const Eigen::Ref<const Eigen::VectorXd>& vec) const override;
  unsigned int numJoints() const override;

  const std::vector<std::string>& getJointNames() const override { return joint_names_; }
  const std::vector<std::string>& getLinkNames() const override { return link_names_; }
  const std::vector<std::string>& getActiveLinkNames() const override { return active_link_names_; }
  const Eigen::MatrixX2d& getLimits() const override { return joint_limits_; }
  const std::string& getBaseLinkName() const override { return base_link_name_; }
  const std::string& getTipLinkName() const override { return tip_link_name_; }
  const std::string& getName() const override { return name_; }
  const std::string& getSolverName() const override { return solver_name_; }
  InverseKinematics::Ptr clone() const override { return std::make_shared<OPWInvKin>(*this); }

  /**
   * @brief Checks if kinematics has been initialized
   * @return True if init() has completed successfully
   */
  bool checkInitialized() const
  {
    if (!initialized_)
    {
      CONSOLE_BRIDGE_logError("Kinematics has not been initialized!");
    }

    return initialized_;
  }

protected:
  bool initialized_ = true;                    /**< @brief Identifies if the object has been initialized */
  opw_kinematics::Parameters<double> params_;  /**< @brief The opw kinematics parameters */
  std::string base_link_name_;                 /**< @brief Kinematic base link name */
  std::string tip_link_name_;                  /**< @brief Kinematic tip link name */
  Eigen::MatrixX2d joint_limits_;              /**< @brief Joint Limits */
  std::vector<std::string> joint_names_;       /**< @brief joint names */
  std::vector<std::string> link_names_;        /**< @brief link names */
  std::vector<std::string> active_link_names_; /**< @brief active link names */
  std::string name_;                           /**< @brief Name of the kinematic chain */
  std::string solver_name_ = "OPWInvKin";      /**< @brief Name of this solver */
};

}  // namespace tesseract_kinematics
#endif  // TESSERACT_KINEMATICS_OPW_INV_KIN_H