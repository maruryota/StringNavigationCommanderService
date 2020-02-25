// -*-C++-*-
/*!
 * @file  TidyUpManagerSVC_impl.cpp
 * @brief Service implementation code of TidyUpManager.idl
 *
 */

#include "TidyUpManagerSVC_impl.h"
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include "MobileRobotStub.h"
#include "ExtendedDataTypesStub.h"
#include "StringNavigationCommanderService.h"

/*
 * Example implementational code for IDL interface ogata::TidyUpManager
 */
ogata_TidyUpManagerSVC_impl::ogata_TidyUpManagerSVC_impl()
{
  // Please add extra constructor code here.
}


ogata_TidyUpManagerSVC_impl::~ogata_TidyUpManagerSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
ogata::RETURN_VALUE ogata_TidyUpManagerSVC_impl::tidyup(const RTC::TimedPose2D& path, const RTC::TimedString& kind)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <ogata::RETURN_VALUE ogata_TidyUpManagerSVC_impl::tidyup(const RTC::TimedPose2D& path, const RTC::TimedString& kind)>"
#endif
	  return ogata::RETURN_VALUE::RETVAL_OK;
}



// End of example implementational code

/*
 * Example implementational code for IDL interface ogata::StringNavigationCommanderService
 */
ogata_StringNavigationCommanderServiceSVC_impl::ogata_StringNavigationCommanderServiceSVC_impl() :
	m_currentPoseIn("currentPose", m_currentPose), m_mapServerPort("mapServer"), m_pathPlannerPort("pathPlanner"), m_pathFollowerPort("pathFollower")
{
  // Please add extra constructor code here.
}


ogata_StringNavigationCommanderServiceSVC_impl::~ogata_StringNavigationCommanderServiceSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
ogata::RETURN_VALUE ogata_StringNavigationCommanderServiceSVC_impl::move(const RTC::TimedPose2D& path)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
	#warning "Code missing in function <ogata::RETURN_VALUE ogata_StringNavigationCommanderServiceSVC_impl::move(const RTC::TimedPose2D& path)>"
#endif

		//	現在のロボットの位置を取得
		//if (m_currentPoseIn.isNew()) {
	  //	  m_currentPoseIn.read();
		//}

	  

	  
	  RTC::TimedPose2D currentPose = m_pRTC->getCurrentPose();
	  //	現在地と目的地が定まる
	  std::cout << "[RTC::StringCommander]	Current	Pose	=	(" << currentPose.data.position.x << ",	"
		  << currentPose.data.position.y << ",	" << currentPose.data.heading << ")" << std::endl;
	  
	  //	マップを要求する
	  RTC::OGMap_var outMap;		//	マップを格納するための変数
	  RTC::RETURN_VALUE	retval = m_pRTC->requestCurrentBuiltMap(outMap);
	  //RTC::RETURN_VALUE retval = m_pRTC->setMap(outMap);
	  if (retval == RTC::RETURN_VALUE::RETVAL_OK) {
		  std::cout << "[RTC::StringCommander]	Map	Request	OK." << std::endl;
	  }
	  else {
		  std::cout << "[RTC::StringCommander]	Map	Request	Unknown	Error	Code	=" << retval << std::endl;
		  return	ogata::RETURN_VALUE::RETVAL_UNKNOWN_ERROR;
	  }

	  //	軌道計画の為のパラメータを調整
	  RTC::PathPlanParameter	param;
	  param.map = outMap;	//	マップ
	  param.currentPose = this->m_currentPose.data;	//	スタート
	  RTC::Pose2D p;
	  p.position= currentPose.data.position;
	  p.heading = currentPose.data.heading;
	  param.currentPose = p;
	  RTC::Pose2D pose_;

	  // 目標座標を手前にする処理
	  RTC::Pose2D target_pose, v, changed_v, adjusted_target_pose, v2;
	  target_pose.position = path.data.position;
	  target_pose.heading = 0;
	  v.position.x = target_pose.position.x - param.currentPose.position.x;
	  v.position.y = target_pose.position.y - param.currentPose.position.y;
	  float s = std::sqrt(std::pow(v.position.x, 2) + std::pow(v.position.y, 2));
	  float duration = 0.6;
	  float ratio = (s - duration) / s;
	  changed_v.position.x = v.position.x * ratio;
	  changed_v.position.y = v.position.y * ratio;

	  adjusted_target_pose.position.x = changed_v.position.x + currentPose.data.position.x;
	  adjusted_target_pose.position.y = changed_v.position.y + currentPose.data.position.y;

	  v2.position.x = target_pose.position.x - adjusted_target_pose.position.x;
	  v2.position.y = target_pose.position.y - adjusted_target_pose.position.y;



	  //pose_.position = path.data.position;
	  pose_.position = adjusted_target_pose.position;
	  //pose_.heading = 0;
	  pose_.heading = std::atan2(v2.position.y, v2.position.x);
	  param.targetPose = pose_;	//	ゴール
	  std::cout << "[RTC::StringCommander]	Target	Pose				=	(" << target_pose.position.x << ",	"
		  << target_pose.position.y << ",	" << target_pose.heading << ")" << std::endl;
	  std::cout << "[RTC::StringCommander]	Goal	Pose				=	(" << param.targetPose.position.x << ",	"
		  << param.targetPose.position.y << ",	" << param.targetPose.heading << ")" << std::endl;
	  param.distanceTolerance = 1.0;	//	軌道からの位置のずれの許容差
	  param.headingTolerance = 1.0;	//	軌道からの角度のずれの許容差
	  param.maxSpeed.vx = 2.0;	param.maxSpeed.vy = 0.0;	param.maxSpeed.va = 1.0;	//	最大㏿度
	  param.timeLimit.sec = 9999;	param.timeLimit.nsec = 0;	//	許容時間
	  RTC::Path2D_var	outPath;	//	軌道を格納するための変数

	  //retval = m_pathPlanner->planPath(param, outPath);
	  retval = m_pRTC->planPath(param, outPath);
	  if (retval == RTC::RETURN_VALUE::RETVAL_OK) {	//	成功
		  std::cout << "[RTC::StringCommander]	Path	Plan	OK." << std::endl;
	  }
	  else if (retval == RTC::RETURN_VALUE::RETVAL_NOT_FOUND) {	//	見つからない
		  std::cout << "[RTC::StringCommander]	Path	Plan	No	Path	Found" << std::endl;
		  return	ogata::RETURN_VALUE::RETVAL_UNKNOWN_ERROR;
	  }
	  else {
		  std::cout << "[RTC::StringCommander]	Path	Plan	Unknown	Error	Code	=" << retval << std::endl;
		  return	ogata::RETURN_VALUE::RETVAL_UNKNOWN_ERROR;
	  }
	  //	軌道追従を要求．終了するまでfollowPathはブロックする
	  //retval = m_pathFollower->followPath(outPath);
	  retval = m_pRTC->pathFollow(outPath);
	  if (retval == RTC::RETURN_VALUE::RETVAL_OK) {	//	成功
		  std::cout << "[RTC::StringCommander]	Follow	OK." << std::endl;
		  return ogata::RETURN_VALUE::RETVAL_OK;
	  }
	  else {	//	失敗も通常終了
		  std::cout << "[RTC::StringCommander]	Follow	Unknown	Error	Code	=" << retval << std::endl;
		  return	ogata::RETURN_VALUE::RETVAL_UNKNOWN_ERROR;
	  }
	  return ogata::RETURN_VALUE::RETVAL_OK;
}



// End of example implementational code

/*
 * Example implementational code for IDL interface ogata::Picker
 */
ogata_PickerSVC_impl::ogata_PickerSVC_impl()
{
  // Please add extra constructor code here.
}


ogata_PickerSVC_impl::~ogata_PickerSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
ogata::RETURN_VALUE ogata_PickerSVC_impl::pick(const RTC::TimedString& kind)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <ogata::RETURN_VALUE ogata_PickerSVC_impl::pick(const RTC::TimedString& kind)>"
#endif
	  return ogata::RETURN_VALUE::RETVAL_OK;
}



// End of example implementational code

/*
 * Example implementational code for IDL interface ogata::Droper
 */
ogata_DroperSVC_impl::ogata_DroperSVC_impl()
{
  // Please add extra constructor code here.
}


ogata_DroperSVC_impl::~ogata_DroperSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
ogata::RETURN_VALUE ogata_DroperSVC_impl::drop(const RTC::TimedString& kind)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  #warning "Code missing in function <ogata::RETURN_VALUE ogata_DroperSVC_impl::drop(const RTC::TimedString& kind)>"
#endif
	  return ogata::RETURN_VALUE::RETVAL_OK;
}



// End of example implementational code



