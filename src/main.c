/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic Input demo -- reads from control pad and indicates button
 *          presses.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Donour Sizemore <donour@uchicago.edu>
 *
 */
#include <dxlibp.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <psphttp.h>
#include <pspkernel.h>
#include <pspnet.h>
#include <pspsdk.h>
#include <psputility_netmodules.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PSP_MODULE_INFO("TEST", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

void dump_threadstatus(void);
void screen_setting(void);
int net_setting(void);

int done = 0;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
  done = 1;
  return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
  int cbid;

  cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();

  return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
  int thid = 0;

  thid =
      sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
  if (thid >= 0) {
    sceKernelStartThread(thid, 0, 0);
  }

  return thid;
}

int main() {
  SetupCallbacks();
  DxLib_Init();
  screen_setting();
  ClearDrawScreen();
  int status = net_setting();
  DrawFormatString(0, 0, DXP_COLOR_WHITE, "status: %d", status);
  int template = sceHttpCreateTemplate("psp", 1, 0);
  DrawFormatString(0, 12, DXP_COLOR_WHITE, "template: %d", template);
  sceHttpSetResolveTimeOut(template, 3 * 1000 * 1000);
  sceHttpSetRecvTimeOut(template, 0x3938700);
  sceHttpSetSendTimeOut(template, 0x3938700);
  int connection = sceHttpCreateConnectionWithURL(
      template, "http://www.ppsspp.org/test.txt", 0);
  DrawFormatString(0, 24, DXP_COLOR_WHITE, "connection: %d", connection);
  int request = sceHttpCreateRequestWithURL(
      connection, PSP_HTTP_METHOD_GET, "http://www.ppsspp.org/test.txt", 0);
  DrawFormatString(0, 36, DXP_COLOR_WHITE, "request: %d", request);
  status = sceHttpSendRequest(request, NULL, 0);
  DrawFormatString(0, 48, DXP_COLOR_WHITE, "send status: %d", status);
  int status_code = 0;
  status = sceHttpGetStatusCode(request, &status_code);
  DrawFormatString(0, 60, DXP_COLOR_WHITE, "send status2: %d", status);
  DrawFormatString(0, 72, DXP_COLOR_WHITE, "status_code: %d", status_code);
  ScreenFlip();
  while (ProcessMessage() != -1) {
    /*
    ClearDrawScreen();
    DrawFormatString(0, 0, DXP_COLOR_WHITE, "%d", status_code);
    ScreenFlip();
    */
  }
  DxLib_End();
  return 0;
}
