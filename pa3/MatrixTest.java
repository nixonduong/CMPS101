/*
Student: Nixon Duong
CruzID: niduong
Professor: Patrick Tantalo
Course: CMPS101
Programming Assignment: PA3
Description: used to test Matrix.java
File: MatrixTest.java
*/
public class MatrixTest{
	public static void main(String [] args){
		Matrix a = new Matrix(3);
		Matrix b = new Matrix(3);
		a.changeEntry(1,1,1);
		a.changeEntry(1,2,2);
		a.changeEntry(1,3,3);
		a.changeEntry(2,1,1);
		a.changeEntry(2,2,2);
		a.changeEntry(2,3,3);
		a.changeEntry(3,1,1);
		a.changeEntry(3,2,2);
		a.changeEntry(3,3,3);
		b.changeEntry(1,1,1);
		b.changeEntry(1,3,1);
		b.changeEntry(2,1,1);
		b.changeEntry(2,3,1);
		b.changeEntry(3,1,1);
		b.changeEntry(3,3,1);
		System.out.println("Matrix A");
		System.out.println(a);
		System.out.println("Matrix A copy");
		System.out.println(a.copy());
		System.out.println("Matrix A scaled by 20");
		System.out.println(a.scalarMult(20));
		System.out.println("Matrix A transpose");
		System.out.println(a.transpose());
		
		System.out.println("********************************");
		System.out.println(a);
		System.out.println(b);
		
		System.out.println("Matrix A add B");
		System.out.println(a.add(b));

		System.out.println("Matrix A sub B");
		System.out.println(a.sub(b));

		System.out.println("Matrix A mult with Identity Matrix");
		Matrix c = new Matrix(a.getSize());		
		c.changeEntry(1,1,1);
		c.changeEntry(2,2,1);
		c.changeEntry(3,3,1);
		System.out.println(a.mult(c));
	}
}

/*
Output:
Matrix A
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 1.0) (2, 2.0) (3, 3.0)
3: (1, 1.0) (2, 2.0) (3, 3.0)

Matrix A copy
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 1.0) (2, 2.0) (3, 3.0)
3: (1, 1.0) (2, 2.0) (3, 3.0)

Matrix A scaled by 20
1: (1, 20.0) (2, 40.0) (3, 60.0)
2: (1, 20.0) (2, 40.0) (3, 60.0)
3: (1, 20.0) (2, 40.0) (3, 60.0)

Matrix A transpose
1: (1, 1.0) (2, 1.0) (3, 1.0)
2: (1, 2.0) (2, 2.0) (3, 2.0)
3: (1, 3.0) (2, 3.0) (3, 3.0)

********************************
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 1.0) (2, 2.0) (3, 3.0)
3: (1, 1.0) (2, 2.0) (3, 3.0)

1: (1, 1.0) (3, 1.0)
2: (1, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

Matrix A add B
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 2.0) (2, 2.0) (3, 4.0)
3: (1, 2.0) (2, 2.0) (3, 4.0)

Matrix A sub B
1: (1, 0.0) (2, 2.0) (3, 2.0)
2: (1, 0.0) (2, 2.0) (3, 2.0)
3: (1, 0.0) (2, 2.0) (3, 2.0)

Matrix A mult with Identity Matrix
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 1.0) (2, 2.0) (3, 3.0)
3: (1, 1.0) (2, 2.0) (3, 3.0)
*/
