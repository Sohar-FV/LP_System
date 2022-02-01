/* file: ezsem.c
 * description: Code du module 'EZSEM' (easy semaphores)
 * date: 04/12/1997
 * P. Moreaux
 * gnu C UNIX
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifndef LOGFILE
#include "logfile.h"
#endif

#ifndef EZSEM
#include "ezsem.h"
#endif

/* variables globales */
int ezsem_pipe_p[EZSEM_NB][2]; /* tubes pour P */
int ezsem_pipe_v[EZSEM_NB][2]; /* tubes pour V */
int ezsem_p_ack;               /* memorisation de l'acquittement de P */
pid_t ezsem_pids[EZSEM_NB];    /* les pid des gestionnaires de semaphores */
int ezsem_trace_level;       /* niveau de tracage: 2, 1 ou 0 */

/* prototypes des fonctions internes a ezsem.c */
void ezsem_run(int i);
void ezsem_wake_up(int);



/* fonctions appelees par l'application
 * ezsem_init, ezsem_init_counter, ezsem_P, ezsem_V, ezsem_end
 *
 */
/* initialise le systeme de semaphores */
int ezsem_init(FILE *logfile, int trace_level)
    {
    int i;

    /* tracer ou non */
    ezsem_trace_level = trace_level;

    if (ezsem_trace_level > 0)
        {
        sprintf(logf_buf,
                "Systeme de semaphores (EZSEM): tracage active au niveau %d.\n",
                ezsem_trace_level);
        logf_write(logf_buf);
        }

    /* initialiser l'acquittement de P a FAUX */
    ezsem_p_ack = 0;

    /* installer le traitant de EZSEM_SIGNAL_P */
    signal(EZSEM_SIGNAL_P, ezsem_wake_up);


    for (i=0; i < EZSEM_NB; i++)
        {
        if (ezsem_trace_level == 2)
            {
            sprintf(logf_buf,
                    "EZSEM: creation des tubes et du gestionnaire %d de semaphore\n",
                    i);
            logf_write(logf_buf);
            }

        /* - creer le gestionnaire du semaphore i */
        /* -- creer les tubes pour P et V */
        pipe(ezsem_pipe_p[i]);
        pipe(ezsem_pipe_v[i]);
        /* -- creer le processus gestionnaire du semaphore i */
        if ((ezsem_pids[i] = fork()) == -1)
            {
            /* erreur en creation du processus: arret */
            fprintf(stderr,"Init. semaphores: erreur en creation du semaphore %d. Arret.\n", i);
            fflush(stderr);
            exit(-i-10);
            }
        /* lancer le gestionnaire sans retour */
        if (ezsem_pids[i] == 0) ezsem_run(i);
        /* pere: fermer les tubes en lecture */
        close(ezsem_pipe_p[i][0]);
        close(ezsem_pipe_v[i][0]);
        }
    /* pere */
    /* les seuls tubes ouverts le sont en ecriture: OK */

    if (ezsem_trace_level == 2)
        {
        logf_write("EZSEM: initialisations des semaphores termines.\n");
        }

    return(1);
    } /* ezsem_init */


/* initialise le compteur du semaphore */
void ezsem_init_counter(int i, int init_value)
    {
    /* placer init_value fois un entier (quelconque) dans le tube
     * ezsem_pipe_v[i][1];
     */
    int tmp = 1;
    int j;

    for (j=0; j < init_value; j++)
        write(ezsem_pipe_v[i][1], &tmp, sizeof(int));
    if (ezsem_trace_level == 2)
        {
        sprintf(logf_buf,
                "EZSEM: semaphore %d: compteur initialise a %d\n",
                i, init_value);
        logf_write(logf_buf);
        }
    } /* ezsem_init_counter */


/* procedure P(s) */
void ezsem_p(int i)
    {
    pid_t my_pid;

    if (ezsem_trace_level >= 1)
        {
        sprintf(logf_buf,
                "EZSEM: semaphore %d: debut d'execution de P par le processus %d\n",
                i, getpid());
        logf_write(logf_buf);
        }
    my_pid = getpid();
    write(ezsem_pipe_p[i][1], &my_pid, sizeof(pid_t));
    if (ezsem_trace_level >= 1)
        {
        time(&logf_date);
        sprintf(logf_buf,
                "EZSEM: semaphore %d: processus %d: fin de P ou endormi a: %s",
                i, getpid(), ctime(&logf_date));     /* ctime ajoute \n */
        logf_write(logf_buf);
        }
    while (ezsem_p_ack == 0){ sleep(1); } /* attente du signal du gestionnaire du semaphore */
    ezsem_p_ack = 0; /* reinitialiser l'acquittement : correct! */
    if (ezsem_trace_level >= 1)
        {
        time(&logf_date);
        sprintf(logf_buf,
                "EZSEM: semaphore %d: fin de P par le processus %d a: %s",
                i, getpid(), ctime(&logf_date));     /* ctime ajoute \n */
        logf_write(logf_buf);
        }
    } /* ezsem_p */


/* procedure V(s) */
void ezsem_v(int i)
    {
    int tmp;

    if (ezsem_trace_level >= 1)
        {
        time(&logf_date);
        sprintf(logf_buf,
                "EZSEM: semaphore %d: execution de V par le processus %d a: %s",
                i, getpid(), ctime(&logf_date));     /* ctime ajoute \n */
        logf_write(logf_buf);
        }
    tmp = 1;
    write(ezsem_pipe_v[i][1], &tmp, sizeof(int));
    } /* ezsem_v */


/* ferme le systeme de semaphores */
void ezsem_end(void)
    {
    int i, nb_dead, tmp;
    pid_t dead;

    if (ezsem_trace_level == 2)
        {
        logf_write("EZSEM: debut de fermeture.\n");
        }

    for (i=0; i < EZSEM_NB; i++)
        {
        /* fermer les tubes du processus racine en ecriture */
        close(ezsem_pipe_p[i][1]);
        close(ezsem_pipe_v[i][1]);
        }
    /* attendre la mort des EZSEM_NB gestionnaires de semaphores
     * non indispensable mais
     * assure qu'ils sont bien morts des la fin du processus racine
     * sinon il faut attendre quelques secondes apres
     * la fin du proc. racine
     * on attend ici tant qu'au moins un processus possede un descripteur
     * ouvert sur un tube (en ecriture)
     */
    nb_dead = 0;
    while (nb_dead != EZSEM_NB)
      {
      dead = wait(&tmp);
      /* le mort est-il un gestionnaire de semaphore ?
       * si oui: le compter
       */
      for (i = 0; i < EZSEM_NB; i++)
        {
        if (dead == ezsem_pids[i])
          {
          ezsem_pids[i] = 0; /* le marquer mort */
          nb_dead++; /* un de plus */
          break;            /* quitter le for */
          }
        }
       } /* tous les gestionnaires sont morts */

    if (ezsem_trace_level == 2)
        {
        logf_write("EZSEM: systeme de semaphores ferme.\n");
        }
    } /* ezsem_end */



/* fonctions internes au module EZSEM
 *
 */
/* traitant de EZSEM_SIGNAL_P d'un processus utilisateur des semaphores
 * le semaphore vient de reveiller le processus endormi sur P
 * OU le signal parvient AVANT que le processus ne se soit endormi
 * => MEMORISER cette arrivee de signal
 * le procesus utilisateur est le seul destinataire du signal
 */
void ezsem_wake_up(int x)
    {
    /* reinstaller le traitant (sysV) */
    signal(EZSEM_SIGNAL_P, ezsem_wake_up);
    if (ezsem_trace_level >= 1)
        {
        sprintf(logf_buf,
                "EZSEM: processus %d: je me reveille pour quitter P\n", getpid());
        logf_write(logf_buf);
        }
    /* memoriser l'arrivee du signal pour l'unique semaphore concerne */
    ezsem_p_ack = 1; /* memoriser l'arrivee du signal */
    } /* ezsem_wake_up */


/* code du gestionnaire du semaphore i
 *
 */
void ezsem_run(int i)
    {
    int j, tmp_v;       /* pour lectures dans ezsem_pipe_v */
    pid_t pid_p;        /* pid de l'appelant de P */
    int nbrc;           /* nombre de caracteres lus au cours d'un read */

    /* intialisations du gestionnaire */
    if (ezsem_trace_level == 2)
        {
        sprintf(logf_buf,
                "EZSEM: semaphore %d. Pid = %d; Initialisations...\n", i, getpid());
        logf_write(logf_buf);
        }

    /* fermer les tubes inutiles */
    for (j=0; j<=i; j++)
        {
        /* tous les tubes < i ont ete fermes en lecture par ezsem_init
         * il reste a les fermer en ecriture
         * fermer aussi ceux pour i
         */
        close(ezsem_pipe_p[j][1]);
        close(ezsem_pipe_v[j][1]);
        }

    /* boucle du gestionnaire:
     * sortie par lecture dans tube vide
     */
    if (ezsem_trace_level == 2)
        {
        sprintf(logf_buf,
                "EZSEM: semaphore %d. Entree dans la boucle principale...\n", i);
        logf_write(logf_buf);
        }
    while (1)
        {
        /* attendre une autorisation ( = V(i)) */
        nbrc = read(ezsem_pipe_v[i][0], &tmp_v, sizeof(int));
        if (nbrc != sizeof(int))
          {
          /* tube ferme pendant le read bloquant =>
           * fin du systeme de semaphores: terminer
           */
          exit(0);
          }

        if (ezsem_trace_level >= 1)
            {
            sprintf(logf_buf,
                    "EZSEM: semaphore %d. Compteur > 0.\n", i);
            logf_write(logf_buf);
            }
        /* un V(i) a ete execute: attendre pour reveiller */
        nbrc = read(ezsem_pipe_p[i][0], &pid_p, sizeof(pid_t));
        if (nbrc != sizeof(pid_t))
          {
          /* tube ferme pendant le read bloquant =>
           * fin du systeme de semaphores: terminer
           */
          exit(0);
          }

        /* un P a ete execute par le processus de pid pid_p: le reveiller */
        if (ezsem_trace_level >= 1)
            {
            sprintf(logf_buf,
                    "EZSEM: semaphore %d. Je reveille le processus %d, endormi par P\n",
                    i, pid_p);
            logf_write(logf_buf);
            }
        kill(pid_p, EZSEM_SIGNAL_P);
        } /* while */
    /* fin du semaphore par reception du signal de mort */
    } /* ezsem_run */

/* end of file ezsem.c */