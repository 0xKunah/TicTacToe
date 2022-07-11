#include <stdio.h>
#include <stdbool.h>

int scores[2] = {0,0};
char players[2][50] = {"Joueur 1", "Joueur 2"};
char symbols[2] = {'x', 'o'};
char plays[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void board(){
    printf(" %c | %c | %c\n",plays[0],plays[1],plays[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n",plays[3],plays[4],plays[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n",plays[6],plays[7],plays[8]);
}

bool win(){ // Vérifie si l'un des deux joueurs à gagné
    if(
        (plays[0]==plays[1] && plays[1]==plays[2]) || // Première ligne
        (plays[3]==plays[4] && plays[4]==plays[5]) || // Deuxième ligne
        (plays[6]==plays[7] && plays[7]==plays[8]) || // Troisième ligne
        (plays[0]==plays[3] && plays[3]==plays[6]) || // Première colonne
        (plays[1]==plays[4] && plays[4]==plays[5]) || // Deuxième colonne
        (plays[8]==plays[5] && plays[5]==plays[8]) || // Troisième colonne
        (plays[0]==plays[4] && plays[4]==plays[8]) || // Première diagonale
        (plays[2]==plays[4] && plays[4]==plays[6])    // Deuxième diagonale
    ){
        return true;
    } else return false;
}

void score(){
    printf("---------------------------------------------------------\n");
    printf("|      Score de %s: %d     |     Score de %s: %d     |\n", players[0], scores[0], players[1], scores[1]);
    printf("---------------------------------------------------------\n");
}

void blank(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void setup(){
    // Les joueurs choisissent leur nom
    printf("Nom du 1er joueur (%s):\n> ", players[0]);
    scanf_s("%s", &players[0]);
    printf("Nom du 2e joueur (%s):\n> ", players[1]);
    scanf_s("%s", &players[1]);
}

void turn(int i){
    // Les i%2 retournent 0 ou 1, donc me permettent de récupérer le symbole/pseudo du joueur en train de jouer son tour
    int choice;
    printf("C'est le tour de %s\nChoisis la case sur laquelle tu veux jouer\n> ", players[i%2]);
    scanf_s("%d",&choice);
    if(choice < 1 || choice > 9){
        printf("Choisis une case valide! \n");
        turn(i);
    }
    choice -=1; // Corrige la différence d'index (La case 1 avait l'index 0, donc en jouant la case 1 on jouait la 2e)
    if(plays[choice] != symbols[0] && plays[choice] != symbols[1]){ // Vérifie si la case n'est pas déja jouée
        plays[choice] = symbols[i%2];
    } else { // Si la case est déja jouée, récursion qui fait recommencer le tour
        printf("Cette case est d\202ja jou\202e ! Choisis en une autre\n");
        turn(i);
    }
};

void reset(){
    plays[0] = '1';
    plays[1] = '2';
    plays[2] = '3';
    plays[3] = '4';
    plays[4] = '5';
    plays[5] = '6';
    plays[6] = '7';
    plays[7] = '8';
    plays[8] = '9';
}

void game(){
    int i = 0;
    while(!win()){
        blank();
        score();
        board();
        turn(i);
        i+=1;
    }
    blank();
    scores[(i-1)%2] += 1;
    score();
    board();
    char c;
    printf("%s a gagn\202, bravo !\n On en refait une ? (y/n)\n>", players[(i-1)%2]);
    scanf(" %c",&c);
    if(c == 'y'){
        reset();
        game();
    } else printf("Ca marche, bisous !");
}

int main() {
    setup();
    game();
    return 0;
}
