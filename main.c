#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "abnf.h"
int main() {
	if (isPORT("8080 ")) {
		printf("1\n");
	}

	if (isSCHEME("a9+2.3-")) {
		printf("2\n");
	}
	if (isUNRESERVED("-")) {
		printf("3\n");
	}
	if (isPCTENCODED("%ff")) {
		printf("4\n");
	}
	if(isGENDELIMS("@@")) {
		printf("5\n");
	}
	if(isSUBDELIMS(")")) {
		printf("6\n");
	}	
	if(isSCRIPT("aibcd")) {
		printf("7\n");
	}
	if(isREGION("3323")) {
		printf("8\n");
	}
	if(isPCHAR("%ff")) {
		printf("9\n");
	}
	if(isPCHAR(":")) {
		printf("10\n");
	}
	if(isRESERVED(":")) {
		printf("11\n");
	}
	if(isSEGMENT("")) {
		printf("12\n");
	}

	if(isSEGMENTNZ("")) {
		printf("13\n");
	}
	if(isSEGMENTNZNC(":@:")) {
		printf("14\n");
	}
	if(isUSERINFO("@:@")) {
		printf("15\n");
	}
	if(isH16("11112")) {
		printf("16\n");
	return 0;}
	if(isDECOCTET("256")) {
		printf("17\n");
	}
	if(isIPV4("123.124.023.255")) {
		printf("18\n");
	}
	if(isIPVFUTURE("vfff.dwe::z")) {
		printf("19\n");
	}
	//printf("%d\n",isH16O("fff::"));
	char *a=substring(":ff",0,3);
	printf("%s\n", a);
	printf("%d\n",isH16I(":fff:"));



}
