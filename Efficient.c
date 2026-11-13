#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
char emptyMessage[256];
uint64_t emptySeed; 
uint64_t zobrist[128][20];
uint64_t zobristEP[32]; //8 on rank 3, 8 on rank 6, * 2 boards
uint64_t zobristCastling[8];
uint64_t zobristToMove[4];
uint64_t zobristBanks[128];
uint64_t currentZobrist;
uint64_t whitePieces1[6];
uint64_t blackPieces1[6];
uint64_t whitePieces2[6];
uint64_t blackPieces2[6];
uint64_t promotedPieces1;
uint64_t promotedPieces2;
bool toMove1;
bool toMove2;
bool castling1[4];
bool castling2[4];
int epSquare1; //-1 if none
int epSquare2;
char* whiteBank1;
char* blackBank1;
char* whiteBank2;
char* blackBank2;
float clocks[4]; //white board 1, black board 1, white board 2, black board 2
typedef struct {
    float eval;
    char message[256];
    float timeTaken;
} Output;
uint64_t largeRand(void) {
    return ((uint64_t)rand() << 48 | (uint64_t)rand() << 32 | (uint64_t)rand() << 16 | (uint64_t)rand());
}
int pieceId(char piece) {
    switch (piece) {
        case 'k': return 0;
        case 'q': return 1;
        case 'r': return 2;
        case 'b': return 3;
        case 'n': return 4;
        case 'p': return 5;
        default: return -1;
    }
}
bool color(int pieceid) {
    return pieceid % 2 == 0;
}
Output evalDepth(int depth, int alpha, int beta) {
    Output out;
    out.eval = 0.0;
    out.timeTaken = 1.0;
    strcpy(out.message, emptyMessage);
    return out;
}
void initialize(void) {
    srand(-0x2B497238);
    strcpy(emptyMessage, "https://www.youtube.com/watch?v=dQw4w9WgXcQ");
    emptySeed = largeRand();
    for (int i = 0; i < 128; i++) {
        zobristBanks[i] = largeRand();
        for (int j = 0; j < 20; j++) zobrist[i][j] = largeRand();
    }
    for (int i = 0; i < 32; i++) zobristEP[i] = largeRand();
    for (int i = 0; i < 4; i++) {
        zobristToMove[i] = largeRand();
        zobristCastling[i*2] = largeRand();
        zobristCastling[i*2+1] = largeRand();
    }
}
int main() {
    printf("BFEN: ");
    char boardNotation[256];
    fgets(boardNotation, sizeof(boardNotation), stdin);
    printf("Do a deep search? ");
    int deepSearch;
    scanf("%d", &deepSearch);
    printf("Initializing...\n");
    initialize();
    printf("done\n");
    printf("Calculating...\n");
    Output display = (deepSearch) ? evalDepth(6, -2147483648, 2147483647) : evalDepth(4, -2147483648, 2147483647);
    printf("Evaluation: %f\nOutput: \n\n%s\n\nin %f seconds", display.eval, display.message, display.timeTaken);
    return 0;
}