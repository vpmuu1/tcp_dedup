
#include <stdlib.h>  
#include <string.h>  
#include <stdio.h>  
#include <zlib.h>  
#include "deal.h"
#include <openssl/md5.h> 
#include <sys/socket.h>
#include "kissdb.h"

static KISSDB db;


int opendb(){
	printf("KISSDB_open \n");
	if (KISSDB_open(&db,"test.db",KISSDB_OPEN_MODE_RWREPLACE,1024,16,BUFSIZE)) {
		printf("KISSDB_open failed\n");
		return 1;
	}
	return 0;
}

int exit_main()
{ 
	KISSDB_close(&db);
	return 0;
}	
void show(unsigned char * md){
	int i;
	for (i=0;i<16;i++) 
		printf("%02X ",md[i]);
	fflush(stdout);
}	
long xrecv(char * buf, long  cnt,int fd){
	long count =0;
	long icnt=0;
	//printf("in xrecv %d\n",cnt);
	do {
	  count = recv(fd, buf+icnt, cnt, 0);
	  cnt-=count;
	  icnt+=count;
	  
	} while (cnt>0);	
	//printf("xrecved %d\n",icnt);
	//fflush(stdout);
	return 0;
}
long doenc(const char *inbuf, const long ilen, struct wrap_pkt *owp){
	int bc;
	static unsigned char tmp[BUFSIZE];
	owp->mw=MAGIC;
	MD5_CTX ctx;  
    
    
    MD5_Init(&ctx);  
    MD5_Update(&ctx,inbuf,ilen);  
    MD5_Final(owp->md5,&ctx); 
	memcpy(owp->encbuf,inbuf,ilen);
	owp->size=ilen;
	bc=sizeof(struct wrap_pkt)-BUFSIZE+ilen;
	owp->deduped=0;
	
	if (ilen==BUFSIZE) { 
		if (!KISSDB_get(&db,owp->md5,tmp)) {
			owp->deduped=1;
			owp->size=0;
			
			bc=sizeof(struct wrap_pkt)-BUFSIZE;
		} else {
			//printf("KISSDB_put\n");
			if (KISSDB_put(&db,owp->md5,inbuf)) {
				printf("KISSDB_put failed \n");
				return 1;
			}
		}
	} else {		
		//printf("owp->size=%d \n",owp->size);
	}
	//
//	show(owp->md5);
	return bc;
}
long dodec(struct wrap_pkt  *inwp, char * obuf){
	unsigned char md[16];  
	static unsigned char tmp[BUFSIZE];
	
	if (inwp->mw!=MAGIC) {
		printf("No MAGIC\n");
		return -1;
	}
	
	MD5_CTX ctx;      
    
    MD5_Init(&ctx);  
    
	
	memset(tmp,0,sizeof(tmp));
	if (inwp->deduped==1) { 
		if (KISSDB_get(&db,inwp->md5,tmp)==0) { //read success
			memcpy(obuf,tmp,BUFSIZE);
			//printf("KISSDB_get ok\n");
			MD5_Update(&ctx,obuf,BUFSIZE);
		} 
	} else {
		if (inwp->size==BUFSIZE) {
			if (KISSDB_put(&db,inwp->md5,inwp->encbuf)) {
				printf("KISSDB_put failed \n");
				return 1;
			}
		}
		memcpy(obuf,inwp->encbuf,inwp->size);
		MD5_Update(&ctx,inwp->encbuf,inwp->size);
	}
	  
    MD5_Final(md,&ctx);
	if (memcmp(md,inwp->md5,sizeof(md)))  {
		printf("md5 err,inwp->size=%d\n",inwp->size);
		return -1;
	}
	if (inwp->deduped==1) return  BUFSIZE;
	return inwp->size;
}

int deal(const unsigned char *inbuf, const int ilen, unsigned char * obuf,int encode){
	//dedup
    unsigned long olen=0;

    if (encode) {
                printf("encode %d\n",ilen);
    } else {
                printf("uncompress failed!\n");
    }

        return (int)olen;
}


int deal_gz(const unsigned char *inbuf, const int ilen, unsigned char * obuf,int encode){
    unsigned long olen;

    if (encode) {
	if(compress(obuf, &olen,inbuf, ilen) != Z_OK)  
	{  
        	printf("compress failed!\n");  
	        return -1;  
    	}
    } else {
	if(uncompress(obuf, &olen, inbuf, ilen) != Z_OK)  
    	{  
        	printf("uncompress failed!\n");  
	        return -1;  
    	} 
    }

        return (int)olen;
}
