#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <getopt.h>
#include <err.h>

#include <mrkcommon/dumpm.h>
#include <mrkcommon/util.h>

#include "diag.h"

static struct option longopts[] = {
    {"file", 1, NULL, 'f'},
    {"help", 0, NULL, 'h'},
    {"dryrun", 0, NULL, 'n'},
    {NULL, 0, NULL, 0},
};

static void
usage(char *progname)
{
    printf("Usage: %s [OPTIONS]\n"
        "\n"
        "Options:\n"
        "  -h, --help        print help message and exit\n"
        "\n",
        basename(progname));
}

int
main(UNUSED int argc, char **argv)
{
    char ch;

    while ((ch = getopt_long(argc, argv, "f:hn", longopts, NULL)) != -1) {
        switch (ch) {
        case 'f':
            TRACE("file: %s", optarg);
            break;

        case 'h':
            usage(argv[0]);
            exit(0);
            break;

        case 'n':
            TRACE("Dry run");
            break;

        case ':':
            /* missing option argument */
            usage(argv[0]);
            errx(1, "Missing option argument");
            break;

        case '?':
            /* unknown option */
            usage(argv[0]);
            errx(1, "Unknown option");
            break;

        default:
            usage(argv[0]);
            errx(1, "Unknown error");
            break;

        }
    }

    argc -= optind;
    argv += optind;

    return 0;
}
