double sqrtNewton(double number, double l = 0.0001) {
    double temp = number;

    double root = 0;

    while (true) {
        root = 0.5 * (temp + (number / temp));

        if (abs(root - temp) < l)
            break;

        temp = root;
    }

    return root;
}



double sqrtNewtonTwo(double number, int l = 100) {
	double result = 1;
	double temp = 1;

	for (int i = 0; i < l; i++) {
		temp = 0.5 * (result + number / result);

		if (temp == result && result != 1)
			return result;

		result = temp;
	}

	return result;
}
