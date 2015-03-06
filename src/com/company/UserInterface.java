package com.company;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
/**
 * Created by nicholasthompson on 3/4/15.
 */
public class UserInterface {
    //reads input file and convert each line to string array
    public static void readFile(String FILE){

        String line;
        ArrayList<String> equations = new ArrayList(); //Array to hold all equations read from file

        try{
            File file = new File(FILE);
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            StringBuffer stringBuffer = new StringBuffer();

            while((line = bufferedReader.readLine()) != null){
                equations.add(line); //add line to array
            }
            fileReader.close();

            if(!equations.isEmpty()) { //as long as array isn't empty, loop through and pass equations to the to stack class
                for (int i = 0; i < equations.size(); i++) {
                    StackManager stackManager = new StackManager();
                    String value = equations.get(i);
                    stackManager.arrayToStack(value);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("Please choose a valid file.");
        }


    }


}
