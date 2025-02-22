/**************************************************************************
 *
 *  $Revision: 1.1 $
 *  $Date: 1999/07/05 02:16:07 $
 *
 **************************************************************************/

#ifndef _ULTRAHOST_H_
#define _ULTRAHOST_H_

#ifdef WIN32 /* { */

int __stdcall uhOpenGame(char *);
int __stdcall uhCloseGame(int);
int __stdcall uhReadGame(int hfd,void *buf,int count);
int __stdcall uhWriteGame(int hfd,void *buf,int count);
int __stdcall uhReadRamrom(int hfd,void *ramrom_adr,void *buf,int count);
int __stdcall uhWriteRamrom(int hfd,void *ramrom_adr,void *buf,int count);
int __stdcall uhPartnerInit(int hfd);
int __stdcall uhPartnerCmd(int hfd,char *ptcmd);
int __stdcall uhGload(int hfd,char *loadfile);

#else /* }{ */
#ifdef PTN64 /* { */

#define	execl		execl_pt

#define uhOpenGame	uhOpenGame_pt
#define uhCloseGame	uhCloseGame_pt

#define uhReadGame	uhReadGame_pt
#define uhWriteGame	uhWriteGame_pt
#define uhReadRamrom	uhReadRamrom_pt
#define uhWriteRamrom	uhWriteRamrom_pt
#define uhPartnerCmd	uhPartnerCmd_pt
#define uhGload		uhGload_pt

int uhPartnerCmd(int,char *);
int uhGload(int,char *);

#endif /* } */

#ifdef __cplusplus
extern "C" {
#endif
int	uhOpenGame(const char *);
int	uhCloseGame(int);

int	uhReadGame(int, void *, int);
int	uhWriteGame(int, void *, int);
int	uhWriteRamrom(int, void *, void*, int);
int	uhReadRamrom(int, void *, void*, int);

#ifdef __cplusplus
}
#endif
#endif /* } */

#endif /* ULTRAHOST */
