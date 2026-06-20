#include "utils.h"

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void esperarEnter(void) {
    getchar();
}

void limparTela(void) {
    system(CLEAR_COMMAND);
#ifndef _WIN32
    printf("\033[3J");
    fflush(stdout);
#endif
}


// Prototypes added as per instruction
int visible_strlen(const char* s);
int lerInteiro(const char* mensagem, int min, int max);

int lerInteiro(const char* mensagem, int min, int max) {
    char buffer[MAX_LINE_BUFFER];
    long valor;
    char* endptr;

    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            continue;
        }

        // Remover \n se existir, ou limpar buffer se a entrada for maior que o esperado
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            limparBufferEntrada();
        }

        if (buffer[0] == '\0') continue;

        errno = 0;
        valor = strtol(buffer, &endptr, 10);

        if (errno == ERANGE || *endptr != '\0' || endptr == buffer) {
            printf("Entrada inválida! Por favor, digite um número inteiro.\n");
        } else if (valor < min || valor > max) {
            printf("Valor fora do intervalo permitido (%d-%d). tente novamente.\n", min, max);
        } else {
            return (int)valor;
        }
    }
}

void lerString(const char* mensagem, char* buffer, int tamanhoMax) {
    printf("%s", mensagem);
    if (fgets(buffer, tamanhoMax, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        limparBufferEntrada();
    }
}

void delaySimples(int milliseconds) {
    long pause;
    clock_t now, then;
    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while ((now - then) < pause)
        now = clock();
}

int visible_strlen(const char* s) {
    if (s == NULL) return 0;
    int len = 0;
    const char* p = s;
    while (*p) {
        if (*p == '\033') {
            p++;
            if (*p == '[') {
                p++;
                while (*p && (*p < 'A' || *p > 'Z') && (*p < 'a' || *p > 'z')) p++;
                if (*p) p++;
                continue;
            }
        }
        if ((*p & 0xc0) != 0x80) {
            len++;
        }
        p++;
    }
    return len;
}

unsigned int calcularChecksum(const char* data) {
    unsigned int hash = 2166136261U;
    for (int i = 0; data[i] != '\0'; i++) {
        hash ^= (unsigned char)data[i];
        hash *= 16777619U;
    }
    return hash;
}

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

int obterTecla(void) {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

KeyCode lerTeclaMenu(void) {
    int ch = obterTecla();
    
    if (ch == 10 || ch == 13) {
        return KEY_ENTER;
    }
    if (ch == 'q' || ch == 'Q') {
        return KEY_Q;
    }
    if (ch == '0') {
        return KEY_0;
    }
    if (ch == 27) { // ESC ou seq de escape no Linux
#ifdef _WIN32
        return KEY_ESC;
#else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
        
        int ch2 = getchar();
        int ch3 = -1;
        if (ch2 == '[') {
            ch3 = getchar();
        }
        
        fcntl(STDIN_FILENO, F_SETFL, flags);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        
        if (ch2 == '[') {
            if (ch3 == 'A') return KEY_UP;
            if (ch3 == 'B') return KEY_DOWN;
            if (ch3 == 'C') return KEY_RIGHT;
            if (ch3 == 'D') return KEY_LEFT;
        }
        return KEY_ESC;
#endif
    }
    
#ifdef _WIN32
    if (ch == 0 || ch == 224) {
        int extra = _getch();
        if (extra == 72) return KEY_UP;
        if (extra == 80) return KEY_DOWN;
        if (extra == 77) return KEY_RIGHT;
        if (extra == 75) return KEY_LEFT;
    }
#endif

    return KEY_OTHER;
}
