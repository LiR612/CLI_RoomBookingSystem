#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void loginMenu(char* email);
void mainMenu(char* email);
void viewSlot(char* email);
void bookSlot(char* email);
void editSlot(char* email);
void roomLocation(char* email);
void slotTiming(char* email);
void dateFileRetrieve(struct tm* tm,char* filenameDate1, char* filenameDate2, char* filenameDate3);
void remove_substring(char *str, char *rem);
void delPastBooking();
bool is_duplicate(char *str);
bool checkCredentials(const char* email, const char* password);

struct loginStore {
   	char email[40];
   	char password[20];
 };

void main(){
    char* email;
    delPastBooking();
    loginMenu(email);
}


void loginMenu(char* email){
    int loginOption;
    char password[20];
    do{
        for(int i=0; i<29; i++){
            printf("+");
        }
        printf("\n+");
        for(int i=0; i<8; i++){
            printf(" ");
        }
        printf("LOGIN MENU");
        for(int i=0; i<9; i++){
            printf(" ");
        }
        printf("+\n");
        for(int i=0; i<29; i++){
            printf("+");
        }
        printf("\n");
        printf("+ 1) Login                  +\n");
        printf("+ 2) Sign up                +\n");
        printf("+ 3) Exit Program           +\n");
        printf("+                           +\n");
        for(int i=0; i<29; i++){
            printf("+");
        }
        printf("\n      ");
        printf("Enter option : ");
        int result = scanf("%d", &loginOption); 
        while (result != 1) { 
            printf("Invalid Input! Enter a number.\n      Enter option : "); 
            while (getchar() != '\n'); // clear the input buffer
            result = scanf("%d", &loginOption);
        }
    }while(loginOption != 1 && loginOption != 2 && loginOption != 3);
    if(loginOption!=3){
        if (loginOption == 1){
            printf("\nLOGIN DETAILS:\n\n1) Student Email : ");
            scanf("%s", email); //Input code for email 40 and password > 20
            printf("\n2) Password : ");
            scanf("%s", password);
            if (checkCredentials(email, password)) {
                printf("\n\nLogin Successful\n\n");
                mainMenu(email);
            } else {
                printf("Invalid email or password. Sign up or try again!\n");
                loginMenu(email);
            }
        }
        else if (loginOption == 2){
            bool valid = false;
            struct loginStore student;
            FILE *f = fopen("LoginData.txt", "a");
            if (f == NULL) {
                printf("Error: Cannot open the file.\n");
            }
            printf("\n\nINPUT NEW STUDENT DETAILS:\n\n1) Student Email : ");
            while (!valid) {
                scanf("%s",student.email);
                if (strlen(student.email) > 39) {
                    printf("Email cannot be more than 39 characters. Try again.\n1) Student Email : ");
                }
                else if (is_duplicate(student.email)) {
                    printf("An account with that email already exists. Try again.\n1) Student Email : ");
                }
                else {
                    valid = true;
                }
            }
            valid = false;
            while (!valid) {
                printf("\n2) Password : ");
                scanf("%s", student.password);
                if (strlen(student.password) > 19) {
                    printf("Password cannot be more than 19 characters. Please try again\n2) Password : ");
                }
                // If both checks pass, set valid to true and exit the loop
                else {
                    valid = true;
                }
            }  
            valid = false;
            fprintf(f,"%s ; %s\n", student.email, student.password); // To write info into the .txt file
            fclose(f);
            printf("\nNew Account Registered\n\n");
            loginMenu(email);
        }
    } else {
        exit(0);
    }
}

void mainMenu(char* email){
    int menuOption;
    printf("\n");
    for(int i=0; i<29; i++){
        printf("+");
    }
    printf("\n+");
    for(int i=0; i<8; i++){
        printf(" ");
    }
    printf("MAIN MENU");
    for(int i=0; i<10; i++){
        printf(" ");
    }
    printf("+\n");
    for(int i=0; i<29; i++){
        printf("+");
    }
    printf("\n");
    printf("+ 1) View Available Slots   +\n");
    printf("+ 2) Book New Slot          +\n");
    printf("+ 3) View / Edit / Cancel   +\n+    Existing Slot          +\n");
    printf("+ 4) View Room Locations    +\n");
    printf("+ 5) View Slot Times        +\n");
    printf("+ 6) Exit / Logout          +\n");
    for(int i=0; i<29; i++){
        printf("+");
    }
    printf("\n      ");
    printf("Enter option : ");
    int result = scanf("%d", &menuOption); 
    while (result != 1) { 
        printf("Invalid Input! Enter a number.\n      Enter option : "); 
        while (getchar() != '\n'); // clear the input buffer
        result = scanf("%d", &menuOption);
    }
    switch(menuOption){
        case 1:
            viewSlot(email);
            break;
        case 2:
            bookSlot(email);
            break;
        case 3:
            editSlot(email);
            break;
        case 4:
            roomLocation(email);
            break;
        case 5:
            slotTiming(email);
            break;
        case 6:
            printf("Thank you for using the system. Logging Out...\n");
            loginMenu(email);
            break;
        default:
            printf("Invalid option. Please try again.\n");
            mainMenu(email); // call mainMenu function again
            break;
    }
}

void viewSlot(char* email){
    struct tm tm;
    char filenameDate1[20];
    char filenameDate2[20];
    char filenameDate3[20];
    int viewChoice;
    int arr[16][11];
    dateFileRetrieve(&tm, filenameDate1, filenameDate2, filenameDate3); // Pass the parameters here
    printf("Rooms are available for today, tomorrow, or the day after. You can view those room's availabilities\n\n");
    while (viewChoice!=1 && viewChoice!=2 && viewChoice!=3 && viewChoice!=4){
        char Date1[20], Date2[20], Date3[20];
        char rem[100] = "_Booking.txt";
        strcpy(Date1, filenameDate1);
        strcpy(Date2, filenameDate2);
        strcpy(Date3, filenameDate3);
        remove_substring(Date1, rem);
        remove_substring(Date2, rem);
        remove_substring(Date3, rem);
        printf("Which date would you like to view availability? (Pick 1,2 or 3)\n");
        printf("1) %s\n2) %s\n3) %s\n4) Return to Menu\nChoice: ", Date1, Date2, Date3);
        int result = scanf("%d", &viewChoice);
        while (result != 1) { 
            printf("Invalid Input! Enter a number.\nEnter choice : "); 
            while (getchar() != '\n'); // clear the input buffer
            result = scanf("%d", &viewChoice);
        }
    }

    FILE* f;
    if (viewChoice == 1) {
        f = fopen(filenameDate1, "r");
        if (f == NULL) {
            printf("Error: Cannot open the file.\n");
        }
    }else if (viewChoice == 2){
        f = fopen(filenameDate2, "r");
        if (f == NULL) {
            printf("Error: Cannot open the file.\n");
        }
    }
    else if (viewChoice == 3){
        f = fopen(filenameDate3, "r");
        if (f == NULL) {
            printf("Error: Cannot open the file.\n");
        }
    }
    else if (viewChoice == 4){
        mainMenu(email);
    }
    if (f == NULL) {
        printf("Error: could not open file\n");
    }
    // Read the data from the text file into the array
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 11; j++) {
            fscanf(f, "%d", &arr[i][j]);
        }
    }
    fclose(f);
    printf("\n");// Printing spaces for alignment
    printf("\t _______________________________________________________________________________________ \n");
    printf("\t|08-09am|09-10am|10-11am|11-12pm|12-01pm|01-02pm|02-03pm|03-04pm|04-05pm|05-06pm|06-07pm|\n");
    printf("\t|"); // Print some spaces for alignment
    for (int j = 0; j < 11; j++) {
        if(j<9){
            printf("Slot 0%d|", j + 1); // Print the column names with spaces
        }
        else{
            printf("Slot %d|", j + 1); // Print the column names with spaces
        }
    }
    printf("\n");
    printf("\t=========================================================================================\n");
    for (int i = 0; i < 16; i++) {
        if(i<9){
            printf("Room 0%d| ", i + 1);
        }
        else{
            printf("Room %d| ", i + 1); 
        }
        for (int j = 0; j < 11; j++) {
            if(arr[i][j]==1){
                printf("X\t|");
            }
            else{
                printf("%d\t|", arr[i][j]);
            } 
        }
        printf("\n");
    }
    printf("\t=========================================================================================\n");
    printf("\n");
    mainMenu(email);
}

void bookSlot(char* email){
    int bookChoice, roomNo, slotAmount=0, slotNo;
    int slots[16][11] = {{0}};
    struct tm tm;
    char filenameDate1[20];
    char filenameDate2[20];
    char filenameDate3[20];
    dateFileRetrieve(&tm, filenameDate1, filenameDate2, filenameDate3); // Pass the parameters here
    char Date1[20], Date2[20], Date3[20];
    char rem[100] = "_Booking.txt";
    strcpy(Date1, filenameDate1);
    strcpy(Date2, filenameDate2);
    strcpy(Date3, filenameDate3);
    remove_substring(Date1, rem);
    remove_substring(Date2, rem);
    remove_substring(Date3, rem);
    while (bookChoice!=1 && bookChoice!=2 && bookChoice!=3 && bookChoice!=4){
        printf("You may book a room for today, tomorrow, or the day after.\n\n");
        printf("When would you like to book a room? (Pick 1,2 or 3)\n");
        printf("1) %s\n2) %s\n3) %s\n4) Return to Menu\nChoice: ", Date1, Date2, Date3);
        int result = scanf("%d", &bookChoice);
        while (result != 1) { 
            printf("Invalid Input! Enter a number.\nEnter choice : "); 
            while (getchar() != '\n'); // clear the input buffer
            result = scanf("%d", &bookChoice);
        }
    }
    char dateSelected[40];
    if(bookChoice==1){
        strcpy(dateSelected, Date1);
    }
    else if(bookChoice==2){
        strcpy(dateSelected, Date2);
    }
    else if(bookChoice==3){
        strcpy(dateSelected, Date3);
    }
    else if(bookChoice==4){
        mainMenu(email);
    }
    // check email and booking date relationship
    FILE* fp = fopen("BookingData.txt", "r");
    char line[100];
    int numSameDayBooking = 0, slotNoRestrict;
    char readValues[4][40];
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%39s ; %s ; %s ; %s ", readValues[0], readValues[1], readValues[2], readValues[3]);
        char bookingDate[20];
        char rem[100] = "_Booking.txt";
        remove_substring(readValues[3], rem);
        strcpy(bookingDate, readValues[3]);
        //bookingDate is DD-MM-YYYY
        if (strcmp(readValues[0], email) == 0 && strcmp(bookingDate, dateSelected) == 0) { 
            numSameDayBooking++;          
        }
    }
    if(numSameDayBooking>=3){
        printf("\nYou already have 3 slots for that date.\nYou are not allowed to book more slots on %s\n", dateSelected);
        printf("Try Another Date\n");
        bookSlot(email);
    }
    else if(numSameDayBooking==2 || numSameDayBooking==1){
        printf("You already have %d slot(s) for that date.\nYou can only book %d more slot for %s\n", numSameDayBooking, 3-numSameDayBooking, dateSelected);
        slotNoRestrict = 3-numSameDayBooking;
    }
    else{
        printf("\nYou have no slots booked for that date.\nYou can book 3 slots for %s\n", dateSelected);
        slotNoRestrict = 3-numSameDayBooking;
    }
    FILE* f;
    if (bookChoice == 1) {
        f = fopen(filenameDate1, "r+");
        if (f == NULL) {
            printf("Error: Cannot open the file.\n");
        }
    }else if (bookChoice == 2){
        f = fopen(filenameDate2, "r+");
        if (f == NULL) {
            printf("Error: Cannot open the file.\n");
        }
    }
    else{
        f = fopen(filenameDate3, "r+");
        if (f == NULL) {
            printf("Error: Cannot open the file.\n");
        }
    }
    // Read the existing data from the file into the ARRAY
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 11; j++) {
            fscanf(f, "%d", &slots[i][j]);
        }
    }
    fclose(f);
    // Prompt the user for the room number and check its validity
    printf("\nWhat room do you want to book?(Pick 1 to 16)\nRoom : ");
    int result = scanf("%d", &roomNo);
    while (result != 1) { 
        printf("Invalid Input! Enter a number.\nEnter choice : "); 
        while (getchar() != '\n'); // clear the input buffer
        result = scanf("%d", &roomNo);
    }
    while(roomNo < 1 || roomNo > 16){
        printf("\nInvalid room number.\n");
        printf("What room do you want to book?(Pick 1 to 16)\nRoom : ");
        int result = scanf("%d", &roomNo);
        while (result != 1) { 
            printf("Invalid Input! Enter a number.\nEnter Room : "); 
            while (getchar() != '\n'); // clear the input buffer
            result = scanf("%d", &roomNo);
        }
    };

    // Ask the user for the number of slots and check its validity
    printf("\nHow many slots(hours) do you want to book?(Max = %d)\nAmount of Slots : ", slotNoRestrict);
    result = scanf("%d", &slotAmount);
    while (result != 1) { 
        printf("Invalid Input! Enter a number.\nEnter Slot Amount : "); 
        while (getchar() != '\n'); // clear the input buffer
        result = scanf("%d", &slotAmount);
    }
    while(slotAmount<1 || slotAmount>slotNoRestrict){
        printf("\nInvalid slot amount. You can only book a maximum of THREE slots for a day.\n");
        printf("You already have %d slots booked for %s\n", numSameDayBooking, dateSelected);
        printf("\nHow many slots(hours) do you want to book?(Max = %d)\nAmount of Slots : ", slotNoRestrict);
        int result = scanf("%d", &slotAmount);
        while (result != 1) { 
            printf("Invalid Input! Enter a number.\nEnter Slot Amount : "); 
            while (getchar() != '\n'); // clear the input buffer
            result = scanf("%d", &slotAmount);
        }
    };
    int booked = 0; // A variable to keep track of how many slots are booked
    while (booked < slotAmount) {
        // Ask the user for the slot number and check its validity
        printf("\nWhat slot do you want to book(Pick 1 to 11)\n(Input 0 to return to menu)\nSlot %d: ", booked+1);   
        int result = scanf("%d", &slotNo);
        while (result != 1) { 
            printf("Invalid Input! Enter a number.\nEnter Slots : "); 
            while (getchar() != '\n'); // clear the input buffer
            result = scanf("%d", &slotNo);
        }
        if(slotNo==0){
            mainMenu(email);
        }
        int timeRestrict = 0, slotHour;
        if(bookChoice == 1){
            slotHour = slotNo + 7;
            if(slotHour<=tm.tm_hour){
                timeRestrict = 1;
            }
        }
        while (slotNo < 0 || slotNo > 11 || timeRestrict == 1){
            printf("\nInvalid slot number.\n");
            if(timeRestrict == 1){
                printf("You cannot book a slot for time that has already passed.\n\n");
            }
            timeRestrict = 0;
            printf("What slot do you want to book(Pick 1 to 11)\nSlot %d: ", booked+1);
            int result = scanf("%d", &slotNo);
            slotHour = slotNo + 7;
            if(slotHour<=tm.tm_hour){
                timeRestrict = 1;
            }
            while (result != 1) { 
                printf("Invalid Input! Enter a number.\nEnter Slot %d: ", booked+1); 
                while (getchar() != '\n'); // clear the input buffer
                result = scanf("%d", &slotNo);
            }
        }
            
        // Check if the slot is available and update the array accordingly
        if (slots[roomNo-1][slotNo-1] == 0) {
            slots[roomNo-1][slotNo-1] = 1;
            printf("You have booked Slot %d in Room %d.\n", slotNo, roomNo);
            booked++;
            if (bookChoice == 1) {
                FILE *f = fopen("BookingData.txt", "a");
                if (f == NULL) {
                    printf("Error opening file\n");
                }
                fprintf(f, "%s ; %d ; %d ; %s\n", email, roomNo, slotNo, filenameDate1 );
                fclose(f); 
            }else if (bookChoice == 2){
                FILE *f = fopen("BookingData.txt", "a");
                if (f == NULL) {
                    printf("Error opening file\n");
                }
                fprintf(f, "%s ; %d ; %d ; %s\n", email, roomNo, slotNo, filenameDate2 );
                fclose(f); 
            }
            else{
                FILE *fp = fopen("BookingData.txt", "a");
                if (fp == NULL) {
                    printf("Error opening file\n");
                }
                fprintf(fp, "%s ; %d ; %d ; %s\n", email, roomNo, slotNo, filenameDate3 );
                fclose(fp); 
            }
        }
        else {
            printf("Slot %d in room %d is already booked.\n", slotNo, roomNo);
        }
    }
    // Open the text file in write mode and write the updated array to it
    if (bookChoice == 1) {
        f = fopen(filenameDate1, "w");
        if (f == NULL) {
            printf("Error: Cannot open the file.\n");
        }
    }else if (bookChoice == 2){
        f = fopen(filenameDate2, "w");
        if (f == NULL) {
            printf("Error: Cannot open the file.\n");
        }
    }
    else{
        f = fopen(filenameDate3, "w");
        if (f == NULL) {
            printf("Error: Cannot open the file.\n");
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 11; j++) {
            fprintf(f, "%d\t", slots[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f); 
    printf("You have booked %d slots in total. Returning to Main Menu...\n",slotAmount);
    mainMenu(email);
}

void editSlot(char* email) {
    FILE* fp;
    fp = fopen("BookingData.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open the file.\n");
        // Return early to avoid further processing if file opening fails
    }
    char line[100];
    int count = 0, editCancelChoice;
    char editCancelDate[20], editCancelRoom[10], editCancelSlot[10];
    char values[4][40];
    char rem[100] = "_Booking.txt";
    printf("\nBelow are all your bookings:\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%39s ; %s ; %s ; %s ", values[0], values[1], values[2], values[3]);
        if (strcmp(values[0], email) == 0) {
            printf("\n++++++++++++++++++++++++++++++++++++++");
            printf("\n  BOOKING DATA %d:\n", count + 1);
            printf("  Email : %s\n", values[0]);
            printf("  Room No : %s\n", values[1]);
            printf("  Slot No : %s\n", values[2]);
            remove_substring(values[3], rem);
            printf("  Booked Date : %s\n", values[3]);
            printf("++++++++++++++++++++++++++++++++++++++\n");
            count++;
        }
    }
    fclose(fp);
    if (count == 0) {
        printf("You don't have any booking made with this email: %s\n", email);
        mainMenu(email);
    }

    do {
        printf("\nWhat would you like to do?\n1) Edit a Slot\n2) Cancel a Slot\n3) Return to Menu\nChoice : ");
        int result = scanf("%d", &editCancelChoice);
        while (result != 1) { 
            printf("Invalid Input! Enter a number.\nEnter choice : "); 
            while (getchar() != '\n'); // clear the input buffer
            result = scanf("%d", &editCancelChoice);
        }
    } while (editCancelChoice != 1 && editCancelChoice != 2 && editCancelChoice != 3);

    if (editCancelChoice == 1) {
        printf("\nWhich date's booking do you want to edit? (INPUT DD-MM-YYYY)\nCancel Date: ");
        scanf("%s", editCancelDate);
        printf("\nInput room number you want to edit from specified date\nCancel Room: ");
        scanf("%s", editCancelRoom);
        printf("\nInput the slot you want to edit from specified date and room\nCancel Slot: ");
        scanf("%s", editCancelSlot);

        FILE* fp = fopen("BookingData.txt", "r");
        FILE* tempFile = fopen("temp.txt", "w");
        if (fp == NULL || tempFile == NULL) {
            printf("Error: Cannot open the file.\n");
            mainMenu(email);
        }
        char line[100];
        int removefromArray = 0, matchNotFound = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            sscanf(line, "%39s ; %s ; %s ; %s ", values[0], values[1], values[2], values[3]);
            char bookingDate[20];
            remove_substring(values[3], rem);
            strcpy(bookingDate, values[3]);

            // Check if the line matches the criteria for cancellation
            if (strcmp(values[0], email) == 0 && strcmp(bookingDate, editCancelDate) == 0 && strcmp(values[1], editCancelRoom) == 0 && strcmp(values[2], editCancelSlot) == 0) { 
                printf("Match found. Implementing your cancellation.\n");
                removefromArray = 1;
                matchNotFound = 0;
                if(removefromArray == 1){
                    int slots[16][11];
                    struct tm tm;
                    char filenameDate1[20];
                    char filenameDate2[20];
                    char filenameDate3[20];
                    FILE* f; 
                    dateFileRetrieve(&tm, filenameDate1, filenameDate2, filenameDate3);
                    strcat(editCancelDate, "_Booking.txt");        
                    if (strcmp(editCancelDate, filenameDate1) == 0) {
                        f = fopen(filenameDate1, "r+");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    else if (strcmp(editCancelDate, filenameDate2) == 0){
                        f = fopen(filenameDate2, "r+");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    else if (strcmp(editCancelDate, filenameDate3)==0){
                        f =  fopen(filenameDate3, "r+");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    // Read the existing data from the file into the ARRAY
                    for (int i = 0; i < 16; i++) {
                        for (int j = 0; j < 11; j++) {
                            fscanf(f, "%d", &slots[i][j]);
                        }
                    }
                    fclose(f);
                    int cancelRoomVal = atoi(editCancelRoom);
                    int cancelSlotVal = atoi(editCancelSlot);
                    if (slots[cancelRoomVal-1][cancelSlotVal-1] == 1) {
                        slots[cancelRoomVal-1][cancelSlotVal-1] = 0;
                        printf("You have removed Slot %d in Room %d on %s\n", cancelSlotVal, cancelRoomVal, bookingDate);
                    }
                    else{
                        printf("You didnt book that room with your email\n");
                    }
                    if (strcmp(editCancelDate, filenameDate1) == 0) {
                        f = fopen(filenameDate1, "w");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    else if (strcmp(editCancelDate, filenameDate2) == 0){
                        f = fopen(filenameDate2, "w");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    else if (strcmp(editCancelDate, filenameDate3)==0){
                        f =  fopen(filenameDate3, "w");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    for (int i = 0; i < 16; i++) {
                        for (int j = 0; j < 11; j++) {
                            fprintf(f, "%d\t", slots[i][j]);
                        }
                    fprintf(f, "\n");
                    } 
                    fclose(f);
                }
                continue; 
            }
            else{
                matchNotFound = 1;
            }
            fputs(line, tempFile); // Write the line to the temporary file
        }
        if(matchNotFound==1){
            printf("\n\e[1mYour input does not match any of your bookings!\e[m\n");
            fclose(fp);
            fclose(tempFile);
            editSlot(email);
        }
        fclose(fp);
        fclose(tempFile);
        remove("BookingData.txt");
        rename("temp.txt", "BookingData.txt");
        bookSlot(email);
    } else if (editCancelChoice == 2)  {
        printf("\nWhich date's booking do you want to cancel? (INPUT DD-MM-YYYY)\nCancel Date: ");
        scanf("%s", editCancelDate);
        printf("\nInput room number you want to cancel from specified date\nCancel Room: ");
        scanf("%s", editCancelRoom);
        printf("\nInput the slot you want to cancel from specified date and room\nCancel Slot: ");
        scanf("%s", editCancelSlot);

        FILE* fp = fopen("BookingData.txt", "r");
        FILE* tempFile = fopen("temp.txt", "w");
        if (fp == NULL || tempFile == NULL) {
            printf("Error: Cannot open the file.\n");
            mainMenu(email);
        }
        char line[100];
        int removefromArray = 0, matchNotFound = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            sscanf(line, "%39s ; %s ; %s ; %s ", values[0], values[1], values[2], values[3]);
            char bookingDate[20];
            remove_substring(values[3], rem);
            strcpy(bookingDate, values[3]);

            // Check if the line matches the criteria for cancellation
            if (strcmp(values[0], email) == 0 && strcmp(bookingDate, editCancelDate) == 0 && strcmp(values[1], editCancelRoom) == 0 && strcmp(values[2], editCancelSlot) == 0) { 
                printf("Match found. Implementing your cancellation.\n");
                removefromArray = 1;
                matchNotFound = 0;
                if(removefromArray == 1){
                    int slots[16][11];
                    struct tm tm;
                    char filenameDate1[20];
                    char filenameDate2[20];
                    char filenameDate3[20];
                    FILE* f; 
                    dateFileRetrieve(&tm, filenameDate1, filenameDate2, filenameDate3);
                    strcat(editCancelDate, "_Booking.txt");        
                    if (strcmp(editCancelDate, filenameDate1) == 0) {
                        f = fopen(filenameDate1, "r+");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    else if (strcmp(editCancelDate, filenameDate2) == 0){
                        f = fopen(filenameDate2, "r+");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    else if (strcmp(editCancelDate, filenameDate3)==0){
                        f =  fopen(filenameDate3, "r+");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    // Read the existing data from the file into the ARRAY
                    for (int i = 0; i < 16; i++) {
                        for (int j = 0; j < 11; j++) {
                            fscanf(f, "%d", &slots[i][j]);
                        }
                    }
                    fclose(f);
                    int cancelRoomVal = atoi(editCancelRoom);
                    int cancelSlotVal = atoi(editCancelSlot);
                    if (slots[cancelRoomVal-1][cancelSlotVal-1] == 1) {
                        slots[cancelRoomVal-1][cancelSlotVal-1] = 0;
                        printf("You have cancelled Slot %d in Room %d on %s\n", cancelSlotVal, cancelRoomVal, bookingDate);
                    }
                    else if (slots[cancelRoomVal-1][cancelSlotVal-1] == 0) {
                        printf("You didnt book that room with your email\n");
                    }
                    if (strcmp(editCancelDate, filenameDate1) == 0) {
                        f = fopen(filenameDate1, "w");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    else if (strcmp(editCancelDate, filenameDate2) == 0){
                        f = fopen(filenameDate2, "w");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    else if (strcmp(editCancelDate, filenameDate3)==0){
                        f =  fopen(filenameDate3, "w");
                        if (f == NULL) {
                            printf("Error: Cannot open the file.\n");
                        }
                    }
                    for (int i = 0; i < 16; i++) {
                        for (int j = 0; j < 11; j++) {
                            fprintf(f, "%d\t", slots[i][j]);
                        }
                    fprintf(f, "\n");
                    } 
                    fclose(f);
                }
                continue; 
            }
            else{
                matchNotFound = 1;
            }
            fputs(line, tempFile); // Write the line to the temporary file
        }
        if(matchNotFound==1){
            printf("\n\e[1mYour input does not match any of your bookings!\e[m\n");
            fclose(fp);
            fclose(tempFile);
            editSlot(email);
        }
        fclose(fp);
        fclose(tempFile);
        remove("BookingData.txt");
        rename("temp.txt", "BookingData.txt");
    }
    else if (editCancelChoice == 3)  {
        mainMenu(email);
    }
    mainMenu(email);
}

void roomLocation(char* email){
    //print all room locations
    printf("\n+++++++++++++++++++++++++++++++++++++++");
    printf("\n           ROOM LOCATIONS");
    printf("\n+++++++++++++++++++++++++++++++++++++++\n");
    printf("Room 1 - Room 8  : APU Library, Level 4\n");
    printf("Room 9           : B-05-01\n");
    printf("Room 10          : B-05-02\n");
    printf("Room 11          : C-04-01\n");
    printf("Room 12          : C-04-02\n");
    printf("Room 13          : D-05-01\n");
    printf("Room 14          : D-05-02\n");
    printf("Room 15          : E-04-01\n");
    printf("Room 16          : E-04-02\n\n");
    mainMenu(email);
}

void slotTiming(char* email){
    printf("\n+++++++++++++++++++++++++++\n");
    printf("\n       Slot Timings");
    printf("\n+++++++++++++++++++++++++++\n");
    printf("Slot 01 : 08:00am - 09:00am\n");
    printf("Slot 02 : 09:00am - 10:00am\n");
    printf("Slot 03 : 10:00am - 11:00am\n");
    printf("Slot 04 : 11:00am - 12:00pm\n");
    printf("Slot 05 : 12:00pm - 01:00pm\n");
    printf("Slot 06 : 01:00pm - 02:00pm\n");
    printf("Slot 07 : 02:00pm - 03:00pm\n");
    printf("Slot 08 : 03:00pm - 04:00pm\n");
    printf("Slot 09 : 04:00pm - 05:00pm\n");
    printf("Slot 10 : 05:00pm - 06:00pm\n");
    printf("Slot 11 : 06:00pm - 07:00pm\n\n");
    mainMenu(email);
}

void dateFileRetrieve(struct tm* tm,char* filenameDate1, char* filenameDate2, char* filenameDate3) {
    time_t t = time(NULL);
    *tm = *localtime(&t);
    long fileSize;
    printf("\nToday's Date is: %02d-%02d-%d\n", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    // Create filenames for the next three days
    sprintf(filenameDate1, "%02d-%02d-%04d_Booking.txt", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    tm->tm_mday++;
    t = mktime(tm);
    *tm = *localtime(&t);
    sprintf(filenameDate2, "%02d-%02d-%04d_Booking.txt", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    tm->tm_mday++;
    t = mktime(tm);
    *tm = *localtime(&t);
    sprintf(filenameDate3, "%02d-%02d-%04d_Booking.txt", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    // Open and close files to create them if they don't exist
    FILE* f1 = fopen(filenameDate1, "a");
    if (f1 == NULL) {
        printf("Error: could not open file %s\n", filenameDate1);
        exit(1);
    }
    fclose(f1);
    f1 = fopen(filenameDate1, "r"); // Open the file in read mode and seek to the end
    fseek(f1, 0, SEEK_END);
    fileSize = ftell(f1); // Get the current position of the file pointer, which is the file size
    fclose(f1);
    if (fileSize == 0) {
        printf("The file is empty.\n");
        // Open the file in write mode and write the array to it
        f1 = fopen(filenameDate1, "w");
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 11; j++) {
                fprintf(f1, "0\t");
            }
            fprintf(f1, "\n");
        }
        fclose(f1);
    }

    FILE* f2 = fopen(filenameDate2, "a");
    if (f2 == NULL) {
        printf("Error: could not open file %s\n", filenameDate2);
        exit(1);
    }
    fclose(f2);
    f2 = fopen(filenameDate2, "r"); // Open the file in read mode and seek to the end
    fseek(f2, 0, SEEK_END);
    fileSize = ftell(f2); // Get the current position of the file pointer, which is the file size
    fclose(f2);
    if (fileSize == 0) {
        printf("The file is empty.\n");
        // Open the file in write mode and write the array to it
        f2 = fopen(filenameDate2, "w");
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 11; j++) {
                fprintf(f2, "0\t");
            }
            fprintf(f2, "\n");
        }
        fclose(f2);
    }

    FILE* f3 = fopen(filenameDate3, "a");
    if (f3 == NULL) {
        printf("Error: could not open file %s\n", filenameDate3);
        exit(1);
    }
    fclose(f3);
    f3 = fopen(filenameDate3, "r"); // Open the file in read mode and seek to the end
    fseek(f3, 0, SEEK_END);
    fileSize = ftell(f3); // Get the current position of the file pointer, which is the file size
    fclose(f3);
    if (fileSize == 0) {
        printf("The file is empty.\n");
        // Open the file in write mode and write the array to it
        f3 = fopen(filenameDate3, "w");
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 11; j++) {
                fprintf(f3, "0\t");
            }
            fprintf(f3, "\n");
        }
        fclose(f3);
    }
}

void remove_substring(char *str, char *rem) {
    char *pos = strstr(str, rem);
    if (pos != NULL) {
        int len = strlen(rem);
        memmove(pos, pos + len, strlen(pos + len) + 1);
    }
}

void delPastBooking(){
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    int today_day = tm->tm_mday;
    int today_month = tm->tm_mon + 1;
    int today_year = tm->tm_year + 1900;
    FILE* fp = fopen("BookingData.txt", "r"); 
    if (fp == NULL) {
        printf("Error: could not open file BookingData.txt\n");
    }
    FILE* temp = fopen("Temp.txt", "w");
    if (temp == NULL) {
        printf("Error: could not open file Temp.txt\n");
    }
    char line[100];
    while (fgets(line, 100, fp) != NULL){
        char email[50];
        int row, col;
        int day, month, year;
        sscanf(line, "%s ; %d ; %d ; %d-%d-%d_Booking.txt", email, &row, &col, &day, &month, &year);
        if (tm->tm_year + 1900 < year) // if the current year is less than the input year
        {
            fprintf(temp, "%s", line); // write the line to the temporary file
        }
        else if (tm->tm_year + 1900 == year) // if the current year is equal to the input year
        {
            if (tm->tm_mon + 1 < month) // if the current month is less than the input month
            {
                fprintf(temp, "%s", line); // write the line to the temporary file
            }
            else if (today_month == month) // if the current month is equal to the input month
            {
                if (tm->tm_mday <= day) // if the current day is less than or equal to the input day
                {
                    fprintf(temp, "%s", line); // write the line to the temporary file
                }
            }
        }
    }
    fclose(fp); // close the BookingData.txt file
    fclose(temp); // close the temporary file
    remove("BookingData.txt"); // delete the BookingData.txt file
    rename("Temp.txt", "BookingData.txt"); // rename the temporary file as BookingData.txt
}


bool is_duplicate(char *str) {
  FILE *file = fopen("LoginData.txt", "r");
  char existingEmail[40];
  char existingPassword[20];
  if (file == NULL) {
    printf("Error opening file\n");
    return false;
  }
  while(fscanf(file, "%39s ; %19s\n", existingEmail, existingPassword)==2){
    if (strcmp(str, existingEmail) == 0) {
    fclose(file);
    return true;
    }
  }
  fclose(file);
  return false;
}

bool checkCredentials(const char* email, const char* password) {
    FILE *f = fopen("LoginData.txt", "r");
    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    struct loginStore login;
    while (fscanf(f, "%39s ; %19s\n", login.email, login.password) == 2) {
        if (strcmp(email, login.email) == 0 && strcmp(password, login.password) == 0) {
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}