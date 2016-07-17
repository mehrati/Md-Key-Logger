#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>




void log_time_now(char *timestring){
    
    time_t rawtime;
    time( &rawtime );
    sprintf(timestring,"\n*************************\n\n %s \n*************************\n", ctime( &rawtime ));
   
    return ;

}

int get_hour_now(){

       time_t rawtime;
       time( &rawtime );
       int int_hour=0;
       char str_hour[3];
       strftime(str_hour,3,"%H", localtime( &rawtime ));
       int_hour=atoi(str_hour);

     return int_hour;
}

    

    

	
