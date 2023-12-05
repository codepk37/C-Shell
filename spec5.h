#ifndef __SPEC5_H
#define __SPEC5_H

struct CommandHistory {
    char history[15][MAX_COMMAND_LENGTH];
    int size;
    int current;
};
void initHistory(struct CommandHistory *history) ;
void tokenize_solve(char input[200]);
void addToHistory(struct CommandHistory *history, const char *command) ;
void loadHistoryFromFile(struct CommandHistory *history) ;
void saveHistoryToFile(const struct CommandHistory *history);
void displayHistory(struct CommandHistory *history);
char * executeFromHistory(struct CommandHistory *history, int index) ;
int parseIndexFromCommand(const char *command) ;
char* execute_pastevents(char* inp,int in);

#endif
