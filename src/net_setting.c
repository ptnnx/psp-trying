#include <pspkernel.h>
#include <pspnet.h>
#include <pspnet_apctl.h>
#include <pspnet_inet.h>
#include <pspnet_resolver.h>
#include <psputility_netmodules.h>
#include <psphttp.h>

int net_setting() {
  int result;
  result = sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
  if (result < 0) return 1;
  result = sceUtilityLoadNetModule(PSP_NET_MODULE_INET);
  if (result < 0) return 2;
  result = sceUtilityLoadNetModule(PSP_NET_MODULE_PARSEHTTP);
  if (result < 0) return 3;
  result = sceUtilityLoadNetModule(PSP_NET_MODULE_PARSEURI);
  if (result < 0) return 4;
  result = sceUtilityLoadNetModule(PSP_NET_MODULE_HTTP);
  if (result < 0) return 5;
  result = sceNetInit(128 * 1024, 42, 4 * 1024, 42, 4 * 1024);
  if (result < 0) return 6;
  result = sceNetInetInit();
  if (result < 0) return 7;
  result = sceNetResolverInit();
  if (result < 0) return 8;
  result = sceNetApctlInit(0x10000, 0x30);
  if (result < 0) return 9;
  result = sceHttpInit(20000);
  if (result < 0) return 10;
  return (1);
}
