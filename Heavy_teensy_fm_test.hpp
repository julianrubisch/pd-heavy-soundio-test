/**
 * Copyright (c) 2018 Enzien Audio, Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the phrase "powered by heavy",
 *    the heavy logo, and a hyperlink to https://enzienaudio.com, all in a visible
 *    form.
 * 
 *   2.1 If the Application is distributed in a store system (for example,
 *       the Apple "App Store" or "Google Play"), the phrase "powered by heavy"
 *       shall be included in the app description or the copyright text as well as
 *       the in the app itself. The heavy logo will shall be visible in the app
 *       itself as well.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef _HEAVY_CONTEXT_TEENSY_FM_TEST_HPP_
#define _HEAVY_CONTEXT_TEENSY_FM_TEST_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvSignalLine.h"
#include "HvSignalSamphold.h"
#include "HvControlBinop.h"
#include "HvControlDelay.h"
#include "HvControlSystem.h"
#include "HvSignalVar.h"
#include "HvSignalPhasor.h"
#include "HvControlVar.h"
#include "HvMath.h"
#include "HvControlCast.h"
#include "HvSignalDel1.h"

class Heavy_teensy_fm_test : public HeavyContext {

 public:
  Heavy_teensy_fm_test(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_teensy_fm_test();

  const char *getName() override { return "teensy_fm_test"; }
  int getNumInputChannels() override { return 0; }
  int getNumOutputChannels() override { return 2; }

  int process(float **inputBuffers, float **outputBuffer, int n) override;
  int processInline(float *inputBuffers, float *outputBuffer, int n) override;
  int processInlineInterleaved(float *inputBuffers, float *outputBuffer, int n) override;

  int getParameterInfo(int index, HvParameterInfo *info) override;

 private:
  HvTable *getTableForHash(hv_uint32_t tableHash) override;
  void scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) override;

  // static sendMessage functions
  static void cMsg_EoZBJLGp_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_7tPFFf8N_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cCast_zWTUefKK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_g2I8F8KP_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_fqotxGQ1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_47r53SWV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_klRwaQQQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_j2IP4ySS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_XOvEkmlO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_rU5iOuGd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_MOQ4377W_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_O80BBgT6_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_b7YjCjhG_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_XYdnemeC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_JSnSxTFV_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_9SzqL1gd_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_HUIufVFe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_FHsSO0kW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_p47RQpQu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_raMdFwMU_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_wYAvAcqG_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_QgzZRyzN;
  SignalPhasor sPhasor_4Lvkrv57;
  SignalPhasor sPhasor_dr6zUHPQ;
  SignalPhasor sPhasor_aBZYyVz7;
  SignalDel1 sDel1_tyj7XQqW;
  SignalSamphold sSamphold_6MyFH8oD;
  SignalPhasor sPhasor_GJqJE1qw;
  SignalLine sLine_mAPEYSqZ;
  ControlDelay cDelay_g2I8F8KP;
  ControlVar cVar_47r53SWV;
  ControlBinop cBinop_klRwaQQQ;
  ControlBinop cBinop_JSnSxTFV;
  ControlBinop cBinop_HUIufVFe;
  ControlBinop cBinop_FHsSO0kW;
  ControlDelay cDelay_raMdFwMU;
  ControlVar cVar_wYAvAcqG;
};

#endif // _HEAVY_CONTEXT_TEENSY_FM_TEST_HPP_
