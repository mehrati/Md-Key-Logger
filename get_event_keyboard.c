
#include <stdio.h>
#include <string.h>
#include "get_event_keyboard.h"

int get_path_keyboard(char *path)
{

	FILE *devices;
	char events[128];
	char handlers[128];
	char *handler_selected;
	char event_selected[128];

	char h_path[] = "/dev/input/";

	devices = fopen("/proc/bus/input/devices", "r");

	if (!devices) {
		perror("fopen");
		return -1;
	}

	while (fgets(events, sizeof(events), devices)) {
		if (strstr(events, "H: Handlers=") == events)
		{
			strcpy(handlers, events);
		}else if (!strcmp(events, "B: EV=120013\n")){

			handler_selected = strstr(handlers, "event");

			for(int i=0;i<=strlen("event");i++)

				event_selected[i] = handler_selected[i];

			return snprintf(path, ( sizeof (h_path)+ sizeof(event_selected)), "%s", strcat(h_path, event_selected));
		}
	}

	return -1;
}
