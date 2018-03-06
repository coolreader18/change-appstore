
#include <easy/easy.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/fs_functions.h"
#include "dynamic_libs/gx2_functions.h"
#include "dynamic_libs/sys_functions.h"
#include "dynamic_libs/vpad_functions.h"
#include "dynamic_libs/padscore_functions.h"
#include "dynamic_libs/socket_functions.h"
#include "dynamic_libs/ax_functions.h"
#include "fs/fs_utils.h"
#include "fs/sd_fat_devoptab.h"
#include "system/memory.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "common/common.h"
#include "keyboard.h"

int Menu_Main(void) {
  FILE * fp;
  fp = fopen("sd:/wiiu/apps/appstore/repository.txt", "w");

  printf(
    "Welcome to the HBL Appstore Repository Changer. Press a button to choose which repository to switch to.\n"
  );
  printf("A - Wiiubru (default) \n");
  printf("B - Utools \n");
  printf("X - Wii U Utilities \n");
  printf("Y - vgmoose \n");
  printf("Home - exit application \n");

  void changeRepo(char url[32], int button) {
    fp = freopen("sd:/wiiu/apps/appstore/repository.txt", "w", fp);
    fprintf(fp, url);
    printf("Changed repository to %s \n", url);
    if (button)
      while (1) {
        update_buttons();
        if (!button_pressed(button)) break;
      }
  }

  while (1) {
    update_buttons();

    if (button_pressed(VPAD_BUTTON_HOME)) break;
    if (button_pressed(VPAD_BUTTON_A)) {
      changeRepo("http://wiiubru.com/appstore", VPAD_BUTTON_R);
    }
    if (button_pressed(VPAD_BUTTON_B)) {
      changeRepo("http://coc4tm.github.io/Utools/web/", VPAD_BUTTON_B);
    }
    if (button_pressed(VPAD_BUTTON_X)) {
      changeRepo("http://wiiu.3utilities.com", VPAD_BUTTON_X);
    }
    if (button_pressed(VPAD_BUTTON_Y)) {
      changeRepo("http://hbas.vgmoose.com", VPAD_BUTTON_Y);
    }
    if (button_pressed(VPAD_BUTTON_R)) {
      InitOSFunctionPointers();
      InitVPadFunctionPointers();
      memory_init();

      OSScreenInit();
      //Grab the buffer size for each screen (TV and gamepad)
      int buf0_size = OSScreenGetBufferSizeEx(0);
      int buf1_size = OSScreenGetBufferSizeEx(1);
      //Set the buffer area.
      OSScreenSetBufferEx(0, (void *)0xF4000000);
      OSScreenSetBufferEx(1, (void *)0xF4000000 + buf0_size);
      //Clear both framebuffers.
      for (int i = 0; i < 2; i++) {
        fillScreen(0, 0, 0, 0);
        flipBuffers();
      }
      OSScreenEnableEx(0, 1);
      OSScreenEnableEx(1, 1);
      char returnedString[256];
      launchKeyboard(&returnedString);
      fp = freopen("sd:/wiiu/apps/appstore/repository.txt", "w", fp);
      fprintf(fp, returnedString);
      printf("Changed repository to custom url \n");
    }
  }

  // Display the exit message
  printf("Exiting...\n");

  fclose(fp);

  // Return
  return 0;
}
