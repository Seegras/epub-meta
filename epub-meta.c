/* 
	epub-meta 0.3
	Peter Keel <seegras@discordia.ch>, January 2011

	This program dumps the metadata of an epub-file. It's 
	based on libepub by Ely Levy <elylevy@cs.huji.ac.il>

	compile as: gcc -lpopt -lepub -o epub-meta epub-meta.c

	This Program underlies the MIT-License
	See file COPYING for details.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <popt.h>
#include <epub.h>

#define GETOPT_NUMBER			1010

void quit(int code) {
  epub_cleanup();
  exit(code);
}

static void printHelp(void) {
    fprintf(stderr,"Usage: ebook-meta [OPTION]... [FILE]...\n");
    fprintf(stderr,"-a, --author               print author\n");
    fprintf(stderr,"-c, --contributors         print contributors\n");
    fprintf(stderr,"-d, --date                 print date\n");
    fprintf(stderr,"-e, --desc                 print description\n");
    fprintf(stderr,"-f, --filename             print filename\n");
    fprintf(stderr,"-h, --help                 print this message\n");
    fprintf(stderr,"-i, --id                   print ID\n");
    fprintf(stderr,"-l, --lang                 print language\n");
    fprintf(stderr,"-m, --meta                 print external meta\n");
    fprintf(stderr,"-p, --publisher            print publisher\n");
    fprintf(stderr,"-r, --rights               print rights\n");
    fprintf(stderr,"-s, --subject              print subject\n");
    fprintf(stderr,"-t, --title                print title\n");
    fprintf(stderr,"-v, --verbose              verbose output\n");
    fprintf(stderr,"-y, --type                 print type\n");
    fprintf(stderr,"\n");
    quit(1);
}

/* not in here yet:
EPUB_FORMAT
EPUB_SOURCE
EPUB_RELATION
EPUB_COVERAGE
*/

int main(int argc, char ** argv) {
int rc;
int debug = 0;
/* int help = 0, verbose = 0, meta = 0;*/
int author = 0, contributor = 0, date = 0, desc = 0, filename = 0, help = 0, id = 0, lang = 0, meta = 0, publisher = 0, rights = 0, subject = 0, title = 0, verbose = 0, type = 0;

struct epub *epub;
int size = 1, i;
char ** epubtitle;
char ** epubauthor;
char ** epubid;
char ** epubsubject;
char ** epubpublisher;
char ** epubdate;
char ** epubtype;
char ** epubdescription;
char ** epubformat;
char ** epubsource;
char ** epublang;
char ** epubrelation;
char ** epubcoverage;
char ** epubrights;
char ** epubcontrib;
char ** epubmeta;
int leng, index1, index2; 

char piece[50];

char * leftarg;
char * fname = NULL;
struct poptOption optionsTable[] = {
    { "author", 'a', 0, &author, 0 },
    { "contributor", 'c', 0, &contributor, 0 },
    { "date", 'd', 0, &date, 0 },
    { "desc", 'e', 0, &desc, 0 },
    { "filename", 'f', 0, &filename, 0 },
    { "help", 'h', 0, &help, 0, "gives help" },
    { "id", 'i', 0, &id, 0 },
    { "lang", 'l', 0, &lang, 0 },
    { "meta", 'm', 0, &meta, 0 },
    { "publisher", 'p', 0, &publisher, 0 },
    { "rights", 'r', 0, &rights, 0 },
    { "subject", 's', 0, &subject, 0 },
    { "title", 't', 0, &title, 0 },
    { "verbose", 'v', 0, &verbose, 0 },
    { "type", 'y', 0, &type, 0 },
    { 0, 0, 0, 0, 0 } 
};
poptContext poptcon;

/*--- parameter-processing ----------------------------*/
/*--- argv[dat] points to file, argv[par] to number ---*/

    poptcon = poptGetContext("popti", argc, (const char**) argv, optionsTable, 0);
    while ((rc = poptGetNextOpt(poptcon)) > 0) { 
	switch (rc) {
	    case 'a': 
		author = 1;
		break;
	    case 'c': 
		contributor = 1;
		break;
	    case 'd': 
		date = 1;
		break;
	    case 'e': 
		desc = 1;
		break;
	    case 'f': 
		filename = 1;
		break;
	    case 'h': 
		help = 1;
		break;
	    case 'i': 
		id = 1;
		break;
	    case 'l': 
		lang = 1;
		break;
	    case 'm': 
		meta = 1;
		break;
	    case 'p': 
		publisher = 1;
		break;
	    case 'r': 
		rights = 1;
		break;
	    case 's': 
		subject = 1;
		break;
	    case 't': 
		title = 1;
		break;
	    case 'v': 
		verbose = 1;
		break;
	    case 'y': 
		type = 1;
		break;

	    default:
		fprintf(stderr, "Internal Error with parameter-processing\n");
		quit(1);
	}
    }
    leftarg = poptGetArg(poptcon);
    fname = leftarg;

    poptFreeContext(poptcon);
    if (help) printHelp();


/*--- open file, if impossible, use stdout -------------*/

  if (! fname) {
    fprintf(stderr, "Missing file name %s\n", fname);
    printHelp();
  }

  if (! (epub = epub_open(fname, verbose)))
    quit(1);


if (verbose || filename) {
    printf("File: %s\n", fname);
}

if (verbose || title) {
    if ((epubtitle = epub_get_metadata(epub, EPUB_TITLE, &size))) {
	for (i = 0;i<size;i++) {
	    printf("Title: %s\n", epubtitle[i]);
        }
    }
}
if (verbose || author) {
    if ((epubauthor = epub_get_metadata(epub, EPUB_CREATOR, &size))) {
	for (i = 0;i<size;i++) {
	    printf("Author: %s\n", epubauthor[i]);
	}
    }
}
if (verbose || id) {
    if ((epubid = epub_get_metadata(epub, EPUB_ID, &size))) {
	for (i = 0;i<size;i++) {
	    printf("ID: %s\n", epubid[i]);
	}
    }
}
if (verbose || subject) {
    if ((epubsubject = epub_get_metadata(epub, EPUB_SUBJECT, &size))) {
	for (i = 0;i<size;i++) {
	    if (epubsubject[i][0] != '\0') {
		printf("Subject: %s\n", epubsubject[i]);
	    }
	}
    }
}
if (verbose || publisher) {
    if ((epubpublisher = epub_get_metadata(epub, EPUB_PUBLISHER, &size))) {
	for (i = 0;i<size;i++) {
	    printf("Publisher: %s\n", epubpublisher[i]);
	}
    }
}
if (verbose || date) {
    if ((epubdate = epub_get_metadata(epub, EPUB_DATE, &size))) {
	for (i = 0;i<size;i++) {
	    printf("Date: %s\n", epubdate[i]);
	}
    }
}
if (verbose || type) {
    if ((epubtype = epub_get_metadata(epub, EPUB_TYPE, &size))) {
	for (i = 0;i<size;i++) {
	    printf("Type: %s\n", epubtype[i]);
	}
    }
}
if (verbose) {
    if ((epubformat = epub_get_metadata(epub, EPUB_FORMAT, &size))) {
	for (i = 0;i<size;i++) {
	    if (epubformat[i][0] != '\0') {
		printf("Format: %s\n", epubformat[i]);
	     }
        }
    }
}
if (verbose) {
    if ((epubsource = epub_get_metadata(epub, EPUB_SOURCE, &size))) {
        for (i = 0;i<size;i++) {
	    printf("Source: %s\n", epubsource[i]);
        }
    }
}
if (verbose || lang) {
    if ((epublang = epub_get_metadata(epub, EPUB_LANG, &size))) {
        for (i = 0;i<size;i++) {
	    printf("Lang: %s\n", epublang[i]);
        }
    }
}
if (verbose) {
    if ((epubrelation = epub_get_metadata(epub, EPUB_RELATION, &size))) {
        for (i = 0;i<size;i++) {
	    printf("Relation: %s\n", epubrelation[i]);
	}
    }
}
if (verbose) {
    if ((epubcoverage = epub_get_metadata(epub, EPUB_COVERAGE, &size))) {
        for (i = 0;i<size;i++) {
	    printf("Coverage: %s\n", epubcoverage[i]);
        }
    }
}
if (verbose || rights) {
    if ((epubrights = epub_get_metadata(epub, EPUB_RIGHTS, &size))) {
        for (i = 0;i<size;i++) {
	    printf("Rights: %s\n", epubrights[i]);
        }
    }
}
if (verbose || contributor) {
    if ((epubcontrib = epub_get_metadata(epub, EPUB_CONTRIB, &size))) {
        for (i = 0;i<size;i++) {
	    printf("Contrib: %s\n", epubcontrib[i]);
        }
    }
}
if (verbose || meta) {
    if ((epubmeta = epub_get_metadata(epub, EPUB_META, &size))) {
        for (i = 0;i<size;i++) {
	    printf("Meta: %s\n", epubmeta[i]);
        }
    }
}
if (verbose || desc) {
    if ((epubdescription = epub_get_metadata(epub, EPUB_DESCRIPTION, &size))) {
        for (i = 0;i<size;i++) {
	    if (epubdescription[i][0] != '\0') {
		printf("Desc: %s\n", epubdescription[i]);
	    }
	}
    }
}


  if (! epub_close(epub)) {
    quit(1);
  }


/*--- clean up ---------------------------------*/
quit(0);
return(0);
}
