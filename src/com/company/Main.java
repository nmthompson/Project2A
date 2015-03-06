package com.company;

import java.util.Scanner;

public class Main {


    public static void main(String[] args) {

        String FILE;

        System.out.println("Please indicate file name: ");
        Scanner user_input = new Scanner(System.in);
        FILE = user_input.next();

        UserInterface userInterface = new UserInterface();
        userInterface.readFile(FILE); //Need to add check for file input

    }
}
