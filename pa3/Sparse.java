/*
Student: Nixon Duong
CruzID: niduong
Professor: Patrick Tantalo
Course: CMPS101
Programming Assignment: PA3
Description: Main class
File: Sparse.java
*/
import java.io.*;
import java.util.Scanner;
public class Sparse{
	public static void main(String [] args)throws FileNotFoundException{
		if(args.length != 2){
			System.err.println("Error: Two argumetns are required");
			System.exit(1);
		}
		Scanner infile = null;
		PrintWriter outfile = null;
		try{
			infile = new Scanner(new File(args[0]));
			outfile = new PrintWriter(new File(args[1]));
		}
		catch(FileNotFoundException exception){
			System.err.println("FileNotFoundException: file could not be found");
			System.exit(1);
		}
		int sizeofMatrix = Integer.parseInt(infile.next());
		int aNNZ = Integer.parseInt(infile.next());
		int bNNZ = Integer.parseInt(infile.next());
		Matrix A = new Matrix(sizeofMatrix + 1);
		Matrix B = new Matrix(sizeofMatrix + 1);
		int row, column;
		double data;
		for(int i = 1; i <= aNNZ; i++){
			row = Integer.parseInt(infile.next());
			column = Integer.parseInt(infile.next());
			data = Double.parseDouble(infile.next());
			A.changeEntry(row, column, data);
		}
		for(int i = 1; i <= bNNZ; i++){
			row = Integer.parseInt(infile.next());
			column = Integer.parseInt(infile.next());
			data = Double.parseDouble(infile.next());
			B.changeEntry(row, column, data);
		}
		// A
		outfile.println("A has " + Integer.toString(A.getNNZ()) + " non-zero entries:");
		outfile.println(A);
		// B
		outfile.println("B has " + Integer.toString(B.getNNZ()) + " non-zero entries:");
		outfile.println(B);
		//(1.5)A
		outfile.println("(1.5)*A =");
		outfile.println(A.scalarMult(1.5));
		// A + B
		outfile.println("A+B =");
		outfile.println(A.add(B));
		// A + A
		outfile.println("A+A =");
		outfile.println(A.add(A));
		// B - A
		outfile.println("B-A =");
		outfile.println(B.sub(A));
		// A - A
		outfile.println("A-A =");
		outfile.println(A.sub(A));
		// A^T
		outfile.println("Transpose(A) = ");
		outfile.println(A.transpose());
		// AB
		outfile.println("A*B =");
		outfile.println(A.mult(B));
		// B^2
		outfile.println("B*B =");
		outfile.println(B.mult(B));

		infile.close();
		outfile.close();
	}
}