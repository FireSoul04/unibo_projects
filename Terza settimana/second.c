#include <stdio.h>
#include <ctype.h>

#ifdef _WIN32 // valido sia per 32 che 64 bit
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>

    int getch(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }

    int getche(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }
#endif

int main() {
    char c = ' ';
    int alphaNums = 0,
        alphabetChars = 0,
        controlChars = 0,
        notControlChars = 0,
        digits = 0,
        graphChars = 0,
        lowerCaseChars = 0,
        upperCaseChars = 0,
        punctuationChars = 0,
        spaces = 0,
        hexDigits = 0;

    do {
        c = getche();
        
        if (isalnum(c)) {
            alphaNums++;
        }
        if (isalpha(c)) {
            alphabetChars++;
        }
        if (iscntrl(c)) {
            controlChars++;
        }
        if (isprint(c)) {
            notControlChars++;
        }
        if (isdigit(c)) {
            digits++;
        }
        if (isgraph(c)) {
            graphChars++;
        }
        if (islower(c)) {
            lowerCaseChars++;
        }
        if (isupper(c)) {
            upperCaseChars++;
        } 
        if (ispunct(c)) {
            punctuationChars++;
        } 
        if (isspace(c)) {
            spaces++;
        }
        if (isxdigit(c)) {
            hexDigits++;
        }
    } while(c != '#');

    printf("\nCaratteri alfanumerici: %d\n", alphaNums);
    printf("Caratteri dell'alfabeto: %d\n", alphabetChars);
    printf("Caratteri di controllo: %d\n", controlChars);
    printf("Caratteri non di controllo: %d\n", notControlChars);
    printf("Caratteri numerici decimali: %d\n", digits);
    printf("Caratteri grafici: %d\n", graphChars);
    printf("Caratteri dell'alfabeto minuscolo: %d\n", lowerCaseChars);
    printf("Caratteri dell'alfabeto maiuscolo: %d\n", upperCaseChars);
    printf("Caratteri simbolici: %d\n", punctuationChars);
    printf("Caratteri di spazio: %d\n", spaces);
    printf("Caratteri numerici esadecimali: %d\n", hexDigits);

    return 0;
}