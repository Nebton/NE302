#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
// for librequest
#include "request.h"

// for parser

// this will declare internal type used by the parser
#include "httpparser.h"
#include "api.h"

#define ERROR "HTTP/1.0 400 BAD REQUEST\r\n\r\n"
#define REPONSE11 "HTTP/1.1 200 OK\r\n"
#define REPONSE10 "HTTP/1.0 200 OK\r\n"
#define True 1
#define False 0
#define MAX 1024



int searchPath(char hosts[][128],char *host){
	int n = strlen(*hosts);
	printf("%d\n",n );
	for (int i = 0; i < n; i++){
		if (strcmp(hosts[i], host) == 0)return i;
	}
	return -1;
}

int initTab(char hosts[MAX][128], char paths[MAX][128]){
	FILE *fich;
	char ligne[MAX];
	fich=fopen("conf.txt","rt");
	int i = 0;
	for(int j = 0; j < MAX ; j++)
		for(int k = 0; k < 128; k++){
			hosts[j][k]='\0';
			paths[j][k]='\0';
		}

	while( fgets(ligne,MAX,fich)!=NULL){
			strcpy(hosts[i], ligne);
			fgets(ligne,MAX,fich);
			strcpy(paths[i], ligne);
			i++;
	}
	fclose(fich);
	return 0;
}


//Rule 1 : Si la version HTTP est 1.1, il doit y avoir un HOST
int Rule1() {
	_Token *version,*host,*root;
	root=getRootTree();
	if(version=searchTree(root,"HTTP_version")) {
		int m;
		char *b;
		b = getElementValue(((Lnode *)version->node),&m);
		if(!strncmp(b,"HTTP/1.1",8)) {
			//on verifie si la version HTTP est 1.1
			if(!(host=searchTree( root,"Host_header"))) {
				//Version 1.1 and no HOST : 400 BAD REQUEST
				#undef ERROR
				#define ERROR "HTTP/1.1 400 BAD REQUEST\r\n"
				return False;
			}

		}
		else {
			return True;
		}
	}
	else {
		return False;
	}
	return True;
}

//Rule 2 : Si la version HTTP est 1.0, il peut pas y avoir un Transfer-Encoding
int Rule2() {
	_Token *version,*transfer,*root;
	root=getRootTree();
	if(version=searchTree(root,"HTTP_version")) {
		int m;
		char *b;
		b = getElementValue(((Lnode *)version->node),&m);
		if(strncmp(b,"HTTP/1.0",8)==0) {
			//on verifie si la version HTTP est 1.0
			if((transfer=searchTree( root,"Transfer_Encoding_header"))) {
				//Version 1.0 and Transfer Encoding HEADER : 400 BAD REQUEST
				#undef ERROR
				#define ERROR "HTTP/1.0 400 BAD REQUEST\r\n"
				return False;
			}
			else {
				return True;
			}

		}
		else {
			return True;
		}
	}
	else {
		return False;
	}

}

//Rule 3 : S'il y a deja un Transfer-Encoding_Header, il peut pas y avoir un Content Length
int Rule3() {
	_Token *version,*transfer,*root,*content;
	root=getRootTree();
	if(transfer=searchTree(root,"Transfer_Encoding_header")) {
			if((content=searchTree( root,"Content_Length_header"))) {
				//Transfer Encoding and Content LENGTH : 400 BAD REQUEST
				#undef ERROR
				#define ERROR "HTTP/1.1 400 BAD REQUEST\r\n"
				return False;
			}
			else {
				return True;
			}

		}
		else {
			return True;
		}
	}



//Fonction pour verifier si le string str termine par le string suffix
int endswith(char *str, char *suffix) {
	char *ext = strrchr(str,'.');
	if(!ext) {
		return 0;
	}
	else {
		return(!strcmp(ext,suffix));
	}
}

// Following function extracts characters present in `src`
// between `m` and `n` (excluding `n`)
char* substr(const char *src, int m, int n){
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


int main(int argc, char *argv[])
{
	message *requete;
	int res;

	char hosts[MAX][128];
	char paths[MAX][128];

	if (initTab(hosts, paths) == -1)printf("erreur\n");
	printf("%s\n",paths[searchPath(hosts,"www.site.com\n")]);

	while ( 1 ) {
		// on attend la reception d'une requete HTTP requete pointera vers une ressource allouée par librequest.
		if ((requete=getRequest(8080)) == NULL ) return -1;

		// Affichage de debug
		printf("#########################################\nDemande recue depuis le client %d\n",requete->clientId);
		printf("Client [%d] [%s:%d]\n",requete->clientId,inet_ntoa(requete->clientAddress->sin_addr),htons(requete->clientAddress->sin_port));
		printf("Contenu de la demande \r\n[%.*s]\n",requete->len,requete->buf);
		if (res=parseur(requete->buf,requete->len) && Rule1() && Rule2()) {
			//Requete syntaxiquement et semantiquement correcte
			_Token *r,*tok,*root,*req,*meth,*version;



			// get the root of the tree this is no longer opaque since we know the internal type with httpparser.h
			//void *root;

			root=getRootTree();
			req=searchTree(root,"request_target");
			version=searchTree(root,"HTTP_version");;


			meth=searchTree(root,"method");
			Lnode *method;
			method =(Lnode *)meth->node;
			//printf("method is [%.*s] at level %d\n\n\n", method->len, method->value, method->level );
			if(strncmp(method->value,"GET",method->len)==0 || strncmp(method->value,"HEAD",method->len)==0) {
				// node is no longer opaque
				Lnode *request;
				request=(Lnode *)req->node;
				char *file;
				//printf("request target is [%.*s] at level %d\n\n\n", request->len, request->value, request->level );

				if(strncmp(request->value,"/",request->len) == 0) {
					file="index.html";

				}
				else {
					file=substr(request->value,1,request->len);

				}
				//printf("file is %s\n", file);
				FILE *fp = fopen(file, "rb");
				if(fp==NULL) {
					fprintf(stderr, "cannot open file [%s]\n", file);
					writeDirectClient(requete->clientId,ERROR,strlen(ERROR));
				}
				else {
				//on met le contenu du fichier dans  le string buffer, et on stocke sa taille dans le long size
				fseek(fp, 0, SEEK_END);
				long size = ftell(fp);
				rewind(fp);
				char *buffer = (char*)malloc(sizeof(char)*size);
				size_t result = fread(buffer, 1, size, fp);
				fclose(fp);
				//on convertit le long size a un string csize
				int enough = (long)((ceil(log10(size))+1)*sizeof(char));
				char csize[enough];
				sprintf(csize, "%ld", size);
				//le fichier a ete trouvee, la reponse doit etre la bonne selon les extensions

				int m;
				char *b;
				b = getElementValue(((Lnode *)version->node),&m);
				if(!strncmp(b,"HTTP/1.1",8)) {
					writeDirectClient(requete->clientId,REPONSE11,strlen(REPONSE11));
					writeDirectClient(requete->clientId,"Connection: keep-alive\r\n", strlen("Connection: Keep-Alive\r\n"));
					}
				else if (!strncmp(b,"HTTP/1.0",8)) {
					writeDirectClient(requete->clientId,REPONSE10,strlen(REPONSE10));
					writeDirectClient(requete->clientId,"Connection: close\r\n", strlen("Connection: close\r\n"));
				}
				else {
					writeDirectClient(requete->clientId,ERROR,strlen(ERROR));
					exit(1);
				}



				FILE *fp;


			  /* Open the command for reading. */

				/*
				char commande[100] ="file -i ";
				strncat(commande,file,strlen(file)+1);
				strncat(commande,"| egrep -o ':.*;' | tr -d ';'", strlen("| egrep -o ':.*;' | tr -d ';'")+1);
				printf("current command is [%s]\n", commande);

				char ctype[1061];
			  fp = popen(commande,"r");
			  if (fp == NULL) {
			    printf("Failed to run command\n" );
			    exit(1);
			  }

			  /* Read the output a line at a time - output it. */
				/*
				 while (fgets(ctype, sizeof(ctype), fp) != NULL) {
    			fscanf(fp, "%s", ctype);
  }
				writeDirectClient(requete->clientId,"Content-Type",strlen("Content-Type"));
				writeDirectClient(requete->clientId,ctype,strlen(ctype));

			   /* close */
			  //pclose(fp);

		  	/************************************************TYPE TEXT DEBUT**********************************************************************/

				/*************************************************************************************************************************************/

				if (endswith(file,".html") || endswith(file,".htm") || endswith(file,".htm")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/html\r\n",strlen("Content-Type: text/html\r\n"));
				}
				if (endswith(file,".css")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/css\r\n",strlen("Content-Type: text/css\r\n"));
				}
				if (endswith(file,".323")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/h323\r\n",strlen("Content-Type: text/h323\r\n"));
				}
				if (endswith(file,".uls")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/iuls\r\n",strlen("Content-Type: text/iuls\r\n"));
				}
				if (endswith(file,".bas") || endswith(file,".c") || endswith(file,".h") || endswith(file,".txt")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/plain\r\n",strlen("Content-Type: text/plain\r\n"));
				}
				if (endswith(file,".rtx")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/richtext\r\n",strlen("Content-Type: text/richtext\r\n"));
				}
				if (endswith(file,".sct")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/scriptlet\r\n",strlen("Content-Type: text/scriptlet\r\n"));
				}
				if (endswith(file,".tsv")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/tab-seperated-values\r\n",strlen("Content-Type: text/tab-seperated-values\r\n"));
				}
				if (endswith(file,".htt")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/webviewhtml\r\n",strlen("Content-Type: text/webviewhtml\r\n"));
				}
				if (endswith(file,".htc")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/x-component\r\n",strlen("Content-Type: text/x-component\r\n"));
				}
				if (endswith(file,".etx")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/x-setext\r\n",strlen("Content-Type: text/x-setext\r\n"));
				}
				if (endswith(file,".vcf")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: text/x-vcard\r\n",strlen("Content-Type: text/x-vcard\r\n"));
				}
				/***********************************************TYPE TEXT FIN************************************************************************/
				/*************************************************************************************************************************************/

				/***********************************************TYPE IMAGE DEBUT**********************************************************************/
				/*************************************************************************************************************************************/

				else if(endswith(file,".png")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/png\r\n",strlen("Content-Type: image/png\r\n"));
				}
				else if(endswith(file,".jpg") || endswith(file,".jpeg") || endswith(file,".jpe")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/jpeg\r\n",strlen("Content-Type: image/jpeg\r\n"));
				}
				else if(endswith(file,".gif")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/gif\r\n",strlen("Content-Type: image/gif\r\n"));
				}
				else if(endswith(file,".ico")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/vnd.microsoft.icon\r\n",strlen("Content-Type: image/vnd.microsoft.icon\r\n"));
				}
				else if(endswith(file,".djvu") || endswith(file,".djv")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/vnd.djvu\r\n",strlen("Content-Type: image/vnd.djvu\r\n"));
				}
				else if(endswith(file,".svg")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/svg+xml\r\n",strlen("Content-Type: image/svg+xml\r\n"));
				}
				else if(endswith(file,".bmp")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/bmp\r\n",strlen("Content-Type: image/bmp\r\n"));
				}
				else if(endswith(file,".cod")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/cis-cod\r\n",strlen("Content-Type: image/cis-cod\r\n"));
				}
				else if(endswith(file,".ief")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/ief\r\n",strlen("Content-Type: image/ief\r\n"));
				}
				else if(endswith(file,".jfif")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/pipeg\r\n",strlen("Content-Type: image/pipeg\r\n"));
				}
				else if(endswith(file,".tif") || endswith(file,".tiff")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/tiff\r\n",strlen("Content-Type: image/tiff\r\n"));
				}
				else if(endswith(file,".pnm")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/x-portable-anymap\r\n",strlen("Content-Type: image/x-portable-anymap\r\n"));
				}
				else if(endswith(file,".pbm")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/x-portable-bitmap\r\n",strlen("Content-Type: image/x-portable-bitmap\r\n"));
				}
				else if(endswith(file,".pgm")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/x-portable-graymap\r\n",strlen("Content-Type: image/x-portable-graymap\r\n"));
				}
				else if(endswith(file,".ppm")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/x-portable-pixmap\r\n",strlen("Content-Type: image/x-portable-pixmap\r\n"));
				}
				else if(endswith(file,".rgb")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/x-rgb\r\n",strlen("Content-Type: image/x-rgb\r\n"));
				}
				else if(endswith(file,".xbm")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/x-xbitmap\r\n",strlen("Content-Type: image/x-xbitmap\r\n"));
				}
				else if(endswith(file,".xpm")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/x-xpixmap\r\n",strlen("Content-Type: image/x-xpixmap\r\n"));
				}
				else if(endswith(file,".xwd")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: image/x-xwindowdump\r\n",strlen("Content-Type: image/x-xwindowdump\r\n"));
				}
				/***********************************************TYPE IMAGE FIN************************************************************************/
				/*************************************************************************************************************************************/

				/***********************************************TYPE VIDEO DEBUT**********************************************************************/
				/*************************************************************************************************************************************/

				else if(endswith(file,".mpeg") || endswith(file,".mp2") || endswith(file,".mpa") || endswith(file,".mpe") || endswith(file,".mpg") || endswith(file,".mpv2")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: video/mpeg\r\n",strlen("Content-Type: video/mpeg\r\n"));
				}
				else if(endswith(file,".mp4")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: video/mp4\r\n",strlen("Content-Type: video/mp4\r\n"));
				}
				else if(endswith(file,".webm")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: video/webm\r\n",strlen("Content-Type: video/webm\r\n"));
				}

				else if(endswith(file,".ogv") || endswith(file,".ogx")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: video/ogg\r\n",strlen("Content-Type: video/ogg\r\n"));
				}
				else if(endswith(file,".mov") || endswith(file,".qt")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: video/quicktime\r\n",strlen("Content-Type: video/quicktime\r\n"));
				}
				else if(endswith(file,".avi")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: video/x-msvideo\r\n",strlen("Content-Type: video/x-msvideo\r\n"));
				}
				else if(endswith(file,".movie")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: video/x-sgimovie\r\n",strlen("Content-Type: video/x-sgimovie\r\n"));
				}

				/***********************************************TYPE VIDEO FIN************************************************************************/
				/*************************************************************************************************************************************/

				/***********************************************TYPE AUDIO DEBUT************************************************************************/
				/*************************************************************************************************************************************/

				else if(endswith(file,".oga") || endswith(file,".ogg") || endswith(file,".spx")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: audio/ogg\r\n",strlen("Content-Type: audio/ogg\r\n"));
				}
				else if(endswith(file,".au") || endswith(file,".snd")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: audio/basic\r\n",strlen("Content-Type: audio/basic\r\n"));
				}
				else if(endswith(file,".mid") || endswith(file,".rmi")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: audio/mid\r\n",strlen("Content-Type: audio/mid\r\n"));
				}
				else if(endswith(file,".mp3")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: audio/mpeg\r\n",strlen("Content-Type: audio/mpeg\r\n"));
				}
				else if(endswith(file,".aif") || endswith(file,".aiff") || endswith(file,".aifc")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: audio/x-aiff\r\n",strlen("Content-Type: audio/x-aiff\r\n"));
				}
				else if(endswith(file,".m3u")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: audio/x-mpegurl\r\n",strlen("Content-Type: audio/x-mpegurl\r\n"));
				}
				else if(endswith(file,".ra") || endswith(file,".ram")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: audio/x-pn-realaudio\r\n",strlen("Content-Type: audio/x-pn-realaudio\r\n"));
				}
				else if(endswith(file,".wav")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: audio/x-wav\r\n",strlen("Content-Type: audio/x-wav\r\n"));
				}


				/***********************************************TYPE AUDIO FIN************************************************************************/
				/*************************************************************************************************************************************/

				/***********************************************TYPE APPLICATION DEBUT************************************************************************/
				/*************************************************************************************************************************************/

				else if(endswith(file,".evy")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/envoy\r\n",strlen("Content-Type: application/envoy\r\n"));
				}
				else if(endswith(file,".fif")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/fractals\r\n",strlen("Content-Type: application/fractals\r\n"));
				}
				else if(endswith(file,".spl")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/futuresplash\r\n",strlen("Content-Type: application/futuresplash\r\n"));
				}
				else if(endswith(file,".hta")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/hta\r\n",strlen("Content-Type: application/hta\r\n"));
				}
				else if(endswith(file,".acx")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/internet-property-stream\r\n",strlen("Content-Type: application/internet-property-stream\r\n"));
				}
				else if(endswith(file,".hqx")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/mac-binhex40\r\n",strlen("Content-Type: application/mac-binhex40\r\n"));
				}
				else if(endswith(file,".doc") || endswith(file,".dot")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/msword\r\n",strlen("Content-Type: application/msword\r\n"));
				}
				else if(endswith(file,".bin") || endswith(file,".class") || endswith(file,".dms") || endswith(file,".exe") || endswith(file,".lha") || endswith(file,".lzh")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/octet-stream\r\n",strlen("Content-Type: application/octet-stream\r\n"));
				}
				else if(endswith(file,".oda")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/oda\r\n",strlen("Content-Type: application/oda\r\n"));
				}
				else if(endswith(file,".axs")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/olescript\r\n",strlen("Content-Type: application/olescript\r\n"));
				}
				else if(endswith(file,".pdf")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/pdf\r\n",strlen("Content-Type: application/pdf\r\n"));
				}
				else if(endswith(file,".prf")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/pics-rules\r\n",strlen("Content-Type: application/pics-rules\r\n"));
				}
				else if(endswith(file,".p10")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/pkcs10\r\n",strlen("Content-Type: application/pkcs10\r\n"));
				}
				else if(endswith(file,".crl")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/pkix-crl\r\n",strlen("Content-Type: application/pkix-crl\r\n"));
				}
				else if(endswith(file,".ai") || endswith(file,".eps") || endswith(file,".ps")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/postscript\r\n",strlen("Content-Type: application/postscript\r\n"));
				}
				else if(endswith(file,".rtf")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/rtf\r\n",strlen("Content-Type: application/rtf\r\n"));
				}
				else if(endswith(file,".setpay")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/set-payment-initiation\r\n",strlen("Content-Type: application/set-payment-initiation\r\n"));
				}
				else if(endswith(file,".setreg")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/set-registration-initiation\r\n",strlen("Content-Type: application/set-registration-initiation\r\n"));
				}
				else if(endswith(file,".xla") || endswith(file,".xlc") || endswith(file,".xlm") || endswith(file,".xls") || endswith(file,".xlt") || endswith(file,".xlw")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/vnd.ms-excel\r\n",strlen("Content-Type: application/vnd.ms-excel\r\n"));
				}

				else if(endswith(file,".msg")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/vnd.ms-outlook\r\n",strlen("Content-Type: application/vnd.ms-outlook\r\n"));
				}
				else if(endswith(file,".sst")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/vnd.ms-pkicertstore\r\n",strlen("Content-Type: application/vnd.ms-pkicertstore\r\n"));
				}
				else if(endswith(file,".cat")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/vnd.ms-pkiseccat\r\n",strlen("Content-Type: application/vnd.ms-pkiseccat\r\n"));
				}
				else if(endswith(file,".stl")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/vnd.ms-pkistl\r\n",strlen("Content-Type: application/vnd.ms-pkistl\r\n"));
				}
				else if(endswith(file,".pps") || endswith(file,".pot") || endswith(file,".ppt")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/vnd.ms-powerpoint\r\n",strlen("Content-Type: application/vnd.ms-powerpoint\r\n"));
				}
				else if(endswith(file,".mpp")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/vnd.ms-project\r\n",strlen("Content-Type: application/vnd.ms-project\r\n"));
				}
				else if(endswith(file,".wcm") || endswith(file,".wdb") || endswith(file,".wks") || endswith(file,".wps") ) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/vnd.ms-works\r\n",strlen("Content-Type: application/vnd.ms-works\r\n"));
				}
				else if(endswith(file,".hlp")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/winhlp\r\n",strlen("Content-Type: application/winhlp\r\n"));
				}
				else if(endswith(file,".bcpio")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-bcpio\r\n",strlen("Content-Type: application/x-bcpio\r\n"));
				}
				else if(endswith(file,".cdf")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-cdf\r\n",strlen("Content-Type: application/x-cdf\r\n"));
				}
				else if(endswith(file,".z")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-compress\r\n",strlen("Content-Type: application/x-compress\r\n"));
				}
				else if(endswith(file,".tgz")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-compressed\r\n",strlen("Content-Type: application/x-compressed\r\n"));
				}
				else if(endswith(file,".cpio")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-cpio\r\n",strlen("Content-Type: application/x-cpio\r\n"));
				}
				else if(endswith(file,".csh")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-csh\r\n",strlen("Content-Type: application/x-csh\r\n"));
				}
				else if(endswith(file,".dcr") || endswith(file,".dir") || endswith(file,".dxr")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-director\r\n",strlen("Content-Type: application/x-director\r\n"));
				}
				else if(endswith(file,".dvi")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-dvi\r\n",strlen("Content-Type: application/x-dvi\r\n"));
				}
				else if(endswith(file,".gtar")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-gtar\r\n",strlen("Content-Type: application/x-gtar\r\n"));
				}
				else if(endswith(file,".gz")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-gzip\r\n",strlen("Content-Type: application/x-gzip\r\n"));
				}
				else if(endswith(file,".hdf")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-hdf\r\n",strlen("Content-Type: application/x-hdf\r\n"));
				}
				else if(endswith(file,".ins") || endswith(file,".isp")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-internet-signup\r\n",strlen("Content-Type: application/x-internet-signup\r\n"));
				}
				else if(endswith(file,".iii")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-iphone\r\n",strlen("Content-Type: application/x-iphone\r\n"));
				}
				else if(endswith(file,".js")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-javascript\r\n",strlen("Content-Type: application/x-javascript\r\n"));
				}
				else if(endswith(file,".latex")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-latex\r\n",strlen("Content-Type: application/x-latex\r\n"));
				}
				else if(endswith(file,".mdb")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-msaccess\r\n",strlen("Content-Type: application/x-msaccess\r\n"));
				}
				else if(endswith(file,".crd")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-mscardfile\r\n",strlen("Content-Type: application/x-mscardfile\r\n"));
				}
				else if(endswith(file,".clp")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-msclip\r\n",strlen("Content-Type: application/x-msclip\r\n"));
				}
				else if(endswith(file,".dll")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-msdownload\r\n",strlen("Content-Type: application/x-msdownload\r\n"));
				}
				else if(endswith(file,".m13") || endswith(file,".m14") || endswith(file,".mvb")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-msmediaview\r\n",strlen("Content-Type: application/x-msmediaview\r\n"));
				}
				else if(endswith(file,".wmf")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-msmetafile\r\n",strlen("Content-Type: application/x-msmetafile\r\n"));
				}
				else if(endswith(file,".mny")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-msmoney\r\n",strlen("Content-Type: application/x-msmoney\r\n"));
				}
				else if(endswith(file,".pub")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-mspublisher\r\n",strlen("Content-Type: application/x-mspublisher\r\n"));
				}
				else if(endswith(file,".scd")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-msschedule\r\n",strlen("Content-Type: application/x-msschedule\r\n"));
				}
				else if(endswith(file,".trm")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-msterminal\r\n",strlen("Content-Type: application/x-msterminal\r\n"));
				}
				else if(endswith(file,".wri")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-mswrite\r\n",strlen("Content-Type: application/x-mswrite\r\n"));
				}
				else if(endswith(file,".cdf")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-netcdf\r\n",strlen("Content-Type: application/x-netcdf\r\n"));
				}
				else if(endswith(file,".nc")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-netcdt\r\n",strlen("Content-Type: application/x-netcdt\r\n"));
				}
				else if(endswith(file,".pma") || endswith(file,".pmc") || endswith(file,".pml") || endswith(file,".pmr") || endswith(file,".pmw")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-perfmon\r\n",strlen("Content-Type: application/x-perfmon\r\n"));
				}
				else if(endswith(file,".p12") || endswith(file,".pfx")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-pkcs12\r\n",strlen("Content-Type: application/x-pkcs12\r\n"));
				}
				else if(endswith(file,".p7b") || endswith(file,".spc")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-pcks7-certificates\r\n",strlen("Content-Type: application/x-pkcs7-certificates\r\n"));
				}
				else if(endswith(file,".p7r")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-pcks7-certreqresp\r\n",strlen("Content-Type: application/x-pkcs7-certreqresp\r\n"));
				}
				else if(endswith(file,".p7c") || endswith(file,".p7m")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-pcks7-mime\r\n",strlen("Content-Type: application/x-pkcs7-mime\r\n"));
				}
				else if(endswith(file,".p7s")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-pcks7-signature\r\n",strlen("Content-Type: application/x-pkcs7-signature\r\n"));
				}
				else if(endswith(file,".sh")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-sh\r\n",strlen("Content-Type: application/x-sh\r\n"));
				}
				else if(endswith(file,".shar")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-shar\r\n",strlen("Content-Type: application/x-shar\r\n"));
				}
				else if(endswith(file,".swf")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-shockwave-flash\r\n",strlen("Content-Type: application/x-shockwave-flash\r\n"));
				}
				else if(endswith(file,".sit")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-stuffit\r\n",strlen("Content-Type: application/x-stuffit\r\n"));
				}
				else if(endswith(file,".sv4cpio")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-sv4cpio\r\n",strlen("Content-Type: application/x-sv4cpio\r\n"));
				}
				else if(endswith(file,".sv4crc")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-sv4crc\r\n",strlen("Content-Type: application/x-sv4crc\r\n"));
				}
				else if(endswith(file,".tar")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-tar\r\n",strlen("Content-Type: application/x-tar\r\n"));
				}
				else if(endswith(file,".tex")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-tex\r\n",strlen("Content-Type: application/x-tex\r\n"));
				}
				else if(endswith(file,".texi") || endswith(file,".texinfo")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-texinfo\r\n",strlen("Content-Type: application/x-texinfo\r\n"));
				}
				else if(endswith(file,".tar")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-tar\r\n",strlen("Content-Type: application/x-tar\r\n"));
				}
				else if(endswith(file,".roff") || endswith(file,".t") || endswith(file, ".tr")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-troff\r\n",strlen("Content-Type: application/x-troff\r\n"));
				}
				else if(endswith(file,".man")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-troff-man\r\n",strlen("Content-Type: application/x-troff-man\r\n"));
				}
				else if(endswith(file,".me")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-troff-me\r\n",strlen("Content-Type: application/x-troff-me\r\n"));
				}
				else if(endswith(file,".ms")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-troff-ms\r\n",strlen("Content-Type: application/x-troff-ms\r\n"));
				}
				else if(endswith(file,".ustar")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-ustar\r\n",strlen("Content-Type: application/x-ustar\r\n"));
				}
				else if(endswith(file,".src")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-wais-source\r\n",strlen("Content-Type: application/x-wais-source\r\n"));
				}
				else if(endswith(file,".cer") || endswith(file,".crt") || endswith(file,".der")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/x-x509-ca-cert\r\n",strlen("Content-Type: application/x-x509-ca-cert\r\n"));
				}
				else if(endswith(file,".pko")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/ynd.ms-pkipko\r\n",strlen("Content-Type: application/ynd.ms-pkipko\r\n"));
				}
				else if(endswith(file,".zip")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: application/zip\r\n",strlen("Content-Type: application/zip\r\n"));
				}

				/***********************************************TYPE APPLICATION FIN************************************************************************/
				/*************************************************************************************************************************************/

				/***********************************************TYPE MESSAGE DEBUT************************************************************************/
				/*************************************************************************************************************************************/

				else if(endswith(file,".mht") || endswith(file,".mhtml") || endswith(file, ".nws")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: message/rfc822\r\n",strlen("Content-Type: message/rfc822\r\n"));
				}
				/***********************************************TYPE MESSAGE FIN************************************************************************/
				/*************************************************************************************************************************************/

				/***********************************************TYPE VIRTUAL WORLD DEBUT************************************************************************/
				/*************************************************************************************************************************************/

				else if(endswith(file,".flr") || endswith(file,".wrl") || endswith(file, ".vrml") || endswith(file, ".wrz") || endswith(file, ".xaf") || endswith(file, ".xof")) {
					//on ecrit le content-type appropriee
					writeDirectClient(requete->clientId,"Content-Type: x-world/x-vrml\r\n",strlen("Content-Type: x-world/x-vrml\r\n"));
				}
				/***********************************************TYPE VIRTUAL WORLD FIN************************************************************************/
				/*************************************************************************************************************************************/



				writeDirectClient(requete->clientId,"Content-Length: ", strlen("Content-Length: "));
				writeDirectClient(requete->clientId, csize, strlen(csize));

				writeDirectClient(requete->clientId,"\r\n\r\n", 4);
				//On differencie le comportement selon GET et HEAD : Que des entetes si la requete est HEAD
				if(strncmp(method->value,"GET",method->len)==0) {
					writeDirectClient(requete->clientId,buffer,size);
				}


			}
			}
			//METHODE POST...
			/*else if(strncmp(method->value,"POT",method->len)==0) {				// node is no longer opaque
					_Token *length,*body,*root,*content,*encoding;
					root=getRootTree();
					if(!(content=searchTree(root,"Content_Type_header") && (length=searchTree(root,"Content_Length_header") || encoding=searchTree(root,"Transfer_Encoding_header"))  && body=searchTree(root,"message_body") )) {
						writeDirectClient(requete->clientId,ERROR,strlen(ERROR));
					}
					else {}




				}

				*/
		purgeElement(&req);
		purgeTree(root);
		}
		else {
			writeDirectClient(requete->clientId,ERROR,strlen(ERROR));
		}
		endWriteDirectClient(requete->clientId);
		requestShutdownSocket(requete->clientId);
	// on ne se sert plus de requete a partir de maintenant, on peut donc liberer...
	freeRequest(requete);
}

	return (1);
}


//A faire :
/*
	-Differencier entre les differentes types de requetes (.png, .html) (et utiliser une methode differente de stocker string (contenu du fichier voulu)
	pour les images car elles sont binaires (un 0 entraine un fin de caractere))
	-Finir de definir les regles semantiques
	-Implementer GET, HEAD et POST (si possible)

*/
