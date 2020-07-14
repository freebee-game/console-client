/*
 * Copyright (c) 2020 Brian Callahan <bcallah@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <err.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <term.h>

#include "freebee.h"
#include "version.h"

FILE *daily_save;

char *term;
char foundlist[2000][17], wordlist[2000][17];
char homedir[PATH_MAX];
char letters[8];

int daily;

size_t found, points, total, words;
size_t newbie, novice, fine, skilled, excellent, superb, marvellous, outstanding, queen;

static int
play_daily(void)
{
	int ch;

	putp(clear_screen);
	printf("Welcome to Free Bee %s | https://freebee.fun/\n", VERSION);
	printf("Would you like to play the (d)aily game or a (r)andom game? ");

	ch = getchar();
	while (getchar() != '\n')
		;
	if (ch == 'd' || ch == 'D')
		return 1;

	return 0;
}

int
main(int argc, char *argv[])
{
	int status;

	(void) argc, (void) argv;

	if ((term = getenv("TERM")) == NULL)
		err(1, "getenv");
	setupterm(term, 1, &status);
	if (status == -1)
		errx(1, "setupterm");

	daily = play_daily();

	create_dir();
	create_anagrams();
	set_rank();
	play_game();

	return 0;
}
