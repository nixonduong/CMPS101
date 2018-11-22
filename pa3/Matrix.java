/*
Student: Nixon Duong
CruzID: niduong
Professor: Patrick Tantalo
Course: CMPS101
Programming Assignment: PA3
Description: Provides elementry matrix operations to clients
File: Matrix.java
*/
public class Matrix{
	private class Entry{
		int column;
		double data;
		Entry(int column, double data){
			this.column = column;
			this.data = data;
		}
		public boolean equals(Entry e){
			if(e instanceof Entry && this.column == e.column && this.data == e.data){
					return true;
			}
			return false;
		}
		public String toString(){
			return("(" + Integer.toString(column) + ", " + Double.toString(data) + ")");
		}
	}

	List [] row;

	//Constructor
	Matrix(int n){//Makes a new n x n zero Matrix. Pre: n>=1
		if(!(n>=1)){
			throw new RuntimeException("Dimension Error: Dimension of array less than 1");
		}
		row = new List[n+1];
		for(int i=1;i<n+1;i++){
			row[i] = new List();
		}
	}

	//Access functions
	int getSize(){//Returns n, the number of rows and columns of this Matrix
		return row.length-1;
	}

	int getNNZ(){//Returns the number of non-zero entries in this Matrix
		int NNZ = 0;
		for(int i=1; i <=getSize();i++){
			NNZ += this.row[i].length();
		}
		return NNZ;
	}

	public boolean equals(Object x){//overrides Object's equals() method
		if(x instanceof Matrix){
			Matrix in = (Matrix) x;
			if(this.getSize() != in.getSize() || this.getNNZ() != in.getNNZ()){
				return false;
			}
			for(int i = 1; i <= getSize(); i++){
				if(!(row[i].equals(in.row[i]))){
					return false;
				}
			}
		}
		return true;
	}

	//Manipulation procedures
	void makeZero(){// sets this Matrix to the zero state
		for(int i=1;i<= getSize(); i++){
			row[i].clear();
		}
	}

	Matrix copy(){// returns a new Matrix having the same entries as this Matrix
		Matrix matrix_copy = new Matrix(getSize());
		for(int i=1;i<=getSize();i++){
			row[i].moveFront();
			while(row[i].index() >= 0){   
				matrix_copy.changeEntry(i,((Entry)(row[i].get())).column,((Entry)(row[i].get())).data);				
				row[i].moveNext();
			}
		}
		return matrix_copy;
	}

	void changeEntry(int i, int j, double x){//changes ith row, jth column of this Matrix to x Pre: 1<=i<=getSize(), 1<=j<=getSize()
		if(i < 1 || i > getSize() || j < 1 || j > getSize()){
			throw new RuntimeException("Entry out of bounds: changeEntry() called on an invalid entry");
		}
		else{
			if(row[i].length() == 0 && x != 0){
				row[i].append(new Entry(j,x));
			}
			else{
				row[i].moveFront();
				boolean inserted = false;
				while(row[i].index() >= 0){
					if(((Entry) row[i].get()).column == j){
						if(x == 0){
							row[i].delete(); 
						}
						else{
							((Entry) row[i].get()).data = x;
						}
						inserted = true;
						break;
					}	
					if(((Entry) row[i].get()).column > j && x != 0){
						row[i].insertBefore(new Entry(j,x));
						inserted = true;
						break;
					}
					row[i].moveNext();
				}
				if(inserted == false && x != 0){
					row[i].append(new Entry(j,x));
				}
			}
		}		
	}

	Matrix scalarMult(double x){// returns a new Matrix that is the scalar product of this Matrix with x
		Matrix scaledMatrix = new Matrix(getSize());
		for(int i=1;i <= getSize();i++){
			row[i].moveFront();
			while(row[i].index() >= 0){
				scaledMatrix.changeEntry(i,((Entry)(row[i].get())).column,(((Entry)(row[i].get())).data) * x);
				row[i].moveNext();
			}
		}
		return scaledMatrix;
	}


	Matrix add(Matrix M){//returns a new Matrix that is the sum of this Matrix with M Pre: getSize() == M.getSize()	
		if(getSize() != M.getSize()){
			throw new RuntimeException("add() called on matricies with different sizes");
		}
		else if(M.getNNZ() == 0){
			return copy();
		}
		else if(getNNZ() == 0){
			return M.copy();
		}
		else if(equals(M)){
			return copy().scalarMult(2);
		}
		else{
			Matrix added_Matrix = new Matrix(getSize());
			for(int i = 1; i <= getSize(); i++){
				if(row[i].length() != 0 && M.row[i].length() == 0){
					row[i].moveFront();
					while(row[i].index() >=0){
						added_Matrix.row[i].append((Entry)row[i].get());
						row[i].moveNext();
					}
				}
				else if(row[i].length() == 0 && M.row[i].length() != 0){
					M.row[i].moveFront();
					while(M.row[i].index() >=0){
						added_Matrix.row[i].append((Entry)M.row[i].get());
						M.row[i].moveNext();
					}
				}
				else if(row[i].length() != 0 && M.row[i].length() != 0){
					row[i].moveFront();
					M.row[i].moveFront();
					Entry A;
					Entry B;
					while(row[i].index() >= 0 && M.row[i].index() >=0){
					    A = (Entry) row[i].get();	
						B = (Entry) M.row[i].get();
						if(A.column == B.column){
							added_Matrix.row[i].append(new Entry(A.column, A.data + B.data));
						}
						else if(A.column > B.column){
							while(A.column > B.column){
								added_Matrix.row[i].append(new Entry(B.column, B.data));
								M.row[i].moveNext();
								if(M.row[i].index() != -1){
									B = (Entry) M.row[i].get();
								}
								else{
									break;
								}
							}
							if(A.column == B.column){
								added_Matrix.row[i].append(new Entry(A.column, A.data + B.data));
							}
						}
						else if(A.column < B.column){
							while(A.column < B.column){
								added_Matrix.row[i].append(new Entry(A.column, A.data));
								row[i].moveNext();
								if(row[i].index() != -1){
									A = (Entry)row[i].get();
								}
								else{
									break;
								}
							}
							if(A.column == B.column){
								added_Matrix.row[i].append(new Entry(A.column, A.data + B.data));
							}
						}
						row[i].moveNext();
						M.row[i].moveNext();
					}
					if(row[i].index() == -1 && M.row[i].index() !=-1){
						while(M.row[i].index() >= 0){
							B = (Entry) M.row[i].get();
							added_Matrix.row[i].append(new Entry(B.column, B.data));
							M.row[i].moveNext();
						}
					}
					if(row[i].index() != -1 && M.row[i].index() == -1){
						while(row[i].index() >=0){
							A = (Entry) row[i].get();
							added_Matrix.row[i].append(new Entry(A.column, A.data));
							row[i].moveNext();
						}
					}
				}
			}
			return added_Matrix;
		}
	}
	
	Matrix sub(Matrix M){//returns a new Matrix that is the difference of this Matrix with M Pre: getSize() == M.getSize()
		if(getSize() != M.getSize()){
			throw new RuntimeException("sub() called on matricies with difference sizes");
		}
		else if(M.getNNZ() == 0 && getNNZ() != 0){
			return copy();
		}
		else if(getNNZ() == 0 && M.getNNZ() != 0){
			return M.copy().scalarMult(-1);
		}
		else if(equals(M)){
			return (new Matrix(getSize()));
		}
		else{
			Matrix sub_Matrix = new Matrix(getSize());
			for(int i = 1; i <= getSize(); i++){
				if(row[i].length() != 0 && M.row[i].length() == 0){
					row[i].moveFront();
					while(row[i].index() >=0){
						sub_Matrix.row[i].append((Entry)row[i].get());
						row[i].moveNext();
					}
				}
				else if(row[i].length() == 0 && M.row[i].length() != 0){
					M.row[i].moveFront();
					Entry C;
					while(M.row[i].index() >=0){
						C = (Entry)M.row[i].get();
						sub_Matrix.row[i].append(new Entry(C.column, C.data * (-1)));
						M.row[i].moveNext();
					}
				}
				else if(row[i].length() != 0 && M.row[i].length() != 0){
					row[i].moveFront();
					M.row[i].moveFront();
					Entry A;
					Entry B;
					while(row[i].index() >= 0 && M.row[i].index() >=0){
					    A = (Entry) row[i].get();	
						B = (Entry) M.row[i].get();
						if(A.column == B.column){
							sub_Matrix.row[i].append(new Entry(A.column, A.data - B.data));
						}
						else if(A.column > B.column){
							while(A.column > B.column){
								sub_Matrix.row[i].append(new Entry(B.column, B.data * (-1)));
								M.row[i].moveNext();
								if(M.row[i].index() != -1){
									B = (Entry) M.row[i].get();
								}
								else{
									break;
								}
							}
							if(A.column == B.column){
								sub_Matrix.row[i].append(new Entry(A.column, A.data - B.data));
							}
						}
						else if(A.column < B.column){
							while(A.column < B.column){
								sub_Matrix.row[i].append(new Entry(A.column, A.data));
								row[i].moveNext();
								if(row[i].index() >= 0){
									A = (Entry)row[i].get();
								}
								else{
									break;
								}
							}
							if(A.column == B.column){
								sub_Matrix.row[i].append(new Entry(A.column, A.data - B.data));
							}
						}
						row[i].moveNext();
						M.row[i].moveNext();
					}
					if(row[i].index() == -1 && M.row[i].index() !=-1){
						while(M.row[i].index() >= 0){
							B = (Entry) M.row[i].get();
							sub_Matrix.row[i].append(new Entry(B.column, B.data * (-1)));
							M.row[i].moveNext();
						}
					}
					if(row[i].index() != -1 && M.row[i].index() == -1){
						while(row[i].index() >=0){
							A = (Entry) row[i].get();
							sub_Matrix.row[i].append(new Entry(A.column, A.data));
							row[i].moveNext();
						}
					}
				}
			}
			return sub_Matrix;
		}
	} 
	
	Matrix transpose(){//returns a new Matrix that is the transpose of this Matrix
		Matrix transpose = new Matrix(getSize());
		if(getNNZ() > 0){
			for(int i = 1; i <= getSize(); i++) {
        		row[i].moveFront();
        		while(row[i].index() >= 0){
        			transpose.changeEntry(((Entry)row[i].get()).column, i, ((Entry)row[i].get()).data);
           			row[i].moveNext();
        		}
     		}
		}
     	return transpose;
	}

	Matrix mult(Matrix M){// returns a new Matrix that is the prodcut of this Matrix with M Pre: getSize()==M.getSize()
		if(getSize() != M.getSize()){
			throw new RuntimeException("mult() called on two matrices with different sizes");
		}
		Matrix mult_Matrix = new Matrix(getSize());
		Matrix transposedSelf = copy().transpose();
		for(int i = 1; i <= getSize(); i++){
			for(int j = 1; j <= getSize(); j++){
				mult_Matrix.changeEntry(i,j,dot(transposedSelf.row[j], M.row[i]));
			}
		} 
		return mult_Matrix;
	}

	//Other functions
	public String toString(){// overrides Object's toString() method
		StringBuffer matrixString = new StringBuffer();
		for(int i=1;i<=getSize();i++){
			if(row[i].length() > 0){
				matrixString.append(Integer.toString(i)+": ");
				row[i].moveFront();
				while(row[i].index() >= 0){
					matrixString.append(((Entry)row[i].get()).toString() + " ");
					row[i].moveNext();
				}
				matrixString.append("\n");
			}
		}
		return(new String(matrixString));
	}

	
	private static double dot(List P, List Q){//returns the dot product of P and Q
		double dotProduct = 0;
		if(P.length() == 0 || Q.length() == 0){
			return (dotProduct);
		}
		else{
			P.moveFront();
			Q.moveFront();
			Entry A;
			Entry B;
			while(P.index() >= 0 && Q.index() >= 0){
				A = (Entry) P.get();
				B = (Entry) Q.get();
				if(A.column == B.column){
					dotProduct += (A.data * B.data);
				}
				else if(A.column > B.column){
					while(A.column > B.column){
						Q.moveNext();
						if(Q.index() != -1){
							B = (Entry) Q.get();
						}
						else{
							break;
						}
					}			
					if(A.column == B.column){
						dotProduct += (A.data * B.data);
					}
				}
				else if(A.column < B.column){
					while(A.column < B.column){
						P.moveNext();
						if(P.index() != -1){
							A = (Entry) P.get();
						}
						else{
							break;
						}
					}
					if(A.column == B.column){
						dotProduct += (A.data * B.data);
					}
				}
				P.moveNext();
				Q.moveNext();
			}
			return dotProduct;
		}
	}
}

