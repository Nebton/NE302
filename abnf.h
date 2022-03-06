#ifndef ABNF_H
#define ABNF_H
int isPORT(char *);
int isSCHEME(char *);
int isUNRESERVED(char *);
int isPCTENCODED(char *);
int isGENDELIMS(char *);
int isSUBDELIMS(char *);
int isSCRIPT(char *);
int isREGION(char *);
int isPCHAR(char *);
int isQCHAR(char *);
int isSEGMENT(char *);
int isRESERVED(char *);
int isSEGMENTNZ(char *);
int isSEGMENTNZNC(char *);
int isUSERINFO(char *);
char* substring(const char *, int, int);
int isH16(char *);
int isDECOCTET(char *);
int isIPV4(char *);
int isNCHAR(char *);
int isREGNAME(char *);
int isIPVFUTURE(char *);
int isH16O(char *);
int isH16I(char *);
#endif
