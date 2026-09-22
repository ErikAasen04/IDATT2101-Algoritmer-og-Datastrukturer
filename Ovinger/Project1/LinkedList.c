#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int siffer;
	struct Node *neste;
	struct Node *forrige;
} Node;

typedef struct {
	Node *head;
	Node *tail;
} DobbeltLenketListe;

DobbeltLenketListe lagNyList(void) {
	DobbeltLenketListe tall;
	tall.head = NULL;
	tall.tail = NULL;
	return tall;
}
void leggTilBakerst(DobbeltLenketListe *tall, int siffer) {
	Node *ny = (Node *)malloc(sizeof(Node));
	ny -> siffer = siffer;
	ny -> neste = NULL;
	ny -> forrige = tall -> tail;
	if (tall -> tail == NULL) {
		tall -> head = ny;
		tall -> tail = ny;
	}
	else {
		tall -> tail -> neste = ny;
		tall -> tail = ny;
	}
}

/*
int main() {
	DobbeltLenketListe siffer1 = lagNyList();
	DobbeltLenketListe siffer2 = lagNyList();

}
*/