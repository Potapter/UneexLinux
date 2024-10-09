#define NCURSES_WIDECHAR 1

#include <curses.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <libgen.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define F 3

int main(int argc, char *argv[]) {
	WINDOW *win;
	wchar_t *buf;
	FILE *fp;
	wchar_t **lines;
	wchar_t c;
	struct stat info;
	int i, j, num_of_lines, Y, cx, cy, size;
	bool done;

	setlocale(LC_ALL, "");

	stat(argv[1], &info);
	buf = calloc(info.st_size + 1, sizeof(wchar_t));
	fp = fopen(argv[1], "rt, css=UTF-8");
	num_of_lines = 0;
	for (size = 0; (c = fgetwc(fp)) != WEOF; size++) {		//Считывание файла в buf
		if (c == L'\n') {
			num_of_lines++;
			c = 0;
		}
		buf[size] = c;
	}
	fclose(fp);
	buf[size] = L'0';

	lines = calloc(num_of_lines + 1, sizeof(wchar_t *));
	lines[0] = buf;
	j = 1;
	for (i = 0; i < size; i++) {		//Формирование lines
		if (!(buf[i])) {
			lines[j] = buf + i + 1;
			j++;
		}
	}

	initscr();
	start_color();
	noecho();
	cbreak();

	win = newwin(LINES - 2*F, COLS - 2*F, F, F);

	mvprintw(0, 0, "%s", argv[1]);
	refresh();

	keypad(win, TRUE);

	done = FALSE;
	Y = cx = cy = c = 0;
	while(!done) {
		werase(win);
		for (i = 0; i <= win->_maxy && i + Y < num_of_lines; i++) {		//Построчный вывод файла
			mvwprintw(win, i, 0, "%4d", i + Y + 1);			//Номер строки
			mvwaddnwstr(win, i, 5, lines[i + Y], win->_maxx - 4);		//Строка
		}
		wmove(win, cy, 5 + cx);			//Перетягивание каретки к началу
		switch(c = wgetch(win)) {		//Обработка нажатий
			case 27:
				done = TRUE;
				break;
			case 338:
				if (Y + win->_maxy < num_of_lines)
					Y = Y + win->_maxy;
				break;
			case 339:
				if (Y - win -> _maxy >= 0)
					Y = Y - win -> _maxy;
				else
					Y = 0;
				break;
			case 258:
				if (Y + 1 < num_of_lines)
					Y = Y + 1;
				break;
			case 259:
				if (Y > 0)
					Y = Y - 1;
				break;
			case 262:
				Y = 0;
				break;
			case 360:
				Y = num_of_lines - win -> _maxy - 1;
				break;
			case 32: if (Y + 5 < num_of_lines)
				Y = Y + 5;
				break;
		}
	}

	free(buf);
	free(lines);
	endwin();

	return 0;
}
