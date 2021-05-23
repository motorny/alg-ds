#include <stdbool.h>
#include<stdlib.h>
#include <stdio.h> 



typedef struct Fork {
	int worth;
	int prev;
	int itr;
	struct Fork* l;
	struct Fork* r;
} Fork;

Fork* InitFork(int worth) {
	Fork* fresh_fork = (Fork*)malloc(sizeof(Fork));
	if (!fresh_fork)
		return NULL;
	fresh_fork->l = fresh_fork->r = NULL;
	fresh_fork->worth = worth;
	fresh_fork->prev = rand();
	fresh_fork->itr = 1;
	return fresh_fork;

}


int OnIter(Fork* ptr) {
	return ptr ? ptr->itr : 0;
}

void RefreshItr(Fork* ptr) {
	if (ptr)
		ptr->itr = OnIter(ptr->l) + OnIter(ptr->r) + 1;
}

Fork* Fusion(Fork* g, Fork* d) {
	Fork* res = NULL;
	if (!g)
		res = d;
	else if (!d)
		res = g;
	else if (g->prev > d->prev) {
		g->r = Fusion(g->r, d);
		res = g;
	}
	else {
		d->l = Fusion(g, d->l);
		res = d;
	}
	RefreshItr(res);
	return res;
}

void Bust(int pin, Fork* seed, Fork** g, Fork** d, int plus) {
	if (!seed) {
		*g = *d = NULL;
		return;
	}
	int actu_pin = OnIter(seed->l) + plus;
	if (pin <= actu_pin) {
		Bust(pin, seed->l, g, &(seed->l), plus);
		*d = seed;
	}
	else {
		Bust(pin, seed->r, &(seed->r), d, plus + 1 + OnIter(seed->l));
		*g = seed;
	}
	RefreshItr(seed);
}
#define MAX_SIZE 12
#define ERASE 0

#define FIRST_PLUSVAL 0
void Put(int worth, int ps, Fork** seed) {
	Fork* fresh_fork = InitFork(worth);
	Fork* front = NULL;
	Fork* back = NULL;
	if (ps < 0 || !fresh_fork)
		return;
	Bust(ps, *seed, &back, &front, 0);
	*seed = Fusion(Fusion(front, fresh_fork), back);
}

void Display(Fork* seed) {
	if (!seed)
		return;
	Display(seed->l);
	printf("%d ", seed->worth);
	Display(seed->r);
}
#define STILL_USEFUL 1
int Erase(int ps, Fork** seed) {
	int res = 1;
	Fork* ps_itm = NULL;
	Fork* front = NULL;
	Fork* back = NULL;
	Fork* fresh_back = NULL;
	if (ps < 0)
		return res;
	Bust(ps, *seed, &front, &back, 0);
	Bust(1, back, &ps_itm, &fresh_back, 0);
	if (ps_itm) {
		res = 0;
		free(ps_itm);
	}
	*seed = Fusion(front, fresh_back);
	return res;
}

void EraseTree(Fork* seed) {
	if (seed) {
		EraseTree((seed)->l);
		EraseTree((seed)->r);
		free(seed);
		seed = NULL;
	}
}

void Scan(int worth, Fork* seed, bool* hold) {
	if (seed) {
		if (seed->worth == worth)
			*hold = true;
		Scan(worth, seed->l, hold);
		Scan(worth, seed->r, hold);
	}
}

void Get(int worth, Fork* seed, Fork** ans) {
	if (seed && !(*ans)) {
		if (seed->worth == worth) {
			*ans = seed;
		}
		Get(worth, seed->l, ans);
		Get(worth, seed->r, ans);
	}
}

void EraseNetWorth(int worth, Fork** seed, bool* erase) {

	if (*seed && !(*erase)) {
		if ((*seed)->worth == worth) {
			Fork* g = (*seed)->l;
			Fork* d = (*seed)->r;
			free(*seed);
			*seed = Fusion(g, d);
			*erase = true;
			return;
		}
		EraseNetWorth(worth, &((*seed)->l), erase);
		EraseNetWorth(worth, &((*seed)->r), erase);
	}
}

	int main(void) {
		Fork* seed = NULL;
		char* cmd = (char*)malloc(12 * sizeof(char));
		int worth;

		if (!cmd) {
			perror("not enough memory");
			exit(1);
		}
		while (fgets(cmd, 12, stdin)) {
			worth = strtol(cmd + 2, NULL, 10);
			if (cmd[0] == 'a')
				Put(worth, OnIter(seed), &seed);
			else if (cmd[0] == 'r') {
				bool erase = false;
				EraseNetWorth(worth, &seed, &erase);
			}
			else if (cmd[0] == 'f') {
				bool hold = false;
				Scan(worth, seed, &hold);
				if (hold)
					printf("yes\n");
				else
					printf("no\n");
			}
		}

		EraseTree(seed);
		free(cmd);
		return 0;
	}

