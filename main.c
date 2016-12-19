/* Program to convert an IP address to base 10 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <locale.h>
#include <regex.h>

#define IPEXPR "([0-9]{1-3})\\.([0-9]{1-3})\\.([0-9]{1-3})\\.([0-9]{1-3})"
#define VERSION "1.0"

void print_help(int exitVal);
void print_version(int exitVal);

int main(int argc, char *argv[]){
	regex_t re;
	int opt = 0;
	int print_flag = 0;
	long unsigned int result = 0;
int var1 = 0, var2 = 0,
	var3 = 0, var4 = 0;

if (argc == 1)
	print_help(1);

/* options */
while((opt = getopt(argc, argv, "hvxa")) != -1){
	switch(opt){
		case 'h': /* print help and exit */
			print_help(0);
		case 'v': /* print program version and exit */ 
			print_version(0);
		case 'x': /* output address in Hex */
			print_flag = 1;
			break;
		case 'a': /* output additional info*/
			print_flag = 2;
			break;
		default:
			fprintf(stderr, "Error: no such option\n\n");
			print_help(0);
	}
}

/* compile ip regular expression */
if(regcomp(&re, IPEXPR, REG_EXTENDED) !=0){
	fprintf(stderr, "Error compiling regular expression\n");
	return 1;
}

/* while parsing remaining options */
for(; optind < argc; optind++){
	/* test for ip4 dotted quad address format */
	if(regexec(&re, argv[optind], 0, NULL, 0) != 0){
	fprintf(stderr, "Error - %s; not an ip4 dotted quad\n", argv[optind]);
	continue;
	}
}

/* read address */	
sscanf(argv[optind], "%d.%d.%d.%d", &var1, &var2, &var3, &var4);
/* convert address to base 10 */
result = (var1 << 24) + (var2 << 16) + (var3 << 8) + var4;

/* output results */
switch(print_flag){
	case '0': /* print base 10 */
		printf("%lu\n", result);
		break;
	case '1': /* print in hex */
		printf("%0lx\n", result);
		break;
	case '2': /* print additional info */
		printf("%%\n");
		printf("ip address: %s\n", argv[optind]);
		printf("formula   : %d * (256^3) + %d * (256^2) + %d * 256 + %d\n",
				var1, var2, var3, var4);
		printf("base10    : %lu\n", result);
		printf("hex       : %0lx\n", result); 
		break;
	}
	return 0;
}

/* Print usage */
void print_help(int exitVal){
	printf("Usage: [-h] [-v] [-x] [-a] IP IP..\n\n");
	printf(" -h		print this help and exit\n");
	printf(" -v		print version and exit\n");
	printf(" -x		print address in hexadecimal\n");
	printf(" -a		print additional info\n\n");

	printf(" Please note, this valid for IP version 4 addreses only!\n");
	exit(exitVal);
}

/* print version */
void print_version(int exitVal){
	printf("Version: %s\n", VERSION);
	exit(exitVal);
}
