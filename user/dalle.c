#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"


int
main(int argc, char *argv[])
{
	// RN - 2023
	int line_num = 0;
	char * lps = malloc(100 * sizeof(char));
	int longest_word = 0;
	char * sps = malloc(100 * sizeof(char));
	int shortest_word = 1000;
	char * longest = malloc(100 * sizeof(char));
	int cmd = 0;
	char * shortest = malloc(100 * sizeof(char));


	share_mem("line_num", &line_num, sizeof(line_num));
	share_mem("lps", lps, 100*sizeof(char));
	share_mem("longest_word", &longest_word,sizeof(longest_word));
	share_mem("sps", sps, 100*sizeof(char));
	share_mem("shortest_word", &shortest_word,sizeof(shortest_word));
	share_mem("shortest", shortest, 100*sizeof(char));
	share_mem("cmd", &cmd, sizeof(cmd));
	share_mem("longest", longest, 100*sizeof(char));


	//////////////////////////

	int pid = fork();

	if(pid == 0){
		char *argv2[] = {"/bin/liSa", 0};
		exec("/bin/liSa", argv2);
	}else{
		int pid2 = fork();
		if(pid2 == 0){
			char *argv3[] = {"/bin/coMMa", 0};
			exec("/bin/coMMa", argv3);
		}else{
			wait();	
			wait();
		}
	}
	exit();
}
