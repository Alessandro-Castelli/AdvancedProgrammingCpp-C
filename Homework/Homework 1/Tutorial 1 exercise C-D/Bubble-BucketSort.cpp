#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
/**
 * General Sort Class
 */
class Sort{
    protected:
        vector<int> data;

    public:
        void show();
        vector<int> getData();
};

/**
 * @return vector
 */
vector<int> Sort::getData(){
    return data;
}

/**
 * This method allows you to show the vector
 */
void Sort::show() {
    int size = this->data.size();
    cout<<"\nThis is the vector: "<<endl;
    for (int i = 0; i < size; ++i) {
        cout<< this->data[i]<<' ';
    }
}

/**
 * Class in which BubbleSort is implemented
 */
class BubbleSort : public Sort{
    public:
        BubbleSort(vector<int> input);
        void bubbleS();
};

/**
 * Constructor of the class BubbleSort
 * @param input
 */
BubbleSort::BubbleSort(vector<int> input) {
    this->data=input;
}

/**
 * BubbleSort algorithm
 */
void BubbleSort::bubbleS() {
    int size = data.size();

    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size - i -1 ; j++) {
            if (data[j]>data[j+1]){
                int temp = data[j];
                data[j]=data[j+1];
                data[j+1]=temp;
            }
        }
    }
}

/**
 * BucketSort Class
 */
class BucketSort:public Sort{
    public:
        BucketSort(vector<int> input);
        void bucketS();
};

/**
 * BucketSort algorithm
 */
void BucketSort::bucketS() {
    int minValue = data[0];
    int maxValue = data[0];

    //Find Maximum and Minimum
    for (int i = 1; i < this->data.size(); i++)
    {
        if (data[i] > maxValue)
            maxValue = data[i];
        if (data[i] < minValue)
            minValue = data[i];
    }

    int bucketLength = maxValue - minValue + 1;
    vector<vector<int>> bucket(bucketLength);


    for (int i = 0; i < bucketLength; i++)
    {
        bucket[i] = vector<int>();
    }

    for (int i = 0; i < this->data.size(); i++)
    {
        bucket[data[i] - minValue].push_back(data[i]);
        //This command is distributing the elements of the `data`
        //vector into the corresponding "buckets" based on their
        // value minus `minValue`.
    }

    int k = 0;
    for (int i = 0; i < bucketLength; i++)
    {
        int bucketSize = bucket[i].size();

        if (bucketSize > 0)
        {
            for (int j = 0; j < bucketSize; j++)
            {
                data[k] = bucket[i][j];
                k++;
            }
        }
    }
}

/**
 * Constructor of the class BucketSort
 * @param input
 */
BucketSort::BucketSort(vector<int> input) {
    this->data=input;
}

int main() {

    random_device rd;  // Create a hardware- or software-based random number generator
    mt19937 gen(rd()); // Initialize a Mersenne Twister generator with a random seed

    int min_value = 1;     // Minimum value that you can find in the input
    int max_value = 100;   // Maximum value that you can find in the input

    // Define uniform distribution between min_value and max_value
    uniform_int_distribution<int> distribution(min_value, max_value);

    int dimInput = 10000;
    vector<int> elements(dimInput);

    // Generate dimInput random numbers
    for (int i = 0; i < dimInput; i++) {
        elements[i] = distribution(gen);
    }

    auto start = chrono::high_resolution_clock::now(); //Start the conometer

    BubbleSort toOrder(elements);
    //toOrder.show();
    toOrder.bubbleS();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << "\n" <<"Total time BubbleSort: " << diff.count() << " s\n";
    toOrder.show();

    
    vector<int> elements2(dimInput);
    // Genera alcuni numeri casuali
    for (int i = 0; i < dimInput; i++) {
        elements2[i] = distribution(gen);
    }

    auto start2 = std::chrono::high_resolution_clock::now(); //Start the conometer
    BucketSort toOrder2(elements2);
    //toOrder2.show();
    toOrder2.bucketS();

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff2 = end2-start2;
    std::cout << "\n" <<"Total time BucketSort: " << diff2.count() << " s\n";
    toOrder2.show();

    return 0;
}
