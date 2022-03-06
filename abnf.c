#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "abnf.h"
#include <stdio.h>
#include <stdlib.h>
 
// Following function extracts characters present in `src`
// between `m` and `n` (excluding `n`)
char* substring(const char *src, int m, int n)
{
    // get the length of the destination string
    int len = n - m;
 
    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
 
    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
 
    // null-terminate the destination string
    *dest = '\0';
 
    // return the destination string
    return dest - len;
}

int isPORT(char *str) {
	int i,result=1;
	if (str==NULL) {result=1;}
	else {
		for (i=0; str[i]!=0; i++) {
			if (!isdigit(str[i])) {
				result=0;
			}
		}
	}
	return (result);
}
int isSCHEME(char *str) {
	int i,result=1;
	if (str==NULL) {result=0;}
	else {
		if (!(isalpha(str[0]))) {
			result=0;}
		else {
			for (i=1;str[i]!=0;i++) {
				if (!(isdigit(str[i]) || isalpha(str[i]) || str[i] =='+' || str[i] == '-' || str[i] == '.')) {
					result=0;
				}
			}
		}
	}
	return (result);
}
int isUNRESERVED(char *str) {
	return ( (strlen(str)==1) && (isalpha(str[0]) || isdigit(str[0]) || str[0] =='-' || str[0] == '.' || str[0] == '_' || str[0] == '~'));
}
int isPCTENCODED(char *str) {
	return ( (strlen(str)==3) && (str[0]=='%' && isxdigit(str[1]) && isxdigit(str[2])) );
}
int isGENDELIMS( char *str) {
	char *match=":/?#[]@" ;
	return( (strlen(str)==1) && (strstr(match, str)));
}
int isSUBDELIMS( char *str) {
	char *match="!$&'()*+,;=" ;
	return( (strlen(str)==1) && (strstr(match, str)));
}
int isSCRIPT(char *str) {
	return( (strlen(str)==4) && (isalpha(str[0]) && isalpha(str[1]) && isalpha(str[2]) && isalpha(str[3])) );
}
int isREGION(char *str) {
	if (isalpha(str[0])) {
		return (strlen(str)==2 && isalpha(str[1]));
	}
	else if (isdigit(str[0])) {
		return( strlen(str)==3 && isdigit(str[1]) && isdigit(str[2]));
	}
	else {
		return 0;
	}
}
int isPCHAR(char *str) {
	if (strlen(str)==1) {
		return( (isUNRESERVED(str) || isSUBDELIMS(str) || str[0]==':' || str[0]=='@'));
	}
	else if (strlen(str)==3) {
		return( isPCTENCODED(str)); }
	
	else {return 0;}

}
int isQCHAR(char *str) {
	if (strlen(str)==1) {
		return( (isUNRESERVED(str) || isSUBDELIMS(str) || str[0]=='@'));
	}
	else if (strlen(str)==3) {
		return( isPCTENCODED(str)); }
	
	else {return 0;}

}
int isRCHAR(char *str) {
	if (strlen(str)==1) {
		return( (isUNRESERVED(str) || isSUBDELIMS(str) || str[0]==':'));
	}
	else if (strlen(str)==3) {
		return( isPCTENCODED(str)); }
	
	else {return 0;}

}
int isNCHAR(char *str) {
	if (strlen(str)==1) {
		return( (isUNRESERVED(str) || isSUBDELIMS(str)));
	}
	else if (strlen(str)==3) {
		return( isPCTENCODED(str)); }
	
	else {return 0;}

}




int isSEGMENT(char *str) {
	if (strlen(str) >= 1) {
		int i;
		int len=strlen(str);
		for (i=0;i<len;i++) {
			char *a=substring(str,0,1);
			char *b=substring(str,0,3);
			if (isPCHAR(a)) {
				str=substring(str,0,strlen(str)-1);
			}
			
			else if (isPCHAR(b)) {
				str=substring(str,2,strlen(str)-2);
			}
			else {
				return 0; }
		
	}
	}
	else if (strlen(str) ==1) {
		return (isPCHAR(str)); 
	}
	else {return 1;}
}
int isSEGMENTNZ(char *str) {
	if (strlen(str) >= 1) {
		int i;
		int len=strlen(str);
		for (i=0;i<len;i++) {
			char *a=substring(str,0,1);
			char *b=substring(str,0,3);
			if (isQCHAR(a)) {
				str=substring(str,0,strlen(str)-1);
			}
			
			else if (isQCHAR(b)) {
				str=substring(str,2,strlen(str)-2);
			}
			else {
				return 0; }
		
	}
	}
	else if (strlen(str)==1) {
		return (isQCHAR(str)); 
	}
	else {return 0;}
}
int isSEGMENTNZNC(char *str) {
	if (strlen(str) >= 1) {
		int i;
		int len=strlen(str);
		for (i=0;i<len;i++) {
			char *a=substring(str,0,1);
			char *b=substring(str,0,3);
			if (isQCHAR(a)) {
				str=substring(str,0,strlen(str)-1);
			}
			
			else if (isQCHAR(b)) {
				str=substring(str,2,strlen(str)-2);
			}
			else {
				return 0; }
		
	}
	}
	else if (strlen(str)==1) {
		return (isQCHAR(str)); 
	}
	else {return 0;}
}



int isRESERVED(char *str) {
	return(isGENDELIMS(str) || isSUBDELIMS(str));
}

int isUSERINFO(char *str) {
	if (strlen(str) >= 1) {
		int i;
		int len=strlen(str);
		for (i=0;i<len;i++) {
			char *a=substring(str,0,1);
			char *b=substring(str,0,3);
			if (isRCHAR(a)) {
				str=substring(str,0,strlen(str)-1);
			}
			
			else if (isRCHAR(b)) {
				str=substring(str,2,strlen(str)-2);
			}
			else {
				return 0; }
		
	}
	}
	else if (strlen(str)==1) {
		return (isRCHAR(str)); 
	}
	else {return 0;}
}
int isH16(char *str) {
	int result=1;
	if (strlen(str)>=1 && strlen(str) <=4) {
	       	int i;
		for (i=0;str[i]!=0;i++) {
			if (!isxdigit(str[i])) {
				result=0; }
		}
	}
	else {result=0;}
	return result;
}

int isDECOCTET(char *str) {
	if (strlen(str) == 1) {
		return(isdigit(str[0]));}
	else if (strlen(str) == 2) {
		return(isdigit(str[0]) && (!(str[0]=='0')) && isdigit(str[1]));}
	else if (strlen(str) == 3) {
		return ( ((str[0]== '1') && (isdigit(str[1]) && (isdigit(str[2]) ) ) ) || (str[0]=='2' && ( str[1] =='0' || str[1] == '1' || str[1]=='2' || str[1]=='3' || str[1]=='4' ) && isdigit(str[2])) || (str[0]=='2' && str[1]=='5' &&  ( str[1] =='0' || str[2] == '1' || str[2]=='2' || str[2]=='3' || str[2]=='4' || str[2]=='5') ) );
	}
	else {return 0;}	
}

int isIPV4(char *str) {
	int i=0;
	int j=0;
	char *ip;
	if (strlen(str) >= 16 || strlen(str) < 8) {return 0;}
	else {
		char *match="." ;
		if(!strstr(str, match)) {
			return 0;
		}
		else {
			for(i=0;i<=16;i++) {
				if (str[i+1]=='.' || str[i+1]=='\0') {
					
					ip=substring(str,j,i+1);
					j=i+2;
			
					if (!isDECOCTET(ip)) {	
						return 0;
					}
				}
		}

		return 1;
		}
	}
}

int isREGNAME(char *str) {
	if (strlen(str) >= 1) {
		int i;
		int len=strlen(str);
		for (i=0;i<len;i++) {
			char *a=substring(str,0,1);
			char *b=substring(str,0,3);
			if (isNCHAR(a)) {
				str=substring(str,0,strlen(str)-1);
			}
			
			else if (isNCHAR(b)) {
				str=substring(str,2,strlen(str)-2);
			}
			else {
				return 0; }
		
	}
	}
	else if (strlen(str)==1) {
		return (isNCHAR(str)); 
	}
	else {return 0;}
}

int isIPVFUTURE(char *str) {
	char *match="." ;
	int i,j;
	char *start;
	char *end;
	if(!strstr(str, match)) {return 0;}	
	if (str[0]!='v') {
		return 0;
	}
	else {
		if(!isxdigit(str[1])) {
			return 0; }
		else {
			for(i=1;str[i]!='.';i++);
			start=substring(str,1,i); //part 1 of string (before .)
			for(j=0;start[j]!=0;j++) {
				if(!isxdigit(start[j])) {
					return 0;
				}
			}
			i++;
			while(str[i]!=0) {
				end=substring(str,i,i+1); //str[i]
				if (! (isUNRESERVED(end) || isSUBDELIMS(end) || str[i]==':')) {
					return 0;
				}
				i++;
			}
		}
		return 1;
	}
}

int isH16O (char* str) {
	char *match=":" ;
	if(!strstr(str, match)) {return 0;}		
	int i,j;
	char *start;
	if (strlen(str) > 5 || str[strlen(str)-1]!=':') {return 0;}
	if (isH16(substring(str,0,1))) {
		printf("start of string is %s\n", str);
		for(j=0;str[j]!=0;j++) {
			printf("parsing %s\n", substring(str,j,j+1));
			if(! isH16(substring(str,j,j+1))) {

				return 0;
			}
		}
	return 1;
	}
}

int isH16I (char* str) {
	char *match=":" ;
	if(!strstr(str, match)) {return 0;}		
	int i,j;
	char *start;
	
	if (strlen(str) > 5 && str[0]!=':') {return 0;}
		printf("start of string is %s\n", str);
		for(j=1;str[j]!=0;j++) {
			printf("parsing %s\n", substring(str,j,j+1));
			if(! isH16(substring(str,j,j+1))) {

				return 0;
			}
		}
	return 1;
	
}


int isIPV6(char *str) {
	int i;

	
}



