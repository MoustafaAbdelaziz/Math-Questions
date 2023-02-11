#include <iostream>
#include <iomanip>
#include <windows.h>
#include "MyLib.h"
#include <string>
using namespace std;

enum enOperator { Sum = 1, Subtract, Multiply, Division, Mix };
enum enQuestionLvl { Easy = 1, Medium, Hard, mix };

struct stQuestionInfo
{
    int Num1 = 0;
    int Num2 = 0;
    enOperator OpType = enOperator::Sum;
    enQuestionLvl QuestionLvl = enQuestionLvl::Easy;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};
struct stQuizzResult
{
    stQuestionInfo QuestionList[100];
    short NumberOfQuestions = 0;
    enQuestionLvl QuestionLvl = enQuestionLvl::Easy;
    enOperator OpType = enOperator::Sum;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool isPass = false;
};

int ReadHowManyQuestions()
{
    cout << "Enter How Many Questions Do You Want [1:100]\n--------------------------------------------\n";
    return  MyLib::ReadNumber(1, 100);
}

enQuestionLvl ReadQuestionLevel()
{
    cout << "\nWhich Question Level Do You Want?";
    cout << "\n\n***********************************\n[1] Easy.\n[2] Medium.\n[3] Hard.\n[4] Mix.\n***********************************\n";
    return (enQuestionLvl)MyLib::ReadNumber(1, 4);
}
enOperator ReadQuestionsType()
{
    cout << "\nWhich Type Of Questions Do You Want?";
    cout << "\n\n***********************************\n[1] Addition Questions.\n[2] Subtraction Questions.\n[3] Multiplying Questions.\n[4] Division Questions.\n[5] Mixed Questions.\n***********************************\n";
    return (enOperator)MyLib::ReadNumber(1, 5);
}

string QuestionLevel(enQuestionLvl QuizzLevel)
{
    string ArrQuizzLevel[4] = { "Easy", "Medium", "Hard", "Mix" };
    return ArrQuizzLevel[QuizzLevel - 1];
}
string QuestionTypeName(enOperator QuestionType)
{
    string ArrQuestionName[5] = { "Addition", "Subtraction", "Multiply", "division", "Mix" };
    return ArrQuestionName[QuestionType - 1];
}
string GetOpTypeSymbol(enOperator OpType)
{
    switch (OpType)
    {
    case enOperator::Sum:
        return"+";
    case enOperator::Subtract:
        return"-";
    case enOperator::Multiply:
        return"x";
    case enOperator::Division:
        return"/";
    default:
        return "Mix";
    }
}

int calculator(int num1, int num2, enOperator OpType)
{
    switch (OpType)
    {
    case enOperator::Sum:
    {
        return num1 + num2;
        break;
    }
    case enOperator::Subtract:
    {
        return num1 - num2;
        break;
    }
    case enOperator::Multiply:
    {
        return num1 * num2;
        break;
    }
    case enOperator::Division:
    {
        return num1 / num2;
        break;
    }
    default:
    {
        return num1 + num2;
        break;
    }
    }
}

void changeColor(int desiredColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

void ShowQuestionNumber(short count)
{
    changeColor(3);
    cout << setw(70);
    cout << "************************" << "\n" << setw(65) << "question Number " << count << endl << setw(71) << "************************\n";
    changeColor(15);
}

enOperator GetRandomOpType()
{
    return (enOperator)MyLib::RandomNumber(1, 4);
}

stQuestionInfo GenerateQuestions(enQuestionLvl QuestionLevel, enOperator OperationType)
{
    stQuestionInfo Question;

    if (QuestionLevel == enQuestionLvl::mix)
        QuestionLevel = (enQuestionLvl)MyLib::RandomNumber(1, 3);

    if (OperationType == enOperator::Mix)
        OperationType = GetRandomOpType();

    Question.OpType = OperationType;

    switch (QuestionLevel)
    {
    case enQuestionLvl::Easy:
    {
        Question.Num1 = MyLib::RandomNumber(1, 10);
        Question.Num2 = MyLib::RandomNumber(1, 10);
        Question.CorrectAnswer = calculator(Question.Num1, Question.Num2, Question.OpType);
        Question.QuestionLvl = QuestionLevel;
        return Question;
    }

    case enQuestionLvl::Medium:
    {
        Question.Num1 = MyLib::RandomNumber(10, 50);
        Question.Num2 = MyLib::RandomNumber(10, 50);
        Question.CorrectAnswer = calculator(Question.Num1, Question.Num2, Question.OpType);
        Question.QuestionLvl = QuestionLevel;
        return Question;
    }

    case enQuestionLvl::Hard:
    {
        Question.Num1 = MyLib::RandomNumber(50, 100);
        Question.Num2 = MyLib::RandomNumber(50, 100);
        Question.CorrectAnswer = calculator(Question.Num1, Question.Num2, Question.OpType);
        Question.QuestionLvl = QuestionLevel;
        return Question;
    }
    default:
        return Question;
    }

}

void GenerateQuizzQuestions(stQuizzResult& Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
        Quizz.QuestionList[Question] = GenerateQuestions(Quizz.QuestionLvl, Quizz.OpType);
}

int ReadQuestionAnswer()
{
    return MyLib::ReadNumber<int>();
}

void PrintQuestion(stQuizzResult& Quizz, short QuestionNumber)
{
    ShowQuestionNumber(QuestionNumber + 1);
    cout << endl << Quizz.QuestionList[QuestionNumber].Num1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Num2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OpType);
    cout << "\n________" << endl;
}
void CorrectTheQuestionAnswer(stQuizzResult& Quizz, int QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].CorrectAnswer == Quizz.QuestionList[QuestionNumber].PlayerAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;
        changeColor(10);
        cout << "Right Answer :-) \n";
        changeColor(15);
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;
        changeColor(4);
        cout << "\aWrong Answer :-(\n";
        changeColor(10);
        cout << "\nThe Right Answer Is : " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
        changeColor(15);
    }
}
void AskAndCorrectQuestionListAnswers(stQuizzResult& Quizz)
{
    for (int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }
    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{
    if (Pass)
    {
        changeColor(10);
        return "PASS :-)";
    }

    else
    {
        changeColor(4);
        return "Fail :-(";
    }
}

void PrintQuizzResults(stQuizzResult Quizz)
{
    cout << "\n";
    cout << "______________________________\n\n";
    cout << " Final Resutls is " << GetFinalResultsText(Quizz.isPass);
    changeColor(15);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level    : " << QuestionLevel(Quizz.QuestionLvl) << endl;
    cout << "OpType             : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right Answers: ";
    changeColor(10);
    cout << Quizz.NumberOfRightAnswers << endl;
    changeColor(15);
    cout << "Number of Wrong Answers: ";
    changeColor(4);
    cout << Quizz.NumberOfWrongAnswers << endl;
    changeColor(15);
    cout << "______________________________\n";
}

void PlayMathGame()
{
    stQuizzResult Quizz;

    Quizz.OpType = ReadQuestionsType();
    Quizz.QuestionLvl = ReadQuestionLevel();
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);
}
void ResetScreen()
{
    system("cls");
    //system("color 0F");
}
void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        changeColor(15);
        PlayMathGame();
        cout << "\n\t\t\tDo you Want to Play again? [N/Y]";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    ResetScreen();
    return 0;
}