/* file: logfile.c
 * description: LOG FILE
 * date: 09/11/1997
 * P. Moreaux
 * gnu C UNIX
 */


/*
 * (sous-systeme logfile)
 * nom du fichier de trace: 100 car au plus y compris les ".log"
 *
 *
 */

#ifndef LOGFILE
#include "logfile.h"
#endif


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


FILE *logf;     /* fichier de log */
char logf_buf[200];  /* tampon de message */
time_t logf_date;   /* DATE Courante pour la trace */

void logf_init(char *fname)
    {
    char log_fname[100];

    strcpy(log_fname,fname);
    strcat(log_fname,".log");
    printf("la trace d'execution sera dans le fichier %s.\n",
            log_fname);
    fflush(stdout);
    if ((logf = fopen(log_fname, "w")) == NULL)
        {
        fprintf(stderr, "erreur (ouverture du fichier log impossible): arret!\n");
        fflush(stderr);
        exit(3);
        }
    sprintf(logf_buf, "%s\n", LOGF_TITLE_APPLI);
    logf_write(logf_buf);
    time(&logf_date);
    sprintf(logf_buf, "Date: %s",ctime(&logf_date));     /* ctime ajoute \n */
    logf_write(logf_buf);
    } /* end of logf_init */

/* utilitaire d'ecriture dans le fichier log */
void logf_write(char *str)
    {
    fprintf(logf, str);
    fflush(logf);
    } /* logf_write */

/* end of logfile.c */

