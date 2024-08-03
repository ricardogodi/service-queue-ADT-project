
#include <stdio.h>
#include <stdlib.h>
#include "sq.h"

/**
* takes a full line of user input and 
*   parses it.
*
* Executes specified command and prints appropriate
*   message if syntactially correct.
*   otherwise prints an error message.
*
* Returns 1 only to indicate the the quite command 'q' was 
*   entered.
* Otherwise, 0 is returned.
*/
int execute_cmd(SQ *q, char *buf) {
int tok;
char cmd;
int buzzer;
char junk[128];

  tok = sscanf(buf, " %c %i %s", &cmd, &buzzer, junk);

  if(tok==0) return 0;
  if(tok > 2){
	printf("    bad command. try again\n");
	return 0;
  }

  switch (cmd) {
	case 'q':
		if(tok != 1){
		  printf("    bad command. try again\n");
		  return 0;
		}
		else{
		  printf("  goodbye...\n");
		  return 1;
		}
	case 'd' : 
		if(tok != 1)
		  printf("    bad command. try again\n");
		else
		  sq_display(q);
		return 0;
	case 'l':
		if(tok != 1)
		  printf("    bad command. try again\n");
		else
		  printf("  len: %i\n", sq_length(q));
		return 0;
	case 'g':
		if(tok != 1)
		  printf("    bad command. try again\n");
		else
		  printf("  buzzer: %i\n", sq_give_buzzer(q));
		return 0;
	case 's':
		if(tok != 1)
		  printf("    bad command. try again\n");
		else
		  printf("  serving buzzer: %i\n", sq_seat(q));
		return 0;
	case 'k':
		if(tok != 2)
		  printf("    bad command. try again\n");
		else {
		  if(sq_kick_out(q, buzzer)) 
			printf("  %i is outta here!\n", buzzer);
		  else 
			printf("  could not remove tkt %i!\n", buzzer);
		}
		return 0;
	case 'b':
		if(tok != 2)
		  printf("    bad command. try again\n");
		else {
		  if(sq_take_bribe(q, buzzer)) 
			printf("  VIP coming through!\n");
		  else 
			printf("  Get in line, then bribe me!\n");

		}
		return 0;
	default:
	    printf("    bad command. try again\n");
	    return 0;
  }
}
	




int main() {
SQ *q = sq_create();
char buf[128];
int done = 0;


  printf("\nWelcome to the simple service-queue interactive program\n");
  printf("   An empty service queue has been created for you\n");
  printf("   Commands:\n");
  printf("    d          : display queue\n");
  printf("    l          : report length of queue\n");
  printf("    g          : give out a buzzer\n");
  printf("    s          : serve the first buzzer in line\n");
  printf("    k <buzzer> : kick specified buzzer out!\n");
  printf("    b <buzzer> : take a bribe to move specified buzzer to front!\n");
  printf("    q          : quit\n");
  printf("-----------------------------------\n\n");
  

  while(!done) {
	printf("cmd > ");
	if(fgets(buf, 127, stdin) != NULL) {
	    if(execute_cmd(q, buf))
		done = 1;
	}
  }
  sq_free(q);
  return 0;
}




