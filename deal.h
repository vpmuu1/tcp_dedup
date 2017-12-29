

#define  BUFSIZE (1024*128)
#define  MAGIC 0x20131102

struct wrap_pkt {

  long mw;
  long size;
  
  unsigned char md5[16];
  long deduped;
  char uu[72];
  unsigned char  encbuf[BUFSIZE];
  
};
int exit_main();
int opendb();
long doenc(const char *inbuf, const long ilen, struct wrap_pkt *owp);
long dodec(struct wrap_pkt  *inwp, char * obuf);
long xrecv(char * buf, long cnt,int fd);
