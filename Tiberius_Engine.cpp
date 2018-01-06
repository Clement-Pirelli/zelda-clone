// Tiberius_Engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Engine.h"
#include <SDL.h>

int main(int ac, char** av){
	Engine tiberius;
	tiberius.initialize();
	tiberius.run();
	tiberius.shutdown();
    return 0;
}