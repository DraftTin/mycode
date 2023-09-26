public class Stack{
	private int top;
	private int[] stack;
	//private int length;
	// top处不存放元素，所以top == 0时栈空，top == maxSize + 1时，栈满
	Stack() {
		top = 0;
		stack = new int[50];
	}
	int length(){
		return top;
	}
	void push(int val){
		stack[top] = val;
		top++;
	}
	void pop(){
		if(!empty())
			top--;
	}
	int top(){
		if(!empty())
			return stack[top - 1];
		System.out.println("The stack is empty");
		return -1;
	}
	boolean empty(){
		if(top == 0)
			return true;
		return false;
	}
	public static void main(String[] args){
		Stack sta = new Stack();
		sta.push(5);
		int tmp = sta.top();
		System.out.println(tmp);
	}
}