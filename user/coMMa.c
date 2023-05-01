#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

void commands(){
	printf("Commands:\n");
	printf("0 (>_<)=> latest\n");
	printf("1 (>_<)=> global extrema\n");
	printf("2 (>_<)=> pause\n");
	printf("3 (>_<)=> resume\n");
	printf("4 (>_<)=> end\n");
}


int
main(int argc, char *argv[])
{

	commands();
		//////////////////
		// loading shared memory
		void *line_num;
		void *lps;
		void *sps;
		void *longest_word;
		void *shortest_word;
		void *cmd;
		void *longest;
		void *shortest;

		get_shared("line_num", &line_num);
		get_shared("lps", &lps);
		get_shared("longest_word", &longest_word);
		get_shared("sps", &sps);
		get_shared("shortest_word", &shortest_word);
		get_shared("shortest", &shortest);
		get_shared("cmd", &cmd);
		get_shared("longest", &longest);
		//////////////////

	while(1){
		char command[100] = {};
		gets(command, 100);
	

		if(strcmp(command, "latest\n") == 0){
			*(int *) cmd = 0;
			printf("Latest sentence %d: Local extrema -> longest: %s || shortest: %s\n", *(int *) line_num, (char *) lps, (char *) sps);
		}
		else if(strcmp(command, "global extrema") == 0 || strcmp(command, "global extrema\n") == 0){	
			*(int *) cmd = 1;
			printf("Global extrema -> longest <%d>: %s || shortest <%d>: %s\n", *(int *)longest_word,(char *) longest, *(int *)shortest_word, (char *) shortest);
		}
		else if(strcmp(command, "pause\n") == 0){
			printf("Pausing...\n");
			*(int *) cmd = 2;
		}
		else if(strcmp(command, "resume\n") == 0){
			printf("Resuming...\n");
			*(int *) cmd = 3;
		}
		else if(strcmp(command, "end\n") == 0){
			*(int *) cmd = 4;
			break;
		}else{
			printf("Unknown command\n");
			commands();
		}
		
	}
	exit();
}
