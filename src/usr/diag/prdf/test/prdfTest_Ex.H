/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/usr/diag/prdf/test/prdfTest_Ex.H $                        */
/*                                                                        */
/* OpenPOWER HostBoot Project                                             */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2012,2014              */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
#ifndef __TEST_PRDFEXTEST_H
#define __TEST_PRDFEXTEST_H

#ifdef __HOSTBOOT_MODULE
  #include <cxxtest/TestSuite.H>
  #include <errl/errlentry.H>
  #include <errl/errlmanager.H>
#else
  #include <cxxtest/TestSuite.h>
  #include <fsp/FipsGlobalFixture.H>
  #include <errlentry.H>
#endif

#include <prdfTrace.H>
#include <prdfMain.H>
#include "prdfsimMacros.H"
#include "prdfsimMfgSync.H"
#include <prdfGlobal.H>
#include <prdfErrlUtil.H>

class ExLFIR:public CxxTest::TestSuite
{
    public:

        void TestRecoverable(void)
        {
            PRDS_BEGIN("EXLFIR recoverable attention");
            PRDS_ERROR_ENTRY("NODE{0}:PROC{0}", PRDF::RECOVERABLE);
            PRDS_EXPECTED_SIGNATURE("NODE{0}:PROC{0}:EX{5}", 0xb53a0007);
            // GLOBAL_RE_FIR set bit 21
            PRDS_SCR_WRITE("NODE{0}:PROC{0}", 0x570F001B, 0x0000040000000000);
            // EX_CHIPLET_RE_FIR[1] Attention from EXLFIR
            PRDS_SCR_WRITE("NODE{0}:PROC{0}:EX{5}", 0x10040001, 0x4000000000000000);
            // set EXLFIR[7]
            PRDS_SCR_WRITE("NODE{0}:PROC{0}:EX{5}", 0x1004000a, 0x0100000000000000);
            // EXLFIR_ACT1
            PRDS_SCR_WRITE("NODE{0}:PROC{0}:EX{5}", 0x10040011, 0xFFFFFFFFFFFFFFFF);
            PRDS_START_SIM();
            if(!(PRDS_END()))
            {
                TS_FAIL("Expected Signature Failed EXLFIR recoverable attention");
            }
        }

        void TestL3CE(void)
        {

            PRDS_BEGIN("L3CE Test");
            PRDS_ERROR_ENTRY("NODE{0}:PROC{0}", PRDF::RECOVERABLE);
            PRDS_EXPECTED_SIGNATURE("NODE{0}:PROC{0}:EX{4}", 0xc6b00004);
            // GLOBAL_RE_FIR bit 20
            PRDS_SCR_WRITE("NODE{0}:PROC{0}", 0x570F001B, 0x0000080000000000);
            // EX_CHIPLET_RE_FIR[4] - Analyze L3FIR
            PRDS_SCR_WRITE("NODE{0}:PROC{0}:EX{4}", 0x10040001, 0x0800000000000000);
            // EX_L3FIR
            PRDS_SCR_WRITE("NODE{0}:PROC{0}:EX{4}", 0x10010800, 0x0800000000000000);
            // EX_L3FIR_ACT1
            PRDS_SCR_WRITE("NODE{0}:PROC{0}:EX{4}", 0x10010807, 0x0800000000000000);
            PRDS_START_SIM();
            if(!(PRDS_END()))
            {
                TS_FAIL("L3CE Test failed");
            }
        }
};
#endif
