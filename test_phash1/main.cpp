#include "pHash.h"
#include "pHash_cpp_wrapper.h"

#include <iostream>
#include <string>
#include <strstream>
#include <vector>

using namespace std;

const int num_mod_files = 5;

#define TEXT_PATH "..\\"

const char forig[] = TEXT_PATH "roman_empire_short.txt";
//char forig[] = "..\\roman_empire1.txt";

const char* modfilenames[] =
	{
		TEXT_PATH "roman_empire_mod1.txt",
		TEXT_PATH "roman_empire_mod2.txt",
		TEXT_PATH "roman_empire_mod3.txt",
		TEXT_PATH "roman_empire_different.txt",
		TEXT_PATH "roman_empire_bonjovi.txt" };

const char * GetModFilename(int index)
{
	return modfilenames[index];
}

int main()
{
	
	

	TextHash_Wrapper thw_orig;
	TextHash_Wrapper thw_mod[num_mod_files];
	thw_orig.ph_texthash(forig);
	cout << "Original number of points: " << thw_orig.GetNPoints() << endl;
	for (int i = 0; i < num_mod_files; i++)
	{
		const char *filename = GetModFilename(i);
		cout << filename << endl;
		thw_mod[i].ph_texthash(filename);
		cout << "Mod " << (i + 1)
			<< " number of points: " << thw_mod[i].GetNPoints()
			<< endl;
	}

	for (int i = 0; i < num_mod_files; i++)
	{
		TextMatch_Wrapper tmw;
		TextHash_Wrapper::ph_compare_text_hashes(
			&thw_orig, &thw_mod[i], &tmw);
		cout << endl;
		cout << "number of match objects: " << tmw.GetNMatches() << endl;
		cout << "lengths of match objects between original and modified " << (i+1) << ":" << endl;
		cout << tmw << endl;
		cout << endl;
		cout << "similarity of : " << forig << " and " << GetModFilename(i) << endl 
			<< tmw.GetSimilarity() << endl;
		cin.get();

	}
	/*cout << "Press enter to continue:";
	cin.get();*/
	//cout << thw;
	cout << endl;

	return 0;
}