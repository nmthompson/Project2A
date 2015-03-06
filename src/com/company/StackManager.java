package com.company;

import java.util.Stack;

/**
 * Created by nicholasthompson on 3/5/15.
 */
public class StackManager{

    Stack equationStack = new Stack();
    Stack holdStack = new Stack();

    public void arrayToStack(String value) { //pushes current equation onto Stack

        for (int i = 0; i < value.length(); i++) { //for each character of equation, push to equationStack
            char ch = value.charAt(i);
            Character.isDigit(ch);
            equationStack.push(ch);
        }
        infixOperation(equationStack);
    }
    public void infixOperation(Stack equationStack) {

        while (!equationStack.isEmpty()) {
            for (int i = 0; i < equationStack.size(); i++) {
                Object top = equationStack.peek(); //look at top of stack and assign value
                if(top == " "){ //if top contains a space, pop it
                    equationStack.pop();
                    return;
                }
                if(top == "+"){

                }

            }
        }

    }

}
