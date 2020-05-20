// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The Hidden Word is: %s"), *HiddenWord); //Debug Line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver) 
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking Player Guess
    {
        //Player receives winning message
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("Congratulations! You have guessed the word correctly."));
            EndGame();
        }
        else
        {
            if (Input.Len() != HiddenWord.Len()) {
                PrintLine(FString::Printf(TEXT("The Hidden Word is %i characters long.\nNo lives will be removed.\nPlease try again..."), HiddenWord.Len()));
            }
            else {
                --Lives;

                //Check if lives is 0
                if (Lives <= 0)
                {
                    PrintLine(TEXT("Game Over! The Hidden Word is " + HiddenWord));
                    EndGame();
                }
                else {
                    PrintLine(TEXT("You have %i lives remaining.\nPlease try again..."), Lives);
                }

            }


        }
    }


    // Check if word is isogram
    //Ask player if they want to play again

}

void UBullCowCartridge::SetupGame()
{
    //Welcome Message
    PrintLine(TEXT("Hi, Welcome to Bulls & Cows!"));;
   
    
    HiddenWord = TEXT("abouts");
    Lives = HiddenWord.Len(); // number of lives is dependent on the length of word
    bGameOver = false;


    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Please provide us with your guess\nand press enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again..."));
    
}