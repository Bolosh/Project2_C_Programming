#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

const short int number_of_options = 4, number_of_transaction_options = 3, number_of_change_account_options = 3;
char menu_option[5][50], gutter[50], transaction_option[4][50], transaction_detailed[3][50], change_account_options[4][50];
short int selected_color_code, normal_color_code, gutter_color, typing_color, detail_color;
bool hidden_message[1];
char fileName[] = "", MainAcc[] = "Main.txt", Log[] = "Log.txt", Users[] = "Users.txt", current_account[101], Accounts[] = "Accounts.txt", username[101], password[101], name_of_accounts[101][101];
int number_of_transactions, number_of_accounts;

struct{
    struct{
        short int day, month, year;
    }date;
    char description[501], type[10];
    float amount;
}transaction[1000];

void load_db(char fileName[]){
    int i = 0;
    char endl;
    FILE *file = fopen(fileName, "r");
    fscanf(file, "%d%c", &number_of_transactions, &endl);

    while(i < number_of_transactions){
        fscanf(file, "%f %s %d %d %d", &transaction[i].amount, transaction[i].type, &transaction[i].date.day, &transaction[i].date.month, &transaction[i].date.year);
        fscanf(file, "%c", &endl);
        fgets(transaction[i].description, 501, file);
        int j = 0;
        while(transaction[i].description[j] != '\0') j++;
        if(transaction[i].description[j - 1] == '\n')
            transaction[i].description[j - 1] = '\0';
        ++i;
    }
    fclose(file);
}
void save_db(char fileName[]){
    FILE *file = fopen(fileName, "w");
    fprintf(file, "%d\n", number_of_transactions);
    for(int i = 0; i < number_of_transactions; ++i){
        fprintf(file, "%.2f", transaction[i].amount);
        fprintf(file, "\n%s", transaction[i].type);
        fprintf(file, "\n%d %d %d", transaction[i].date.day, transaction[i].date.month, transaction[i].date.year);
        fprintf(file, "\n%s", transaction[i].description);
        fprintf(file, "\n");
    }
    fclose(file);
}
void load_accounts_name(){
    int i = 0;
    char endl;

    FILE* file = fopen(Accounts, "r");
    fscanf(file, "%d%c", &number_of_accounts, &endl);

    while(i < number_of_accounts){
        fgets(name_of_accounts[i], 101, file);
        int j = 0;
        while(name_of_accounts[i][j] != '\0') j++;
        if(name_of_accounts[i][j - 1] == '\n')
            name_of_accounts[i][j - 1] = '\0';
        ++i;
    }
}
void save_accounts(){
    FILE *file = fopen(Accounts, "w");
    fprintf(file, "%d\n", number_of_accounts);
    for(int i = 0; i < number_of_accounts; ++i){
        fprintf(file, "%s", name_of_accounts[i]);
        fprintf(file, "\n");
    }
    fclose(file);
}
void remove_account_at_index(int index){
    int i = index;
    if(i < number_of_accounts){
        while(i < number_of_accounts - 1){
        strcpy(name_of_accounts[i], name_of_accounts[i+1]);
        ++i;
        }
        number_of_accounts--;
    }
}
void add_to_log(char* message){
    FILE* file = fopen(Log, "a");
    fprintf(file, "%s", message);
    fclose(file);
}
char* get_time(){
    time_t current_time = time(NULL);
    char* current_time_string = ctime(&current_time);
    int size = strlen(current_time_string);
    current_time_string[size - 1] = '\0';
    return current_time_string;
}
void initialisation(){
    selected_color_code = 112; // inverted white
    normal_color_code = 7; // normal white
    gutter_color = 14; // yellow
    typing_color = 11; // aqua
    detail_color = 10; // neon green

    strcpy(menu_option[0], "Manage transactions");
    strcpy(menu_option[1], "Generate report");
    strcpy(menu_option[2], "Help");
    strcpy(menu_option[3], "Change account");
    strcpy(menu_option[4], "Exit");

    strcpy(gutter, "Main Account");
    strcpy(current_account, "Main");
    strcpy(fileName, MainAcc);

    strcpy(transaction_option[0], "Show transactions");
    strcpy(transaction_option[1], "Add transaction");
    strcpy(transaction_option[2], "Bank statement");
    strcpy(transaction_option[3], "Close menu");

    strcpy(transaction_detailed[0], "Modify transaction");
    strcpy(transaction_detailed[1], "Delete transaction");
    strcpy(transaction_detailed[2], "Close menu");

    strcpy(change_account_options[0], "Pick an existing account");
    strcpy(change_account_options[1], "Add a new account");
    strcpy(change_account_options[2], "Remove an account");
    strcpy(change_account_options[3], "Close menu");

    load_db(fileName);
    load_accounts_name();
}
void show_console_cursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void text_color(unsigned int code){
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), code);
}
void cls(){
    system("CLS");
}
void force_stop(){
    text_color(normal_color_code);
    cls();
    printf("\n      ");
    text_color(202);
    printf("Program force stopped");
    text_color(normal_color_code);
    printf("\n");
    char* time = get_time();
    add_to_log("[");
    add_to_log(time);
    add_to_log("]   ");
    add_to_log(username);
    add_to_log(" forced stopped the program.\n");
    int c = getch();
    exit(0);
}
void exit_program(){
    save_db(fileName);
    text_color(normal_color_code);
    system("CLS");
    printf("\n\n\n");
    printf("         ____          _              _         \n");
    printf("        |  _ \\        | |            | |       \n");
    printf("        | |_) |  ___  | |  ___   ___ | |__      \n");
    printf("        |  _ <  / _ \\ | | / _ \\ / __|| '_ \\  \n");
    printf("        | |_) || (_) || || (_) |\\__ \\| | | |  \n");
    printf("        |____/  \\___/ |_| \\___/ |___/|_| |_|  \n");
    printf("\n\n");
    printf("%c", 7);
    char* time = get_time();
    add_to_log("[");
    add_to_log(time);
    add_to_log("]   ");
    add_to_log(username);
    add_to_log(" closed the program.\n");
    int c = getch();
}
bool dez_menu(bool hidden_message[], char c){
    if(hidden_message[0] == false && (c == 'd' || c == 'D')){
        hidden_message[0] = true;
        return false;
    }
    else
        if(hidden_message[0] == true && hidden_message[1] == false && (c == 'e' || c == 'E')){
            hidden_message[1] = true;
            return false;
        }
        else
            if(hidden_message[1] == true && (c == 'v' || c == 'V')){
                hidden_message[0] = false;
                hidden_message[1] = false;
                return true;
            }
            else{
                hidden_message[0] = false;
                hidden_message[1] = false;
                return false;
            }
}
void show_dez_menu(){
    cls();
    text_color(normal_color_code);
    printf("\n\n  ");
    for(int i = 0; i < 3; ++i)
        printf(" %c%c%c%c%c%c%c%c%c", (char)176, (char)176, (char)177, (char)177, (char)178, (char)177, (char)177, (char)176, (char)176);
    printf("\n        Developer menu.\n\n   Made by Bolos Mihai-Razvan\n    > Proud member of 911 group  :)");
    printf("\n  ");
    for(int i = 0; i < 3; ++i)
        printf(" %c%c%c%c%c%c%c%c%c", (char)176, (char)176, (char)177, (char)177, (char)178, (char)177, (char)177, (char)176, (char)176);
    int c = getch();
}
void help_menu(){
    cls();
    text_color(gutter_color);
    printf("\n\n                         > Help menu <\n");
    text_color(normal_color_code);
    printf("         "), text_color(detail_color), printf(">"), text_color(normal_color_code), printf(" Movement is done using the arrows keys.\n");
    printf("         "), text_color(detail_color), printf(">"), text_color(normal_color_code), printf(" To show this menu, use the `h` key in any menu.\n");
    printf("         "), text_color(detail_color), printf(">"), text_color(normal_color_code), printf(" Enter a selected menu pressing the `Enter` key.\n");
    printf("         "), text_color(detail_color), printf(">"), text_color(normal_color_code), printf(" To exit any menu, use the `Esc` key.\n");
    printf("         "), text_color(detail_color), printf(">"), text_color(normal_color_code), printf(" In any menu, if consecutive type 'd e v' the 'Developer menu' will show up.\n");
    printf("         "), text_color(detail_color), printf(">"), text_color(normal_color_code), printf(" In the modify option, '0' input dose not change that transaction information.\n");
    printf("         "), text_color(detail_color), printf(">"), text_color(normal_color_code), printf(" To force stop the program press the `End` key.\n");
    printf("         "), text_color(detail_color), printf(">"), text_color(normal_color_code), printf(" Force stopping does not save the modifications in the data base file.\n");
    printf("\n    (Exit with `Esc`)");
    int c = 1;
    while(c != 27){
        c = getch();
        if(dez_menu(hidden_message, c)){
            show_dez_menu();
            c = 27;
        }
        if(c == 224){
            int c1 = getch();
            if(c1 == 79) force_stop();
        }
    }
}
void show_main_menu(int option){
    text_color(normal_color_code);
    printf("\n  ");
    text_color(gutter_color);
    printf("[");
    printf("%s", gutter);
    printf("] ");
    text_color(normal_color_code);
    switch(option){
    case 0:
        text_color(selected_color_code);
        printf("%s", menu_option[0]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", menu_option[1]);
        printf(" | ");
        printf("%s", menu_option[2]);
        printf(" | ");
        printf("%s", menu_option[3]);
        printf(" | ");
        printf("%s", menu_option[4]);
        break;
    case 1:
        text_color(normal_color_code);
        printf("%s", menu_option[0]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", menu_option[1]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", menu_option[2]);
        printf(" | ");
        printf("%s", menu_option[3]);
        printf(" | ");
        printf("%s", menu_option[4]);
        break;
    case 2:
        text_color(normal_color_code);
        printf("%s", menu_option[0]);
        printf(" | ");
        printf("%s", menu_option[1]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", menu_option[2]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", menu_option[3]);
        printf(" | ");
        printf("%s", menu_option[4]);
        break;
    case 3:
        text_color(normal_color_code);
        printf("%s", menu_option[0]);
        printf(" | ");
        printf("%s", menu_option[1]);
        printf(" | ");
        printf("%s", menu_option[2]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", menu_option[3]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", menu_option[4]);
        break;
    case 4:
        text_color(normal_color_code);
        printf("%s", menu_option[0]);
        printf(" | ");
        printf("%s", menu_option[1]);
        printf(" | ");
        printf("%s", menu_option[2]);
        printf(" | ");
        printf("%s", menu_option[3]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", menu_option[4]);
        break;
    }
    text_color(normal_color_code);
}
void show_transaction_menu(int option){
    text_color(0);
    printf("\n\n   %s", gutter);
    printf("  ");
    text_color(normal_color_code);
    switch(option){
    case 0:
        text_color(selected_color_code);
        printf("%s", transaction_option[0]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", transaction_option[1]);
        printf(" | ");
        printf("%s", transaction_option[2]);
        printf(" | ");
        printf("%s", transaction_option[3]);
        break;
    case 1:
        text_color(normal_color_code);
        printf("%s", transaction_option[0]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", transaction_option[1]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", transaction_option[2]);
        printf(" | ");
        printf("%s", transaction_option[3]);
        break;
    case 2:
        text_color(normal_color_code);
        printf("%s", transaction_option[0]);
        printf(" | ");
        printf("%s", transaction_option[1]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", transaction_option[2]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", transaction_option[3]);
        break;
    case 3:
        text_color(normal_color_code);
        printf("%s", transaction_option[0]);
        printf(" | ");
        printf("%s", transaction_option[1]);
        printf(" | ");
        printf("%s", transaction_option[2]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", transaction_option[3]);
        break;
    }
    text_color(normal_color_code);

}
void generate_report(){
    int year;
    char tmp, clear_scanf[10];
    bool ok = true;
    float year_sum = 0.0, biggest_year_expense = 0.0;

    while(ok){
        ok = false;
        cls();
        show_main_menu(1);

        text_color(gutter_color);
        printf("\n\n        Enter the year: ");
        text_color(typing_color);

        if(scanf("%d%c", &year, &tmp) != 2 || tmp != '\n'){
            text_color(normal_color_code);
            printf("\n      ");
            text_color(12);
            printf("Year should be numerical!");
            Sleep(2000);
            text_color(normal_color_code);
            ok = true;
            scanf("%s", clear_scanf);
        }
    }

    text_color(detail_color);
    printf("\n        %s", "Summary for each month of the year: ");
    text_color(normal_color_code);
    printf("%d", year);

    for(int month = 1; month <= 12; ++month){
        float sum = 0;
        for(int i = 0; i < number_of_transactions; ++i){
            if(transaction[i].date.year == year && transaction[i].date.month == month)
                if(strcmp(transaction[i].type, "withdraw") == 0 || strcmp(transaction[i].type, "transfer") == 0 || strcmp(transaction[i].type, "payment") == 0){
                    sum -= transaction[i].amount;
                    if(sum < biggest_year_expense)
                        biggest_year_expense = sum;
                }
                else
                    sum += transaction[i].amount;
        }
        year_sum += sum;
        text_color(normal_color_code);
        printf("\n      ");
        text_color(detail_color);
        switch (month){
        case 1:
            printf(">January:    ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 2:
            printf(">February:   ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 3:
            printf(">March:      ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 4:
            printf(">April:      ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 5:
            printf(">May:        ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 6:
            printf(">June:       ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 7:
            printf(">July:       ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 8:
            printf(">August:     ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 9:
            printf(">September:  ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 10:
            printf(">October:    ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 11:
            printf(">November:   ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        case 12:
            printf(">December:   ");
            text_color(normal_color_code);
            printf("%.2f", sum);
            break;
        }
    }
    text_color(gutter_color);
    printf("\n\n        Total year summary:   ");
    text_color(normal_color_code);
    printf("%.2f", year_sum);
    text_color(gutter_color);
    printf("\n        Biggest year expense: ");
    text_color(normal_color_code);
    printf("%.2f", biggest_year_expense);

    char* time = get_time();
    add_to_log("[");
    add_to_log(time);
    add_to_log("]   ");
    add_to_log(username);
    add_to_log(" generated a report for ");
    char year_str[10];
    sprintf(year_str, "%d", year);
    add_to_log(year_str);
    add_to_log(" in ");
    add_to_log(current_account);
    add_to_log(" account.\n");

    int c = 1;
    while(c != 27){
        c = getch();
        if(dez_menu(hidden_message, c)) show_dez_menu(), c = 27;
        if(c == 'h' || c == 'H') help_menu(), c = 27;
        if(c == 224){
            int c1 = getch();
            if(c1 == 79) force_stop();
        }
    }


}
void show_detailed_transaction(int index_of_transaction){
    int i = index_of_transaction;
    cls();
    text_color(normal_color_code);
    printf("\n      ");
    text_color(detail_color);
    printf("Transaction index:");
    text_color(normal_color_code);
    printf(" %d", i + 1);
    printf("\n\n   ");
    text_color(detail_color);
    printf(">Amount:");
    text_color(normal_color_code);
    printf("  %.2f", transaction[i].amount);
    printf("\n   ");
    text_color(detail_color);
    printf(">Type:");
    text_color(normal_color_code);
    printf("    %s", transaction[i].type);
    printf("\n   ");
    text_color(detail_color);
    printf(">Date:");
    text_color(normal_color_code);
    printf("    %d.%d.%d", transaction[i].date.day, transaction[i].date.month, transaction[i].date.year);
    printf("\n\n   ");
    text_color(detail_color);
    printf(">Description:");
    text_color(normal_color_code);
    printf("  %s", transaction[i].description);
    printf("\n\n        ");
}
void modify_transaction(int index_of_transaction){
    show_console_cursor(true);
    int i = index_of_transaction;
    bool ok = true;
    struct{
        bool amount;
        bool type;
        bool day;
        bool month;
        bool year;
    }jump_over;

    jump_over.amount = false;
    jump_over.type = false;
    jump_over.day = false;
    jump_over.month = false;
    jump_over.year = false;

    char input_type[10], input_description[501];
    int len_read_amount, len_read_day, len_read_month, len_read_year;
    int input_day, input_month, input_year;
    float input_amount;

    while(ok){
        show_detailed_transaction(i);

        ok = false;
        char tmp = '0', clear_scanf[50];

        // Amount
        printf("\n\n        ");
        text_color(gutter_color);
        printf("Amount:");
        text_color(normal_color_code);
        printf("  ");
        text_color(typing_color);

        if(jump_over.amount == false)
            len_read_amount = scanf("%f%c", &input_amount, &tmp);
        else{
            tmp = '\n';
            text_color(typing_color);
            printf("%.2f", transaction[i].amount);
            text_color(normal_color_code);
            printf("\n");
        }

        if(input_amount != 0) transaction[i].amount = input_amount;
        else{
            input_amount = transaction[i].amount;
            show_detailed_transaction(i);
            // Amount
            printf("\n\n        ");
            text_color(gutter_color);
            printf("Amount:");
            text_color(normal_color_code);
            printf("  ");
            text_color(typing_color);
            printf("%.2f", transaction[i].amount);
            text_color(normal_color_code);
            printf("\n");
        }

        if(len_read_amount != 2 || tmp != '\n'){
            text_color(normal_color_code);
            printf("\n      ");
            text_color(12);
            printf("Amount should be numerical data with decimal point!");
            Sleep(2000);
            text_color(normal_color_code);
            ok = true;
            scanf("%s", clear_scanf);
        }
        else{
            jump_over.amount = true;
            // Type
            text_color(normal_color_code);
            printf("        ");
            text_color(gutter_color);
            printf("Type:");
            text_color(normal_color_code);
            printf("    ");
            text_color(typing_color);

            if(jump_over.type == false)
                scanf("%s%c", input_type, &tmp);
            else{
                text_color(typing_color);
                printf("%s", transaction[i].type);
                text_color(normal_color_code);
                printf("\n");
            }

            if(input_type[0] != '0') strcpy(transaction[i].type, input_type);
            else{
                strcpy(input_type, transaction[i].type);
                show_detailed_transaction(i);
                // Amount
                printf("\n\n        ");
                text_color(gutter_color);
                printf("Amount:");
                text_color(normal_color_code);
                printf("  ");
                text_color(typing_color);
                printf("%.2f", transaction[i].amount);
                text_color(normal_color_code);
                printf("\n");
                // Type
                text_color(normal_color_code);
                printf("        ");
                text_color(gutter_color);
                printf("Type:");
                text_color(normal_color_code);
                printf("    ");
                text_color(typing_color);
                printf("%s", transaction[i].type);
                text_color(normal_color_code);
                printf("\n");
            }

            if(transaction[i].type[0] >= 'A' && transaction[i].type[0] <= 'Z')
                transaction[i].type[0] += 32;

            if(strcmp(transaction[i].type, "deposit") == 0 || strcmp(transaction[i].type, "withdraw") == 0 || strcmp(transaction[i].type, "transfer") == 0 || strcmp(transaction[i].type, "payment") == 0){
                jump_over.type = true;
                // Date
                text_color(normal_color_code);
                printf("        ");
                text_color(gutter_color);
                printf("Date:");
                // Day
                text_color(normal_color_code);
                printf(" ");
                text_color(gutter_color);
                printf("Day:      ");
                text_color(typing_color);

                if(jump_over.day == false)
                    len_read_day = scanf("%d%c", &input_day, &tmp);
                else{
                    text_color(typing_color);
                    printf("%d", transaction[i].date.day);
                    text_color(normal_color_code);
                    printf("\n");
                }

                if(input_day != 0) transaction[i].date.day = input_day;
                else{
                    input_day = transaction[i].date.day;
                    show_detailed_transaction(i);
                    // Amount
                    printf("\n\n        ");
                    text_color(gutter_color);
                    printf("Amount:");
                    text_color(normal_color_code);
                    printf("  ");
                    text_color(typing_color);
                    printf("%.2f", transaction[i].amount);
                    text_color(normal_color_code);
                    printf("\n");
                    // Type
                    text_color(normal_color_code);
                    printf("        ");
                    text_color(gutter_color);
                    printf("Type:");
                    text_color(normal_color_code);
                    printf("    ");
                    text_color(typing_color);
                    printf("%s", transaction[i].type);
                    text_color(normal_color_code);
                    printf("\n");
                    // Date
                    text_color(normal_color_code);
                    printf("        ");
                    text_color(gutter_color);
                    printf("Date:");
                    // Day
                    text_color(normal_color_code);
                    printf(" ");
                    text_color(gutter_color);
                    printf("Day:      ");
                    text_color(typing_color);
                    printf("%d", transaction[i].date.day);
                    text_color(normal_color_code);
                    printf("\n");
                }

                if(len_read_day != 2 || tmp != '\n'){
                    text_color(normal_color_code);
                    printf("\n      ");
                    text_color(12);
                    printf("Should input numerical data!");
                    Sleep(2000);
                    text_color(normal_color_code);
                    ok = true;
                    scanf("%s", clear_scanf);
                }
                else{
                    jump_over.day = true;
                    // Month
                    text_color(normal_color_code);
                    printf("              ");
                    text_color(gutter_color);
                    printf("Month:    ");
                    text_color(typing_color);

                    if(jump_over.month == false)
                        len_read_month = scanf("%d%c", &input_month, &tmp);
                    else{
                        text_color(typing_color);
                        printf("%d", transaction[i].date.month);
                        text_color(normal_color_code);
                        printf("\n");
                    }

                    if(input_month != 0) transaction[i].date.month = input_month;
                    else{
                        input_month = transaction[i].date.month;
                        show_detailed_transaction(i);
                        // Amount
                        printf("\n\n        ");
                        text_color(gutter_color);
                        printf("Amount:");
                        text_color(normal_color_code);
                        printf("  ");
                        text_color(typing_color);
                        printf("%.2f", transaction[i].amount);
                        text_color(normal_color_code);
                        printf("\n");
                        // Type
                        text_color(normal_color_code);
                        printf("        ");
                        text_color(gutter_color);
                        printf("Type:");
                        text_color(normal_color_code);
                        printf("    ");
                        text_color(typing_color);
                        printf("%s", transaction[i].type);
                        text_color(normal_color_code);
                        printf("\n");
                        // Date
                        text_color(normal_color_code);
                        printf("        ");
                        text_color(gutter_color);
                        printf("Date:");
                        // Day
                        text_color(normal_color_code);
                        printf(" ");
                        text_color(gutter_color);
                        printf("Day:      ");
                        text_color(typing_color);
                        printf("%d", transaction[i].date.day);
                        text_color(normal_color_code);
                        printf("\n");
                        // Month
                        text_color(normal_color_code);
                        printf("              ");
                        text_color(gutter_color);
                        printf("Month:    ");
                        text_color(typing_color);
                        printf("%d", transaction[i].date.month);
                        text_color(normal_color_code);
                        printf("\n");
                    }

                    if(len_read_month != 2 || tmp != '\n'){
                        text_color(normal_color_code);
                        printf("\n      ");
                        text_color(12);
                        printf("Should input numerical data!");
                        Sleep(2000);
                        text_color(normal_color_code);
                        ok = true;
                        scanf("%s", clear_scanf);
                    }
                    else{
                        jump_over.month = true;
                        // Year
                        text_color(normal_color_code);
                        printf("              ");
                        text_color(gutter_color);
                        printf("Year:     ");
                        text_color(typing_color);

                        if(jump_over.year == false)
                            len_read_year = scanf("%d%c", &input_year, &tmp);
                        else{
                            text_color(typing_color);
                            printf("%d", transaction[i].date.year);
                            text_color(normal_color_code);
                            printf("\n");
                        }

                        if(input_year != 0) transaction[i].date.year = input_year;
                        else{
                            input_year = transaction[i].date.year;
                            show_detailed_transaction(i);
                            // Amount
                            printf("\n\n        ");
                            text_color(gutter_color);
                            printf("Amount:");
                            text_color(normal_color_code);
                            printf("  ");
                            text_color(typing_color);
                            printf("%.2f", transaction[i].amount);
                            text_color(normal_color_code);
                            printf("\n");
                            // Type
                            text_color(normal_color_code);
                            printf("        ");
                            text_color(gutter_color);
                            printf("Type:");
                            text_color(normal_color_code);
                            printf("    ");
                            text_color(typing_color);
                            printf("%s", transaction[i].type);
                            text_color(normal_color_code);
                            printf("\n");
                            // Date
                            text_color(normal_color_code);
                            printf("        ");
                            text_color(gutter_color);
                            printf("Date:");
                            // Day
                            text_color(normal_color_code);
                            printf(" ");
                            text_color(gutter_color);
                            printf("Day:      ");
                            text_color(typing_color);
                            printf("%d", transaction[i].date.day);
                            text_color(normal_color_code);
                            printf("\n");
                            // Month
                            text_color(normal_color_code);
                            printf("              ");
                            text_color(gutter_color);
                            printf("Month:    ");
                            text_color(typing_color);
                            printf("%d", transaction[i].date.month);
                            text_color(normal_color_code);
                            printf("\n");
                            // Year
                            text_color(normal_color_code);
                            printf("              ");
                            text_color(gutter_color);
                            printf("Year:     ");
                            text_color(typing_color);
                            printf("%d", transaction[i].date.year);
                            text_color(normal_color_code);
                            printf("\n");
                        }

                        if(len_read_year != 2 || tmp != '\n'){
                            text_color(normal_color_code);
                            printf("\n      ");
                            text_color(12);
                            printf("Should input numerical data!");
                            Sleep(2000);
                            text_color(normal_color_code);
                            ok = true;
                            scanf("%s", clear_scanf);
                        }
                        else{
                            jump_over.year = true;
                            // Description
                            text_color(normal_color_code);
                            printf("\n        ");
                            text_color(gutter_color);
                            printf("Description:");
                            text_color(normal_color_code);
                            printf("\n          ");
                            text_color(typing_color);
                            scanf("%[^\n]%c", input_description);
                            if(input_description[0] != '0') strcpy(transaction[i].description, input_description);
                            else strcpy(input_description, transaction[i].description);
                            text_color(normal_color_code);
                        }
                    }
                }
            }
            else{
                text_color(normal_color_code);
                printf("\n      ");
                text_color(12);
                printf("Type should be 'deposit', 'withdraw', 'transfer' or 'payment' only!");
                Sleep(2000);
                text_color(normal_color_code);
                ok = true;
            }
        }
    }
    char* time = get_time();
    add_to_log("[");
    add_to_log(time);
    add_to_log("]   ");
    add_to_log(username);
    add_to_log(" modified transaction ");
    char index_of_transaction_str[1001];
    sprintf(index_of_transaction_str, "%d", index_of_transaction);
    add_to_log(index_of_transaction_str);
    add_to_log(" in ");
    add_to_log(current_account);
    add_to_log(" account.\n");

    show_console_cursor(false);
}
void remove_transaction(int index_of_transaction){
    bool ok = true;
    while(ok){
        text_color(normal_color_code);
        cls();
        printf("\n\n        ");
        text_color(12);
        printf("Are you sure you want to delete transaction number");
        text_color(detail_color);
        printf(" %d ", index_of_transaction + 1);
        text_color(12);
        printf("? y/n");
        int c = getch();
        if(c == 'y'){
            for(int i = index_of_transaction; i < number_of_transactions - 1; i++){
                float float_tmp;
                float_tmp = transaction[i].amount;
                transaction[i].amount = transaction[i + 1].amount;
                transaction[i + 1].amount = float_tmp;

                char char_tmp[10];
                strcpy(char_tmp, transaction[i].type);
                strcpy(transaction[i].type, transaction[i + 1].type);
                strcpy(transaction[i + 1].type, char_tmp);

                int int_tmp;
                int_tmp = transaction[i].date.day;
                transaction[i].date.day = transaction[i + 1].date.day;
                transaction[i + 1].date.day = int_tmp;

                int_tmp = transaction[i].date.month;
                transaction[i].date.month = transaction[i + 1].date.month;
                transaction[i + 1].date.month = int_tmp;

                int_tmp = transaction[i].date.year;
                transaction[i].date.year = transaction[i + 1].date.year;
                transaction[i + 1].date.year = int_tmp;

                char long_char_tmp[501];
                strcpy(char_tmp, transaction[i].description);
                strcpy(transaction[i].description, transaction[i + 1].description);
                strcpy(transaction[i + 1].description, char_tmp);
            }
            number_of_transactions--;
            ok = false;
        }
        else ok = false;
    }
    char* time = get_time();
    add_to_log("[");
    add_to_log(time);
    add_to_log("]   ");
    add_to_log(username);
    add_to_log(" removed transaction ");
    char index_of_transaction_str[1001];
    sprintf(index_of_transaction_str, "%d", index_of_transaction-1);
    add_to_log(index_of_transaction_str);
    add_to_log(" in ");
    add_to_log(current_account);
    add_to_log(" account.\n");
}
void show_transaction_detail(int index_of_transaction, int option){
    int i = index_of_transaction;
    show_detailed_transaction(i);

    switch(option){
    case 0:
        text_color(selected_color_code);
        printf("%s", transaction_detailed[0]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", transaction_detailed[1]);
        printf(" | ");
        printf("%s", transaction_detailed[2]);
        break;
    case 1:
        printf("%s", transaction_detailed[0]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", transaction_detailed[1]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", transaction_detailed[2]);
        break;
    case 2:
        printf("%s", transaction_detailed[0]);
        printf(" | ");
        printf("%s", transaction_detailed[1]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", transaction_detailed[2]);
        text_color(normal_color_code);
        break;
    }
}
void focus_on_transaction(int index_of_transaction){
    int option = 0;
    bool ok = true;
    while(ok){
        show_transaction_detail(index_of_transaction, option);
        int c = getch();
        if(dez_menu(hidden_message, c)) show_dez_menu();
        if(c == 27) break;
        if(c == 13){
            if(option == 0) modify_transaction(index_of_transaction);
            else if (option == 1) remove_transaction(index_of_transaction), ok = false;
            else break;
        }
        if(c == 'h' || c == 'H') help_menu();
        if(c == 224){
            int c1 = getch();
            if(c1 == 79) force_stop();
            else if(c1 == 77)
                if(option < 2) option++;
                else option = 0;
            else if(c1 == 75)
                if(option > 0) option--;
                else option = 2;
        }
    }
}
void show_transactions(){
    int i = 0, option = 0, c;
    bool ok = true;
    while(ok){
        cls();
        show_main_menu(0);
        show_transaction_menu(0);
        printf("\n  ");
        i = 0;
        while(i < number_of_transactions){
            text_color(normal_color_code);
            if(i == option)
                text_color(selected_color_code);
            printf("\n%d%s", i + 1,".");
            text_color(normal_color_code);
            if(i < 9) printf("  ");
            else printf(" ");
            text_color(15);
            int printed_caracters = printf("%.2f", transaction[i].amount);
            text_color(normal_color_code);
            for(int j = printed_caracters; j <= 10; ++j)
                printf(" ");
            if(strcmp(transaction[i].type, "deposit") == 0) text_color(160);
            else text_color(192);
            printed_caracters = printf("%s", transaction[i].type);
            text_color(normal_color_code);
            for(int j = printed_caracters; j <= 10; ++j)
                printf(" ");
            text_color(252);
            printf("%d.%d.%d", transaction[i].date.day, transaction[i].date.month, transaction[i].date.year);
            text_color(normal_color_code);
            printf("\n");
            i++;
        }
        c = getch();
        if(dez_menu(hidden_message, c)) show_dez_menu();
        if(c == 27) break;
        if(c == 13) focus_on_transaction(option),option = 0;
        if(c == 'h' || c == 'H') help_menu();
        if(c == 224){
            int c1 = getch();
            if(c1 == 79) force_stop();
            else if(c1 == 80)
                if(option < number_of_transactions - 1) option++;
                else option = 0;
            else if(c1 == 72)
                if(option > 0) option--;
                else option = number_of_transactions - 1;
        }
    }
}
void bank_statement(){
    float sum = 0.0;
    for(int i = 0; i < number_of_transactions; i++){
        if(strcmp(transaction[i].type, "expense") == 0)
            sum = sum - transaction[i].amount;
        else sum = sum + transaction[i].amount;
    }
    printf("\n\n        ");
    text_color(detail_color);
    printf("Avalible balance:");
    text_color(normal_color_code);
    printf(" %.2f", sum);
    int c = 1;
    while(c != 27){
        c = getch();
        if(dez_menu(hidden_message, c)) show_dez_menu(), c = 27;
        if(c == 'h' || c == 'H') help_menu(), c = 27;
        if(c == 224){
            int c1 = getch();
            if(c1 == 79) force_stop();
        }
    }
    char* time = get_time();
    add_to_log("[");
    add_to_log(time);
    add_to_log("]   ");
    add_to_log(username);
    add_to_log(" calculated the balance in ");
    add_to_log(current_account);
    add_to_log(" account.\n");
}
void add_transaction(){
    show_console_cursor(true);
    bool ok = true;
    struct{
        bool amount;
        bool type;
        bool day;
        bool month;
        bool year;
    }jump_over;

    jump_over.amount = false;
    jump_over.type = false;
    jump_over.day = false;
    jump_over.month = false;
    jump_over.year = false;

    int len_read_amount, len_read_day, len_read_month, len_read_year;

    while(ok){
        cls();
        show_main_menu(0);
        show_transaction_menu(1);

        ok = false;
        char tmp = '0', clear_scanf[50];

        // Amount
        printf("\n\n        ");
        text_color(detail_color);
        printf("Amount:");
        text_color(normal_color_code);
        printf("  ");
        text_color(typing_color);

        if(jump_over.amount == false)
            len_read_amount = scanf("%f%c", &transaction[number_of_transactions].amount, &tmp);
        else{
            tmp = '\n';
            text_color(typing_color);
            printf("%.2f", transaction[number_of_transactions].amount);
            text_color(normal_color_code);
            printf("\n");
        }

        if(len_read_amount != 2 || tmp != '\n'){
            text_color(normal_color_code);
            printf("\n      ");
            text_color(12);
            printf("Amount should be numerical data with decimal point!");
            Sleep(2000);
            text_color(normal_color_code);
            ok = true;
            scanf("%s", clear_scanf);
        }
        else{
            jump_over.amount = true;
            // Type
            text_color(normal_color_code);
            printf("        ");
            text_color(detail_color);
            printf("Type:");
            text_color(normal_color_code);
            printf("    ");
            text_color(typing_color);

            if(jump_over.type == false)
                scanf("%s%c", transaction[number_of_transactions].type, &tmp);
            else{
                text_color(typing_color);
                printf("%s", transaction[number_of_transactions].type);
                text_color(normal_color_code);
                printf("\n");
            }

            if(transaction[number_of_transactions].type[0] >= 'A' && transaction[number_of_transactions].type[0] <= 'Z')
                transaction[number_of_transactions].type[0] += 32;

            if(strcmp(transaction[number_of_transactions].type, "deposit") == 0 || strcmp(transaction[number_of_transactions].type, "withdraw") == 0 || strcmp(transaction[number_of_transactions].type, "transfer") == 0 || strcmp(transaction[number_of_transactions].type, "payment") == 0){
                jump_over.type = true;
                // Date
                text_color(normal_color_code);
                printf("        ");
                text_color(detail_color);
                printf("Date:");
                // Day
                text_color(normal_color_code);
                printf(" ");
                text_color(detail_color);
                printf("Day:      ");
                text_color(typing_color);

                if(jump_over.day == false)
                    len_read_day = scanf("%d%c", &transaction[number_of_transactions].date.day, &tmp);
                else{
                    text_color(typing_color);
                    printf("%d", transaction[number_of_transactions].date.day);
                    text_color(normal_color_code);
                    printf("\n");
                }

                if(len_read_day != 2 || tmp != '\n'){
                    text_color(normal_color_code);
                    printf("\n      ");
                    text_color(12);
                    printf("Should input numerical data!");
                    Sleep(2000);
                    text_color(normal_color_code);
                    ok = true;
                    scanf("%s", clear_scanf);
                }
                else{
                    jump_over.day = true;
                    // Month
                    text_color(normal_color_code);
                    printf("              ");
                    text_color(detail_color);
                    printf("Month:    ");
                    text_color(typing_color);

                    if(jump_over.month == false)
                        len_read_month = scanf("%d%c", &transaction[number_of_transactions].date.month, &tmp);
                    else{
                        text_color(typing_color);
                        printf("%d", transaction[number_of_transactions].date.month);
                        text_color(normal_color_code);
                        printf("\n");
                    }

                    if(len_read_month != 2 || tmp != '\n'){
                        text_color(normal_color_code);
                        printf("\n      ");
                        text_color(12);
                        printf("Should input numerical data!");
                        Sleep(2000);
                        text_color(normal_color_code);
                        ok = true;
                        scanf("%s", clear_scanf);
                    }
                    else{
                        jump_over.month = true;
                        // Year
                        text_color(normal_color_code);
                        printf("              ");
                        text_color(detail_color);
                        printf("Year:     ");
                        text_color(typing_color);

                        if(jump_over.year == false)
                            len_read_year = scanf("%d%c", &transaction[number_of_transactions].date.year, &tmp);
                        else{
                            text_color(typing_color);
                            printf("%d", transaction[number_of_transactions].date.year);
                            text_color(normal_color_code);
                            printf("\n");
                        }

                        if(len_read_year != 2 || tmp != '\n'){
                            text_color(normal_color_code);
                            printf("\n      ");
                            text_color(12);
                            printf("Should input numerical data!");
                            Sleep(2000);
                            text_color(normal_color_code);
                            ok = true;
                            scanf("%s", clear_scanf);
                        }
                        else{
                            jump_over.year = true;
                            // Description
                            text_color(normal_color_code);
                            printf("\n        ");
                            text_color(detail_color);
                            printf("Description:");
                            text_color(normal_color_code);
                            printf("\n          ");
                            text_color(typing_color);
                            scanf("%[^\n]%c", transaction[number_of_transactions].description);
                            text_color(normal_color_code);
                        }
                    }
                }
            }
            else{
                text_color(normal_color_code);
                printf("\n      ");
                text_color(12);
                printf("Type should be 'deposit', 'withdraw', 'transfer' or 'payment' only!");
                Sleep(2000);
                text_color(normal_color_code);
                ok = true;
            }
        }
    }
    show_console_cursor(false);
    number_of_transactions++;

    char* time = get_time();
    add_to_log("[");
    add_to_log(time);
    add_to_log("]   ");
    add_to_log(username);
    add_to_log(" added transaction ");
    char nr_str[1001];
    sprintf(nr_str, "%d", number_of_transactions);
    add_to_log(nr_str);
    add_to_log(" in ");
    add_to_log(current_account);
    add_to_log(" account.\n");
}
void transactions_menu(){
    int option = 0;
    bool ok = true;
    while(ok){
        cls();
        show_main_menu(0);
        show_transaction_menu(option);
        int c = getch();
        if(dez_menu(hidden_message, c)) show_dez_menu();
        if(c == 27) break;
        if(c == 13){
            switch(option){
            case 0:
                show_transactions();
                break;
            case 1:
                add_transaction();
                break;
            case 2:
                bank_statement();
                break;
            case 3:
                ok = false;
            }
        }
        if(c == 'h' || c == 'H') help_menu();
        if(c == 224){
            int c1 = getch();
            if(c1 == 79) force_stop();
            else if(c1 == 77)
                if(option < number_of_transaction_options) option++;
                else option = 0;
            else if(c1 == 75)
                if(option > 0) option--;
                else option = number_of_transaction_options;
        }
    }
}
void show_change_account_options(int option){
    text_color(0);
    printf("\n\n   %s", gutter);
    printf("  ");
    text_color(normal_color_code);
    switch(option){
    case 0:
        text_color(selected_color_code);
        printf("%s", change_account_options[0]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", change_account_options[1]);
        printf(" | ");
        printf("%s", change_account_options[2]);
        printf(" | ");
        printf("%s", change_account_options[3]);
        break;
    case 1:
        text_color(normal_color_code);
        printf("%s", change_account_options[0]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", change_account_options[1]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", change_account_options[2]);
        printf(" | ");
        printf("%s", change_account_options[3]);
        break;
    case 2:
        text_color(normal_color_code);
        printf("%s", change_account_options[0]);
        printf(" | ");
        printf("%s", change_account_options[1]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", change_account_options[2]);
        text_color(normal_color_code);
        printf(" | ");
        printf("%s", change_account_options[3]);
        break;
    case 3:
        text_color(normal_color_code);
        printf("%s", change_account_options[0]);
        printf(" | ");
        printf("%s", change_account_options[1]);
        printf(" | ");
        printf("%s", change_account_options[2]);
        printf(" | ");
        text_color(selected_color_code);
        printf("%s", change_account_options[3]);
        text_color(normal_color_code);
        break;
    }
    text_color(normal_color_code);
}
void show_accounts(){
    int i = 0;
    char account_name[101];
    text_color(normal_color_code);
    printf("\n\n");
    while(i < number_of_accounts){
        text_color(normal_color_code);
        printf("        ");
        text_color(detail_color);
        printf("%d.", i+1);
        text_color(normal_color_code);
        int len = strlen(name_of_accounts[i]);
        strcpy(account_name, name_of_accounts[i]);
        account_name[len-4] = '\0';
        strcat(account_name, " Accout");
        printf(" %s\n", account_name);
        ++i;
    }
    printf("\n");
}

void change_account(){
    int option = 0, index;
    char account_name[101];
    bool ok = true;
    while(ok){
        cls();
        show_main_menu(3);
        show_change_account_options(option);
        int c = getch();
        if(dez_menu(hidden_message, c)) show_dez_menu();
        if(c == 27) break;
        if(c == 13){
            switch(option){
            case 0:
                show_accounts();
                text_color(normal_color_code);
                show_console_cursor(true);
                printf("    Account number > ");
                text_color(typing_color);
                scanf("%d", &index);
                show_console_cursor(false);
                text_color(normal_color_code);

                strcat(current_account, ".txt");
                save_db(current_account);

                strcpy(current_account, name_of_accounts[index-1]);
                printf("%s", current_account);
                load_db(current_account);

                strcpy(fileName, current_account);

                strcpy(gutter, current_account);
                int len = strlen(current_account);
                gutter[len-4] = '\0';
                strcat(gutter, " Account");

                current_account[len-4] = '\0';
                break;
            case 1:
                text_color(normal_color_code);
                show_console_cursor(true);
                printf("\n\n    Account name > ");
                text_color(typing_color);
                scanf("%s", account_name);
                show_console_cursor(false);
                text_color(normal_color_code);
                strcat(account_name, ".txt");
                strcpy(name_of_accounts[number_of_accounts], account_name);
                number_of_accounts++;
                FILE* file = fopen(account_name, "w");
                fprintf(file, "%d", 0);
                fclose(file);
                save_accounts();
                break;
            case 2:
                show_accounts();
                text_color(normal_color_code);
                show_console_cursor(true);
                printf("    Account number > ");
                text_color(typing_color);
                scanf("%d", &index);
                show_console_cursor(false);
                text_color(normal_color_code);
                strcpy(account_name, name_of_accounts[index-1]);
                remove_account_at_index(index-1);
                remove(account_name);
                save_accounts();
                break;
            case 3:
                ok = false;
            }
        }
        if(c == 'h' || c == 'H') help_menu();
        if(c == 224){
            int c1 = getch();
            if(c1 == 79) force_stop();
            else if(c1 == 77)
                if(option < number_of_change_account_options) option++;
                else option = 0;
            else if(c1 == 75)
                if(option > 0) option--;
                else option = number_of_change_account_options;
        }
    }
}
void main_menu(){
    int option = 0;
    bool ok = true;
    while(ok){
        cls();
        show_main_menu(option);
        int c = getch();
        if(dez_menu(hidden_message, c)) show_dez_menu();
        if(c == 27){
            exit_program();
            break;
        }
        if(c == 13){
            switch(option){
            case 0:
                transactions_menu();
                break;
            case 1:
                generate_report();
                break;
            case 2:
                help_menu();
                break;
            case 3:
                change_account();
                break;
            case 4:
                exit_program();
                ok = false;
            }
        }
        if(c == 'h' || c == 'H') help_menu();
        if(c == 224){
            int c1 = getch();
            if(c1 == 79) force_stop();
            else if(c1 == 77)
                if(option < number_of_options) option++;
                else option = 0;
            else if(c1 == 75)
                if(option > 0) option--;
                else option = number_of_options;
        }
    }
}
void get_login_info(){
    char tmp = '0';
    show_console_cursor(true);

    text_color(normal_color_code);
    printf("\n\n        ");
    text_color(15);
    printf("Username:");
    text_color(normal_color_code);
    printf(" ");
    text_color(typing_color);
    scanf("%s%c", username, &tmp);
    text_color(normal_color_code);
    printf("        ");
    text_color(15);
    printf("Password:");
    text_color(normal_color_code);
    printf(" ");
    text_color(typing_color);
    scanf("%s%c", password, &tmp);
    text_color(normal_color_code);

    show_console_cursor(false);
}
bool validation_of_login_info(){
    get_login_info();
    int number_of_users;
    char tmp = '0';
    char user[101], pass[101];
    bool ok = false;
    FILE* file = fopen(Users, "r");
    fscanf(file, "%d%c", &number_of_users, &tmp);
    for(int i = 0; i < number_of_users; ++i){
        fscanf(file, "%s %s%c", user, pass, &tmp);
        if(strcmp(username, user) == 0)
            if(strcmp(password, pass) == 0){
                ok = true;
                break;
            }
    }
    fclose(file);
    return ok;
}
void text_color_checker(){
    for(int i=0; i<256; i++){
        text_color(i);
        printf("%d",i);
        text_color(7);
        printf("%c", ' ');
        if(i%15 == 0) printf("%c", '\n');
    }
}
void key_tester(){
    printf("\n");
    int c = getch();
    while(c!=27){
        c = getch();
        printf("%d", c);
        printf("\n");
    }
}
bool start_with_login(){
    text_color(normal_color_code);
    if(validation_of_login_info() == false){
        printf("\n          ");
        text_color(7);
        printf("Access denied.");
        text_color(normal_color_code);

        char* time = get_time();
        add_to_log("[");
        add_to_log(time);
        add_to_log("]   ");
        add_to_log(username);
        add_to_log(" tried to login.\n");
        int c = getch();
        return false;
    }
    else{
        char* time = get_time();
        add_to_log("[");
        add_to_log(time);
        add_to_log("]   ");
        add_to_log(username);
        add_to_log(" logged in.\n");
        return true;
    }
}
int main(){
    show_console_cursor(false);

    initialisation();

    if(start_with_login() == true)
        main_menu();

    //text_color_checker();
    //key_tester();

    return 0;
}
