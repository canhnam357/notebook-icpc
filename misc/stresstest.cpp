int main() {
    cout << "Compiling..." << endl;
    system("g++ main.cpp -o main_1");
    system("g++ main_2.cpp -o main_2");
    for(int test = 1; test <= 2000; test++) {
        generate_test();
        cout << "Test " << test << ": ";
        if(system("cat input.txt | ./main_1 > output1.txt") || system("cat input.txt | ./main_2 > output2.txt")) {
            cout << "Runtime error\n";
            return 0;
        }
        if(system("diff output1.txt output2.txt") != 0) {
            cout << "Wrong!\n";
            return 0;
        }
        else {
            cout << "OK!\n";
        }
    }
}
