// JOHN ALEXANDER LE ROUX
#ifndef ANSI_HPP
#define ANSI_HPP

namespace ANSI
{
#define                  ASCII_ESC "\x1b"
#define RESET            ASCII_ESC "[0m"
#define BOLD             ASCII_ESC "[1m"
#define DIM              ASCII_ESC "[2m"
#define ITALIC           ASCII_ESC "[3m"
#define UNDERLINE        ASCII_ESC "[4m"
#define BLINK            ASCII_ESC "[5m"
#define REVERSE          ASCII_ESC "[7m"
#define HIDDEN           ASCII_ESC "[8m"
#define STRIKETHROUGH    ASCII_ESC "[9m"

#define F_BLACK          ASCII_ESC "[30m"
#define F_RED            ASCII_ESC "[31m"
#define F_GREEN          ASCII_ESC "[32m"
#define F_YELLOW         ASCII_ESC "[33m"
#define F_BLUE           ASCII_ESC "[34m"
#define F_MAGENTA        ASCII_ESC "[35m"
#define F_CYAN           ASCII_ESC "[36m"
#define F_WHITE          ASCII_ESC "[37m"
#define F_DEFAULT        ASCII_ESC "[39m"

#define D_BLACK          ASCII_ESC "[40m"
#define D_RED            ASCII_ESC "[41m"
#define D_GREEN          ASCII_ESC "[42m"
#define D_YELLOW         ASCII_ESC "[43m"
#define D_BLUE           ASCII_ESC "[44m"
#define D_MAGENTA        ASCII_ESC "[45m"
#define D_CYAN           ASCII_ESC "[46m"
#define D_WHITE          ASCII_ESC "[47m"
#define D_DEFAULT        ASCII_ESC "[49m"

#define F_BRIGHT_BLACK   ASCII_ESC "[90m"
#define F_BRIGHT_RED     ASCII_ESC "[91m"
#define F_BRIGHT_GREEN   ASCII_ESC "[92m"
#define F_BRIGHT_YELLOW  ASCII_ESC "[93m"
#define F_BRIGHT_BLUE    ASCII_ESC "[94m"
#define F_BRIGHT_MAGENTA ASCII_ESC "[95m"
#define F_BRIGHT_CYAN    ASCII_ESC "[96m"
#define F_BRIGHT_WHITE   ASCII_ESC "[97m"

#define D_BRIGHT_BLACK   ASCII_ESC "[100m"
#define D_BRIGHT_RED     ASCII_ESC "[101m"
#define D_BRIGHT_GREEN   ASCII_ESC "[102m"
#define D_BRIGHT_YELLOW  ASCII_ESC "[103m"
#define D_BRIGHT_BLUE    ASCII_ESC "[104m"
#define D_BRIGHT_MAGENTA ASCII_ESC "[105m"
#define D_BRIGHT_CYAN    ASCII_ESC "[106m"
#define D_BRIGHT_WHITE   ASCII_ESC "[107m"
}

#endif // ANSI_HPP
