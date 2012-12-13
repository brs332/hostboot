/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/usr/hwpf/hwp/dram_training/mss_draminit_trainadv/mss_draminit_training_advanced.H $ */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2012                   */
/*                                                                        */
/* p1                                                                     */
/*                                                                        */
/* Object Code Only (OCO) source materials                                */
/* Licensed Internal Code Source Materials                                */
/* IBM HostBoot Licensed Internal Code                                    */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* Origin: 30                                                             */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
// $Id: mss_draminit_training_advanced.H,v 1.13 2012/12/06 11:13:42 lapietra Exp $
/* File is created by SARAVANAN SETHURAMAN on Thur Sept 28 2011. */

//------------------------------------------------------------------------------
// *! (C) Copyright International Business Machines Corp. 2007
// *! All Rights Reserved -- Property of IBM
// *! *** IBM Confidential ***
//------------------------------------------------------------------------------
// *! TITLE :mss_draminit_training_advanced.H
// *! DESCRIPTION : Tools for centaur procedures
// *! OWNER NAME : SARAVANAN SETHURAMAN         email id: saravanans@in.ibm.com
// *! BACKUP NAME :MARK D BELLOWS		email id: bellows@us.ibm.com
// #! ADDITIONAL COMMENTS :
//
// General purpose funcs

//------------------------------------------------------------------------------
// Don't forget to create CVS comments when you check in your changes!
//------------------------------------------------------------------------------
// CHANGE HISTORY:
//------------------------------------------------------------------------------
// Version:|  Author:  |  Date:   | Comment:
//---------|---------- |--------- |-----------------------------------------------
//  1.0    | 28-Sep-11 | sasethur | First drop of Centaur
//  1.1    | 18-Nov-11 | sasethur | Added typedef and comment update
//  1.2    | 13-Feb-12 | sasethur | Updated scom address naming convention
//  1.9    | 16-Jul-12 | bellows  | Added in Id tag
//  1.10   | 15-Oct-12 | sasethur | Updated user option  
//  1.11   | 26-Oct-12 | sasethur | Updated fapi:: and const Target & for HB environment
//  1.12   | 15-Nov-12 | sasethur | Updated fw review comments
//  1.13   | 07-Dec-12 | sasethur | Updated for fw review in comment section


#ifndef _MSS_DRAMINIT_TRAINING_ADVANCED_H
#define _MSS_DRAMINIT_TRAINING_ADVANCED_H

//----------------------------------------------------------------------
//  Includes
//----------------------------------------------------------------------
#include <fapi.H>

typedef fapi::ReturnCode (*mss_draminit_training_advanced_FP_t)(const fapi::Target &,uint8_t i_pattern,uint8_t i_test_type);


extern "C"
{
/**
* @brief Draminit training advanced procedure shmoo's drv_impedance, slew, vref and receiver impedance and get the optimum value 
*
* @param[in] i_target Reference to target
* i_pattern  To enable patterns for mcbist used in lab/debug mode - user option
* i_test_type  To enable test types for mcbist used in lab/debug mode - user option
* @return ReturnCode
*/

fapi::ReturnCode mss_draminit_training_advanced(const fapi::Target & i_target_mba,uint8_t i_pattern,uint8_t i_test_type);

} // extern C

#endif// _MSS_DRAMINIT_TRAINING_ADVANCED_H 