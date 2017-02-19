//
// Created by lieroz on 27.11.16.
//

#ifndef LAB_06_COLORMODIFIER_H
#define LAB_06_COLORMODIFIER_H

#include <ostream>

#define BOLD(x) "\033[1m" x "\033[0m"

enum CODE {
	FG_RED     = 31,
	FG_GREEN   = 32,
	FG_YELLOW  = 33,
	FG_BLUE    = 34,
	FG_MAGENTA = 35,
	FG_CYAN    = 36,
	FG_DEFAULT = 39,
	BG_RED     = 41,
	BG_GREEN   = 42,
	BG_YELLOW  = 43,
	BG_BLUE    = 44,
	BG_DEFAULT = 49
};

class ColorModifier {
	private:
		CODE code;

	public:
		ColorModifier(CODE p_code) : code{p_code} {}
		friend std::ostream& operator<<(std::ostream& out, const ColorModifier& mod) {
			return out << "\033[" << mod.code << 'm';
		}
};

// Colors for foreground of output elements
ColorModifier fg_red(FG_RED);
ColorModifier fg_green(FG_GREEN);
ColorModifier fg_yellow(FG_YELLOW);
ColorModifier fg_blue(FG_BLUE);
ColorModifier fg_magenta(FG_MAGENTA);
ColorModifier fg_cyan(FG_CYAN);
ColorModifier fg_default(FG_DEFAULT);

// Colors for background of output elements
ColorModifier bg_red(BG_RED);
ColorModifier bg_green(BG_GREEN);
ColorModifier bg_yellow(BG_YELLOW);
ColorModifier bg_blue(BG_BLUE);
ColorModifier bg_default(BG_DEFAULT);

#endif //LAB_06_COLORMODIFIER_H
