#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int read_line(int fd, char* buf, int max){
	char c = 0;
	int i = 0;
	int flag = 0;
	while(c != '.'){
		if(read(fd, &c, 1) < 1)
			break;
		if((c == ' ' && i == 0))
			continue;
		buf[i] = c;
		if(c == '.'){
			flag = 1;
			break;
		}
		i++;
	}
	buf[i] = '\0';
	return flag? i : -1;
}


int
main(int argc, char *argv[])
{
	//////////////////////////////////////
		// loading shared memory
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
	//////////////////////////////////////
	
	int fd = open("../home/README", O_RDONLY);
	if(fd <= 0){
		printf("Error opening file\n");
		exit();
	}
	int should_continue = 1;
	
	while(1){
		if((*(int *) cmd) == 3){ // cmd == 3 means resume
			should_continue = 1;
		}
		if(*(int *) cmd == 2)	// cmd == 2 means pause
			should_continue = 0;
		
		if(should_continue){
			sleep(100);
			char buf[1000] = {};
			if(read_line(fd, buf, sizeof(buf)) <= 0)
				break;
								
			*(int *)line_num = (*(int *)line_num) + 1;
			char word[100] = {};
			int maxi = 0;
			int mini = 100;
			int wi = 0;
			char temp_s[100] = {};
			char temp_l[100] = {};

			char temp_ss[100] = {};
			char temp_ll[100] = {};
			///////////////////////////////////////////
			// sentence analysis
			for(int i = 0; i < strlen(buf); i++){
				if(buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n' || buf[i] == '\r'){
					word[wi] = '\0';
					wi = 0;
					if(strlen(word) > maxi){
						maxi = strlen(word);
						strcpy(temp_l, word);
						if(strlen(word) > strlen((char *)longest_word))
							strcpy(temp_ll, word);
					}
					if(strlen(word) < mini && strlen(word) > 0 && word[0] != '\0' && word[0] != ' ' && word[0] != '\t' && word[0] != '\n' && word[0] != '\r'){
						mini = strlen(word);
						strcpy(temp_s, word);
						if(strlen(word) < strlen((char *)shortest_word) || strlen((char *)shortest_word) == 0)
							strcpy(temp_ss, word);
					}
					continue;
				}
				word[wi++] = buf[i];
			}
			word[wi] = '\0';
			if(strlen(word) > maxi){
				maxi = strlen(word);
				strcpy(temp_l, word);
				if(strlen(word) > strlen((char *)longest_word))
					strcpy(temp_ll, word);
			}
			if(strlen(word) < mini && strlen(word) > 0 && word[0] != '\0' && word[0] != ' ' && word[0] != '\t' && word[0] != '\n' && word[0] != '\r'){
				mini = strlen(word);
				strcpy(temp_s, word);
				if(strlen(word) < strlen((char *)shortest_word) || strlen((char *)shortest_word) == 0)
					strcpy(temp_ss, word);
			}
			


			memmove((char *)lps, temp_l, 100*sizeof(char));
			memmove((char *)sps, temp_s, 100*sizeof(char));
			if(strlen(temp_ll) > *(int *)longest_word){
				*(int *) longest_word = strlen(temp_ll);
				memmove((char *)longest, temp_ll, 100*sizeof(char));
			}
			if(strlen(temp_ss) < *(int *)shortest_word && strlen(temp_ss) > 0){
				*(int *) shortest_word = strlen(temp_ss);
				memmove((char *)shortest, temp_ss, 100*sizeof(char));
			}
			///////////////////////////////////
		}
		if(*(int *) cmd == 4){ // cmd == 4 means end
			printf("Ending...\n");
			break;
		}
		sleep(7);
	}
	close(fd);
	printf("Done analyzing file\n");
	exit();
}
