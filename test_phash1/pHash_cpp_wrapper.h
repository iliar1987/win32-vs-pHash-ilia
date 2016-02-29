#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "pHash.h"

class TextHash_Wrapper;
std::ostream& operator << (std::ostream& o, const TextHash_Wrapper& pw);
class TextMatch_Wrapper;

class TextHash_Wrapper
{
	TxtHashPoint* phash_vec;
	unsigned int npoints;
	bool assigned;
	void PopulateSelf(unsigned int npoints_, TxtHashPoint* arr)
	{
		if (assigned)
		{
			Destroy();
		}
		assigned = true;
		npoints = npoints_;
		phash_vec = arr;
	}
	TextHash_Wrapper(const TextHash_Wrapper &);
public:
	static bool ph_compare_text_hashes(const TextHash_Wrapper *thw1,
		const TextHash_Wrapper *thw2, TextMatch_Wrapper* result_out);

	void Destroy()
	{
		if (assigned)
		{
			delete[] phash_vec;
			assigned = false;
		}
	}
	~TextHash_Wrapper() { Destroy(); }

	bool ph_texthash(const string &filename);

	TextHash_Wrapper() { assigned = false; npoints = 0; }

	unsigned int GetNPoints() const { return npoints; }
	bool IsAssigned() { return assigned; }

	friend std::ostream&  operator << (std::ostream& o, const TextHash_Wrapper& pw);
};

class TextMatch_Wrapper
{
	int nmatches;
	TxtMatch *matches;
	bool assigned;
	void SetValues(int nmatches_, TxtMatch* arr_, unsigned int na, unsigned int nb);
	TextMatch_Wrapper(const TextMatch_Wrapper&);
	unsigned int na, nb;
public:
	void Destroy()
	{
		if (assigned)
		{
			delete[] matches;
			assigned = false;
		}
	}
	~TextMatch_Wrapper() { Destroy(); }
	TextMatch_Wrapper() { assigned = false; nmatches = 0; }
	unsigned int GetNMatches() const
	{
		return nmatches;
	}
	bool IsAssigned() { return assigned; }
	friend class TextHash_Wrapper;
	friend std::ostream&  operator << (std::ostream& o, const TextMatch_Wrapper& pw);
	double GetSimilarity();
};
