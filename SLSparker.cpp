#include "LifeAPI.h"
#include <iostream> 
#include <vector>
#include <string> 
#include <time.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <tuple>

using namespace std; 

void InitSL(LifeState* states[])
{
   	states[0] = NewState("b2o$obo$bo!");
	states[1] = NewState("bo$obo$2o!");
	states[2] = NewState("bo$obo$b2o!");
	states[3] = NewState("2o$obo$bo!");
	states[4] = NewState("bo$obo$obo$bo!");
	states[5] = NewState("b2o$o2bo$b2o!");
	states[6] = NewState("b2o$o2bo$bobo$2bo!");
	states[7] = NewState("bo$obo$o2bo$b2o!");
	states[8] = NewState("2bo$bobo$o2bo$b2o!");
	states[9] = NewState("b2o$o2bo$obo$bo!");
	states[10] = NewState("bo$obo$o2bo$bobo$2bo!");
	states[11] = NewState("b2o$o2bo$bo2bo$2b2o!");
	states[12] = NewState("2bo$bobo$o2bo$obo$bo!");
	states[13] = NewState("2b2o$bo2bo$o2bo$b2o!");
	states[14] = NewState("2bo$bobo$obo$bo!");
	states[15] = NewState("bo$obo$bobo$2bo!");
	states[16] = NewState("2b2o$bobo$obo$bo!");
	states[17] = NewState("2bo$bobo$obo$2o!");
	states[18] = NewState("bo$obo$bobo$2b2o!");
	states[19] = NewState("2o$obo$bobo$2bo!");
	states[20] = NewState("2o$2o$2b2o$2b2o!");
	states[21] = NewState("2b2o$2b2o$2o$2o!");
	states[22] = NewState("bo$obo$bo!");
	states[23] = NewState("2b2o$3bo$3o$o!");
	states[24] = NewState("2b2o$2bo$obo$2o!");
	states[25] = NewState("o$3o$3bo$2b2o!");
	states[26] = NewState("2o$obo$2bo$2b2o!");
	states[27] = NewState("2o$o$b3o$3bo!");
	states[28] = NewState("2o$bo$bobo$2b2o!");
	states[29] = NewState("3bo$b3o$o$2o!");
	states[30] = NewState("2b2o$bobo$bo$2o!");
	states[31] = NewState("4b2o$3bobo$3b2o$b2o$obo$2o!");
	states[32] = NewState("2o$obo$b2o$3b2o$3bobo$4b2o!");
	states[33] = NewState("b2o$obo$2o!");
	states[34] = NewState("2o$obo$b2o!");
	states[35] = NewState("3o$b3o!");
	states[36] = NewState("b3o$3o!");
	states[37] = NewState("o$2o$2o$bo!");
	states[38] = NewState("bo$2o$2o$o!");
	states[39] = NewState("b2o$3bo$o$b2o!");
	states[40] = NewState("b2o$o$3bo$b2o!");
	states[41] = NewState("2bo$o2bo$o2bo$bo!");
	states[42] = NewState("bo$o2bo$o2bo$2bo!");
	states[43] = NewState("5bo$4bobo$3bo2bo$2bob2o$bobo$o2bo$b2o!");
	states[44] = NewState("b2o$o2bo$bobo$2bob2o$3bo2bo$4bobo$5bo!");
	states[45] = NewState("bo$obo$o2bo$b2obo$3bobo$3bo2bo$4b2o!");
	states[46] = NewState("4b2o$3bo2bo$3bobo$b2obo$o2bo$obo$bo!");
	states[47] = NewState("b2o$o2bo$o2bo$b2o!");
	states[48] = NewState("2o$2o!");
	states[49] = NewState("2b2o$3bo$o$2o!");
	states[50] = NewState("2o$o$3bo$2b2o!");
	states[51] = NewState("o$o$o!");
	states[52] = NewState("3o!");
}

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

class SearcRect
{
public:
	int minx, miny, width, height; 
	SearcRect() {} 
	
	void Init(int minx_, int miny_, int width_, int height_)
	{
		minx = minx_; 
		miny = miny_; 
		width = width_;
		height = height_;		
	}
	
	
	int maxX()
	{
		return minx + width; 
	}
	
	int maxY()
	{
		return miny + height; 
	}
	
	int Area()
	{
		return width * height;
	}
	
	void Print()
	{
		cout << minx << "," << miny << "," << width << "," <<  height;
	}
};

class SearchParams
{
public:
	SearcRect sl1, sl2, top; 
	
	string top_rle; 
	vector<string> target_rle; 
	int max_result = 1000000;
	int max_gen = 100; 
	bool two_only = false; 
	int report_top = 1000000;
	void Print()
	{
		cout << "Searching Area:\n";
		cout << "max-gen:" << max_gen << "\n";
		cout << "sl1:";
		sl1.Print();
		cout << "\n";
		
		cout << "sl2:";
		sl2.Print();
		cout << "\n";
		
		cout << "top:";
		top.Print();
		cout << "\n";
	}
	
	SearchParams()
	{
		sl1.Init(-10, -7, 20, 7); 
		sl2.Init(-10, -7, 20, 7);
		top.Init(-10, -8, 20, 1); 
	}
	
	int maxX()
	{
		return max(max(sl1.maxX(), sl2.maxX()), top.maxX()); 
	}
	
	int maxY()
	{
		return max(max(sl1.maxY(), sl2.maxY()), top.maxY()); 
	}
	
	uint64_t Total()
	{
		
		uint64_t res = 1; 
		res *= sl1.Area(); 
		res *= sl2.Area(); 
		res *= top.Area(); 
		res *= 53 * 53; 
		
		if(top_rle == "")
			res *= 53; 
		
		return res;
	}
	
};

int tonumber(const string& str)
{
	return atoi(str.c_str());
}

bool ReadParams(std::string fname, SearchParams& params)
{
	std::ifstream infile;
	infile.open(fname.c_str(), std::ifstream::in);

	std::string max_gen = "max-gen";
	std::string sl1 = "sl1-range";
	std::string sl2 = "sl2-range";
	std::string top = "top-range";
	std::string target_rle = "target-rle";
	std::string top_rle = "top-rle";
	std::string max_result = "max-result";
	std::string two_only = "two-only";
	std::string report_top = "report-top";
	
	std::string line; 
	
	while (std::getline(infile, line))
	{
		try
		{
			std::vector<std::string> elems;
			split(line, ' ', elems);
			
			if(elems.size() == 0)
				continue; 
			
			if(elems[0] == report_top) 
				params.report_top = tonumber(elems[1]);
			
			if(elems[0] == max_gen) 
				params.max_gen = tonumber(elems[1]);
			
			if(elems[0] == max_result) 
				params.max_result = tonumber(elems[1]);
			
			if(elems[0] == two_only) 
				params.two_only = true; 
			
			if(elems[0] == sl1) 
				params.sl1.Init(tonumber(elems[1]), tonumber(elems[2]), tonumber(elems[3]), tonumber(elems[4]));
			
			if(elems[0] == sl2) 
				params.sl2.Init(tonumber(elems[1]), tonumber(elems[2]), tonumber(elems[3]), tonumber(elems[4]));
			
			if(elems[0] == top) 
				params.top.Init(tonumber(elems[1]), tonumber(elems[2]), tonumber(elems[3]), tonumber(elems[4]));
			
			if(elems[0] == target_rle) 
				params.target_rle.push_back(elems[1]);
			
			if(elems[0] == top_rle) 
				params.top_rle = elems[1];
		}
		catch(const std::exception& ex)
		{
		}
	}
	
	if(params.target_rle.size() == 0)
		return false;
	
	return true; 
}

LifeIterator* CreateIterator(LifeState* sls[], int num, const SearcRect& box)
{
	return NewIterator(sls, box.minx, box.miny, box.width, box.height, num);
}

pair<int, int> OrderOfMagnitude(uint64_t val)
{
	uint64_t o = 1; 
	int deg = 0; 
	while(o < val)
	{	
		o *= 10; 
		deg++; 
	}
	
	o /= 10; 
	deg--; 
	
	float x = (float)(val / o);
	
	return pair<int, int>((int)(x + 0.5), deg); 
}

void PrintPhysicalNotation(int64_t val)
{
	pair<int, int> val_dec = OrderOfMagnitude(val);
	printf("%d*10^%d", val_dec.first, val_dec.second);
	
}

int sumvec(vector<vector<tuple<int, int, string> > >& vector)
{
	int sum_of_elems = 0; 
	
	for (auto& n : vector)
		sum_of_elems += n.size();
	
	return sum_of_elems;
}

int main (int argc, char *argv[]) 
{
	
	if(argc < 2)
	{
		std::cout << "Usage SLSparker.exe <in file>";
		exit(0);
	}
	
	SearchParams search_params; 
	bool valid = ReadParams(argv[1], search_params);
	
	if(!valid)
	{
		cout << "Please input a target-rle line in the input file";
		exit(0);
	}
	
	cout << "Thank you for shosing SLSparker application\n";
	cout << "Your search params:\n ";
	search_params.Print();
	
	cout << "Your search is consisting of ";
	PrintPhysicalNotation(search_params.Total()); 
	cout << " Soups\n";
	
	//search_params.Print(); 
	
	
	//cout << "Soups\n";
	vector<vector<tuple<int, int, string> > > results(search_params.target_rle.size()); 
	
	long long count = 0; 

	#pragma omp parallel
	{
	New();
   
	LifeState* sls[53];
	InitSL(sls);
	
	
	LifeIterator *iter1 = CreateIterator(sls, 53, search_params.sl1);
	LifeIterator *iter2 = CreateIterator(sls, 53, search_params.sl2);
	
	LifeIterator *iter3 = NewIterator(sls[0], 1, 1, 1, 1); 
	
	if(!search_params.two_only)
	{		
		if(search_params.top_rle != "")
		{
			LifeState* init = NewState(search_params.top_rle.c_str());
			iter3 = NewIterator(init, search_params.top.minx, search_params.top.miny, search_params.top.width, search_params.top.height);
		}
		else
		{
			iter3 = CreateIterator(sls, 53, search_params.top);
		}
	}
	LifeState* gld = NewState("3o$o$bo!", search_params.maxX() + 10, search_params.maxY() + 10);
	
	vector<TargetLocator*> locs;

	for(int i = 0; i < search_params.target_rle.size(); i++)
		locs.push_back(NewTargetLocator(search_params.target_rle[i].c_str()));

	do{
    #pragma omp single nowait
	{
		#pragma omp critical
		{
			count++;
			
			if(count % 1000000 == 0)
				cout << "Reached:" << count << ", and found " << sumvec(results) << " results \n";
		}
		
		if(Validate(iter1, iter2) != FAIL)
		{
			New();
			PutState(gld);
			PutState(iter1);
			PutState(iter2);
			
			if(!search_params.two_only)
				PutState(iter3);
			
			bool fail = false; 
			
			int pop = GetPop();
			Run(1);
			
			if(pop != GetPop())
				fail = true;
			
			Run(1);
			
			if(pop != GetPop())
				fail = true; 
			
			if(fail == false)
			{

				Capture(1);
							
				for(int i = 0; i < search_params.max_gen && fail == false; i++)
				{
					Run(1);
					
					if(i%2 == 0)
					{
						if(IsSame(1))
							fail = true;
						
						Capture(1);
					}	
					
					int idx; 
					
					if(ContainsLocatorArray(&locs[0], locs.size(), idx) == YES)
					{
						int pop = GetPop(); 
						
						New();
						PutState(gld);
						PutState(iter1);
						PutState(iter2);
						
						if(!search_params.two_only)
							PutState(iter3);

						#pragma omp critical
						{
							results[idx].push_back(tuple<int, int, string>(pop, i, GetRLE(GlobalState)));
							//printf("Found at generation %d\n", i);
							//printf(GetRLE(GlobalState));
							//printf("\n");
						}
					}
				}
			}
		}
	}
   }while(Next(iter1, iter2, iter3, NO) && search_params.max_result > sumvec(results));
   //}while(Next(iter1, iter3, NO));
	}
	
	for(int j = 0; j < results.size(); j++)
	{
		cout << "\n\n\nStarting Report for case #" << j << "\n";
	
		sort(results[j].begin(), results[j].end()); 
		
		//for(int i = 0; i < results[j].size() && i < search_params.report_top; i++)
		//{
			//cout << "\nSoup " << i << " Generation " << get<1>(results[j][i]);
		//}
		
		cout << "\n\nThe soups\n\n";
		
		for(int i = 0; i < results[j].size() && i < search_params.report_top; i++)
		{
			cout << get<2>(results[j][i]) << "100$";
		}
	}	
	
	printf("!");
	printf("\n\nFINISH");
	getchar();
}