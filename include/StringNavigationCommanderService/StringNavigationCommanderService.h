﻿// -*- C++ -*-
/*!
 * @file  StringNavigationCommanderService.h
 * @brief ModuleDescription
 * @date  $Date$
 *
 * $Id$
 */

#ifndef STRINGNAVIGATIONCOMMANDERSERVICE_H
#define STRINGNAVIGATIONCOMMANDERSERVICE_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">
#include "TidyUpManagerSVC_impl.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "MobileRobotStub.h"
#include "ExtendedDataTypesStub.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

using namespace RTC;

/*!
 * @class StringNavigationCommanderService
 * @brief ModuleDescription
 *
 */

namespace ogata_lab {
	class StringNavigationCommanderService
		: public RTC::DataFlowComponentBase
	{
	public:
		/*!
		 * @brief constructor
		 * @param manager Maneger Object
		 */
		StringNavigationCommanderService(RTC::Manager* manager);

		/*!
		 * @brief destructor
		 */
		~StringNavigationCommanderService();

		// <rtc-template block="public_attribute">

		// </rtc-template>

		// <rtc-template block="public_operation">

		// </rtc-template>

		/***
		 *
		 * The initialize action (on CREATED->ALIVE transition)
		 * formaer rtc_init_entry()
		 *
		 * @return RTC::ReturnCode_t
		 *
		 *
		 */
		virtual RTC::ReturnCode_t onInitialize();

		/***
		 *
		 * The finalize action (on ALIVE->END transition)
		 * formaer rtc_exiting_entry()
		 *
		 * @return RTC::ReturnCode_t
		 *
		 *
		 */
		 // virtual RTC::ReturnCode_t onFinalize();

		 /***
		  *
		  * The startup action when ExecutionContext startup
		  * former rtc_starting_entry()
		  *
		  * @param ec_id target ExecutionContext Id
		  *
		  * @return RTC::ReturnCode_t
		  *
		  *
		  */
		  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

		  /***
		   *
		   * The shutdown action when ExecutionContext stop
		   * former rtc_stopping_entry()
		   *
		   * @param ec_id target ExecutionContext Id
		   *
		   * @return RTC::ReturnCode_t
		   *
		   *
		   */
		   // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

		   /***
			*
			* The activated action (Active state entry action)
			* former rtc_active_entry()
			*
			* @param ec_id target ExecutionContext Id
			*
			* @return RTC::ReturnCode_t
			*
			*
			*/
			 virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

			/***
			 *
			 * The deactivated action (Active state exit action)
			 * former rtc_active_exit()
			 *
			 * @param ec_id target ExecutionContext Id
			 *
			 * @return RTC::ReturnCode_t
			 *
			 *
			 */
			  virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

			 /***
			  *
			  * The execution action that is invoked periodically
			  * former rtc_active_do()
			  *
			  * @param ec_id target ExecutionContext Id
			  *
			  * @return RTC::ReturnCode_t
			  *
			  *
			  */
			   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

			  /***
			   *
			   * The aborting action when main logic error occurred.
			   * former rtc_aborting_entry()
			   *
			   * @param ec_id target ExecutionContext Id
			   *
			   * @return RTC::ReturnCode_t
			   *
			   *
			   */
			   // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

			   /***
				*
				* The error action in ERROR state
				* former rtc_error_do()
				*
				* @param ec_id target ExecutionContext Id
				*
				* @return RTC::ReturnCode_t
				*
				*
				*/
				// virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

				/***
				 *
				 * The reset action that is invoked resetting
				 * This is same but different the former rtc_init_entry()
				 *
				 * @param ec_id target ExecutionContext Id
				 *
				 * @return RTC::ReturnCode_t
				 *
				 *
				 */
				 // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);

				 /***
				  *
				  * The state update action that is invoked after onExecute() action
				  * no corresponding operation exists in OpenRTm-aist-0.2.0
				  *
				  * @param ec_id target ExecutionContext Id
				  *
				  * @return RTC::ReturnCode_t
				  *
				  *
				  */
				  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

				  /***
				   *
				   * The action that is invoked when execution context's rate is changed
				   * no corresponding operation exists in OpenRTm-aist-0.2.0
				   *
				   * @param ec_id target ExecutionContext Id
				   *
				   * @return RTC::ReturnCode_t
				   *
				   *
				   */
				   // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


	protected:
		// <rtc-template block="protected_attribute">

		// </rtc-template>

		// <rtc-template block="protected_operation">

		// </rtc-template>

		// Configuration variable declaration
		// <rtc-template block="config_declare">

		// </rtc-template>

		// DataInPort declaration
		// <rtc-template block="inport_declare">
		RTC::TimedPose2D m_currentPose;
		/*!
		 */
		InPort<RTC::TimedPose2D> m_currentPoseIn;

		// </rtc-template>


		// DataOutPort declaration
		// <rtc-template block="outport_declare">

		// </rtc-template>

		// CORBA Port declaration
		// <rtc-template block="corbaport_declare">
		/*!
		 */
		RTC::CorbaPort m_StringNavigationManagerServicePort;
		/*!
		 */
		RTC::CorbaPort m_mapServerPort;
		/*!
		 */
		RTC::CorbaPort m_pathPlannerPort;
		/*!
		 */
		RTC::CorbaPort m_pathFollowerPort;

		// </rtc-template>

		// Service declaration
		// <rtc-template block="service_declare">
		/*!
		 */
		ogata_StringNavigationCommanderServiceSVC_impl m_StringNavigationManagerService;

		// </rtc-template>

		// Consumer declaration
		// <rtc-template block="consumer_declare">
		/*!
		 */
		RTC::CorbaConsumer<RTC::OGMapServer> m_mapServer;
		/*!
		 */
		RTC::CorbaConsumer<RTC::PathPlanner> m_pathPlanner;
		/*!
		 */
		RTC::CorbaConsumer<RTC::PathFollower> m_pathFollower;

		// </rtc-template>

	private:
		// <rtc-template block="private_attribute">

		// </rtc-template>

		// <rtc-template block="private_operation">

		// </rtc-template>

	public:

		/// このメソッドの名前を変更。
		/// RTC本体を通してサービスポートを呼ぶのは正解
		RTC::RETURN_VALUE requestCurrentBuiltMap(RTC::OGMap_var& outmap) {
			return m_mapServer->requestCurrentBuiltMap(outmap);
		}

		RTC::RETURN_VALUE planPath(RTC::PathPlanParameter& param, RTC::Path2D_var& outPath) {
			return m_pathPlanner->planPath(param, outPath);
		}

		RTC::RETURN_VALUE pathFollow(RTC::Path2D_var& outPath) {
			return m_pathFollower->followPath(outPath);
		}

		/// 現在の位置データを保存するための変数。onExecuteでこの変数に最新データを代入しておく。
		RTC::TimedPose2D m_currentPoseBuffer;

		/// 現在の位置データを取得するための関数。このままだとonExecuteで最新データが代入する前に呼ばれるとエラーになる可能性がある。
		RTC::TimedPose2D getCurrentPose() {
			return m_currentPoseBuffer;
		}
		
	};


}


extern "C"
{
	DLL_EXPORT void StringNavigationCommanderServiceInit(RTC::Manager* manager);
};

#endif // STRINGNAVIGATIONCOMMANDERSERVICE_H

