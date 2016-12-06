#include <time.h>
#include <string.h>
#include <stdio.h>
#include "console.h"
#include <stdbool.h>
#include <inttypes.h>
#include "segment.h"
#include "cpu.h"
#include "process.h"
#include "start.h"

int32_t pid_actif = 0;
int pid_a_creer = 0;
/**
* Première partie de gestion des processus
*/
/*
void idle(void) {
  printf("[idle] je tente de passer la main a proc1...\n");
  ctx_sw(tab[0].contexte, tab[1].contexte);
}

void proc1(void) {
  printf("[proc1] idle m’a donne la main\n");
  printf("[proc1] j’arrete le systeme\n");
  hlt();
}
*/
/**
*Deuxième partie de gestion des processus
*/
/*
void idle(void) {
  for (int i = 0; i < 3; i++) {
    printf("\n[idle] je tente de passer la main a proc1...\n");
    ctx_sw(tab[0].contexte, tab[1].contexte);
    printf("\n[idle] proc1 m’a redonne la main\n");
  }
  printf("[idle] je bloque le systeme\n");
  hlt();
}
void proc1(void) {
  for (;;) {
    printf("\n[proc1] idle m’a donne la main\n");
    printf("[proc1] je tente de lui la redonner...\n");
    ctx_sw(tab[1].contexte, tab[0].contexte);
  }
}
*/
/**
*Troisième partie de gestion des processus : politique d'ordonnancement
*/
/*
void idle(void) {
  for (;;) {
    printf("\n[%s] pid = %i\n", mon_nom(), mon_pid());
    ordonnance();
  }
}
void proc1(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    ordonnance();
  }
}

void proc2(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    ordonnance();
  }
}

void proc3(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    ordonnance();
  }
}
*/
/**
*Quatrième partie de gestion des processus : politique d'ordonnancement
*/
/*
void idle(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    sti();
    hlt();
    cli();
  }
}
void proc1(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    sti();
    hlt();
    cli();
  }
}
void proc2(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    sti();
    hlt();
    cli();
  }
}
void proc3(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    sti();
    hlt();
    cli();
  }
}
*/
<<<<<<< HEAD
/**
*Cinquième partie gestion des processus
=======

/**
*Cinquième partie de gestion des processus
>>>>>>> b87755b57f5be51455b983c817bc9680255f5eab
*/
void idle() {
  for (;;) {
    sti();
    hlt();
    cli();
  }
}
void proc1(void) {
<<<<<<< HEAD
  //for (;;) {
  for (int32_t i = 0; i < 2; i++){
=======
  for (;;) {
>>>>>>> b87755b57f5be51455b983c817bc9680255f5eab
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
    mon_nom(), mon_pid());
    dors(2);
  }
<<<<<<< HEAD
  fin_processus();
  //}
}
void proc2(void) {
// for (;;) {
for (int32_t i = 0; i < 2; i++){
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
    mon_nom(), mon_pid());
    dors(3);
}
    fin_processus();
//  }
}
void proc3(void) {
  //for (;;) {
  for (int32_t i = 0; i < 2; i++){
=======
}
void proc2(void) {
  for (;;) {
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
    mon_nom(), mon_pid());
    dors(3);
  }
}
void proc3(void) {
  for (;;) {
>>>>>>> b87755b57f5be51455b983c817bc9680255f5eab
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
    mon_nom(), mon_pid());
    dors(5);
  }
<<<<<<< HEAD
    fin_processus();
  //}
=======
>>>>>>> b87755b57f5be51455b983c817bc9680255f5eab
}
/**
*fonction pour créer et initialiser les processus
*/
int32_t cree_processus(void (*code)(void), char *nom) {
  int i;
  if(pid_a_creer == NB_PROC -1) {
    return -1;
  }
  else {
      i = pid_a_creer +1;
      tab[i].pid = i;
      strcpy(tab[i].nom,nom);
      tab[i].etat = ACTIVABLE;
      tab[i].contexte[1] =(int)(&(tab[i].pile[511]));
      //la case en sommet de pile doit contenir l’adresse de la fonction proc1
      tab[i].pile[511] = (uint32_t)(code);
      pid_a_creer++;
      return pid_a_creer;
  }
}
/**
*fonction pour endormir le processus appelant pdt nbr_secs
*/
void dors(uint32_t nbr_secs) {
  tab[pid_actif].temps_reveil = nbr_secondes() + nbr_secs;
  tab[pid_actif].etat = ENDORMI;
  ordonnance();
}

void elir(uint32_t pid) {
	tab[pid].etat = ELU;
	pid_actif = pid;
}
/**
*Fonction qui retourne le pid du processus en cours d'exécution
*/
int32_t mon_pid(void) {
  int32_t le_pid;
  for (int i = 0; i < NB_PROC; i++) {
    if (tab[i].etat == ELU) {
      le_pid = (int32_t)(tab[i].pid);
    }
  }
  return le_pid;
}

/*
*Fonction qui retourne le nom du processus en cours d'exécution
*/
char *mon_nom(void) {
  char *elu;
  for (int i = 0; i < NB_PROC; i++) {
    if (tab[i].etat == ELU) {
      elu = (char*)(tab[i].nom);
    }
  }
  return elu;
}
/**
*fonction qui endors le processus appelant
*/
void dors(uint32_t nbr_secs) {
  tab[pid_actif].temps_reveil = nbr_secs + nbr_secondes();
  tab[pid_actif].etat = ENDORMI;
  ordonnance();
}
/**
*fonction qui termine un processus en le plaçant dans l'etat mort
*/
void fin_processus(void) {
  tab[pid_actif].etat = MORT;
  ordonnance();
}
/**
*Implantation de la politique d'ordonnancement collaboratif
*/
void ordonnance(void) {
<<<<<<< HEAD
  process temps;
  int i;
  int32_t activable;
  pid_actif = mon_pid();
  while(tab[pid_actif].etat == ENDORMI && tab[pid_actif].temps_reveil <= nbr_secondes()) {
    i = (pid_actif + 1)%NB_PROC;
    activable = (i + 1)%NB_PROC;
    temps = tab[i];
    temps.etat = ACTIVABLE;
    tab[activable].etat = ELU;
    ctx_sw(temps.contexte, tab[activable].contexte);
    pid_actif = activable;
  }
  if(tab[pid_actif].etat == MORT) {
    pid_actif = (pid_actif + 1)%NB_PROC;
  }
  activable = (pid_actif + 1)%NB_PROC;
  tab[pid_actif].etat = ACTIVABLE;
  tab[(pid_actif + 1)%NB_PROC].etat = ELU;
  ctx_sw(tab[pid_actif].contexte, tab[activable].contexte);

/*  for (i = 0; i < NB_PROC; i++) {
    if (tab[i].etat == ENDORMI){
      j = 0;
      while(j <= tab[i].temps_reveil) {
        j++;
      }
      tab[i].etat = ACTIVABLE;
    }
    else {
      pid_actif = mon_pid();
      activable = (pid_actif + 1)%NB_PROC;
      tab[pid_actif].etat = ACTIVABLE;
      tab[(pid_actif + 1)%NB_PROC].etat = ELU;
      ctx_sw(tab[pid_actif].contexte, tab[activable].contexte);
    }
  }*/
=======
  process temp;
  int32_t activable;
  int32_t new_process = 0;
  //pid_actif = mon_pid();
  activable = (pid_actif + 1)%NB_PROC;
  while(activable != pid_actif) {
    temp = tab[activable];
    activable = (activable + 1)%NB_PROC;
    if(temp.etat == ENDORMI && temp.temps_reveil <= nbr_secondes()) {
      temp.etat = ACTIVABLE;
    }
  }
  // on prend le premier processus eligible
	activable = (pid_actif + 1)%NB_PROC;
	while(activable != pid_actif) {
		temp = tab[activable];
		activable = (activable + 1)%NB_PROC;

		if(temp.etat == ACTIVABLE) {
			new_process = (activable - 1)%NB_PROC;
			break;
		}
	}
	uint32_t old_process = pid_actif;
	elir(new_process);
  ctx_sw(tab[old_process].contexte, tab[new_process].contexte);
>>>>>>> b87755b57f5be51455b983c817bc9680255f5eab
}
