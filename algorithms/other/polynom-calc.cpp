#include<iostream>	
#include<list>
#include<algorithm>
#include<string>
#include<vector>

struct poly {
	size_t exp;
	size_t coef;

	bool operator==(const poly& other) const {
		return exp == other.exp;
	}

	bool operator<(const poly& other) const {
		return exp < other.exp;
	}
};

using polynom = std::list<poly>;

void insert(polynom& p, poly pol) {
	poly parg = { 0, 0 };

	const auto& last = std::find_if(p.rbegin(),
		p.rend(),
		[&](const poly& arg) -> bool { return pol < arg || arg == pol; });

	if (last == p.rend()) {
		p.insert(p.begin(), pol);
	}
	else if (last->exp == pol.exp) {
		last->coef += pol.coef;
	}
	else {
		p.insert(last.base(), pol);
	}
}

polynom sum(const polynom& fst, const polynom& snd) {
	polynom toReturn;

	for (const auto& pol : fst) {
		insert(toReturn, pol);
	}

	for (const auto& pol : snd) {
		insert(toReturn, pol);
	}

	return toReturn;
}

polynom multiply(const polynom& fst, const polynom& snd) {
	polynom toReturn;

	for (const auto& first : fst) {
		for (const auto& second : snd) {
			poly toInsert = { first.exp + second.exp, first.coef * second.coef };
			insert(toReturn, toInsert);
		}
	}

	return toReturn;
}

void print(const polynom& ll) {
	std::string toPrint;

	for (const auto& p : ll) {
		if (p.coef != 0)
			toPrint +=
			std::to_string(p.coef)
			+ std::string("x^") +
			std::to_string(p.exp)
			+ std::string(" + ");
	}

	if (toPrint.length() >= 3) {
		toPrint.pop_back();
		toPrint.pop_back();
		toPrint.pop_back();
	}

	std::cout << toPrint << std::endl;
}


// A quick snipped for visualizing a task given to me.
// a_1 = 0
// a_2 = s
// s_3 = 3
// a_n = s * a_{n-2} + a_{n-3}

int main() {
	std::vector<polynom> p(100, polynom());

	insert(p[0], { 0, 0 });
	insert(p[1], { 1, 2 });
	insert(p[2], { 0, 3 });

	polynom s;
	insert(s, { 1, 1 });

	for (size_t i = 0; i < 50; i++) {
		p[i + 3] = sum(multiply(s, p[i + 1]), p[i]);
	}

	for (const auto& row : p) {
		print(row);
	}
}
