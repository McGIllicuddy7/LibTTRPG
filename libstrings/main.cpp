#include <stdio.h>
#include "arena.h"
#include <cstring>
int main(){
	Arena arena;
	for(int i =0; i<12; i++){
		Deletable *a = arena.alloc<Deletable>(i);
	}	
}
