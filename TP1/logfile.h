/* file: logfile.h
 * description: gestion du LOG FILE: fichier de trace
 * date: 08/11/97
 * P. Moreaux
 * gnu C UNIX
 */

/* (sous-systeme logfile)
 * nom du fichier de trace: 100 car au plus y compris ".log"
 *
 */

#define LOGFILE


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


extern FILE *logf;                      /* fichier de "log" */
extern char logf_buf[200];              /* tampon de message */
extern time_t logf_date;                /* date courante pour la trace */

extern void logf_write(char *str);      /* ecriture dans le fichier de log */
extern const char *LOGF_TITLE_APPLI;    /* le titre de l'application,
                                         * fourni par elle
                                         */

/* end of file logfile.h */
