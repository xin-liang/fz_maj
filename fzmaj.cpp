#include "fzmaj.h"
#include "memory.h"
#include "error.h"
#include "input.h"
#include "game.h"
#include "tools.h"
#include "paili.h"

#include "string.h"
#include "ctype.h"
#include "style_command.h"

using namespace FZMAJ_NS;

FZMAJ::FZMAJ(int narg, char **arg)
{
	memory = new Memory(this);
	error = new Error(this);

	screen = stdout;
	logfile = NULL;
	infile = stdin;

	int inflag = 0;
	int logflag = 0;
	int helpflag = 0;

	int iarg = 1;

	while (iarg < narg) {
		if (!strcmp(arg[iarg],"-in") ||
		    !strcmp(arg[iarg],"-i")) {
			if (iarg+2 > narg)
				error->all(FLERR, "Invalid command-line argument");

			inflag = iarg + 1;
			iarg += 2;
		} else if (!strcmp(arg[iarg],"-log") ||
				   !strcmp(arg[iarg],"-l")) {
			if (iarg+2 > narg)
				error->all(FLERR, "Invalid command-line argument");
			logflag = iarg + 1;
			iarg += 2;
		} else if (!strcmp(arg[iarg],"-help") ||
				   !strcmp(arg[iarg],"-h")) {
			if (iarg+1 > narg)
				error->all(FLERR, "Invalid command-line argument");
			helpflag = 1;
			iarg += 1;
		} else error->all(FLERR, "Invalid command-line argument");
	}

	if (inflag){
		infile = fopen(arg[inflag],"r");
		if (infile==NULL) {
			char str[128];
			sprintf(str, "Cannot open input script %s",arg[inflag]);
			error->all(FLERR, str);
		}
	}
	if (!logflag) {
		if (!helpflag) {
			logfile = fopen("log.fzmaj","w");
			if (logfile == NULL)
				error->all(FLERR, "Cannot open log.fzmaj for writing");
		}
	}
	else if (!strcmp(arg[logflag],"none"))
			logfile = NULL;
	else {
		logfile = fopen(arg[logflag],"w");
		if (logfile == NULL)
			error->all(FLERR, "Cannot open logfile");
		}
	if (helpflag) {
		if (screen) help();
		error->done();
	}

	input = new Input(this,narg,arg);
    game = new Game(this);
    tools = new Tools(this);
    paili = new Paili(this);
}

FZMAJ::~FZMAJ()
{
	if (logfile) fclose(logfile);
	logfile = NULL;

	if (infile && infile != stdin) fclose(infile);
	delete input;
	delete error;
	delete memory;

	fprintf(screen, "Game destructed");
}

void FZMAJ::help()
{
	fprintf(screen,
		"\nCommand line options:\n\n"
		"-in (or -i) filename				: read input from file, not stdin\n"
		"-help (or -h) 						: print this help message\n"
		"-log (or -l) none/filename 				: where to send log output\n");
}



