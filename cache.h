#include <cstdint>
#include <vector>
#include <math.h>
using namespace std;

typedef unsigned long int  address_t;

//the Cache line sturct
typedef struct {
	bool valid;
	bool isDirty;
	int32_t address;
	int32_t tag;
} Cache_line;

// ------------------------------- Cache ------------------------------- //
class Cache {
public:
	//constructor
	Cache(unsigned BSize, unsigned LSize, unsigned LAssoc) : offset_bit_size(BSize), set_bit_size(LSize - BSize - LAssoc), tag_bit_size(32 - set_bit_size - offset_bit_size), num_of_ways(pow(2, LAssoc)), num_of_lines(pow(2, set_bit_size)) {
		ways_array = new Cache_line*[num_of_ways];
		for (unsigned i = 0; i < num_of_ways; i++) {
			ways_array[i] = new Cache_line[num_of_lines];
			for (unsigned j = 0; j < num_of_lines; j++) {
				ways_array[i][j].valid = false;
			}
		}
		lru_array = new vector<int>[num_of_lines];
	}

	//destructor
	~Cache() {
		for (unsigned i = 0; i < num_of_ways; i++) {
			delete[] ways_array[i];
		}
		delete[] ways_array;
		delete[] lru_array;
	}

	//public functions
	bool readWriteCache(address_t address);
	bool add2Cache(bool& isDirty, address_t& removed_address, address_t added_address);
	void removeCache(address_t address);
	void updateDirty(address_t address);
	void updateLRU(address_t address);

private:
	//pirvate parameters
	unsigned offset_bit_size;
	unsigned set_bit_size;
	unsigned tag_bit_size;
	unsigned num_of_ways;
	unsigned num_of_lines;
	Cache_line** ways_array;
	vector <int>* lru_array;

	//private function
	void updateLRU(int way_num, int set_num);
};

