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
