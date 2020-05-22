// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    SetupGame();

}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver) 
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking Player Guess
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    //Welcome Message
    PrintLine(TEXT("Hi, Welcome to Bulls & Cows!"));;
   
    
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len(); // number of lives is dependent on the length of word
    bGameOver = false;


    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    //PrintLine(TEXT("The Hidden Word is: %s"), *HiddenWord); //Debug Line
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Please provide us with your guess and\npress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    //Ask player if they want to play again
    PrintLine(TEXT("Press enter to play again..."));
    
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
        PrintLine(TEXT("There are no repeating letters.\nPlease try again..."));
        return;
    }

    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("Game Over! The Hidden Word is " + HiddenWord));
        EndGame();
        return;
    }

    //Show player Bulls and Cows count
    FBullCowCounter Counter = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Counter.Bulls, Counter.Cows);

    PrintLine(TEXT("Sorry, that is incorrect.\nYou have %i lives remaining.\nPlease try again..."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Compare = Index + 1; Compare < Word.Len(); Compare++)
        {
            if (Word[Index] == Word[Compare]) {
                return false;
            }
        }
    }

    return true;

    // update to check for case sensitivity
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList) 
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

FBullCowCounter UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCounter Counter;

    for (int32 GIndex = 0; GIndex < Guess.Len(); GIndex++)
    {
        if (Guess[GIndex] == HiddenWord[GIndex])
        {
            Counter.Bulls;
            continue;
        }

        for (int32 HIndex = 0; HIndex < Guess.Len(); HIndex++)
        {
            if (Guess[GIndex] == HiddenWord[HIndex]) 
            {
                Counter.Cows++;
                break;
            }
        }
    }
    return Counter;
}