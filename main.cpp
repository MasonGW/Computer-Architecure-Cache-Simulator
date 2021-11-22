// to compile: clang++-7 -pthread -std=c++17 -o main main.cpp
// To run: ./main 4 2 cache

#include<iostream>
#include<fstream>
#include<cstdlib> 
#include<vector>

using namespace std;

const int MAX_SIZE = 1000;
//----------------------------------------------
class Entry {
public:
  Entry();
  ~Entry();
  void display(ofstream& outfile);

  void set_tag(int _tag) { tag = _tag; }
  int get_tag() { return tag; }

  void set_valid(bool _valid) { valid = _valid; }
  bool get_valid() { return valid; }

  void set_ref(int _ref) { ref = _ref; }
  int get_ref() { return ref; }

private:  
  bool valid;
  unsigned tag;
  int ref;
};

class Cache {
public:
  Cache(int, int);
  ~Cache();

  void display(ofstream& outfile);


  int get_index(unsigned long addr);
  int get_tag(unsigned long addr);

  unsigned long retrieve_addr(int way, int index);
  
  bool hit(ofstream& outfile, unsigned long addr);

  void update(ofstream& outfile, unsigned long addt);

  
private:
  int assoc;
  unsigned num_entries;
  int num_sets;
  Entry **entries;
};
//----------------------------------------------------
int main(int argc, char*argv[]) {

  if (argc < 2) {
    cout << "Usage: " << endl;
    cout << "   ./file_process filename" << endl;
    return 0;
  }

  /* get base file name from command-line */
  string filename = argv[3];

  /* create input and output filenames */
  string input_filename = filename + "_input";
  string output_filename = filename + "_output";

  /* create input and output files streams */
  ofstream output;
  ifstream input;

  /* open input stream for reading */
  input.open(input_filename);

  /* check if input stream has been succesfully opened; bail otherwise */
  if (!input.is_open()) {
    cerr << "Could not open input file " << input_filename << ". Exiting ..." << endl;
    exit(0);
  }
    
  unsigned long *nums = new unsigned long[MAX_SIZE];
  int count = 0;
  while (!input.eof() && count < MAX_SIZE) {
    input >> nums[count];
    count++;
  }

  /* done reading from input file; close the stream */
  input.close();
  
  /* open output file stream for writing */
  output.open(output_filename);

  /* no need to check if output file is open; we will create new file if it doesn't exist; 
     overwrite otherwise */
  
  int misses;
  unsigned cache_size = atoi(argv[2]);
  unsigned assoc = atoi(argv[2]);
  

std::vector<int> vec;

int vec_size;
for(int vecSize = 0; vecSize < assoc; vecSize++){ //populates the vector with 0's
vec.push_back(0);
}
  int missArr[atoi(argv[1])];
  int miss;
int hit;
int distance;
for(int i = 0; i < count; i++){ // used to iterate through nums
  hit = 0;
  miss = 0;
  for(int j = 0; j < assoc; j++){ // Used to iterate through cache
    if (nums[i]==vec.at(j)){ //these keep tracks of hits, and the location of the hit
    hit++;  
    distance = j;
    }
  }
if (hit > 0)
      {
        // erase value from current location, add to front
        vec.erase(vec.begin()+distance);
        vec.push_back(nums[i]);
      }
  else{
        miss++; //adds one to the miss counter to check if hit or miss

        vec.pop_back(); //removes number at back of vec
        vec.insert(vec.begin(), nums[i]); //adds number at the beginning of the vec
      
      }
 missArr[i] = miss;

}
  // States whether the value hit or missed based on the miss value
  for (int value = 0; value < count; value++){
  if(missArr[value] > 0)
  {
    cout << nums[value] << " : MISS" << endl;    
  }
 else{
    cout << nums[value] << " : HIT" << endl;
  }
  }

  /* check if the correct number of arguments have been passed; bail otherwise */
  if (argc < 4) {
    cout << "Usage: " << endl;
    cout << "   ./cache num_entries associativity filename" << endl;
    return 0;
  }

  /* get args; all args come in as strings; need to convert to int with atoi() */
  unsigned entries = atoi(argv[1]);
  //unsigned assoc = atoi(argv[2]);

  input_filename = argv[3];

  /* print the args */
  cout << "Number of entries: " << entries << endl;
  cout << "Associativity: " << assoc << endl;
  cout << "Input File Name: " << input_filename << endl;
  
  output.close();
  return 0;
}
