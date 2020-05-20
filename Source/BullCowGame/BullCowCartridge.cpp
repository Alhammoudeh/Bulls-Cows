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
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    //Welcome Message
    PrintLine(TEXT("Hi, Welcome to Bulls & Cows!"));;
   
    
    HiddenWord = TEXT("about");
    Lives = HiddenWord.Len(); // number of lives is dependent on the length of word
    bGameOver = false;


    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Please provide us with your guess and\npress enter to continue..."));

    //PrintLine(TEXT("The first character of the hidden word is:%c"), HiddenWord[0]); // print "a"
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    //Ask player if they want to play again
    PrintLine(TEXT("Press enter to play again..."));
    
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    //Player receives winning message
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Congratulations! You have guessed the word\ncorrectly."));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len()) {
        PrintLine(FString::Printf(TEXT("The Hidden Word is %i letters long.\nNo lives will be removed.\nPlease try again..."), HiddenWord.Len()));
        return;
    }

    // Check if Guess is Isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("There are no repeating letters for this word. Please try again..."));
        return;
    }

    --Lives;

    if (Lives <= 0)
    {
        PrintLine(TEXT("Game Over! The Hidden Word is " + HiddenWord));
        EndGame();
        return;
    }

    ClearScreen();
    PrintLine(TEXT("Sorry, that is incorrect.\nYou have %i lives remaining.\nPlease try again..."), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    // Check each character for repeats
        // For each letter in Guess
        // Start from first element to final element
        // Compare element with next element
        // repeat until we reach Guess.Len() - 1
    // return True if no repeating
    // else return False if repeating

    return true;

}