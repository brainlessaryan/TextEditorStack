#include <iostream>
#include <stack>

using namespace std;

class textEditor {

    private:
    stack<char> leftStack;
    stack<char> rightStack;

    public:
        void insertWord(char word[]);
        void insertCharacter(char character);
        bool deleteCharacter();
        bool backSpaceCharacter();
        void moveCursor(int position);
        void moveLeft(int position);
        void moveRight(int position);
        void findAndReplaceChar(char findWhat, char replaceWith);
        void examineTop();
}; 

void textEditor::examineTop(){
    if(leftStack.empty())
        cout << "leftStack: empty\t";
    else
        cout << "leftStack: " << leftStack.top() << "," << leftStack.size() << "\t\t";
    if(rightStack.empty())
        cout << "rightStack: empty\n";
    else
        cout << "rightStack: " << rightStack.top() << "," << rightStack.size() << endl;
} 

void textEditor::insertWord(char word[]) {
    int i=0;

    while(word[i]!='\0') {
        insertCharacter(word[i]);
        i++;
    }
} 

void textEditor::insertCharacter(char character){

    leftStack.push(character);
} 

bool textEditor::deleteCharacter(){

    if (rightStack.empty())
        return false;
    else
        rightStack.pop();
    return true;
}

bool textEditor::backSpaceCharacter(){

    if (leftStack.empty())
        return false;
    else
        leftStack.pop();
    return true;
}

void textEditor::moveCursor(int position){

    int leftSize, rightSize, count;
    leftSize = leftStack.size();
    rightSize = rightStack.size();
    if (position < leftSize)
        moveLeft(position);
    else {
        count = position - leftSize;
        moveRight(count);
    }
}

void textEditor::moveLeft(int position){
    int leftSize;
    leftSize = leftStack.size();
    while(position!=leftSize) {
        rightStack.push(leftStack.top());
        leftStack.pop();
        leftSize = leftStack.size();
    }
}

void textEditor::moveRight(int count){
    int rightSize, i=1;
    rightSize = rightStack.size();
    if (count > rightSize)
        cout << "Cannot move the cursor, right, to the specified position";
    else {
        while(i<=count) {
            leftStack.push(rightStack.top());
            rightStack.pop();
            i++;
        }
    } 
}

void textEditor::findAndReplaceChar(char findWhat, char replaceWith){

    int count=1, originalCursorPoistion = leftStack.size();
    moveCursor(0); 
    while(!rightStack.empty()) {
        if(rightStack.top()==findWhat) {
        deleteCharacter();
        insertCharacter(replaceWith);
        }
        else
            moveCursor(count);
            count++;
    } 
    moveCursor(originalCursorPoistion); 
} 


int main() {
    int i=0; char text[80];
    textEditor txt;

    cout << "Enter the word to be inserted: ";
    cin.getline(text,80);
    txt.insertWord(text);

    cout << "Inserting the word:";
    txt.examineTop();

    cout << "Enter the word to be inserted: ";
    cin.getline(text,80);
    txt.insertWord(text);
    cout << "Inserting the word:";
    txt.examineTop();
    cout << "Move cursor to the position 14: ";
    txt.moveCursor(14); txt.examineTop();
    cout << "Move cursor to the position 17: ";
    txt.moveCursor(17);
    txt.examineTop();

    for(i=0;i<3;i++){
        if(!txt.deleteCharacter())
            cout << "There is nothing to delete. Move your cursor accordingly to delete the character";
        else
            cout << "Delete characters using DEL: ";
            txt.examineTop();
    }

    for(i=0;i<7;i++){
        if(!txt.backSpaceCharacter())
            cout << "There is nothing to delete. Move your cursor accordingly to delete the character";
        else
            cout << "Delete characters using Backspace: ";
            txt.examineTop();
    }

    txt.findAndReplaceChar('t','T');
    cout << "Replace occurrences of t with T: ";
    txt.examineTop();
    return 0;
}
