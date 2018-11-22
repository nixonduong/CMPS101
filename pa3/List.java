/*
Student: Nixon Duong
CruzID: niduong
Professor: Patrick Tantalo
Course: CMPS101
Programming Assignment: PA3
Description: Provides a bi-directional list to clients
File: List.java
Clients: Matrix.java
*/
public class List{
	private class Node{
		Object data;
		Node prev;
		Node next;
		Node(Object data){
			this.data = data;
			this.prev = null;
			this.next = null;
		}
		public String toString(){
			return String.valueOf(data);
		}
	}
	private Node front,back,cursor;
	private int length;
	private int index;
	
	//Constructor
	List(){// Creates a new empty list.
		front = back = cursor = null;
		length = 0;
		index = -1;
	}

	//Access functions
	int length(){//Returns the number of elements in this List.
		return this.length;
	}

	int index(){//If cursor is defined, returns the index of the cursor element, otherwise -1.
		if(this.cursor != null){
			return this.index;
		}
		return -1;
	}

	Object front(){//Returns front element. Pre: length()>0
		if(this.length>0){
			return this.front.data;
		}
		throw new RuntimeException("front() called on an empty List");
	}

	Object back(){//Returns back element. Pre: length()>0
		if(this.length>0){
			return this.back.data;
		}
		throw new RuntimeException("back() called on an empty List");
	}

    Object get(){//Returns cursor element. Pre: length()>0, index() >=0
		if(length()>0){
		    if(cursor != null){
				return cursor.data;
	    	}
		    else{
				throw new RuntimeException("get() called on an undefined cursor");
	    	}
		}
		throw new RuntimeException("get() called on an empty List");
    }
	    
	public boolean equals(Object x){//Returns true if and only if this List and L are the same integer sequence. The states of the cursors in the two List are not used in determining equality
		return(this.toString().equals(x.toString()));
	}

	//Manipulation procedures
	void clear(){//Resets this List to its original empty state
		this.front = null;
		this.back = null;
		this.cursor = null;
		this.length = 0;
		this.index = -1;
	}

	void moveFront(){//If List is non-empty, places cursor under the front element, otherwise does nothing
		if(this.length>0){
			this.cursor = this.front;
		}
		this.index = 0;
	}

	void moveBack(){//If List is non-empty, places the cursor under the back element, otherwise does nothing
		if(this.length>0){
			this.cursor = this.back;
			this.index = this.length - 1;
		}
	}

	void movePrev(){//If cursor is defined and not at front, moves cursor one step toward front of this List, if cursor is defined and at the front, cursor becomes undefined, if cursor is undefined does nothing
		if(this.cursor!=null){
			if(this.cursor!=this.front){
				this.cursor = this.cursor.prev;
			}
			else{
				this.cursor = null;
			}
		}
		this.index--;
	}

	void moveNext(){//If cursor is defined and not at back, moves cursor one step toward back of this List, if cursor is defined and at the back, cursor becomes undefined, if cursor is undefined does nothing
		if(this.cursor!=null){
			if(this.cursor!=this.back){
				this.cursor = this.cursor.next;
			}
			else{
				this.cursor = null;
			}
		}
		this.index++;
	}

	void prepend(Object data){//Insert new element into this List. If List is non-empty, insertion takes place before front element.
		Node newNode = new Node(data);
		if(this.length == 0){
			this.front = this.back = newNode;
		}
		else{
			newNode.next = this.front;
			this.front.prev = newNode;
			this.front = newNode;
		}
		this.length++;
		this.index++;
	}

	void append(Object data){//Insert new element into this List. If List is non-empty, insertion takes place after back element.
		Node newNode = new Node(data);
		if(this.length == 0){
			this.front = this.back = newNode;
		}
		else{
			this.back.next = newNode;
			newNode.prev = this.back;
			this.back = newNode;
		}
		length++;
	}

	void insertBefore(Object data){//Insert new element before cursor. Pre: length()>0, index()>=0
		if(this.index == -1){
			throw new RuntimeException("insertBefore() on undeclared cursor");
		}
		if(this.length > 0 && this.index >=0){
			Node newNode = new Node(data);
			if(this.cursor == this.front){
				this.prepend(data);
			}
			else{
				newNode.next = this.cursor;
				this.cursor.prev.next = newNode;
				newNode.prev = this.cursor.prev;
				this.cursor.prev = newNode;
				this.length++;
				this.index++;
			}
		}
	}

	void insertAfter(Object data){//Insert new element after cursor. Pre: length()>0, index()>=0
		if(this.index == -1){
			throw new RuntimeException("insertAfter() on undeclared cursor");
		}
		if(this.length > 0 && this.index >=0){
			if(this.cursor == this.back){
				append(data);
			}
			else{
				Node newNode = new Node(data);
				newNode.prev = this.cursor;
				newNode.next = this.cursor.next;
				this.cursor.next.prev = newNode;
				this.cursor.next = newNode;
				this.length++;
			}
		}
	}

	void deleteFront(){//Deletes the front element. Pre: length()>0
		if(this.length == 0){
			throw new RuntimeException("deleteFront() on emptyList");
		}
		if(this.length > 0){
			if(this.length == 1){
				this.cursor = this.front = this.back = null;
				this.index = -1;
			}
			else{
				if(this.cursor == this.front){
					this.front = this.front.next;
					this.front.prev = null;
					this.cursor = null;
					this.index = -1;
				}
				else{
					this.front = this.front.next;
					this.front.prev = null;
					if(this.cursor!=null){
						this.index--;
					}
				}
			}
			this.length--;
		}
	}

	void deleteBack(){//Deletes the back element. Pre: length()>0
		if(this.length == 0){
			throw new RuntimeException("deleteBack() on emptyList");
		}
		if(this.length > 0){
			if(this.length == 1){
				this.cursor = this.front = this.back = null;
				this.index = -1;
			}
		else{
			if(this.cursor == this.back){
				this.cursor = null;
				this.index = -1;
			}
			this.back = this.back.prev;
			this.back.next = null;
		}
			this.length--;
		}
	}

	void delete(){//Deletes cursor element, making cursor undefined. Pre: length()>0, index()>=0
		if(this.length == 0){
			throw new RuntimeException("delete() on emptyList");
		}
		if(this.length>0 && this.index >=0){
			if(this.cursor == this.front){
				this.deleteFront();
			}
			else if(this.cursor == this.back){
				this.deleteBack();
			}
			else{
				this.cursor.prev.next = this.cursor.next;
				this.cursor.next.prev = this.cursor.prev;
				this.length--;
			}
			this.cursor = null;
			this.index = -1;
		}
	}

	//Other methods
	public String toString(){//Overrides Object's toStrig method. Returns a String representation of this List consistign of a space separated sequence of integers, with front on left
		if(this.length == 0){
			return "";
		}
		else{
			Node iterator = this.front;
			StringBuffer list = new StringBuffer();
			while(iterator != null){
				list.append(iterator.toString()).append(" ");
				iterator = iterator.next;
			}
			return (new String(list));
		}
	}
}
