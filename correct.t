
charp x;
int x,z;
intp y;

y =&x;
x = 5;
z = ^y;

////

int foo() {
	return 0;
}

void main() {
	int a;
	a = foo();
}

////

int foo(int i, int j, int k) {
	intp i;
	boolean fee(int l, int i, char n) {
		return true;
	}
	return 0;
}

////

int foo_2() { }
char f234() { return '0'; }

////
int foo(int i, char j, string k) {
	int k;
	int square(int t)
	{
		int temp;
		temp = t*t;
		return temp;
	}
	int total;

	k = 5;
	total = i + square(k);
	return total - 10;
}


////

int i;
boolean m, n;
char c;
string s1[10], s2[20];

////
c = 'e';
a[19] = 'f';
a[4+3] = 'd';
b = a;
a = "test";
i = |s|;

////
int foo() {
	int x;
	{
		int y;
		x = 1;
		y = 2;
		{
			x = 2;
		}
		y = 3;
	}
	return 0;
}

int foo() {
	{} /* empty block */
	return 0;
}

////

int foo() { return 0; }
int foo_2() { int a; a =2; return a; }
int foo_3() {  return foo(); }
int foo_4() { if(true) { return 4; } return 10; }

////
3 || 2
(3+2) / 3 - 5 * 2
true && false || false
0x512
true
-5
^x
^(p+5)
!false

////

a = foo(i,j);
goo("hello");

////
charp z;
intp y;
y  = &x;
z = "foobar";
z = &z[5];
z = ^(z-5);


