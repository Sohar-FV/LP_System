/* file: ezsem.h
 * description: interface pour l'utilisation du module 'EZSEM'
 * date: 04/12/1997
 * P. Moreaux
 * gnu C UNIX
 */


/* EZSEM (EaSy SEMaphores)
 * Specifications
 * les semaphores sont crees en debut d'execution, dans l'ordre de 0 a EZSEM_NB
 * en cas d'erreur pendant la creation du semaphore i, le programme
 * est arrete, avec comme valeur de retour -i-10 (pour distinguer 0 a -9)
 *
 * (sous-systeme logfile)
 * nom du fichier de trace: 100 car au plus y compris les ".log"
 *
 * utilise SIGUSR1 pour reveiller les endormis sur P(s)
 *   donc, ne pas utiliser SIGUSR1
 *
 * interface:
 * appel EZSEM_INIT(FILE *logfile, trace_level)
 *       pour initialiser le systeme de semaphores:
 *       trace_level = 0 pas de trace,
 *                     1 tracage des appels P et V
 *                     2 tracage complet
 *       on dispose de 10 semaphores reperes par un entier entre 0 et 9
 * appel EZSEM_INIT_COUNTER(i,k) pour initialiser le compteur
 *                             du semaphore i avec la valeur entiere k>=0
 *                             a faire AVANT tout emploi du semaphore i
 * appel EZSEM_P(i) ou EZSEM_V(i)
 * appel EZSEM_END pour fermer le systeme de semaphores
 *   attend qu'aucun autre processus que la racine ne manipule les
 *   les semaphores: non indispensable mais si non appele,
 *   les processus gerant les semaphores meurent apres la fin
 *   du processus racine.
 *
 * Apres la fin d'execution de EZSEM_END, il faut un delai (quelques secondes)
 * pour que les processus de gestion des semaphores soient detruits.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define EZSEM

#ifndef LOGFILE
#include "logfile.h"
#endif


#include <signal.h>

/* nombre de semaphores */
#define EZSEM_NB 10

/* valeur de niveau de tracage par defaut */
#define EZSEM_TL_DFLT 0


/* signal utilise pour reveiller les endormis par P:
 * peut etre modifie, amis attention aux conflits
 */
#define EZSEM_SIGNAL_P SIGUSR1

/* noms simplifies pour l'emploi des semaphores */
#define EZSEM_INIT  ezsem_init
#define EZSEM_INIT_COUNTER ezsem_init_counter
#define EZSEM_END ezsem_end()
#define EZSEM_P ezsem_p
#define EZSEM_V ezsem_v



/* prototypes des fonctions appelables de ezsem.c */
extern int ezsem_init(FILE *logfile, int trace_level);
extern void ezsem_end(void);
extern void ezsem_init_counter(int i, int init_value);
extern void ezsem_p(int i);
extern void ezsem_v(int i);

/* end of file ezsem.h */