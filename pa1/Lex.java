/*
Student: Nixon Duong
CruzID: niduong
Professor: Patrick Tantalo
Course: CMPS101
Programming Assignment: PA1
Description: Opens and reads files contents into an array. Indirectly sorts the array using service provided
from List.java. Writes the sorted version of the array onto an outfile.
File: Lex.java
Dependencies: List.java
*/
import java.io.*;
import java.util.Scanner;
public class Lex{
    public static void main(String[] args) throws IOException{
		int lines = 0;
		if(args.length<2){
			System.err.println("Usage: FileIO infile outfile");
			System.exit(1);
		}
		Scanner inputFile = new Scanner(new File(args[0]));
		while(inputFile.hasNextLine()){
			inputFile.nextLine();
			lines++;
		}
		inputFile.close();
		Scanner input = new Scanner(new File(args[0]));
		String array [] = new String[lines];
		int index = 0;
		while(input.hasNextLine()){
			array[index] = input.nextLine();
			index++;
		}
		input.close();
		List list = new List();
		boolean marker = false;
		list.append(0);
		list.moveFront();
		for(int i =1;i<lines;i++){
			marker = false;
			list.moveFront();
			while(marker==false){
				if(list.index()==-1){
					list.append(i);
					marker = true;
				}
				else if(array[i].compareTo(array[list.get()])>0){
					list.moveNext();
				}
				else{
					list.insertBefore(i);
					marker = true;
				} 
			}
		}
		PrintWriter outfile = new PrintWriter(new FileWriter(args[1]));
		list.moveFront();
		for(int i =0; i < array.length;i++){
		    outfile.println(array[list.get()]);
		    list.moveNext();
		}
		outfile.close();
	}
}