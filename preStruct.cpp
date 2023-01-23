//
// Created by National Cyber City on 1/10/2023.
// pre 1 struct

#include "stdio.h"
#include "stdlib.h"
#define SIZE 3
struct Worker{
    int id;
    int age;
    char name[30];
    char email[50];
    char password[50];

};

struct Worker info[SIZE];

void printingAllData();
void login();
int charCounting(char toCount[50]);
void myStrCmp(char userInputChar[50]);
int gmailValidation(char userInputChar[50]);
void recordingToAFile();
void userActionSector();
void loadingAllDataFromFile();
void lobby();
void registerFun();
void passChecking(char pass[],int userIndex);
int globalIndex = 0;
int index = 0;

int eFound = -1;
int pFound = -1;
int main(){

    loadingAllDataFromFile();
    printingAllData();
    lobby();
    userActionSector();

    return 0;
}

void printingAllData(){

    for(int gcc=0; gcc < globalIndex ; gcc++ ){

        printf("id:%d name:%s - age:%d - email:%s - password:%s\n",info[gcc].id,info[gcc].name , info[gcc].age , info[gcc].email , info[gcc].password);

    }
}

void login(){
    char lEmail[50];
    char lPassword[50];
    printf("This is login form:\n");

    printf("Enter your email to login:");
    scanf(" %[^\n]",&lEmail);

    printf("Enter your password to login:");
    scanf(" %[^\n]",&lPassword);

    eFound = -1;
    myStrCmp(lEmail);

    pFound = -1;
    passChecking(lPassword,eFound);

    if(eFound != -1 && pFound == 1){
        printf("Login Success\n");
        printf("Welcome Sir: %s\n", info[eFound].name);
        userActionSector();
    } else{
        printf("Invalid email: Or Password\n");
        login();
    }

}

void myStrCmp(char userInputChar[50]){

    int sameCount=0;
    int sec = charCounting(userInputChar);
    for(int i=0; i< globalIndex ; i++){
        int first = charCounting(info[i].email);

        if( first == sec){
            for(int gcc=0; gcc<first ; gcc++){
                if( info[i].email[gcc] != userInputChar[gcc]){
                    break;
                } else{
                    sameCount++;
                }

            }

        }
        if( sec == sameCount){
            eFound = i;
            break;
        }

    }

}

int charCounting(char toCount[50]) { // toCount[50] = {'w','i','n','@'gmail.com,'\0' , '\0'}
    int charCount = 0;
    for (int gcc = 0; gcc < 50; gcc++) {
            if (toCount[gcc] == '\0') {
                break;
            } else {
                charCount++;
            }
    }
        return charCount;
    }

int gmailValidation(char toCount[50]) {

    for (int i = 0; i <50; i++) {
        if (toCount[i] == '@'){
            if (toCount[i+1] == 'g' &&
            toCount[i+2] == 'm' &&
            toCount[i+3] == 'a' &&
            toCount[i+4] == 'i' &&
            toCount[i+5] == 'l' &&
            toCount[i+6] == '.' &&
            toCount[i+7] == 'c' &&
            toCount[i+8] == 'o' &&
            toCount[i+9] == 'm' ){
                return 1;
            }
        }
    }
    return -1;


}



void recordingToAFile(){

    FILE *fptr2;
    fptr2 = fopen("recording.txt","a");

    if (fptr2 == NULL){
        printf("Error at opening recording file\n");
    }else {
        for (int i = 0; i < globalIndex; i++) {
            fprintf(fptr2, "%d %d %s %s %s\n",info[i].id, info[i].age,info[i].name,info[i].email,info[i].password);
        }
        printf("Recording to text file\n");
    }
    fclose(fptr2);
}


void lobby(){
    int lob = 0;
    printf("This is from Lobby\n");
    printf("Press 1 to register\n");
    printf("Press 2 to login\n");
    printf("Press 3 to Exit\n");
    scanf("%d",&lob);

    if (lob == 1){
        registerFun();
    }else if (lob == 2){
        login();
    }else if (lob == 3){
        recordingToAFile();
        exit(1);
    }else{
        printf("Invalid option\n");
        lobby();
    }
}

void passChecking(char pass[],int userIndex) {
    int sameCount = 0;
    int passCount = charCounting(pass);
    int infoPassCount = charCounting(info[userIndex].password);
    if (passCount == infoPassCount) {
        for (int i = 0; i < passCount; i++) {
            if (pass[i] == info[userIndex].password[i]){
                sameCount++;
            }else{
                break;
            }
        }
        if (sameCount == passCount){
            pFound = 1;
        }
    }
}
void userActionSector() {
    int userAction;
//    printf("Welcome Sir: %s\n", info[eFound].name);
    printf("Press 1 to User Action Sector\n");
    printf("Press 2 to Go Home\n");
    printf("Press 3 to Exit:\n");
    scanf("%d",&userAction);

    if (userAction == 1){
        printf("This is user action sector\n");
    }else if (userAction == 2){
        lobby();
    }else if (userAction == 3){
        recordingToAFile();
        exit(1);
    }else{
        printf("Invalid option\n");
        userActionSector();

    }
}

void registerFun() {
    int result = 0;
    int answer = 0;

    printf("Please enter your email:");
    scanf(" %[^\n]", info[globalIndex].email);
    result = gmailValidation(info[globalIndex].email);
    if (result != 1) {
        printf("Invalid Gmail\n");
    } else {
        printf("Valid Gmail\n");

        eFound = -1;
        myStrCmp(info[globalIndex].email);
        if (eFound == -1) {

            printf("Enter age:");
            scanf("%d", &info[globalIndex].age);

            printf("Enter name:");
            scanf(" %[^\n]", &info[globalIndex].name);

            printf("Enter password:");
            scanf(" %[^\n]", &info[globalIndex].password);
            globalIndex++;
            printf("Registration Success\n");
            lobby();


        } else {

            printf("Email already exist\n");
            registerFun();
        }

    }
}

void loadingAllDataFromFile(){

    FILE *fptr2;
    fptr2 = fopen("recording.txt","a");
    fclose(fptr2);
    FILE *fptr;
    fptr = fopen("recording.txt","r");

    if (fptr == NULL){
        printf("Error at opening file\n");
    }else {
        for (int i = 0; i < SIZE; i++) {

            fscanf(fptr, "%d%d%s%s%s", &info[i].id,&info[i].age,&info[i].name,&info[i].email,&info[i].password);

            if (info[i].name[0] == '\0'){
                break;
            }
            globalIndex++;
        }
    }
    fclose(fptr);
}

// gmail validation
// winhtut@gmail.com
// winhtut@gmil.com
