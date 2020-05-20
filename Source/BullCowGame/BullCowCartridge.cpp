// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The Hidden Word is: %s"), *HiddenWord); //Debug Line

    //Welcome Message
    PrintLine(TEXT("Hi, Welcome to Bulls & Cows!"));;
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());

    //Ask player to guess
    PrintLine(TEXT("Please provide us with your guess and press enter to continue..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    HiddenWord.Len();

    // Check if word is isogram

    //while the input isn't the hidden word
    while(Input != HiddenWord){
        if(Input.Len() != HiddenWord.Len()){
            PrintLine(FString::Printf(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len()));
            //Provide user with input
            break;
        
        }
        else{
            --Lives;

            //Check if lives is 0
            if(Lives > 0)
            {
                break;
            }
            PrintLine(TEXT("Sorry! That is incorrect. Please try again"));
            
            //Show player the number of lives
            //Ask player to guess again

        }
    }

    //Player receives winning message
    if (Input == HiddenWord){
       PrintLine(TEXT("Congratulations! You have guessed the word correctly.")); 
    }

    //Player receives game over message
    else{
        PrintLine(TEXT("Game Over! The Hidden Word is "+ HiddenWord));
    }

    //Ask player if they want to play again
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("abouts");
    Lives = HiddenWord.Len(); // number of lives is dependent on the length of word
}