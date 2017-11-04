#include <easy/easy.h>
#include <stdio.h>

int Menu_Main(void)
{
	FILE *fp;
	fp = fopen("sd:/wiiu/apps/appstore/repository.txt", "w");

	printf("Welcome to the HBL Appstore Repository Changer. Press a button to choose which repository to switch to.\n");
	printf("A - Wiiubru (default) \n");
	printf("B - Utools \n");
	printf("X - Wii U Utilities \n");
	printf("Y - vgmoose \n");
	printf("Home - exit application \n");

	// Wait for the user to press the Home Button
	while(1)
	{
		update_buttons();

		if (button_pressed(VPAD_BUTTON_HOME))
			break;

		if (button_pressed(VPAD_BUTTON_A)){
			fp = freopen("sd:/wiiu/apps/appstore/repository.txt", "w", fp);
			fprintf(fp, "http://wiiubru.com/appstore");
			printf("Changed repository to http://wiiubru.com/appstore \n");
			while(1) {
				update_buttons();
				if (!button_pressed(VPAD_BUTTON_A))
					break;
			}
		}
		if (button_pressed(VPAD_BUTTON_B)){
			fp = freopen("sd:/wiiu/apps/appstore/repository.txt", "w", fp);
			fprintf(fp,"http://coc4tm.github.io/Utools/web/");
			printf("Changed repository to http://coc4tm.github.io/utools/web \n");
			while(1) {
				update_buttons();
				if (!button_pressed(VPAD_BUTTON_B))
					break;
			}
		}
		if (button_pressed(VPAD_BUTTON_X)){
			fp = freopen("sd:/wiiu/apps/appstore/repository.txt", "w", fp);
			fprintf(fp, "http://wiiu.3utilities.com");
			printf("Changed repository to http://wiiu.3utilities.com \n");
			while(1) {
				update_buttons();
				if (!button_pressed(VPAD_BUTTON_X))
					break;
			}
		}
		if (button_pressed(VPAD_BUTTON_Y)){
			fp = freopen("sd:/wiiu/apps/appstore/repository.txt", "w", fp);
			fprintf(fp, "http://hbas.vgmoose.com");
			printf("Changed repository to http://hbas.vgmoose.com \n");
			while(1) {
				update_buttons();
				if (!button_pressed(VPAD_BUTTON_Y))
					break;
			}
		}
	}

	// Display the exit message
	printf("Exiting...\n");

	fclose(fp);

	// Return
	return 0;
}
