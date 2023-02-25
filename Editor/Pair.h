template <class A, class B>
struct Pair {
	A elemA;
	B elemB;
	Pair() {

	}
	Pair(A a, B b) {
		elemA = a;
		elemB = b;
	}
	bool operator==(Pair &p) {
		return elemA == p.elemA;
	}
	bool operator!=(Pair &p) {
		return elemA != p.elemA;
	}
	bool operator>(Pair &p) {
		return elemA>p.elemA;
	}
	bool operator<(Pair &p) {
		return elemA<p.elemA;
	}
	operator A() {
		return elemA;
	}
};

template <class A, class B, class C>
struct Triple {
	A elemA;
	B elemB;
	C elemC;
	Triple() {

	}
	Triple(A a, B b, C c) {
		elemA = a;
		elemB = b;
		elemC = c;
	}
	bool operator==(Triple &p) {
		return elemA == p.elemA;
	}
	bool operator!=(Triple &p) {
		return elemA != p.elemA;
	}
	bool operator>(Triple &p) {
		return elemA>p.elemA;
	}
	bool operator<(Triple &p) {
		return elemA<p.elemA;
	}
	operator A() {
		return elemA;
	}
};

template <class A, class B, class C, class D>
struct Quad {
	A elemA;
	B elemB;
	C elemC;
	D elemD;
	Quad() {

	}
	Quad(A a, B b, C c, D d) {
		elemA = a;
		elemB = b;
		elemC = c;
		elemD = d;
	}
	bool operator==(Quad &p) {
		return elemA == p.elemA;
	}
	bool operator!=(Quad &p) {
		return elemA != p.elemA;
	}
	bool operator>(Quad &p) {
		return elemA>p.elemA;
	}
	bool operator<(Quad &p) {
		return elemA<p.elemA;
	}
	operator A() {
		return elemA;
	}
}; 
